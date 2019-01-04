package pacman.controllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;
import pacman.game.GameManager;

/**
 * The controller of Start screen
 * @author Ang Ding
 *
 */
public class StartController {
	
	/**
	 * Enter the pacman game
	 * @param e
	 */
	public void startGame(ActionEvent e) {
		Group root = new Group();
		Scene theScene = new Scene(root, 1225, 720);
		Node source = (Node) e.getSource();
	    Stage mainStage = (Stage) source.getScene().getWindow();
        mainStage.setScene( theScene );
        Canvas canvas = new Canvas( 1225, 600 );
        root.getChildren().add( canvas );
        theScene.setFill(SetupController.getBgdColor());
        GameManager gameManager = new GameManager(root);

        gameManager.drawBoard();

        theScene.addEventHandler(KeyEvent.KEY_PRESSED, event -> gameManager.movePacman(event));
        theScene.addEventHandler(KeyEvent.KEY_RELEASED, event -> gameManager.stopPacman(event));
        theScene.addEventHandler(KeyEvent.KEY_PRESSED, event -> gameManager.restartGame(event));
        theScene.addEventHandler(KeyEvent.KEY_PRESSED, event -> gameManager.nextLevel(event));
	}
	
	/**
	 * Open the setup screen
	 * @param e
	 * @throws Exception
	 */
	public void setup(ActionEvent e) throws Exception {
		System.out.println("set up!");
		Parent root = FXMLLoader.load(getClass().getResource("setup.fxml"));
		Scene theScene = new Scene(root, 1225, 720);
		Node source = (Node) e.getSource();
	    Stage mainStage = (Stage) source.getScene().getWindow();
        mainStage.setScene( theScene );
	}
}
