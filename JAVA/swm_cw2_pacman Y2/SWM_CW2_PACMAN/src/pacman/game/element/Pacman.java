package pacman.game.element;

import javafx.animation.AnimationTimer;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;
import javafx.scene.paint.ImagePattern;
import javafx.scene.shape.Circle;
import pacman.Main;
import pacman.game.GameManager;

/**
 * Pacman's constructor and animation
 * @author Ang Ding
 *
 */
public class Pacman extends Circle {

	String direction;
    GameManager gameManager;
    Maze maze;
    AnimationTimer animation;
    Image pacmanimage;
    
    /**
     * Constructor
     * @param x - x coordinate
     * @param y - y coordinate
     * @param image - pacman image
     * @param maze - maze of pacman game
     * @param gameManager - game's manager
     */
    public Pacman(double x, double y, String image, Maze maze, GameManager gameManager) {
        this.setCenterX(x);
        this.setCenterY(y);
        this.setRadius(25);
        this.setFill(Color.YELLOW);
        this.maze = maze;
        this.gameManager = gameManager;
        this.pacmanimage = new Image(Main.class.getResourceAsStream(image));
        this.setFill(new ImagePattern(pacmanimage));
    }
    
    /**
     * Creates an animation of the movement for pacman.
     * @param direction - direction of the pacman
     * @return
     */
    public AnimationTimer createAnimation(String direction) {
        double step = 5;
        return new AnimationTimer()
        {
            public void handle(long currentNanoTime)
            {
            switch (direction) {
                case "left":
                    if (!maze.isTouching(getCenterX() - getRadius(), getCenterY(), 15)) {
                        setCenterX(getCenterX() - step);
                        gameManager.checkCookieCoalition("x");
                        gameManager.checkGhostCoalition();
                        if(getCenterX() < 0) {
                        	setCenterX(1225);
                        	setCenterY(12.5 * BarObstacle.THICKNESS);
                        }
                        setRotate(180);
                    }
                    break;
                case "right":
                    if (!maze.isTouching(getCenterX() + getRadius(), getCenterY(), 15)) {
                        setCenterX(getCenterX() + step);
                        gameManager.checkCookieCoalition("x");
                        gameManager.checkGhostCoalition();
                        if(getCenterX() > 1225) {
                        	setCenterX(0);
                        	setCenterY(12.5 * BarObstacle.THICKNESS); 	
                        }
                        setRotate(0);
                    }
                    break;
                case "up":
                    if (!maze.isTouching(getCenterX(), getCenterY() - getRadius(), 15)) {
                        setCenterY(getCenterY() - step);
                        gameManager.checkCookieCoalition("y");
                        gameManager.checkGhostCoalition();
                        setRotate(270);
                    }
                    break;
                case "down":
                   if (!maze.isTouching(getCenterX(), getCenterY() + getRadius(), 15)) {
                       setCenterY(getCenterY() + step);
                       gameManager.checkCookieCoalition("y");
                       gameManager.checkGhostCoalition();
                       setRotate(90);
                   }
                   break;
            }
            }
        };
    }
}
