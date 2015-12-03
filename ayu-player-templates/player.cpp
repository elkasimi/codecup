#include <iostream>
#include <string>

using namespace std;

struct Move {
	int fromX;
	int fromY;
	int toX;
	int toY;
};

class Position {
public:
	// initialiser votre position pour l'utiliser
	// dans le constructeur de la classe Position
	Position() {}

	// faire les changements nécessaires à la structure pos
	// si le coup en paramètre est joué	
	void doMove(const Move& move) {
		//un message de log sur stderr
		cerr << "Doing a move" << endl;
	}
	
private:
	//définir les champs que vs juger
	//intéressants pour la position
	//à mettre dans cette structure
	//par exemple
	//int fields[N][N];
	//int player;
};

class AI {
public:
static Move getBestMove(const Position& pos) {
		Move bestMove;
		// c'est ici où vous devez élaborer un algorithme ou un
		// méchanisme pour trouver le bon coup à jouer dans la position pos
		//! TODO
		//un message de log sur stderr
		cerr <<  "Searching the best move" << endl;
		
		return bestMove;
	}
};

//Pour les entrées/sorties
class IO {
public:
	static Move readMove(const string& s) {
		Move move;
		
		//Parser la chaine de caractères pour récupérer les valeurs de
		//fromX, fromY, toX et toY
		//un message de log sur stderr
		cerr << "Reading move" << endl;
		
		return move;
	}
	
	static void displayMove(const Move& move) {
		// faire ici le traitement pour afficher le coup en paramètre
		//!TODO
		
		//un message de log sur stderr
		cerr << "Displaying a move" << endl;
	}

};

int main() {
	string s;
	Position pos;
	
	cin >> s;
	
	//tant que la chaine lue est différente de "Quit" on boucle
	while(s != "Quit") {
		//si la chaine lue est différente de Start donc c'est un coup de l'adversaire
		//qu'on doit lire
		if(s != "Start") {
			Move oppMove = IO::readMove(s);
			pos.doMove(oppMove);
		}
		
		//ici on doit donner notre coup à jouer 
		Move bestMove = AI::getBestMove(pos);
		pos.doMove(bestMove);
		IO::displayMove(bestMove);
		
		cin >> s;
	}
	
	return 0;
}
