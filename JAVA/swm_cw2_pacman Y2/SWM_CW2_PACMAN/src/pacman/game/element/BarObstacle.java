package pacman.game.element;

import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import pacman.controllers.SetupController;

/**
 * Bar Obstacle
 * @author Ang Ding
 *
 */
public class BarObstacle extends Rectangle {

    public static double THICKNESS = 25;
    
    /**
     * Constructor
     * @param x - x coordinate
     * @param y - y coordinate
     * @param orientation - horizontal or vertical
     * @param length - the length of the bar (1 == 100px)
     */
    public BarObstacle(double x, double y, String orientation, double length) {
        this.setX(x);
        this.setY(y);
        if (orientation.equals("horizontal")) {
            this.setHeight(BarObstacle.THICKNESS);
            this.setWidth(length * BarObstacle.THICKNESS);
        } else {
            this.setHeight(length * BarObstacle.THICKNESS);
            this.setWidth(BarObstacle.THICKNESS);
        }
        if(SetupController.getWallColor() != null) {
        	this.setFill(SetupController.getWallColor());
        }else {
        	this.setFill(Color.CADETBLUE);
        }
        this.setStrokeWidth(3);
    }
}
