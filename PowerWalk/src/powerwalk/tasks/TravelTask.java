package powerwalk.tasks;

import java.util.ArrayList;
import java.util.List;
import org.powerbot.core.script.job.Task;
import org.powerbot.game.api.methods.Walking;
import powerwalk.Bot;
import powerwalk.Starter;
import powerwalk.control.PathFinder;
import powerwalk.model.Destination;
import powerwalk.model.OutOfReachException;
import powerwalk.model.Point;
import powerwalk.model.interact.Lodestone;

/**
 * This Task travels to the given destination using all available methods.
 * @author Chronio
 */
public class TravelTask extends StepTask {

    private Point destination = null;
    
    private List<Point> path = null;
    private int target = 0;
    
    /**
     * Creates a new TravelTask set to travel to the specified Point
     * @param destination the point this TravelTask travels to
     * @param priority the priority of this Task
     */
    public TravelTask(Point destination, int priority) {
        super(priority);
        this.destination = destination;
        
        String name = Destination.getDestination(destination).getName();
        if (name == null) name = destination.toString();
        setName("Travel to " + name);
    }
    
    public TravelTask(Destination d, int priority) {
        super (priority);
        this.destination = d.getPosition();
        setName("Travel to " + d.getName());
    }
    
    /**
     * Creates a new TravelTask set to travel to the specified Point.
     * <p />
     * The Task will be made with priority 0.
     * @param destination the point this TravelTask travels to
     */
    public TravelTask(Point destination) {
        this(destination,0);
    }
    
    /**
     * Calculates a path and checks preconditions for this TravelTask.
     * The Task is immediately canceled when <code>getDestination() == null</code>, 
     * or when the PathFinder class has found no path to the given destination.
     */
    @Override public synchronized void start() {
        target = 0;
        if (destination == null)
            cancel();
        else {
            try {
                path = PathFinder.findPath(Bot.getBot().getPosition(), destination);
                if (Starter.devmode()) {
                    StringBuilder sb = new StringBuilder("Composed path:\n");
                    for (Point p : path) {
                        Lodestone l = Lodestone.getLodestone(p);
                        if (l == null)
                            sb.append("  ").append(p.toString()).append("\n");
                        else
                            sb.append("  Lodestone to ").append(l.getName())
                              .append(" (").append(p.toString()).append(")\n");
                    }

                    Starter.logMessage(sb.toString());
                }
                if (path.size() > 0) {
                    Point t = path.get(target);
                    Starter.logMessage("travel to " + path.get(path.size() - 1) + " has started, there are " + path.size() + " points on this path.", "Task");
                    walkToTile(t);
                }
            } catch (OutOfReachException e) {
                path = new ArrayList<>(1);
                path.add(Bot.getBot().getPosition());
                Starter.logMessage("No path found to " + destination + ", task was canceled","TravelTask");
                cancel();
            }
        }
    }
    
    /**
     * Attempts to move to the next Point in the path, or waits if no action is 
     * required.
     * <p />
     * When the Player has more then 20 stamina left, but the Player's run mode 
     * is set to false, Run mode is automatically enabled.
     */
    @Override public synchronized void step() {
        setStepsLeft(path.size() - target);
        Point playerPos = Bot.getBot().getPosition();
        // check the distance to our next point.
        double distToTarget = playerPos.distance(path.get(target));

        // check if we are running. If not, enable when we have some stamina left
        if (!Walking.isRunEnabled() && Walking.getEnergy() >= 20) {
            Walking.setRun(true);
        }

        // Are we are close enough?
        if (distToTarget < (1 + 3 * Math.random())) {
            // Are there more points?
            if (target + 1 < path.size()) {
                ++target;
                // Then we walk to the next tile.
                Point t = path.get(target);
                walkToTile(t);
            } else {
                // There are no more points, so we are done.
                cancel();
            }
        }

        // wait a while before checking again
        Task.sleep(130, 210);
    }
    
    /**
     * This method overrides the basic reset behavior of throwing an Exception.
     * <p/>
     * This method, however, does nothing by itself. TravelTask instances can be 
     * run over and over again and the path will be recalculated every time. 
     * This allows creation of reusable TravelTasks, which can be useful when 
     * moving between a fixed set of Points.
     */
    @Override public void reset() {}
    
    /**
     * returns the destination that this TravelTask is set to travel to.
     * @return the destination of this TravelTask
     */
    public Point getDestination() {
        return new Point(destination);
    }
    
    // walks to the given tile and possibly executes the appropriate action
    private void walkToTile(Point p) {
        Point playerPos = Bot.getBot().getPosition();
        if (playerPos.distance(p) > PathFinder.maxDist) {
            Lodestone l = Lodestone.getLodestone(p);
            if (l != null) {
                try { 
                    if (Starter.devmode()) Starter.logMessage("Attempting to follow Lodestone to " + l.getPosition(),"TravelTask");
                    l.follow();
                    Task.sleep(134,245);
                    walkToTile(path.get(++target));
                } catch (OutOfReachException e) {
                    Starter.logMessage("Failed to follow Lodestone to " + l.getName() + ", aborting travel.","TravelTask",e);
                    cancel();
                }
            } else {
                // attempt walkTo anyways
                Walking.walk(p);
            }
        } else {
            Walking.walk(p);
        }
    }
}
