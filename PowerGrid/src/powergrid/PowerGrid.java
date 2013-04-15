package powergrid;

import java.awt.Window;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.logging.ConsoleHandler;
import java.util.logging.Formatter;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.LogRecord;
import java.util.logging.Logger;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import org.powerbot.Boot;
import org.powerbot.game.client.Client;
import powergrid.control.Mapper;
import powergrid.control.ScriptLoader;
import powergrid.control.TaskManager;
import powergrid.control.interaction.InteractionController;
import powergrid.control.uicontrols.RSInteractor;
import powergrid.model.structure.WorldMap;
import powergrid.plugins.Plugin;
import powergrid.plugins.PluginInfo;
import powergrid.plugins.PluginLoader;
import powergrid.plugins.PowerGridPlugin;
import powergrid.task.Task;
import powergrid.view.ControlPanel;

/**
 * Main class for PowerGrid.
 * <p/>
 * This class deals with starting and stopping PowerGrid, loading and starting 
 * available scripts, and handling configuration settings and parameters.
 * <p/>
 * PowerGrid's main method can take the following arguments:
 * <dl>
 *   <dt>-d</dt>
 *   <dd>PowerGrid developer mode. Setting this flag logs more detailed messages
 *       to the console.</dd>
 *   <dt>-p</dt>
 *   <dd>Specify a custom Plugins directory. For example: 
 *       <code>java -jar PowerGrid.jar -p someFolder\customPluginDirectory</code> will look 
 *       for plugins in the directory named <code>someFolder\customPluginDirectory</code>
 *       instead of the default "plugins" directory.</dd>
 *   <dt>-u</dt>
 *   <dd>Forces PowerGrid to update the RSBot jar file. This must be the first 
 *       parameter. After the update, PowerGrid will restart with the other 
 *       specified parameters.</dd>
 * </dl>
 * <p/>
 * @author Chronio
 */
public class PowerGrid {
    
    /** The name of PowerGrid, which is "PowerGrid". */
    public static final String NAME = "PowerGrid";
    
    /** The PowerGrid version. */
    public static final double VERSION = 0.1;
    
    /** The PowerGrid Logger. */
    public static final Logger LOGGER = Logger.getLogger(NAME);
    
    /** The startup delay in milliseconds. 
     * <p/>
     * PowerGrid waits this amount of milliseconds after the Client is loaded
     * before initializing itself. This is to prevent unexpected Exceptions.
     */
    public static final int STARTUP_DELAY = 800;
    
    /** The PowerGrid instance. */
    public static PowerGrid PG = null;
    
    /** The default plugin directory, which is "plugins". */
    public static File pluginDirectory = new File("plugins");
    
    /** The path to the file that will be used as icon. */
    public static final String ICON_PATH = "powergrid/images/icon_small.png";
    
    private static Icon icon = null;

    /**
     * Returns the PowerGrid icon to be used on user interfaces and such.
     * <p/>
     * The Icon is cached once it's created, so consecutive calls return the 
     * same Icon.
     * @return the PowerGrid Icon
     */
    public static Icon getIcon() {
        if (icon == null) {
            icon = new ImageIcon(ClassLoader.getSystemResource(ICON_PATH));
        }
        return icon;
    }
    
    /**
     * Main method of PowerGrid. 
     * <p/>
     * This method starts RSBot and integrates PowerGrid in it. 
     * <p/>
     * @param args the command-line arguments
     */
    public static void main(String[] args) {
        setupLogger(LOGGER, new ConsoleHandler(), false);
        RSBotUpdater updater = new RSBotUpdater();
        
        if (args.length > 0 && args[0].equals("-u")) {
            updater.update();
            String[] newArgs = new String[args.length - 1];
            for (int i = 1; i < args.length; i++) {
                newArgs[i - 1] = args[i];
            }
            try {
                updater.useCmdArgs(newArgs).restart();
            } catch (IOException e) {
                LOGGER.log(Level.SEVERE, "Restart failed", e);
                System.exit(1);
            }
        }
        
        // launch RSBot
        try {
            Boot.main(new String[0]);
            updater.useCmdArgs(args).hook();
            LOGGER.info("RSBot started.");
        } catch (Exception e) {
            LOGGER.log(Level.SEVERE, "RSBot failed to start.", e);
            System.exit(1);
        }
        
        boolean devMode = false;
        
        Iterator<String> it = Arrays.asList(args).iterator();
        while (it.hasNext()) {
            String arg = it.next();
            switch (arg) {
                case "-p":
                    if (it.hasNext()) {
                        File pluginDir = new File(it.next());
                        if (pluginDir.isDirectory()) {
                            pluginDirectory = pluginDir;
                            LOGGER.info("Custom plugin directory set at " 
                                    + pluginDir.getPath());
                        }
                    }
                    break;
                case "-d":
                    devMode = true;
                    break;
            }
        }
        // Wait for Client's Thread to start
        waitForClient();
        
        // when RSBot has loaded the client, there are no updates.
        updater.unhook();
        
        PG = new PowerGrid(org.powerbot.core.Bot.client());
        
        LOGGER.info("Plugins loaded. Starting PowerGrid...");
        if (PG.launch(devMode)) {
            LOGGER.info("PowerGrid started and running");
        } else {
            LOGGER.severe("PowerGrid failed to start, shutting down");
            System.exit(1);
        }
    }
    
    /**
     * Sets up the provided Logger to use the custom Formatter of PowerGrid.
     * <p/>
     * It changes the Formatter of all registered handlers to a PGFormatter 
     * instance.
     * @param l the Logger to configure
     * @param h the Handler to apply to the Logger
     * @param useParentHandlers true to keep parent handlers, false to disable.
     */
    public static void setupLogger(Logger l, Handler h, 
            boolean useParentHandlers) {
        l.setUseParentHandlers(useParentHandlers);
        h.setFormatter(new PGFormatter());
        l.addHandler(h);
    }
    
    /**
     * Waits for the RSBot client to start, and returns after that.
     * <p/>
     * There is a delay in order to give RSBot the time to properly 
     * initialize itself. Therefore, it is safe to assume that most RSBot 
     * functions are available after this method returns. The delay is equal to
     * the amount of milliseconds specified in <code>STARTUP_DELAY</code>
     */
    public static void waitForClient() {
        Thread main = Thread.currentThread();
        ThreadGroup mainGroup = main.getThreadGroup();
        ThreadGroup[] groups = new ThreadGroup[1];
        
        while (true) {
            // find all ThreadGroups directly in the main ThreadGroup
            mainGroup.enumerate(groups, false);
            if (groups[0] != null && 
                    org.powerbot.core.Bot.instantiated() &&
                    org.powerbot.core.Bot.client() != null) {
                // RSBot's ThreadGroup is active and the bot is instantiated.
                break;
            }
            Task.sleep(50);
        }
        // Give the GUI time to properly initialize before continuing.
        Task.sleep(STARTUP_DELAY);
    }
    
    private boolean isRunning = false;
    private boolean devmode = false;
    
    private ControlPanel theControlPanel = null;
    
    private ArrayList<Plugin> plugins;
    
    private Client client;
    private InteractionController iController;
    private Mapper mapper;
    private RSInteractor rsInteractor;
    private TaskManager taskManager;
    private ScriptLoader taskManagerLoader;
    
    private Thread terminationThread;
    
    /**
     * Constructs a PowerGrid instance that can operate on the given Client.
     * @param c the RSBot Client object
     */
    public PowerGrid(Client c) {
        assert c != null;
        plugins = new ArrayList<>();
        client = c;
        iController = new InteractionController();
        mapper = new Mapper().withClient(client);
        rsInteractor = new RSInteractor().useClient(client)
                .useWorldMap(mapper.getWorldMap());
        taskManager = new TaskManager();
        taskManagerLoader = null;
        terminationThread = null;
    }
    
    /**
     * Loads Plugins from the specified directory.
     * <p/>
     * When the directory does not exist, this method does nothing.
     * @param directory the directory from which to load.
     */
    public void loadPlugins(File directory) {
        assert directory != null;
        if (directory.exists()) {
            Plugin[] ps = new PluginLoader(directory).getLoadedPlugins();
            plugins.ensureCapacity(plugins.size() + ps.length);
            for (Plugin p : ps) {
                loadPlugin(p);
            }
        }
    }
    
    /**
     * Returns an unmodifiable List containing the loaded Plugins.
     * @return an unmodifiable List containing the loaded Plugins.
     */
    public List<Plugin> getPlugins() {
        return Collections.unmodifiableList(plugins);
    }
    
    
    /**
     * Loads the specified Plugin.
     * @param p the Plugin to load.
     */
    public void loadPlugin(Plugin p) {
        assert p != null : "Null value for Plugin";
        String name = p.getClass().getAnnotation(PluginInfo.class).name();
        plugins.add(p);
        try {
            p.withPowerGrid(this);
            p.setUp();
            LOGGER.info("Plugin loaded: " + name);
        } catch (Exception e) {
            LOGGER.log(Level.WARNING, "Failed to load Plugin " + name, e);
            plugins.remove(p);
        }
    }
    
    /**
     * unloads the specified Plugin
     * @param p the Plugin to unload
     * @return true if the plugin list changed as a result of this call, false 
     *         otherwise.
     */
    public boolean removePlugin(Plugin p) {
        assert p != null : "Null value for Plugin";
        int index = plugins.indexOf(p);
        if (index < 0) {
            return false;
        } else {
            plugins.remove(index);
            p.tearDown();
            return true;
        }
    }
    
    /**
     * Looks up the Plugin that provides the specified Task
     * @param t the Task to look up the Plugin for.
     * @return the Plugin for the Task, or null if no Plugin was found.
     */
    public Plugin lookupPluginForTask(Task t) {
        if (t == null) {
            return null;
        }
        for (Plugin p : getPlugins()) {
            if (p.getPublicTasks().contains(t.getClass())) {
                return p;
            }
        }
        return null;
    }
    
    /** 
     * @return the Client of RSBot.
     */
    public Client client() {
        return client;
    }
    
    /**
     * @return the InteractionController used to handle interactions.
     */
    public InteractionController interactionController() {
        return iController;
    }
    
    /*
     * @return the Mapper that maps the Runescape world.
     */
    public Mapper mapper() {
        return mapper;
    }
    
    /**
     * @return the RSInteractor used to interact with the Runescape interface.
     */
    public RSInteractor rsInteractor() {
        return rsInteractor;
    }
    
    /**
     * @return the TaskManager instance that schedules and executes Tasks.
     */
    public TaskManager taskManager() {
        return taskManager;
    }
    
    /**
     * @return the WorldMap instance contained in the Mapper.
     */
    public WorldMap worldmap() {
        return mapper().getWorldMap();
    }
    
    /**
     * Launches PowerGrid with the given settings.
     * <p/>
     * @param devmode true to enable developer mode, false to disable
     * @return whether the launch was successful
     */
    public boolean launch(boolean devmode) {
        if (isRunning) {
            return false;
        }
        this.devmode = devmode;
        return launch();
    }
    
    /**
     * Launches PowerGrid with the current (or default) settings.
     * <p/>
     * After launching PowerGrid, the Mapper will automatically start mapping 
     * and Tasks will be executed from the Task queue.
     * @return whether the launch was successful
     */
    public boolean launch() {
        if (isRunning) 
            return false;
        
        loadPlugin(new PowerGridPlugin());
        loadPlugins(pluginDirectory);
        LOGGER.info("starting PowerGrid...");
        LOGGER.fine("    (in Developer mode)");
        
        LOGGER.fine("Modifying RSBot JFrame...");
        Window[] ws = Window.getWindows();
        if (ws.length > 0 && ws[0] instanceof JFrame) {
            theControlPanel = ControlPanel.addControlPanel(ws[0], "South");
        }
        
        LOGGER.fine("ControlPanel created");
        
        if (taskManagerLoader == null) {
            taskManagerLoader = new ScriptLoader(taskManager);
        } else {
            taskManagerLoader = taskManagerLoader.copy();
        }
        
        taskManagerLoader.run();
        LOGGER.fine("TaskManager started");
        
        mapper().startMapping();
        LOGGER.fine("Mapper Started");
        
        terminationThread = new Thread(new PGTerminator());
        Runtime.getRuntime().addShutdownHook(terminationThread);
        theControlPanel.setMessage("PowerGrid has started");
        isRunning = true;
        
        return true;
    }
    
    /**
     * Terminates PowerGrid, disabling core functionality.
     * <p/>
     * PowerGrid can still be used for Pathfinding and such, but be aware that 
     * the WorldMap will not be updated and Tasks will not be executed anymore.
     * <p/>
     * @return whether the termination was successful
     */
    public boolean terminate() {
        if (!isRunning)
            return false;
        LOGGER.info("stopping PowerGrid...");
        theControlPanel.setMessage("PowerGrid stopping...");
        try {
            Runtime.getRuntime().removeShutdownHook(terminationThread);
            terminationThread = null;
        } catch (IllegalStateException e) {} // was already shutting down
        if (mapper().isMapping()) {
            mapper().stopMapping();
            LOGGER.fine("Mapper stopped");
        }
        
        theControlPanel.getParent().remove(theControlPanel);
        LOGGER.fine("ControlPanel removed");
        
        taskManagerLoader.stop();
        LOGGER.fine("TaskManager stopped");
        
        for (Plugin p : plugins) {
            p.tearDown();
        }
        LOGGER.fine("Plugins finalized");
        
        LOGGER.info("PowerGrid stopped");
        isRunning = false;
        return true;
    }

    /**
     * Returns whether PowerGrid is started in DevMode.
     * <p/>
     * Plugin developers can use this to enable or disable certain options depending
     * on this setting.
     * @return whether PowerGrid is running in Developer Mode.
     */
    public boolean isDevmode() {
        return devmode;
    }
    
    /**
     * Custom Formatter for the PowerGrid Logger.
     */
    public static class PGFormatter extends Formatter {
        @Override
        public String format(LogRecord record) {
            StringBuilder sb = new StringBuilder("[")
                    .append(record.getLoggerName())
                    .append(": ").append(record.getLevel()).append("] ")
                    .append(record.getMessage());
            Throwable thrown = record.getThrown();
            while (thrown != null) {
                sb.append("\n  caused by: ")
                        .append(thrown.getClass().getSimpleName())
                        .append("\n    ").append(thrown.getMessage());
                thrown = thrown.getCause();
            }
            return sb.append("\n").toString();
        }
    }
    
    /**
     * Runnable that ensures that PowerGrid is terminated gracefully in case 
     * of RSBot shutdown.
     */
    public class PGTerminator implements Runnable {
        /**
         * Attempts to terminate PowerGrid gracefully, or prints a warning 
         * message otherwise.
         */
        @Override public void run() {
            if (!terminate()) {
                LOGGER.severe("PowerGrid failed to terminate gracefully");
            }
        }
        
    }
}
