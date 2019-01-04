package pacman.controllers;


import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

/**
 * The controller of the setup screen
 * @author Ang Ding
 *
 */
public class SetupController {

	@FXML private ComboBox<String> bgdComboBox;
	@FXML private ComboBox<String> wallComboBox;
	@FXML private static Color bgdColor;
	@FXML private static Color wallColor;
	@FXML private Rectangle bgdRect;
	@FXML private Rectangle wallRect;
	
	public static Color getBgdColor() {
		return bgdColor;
	}

	public static Color getWallColor() {
		return wallColor;
	}
	
	/**
	 * Initialize setup screen
	 */
	@FXML private void initialize() {
		bgdComboBox.getItems().addAll("WHITE", "ANTIQUEWHITE", "LIGHTPINK", "LIGHTYELLOW", "LIGHTSKYBLUE", "PALEGREEN", "LIGHTCYAN", "PLUM");
		wallComboBox.getItems().addAll("CADETBLUE", "BLACK", "BROWN", "DARKBLUE", "DIMGRAY", "RED", "PURPLE", "GREEN");
		bgdRect.setFill(Color.WHITE);
		wallRect.setFill(Color.CADETBLUE);
	}
	
	/**
	 * Go back to start screen
	 * @param e
	 * @throws Exception
	 */
	public void setupback(ActionEvent e) throws Exception {
		System.out.println("back to start");
		Parent root = FXMLLoader.load(getClass().getResource("Start.fxml"));
		Scene theScene = new Scene(root, 1225, 720);
		Node source = (Node) e.getSource();
	    Stage mainStage = (Stage) source.getScene().getWindow();
        mainStage.setScene( theScene );
	}
	
	/**
	 * Detects which background color is selected by the user
	 */
	public void bgdColor() {
		switch(bgdComboBox.getValue()) {
			case "WHITE":
				bgdColor = Color.WHITE;
				break;
			case "ANTIQUEWHITE":
				bgdColor = Color.ANTIQUEWHITE;
				break;
			case "LIGHTPINK":
				bgdColor = Color.LIGHTPINK;
				break;
			case "LIGHTYELLOW":
				bgdColor = Color.LIGHTYELLOW;
				break;
			case "LIGHTSKYBLUE":
				bgdColor = Color.LIGHTSKYBLUE;
				break;
			case "PALEGREEN":
				bgdColor = Color.PALEGREEN;
				break;
			case "LIGHTCYAN":
				bgdColor = Color.LIGHTCYAN;
				break;
			case "PLUM":
				bgdColor = Color.PLUM;
				break;
		}
		bgdRect.setFill(bgdColor);
	}
	
	/**
	 * Detects which wall color is selected by the user
	 */
	public void wallColor() {
		switch(wallComboBox.getValue()) {
			case "CADETBLUE":
				wallColor = Color.CADETBLUE;
				break;
			case "BLACK":
				wallColor = Color.BLACK;
				break;
			case "BROWN":
				wallColor = Color.BROWN;
				break;
			case "DARKBLUE":
				wallColor = Color.DARKBLUE;
				break;
			case "DIMGRAY":
				wallColor = Color.DIMGRAY;
				break;
			case "RED":
				wallColor = Color.RED;
				break;
			case "PURPLE":
				wallColor = Color.PURPLE;
				break;
			case "GREEN":
				wallColor = Color.GREEN;
				break;
		}
		wallRect.setFill(wallColor);
		
	}
	
}