/*
 * Copyright 2012-2013 Patrick Kramer, Vincent Wassenaar
 * 
 * This file is part of PowerGrid.
 *
 * PowerGrid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PowerGrid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PowerGrid.  If not, see <http://www.gnu.org/licenses/>.
 */
package net.pgrid.loader;

import java.applet.Applet;
import java.applet.AppletContext;
import java.applet.AppletStub;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Font;
import java.awt.Insets;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JLabel;
import net.pgrid.loader.logging.Logger;

/**
 * This class functions as the window in which the Applet can run.
 * <p/>
 * It implements AppletStub to provide the Applet with a valid environment and
 * sets up the itself as a JFrame in which the Applet can draw.
 * <p/>
 * @author Patrick Kramer
 */
public class AppletFrame extends JFrame implements AppletStub {

    /** The Logger instance of this class. */
    private static final Logger LOGGER = Logger.get("APPLET");
    
    /**
     * The JLabel that shows the logging message.
     */
    protected JLabel label;
    private Applet applet = null;
    private RSVersionInfo info = null;

    /**
     * Creates a new AppletFrame instance.
     */
    public AppletFrame() {
        super("PowerGrid (Runescape client)");
    }
    
    /**
     * Initializes the AppletFrame.
     * <p/>
     * When this method returns the AppletFrame has been correctly set up and
     * made visible.
     */
    public synchronized void init() {
        label = new JLabel();
        createAndShowFrame();
    }

    /**
     * @return the loaded Applet, or null if no Applet is loaded.
     */
    public Applet getApplet() {
        return applet;
    }
    
    /**
     * @return the width of the internal Applet, or -1 if the Applet does not exist.
     */
    public int getAppletWidth() {
        return (applet != null ? applet.getWidth() : -1);
    }
    
    /**
     * @return the height of the internal Applet, or -1 if the Applet does not exist.
     */
    public int getAppletHeight() {
        return (applet != null ? applet.getHeight() : -1);
    }

    /**
     * Sets up the AppletFrame and shows it.
     */
    private void createAndShowFrame() {
        try {
            setIconImage(ImageIO.read(ClassLoader.getSystemResourceAsStream("net/pgrid/loader/icon.png")));
        } catch (IOException e) {
            // Since the icon is embedded in the jar file, this should never happen
            throw (Error) new InternalError("Cannot find jar resource").initCause(e);
        }
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        
        Insets in = getInsets();
        int bHeight = in.top + in.bottom;
        int bWidth = in.right + in.left;
        setSize(1056 + bWidth, 750 + bHeight);
        setMinimumSize(new Dimension(765 + bWidth, 540 + bHeight));
        setMaximumSize(new Dimension(3200 + bWidth, 1200 + bHeight));

        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        getContentPane().setBackground(Color.BLACK);

        label.setForeground(Color.GRAY.brighter());
        label.setFont(new Font("Consolas", Font.BOLD, 21));
        label.setHorizontalAlignment(JLabel.CENTER);
        add(label, "Center");

        setVisible(true);
    }

    /**
     * Takes the provided Applet instance and starts it in this Window.
     * <p/>
     * @param info the RSVersionInfo object to use for getting parameters for the client
     * @param a the Applet to start (should not be null)
     * @return true if the Applet started without Exceptions, false if an Exception occurred.
     * @throws NullPointerException if the provided Applet is null.
     */
    public synchronized boolean startApplet(RSVersionInfo info, Applet a) {
        showMessage("Starting Applet");
        this.info = info;
        applet = a;
        applet.setStub(this);
        try {
            applet.init();
            getContentPane().add(applet, BorderLayout.CENTER);
            getContentPane().remove(label);
            label = null;
            revalidate();
            applet.start();
            LOGGER.log("Applet started");
            return true;
        } catch (RuntimeException e) {
            LOGGER.log("Failed to start client.", e);
            return false;
        }
    }
    
    /**
     * Shows the given log message in the AppletFrame.
     * <p/>
     * If the client is already started, this method does nothing (as the 
     * message will never be visible anyway).
     * @param text the message to display
     */
    public synchronized void showMessage(final String text) {
        if (applet == null) {
            EventQueue.invokeLater(new Runnable() {
                @Override
                public void run() {
                    label.setText(text);
                }
            });
        }
    }

    @Override
    public void appletResize(int width, int height) {}

    @Override
    public String getParameter(String name) {
        return info.getAppletParameter(name);
    }

    @Override
    public URL getDocumentBase() {
        String codebase = info.getClientParameter("codebase");
        if (codebase != null) {
            try {
                return new URL(codebase);
            } catch (MalformedURLException e) {
                // This normally never happens, as the codebase was validated when
                // the client was downloaded. The reason we don't throw 
                // AssertionError here is, that we don't want to interfere 
                // with the running Runescape client.
                LOGGER.log("[WARNING] Applet requested codebase URL, but the codebase was invalid.");
            }
        }
        return null;
    }

    @Override
    public URL getCodeBase() {
        return getDocumentBase();
    }

    /**
     * Returns the AppletContext. 
     * <p/>
     * Since the Runescape Applet does not care about this, this method will 
     * always return {@code null}.
     * @return {@code null}
     */
    @Override
    public AppletContext getAppletContext() {
        return null;
    }
}
