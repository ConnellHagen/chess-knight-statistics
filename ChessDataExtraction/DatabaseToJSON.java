package ChessDataExtraction;

import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.HashMap;

public class DatabaseToJSON
{
    ChessDatabase database;
    
    public DatabaseToJSON(ChessDatabase database)
    {
        this.database = database;
    }

    public void toJSON(String directory, String fileName)
    {
        ArrayList<String> coordinates = new ArrayList<String>();
        String letters = "abcdefgh";
        String numbers = "12345678";
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                coordinates.add(letters.substring(i, i + 1) + numbers.substring(j, j + 1));
            }
        }

        HashMap<String, HashMap<PLAYER_COLOR, Integer>> squareFreq = database.getSquareFrequencies();
        HashMap<String, HashMap<PLAYER_COLOR, Double>> squarePercentTime = database.getSquarePercentTime();
        HashMap<String, HashMap<PLAYER_COLOR, Double>> squarePercentWin = database.getSquarePercentWin();

        try
        {
            FileWriter dataFileWriter = new FileWriter(new File(directory, fileName));
            dataFileWriter.write("{\n");
                dataFileWriter.write("\t\"total-games\": " + database.getTotalGames() + ",\n");
                dataFileWriter.write("\t\"white\": " + "\n");
                dataFileWriter.write("\t[\n");
                    for(String coord : coordinates)
                    {
                        dataFileWriter.write("\t\t{\n");
                            dataFileWriter.write("\t\t\t\"" + coord + "\":\n");
                            dataFileWriter.write("\t\t\t[\n");
                                dataFileWriter.write("\t\t\t\t{\"square-num-times\": " + squareFreq.get(coord).get(PLAYER_COLOR.WHITE) + "},\n");
                                dataFileWriter.write("\t\t\t\t{\"square-percent-time\": " + squarePercentTime.get(coord).get(PLAYER_COLOR.WHITE) + "},\n");
                                dataFileWriter.write("\t\t\t\t{\"square-percent-win\": " + squarePercentWin.get(coord).get(PLAYER_COLOR.WHITE) + "}\n");
                            dataFileWriter.write("\t\t\t]\n");
                        dataFileWriter.write("\t\t}");
                        if(!coord.equals("h8")) dataFileWriter.write(",");
                        dataFileWriter.write("\n");
                    }
                dataFileWriter.write("\t],\n");
                dataFileWriter.write("\t\"black\": " + "\n");
                dataFileWriter.write("\t[\n");
                    for(String coord : coordinates)
                    {
                        dataFileWriter.write("\t\t{\n");
                            dataFileWriter.write("\t\t\t\"" + coord + "\":\n");
                            dataFileWriter.write("\t\t\t[\n");
                                dataFileWriter.write("\t\t\t\t{\"square-num-times\": " + squareFreq.get(coord).get(PLAYER_COLOR.BLACK) + "},\n");
                                dataFileWriter.write("\t\t\t\t{\"square-percent-time\": " + squarePercentTime.get(coord).get(PLAYER_COLOR.BLACK) + "},\n");
                                dataFileWriter.write("\t\t\t\t{\"square-percent-win\": " + squarePercentWin.get(coord).get(PLAYER_COLOR.BLACK) + "}\n");
                            dataFileWriter.write("\t\t\t]\n");
                        dataFileWriter.write("\t\t}");
                        if(!coord.equals("h8")) dataFileWriter.write(",");
                        dataFileWriter.write("\n");
                    }
                dataFileWriter.write("\t]\n");
            dataFileWriter.write("}");
            dataFileWriter.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}
