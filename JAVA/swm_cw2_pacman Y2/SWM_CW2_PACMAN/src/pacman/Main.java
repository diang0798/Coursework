package pacman;


import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * Main method
 * @author Ang Ding
 *
 */
public class Main extends Application {

    @Override
    public void start(Stage theStage) throws Exception{
        theStage.setTitle( "Pacman" );
        Parent root = FXMLLoader.load(getClass().getResource("./controllers/Start.fxml"));
        Scene theScene = new Scene(root, 1225, 720);
        theStage.setScene( theScene );
        theStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}