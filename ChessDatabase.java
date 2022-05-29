import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;

public class ChessDatabase
{
    private ArrayList<Game> gameList;
    private HashMap<String, HashMap<PLAYER_COLOR, Integer>> squareFrequencies;
    private HashMap<String, HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>> winFrequencies;

    private int totalTurns;
    private int totalGames;
    private HashMap<String, HashMap<PLAYER_COLOR, Double>> squarePercentTime;
    private HashMap<String, HashMap<PLAYER_COLOR, Double>> squarePercentWin;

    public ChessDatabase(File database)
    {
        gameList = new ArrayList<Game>();

        squareFrequencies = new HashMap<String, HashMap<PLAYER_COLOR, Integer>>();
        winFrequencies = new HashMap<String, HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>>();

        squarePercentTime = new HashMap<String, HashMap<PLAYER_COLOR, Double>>();
        squarePercentWin = new HashMap<String, HashMap<PLAYER_COLOR, Double>>();

        extractData(database);
        calculateMetaData();
    }

    public void addData(File database)
    {
        extractData(database);
        calculateMetaData();
    }

    private void extractData(File database)
    {
        try
        {
            Scanner gameScanner = new Scanner(database);

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
    }

    private void calculateMetaData()
    {
        squarePercentTime.clear();
        squarePercentWin.clear();
        totalGames = gameList.size();

        String[] squareLetters = {"a", "b", "c", "d", "e", "f", "g", "h"};
        String[] squareNumbers = {"1", "2", "3", "4", "5", "6", "7", "8"};
        for(String letter : squareLetters)
        {
            for(String number : squareNumbers)
            {
                String coordinate = letter + number;

                totalTurns += squareFrequencies.get(coordinate).get(PLAYER_COLOR.WHITE);
                totalTurns += squareFrequencies.get(coordinate).get(PLAYER_COLOR.BLACK);
                totalGames += winFrequencies.get(coordinate).get(PLAYER_COLOR.WHITE).size();
                totalGames += winFrequencies.get(coordinate).get(PLAYER_COLOR.BLACK).size();
            }
        }

        for(String letter : squareLetters)
        {
            for(String number : squareNumbers)
            {
                String coordinate = letter + number;
                PLAYER_COLOR[] colors = {PLAYER_COLOR.WHITE, PLAYER_COLOR.BLACK};

                squarePercentTime.put(coordinate, new HashMap<PLAYER_COLOR, Double>());
                squarePercentWin.put(coordinate, new HashMap<PLAYER_COLOR, Double>());

                for(PLAYER_COLOR color : colors)
                {
                    squarePercentTime.get(coordinate).put(color, (double)(squareFrequencies.get(coordinate).get(color)) / totalTurns * 100);

                    ArrayList<PLAYER_COLOR> winsList = winFrequencies.get(coordinate).get(color);
                    int wins = 0;
                    for(PLAYER_COLOR winner : winsList)
                    {
                        if(winner == color) wins++;
                    }
                    squarePercentWin.get(coordinate).put(color, (double)wins / winsList.size() * 100);
                }
            }
        } 
    }

    public void printMetaData()
    {
        System.out.println("Percent Time Spent On Square:\n");
        System.out.println(squarePercentTime.toString());
        System.out.println("\n\nPercent Time Won On Square:\n");
        System.out.println(squarePercentWin.toString());
    }
}
