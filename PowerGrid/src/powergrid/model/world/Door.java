package powergrid.model.world;

import java.util.Arrays;
import org.powerbot.game.api.methods.node.SceneEntities;
import org.powerbot.game.api.wrappers.node.SceneObject;
import powergrid.model.GameObject;
import powergrid.model.OutOfReachException;
import powergrid.model.Point;
import powergrid.model.interact.Interactable;

/**
 * Class representing a Door in the RSBot environment. 
 * <p>Doors are different from gates in that they usually cover only one tile, 
 * and they have different states (open and close). Gates only have one state, 
 * and always require an interact() command to pass through.</p>
 * @author Chronio
 */
public class Door extends GameObject implements Interactable {
    /** Raw values that represent doors in the RSBot environment */
    public static final int[] values = {
        /* Appears to be:
         *   First column: open.
         *   Second column: closed.
         *   Each row forms a pair (same door, different states).
         */
        15535,15536, // Varrock "private" buildings, normal homes and such. Also: Cooks' guild
        16777,16776, // Lunar house front door
        16779,16778, // Lunar house front door
        
        24375,24376, // Varrock public buildings (stores and other places of interest)
        24377,24378, 
        24379,24381, // Varrock inner doors
        24383,24384, // Varrock back streets
        24387,24388, 
        /*?*/ 24536, // Varrock museum chain (this can only be opened by members, hence missing open value)
        /*?*/ 24565, // Varrock Museum back door (cannot be opened, I guess)
        /*?*/ 24567, // Varrock Museum back door (cannot be opened, I guess)
    };
    /** Raw values that represent open doors in the RSBot environment */
    public static final int[] openDoors = {15535,16777,24375,24377,24379,24383,24387};
    
    /**
     * Creates a new Door at the given position. the <code>rawNumber</code> 
     * indicates the type of object as provided by the RSBot environment.
     * @param x the x-coordinate of this object
     * @param y the y-coordinate of this object
     * @param z the z-coordinate of this object
     * @param rawValue the raw value from the environment specifying the type
     */
    public Door(int x,int y,int z,int rawValue) {
        super(new Point(x,y,z),rawValue);
        if (Arrays.binarySearch(values,rawValue) == -1)
            throw new IllegalArgumentException("value " + rawValue + " does not represent a Door");
    }
    
    /**
     * Performs the default interaction on the door.
     * <p>Use the open() and close() methods to ensure a specific door state</p>
     * @throws OutOfReachException when the door could not be interacted with
     */
    @Override public void interact() throws OutOfReachException {
        SceneObject d = SceneEntities.getAt(getPosition());
        if (d == null) throw new OutOfReachException("The door is not loaded");
        d.click(true);
    }
    
    /**
     * Tries to open the door.
     * @throws OutOfReachException when the door could not be opened
     */
    public void open() throws OutOfReachException {
        if (!stateIsOpen()) {
            SceneObject d = SceneEntities.getAt(getPosition());
            if (d == null) throw new OutOfReachException(getPosition(),"Door not loaded");
            d.click(true);
        }
    }
    
    /**
     * Tries to close the door.
     * @throws OutOfReachException when the door could not be closed
     */
    public void close() throws OutOfReachException {
        if (stateIsOpen()) {
            SceneObject d = SceneEntities.getAt(getPosition());
            if (d == null) throw new OutOfReachException(getPosition(),"Door not loaded");
            d.click(true);
        }
    }
    
    /**
     * Interacts with this door.
     * <p> The following actions are supported: </p>
     * <ul>
     *  <li>open</li>
     *  <li>close</li>
     *  <li>examine</li>
     * </ul>
     * 
     * @param method the method of interaction with this door
     * @throws UnsupportedOperationException when the given method is not supported
     * @throws OutOfReachException when the door could not be reached
     */
    @Override public void interact(String method) throws OutOfReachException {
        SceneObject d = SceneEntities.getAt(getPosition());
        if (d == null) throw new OutOfReachException(getPosition(),"Door not loaded");
        if (!d.interact(method))
            throw new UnsupportedOperationException("Operation not supported for this Door");
    }
    
     /**
     * returns whether this door is opened.
     * @return true if this door is opened, false if it is not.
     */
    public boolean stateIsOpen() {
        SceneObject d = SceneEntities.getAt(getPosition());
        return d.interact("open");
    }
    
    /**
     * returns whether this door is opened.
     * @return true if this door is opened, false if it is not.
     */
    @Deprecated public boolean isOpen() {
        return (-1 != Arrays.binarySearch(openDoors, getRawNumber()));
    }
}
