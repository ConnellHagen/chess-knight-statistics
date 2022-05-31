import java.io.File;

import ChessDataExtraction.*;

public class Main
{
    public static void main(String[] args)
    {
        ChessDatabase jan2013 = new ChessDatabase(new File("data/lichess-database-jan2013.pgn"));
        DatabaseToJSON jan2013json = new DatabaseToJSON(jan2013);
        jan2013json.toJSON(System.getProperty("user.dir"), "metadata.json");
    }
}