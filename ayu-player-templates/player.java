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

	// faire les changements nécessaires à la structure pos
	// si le coup en paramètre est joué	
	public void doMove(Move move) {
		//un message de log sur stderr
		System.err.println("Doing a move");
	}
	
	//définir les champs que vs juger
	//intéressants pour la position
	//à mettre dans cette structure
	//par exemple
	//int fields[N][N];
	//int player;
}

class AI {
	public static Move getBestMove(Position pos) {
		Move bestMove = new Move();
		// c'est ici où vous devez élaborer un algorithme ou un
		// méchanisme pour trouver le bon coup à jouer dans la position pos
		//! TODO
		//un message de log sur stderr
		System.err.println("Searching the best move");
		
		return bestMove;
	}
}

//Pour les entrées/sorties
class IO {
	public static Move readMove(String s) {
		Move move = new Move();
		
		//Parser la chaine de caractères pour récupérer les valeurs de
		//fromX, fromY, toX et toY
		//un message de log sur stderr
		System.err.println("Reading move");
		
		return move;
	}
	
	public static void displayMove(Move move) {
		// faire ici le traitement pour afficher le coup en paramètre
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
		
		//tant que la chaine lue est différente de "Quit" on boucle
		while(s.compareTo("Quit") != 0) {
			//si la chaine lue est différente de Start donc c'est un coup de l'adversaire
			//qu'on doit lire
			if(s.compareTo("Start") != 0) {
				Move oppMove = IO.readMove(s);
				pos.doMove(oppMove);
			}
			
			//ici on doit donner notre coup à jouer 
			Move bestMove = AI.getBestMove(pos);
			pos.doMove(bestMove);
			IO.displayMove(bestMove);
			
			s = reader.readLine();
		}
	}
}
