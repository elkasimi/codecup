import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class Move {
	public Move() {}
	int fromX;
	int fromY;
	int toX;
	int toY;
}

class Position {
	// initialiser votre position pour l'utiliser
	// dans le constructeur de la classe Position
	public Position() {}

	// faire les changements n�cessaires � la structure pos
	// si le coup en param�tre est jou�	
	public void doMove(Move move) {
		//un message de log sur stderr
		System.err.println("Doing a move");
	}
	
	//d�finir les champs que vs juger
	//int�ressants pour la position
	//� mettre dans cette structure
	//par exemple
	//int fields[N][N];
	//int player;
}

class AI {
	public static Move getBestMove(Position pos) {
		Move bestMove = new Move();
		// c'est ici o� vous devez �laborer un algorithme ou un
		// m�chanisme pour trouver le bon coup � jouer dans la position pos
		//! TODO
		//un message de log sur stderr
		System.err.println("Searching the best move");
		
		return bestMove;
	}
}

//Pour les entr�es/sorties
class IO {
	public static Move readMove(String s) {
		Move move = new Move();
		
		//Parser la chaine de caract�res pour r�cup�rer les valeurs de
		//fromX, fromY, toX et toY
		//un message de log sur stderr
		System.err.println("Reading move");
		
		return move;
	}
	
	public static void displayMove(Move move) {
		// faire ici le traitement pour afficher le coup en param�tre
		//!TODO
		
		//un message de log sur stderr
		System.err.println("Displaying a move");
	}

}

public class player {
	public static void main(String[] args) throws IOException {
		
		Position pos = new Position();
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String s = reader.readLine();
		
		//tant que la chaine lue est diff�rente de "Quit" on boucle
		while(s.compareTo("Quit") != 0) {
			//si la chaine lue est diff�rente de Start donc c'est un coup de l'adversaire
			//qu'on doit lire
			if(s.compareTo("Start") != 0) {
				Move oppMove = IO.readMove(s);
				pos.doMove(oppMove);
			}
			
			//ici on doit donner notre coup � jouer 
			Move bestMove = AI.getBestMove(pos);
			pos.doMove(bestMove);
			IO.displayMove(bestMove);
			
			s = reader.readLine();
		}
	}
}
