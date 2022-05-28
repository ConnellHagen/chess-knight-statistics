public class Game
{
    public enum PLAYER_COLOR{WHITE, BLACK, DRAW};
    PLAYER_COLOR winner;

    String moves;
    
    public Game(String gameResult, String moves)
    {
        if(gameResult.contains("1-0")) winner = PLAYER_COLOR.WHITE;
        else if(gameResult.contains("0-1")) winner = PLAYER_COLOR.BLACK;
        else winner = PLAYER_COLOR.DRAW;

        this.moves = moves;
    }

}