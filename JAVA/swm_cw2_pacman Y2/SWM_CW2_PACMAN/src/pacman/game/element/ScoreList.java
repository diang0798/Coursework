package pacman.game.element;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import javafx.event.ActionEvent;
import javafx.scene.Group;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

/**
 * Create a permanent high score list 
 * @author Ang Ding
 *
 */
public class ScoreList {
	
	String filename = "resources/scorelist/ScoreList.txt";
	String temp = null;
	String historyScore = null;
	String newScore = null;
	String space = "           ";
	String playerName = null;
	public Text congrats;
	
	/**
	 * Write arrayList into ScoreList.txt file
	 * @param scoreList - An arrayList of high scores 
	 */
	public void writeList(ArrayList<String> scoreList) {
		try {
			BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(filename));
			for(String x : scoreList) {
				bufferedWriter.write(x);
				bufferedWriter.newLine();
			}
			bufferedWriter.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * Read txt file into an arrayList and Scan it.
	 * If player create a new record, return its rank.
	 * @param scoreList - An arrayList to store high scores
	 * @param score - the score of this game
	 * @return the rank of new record or -1
	 */
	public int scanList(ArrayList<String> scoreList, int score) {
		int flag = -1;
		try {
			BufferedReader bufferedReader = new BufferedReader(new FileReader(filename));
			for(int i = 0; i < 10 ; i++) {
				temp = bufferedReader.readLine();
				String[] tempSplit = temp.split(space);
				int historyScore = Integer.parseInt(tempSplit[0]);
				if(score > historyScore && flag == -1) {
					flag = i;
				}
				scoreList.add(temp);
			}
			bufferedReader.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return flag;
	}
	
	/**
	 * Show a screen to allow player to enter his name
	 * Add new high score into arrayList
	 * @param root - group root
	 * @param scoreList - An arrayList
	 * @param score	- the score of this game
	 * @param flag - the rank of new record or -1
	 * @param currentLevel - the level when game ended
	 */
	public void addNewScore(Group root, ArrayList<String> scoreList, int score, int flag, int currentLevel) {
		Text congrats = new Text();
		if(currentLevel == 5) {
			congrats.setText("Congratulations! You have passed all the levels!");
			congrats.setX(BarObstacle.THICKNESS * 4);
	        congrats.setY(BarObstacle.THICKNESS * 5);   
			congrats.setFont(Font.font("Arial", 50));
			congrats.setFill(Color.RED);
		}else {
			congrats.setText("GAME OVER!");
			congrats.setX(BarObstacle.THICKNESS * 11);
	        congrats.setY(BarObstacle.THICKNESS * 5); 
			congrats.setFont(Font.font("Arial", 100));
			congrats.setFill(Color.ROYALBLUE);
		}       
        root.getChildren().add(congrats);
        Text createText = new Text("You create a new record! Please enter your name:");
        createText.setX(BarObstacle.THICKNESS * 11);
        createText.setY(BarObstacle.THICKNESS * 10);
        createText.setFont(Font.font("Arial", 30));
        createText.setFill(Color.RED);
        root.getChildren().add(createText);
        TextField addName = new TextField();
        addName.setLayoutX(BarObstacle.THICKNESS * 20);
        addName.setLayoutY(BarObstacle.THICKNESS * 12);
        addName.setPrefSize(200, 40);
        addName.setPromptText("Enter your name:");
        root.getChildren().add(addName);
        Button enterBtn = new Button("Enter");
        enterBtn.setLayoutX(BarObstacle.THICKNESS * 22);
        enterBtn.setLayoutY(BarObstacle.THICKNESS * 15);
        enterBtn.setPrefSize(100, 50);
        enterBtn.setOnAction((ActionEvent e)->{
        	String scoreStr = Integer.toString(score);
        	if(addName.getText().equals("")) {
        		playerName = "player";
        	}else {
        		playerName = addName.getText();
        	}
			Date date = new Date();
			SimpleDateFormat getTime = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	        String dateStr = getTime.format(date);
	        String newScore = scoreStr + space + "  " + playerName + space + space + dateStr;
	        for(int i = 9; i > flag; i--) {
	        	scoreList.set(i,scoreList.get(i-1));
	        }
	        scoreList.set(flag, newScore);
	        writeList(scoreList);
	        root.getChildren().clear();
	        printScoreList(root, scoreList, flag);
        });
        root.getChildren().add(enterBtn);
	}
	
	/**
	 * Show high score list on the screen
	 * @param root - group root
	 * @param scoreList - An arrayList 
	 * @param flag - the rank of new record or -1
	 */
	public void printScoreList(Group root, ArrayList<String> scoreList, int flag) {
		Text title = new Text("HighScore List");
        title.setX(BarObstacle.THICKNESS * 17);
        title.setY(BarObstacle.THICKNESS * 2.5);
        title.setFont(Font.font("Arial", 60));
        title.setFill(Color.RED);
        root.getChildren().add(title);
        Text items = new Text();
        items.setText(" Rank" + space + "Score" + space + "Player Name" + space + space + "Time");
        items.setX(BarObstacle.THICKNESS * 3);
        items.setY(BarObstacle.THICKNESS * 4.5);
        items.setFont(Font.font("Arial", 30));
        items.setFill(Color.BLACK);
        root.getChildren().add(items);       
        for(int i = 0; i < 10 ; i++) {
        	javafx.scene.text.Text score = new javafx.scene.text.Text();
        	if(i+1 == 10) {
        		score.setText("NO." + (i+1) + "            " + scoreList.get(i));
        	}
        	else {
        		score.setText("  " + "NO." + (i+1) + "            " + scoreList.get(i));
        	}
            score.setX(BarObstacle.THICKNESS * 3);
            score.setY(BarObstacle.THICKNESS * (7 + 2 * i));
            score.setFont(Font.font("Arial", 30));
            if(flag == i) {
            	score.setFill(Color.RED);
            }
            else {
            	score.setFill(Color.BLACK);
            }
            root.getChildren().add(score);
        }
        Text endGame = new Text("Game Over, press ESC to restart");
        endGame.setX(BarObstacle.THICKNESS * 3);
        endGame.setY(BarObstacle.THICKNESS * 28);
        endGame.setFont(Font.font("Arial", 40));
        endGame.setFill(Color.ROYALBLUE);
        root.getChildren().add(endGame);
        
	}
}

	
