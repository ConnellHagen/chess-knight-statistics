import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;

public class Main
{
    public static void main(String[] args)
    {
        ArrayList<Game> gameList = new ArrayList<Game>();

        HashMap<String, HashMap<PLAYER_COLOR, Integer>> squareFrequencies = new HashMap<String, HashMap<PLAYER_COLOR, Integer>>();
        HashMap<String, HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>> winFrequencies = new HashMap<String, HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>>();

        try
        {
            Scanner gameScanner = new Scanner(new File("data/lichess-database.pgn"));

            String gameResult = new String();
            String gameMoves = new String();

            while(gameScanner.hasNextLine())
            {
                while(true)
                {
                    String testLine = gameScanner.nextLine();

                    if(!testLine.contains("Result") && !testLine.matches("(.*)\\d\\.\\s(.*)")) continue;
                    if(testLine.contains("Result")) gameResult = testLine;
                    else
                    {
                        gameMoves = testLine;
                        break;
                    }
                }

                gameList.add(new Game(gameResult, gameMoves));
            }

            gameScanner.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

        for(Game game : gameList)
        {
            game.extractData(squareFrequencies, winFrequencies);
        }

        // System.out.println(winFrequencies.toString());
        System.out.println(squareFrequencies.toString());

    }
}
