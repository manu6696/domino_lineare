#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

enum Status { CONTINUE, INTERACTIVE, AI, FINISH };

typedef unsigned char uchar;

//Definizione struttura tessera
struct elem {
	int sinistra;
	int destra;
};
typedef struct elem elemento;

//////////////
//			//
// Function //
//			//
//////////////

//Stampa intestazione
void stampa_intestazione(int row, int col) {

	printf("\n");

	for (int j = 0; j < row; ++j) {
		for(int i = 0; i < col; ++i) {
			printf("*");
		}
		printf("\n");
	}

	printf("\n");

	for (int i = 0; i < 2; ++i) printf("\t");

	printf("DOMINO LINEARE");

	printf("\n");

	printf("\n");

	for (int j = 0; j < row; ++j) {
		for(int i = 0; i < col; ++i) {
			printf("*");
		}
		printf("\n");
	}

	printf("\n");
}

//Stampa singola tessera
void stampa_tessera (int const s, int const d) {
	printf("[");
	printf("%d", s);
	printf("|");
	printf("%d", d);
	printf("]");
}

//Stampo tutte le tessere
void stampa_tessere (elemento* tessere, int qty) {
	for(int i = 0; i < qty; i++) {
		if(tessere[i].sinistra != 0 && tessere[i].destra != 0){
			stampa_tessera(tessere[i].sinistra, tessere[i].destra);
			printf(" ");
		}
	}
	printf("\n");
}

//Controllo se la tessera non è vuota
bool is_null (elemento* tessere,int i) {
	if(tessere[i].sinistra == 0 && tessere[i].destra == 0) return true;
	return false;
}

//Controllo se l'array è vuoto
bool is_void (elemento* tessere, int qty) {

	bool controllo = true;

	for(int i = 0; i < qty; i++) {
		if(tessere[i].sinistra && tessere[i].destra) controllo = false;
	}

	return controllo;
}

//Controllo se la tessera selezionata può essere inserita sul campo
bool is_match (elemento* tessere, int qty, int s, int d, int lato) {
	if (!lato && tessere[0].sinistra != d) return false;
	if (lato == 1) {
		int indice = 0;
		for(int i = 0; i < qty; i++) {
			if(tessere[i].sinistra == 0 && tessere[i].destra == 0) {
				indice = i - 1;
				break;
			}
		}
		if(tessere[indice].destra != s) return false;
	}

	return true;
}

//Controllo se ci sono ancora tessere valide che possono essere inserite sul campo
bool continue_game (elemento* tessere, elemento* campo, int qty) {

	int indice = 0;

	for(int i = 0; i < qty; i++) {
		if(campo[i].sinistra == 0 && campo[i].destra == 0) {
			indice = i - 1;
			break;
		}
	}

	for(int i = 0; i < qty; i++) {
		if(tessere[i].sinistra && tessere[i].destra) {
			if(tessere[i].sinistra == campo[0].sinistra || tessere[i].destra == campo[0].sinistra) {
				return true;
			}
				
			if(tessere[i].sinistra == campo[indice].destra || tessere[i].destra == campo[indice].destra) {
				return true;
			}
		}
			
	}

	return false;	
}

//Ricerco esistenza tessera
int ricerca_tessera (elemento* tessere, int qty, int s, int d) {

	for(int i = 0; i < qty; i++) {
		 if(s == tessere[i].sinistra && d == tessere[i].destra) return 1;
		 if(d == tessere[i].sinistra && s == tessere[i].destra) return 1;
	}

	return 0;
}

//Aggiorno le tessere
void aggiorna_tessere (elemento* tessere, elemento* campo, int qty, int s, int d, int lato) {
	
	bool campo_vuoto = true;
	int indice_tes = 0;
	int indice_cam = 0;

	for(int i = 0; i < qty; i++) {
		if((tessere[i].sinistra == s && tessere[i].destra == d) || (tessere[i].sinistra == d && tessere[i].destra == s))
			indice_tes = i;
		if(campo[i].sinistra != 0 && campo[i].destra != 0) campo_vuoto = false;
	}

	if(campo_vuoto){
		campo[0].sinistra = s;
		campo[0].destra = d;
		tessere[indice_tes].sinistra = 0;
		tessere[indice_tes].destra = 0;
	} else {
		if(lato) {
			for(int i = 0; i < qty; i++) {
				if(campo[i].sinistra == 0 && campo[i].destra == 0) {
					indice_cam = i;
					break;
				}
			}
			campo[indice_cam].sinistra = s;
			campo[indice_cam].destra = d;
			tessere[indice_tes].sinistra = 0;
			tessere[indice_tes].destra = 0;

		} else {
			for(int i = qty - 1; i != 0; i--) {
				campo[i] = campo[i - 1];
			}
			campo[0].sinistra = s;
			campo[0].destra = d;
			tessere[indice_tes].sinistra = 0;
			tessere[indice_tes].destra = 0;
		}
	}
}

//Calcolo punteggio finale
int calcolo_punteggio (elemento* tessere, int qty) {
	if(qty == 0) return 0;
	return tessere[0].sinistra + tessere[0].destra + calcolo_punteggio(tessere+1,qty-1);
}

//Cerco migliore combinazione ricorsione
int best_comb_rec (elemento* tessere,elemento* campo, int qty,int camp_qty, int act_sum, int ind_tex, int mode) {
	
	int sum = 0;

	if(mode == 1) {
		printf("\n#####################\n");
		printf("\nTESSERE A DISPOSIZIONE: ");
		stampa_tessere(tessere, qty);
		printf("\nCAMPO: ");
		stampa_tessere(campo, qty);
		printf("\n#####################\n");
	}

	if(ind_tex == qty) return sum;

	if(qty == camp_qty) return sum;		
	
	
	for(int i = 0; i < qty; i++) {
		if(is_match(campo,qty,tessere[i].sinistra,tessere[i].destra, 0) && i != ind_tex && !is_null(tessere,i)) {
			aggiorna_tessere(tessere,campo,qty,tessere[i].sinistra,tessere[i].destra,0);
			sum = tessere[i].sinistra + tessere[i].destra + best_comb_rec(tessere,campo,qty,camp_qty+1,act_sum,i,mode);
		}

		if(is_match(campo,qty,tessere[i].destra,tessere[i].sinistra, 0) && i != ind_tex && !is_null(tessere,i)) {
			aggiorna_tessere(tessere,campo,qty,tessere[i].destra,tessere[i].sinistra,0);
			sum = tessere[i].sinistra + tessere[i].destra + best_comb_rec(tessere,campo,qty,camp_qty+1,act_sum,i,mode);
		}

		if(is_match(campo,qty,tessere[i].sinistra,tessere[i].destra, 1) && i != ind_tex && !is_null(tessere,i)) {
			aggiorna_tessere(tessere,campo,qty,tessere[i].sinistra,tessere[i].destra,1);
			sum = tessere[i].sinistra + tessere[i].destra + best_comb_rec(tessere,campo,qty,camp_qty+1,act_sum,i,mode);
		}

		if(is_match(campo,qty,tessere[i].destra,tessere[i].sinistra, 1) && i != ind_tex && !is_null(tessere,i)) {
			aggiorna_tessere(tessere,campo,qty,tessere[i].destra,tessere[i].sinistra,1);
			sum = tessere[i].sinistra + tessere[i].destra + best_comb_rec(tessere,campo,qty,camp_qty+1,act_sum,i,mode);
		}
	}
}

//Cerco migliore combinazione 
int best_comb (elemento* tessere,elemento* campo, int qty,elemento* tessere_rim, int* s, int* d, int* ind) {

	int sum = 0;

	elemento*tessere_copy = (elemento*) malloc(sizeof(elemento)*qty);
	if(!tessere_copy) exit(EXIT_FAILURE);

	for(int i = 0; i < qty; i++) {
		tessere_copy[i] = tessere[i];
	}

	for(int i = 0; i < qty; i++) {

		//printf("\n***************\n HO INIZIATO CON [%d|%d]\n*****************\n",tessere[i].sinistra, tessere[i].destra );

		elemento* campo_prova = (elemento*) malloc(sizeof(elemento)*qty);
		if(!campo_prova) exit(EXIT_FAILURE);

		for(int j = 0; j < qty; j++) {
			campo_prova[j].sinistra = 0;
			campo_prova[j].destra = 0;
		}

		campo_prova[0] = tessere_copy[i];
		tessere_copy[i].sinistra = 0;
		tessere_copy[i].destra = 0;

		best_comb_rec(tessere_copy,campo_prova,qty, 1, 0, i, 0);
		int punti = calcolo_punteggio(campo_prova,qty);

		if(punti > sum) {
			//printf("\n***************\n IL VINCENTE E' [%d|%d]\n*****************\n",tessere[i].sinistra, tessere[i].destra );
			*ind = i;
			*s = tessere[i].sinistra;
			*d = tessere[i].destra;
			sum = punti;
			for(int j = 0; j < qty; j++) 
				tessere_rim[j] = tessere_copy[j];
			for(int i = 0; i < qty; i++)
				campo[i] = campo_prova[i];
		}

		for(int j = 0; j < qty; j++)
			tessere_copy[j] = tessere[j];

		for(int k = 0; k < qty; k++) {
			campo_prova[k].sinistra = 0;
			campo_prova[k].destra = 0;
		}
			

		free(campo_prova);
		
	}

	free(tessere_copy);
	return sum;
}

//Solo per visualizzazione passaggi posizionamenti computer
int single_comb (elemento* tessere,elemento* campo, int qty,elemento* tessere_rim, int s, int d, int ind, int mode) {

	elemento* tessere_new = (elemento*) malloc(sizeof(elemento)*qty);
	if(!tessere_new) exit(EXIT_FAILURE);

	for(int i = 0; i < qty; i++) {
		tessere_new[i] = tessere[i];
	}

	elemento* campo_new = (elemento*) malloc(sizeof(elemento)*qty);
	if(!campo_new) exit(EXIT_FAILURE);

	for(int i = 0; i < qty; i++) {
		campo_new[i].sinistra = 0;
		campo_new[i].destra = 0;
	}

	campo_new[0].sinistra = s;
	campo_new[0].destra = d;

	for(int i = 0; i < qty; i++) {
		if((tessere_new[i].sinistra == campo_new[0].sinistra && tessere_new[i].destra == campo_new[0].destra) || (tessere_new[i].destra == campo_new[0].sinistra && tessere_new[i].sinistra == campo_new[0].destra)) {
			tessere_new[i].sinistra = 0;
			tessere_new[i].destra = 0;
			break;
		}
	}

	best_comb_rec(tessere_new,campo_new,qty, 1, 0, ind, mode);
			

	for(int j = 0; j < qty; j++) 
		tessere_rim[j] = tessere_new[j];

	for(int i = 0; i < qty; i++)
		campo[i] = campo_new[i];
	
	free(campo_new);
	free(tessere_new);
}

//Gioco
void gioco (elemento* tessere, elemento* campo, int qty) {

	int d = 0;
	int s = 0;
	int j = 0;

	enum Status gameStatus;

	while (gameStatus != FINISH) {

		char* mystr_tessera = (char*)malloc(100+1);
		if(!mystr_tessera) exit(EXIT_FAILURE);

		int lato = -1;
		int lato_app = 0;
		bool found = false;

		printf("\n#######################################\n");
		if(!is_void(campo,qty)) 
			printf("\n---> Il punteggio e' di %d punti\n", calcolo_punteggio(campo, qty));

		printf("\nHai a disposizione le seguenti tessere:\n");
		stampa_tessere(tessere, qty);
		printf("\nCampo di gioco:\n");

		if(!is_void(campo,qty)) stampa_tessere(campo, qty);
		else printf("[vuoto]\n");

		printf("\nInserisci la tessera:\n[  ]\b\b\b");

		scanf("%s", mystr_tessera);

		s = mystr_tessera[0] - '0';
		d = mystr_tessera[1] - '0';
		free(mystr_tessera);

		if(s < 1 || s > 6 || d < 1 || d > 6) {
			printf("\nInserimento non valido! Riprovare.\n");
			s = 0;
			d = 0;
			continue;
		}

		if(ricerca_tessera(tessere, qty, s, d)) {
			if(campo[0].sinistra && campo[0].destra) {
				printf("\nIn quale lato la vuoi inserire?\nA = Sinistra\nD = Destra\n\n0 = Annulla\n");
				printf("\nLato: ");

				char* lato_str = (char*)malloc(100+1);
				if(!lato_str) exit(EXIT_FAILURE);

				scanf("%s", lato_str);

				lato_app = (int)lato_str[0];
				free(lato_str);

				if (lato_app==97 || lato_app==65) lato = 0; // 97=a 65=A
				if (lato_app==100 || lato_app ==68) lato = 1; // 100=d 68=D
				if (lato_app == 48) lato = 3; // 48 = zero

				if(lato != 0 && lato != 1 && lato != 3) {
					lato = -1;
					printf("\nSelezione lato errata!\n");
					continue;
				}
			}

			if(!is_void(campo,qty) && lato != 0 && lato != 1 && lato != 3) {
				printf("\nSelezione lato errata!\n");
				continue;
			}

			if(lato == 3) continue;

			if(!is_void(campo,qty) && !is_match(campo,qty,s,d,lato) ) {
				printf("\n!!!!!!!!!!!!!!!!!\n");
				printf("Mossa non valida!\n");
				printf("!!!!!!!!!!!!!!!!!\n");
				continue;
			}

			aggiorna_tessere(tessere,campo, qty, s, d, lato);
		} else {
			printf("\n\nTessera non esistente!\n");
		}
		
		if(is_void(tessere, qty) || !continue_game(tessere,campo,qty)) gameStatus = FINISH;
	
	}
}


//////////////
//			//
// Modalità //
//			//
//////////////


int interactive_mode (int enable, elemento* tessere, elemento* campo, int qty) {

	if(enable != INTERACTIVE) return 1;

	printf("\n#######################################\n\n");
	printf("Hai scelto la modalita' interattiva!\n");
	gioco(tessere, campo, qty);
	printf("\n#######################################\n");
	printf("                RISULTATO\n");

	printf("\nTessere rimanenti: ");
	stampa_tessere(tessere, qty);

	printf("\nCampo finale: ");
	stampa_tessere(campo, qty);

	printf("\n+++++++++++++++++++++++++++++++++++++++\n");
	printf("Il punteggio finale e' di %d punti\n", calcolo_punteggio(campo, qty));
	printf("+++++++++++++++++++++++++++++++++++++++\n");
	printf("\n#######################################\n\n");
}

int AI_mode (int enable, elemento* tessere, elemento* campo, int qty) {


	int s = 0;
	int d = 0;
	int ind = 0;
	int ind_sing = 0;
	int mode = 0;
	int mode_app = 1;

	if(enable != AI) return 1;

	elemento* campo_cpu = (elemento*) malloc(sizeof(elemento)*qty);
	if(!campo_cpu) exit(EXIT_FAILURE);

	elemento* tessere_rim_cpu = (elemento*) malloc(sizeof(elemento)*qty);
	if(!tessere_rim_cpu) exit(EXIT_FAILURE);

	elemento* tessere_copy = (elemento*) malloc(sizeof(elemento)*qty);
	if(!tessere_copy) exit(EXIT_FAILURE);

	for(int i = 0; i < qty; i++) {
		campo_cpu[i].sinistra = 0;
		campo_cpu[i].destra = 0;
		tessere_rim_cpu[i].sinistra = 0;
		tessere_rim_cpu[i].destra = 0;
	}

	for(int i = 0; i < qty; i++) 
		tessere_copy[i] = tessere[i];


	int sum = best_comb(tessere,campo_cpu,qty,tessere_rim_cpu, &s, &d, &ind);
	printf("\n#######################################\n\n");
	printf("Hai scelto la modalita' vs Computer!\n");
	
	gioco(tessere, campo, qty);

	printf("\n#######################################\n");
	printf("\nAdesso tocca a me...\n");
	printf("\nVuoi visualizzare i passaggi che ho fatto?\n0 = No\n1 = (Si)\n\nContinua: ");

	char* mode_str = (char*) malloc(100+1);
	if(!mode_str) exit(EXIT_FAILURE);

	scanf("%s", mode_str);

	mode = mode_str[0] - '0';
	free(mode_str);

	if(mode == 0) mode_app = 0;
	else mode_app = 1;

	elemento* campo_new = (elemento*) malloc(sizeof(elemento)*qty);
	if(!campo_new) exit(EXIT_FAILURE);

	elemento* tessere_new = (elemento*) malloc(sizeof(elemento)*qty);
	if(!tessere_new) exit(EXIT_FAILURE);

	for(int i = 0; i < qty; i++) {
		campo_new[i].sinistra = 0;
		campo_new[i].destra = 0;
		tessere_new[i].sinistra = 0;
		tessere_new[i].destra = 0;
	}

	single_comb(tessere_copy,campo_new,qty,tessere_new, s, d, ind, mode_app);

	printf("\n#######################################\n");
	printf("                RISULTATO\n");

	printf("\nTessere rimanenti giocatore: ");
	stampa_tessere(tessere, qty);

	printf("\nCampo finale giocatore: ");
	stampa_tessere(campo, qty);

	printf("\n---------------------------\n");

	printf("\nTessere rimanenti computer: ");
	stampa_tessere(tessere_new, qty);

	printf("\nCampo finale computer: ");
	stampa_tessere(campo_new, qty);

	printf("\n+++++++++++++++++++++++++++\n\n");
	printf("Il punteggio finale del giocatore e' di %d punti\n", calcolo_punteggio(campo, qty));
	printf("Il punteggio finale del computer e' di %d punti\n", calcolo_punteggio(campo_new, qty));
	printf("\n+++++++++++++++++++++++++++\n");

	if(calcolo_punteggio(campo, qty) > calcolo_punteggio(campo_new, qty)) printf("\nHAI VINTO!\n");
	else if (calcolo_punteggio(campo, qty) == calcolo_punteggio(campo_new, qty)) printf("\nPAREGGIO!\n");
	else printf("\nHAI PERSO!\n");

	printf("\n#######################################\n\n");

	free(campo_new);
	free(tessere_new);
	free(campo_cpu);
	free(tessere_rim_cpu);
	free(tessere_copy);
	
}


//////////
//		//
// Main //
//		//
//////////


int main() {

	stampa_intestazione(1, 49);

	//In base all'orario attuale del pc modifico 
	//il seme del generatore di numeri random
	srand(time(NULL));

	//Dichiarate fuori per evitare loop infinto nel caso di selezione non valida
	int continua_int = 1;
	char modality = 0;
	int modality_int = 0;

	while(continua_int) {

		//Genero quantità casuale di tessere da 4 a 21
		//Non considero la generazione di sole 3 tessere
		int qty = 4 + rand() % 17;

		elemento* tessere = (elemento*) malloc(sizeof(elemento)*qty);
		if(!tessere) exit(EXIT_FAILURE);
		
		elemento* campo = (elemento*) malloc(sizeof(elemento)*qty);
		if(!campo) exit(EXIT_FAILURE);

		char* modality = (char*) malloc(100+1);
		if(!modality) exit(EXIT_FAILURE);

		char* continua = (char*) malloc(100+1);
		if(!continua) exit(EXIT_FAILURE);


		//Inizializzo il campo
		for(int i = 0; i < qty; i++) {
			campo[i].sinistra = 0;
			campo[i].destra = 0;
		}

		//Popolo facce di sinistra
		for(int i = 0; i < qty; i++) {
			int num_rand = 1 + rand() % 6;
			tessere[i].sinistra = num_rand;
		}

		//Popolo facce di destra
		for(int i = 0; i < qty; i++) {
			int num_rand = 1 + rand() % 6;
			tessere[i].destra = num_rand;
		}

		printf("Scegliere la modalita' di gioco digitando il numero corrispondente:\n1 = Modalita' interattiva\n2 = Modalita' AI contro Computer\n");

		printf("\n");
		printf("Modalita': ");

		scanf("%s", modality);

		modality_int = modality[0] - '0';
		free(modality);

		printf("\n");

		if(modality_int != INTERACTIVE && modality_int != AI) {
			printf("Selezione non valida!\n\n");
			free(campo);
			free(tessere);
			continue;
		}
		
		interactive_mode(modality_int, tessere, campo, qty);
		AI_mode(modality_int, tessere, campo, qty);

		printf("Vuoi giocare di nuovo?\n0 = No\n1 = Si\n\nContinua: ");

		scanf("%s", continua);
		continua_int = continua[0] - '0';
		free(continua);

		printf("\n");

		if(continua_int != 0 && continua_int != 1) {
			printf("Selezione non valida!\n\n");
			exit(EXIT_FAILURE);
		}
		
		free(campo);
		free(tessere);

		
	}
}