package pacman.game.element;

import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

/**
 * Types and functions of cookie
 * @author Ang Ding
 *
 */
public class Cookie extends Circle {

    private int value;
    private int life = 0;

    /**
     * Constructor
     * There are three kinds of cookies
     * @param x - x coordinate
     * @param y - y coordinate
     * @param type - type of the cookies 
     */
    public Cookie(double x, double y, int type) {
    	// ordinary cookie
    	if(type == 1) {
    		this.value = 5;
            this.setCenterX(x);
            this.setCenterY(y);
            this.setRadius(12.5);
            this.setFill(Color.SADDLEBROWN);
    	}
    	//high score cookie
    	if(type == 2) {
    		this.value = 50;
            this.setCenterX(x);
            this.setCenterY(y);
            this.setRadius(18);
            this.setFill(Color.YELLOW);
    	}
    	//life cookie
    	if(type == 3) {
    		this.value = 30;
    		this.life = 1;
            this.setCenterX(x);
            this.setCenterY(y);
            this.setRadius(20);
            this.setFill(Color.RED);
    	}
    }

    public int getValue() {
        return value;
    }

    public int getLife() {
    	return life;
    }
    
    public void hide() {
        this.setVisible(false);
    }

    public void show() {
        this.setVisible(true);
    }

}