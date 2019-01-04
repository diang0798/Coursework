package pacman.game;

import javafx.animation.AnimationTimer;
import javafx.scene.Group;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import pacman.game.element.BarObstacle;
import pacman.game.element.Cookie;
import pacman.game.element.Ghost;
import pacman.game.element.ScoreReporter;
import pacman.game.element.Maze;
import pacman.game.element.Pacman;
import pacman.game.element.Score;
import pacman.game.element.ScoreList;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

/**
 * Manage the whole pacman game
 * @author Ang Ding
 *
 */
public class GameManager {

    private Pacman pacman;
    private Group root;
    private Set<Cookie> cookieSet;
    private Set<Ghost> ghosts;
    private AnimationTimer leftPacmanAnimation;
    private AnimationTimer rightPacmanAnimation;
    private AnimationTimer upPacmanAnimation;
    private AnimationTimer downPacmanAnimation;
    private Maze maze;
    private int lifes;
    private int score;
    private Score scoreBoard;
    private boolean gameEnded;
    private boolean noCookies;
    private boolean levelPassed;
    private int cookiesEaten;
    private ScoreList scoreList;
    private ArrayList<String> scoreArray;
    private ScoreReporter scoreReporter;
    private int currentLevel;

    /**
     * Constructor
     * @param root - group root
     */
    public GameManager(Group root) {
        this.root = root;
        this.maze = new Maze();
        this.pacman = new Pacman(2.5 * BarObstacle.THICKNESS, 2.5 * BarObstacle.THICKNESS, "/img/pacman.png", maze, this);
        this.cookieSet = new HashSet<>();
        this.ghosts = new HashSet<>();
        this.scoreArray = new ArrayList<String>();
        this.scoreList = new ScoreList();
        this.scoreReporter = new ScoreReporter();
        this.leftPacmanAnimation = pacman.createAnimation("left");
        this.rightPacmanAnimation = pacman.createAnimation("right");
        this.upPacmanAnimation = pacman.createAnimation("up");
        this.downPacmanAnimation = pacman.createAnimation("down");
        this.lifes = 3;
        this.score = 0;
        this.cookiesEaten = 0;
        this.currentLevel = 1;
        this.levelPassed = false;
    }

    /**
     * Set one life less
     */
    private void lifeLost() {
        this.leftPacmanAnimation.stop();
        this.rightPacmanAnimation.stop();
        this.upPacmanAnimation.stop();
        this.downPacmanAnimation.stop();
        for (Ghost ghost : ghosts) {
            ghost.getAnimation().stop();
        }
        this.pacman.setCenterX(2.5 * BarObstacle.THICKNESS);
        this.pacman.setCenterY(2.5 * BarObstacle.THICKNESS);
        lifes--;
        score -= 10;
        this.scoreBoard.lifes.setText("Lifes: " + this.lifes);
        this.scoreBoard.score.setText("Score: " + this.score);
        if (lifes == 0) {
        	currentLevel--;
            this.endGame();
        }
    }
    
   /**
    * Go to next level of pacman game
    * @param event - keyboard input
    */
    public void nextLevel(KeyEvent event) {
    	if(event.getCode() == KeyCode.SPACE && noCookies) {
    			currentLevel++;
    			root.getChildren().clear();
    			this.cookieSet.clear();
    			this.ghosts.clear();
    			this.drawBoard();
                this.pacman.setCenterX(2.5 * BarObstacle.THICKNESS);
                this.pacman.setCenterY(2.5 * BarObstacle.THICKNESS);
                noCookies = false;
                levelPassed = false;
                this.cookiesEaten = 0;
    	}
    }
    
    /**
     * Ends the game
     * Enter the user's name and show the high score list
     */
    private void endGame() {
    	this.gameEnded = true;
        root.getChildren().remove(pacman);
        for (Ghost ghost : ghosts) {
               root.getChildren().remove(ghost);
           }
        int flag = scoreList.scanList(scoreArray, score);
        root.getChildren().clear();
        if(flag != -1) {
        	scoreList.addNewScore(root, scoreArray, score, flag, currentLevel);
        }
        else {
        	scoreList.printScoreList(root, scoreArray, flag);
        }
    }

    /**
     * Restart the game
     * @param event - keyboard input
     */
    public void restartGame(KeyEvent event) {
        if (event.getCode() == KeyCode.ESCAPE && gameEnded) {
            root.getChildren().clear();
            this.cookieSet.clear();
            this.ghosts.clear();
            this.scoreArray.clear();
            this.currentLevel = 1;
            this.lifes = 3;
            this.score = 0;
            this.drawBoard();
            this.pacman.setCenterX(2.5 * BarObstacle.THICKNESS);
            this.pacman.setCenterY(2.5 * BarObstacle.THICKNESS);
            this.cookiesEaten = 0;
            gameEnded = false;
            levelPassed = false;
        }
    }

    /**
     * Draws the board of the game with the cookies and the Pacman
     */
    public void drawBoard() {
        this.maze.CreateMaze(root, this.currentLevel);
        this.maze.addcookies(root, cookieSet, this.currentLevel);
        root.getChildren().add(this.pacman);
        this.generateGhosts(this.currentLevel);
        root.getChildren().addAll(this.ghosts);
        this.scoreBoard = new Score(root, this.score, this.lifes, this.currentLevel);
    }

    /**
     * Generate ghosts for the pacman game
     * @param currentLevel - current level of the game
     */
    public void generateGhosts(int currentLevel) {
        this.ghosts.add(new Ghost(18.5 * BarObstacle.THICKNESS, 12.5 * BarObstacle.THICKNESS, "/img/ghost1.png", maze, this));
        this.ghosts.add(new Ghost(22.5 * BarObstacle.THICKNESS, 12.5 * BarObstacle.THICKNESS, "/img/ghost2.png", maze, this));
        this.ghosts.add(new Ghost(28.5 * BarObstacle.THICKNESS, 12.5 * BarObstacle.THICKNESS, "/img/ghost3.png", maze, this));
        this.ghosts.add(new Ghost(28.5 * BarObstacle.THICKNESS, 9.5 * BarObstacle.THICKNESS, "/img/ghost4.png", maze, this));
        if(currentLevel > 1) {
        	this.ghosts.add(new Ghost(18.5 * BarObstacle.THICKNESS, 9.5 * BarObstacle.THICKNESS, "/img/ghost5.png", maze, this));
        }
    }

    /**
     * Moves the pacman
     * @param event - keyboard input
     */
    public void movePacman(KeyEvent event) {
        for (Ghost ghost : this.ghosts) {
            ghost.run();
        }
        switch(event.getCode()) {
            case RIGHT:
                this.rightPacmanAnimation.start();
                break;
            case LEFT:
                this.leftPacmanAnimation.start();
                break;
            case UP:
                this.upPacmanAnimation.start();
                break;
            case DOWN:
                this.downPacmanAnimation.start();
                break;
		default:
			break;
        }
    }

    /**
     * Stops the pacman
     * @param event - keyboard input
     */
    public void stopPacman(KeyEvent event) {
        switch(event.getCode()) {
            case RIGHT:
                this.rightPacmanAnimation.stop();
                break;
            case LEFT:
                this.leftPacmanAnimation.stop();
                break;
            case UP:
                this.upPacmanAnimation.stop();
                break;
            case DOWN:
                this.downPacmanAnimation.stop();
                break;
		default:
			break;
        }
    }


    /**
     * Checks if the Pacman touches cookies.
     * @param axis - axis of the pacman
     */
    public void checkCookieCoalition(String axis) {
        double pacmanCenterY = pacman.getCenterY();
        double pacmanCenterX = pacman.getCenterX();
        double pacmanLeftEdge = pacmanCenterX - pacman.getRadius();
        double pacmanRightEdge = pacmanCenterX + pacman.getRadius();
        double pacmanTopEdge = pacmanCenterY - pacman.getRadius();
        double pacmanBottomEdge = pacmanCenterY + pacman.getRadius();
        for (Cookie cookie:cookieSet) {
            double cookieCenterX = cookie.getCenterX();
            double cookieCenterY = cookie.getCenterY();
            double cookieLeftEdge = cookieCenterX - cookie.getRadius();
            double cookieRightEdge = cookieCenterX + cookie.getRadius();
            double cookieTopEdge = cookieCenterY - cookie.getRadius();
            double cookieBottomEdge = cookieCenterY + cookie.getRadius();
            if (axis.equals("x")) {
                // pacman goes right
                if ((cookieCenterY >= pacmanTopEdge && cookieCenterY <= pacmanBottomEdge) && (pacmanRightEdge >= cookieLeftEdge && pacmanRightEdge <= cookieRightEdge)) {
                    if (cookie.isVisible()) {
                        this.score += cookie.getValue();
                        this.lifes += cookie.getLife();
                        this.cookiesEaten++;
                    }
                    cookie.hide();
                }
                // pacman goes left
                if ((cookieCenterY >= pacmanTopEdge && cookieCenterY <= pacmanBottomEdge) && (pacmanLeftEdge >= cookieLeftEdge && pacmanLeftEdge <= cookieRightEdge)) {
                    if (cookie.isVisible()) {
                        this.score += cookie.getValue();
                        this.lifes += cookie.getLife();
                        this.cookiesEaten++;
                    }
                    cookie.hide();
                }
            } else {
                // pacman goes up
                if ((cookieCenterX >= pacmanLeftEdge && cookieCenterX <= pacmanRightEdge) && (pacmanBottomEdge >= cookieTopEdge && pacmanBottomEdge <= cookieBottomEdge)) {
                    if (cookie.isVisible()) {
                        this.score += cookie.getValue();
                        this.lifes += cookie.getLife();
                        this.cookiesEaten++;
                    }
                    cookie.hide();
                }
                // pacman goes down
                if ((cookieCenterX >= pacmanLeftEdge && cookieCenterX <= pacmanRightEdge) && (pacmanTopEdge <= cookieBottomEdge && pacmanTopEdge >= cookieTopEdge)) {
                    if (cookie.isVisible()) {
                        this.score += cookie.getValue();
                        this.lifes += cookie.getLife();
                        this.cookiesEaten++;
                    }
                    cookie.hide();
                }
            }
            this.scoreBoard.score.setText("Score: " + this.score);
            this.scoreBoard.lifes.setText("Life:" + this.lifes);
            if (this.cookiesEaten == this.cookieSet.size() && !levelPassed) {
            	levelPassed = true;
            	root.getChildren().clear();
            	root.getChildren().remove(pacman);
                for (Ghost ghost : ghosts) {
                    root.getChildren().remove(ghost);
                }
                this.ghosts.clear();
                if(currentLevel == 5) {
                	this.endGame();
                }else {
                	scoreReporter.scoreReport(root, this.score);
                	noCookies = true;
                }
            }
        }
    }

    /**
     * Checks if pacman is touching a ghost
     */
    public void checkGhostCoalition() {
        double pacmanCenterY = pacman.getCenterY();
        double pacmanCenterX = pacman.getCenterX();
        double pacmanLeftEdge = pacmanCenterX - pacman.getRadius();
        double pacmanRightEdge = pacmanCenterX + pacman.getRadius();
        double pacmanTopEdge = pacmanCenterY - pacman.getRadius();
        double pacmanBottomEdge = pacmanCenterY + pacman.getRadius();
        for (Ghost ghost : ghosts) {
            double ghostLeftEdge = ghost.getX();
            double ghostRightEdge = ghost.getX() + ghost.getWidth();
            double ghostTopEdge = ghost.getY();
            double ghostBottomEdge = ghost.getY() + ghost.getHeight();
            if ((pacmanLeftEdge <= ghostRightEdge && pacmanLeftEdge >= ghostLeftEdge) || (pacmanRightEdge >= ghostLeftEdge && pacmanRightEdge <= ghostRightEdge)) {
                if ((pacmanTopEdge <= ghostBottomEdge && pacmanTopEdge >= ghostTopEdge) || (pacmanBottomEdge >= ghostTopEdge && pacmanBottomEdge <= ghostBottomEdge)) {
                    lifeLost();
                }
            }
        }
    }

}
