package powergrid.task;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.logging.Level;
import org.powerbot.core.script.job.Task;
import org.powerbot.game.api.methods.Walking;
import powergrid.PowerGrid;
import powergrid.control.PathFinder;
import powergrid.control.uicontrols.RSInteractor;
import powergrid.model.OutOfReachException;
import powergrid.model.Point;
import powergrid.model.structure.DestinationMap.Destination;
import powergrid.model.world.GameTile;

/**
 * This Task travels to the given destination using all available methods.
 *
 * @author Chronio
 */
public class TravelTask extends StepTask {

    private Point destination = null;
    protected List<Point> path = null;
    private int target = 0;

    /**
     * Creates a new TravelTask set to travel to the specified Point
     *
     * @param destination the point this TravelTask travels to
     * @param priority the priority of this Task
     */
    public TravelTask(Point destination, int priority) {
        super(priority);
        assert destination != null;
        this.destination = destination;
        setName("Travel to " + destination.toString());
    }

    public TravelTask(Destination d, int priority) {
        super(priority);
        assert d != null;
        this.destination = d.getPos();
        setName("Travel to " + d.getName());
    }

    /**
     * Creates a new TravelTask set to travel to the specified Point. <p /> The
     * Task will be made with priority 0.
     *
     * @param destination the point this TravelTask travels to
     */
    public TravelTask(Point destination) {
        this(destination, MEDIUM);
    }

    public TravelTask() {
        super(MEDIUM);
    }

    public synchronized void setDestination(Point dest) {
        assert dest != null && destination == null;
        destination = dest;
    }

    /**
     * Calculates a path and checks preconditions for this TravelTask.
     * <p/>
     * The Task is immediately canceled when
     * <code>getDestination() == null</code>, or when the PathFinder class has
     * found no path to the given destination.
     */
    @Override
    public synchronized void start() {
        target = 0;
        if (destination == null) {
            cancel();
        } else {
            RSInteractor in = PowerGrid.PG.rsInteractor();
            try {
                path = PathFinder.findPath(in.getPosition(), destination);
                if (path.size() > 0) {
                    Point t = path.get(target);
                    PowerGrid.LOGGER.info("Travel to " + path.get(path.size() - 1) + " has started, there are " + path.size() + " points on this path.");
                    walkToTile(t);
                }
            } catch (OutOfReachException e) {
                path = new ArrayList<>(1);
                path.add(in.getPosition());
                PowerGrid.LOGGER.log(Level.WARNING, 
                        "No path found to " + destination + ", task was canceled", e);
                cancel();
            }
        }
    }

    /**
     * Attempts to move to the next Point in the path, or waits if no action is
     * required.
     * <p/>
     * When the Player has more then 20 stamina left, but the Player's run mode
     * is set to false, Run mode is automatically enabled.
     */
    @Override
    public synchronized void step() {
        setStepsLeft(path.size() - target);
        Point playerPos = PowerGrid.PG.rsInteractor().getPosition();
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
     * This method resets the pathCounter so that the path will be recalculated.
     * TravelTask instances can be run over and over again and the path will be
     * recalculated every time. This allows creation of reusable TravelTasks,
     * which can be useful when moving between a fixed set of Points.
     */
    @Override
    public void reset() {
        target = 0;
    }

    /**
     * returns the destination that this TravelTask is set to travel to.
     *
     * @return the destination of this TravelTask
     */
    public Point getDestination() {
        return destination;
    }

    // walks to the given tile and possibly executes the appropriate action
    private void walkToTile(Point p) {
        Point playerPos = PowerGrid.PG.rsInteractor().getPosition();
        if (playerPos.distance(p) > PathFinder.maxDist) {
            //attempt walkTo anyways, insert teleportable / transportable usage
            GameTile obj = PowerGrid.PG.mapper().getWorldMap().get(p);
        } else {
            Walking.walk(p);
        }
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 59 * hash + Objects.hashCode(this.destination);
        return hash;
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof TravelTask) {
            TravelTask that = (TravelTask) other;
            return this.getDestination().equals(that.getDestination());
        }
        return false;
    }
}