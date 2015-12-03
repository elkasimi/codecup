#include <stdio.h>
#include <string.h>

#define EQUAL_STRING(s1, s2) (strcmp((s1), (s2)) == 0)

typedef struct Position {
	//d�finir les champs que vs juger
	//int�ressants pour la position
	//� mettre dans cette structure
	//par exemple
	//int fields[N][N];
	//int player;
} Position;

typedef struct Move {
	int from_x;
	int from_y;
	int to_x;
	int to_y;
} Move;

// initialiser votre position pour l'utiliser
void init_position(Position* pos) {
	//! TODO
}

Move get_best_move(Position* pos) {
	Move best_move;
	// c'est ici o� vous devez �laborer un algorithme ou un
	// m�chanisme pour trouver le bon coup � jouer dans la position pos
	//! TODO
	//un message de log sur stderr
	fprintf(stderr, "Searching the best move\n");
	fflush(stderr);
	
	return best_move;
}

Move read_move(const char* s) {
	Move move;
	
	//Parser la chaine de caract�res pour r�cup�rer les valeurs de
	//from_x, from_y, to_x et to_y
	//un message de log sur stderr
	fprintf(stderr, "Reading move\n");
	fflush(stderr);
	
	return move;
}


void do_move(Position* pos, Move* move) {
	// faire les changements n�cessaires � la structure pos
	// si le coup en param�tre est jou�
	
	//un message de log sur stderr
	fprintf(stderr, "Doing a move\n");
	fflush(stderr);
}

void display_move(Move* move) {
	// faire ici le traitement pour afficher le coup en param�tre
	//!TODO
	
	//un message de log sur stderr
	fprintf(stderr, "Displaying a move\n");
	fflush(stderr);
}

int main() {
	char s[1024];
	Position pos;
	
	init_position(&pos);
	scanf("%s", s);
	
	//tant que la chaine lue est diff�rente de "Quit" on boucle
	while(!EQUAL_STRING(s, "Quit")) {
		//si la chaine lue est diff�rente de Start donc c'est un coup de l'adversaire
		//qu'on doit lire	
		if(!EQUAL_STRING(s, "Start")) {
			Move opp_move = read_move(s);
			do_move(&pos, &opp_move);
		}
		
		//ici on doit donner notre coup � jouer 
		Move best_move = get_best_move(&pos);
		do_move(&pos, &best_move);
		display_move(&best_move);
		
		scanf("%s", s);
	}
	
	return 0;
}
