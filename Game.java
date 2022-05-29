import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;

public class Game
{
    private PLAYER_COLOR winner;

    private String moves;
    
    public Game(String gameResult, String moves)
    {
        if(gameResult.contains("1-0")) winner = PLAYER_COLOR.WHITE;
        else if(gameResult.contains("0-1")) winner = PLAYER_COLOR.BLACK;
        else winner = PLAYER_COLOR.DRAW;

        this.moves = moves;
    }

    private String[] splitMoves()
    {
        // (\s*\d+\.+\s)|(\s{\s\[%eval\s-*((\d+\.\d+)|(#\d))\]\s\}\s)|([+!?#]+)|(\d\/*\d*-\d\/*\d*)|(\s)
        return moves.split("((\\s*\\d+\\.+\\s)|(\\s\\{\\s\\[%eval\\s-*((\\d+\\.\\d+)|(#\\d))\\]\\s\\}\\s)|([+!?#]+)|(\\d\\/*\\d*-\\d\\/*\\d*)|(\\s))");
    }
    //                              square,         knight color, number of turns spent there          square          knight color,           winner color
    public void extractData(HashMap<String, HashMap<PLAYER_COLOR, Integer>> squareFrequencies, HashMap<String, HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>> winFrequencies)
    {
        String[] seperatedMoves = splitMoves();

        ArrayList<String> whiteKnights = new ArrayList<String>();
        ArrayList<String> blackKnights = new ArrayList<String>();

        whiteKnights.add("b1");
        whiteKnights.add("g1");
        blackKnights.add("b8");
        blackKnights.add("g8");

        // initialization
        for(String wKnight : whiteKnights)
        {
            winFrequencies.putIfAbsent(wKnight, new HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>());
            winFrequencies.get(wKnight).putIfAbsent(PLAYER_COLOR.WHITE, new ArrayList<PLAYER_COLOR>());
            squareFrequencies.putIfAbsent(wKnight, new HashMap<PLAYER_COLOR, Integer>());
        }
        for(String bKnight : blackKnights)
        {
            winFrequencies.putIfAbsent(bKnight, new HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>());
            winFrequencies.get(bKnight).putIfAbsent(PLAYER_COLOR.BLACK, new ArrayList<PLAYER_COLOR>());
            squareFrequencies.putIfAbsent(bKnight, new HashMap<PLAYER_COLOR, Integer>());
        }

        // starting position
        for(String wKnight : whiteKnights)
        {
            winFrequencies.get(wKnight).get(PLAYER_COLOR.WHITE).add(winner);
            // initialize num turns to 1, or if it has already been initialized, increment by one
            if(squareFrequencies.get(wKnight).putIfAbsent(PLAYER_COLOR.WHITE, 1) != null)
            {
                squareFrequencies.get(wKnight).put(PLAYER_COLOR.WHITE, squareFrequencies.get(wKnight).get(PLAYER_COLOR.WHITE) + 1);
            }
        }
        for(String bKnight : blackKnights)
        {
            winFrequencies.get(bKnight).get(PLAYER_COLOR.BLACK).add(winner);
            if(squareFrequencies.get(bKnight).putIfAbsent(PLAYER_COLOR.BLACK, 1) != null)
            {
                squareFrequencies.get(bKnight).put(PLAYER_COLOR.BLACK, squareFrequencies.get(bKnight).get(PLAYER_COLOR.BLACK) + 1);
            }
        }

        PLAYER_COLOR turn = PLAYER_COLOR.WHITE;

        for(String move : seperatedMoves)
        {
            if(move == "") continue;

            ArrayList<String> knightListPtr = null;
            ArrayList<String> opKnightListPtr = null;
            if(turn == PLAYER_COLOR.WHITE)
            {
                knightListPtr = whiteKnights;
                opKnightListPtr = blackKnights;
            }
            else if(turn == PLAYER_COLOR.BLACK)
            {
                knightListPtr = blackKnights;
                opKnightListPtr = whiteKnights;
            }

            // testing for opposing color knights being captured
            if(move.contains("x"))
            {
                Iterator<String> knightIterator = opKnightListPtr.iterator();

                while(knightIterator.hasNext())
                {
                    String knight = knightIterator.next();
                    String captureNotation = "x" + knight;
                    if(move.contains(captureNotation)) knightIterator.remove();
                }
            }

            // if a pawn is promoted to a knight
            if(move.contains("=N"))
            {
                String newCoord = move.substring(move.length() - 4, move.length() - 2);
                knightListPtr.add(newCoord);
            }
            // if a knight is moved
            else if(move.contains("N"))
            {
                String newCoord = move.substring(move.length() - 2);
                String strippedCoordinate = move.substring(1, move.length() - 2);
                if(strippedCoordinate.contains("x"))
                {
                    strippedCoordinate = strippedCoordinate.substring(0, strippedCoordinate.length() - 1);
                }

                // tests to determine which knight was moved
                if(strippedCoordinate.matches("(.*)([a-h]|[1-8])(.*)"))
                {
                    for(int i = 0; i < knightListPtr.size(); i++)
                    {
                        if(strippedCoordinate.contains(knightListPtr.get(i)))
                        {
                            knightListPtr.set(i, newCoord);
                        }
                    }
                }
                else
                {
                    char letter = Character.valueOf(newCoord.charAt(0));
                    int number = Integer.valueOf(newCoord.substring(1, 2));

                    HashSet<String> possibleKnightCoords = new HashSet<String>();
                    possibleKnightCoords.add(String.valueOf((char)(letter + 1)) + String.valueOf(number + 2));
                    possibleKnightCoords.add(String.valueOf((char)(letter + 2)) + String.valueOf(number + 1));
                    possibleKnightCoords.add(String.valueOf((char)(letter + 2)) + String.valueOf(number - 1));
                    possibleKnightCoords.add(String.valueOf((char)(letter + 1)) + String.valueOf(number - 2));
                    possibleKnightCoords.add(String.valueOf((char)(letter - 1)) + String.valueOf(number + 2));
                    possibleKnightCoords.add(String.valueOf((char)(letter - 1)) + String.valueOf(number - 2));
                    possibleKnightCoords.add(String.valueOf((char)(letter - 2)) + String.valueOf(number + 1));
                    possibleKnightCoords.add(String.valueOf((char)(letter - 2)) + String.valueOf(number - 1));

                    // System.out.println(possibleKnightCoords);

                    for(int i = 0; i < knightListPtr.size(); i++)
                    {
                        if(possibleKnightCoords.contains(knightListPtr.get(i)))
                        {
                            knightListPtr.set(i, newCoord);
                        }
                    }
                }
            }
            
            // updating the win probabilities for the knights at the current squares
            for(String knight : knightListPtr)
            {
                winFrequencies.putIfAbsent(knight, new HashMap<PLAYER_COLOR, ArrayList<PLAYER_COLOR>>());
                winFrequencies.get(knight).putIfAbsent(turn, new ArrayList<PLAYER_COLOR>());
                squareFrequencies.putIfAbsent(knight, new HashMap<PLAYER_COLOR, Integer>());

                winFrequencies.get(knight).get(turn).add(winner);
                if(squareFrequencies.get(knight).putIfAbsent(turn, 1) != null)
                {
                    squareFrequencies.get(knight).put(turn, squareFrequencies.get(knight).get(turn) + 1);
                }
            }
            
            // switch turns so the next move can be analyzed
            if(turn == PLAYER_COLOR.WHITE) turn = PLAYER_COLOR.BLACK;
            else turn = PLAYER_COLOR.WHITE;
        }
    }

}