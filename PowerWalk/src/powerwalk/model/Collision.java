package powerwalk.model;

/**
 * represents a collision object on the world map
 * @author Vincent W, P.Kramer
 */
public class Collision extends GameObject {
    
    /**
     * Creates a new Collision object at the given x,y,z location.
     * @param x the x-coordinate
     * @param y the y-coordinate
     * @param z the z-coordinate
     * @param raw the raw value for the object
     */
    public Collision(int x,int y,int z,int raw) {
        super(x,y,z,raw);
    }
    
}
