package powerwalk.model;

import org.powerbot.game.api.wrappers.Tile;

/**
 * Three dimensional Point.
 * @author Chronio
 */
public class Point {
    /** The X-coordinate of this Point */
    public int x;
    /** The Y-coordinate of this Point */
    public int y;
    /** The Z-coordinate of this Point */
    public int z;
    
    /**
     * Creates a new Point with the given coordinates. 
     * The z-coordinate is taken as 0.
     * @param x the x-coordinate of the Point
     * @param y the y-coordinate of the Point
     */
    public Point(int x,int y) {
        this.x = x;
        this.y = y;
        this.z = 0;
    }
    /**
     * Creates a new Point with the given coordinates
     * @param x the x-coordinate of the Point
     * @param y the y-coordinate of the Point
     * @param z the z-coordinate of the Point
     */
    public Point(int x,int y,int z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    
    /**
     * Creates a Point with the same Position as the given Point
     * @param p The Position this Point will refer to
     */
    public Point(Point p) {
        this(p.x,p.y,p.z);
    }
    
    /**
     * Returns the result of adding the given point to this Point.
     * @param p the Point to add
     * @return the sum of this Point and Point p
     */
    public Point add(Point p) {
        return new Point(x+p.x, y+p.y, z+p.z);
    }
    
    /**
     * Calculates the distance between this Point and the given Point
     * @param that the Point to calculate the distance from
     * @return the distance between this Point and the Point that
     */
    public double distance(Point that) {
        return subtract(that).length();
    }
    
    /**
     * Calculates and returns the distance between (0,0,0) and this Point.
     * @return the length of the vector denoted by this Point.
     */
    public double length() {
        return Math.sqrt(x*x + y*y + z*z);
    }
    
    /**
     * Calculates and returns the distance between (0,0) and this Point, ignoring the plane.
     * @return the length of the vector denoted by this Point, where this Point's z coordinate is taken as 0.
     */
    public double lengthOnPlane() {
        return Math.sqrt(x*x + y*y);
    }
    
    /**
     * returns the angle of the vector denoted by this Point.
     * <p/>
     * The returned angle is the angle between the vector and the x-axis. 
     * Positive angles rotate counterclockwise.
     * @return the angle of the vector denoted by this Point.
     */
    public double theta() {
        return Math.atan2(y, x);
    }
    
    /**
     * Returns a Point that represents the position of this Point relative to offset
     * @param offset the offset to subtract from this Point
     * @return a Point representing the position of this Point relative to offset
     */
    public Point subtract(Point offset) {
        return new Point(x-offset.x,y-offset.y,z-offset.z);
    }
    
    /**
     * Returns whether this Point is equal to the given object.
     * This Point is equal if and only if:
     * <ul>
     *  <li>The given object is an instance of Point</li>
     *  <li>The object points to the same position</li>
     * </ul>
     * @param obj the Object to compare this Point with
     * @return true if and only if this Point is equal to the given Object, false otherwise.
     */
    @Override public boolean equals(Object obj) {
        if (obj instanceof Point) {
            Point p = (Point)obj;
            return (x==p.x && y==p.y && z==p.z);
        }
        return false;
    }
    
    /**
     * calculates the hashCode corresponding to this Point.
     * @return the hashCode corresponding to this Point
     */
    @Override public int hashCode() {
        int hash = 5;
        hash = 7 * hash + x;
        hash = 7 * hash + y;
        hash = 7 * hash + z;
        return hash;
    }
    
    /**
     * Returns a String-representation of this Point.
     * The returned string is of the form "(x,y,z)"
     * @return a String-representation of this Point
     */
    @Override public String toString() {
        return "(" + x + "," + y + "," + z + ")";
    }
    
    /**
     * Parses a Point from a String that contains one or more values separated by "," and surrounded by braces.
     * 
     * @param s the String to parse
     * @throws NumberFormatException when one or more values could not be parsed
     * @return the Point denoted by this String
     */
    public static Point fromString(String s) {
        int start = s.indexOf("(")+1;
        int end   = s.indexOf(")");
        String[] vals = s.substring(start,end).split(",");
        int x=0,y=0,z=0;
        if (vals.length>0) x = Integer.parseInt(vals[0]);
        if (vals.length>1) y = Integer.parseInt(vals[1]);
        if (vals.length>2) z = Integer.parseInt(vals[2]);
        
        return new Point(x,y,z);
    }
    
    /**
     * Returns a Tile-representative of this Point
     * @return a Tile object indicating the same location as this Point
     */
    public Tile toTile() {
        return new Tile(x,y,z);
    }
    
    /**
     * Returns a Point-representative of the given Tile
     * @param t the Tile to create a Point object for.
     * @return a Point object indicating the same location as the given Tile
     */
    public static Point fromTile(Tile t) {
        return new Point(t.getX(),t.getY(),t.getPlane());
    }
    
    /**
     * Creates a new Point from the given Polar coordinates.
     * @param theta the angle
     * @param r the length
     * @return a Point representing the position denoted by the given polar coordinates.
     */
    public static Point fromPolar(double theta, double r) {
        int x = (int)(r * Math.cos(theta));
        int y = (int)(r * Math.sin(theta));
        return new Point(x,y);
    }
   
}
