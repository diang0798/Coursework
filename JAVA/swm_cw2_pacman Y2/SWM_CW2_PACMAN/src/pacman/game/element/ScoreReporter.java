package pacman.game.element;

import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;

/**
 * Report intermediate scores at end of a level 
 * @author Ang Ding
 *
 */
public class ScoreReporter {

	/**
	 * Report current scores after the player passing a level
	 * @param root - group root
	 * @param score - current scores
	 */
	public void scoreReport(Group root, int score) {
		javafx.scene.text.Text wd = new javafx.scene.text.Text("Well done! You have passed this level!");
        wd.setX(BarObstacle.THICKNESS * 5);
        wd.setY(BarObstacle.THICKNESS * 5);
        wd.setFont(Font.font("Arial", 60));
        wd.setFill(Color.BLACK);
        root.getChildren().add(wd);
        javafx.scene.text.Text currentScore = new javafx.scene.text.Text("Current scores:" + score);
        currentScore.setX(BarObstacle.THICKNESS * 12);
        currentScore.setY(BarObstacle.THICKNESS * 14);
        currentScore.setFont(Font.font("Arial", 70));
        currentScore.setFill(Color.RED);
        root.getChildren().add(currentScore);
        javafx.scene.text.Text next = new javafx.scene.text.Text("Press SPACE to next level");
        next.setX(BarObstacle.THICKNESS * 3);
        next.setY(BarObstacle.THICKNESS * 28);
        next.setFont(Font.font("Arial", 40));
        next.setFill(Color.ROYALBLUE);
        root.getChildren().add(next);
	}
}
