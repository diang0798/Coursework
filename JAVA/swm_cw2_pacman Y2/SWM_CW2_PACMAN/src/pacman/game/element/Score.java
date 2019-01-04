package pacman.game.element;

import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

/**
 * Score, life and current level of the game
 * @author Ang Ding
 *
 */
public class Score {

    public Text score;
    public Text lifes;
    public Text level;

    /**
     * Constructor
     * @param root - group root
     * @param currentScores - current scores
     * @param currentLife - current lifes
     * @param currentLevel - current level
     */
    public Score(Group root, int currentScores, int currentLife, int currentLevel) {
        this.score = new Text(BarObstacle.THICKNESS * 4, BarObstacle.THICKNESS * 28, "Score: " + currentScores);
        this.lifes = new Text(BarObstacle.THICKNESS * 20, BarObstacle.THICKNESS * 28,"Lifes: " + currentLife);
        this.level = new Text(BarObstacle.THICKNESS * 36, BarObstacle.THICKNESS * 28,"Level: " + currentLevel);
        score.setFill(Color.MAGENTA);
        score.setFont(Font.font("Arial", 30));

        lifes.setFill(Color.MAROON);
        lifes.setFont(Font.font("Arial", 30));
        
        level.setFill(Color.ROYALBLUE);
        level.setFont(Font.font("Arial", 30));

        root.getChildren().add(score);
        root.getChildren().add(lifes);
        root.getChildren().add(level);
    }
}
