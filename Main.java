import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;

public class Main
{
    public static void main(String[] args)
    {
        ArrayList<Game> gameList = new ArrayList<Game>();

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

    }
}
