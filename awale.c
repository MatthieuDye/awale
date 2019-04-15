#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 6

// propre à toutes les parties
int player_score = 0;
int player_table[TABLE_SIZE] = {4,4,4,4,4,4};

int computer_score = 0;
int computer_table[TABLE_SIZE] = {4,4,4,4,4,4};

// propre à une partie
int ingame_progress = 1;

int nb_turns = 0;
int id_selected_case = 0;
int nb_seeds_to_move = 0;
int id_final_case = 0;

void table_displayed()
{
	for (int i = TABLE_SIZE - 1; i >= 0 ; i--){
		printf("|%d|\t", computer_table[i]);
	}
	printf(" Computer, Score : %d,\n", computer_score);
	
	printf("\n");
	
	for (int i = 0; i < TABLE_SIZE ; i++) {
		printf("|%d|\t", player_table[i]);
	}
	printf(" Player, Score : %d,\n", player_score );
	
	printf("\n");
}

int * table_Of(int active_player) {
	if (active_player==0) {
		return computer_table;
	} else {
		return player_table;
	}
}

// retourne le nombre de granes sur la table d'u joueur
int table_sum_seeds(int player) {
	int cpt=0;
	for (int i = 0; i < TABLE_SIZE ; i++) {
			cpt = cpt + table_Of(player)[i];
		}
	return cpt;
}

// retourne le nombre total de graines sur les deux plateaux
int total_sum_seeds(){
	return table_sum_seeds(0)+table_sum_seeds(1);
}

int a_table_is_empty() {

	// ordi vide + joueur pas vide = 0
	// ordi vide + joueur vide = -2 = egalité ou autre condition de victoire
	// ordi pas vide + joueur vide = 1
	// ordi pas vide + joueur pas vide = -1
	int result = 0;
	if (table_sum_seeds(0)==0) { // si le tableau de l'ordi est vide
		result = 0; // je renvoie son id
		if (table_sum_seeds(1)==1) { // si le tableau du joueur est vide LUI AUSSI
			result = -2; // les d pas vide + joueur pas vide eux joueurs ont perdu
		}
	} else {// sinon, si le tbl de l'ordi n'est pas vide
		if (table_sum_seeds(1)==1) { // si le joueur n'a plus de graines
			result = 1; // il a perdu
		} else {
			result = -1; // personne ne perd
		}
	}
	return result;
}

int score(int player) {
	if (player == 0) {
		return computer_score;
	} else { 
		return player_score;
	}
}

void update_score(int player, int score_to_add) {
	if (player == 0) {
		computer_score = computer_score + score_to_add;
	} else { 
		player_score = player_score + score_to_add;
	}
}

int swap(int player) {
	return 1 - player;
}

void player_choice() {
	printf("Choisisez la case que vous allez vider. \n");
	scanf("%d", &id_selected_case);
	if (id_selected_case<1 && id_selected_case>6) {
		printf("Le nombre choisi doit être compris entre 1 et 6 inclus.\n");
		player_choice();
	} else {
		id_selected_case = id_selected_case-1;
		printf("Vous avez choisi la case n°%d. \n", id_selected_case+1 );
	}
}

void computer_choice() {
	id_selected_case = rand() % 6;
	printf("L'ordinateur a choisi la case n°%d. \n", id_selected_case+1 );
}

void checking_for_harvest(int player) {
	
	printf("Vérification récolte...\n");
	if ((id_final_case < TABLE_SIZE && 
			table_Of(swap(player))[id_final_case] == 2 ) || 
				table_Of(swap(player))[id_final_case] == 3) {
		printf("Récolte en cours...\n");
		update_score(player, table_Of(swap(player))[id_final_case] );
		table_Of(swap(player))[id_final_case] = 0;
		id_final_case++;
		checking_for_harvest(player);
	}

}

void check_for_victory(int player) {
	if (a_table_is_empty() != -1) {
		printf("Le joueur n°%d a perdu : son tableau est vide.\n", a_table_is_empty() );
		ingame_progress = 0;
	} else {
		if (total_sum_seeds() <= 6) {
			printf("Il y a plus que 6 graines ou moins en jeu.\n");
			printf("Le joueur gagnant a le plus gros grenier.\n");
		} else { 
			if (nb_turns == 0) {
				printf("Vous n'avez plus de tours à jouer.\n");
				printf("Le joueur gagnant a le plus gros grenier.\n");
				ingame_progress =0;
			} else {
				if (score(player) >= 25) {
					printf("Le joueur gagnant est le joueur X !!\n!");
					ingame_progress = 0;
				}

			} 
		}
	}
}

// le joueur remplit son tableau
void player_sow(int number_seeds_to_move) {

	int nb_seeds_to_move = number_seeds_to_move;
	int case_to_fill = id_selected_case;	

	while (nb_seeds_to_move != 0 && case_to_fill < TABLE_SIZE ) {

		if (case_to_fill != id_selected_case) {
			player_table[case_to_fill]++;
			nb_seeds_to_move--;
		}
		case_to_fill++;
	}

	if (nb_seeds_to_move != 0) { // si il n'y a plus de graines
		case_to_fill = 0;
		// on remplit le tableau de l'ordinateur
		while (nb_seeds_to_move != 0 && case_to_fill < TABLE_SIZE ) {
			computer_table[case_to_fill]++;
			nb_seeds_to_move--;
			case_to_fill++;	
		}
			
	}

	// on sort si il n'y a plus de graines OU si on sort du tableau

	if (nb_seeds_to_move == 0) { // s'il n'y a plus de graines
		id_final_case = case_to_fill-1; // on garde en mémoire la case sur laquelle on s'est arrêté
		checking_for_harvest(1);
	} else {
		id_selected_case = 0;
		player_sow(nb_seeds_to_move);
	}

}

void computer_sow(int number_seeds_to_move) {

	int nb_seeds_to_move = number_seeds_to_move;
	int case_to_fill = id_selected_case;	

	while (nb_seeds_to_move != 0 && case_to_fill < TABLE_SIZE ) {

		if (case_to_fill != id_selected_case) {
			computer_table[case_to_fill]++;
			nb_seeds_to_move--;
		}
		case_to_fill++;
	}

	if (nb_seeds_to_move == 0) { // si il n'y a plus de graines
		id_final_case = case_to_fill-1; // on garde en mémoire la case sur laquelle on s'est arrêté
	} else {

		case_to_fill = 0;
		// on remplit le tableau de l'ordinateur
		while (nb_seeds_to_move != 0 && case_to_fill < TABLE_SIZE ) {
			player_table[case_to_fill]++;
			nb_seeds_to_move--;
			case_to_fill++;	
		}
			
	}

	// on sort si il n'y a plus de graines OU si on sort du tableau

	if (nb_seeds_to_move == 0) { // s'il n'y a plus de graines
		id_final_case = case_to_fill-1; // on garde en mémoire la case sur laquelle on s'est arrêté
		checking_for_harvest(0);
	} else {
		id_selected_case = 0;
		computer_sow(nb_seeds_to_move);
	}

}

void sowing(int player) {

	if (player == 0) { 
		computer_choice();
		nb_seeds_to_move = computer_table[id_selected_case];
		computer_table[id_selected_case] = 0;
		computer_sow(nb_seeds_to_move);
	} else {
		player_choice();
		nb_seeds_to_move = player_table[id_selected_case];
		player_table[id_selected_case] = 0;
		player_sow(nb_seeds_to_move);
	}
}


int main() {

	// propre à chaque partie

	printf("Bonjour utilisateur !\n");

		    // variable pour partie en cours
		    // menu : nouvelle partie, quitter, consulter regles

	int number_turns = 0;
	printf("Combien de tours voulez vous jouer ? Entrez une valeur :\n");
	scanf("%d", &number_turns);

	printf("Vous jouerez donc %d tours chacun. Bonne partie !\n", number_turns );

	// chaque joueur joue number_turns tours, donc il faut compter 2 fois ce nombre, et enlever le premier tour. 
	nb_turns = (2*number_turns) - 1;

	int active_player = 1; //choose_random_player();

	table_displayed();

		    while (ingame_progress == 1) {

		    	sowing(active_player);

		    	check_for_victory(active_player);

		    	nb_turns--;
		    	active_player = swap(active_player);

		    	table_displayed();
		    }
		    return 0;
		}
