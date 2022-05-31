package ChessDataExtraction;

import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;

public class ChessDatabase
{
    private ArrayList<Game> gameList;
    private HashMap<String, HashMap<PLAYER_COLOR, Integer>> squareFrequencies;
    private HashMap<String, HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>> winFrequencies;

    private HashMap<PLAYER_COLOR, Integer> totalTurns;
    private int totalGames;
    private HashMap<String, HashMap<PLAYER_COLOR, Double>> squarePercentTime;
    private HashMap<String, HashMap<PLAYER_COLOR, Double>> squarePercentWin;

    public ChessDatabase(File database)
    {
        gameList = new ArrayList<Game>();

        squareFrequencies = new HashMap<String, HashMap<PLAYER_COLOR, Integer>>();
        winFrequencies = new HashMap<String, HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>>();

        totalTurns = new HashMap<PLAYER_COLOR, Integer>();

        squarePercentTime = new HashMap<String, HashMap<PLAYER_COLOR, Double>>();
        squarePercentWin = new HashMap<String, HashMap<PLAYER_COLOR, Double>>();

        extractData(database);
        calculateMetaData();
    }
    
    public HashMap<String, HashMap<PLAYER_COLOR, Integer>> getSquareFrequencies(){ return squareFrequencies; }
    public HashMap<String, HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>> getWinFrequencies(){ return winFrequencies; }
    public int getTotalGames(){ return totalGames; }
    public HashMap<String, HashMap<PLAYER_COLOR, Double>> getSquarePercentTime(){ return squarePercentTime; }
    public HashMap<String, HashMap<PLAYER_COLOR, Double>> getSquarePercentWin(){ return squarePercentWin; }

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
        totalTurns.clear();
        totalGames = gameList.size();

        PLAYER_COLOR[] colors = {PLAYER_COLOR.WHITE, PLAYER_COLOR.BLACK};

        String letters = "abcdefgh";
        String numbers = "12345678";
        ArrayList<String> coordinates = new ArrayList<String>();
        for(int i = 0; i < 8; i ++)
        {
            for(int j = 0; j < 8; j++)
            {
                coordinates.add(letters.substring(i, i + 1) + numbers.substring(j, j + 1));
            }
        }
        
        for(String coord : coordinates)
        {
            for(PLAYER_COLOR color : colors)
            {
                totalTurns.putIfAbsent(color, 0);
                totalTurns.put(color, totalTurns.get(color) + squareFrequencies.get(coord).get(color));
            }
        }
        for(String coord : coordinates)
        {
            squarePercentTime.put(coord, new HashMap<PLAYER_COLOR, Double>());
            squarePercentWin.put(coord, new HashMap<PLAYER_COLOR, Double>());

            for(PLAYER_COLOR color : colors)
            {
                squarePercentTime.get(coord).put(color, (double)(squareFrequencies.get(coord).get(color)) / totalTurns.get(color) * 100);

                ArrayList<PLAYER_COLOR> winsList = winFrequencies.get(coord).get(color);
                int wins = 0;
                for(PLAYER_COLOR winner : winsList)
                {
                    if(winner == color) wins++;
                }
                squarePercentWin.get(coord).put(color, (double)wins / winsList.size() * 100);
            }
        }

    }

}
