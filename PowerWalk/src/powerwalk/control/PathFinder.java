package powerwalk.control;

import java.util.*;
import powerwalk.Bot;
import powerwalk.model.GameObject;
import powerwalk.model.OutOfReachException;
import powerwalk.model.Point;
import powerwalk.model.world.Wall;

/**
 * This class deals with finding a path between two Points in the RSBot
 * environment.
 * <p/>
 * It uses the A* algorithm on the map data collected by the mapper.
 * 
 * @author Alaineman
 * @author Chronio
 */
public class PathFinder {
    
    /**
     * Finds a path between the given start and end using the A* algorithm.
     * <p/>
     * An ArrayList of the Points is returned that indicates a shortest path 
     * between the start and endpoints.
     * @param start the startPoint
     * @param end the endPoint
     * @return a shortest path between the given start and endpoints.
     * @throws OutOfReachException when no path exists between start and end
     * @throws IllegalArgumentException when the start or endpoint is null
     */
    public static ArrayList<Point> findPath(Point start, Point end) throws OutOfReachException {
        return new PathFinder(start,end).calculatePath();
    }
    
    /**
     * Calculates and returns a shortest path from the player's current position to the given endpoint.
     * <p/>
     * This method is effectively the same as calling 
     * <code>PathFinder.findPath(Bot.getBot().getPosition(),end)</code>.
     * @param end the Point to travel to
     * @return a shortest path between the player's current position and the given endpoint.
     * @throws OutOfReachException when no path exists between the player's current position and the given endpoint.
     * @throws IllegalArgumentException when the endpoint is null.
     */
    public static ArrayList<Point> findPathTo(Point end) throws OutOfReachException {
        return new PathFinder(Bot.getBot().getPosition(), end).calculatePath();
    }
    
    /**
     * The maximum distance between two Points in the result Path.
     */
    public static final int maxDist = 15;
    
    private Point start,goal;
    private HashMap<Point, Point> cameFrom;
    private HashMap<Point, Double> pathCost;
    private HashMap<Point, Double> fScore;
    private HashSet<Point> closedSet;
    private PriorityQueue<Point> pending;

    private PathFinder(Point start,Point goal) {
        if (start == null) throw new IllegalArgumentException("Startpoint is null");
        if (goal  == null) throw new IllegalArgumentException("Endpoint is null");
        this.start = start;
        this.goal = goal;
        
        Point delta = start.subtract(goal);
        int dist = delta.x + delta.y + delta.z;
        int tiles = delta.x * delta.y;
        cameFrom = new HashMap<>(tiles);
        pathCost = new HashMap<>(tiles);
        fScore   = new HashMap<>(tiles);
        closedSet = new HashSet<>(tiles);
        pending = new PriorityQueue(dist, new Comparator<Point>() {
            @Override public int compare(Point p1, Point p2) {
                return (int)(fScore.get(p1) - fScore.get(p2));
            }
        });
        
        pathCost.put(start, 1d);
        fScore.put(start,Math.sqrt(Math.pow(start.x - goal.x, 2) + Math.pow(start.y - goal.y, 2))); 
        pending.offer(start);
    }
    
    /**
     * Calculates a path between start and goal using the A* algorithm.
     *
     * @param start The start Point
     * @param goal The goal Point
     * @return A Path from start to goal
     * @throws OutOfReachException When no path between start and goal exists
     */
    private ArrayList<Point> calculatePath() throws OutOfReachException {
        while (!pending.isEmpty()) {
            Point current = pending.poll();
            if (current.equals(goal)) {
                ArrayList<Point> fullPath = reconstruct(goal);
                return reducePoints(fullPath);
            }
            closedSet.add(current);
            ArrayList<Point> adjacents = availableEdges(current);
            for (Point p : adjacents) {
                if (!closedSet.contains(p)) {                                           
                        double tempPathCost = pathCost.get(current) + 1;
                        boolean isPending = pending.contains(p);
                        if (!isPending || tempPathCost <= pathCost.get(p) || pathCost.get(p) == 0) {
                            cameFrom.put(p, current);
                            pathCost.put(p, tempPathCost);
                            fScore.put(p,tempPathCost + Math.sqrt(Math.pow(start.x - goal.x, 2) + Math.pow(start.y - goal.y, 2)));
                            if (!isPending) {
                                pending.offer(p);
                            }
                        }
                    }
               }
        }
        throw new OutOfReachException(goal, "Destination could not be reached, is the area explored?");
    }

    private static int getDirection(Point base, Point adj) {
        if (base.distance(adj) == 1) {
            Point delta = adj.subtract(base);
            if (delta.x > 0) return Wall.EAST;
            if (delta.x < 0) return Wall.WEST;
            if (delta.y > 0) return Wall.NORTH;
            if (delta.y < 0) return Wall.SOUTH;
        }
        return 0;
    }

    // helper method that returns all tiles that are directly next to base, 
    // and can be reached from base.
    private static ArrayList<Point> availableEdges(Point base) {
        ArrayList<Point> points = new ArrayList<>(4);
        Point[] edges = { // the possible adjacent edges
            new Point(base.x, base.y-1, base.z), 
            new Point(base.x+1, base.y, base.z), 
            new Point(base.x, base.y+1, base.z), 
            new Point(base.x-1, base.y, base.z)
        };
        for(Point p : edges){
            GameObject go = Bot.getBot().getWorldMap().get(p);
            if(!(go instanceof Wall)) points.add(p);
            else if(!((Wall) go).containsType(getDirection(p, base))) points.add(p);
        }
        return points;
    }

    // helper method that reconstructs the path that was found using the cameFrom map
    private ArrayList<Point> reconstruct(Point current) {
        // reconstruct the path from the came_from HashMap
        Point prev = cameFrom.get(current);
        if (prev == null || prev.equals(start)) {
            // we reached the start of the path
            ArrayList<Point> thePath = new ArrayList<>();
            thePath.add(current);
            return thePath;
        } else {
            ArrayList<Point> thePath = reconstruct(cameFrom.get(current));
            thePath.add(current);
            return thePath;
        }
    }
    
    // helper method that reduces the amount of Points in the result path to
    // prevent unnecessary clicking.
    private static ArrayList<Point> reducePoints(ArrayList<Point> path) {
        // Greedy algorithm reducing the points the Bot will click
        ArrayList<Point> selected = new ArrayList<>((int)Math.ceil(path.size() / (maxDist - 3)));
        int distSinceLastSelected = 0;
        int targetDistance = maxDist - (int) (3 + 5 * Math.random());
        for (Point p : path) {
            if (distSinceLastSelected < targetDistance) {
                distSinceLastSelected++;
            } else {
                // set a new targetDistance
                targetDistance = maxDist - (int) (2 + 5 * Math.random());
                selected.add(p);
                distSinceLastSelected = 0;
            }
        }
        Point lastPoint = path.get(path.size() - 1);
        if (selected.isEmpty() || !selected.get(selected.size() - 1).equals(lastPoint)) {
            // if the final Point is not there, add it to the selected Points
            selected.add(lastPoint);
        }
        return selected;
    }
}
