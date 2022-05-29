import java.io.File;

public class Main
{
    public static void main(String[] args)
    {
        ChessDatabase jan2013 = new ChessDatabase(new File("data/lichess-database-jan2013.pgn"));
        jan2013.printMetaData();
    }
}
