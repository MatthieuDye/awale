#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 6

/*  #define bleu "\033[1;34m"
    #define rouge "\033[1;31m"*/

//Bibliothèque des fonctions
void afficher (int T[], int n, int *g);
void remplir(int T[], int n);
int choix_joueur(int T[], int n);
int rand_a_b(int a, int b);
int choix_ordi(int T[], int n);
int changement_plateau_joueur (int joueur[], int ordi[], int n);
int changement_plateau_ordi (int joueur[], int ordi[], int n);
int recolte_joueur(int joueur[], int ordi[], int n, int *grenier_joueur, int case_finale_joueur, int *affichage_nvx_plateau);
int recolte_ordi(int joueur[], int ordi[], int n, int *grenier_ordi, int case_finale_ordi, int *affichage_nvx_plateau);
void jeu(int joueur[], int ordi[], int n, int *grenier_ordi, int *grenier_joueur, int compteur, int *affichage_nvx_plateau);
int graines_joueur(int joueur[], int n);
int graines_ordi(int joueur[], int n);
int fin_jeu(int joueur[], int ordi[], int n, int *grenier_joueur, int *grenier_ordi, int compteur,int nb_coups);


//INITIALISATION
void afficher (int T[], int n, int *g)
{
int i ;
for (i=0 ; i<n ; i++)
  {
printf ("| %d |\t", T[i]);
}
printf("\tGrenier : %d",*g);
}

void remplir(int T[], int n)
{
for(int i=0 ; i<n ; i++)
  {
T[i]=4;
}
}

//SEMER

int choix_joueur(int T[], int n)
{
int i;
printf("C'est a vous de jouer !\nChoisissez une case (attention ce doit être un chiffre entre 1 et 6) :");
scanf("%d",&i);

while((i>6)||(i<1))
  {
printf("Veuillez choisir une case entre 1 et 6.\nCase choisie :");
scanf("%d",&i);
}

while(T[i-1]==0)
  {
printf("La case que vous avez choisie est vide. Veuillez choisir une case contenant des graines.\nCase choisie :");
scanf("%d",&i);
}
return i;
}

//Fonction permettant de choisir un nombre aléatoirement compris dans l'intervalle [1;6]
int rand_a_b(int a, int b)
{
return rand()%(b-a+1)+a;
}

int choix_ordi(int T[], int n)
{
int nb_alea;
srand(time(NULL));
nb_alea=rand_a_b(1,6);

while(T[nb_alea-1]==0)
  {
nb_alea=rand_a_b(1,6);
}

return nb_alea;
}

int changement_plateau_joueur (int joueur[], int ordi[], int n)
{
int graines;
int case_joueur=choix_joueur(joueur,n); // [1,6]
int case_depart=case_joueur-1; //[0,5]

graines=joueur[case_joueur-1];
joueur[case_joueur-1]=0;

while(graines!=0)
  {
//tableau joueur
while((case_joueur<n)&&(graines!=0))
  {
if(case_joueur==case_depart)
  {
case_joueur++;
} else
  {
joueur[case_joueur]=joueur[case_joueur]+1;
graines--;
case_joueur++;
}
}
if(graines==0)
  {
return -1;
}
 else
   {
//tableau ordi
while((case_joueur>0)&&(graines!=0))
  {
ordi[case_joueur-1]=ordi[case_joueur-1]+1;
graines--;
case_joueur--;
}
if(graines==0)
  {
return case_joueur++;
}
}
}
}

int changement_plateau_ordi (int joueur[], int ordi[], int n)
{
int graines;
int case_ordi=choix_ordi(ordi,n); // [1,6]
int case_depart=case_ordi-1; //[0,5]


printf("Case ordi : %d\n",case_ordi);
case_ordi=case_ordi-1;
graines=ordi[case_ordi];
ordi[case_ordi]=0;


while(graines!=0) // ~
  {
//tableau ordi
// case_ordi [0,5]
while((case_ordi>=0)&&(graines!=0)) // ~
  {
if(case_ordi==case_depart) // besoin du cpt ?

  {
case_ordi--;
} else
  {
ordi[case_ordi]=ordi[case_ordi]+1;
graines--;
case_ordi--;
}



}

// sort si case_ordi < 0 (-1) OU graines = 0

if(graines==0)
  {
return -1;
}
 else // graines != 0 && case_ordi = -1
   {

case_ordi++; // case_ordi = 0

//tableau joueur

while((case_ordi<n)&&(graines!=0)) // n = 6 case_ordi [0,5]
  {
joueur[case_ordi]=joueur[case_ordi]+1; // ?
graines--;
case_ordi++;
}

// case_ordi = 6 OU graines = 0

if(graines==0)
  {
return case_ordi;
}
 else
   {
case_ordi--;
}
}
}
}



int recolte_joueur(int joueur[], int ordi[], int n, int *grenier_joueur, int case_finale_joueur, int *affichage_nvx_plateau)
{
int recolte = *grenier_joueur ;
*affichage_nvx_plateau=0;
if (case_finale_joueur== -1)
  {
printf("\nC'est a l'ordinateur de jouer !\n\n");
} else
  {
if( (ordi[case_finale_joueur]==2) || (ordi[case_finale_joueur]==3) )
  {
*affichage_nvx_plateau=1;
printf("\n Vous pouvez recolter.\n");
while( ( case_finale_joueur <= n ) && ( (ordi[case_finale_joueur]==2) || (ordi[case_finale_joueur]==3) ) )
  {
*grenier_joueur = *grenier_joueur + ordi[case_finale_joueur];
ordi[case_finale_joueur]=0;
case_finale_joueur++;
}
recolte = *grenier_joueur - recolte ;
printf(" \n Vous avez fini de recolter. \n Vous avez recolte %d graines, voici le nouveau plateau.\n", recolte);
}
 else
   {
printf("\nVous ne pouvez pas recolter car il n'y a pas 2 ou 3 graines. \n\n");
}
}

return *grenier_joueur;
}

int recolte_ordi(int joueur[], int ordi[], int n, int *grenier_ordi, int case_finale_ordi, int *affichage_nvx_plateau)
{
*affichage_nvx_plateau=0 ;
int recolte = *grenier_ordi ;
if (case_finale_ordi==-1)
  {
printf("C'est a vous de jouer! \n");
} else
  {
if(joueur[case_finale_ordi-1]==2||joueur[case_finale_ordi-1]==3)
  {
*affichage_nvx_plateau=1;
printf("L'ordinateur peut recolter.\n");
while( ( case_finale_ordi > 0 ) && ( (joueur[case_finale_ordi-1]==2) || (joueur[case_finale_ordi-1]==3) ) )
  {
*grenier_ordi = *grenier_ordi + joueur[case_finale_ordi-1];
 joueur[case_finale_ordi-1]=0;
 case_finale_ordi--;
  }
 recolte = *grenier_ordi - recolte ;
 printf("Voici le nouveau plateau.\n");
  }
 else
   {
     printf("\nIl ne peut pas recolter car il n'y a pas 2 ou 3 graines.\n\n");
   }
  }
 return *grenier_ordi;
}

void jeu(int joueur[], int ordi[], int n, int *grenier_joueur, int *grenier_ordi, int compteur, int *affichage_nvx_plateau)
{
  int case_finale_joueur;
  int case_finale_ordi ;

  if (compteur%2==0)
    {
      case_finale_joueur=changement_plateau_joueur(joueur, ordi,n);
      printf("\n\nORDI \n");
      afficher(ordi,N,grenier_ordi);
      printf("\n");
      printf("JOUEUR \n");
      afficher(joueur,N,grenier_joueur);
      printf("\n");
      *grenier_joueur=recolte_joueur(joueur,ordi,n,grenier_joueur,case_finale_joueur,affichage_nvx_plateau);
      if ( *affichage_nvx_plateau==1)
	{
	 
	  printf("\nNouveau plateau\n");
	  printf("\n\nORDI \n");
	  afficher(ordi,N,grenier_ordi);
	  printf("\n");
	  printf("JOUEUR \n");
	  afficher(joueur,N,grenier_joueur);
	  printf("\n");
	  
	}
    } else
    {
      case_finale_ordi=changement_plateau_ordi(joueur, ordi,n);
      printf("\nORDI \n");
      afficher(ordi,N,grenier_ordi);
      printf("\n");
      printf("JOUEUR \n");
      afficher(joueur,N,grenier_joueur);
      printf("\n");
      *grenier_ordi=recolte_ordi(joueur,ordi,n,grenier_ordi,case_finale_ordi,affichage_nvx_plateau);
      if ( *affichage_nvx_plateau==1)
	{
	 
	  printf("\nNouveau plateau\n");
	  printf("\n\nORDI \n");
	  afficher(ordi,N,grenier_ordi);
	  printf("\n");
	  printf("JOUEUR \n");
	  afficher(joueur,N,grenier_joueur);
	  printf("\n");

	}

    }
}
int recolte_joueur_demo(int joueur[], int ordi[], int n, int *grenier_joueur, int case_finale_joueur, int *affichage_nvx_plateau)
{
int recolte = *grenier_joueur ;
*affichage_nvx_plateau=0;
if (case_finale_joueur== -1)
  {
printf("\nVous ne pouvez pas recolter car vous etes arrivée sur le plateau de l'ordinateur. C'est a l'ordinateur de jouer !\n");
} else
  {
if( (ordi[case_finale_joueur]==2) || (ordi[case_finale_joueur]==3) )
  {
*affichage_nvx_plateau=1;
printf("\nVous pouvez recolter car la case sur laquelle vous etes arrivée contient 2 ou 3 graines.\n");
while( ( case_finale_joueur <= n ) && ( (ordi[case_finale_joueur]==2) || (ordi[case_finale_joueur]==3) ) )
  {
*grenier_joueur = *grenier_joueur + ordi[case_finale_joueur];
ordi[case_finale_joueur]=0;
case_finale_joueur++;
}
recolte = *grenier_joueur - recolte ;
printf("\nVous avez fini de recolter \n Vous avez recolte %d graines.	Voici le nouveau plateau.\n", recolte);
}
 else
   {
printf("\nVous ne pouvez pas recolter car il n'y a pas 2 ou 3 graines dans la case sur laquelle vous êtes arrivée.\n\n");
}
}

return *grenier_joueur;
}

int recolte_ordi_demo(int joueur[], int ordi[], int n, int *grenier_ordi, int case_finale_ordi, int *affichage_nvx_plateau)
{
*affichage_nvx_plateau=0 ;
int recolte = *grenier_ordi ;
if (case_finale_ordi==-1)
  {
printf("\nL'ordinateur ne peut pas recolter car la case sur laquelle il est arrivé ne contient as 2 ou 3 graines. C'est a vous de jouer !\n\n");
} else
  {
if(joueur[case_finale_ordi-1]==2||joueur[case_finale_ordi-1]==3)
  {
*affichage_nvx_plateau=1;
printf("\nL'ordinateur peut recolter car il y a 2 ou 3 graines sur la case sur laquelle il est arrvé.\n");
while( ( case_finale_ordi > 0 ) && ( (joueur[case_finale_ordi-1]==2) || (joueur[case_finale_ordi-1]==3) ) )
  {
*grenier_ordi = *grenier_ordi + joueur[case_finale_ordi-1];
 joueur[case_finale_ordi-1]=0;
 case_finale_ordi--;
  }
 recolte = *grenier_ordi - recolte ;
 printf("\nL'ordinateur a fini de recolter. \nIl a recolte %d graines. Voici le nouveau plateau\n.", recolte);
  }
 else
   {
     printf("\nIl ne peut pas recolter car il n'y a pas 2 ou 3 graines sur sa case d'arrivee.\n");
   }
  }
 return *grenier_ordi;
}

void jeu_demo(int joueur[], int ordi[], int n, int *grenier_joueur, int *grenier_ordi, int compteur, int *affichage_nvx_plateau)
{
  int case_finale_joueur;
  int case_finale_ordi ;

  if (compteur%2==0)
    {
      case_finale_joueur=changement_plateau_joueur(joueur, ordi,n);
      printf("\n\nORDI \n");
      afficher(ordi,N,grenier_ordi);
      printf("\n");
      printf("JOUEUR \n");
      afficher(joueur,N,grenier_joueur);
      printf("\n");
      *grenier_joueur=recolte_joueur_demo(joueur,ordi,n,grenier_joueur,case_finale_joueur,affichage_nvx_plateau);
      if ( *affichage_nvx_plateau==1)
	{
	 
	  printf("\nNouveau plateau\n");
	  printf("\n\nORDI \n");
	  afficher(ordi,N,grenier_ordi);
	  printf("\n");
	  printf("JOUEUR \n");
	  afficher(joueur,N,grenier_joueur);
	  printf("\n");
	  
	}
    } else
    {
      case_finale_ordi=changement_plateau_ordi(joueur, ordi,n);
      printf("\nORDI \n");
      afficher(ordi,N,grenier_ordi);
      printf("\n");
      printf("JOUEUR \n");
      afficher(joueur,N,grenier_joueur);
      printf("\n");
      *grenier_ordi=recolte_ordi_demo(joueur,ordi,n,grenier_ordi,case_finale_ordi,affichage_nvx_plateau);
      if ( *affichage_nvx_plateau==1)
	{
	 
	  printf("\nNouveau plateau\n");
	  printf("\n\nORDI \n");
	  afficher(ordi,N,grenier_ordi);
	  printf("\n");
	  printf("JOUEUR \n");
	  afficher(joueur,N,grenier_joueur);
	  printf("\n");

	}

    }
}

int graines_joueur(int joueur[], int n)
{
  int i;
  int graines_j=0;

  for(i=0;i<n;i++)
    {
      graines_j=graines_j+joueur[i];
    }
  return graines_j;
}

int graines_ordi(int ordi[], int n)
{
  int i;
  int graines_o=0;

  for(i=0;i<n;i++)
    {
      graines_o=graines_o+ordi[i];
    }
  return graines_o;
}

int fin_jeu(int joueur[], int ordi[], int n, int *grenier_joueur, int *grenier_ordi, int compteur,int nb_coups)
{
  int graines_j=graines_joueur(joueur,n);
  int graines_o=graines_ordi(ordi,n);
  int graines_plateau=graines_j+graines_o;

  if(compteur>nb_coups)
    {
      return -1;
    } else
    {
      if (*grenier_ordi>25)
	{
	  return -2;
	} else
	{
	  if (*grenier_joueur>25)
	    {
	      return -3;
	    } else
	    {
	      if (graines_plateau<6)
		{
		  return -4;
		}
	      else
		{
		  if(graines_j==0)
		    {
		      return -5;
		    } else
		    {
		      if(graines_o==0)
			{
			  return -6;
			} else
			{
			  return 1;
			}
		    }
		}
	    }
	}
    }
}


int main()
{
  int joueur[N];
  int ordi[N];
  int case_joueur;
  int a;
  int case_ordi;
  int grenier_joueur=0;
  int grenier_ordi=0;
  int compteur =0 ;
  int fj=1;
  int nb_coups ;
  int rejouer=1;
  int affichage_nvx_plateau;
  int menu;

  system("clear");
  printf ("\n\t\t\tBienvenue dans le jeu Awale !\n") ;
  printf("\nMENU\n");
  printf("\n| Tapez 1 | Lire les règles  \n");
  printf("| Tapez 2 | Voir une demonsration  \n");
  printf("| Tapez 3 | Jouer  \n");
  printf("| Tapez 4 | Quitter  \n");

  printf("\nChoix : ");
  scanf("%d",&menu);

  //REMPLIT TABLEAUX
  remplir(joueur,N);
  remplir(ordi,N);

  if(menu==1){
  	//AFFICHAGE REGLE DU JEU
    printf("\nVoici les regles du jeu :\n\nJOUEUR ET MATERIEL :\nVous jouez contre l'ordinateur.\nLe plateau de jeu se decompose en deux parties de 6 cases chacun.\n\nINITIALISATION:\nAu depart, il y a 4 graines dans chaque case, le but du jeu est de semer puis recolter le maximum de graines.Des que l'un des joueurs en recolte 25 ou plus, il a gagne.\n\nSEMER : \nPour cela, a tour de role, vous choisissez une case de votre plateau et distribuez les graines une par une dans les cases suivantes, dans le sens anti-horaire.\n\nRECOLTER : \nC'est toujours la derniere graine semee qui permet de recolter. Deux conditions doivent etre remplies : \n\t* La derniere graine semee doit etre semee chez l'adversaire.\n\t* Une fois la graine deposee, la case doit contenir exactement 2 ou 3 graines.\nSi la case precedente est toujours chez l'adversaire et contient egalement 2 ou 3 graines, la case est recoltee et ainsi de suite...\nSi un joueur a plus de 12 graines a deposer, il fait le tour du plateau en sautant la case de provenance des graines.\n\nFIN :\nLa partie se termine si : \n\t* L'un des joueurs a recole au moins 25 graines. \n\t* L'un des joueurs n'a plus de graines sur son plateau. \n\t* Il reste moins de 6 graines sur le plateau. \n\t* Le maximum de coups a jouer est atteint. \n\nGAGNANT :\nCelui qui a le grenier le plus rempli ! \n");

    printf("\n| Tapez 2 | Voir une demonsration  \n");
    printf("| Tapez 3 | Jouer  \n");
    printf("| Tapez 4 | Quitter  \n");

    printf("\nChoix : ");
    scanf("%d",&menu);

    // DEMONSTRATION
    if(menu==2){
      system("clear");
      printf("\nDEMONSTRATION");
      printf("\nVoici une petite demonstration qui vous permettra de vous familiariser un peu plus avec le jeu. \n Ceci est le plateau initial : \n");
      printf("\n\nORDI \n");
      afficher(ordi,N,&grenier_ordi);
      printf("\n");
      printf("JOUEUR \n");
      afficher(joueur,N,&grenier_joueur);
      printf("\n\n");

      nb_coups=6;

      while (fj == 1)
	{
	  //Le tour commence
	  jeu_demo (joueur, ordi, N, &grenier_joueur, &grenier_ordi, compteur, &affichage_nvx_plateau);
	  compteur++;

	  fj =fin_jeu(joueur,ordi,N,&grenier_joueur, &grenier_ordi, compteur,nb_coups);
	  if (fj<0)
	    {
	      printf ("La partie est finie.\n") ;
	      if (fj == -1)
		{
		  printf ("Le nombre de coup maximal est atteint.\n");
		  if(grenier_joueur>grenier_ordi)
		    {
		      printf("Vous avez gagne ! Felicitation !\n");
		    } else
		    {
		      if(grenier_joueur<grenier_ordi)
			{
			  printf("Vous avez perdu...\n");
			} else
			{
			  printf("Vous etes a egalite ! :s\n");
			}
		    }
		}
	    }
	}

      printf("\n| Tapez 3 | Jouer  \n");
      printf("| Tapez 4 | Quitter  \n");

      printf("\nChoix : ");
      scanf("%d",&menu);

      if(menu==3){
	system("clear");
	printf("La partie commence !\n");
      }
      else
	{
	  if(menu==4)
	    {
	      return 0;
	    }
	}
    }
    else {
      if(menu==3)
	{
	  system("clear");
	  printf("La partie commence !\n");
	}
      else
	{
	  if(menu==4)
	    {
	      return 0;
	    }
	}
    }
  }
  else
  {
    if (menu==2){
      system("clear");
      printf("\nDEMONSTRATION\n");
      printf("\nVoici une petite demonstration qui vous permettra de vous familiariser un peu plus avec le jeu. \nCeci est le plateau initial : \n");
      printf("\n\nORDI \n");
      afficher(ordi,N,&grenier_ordi);
      printf("\n");
      printf("JOUEUR \n");
      afficher(joueur,N,&grenier_joueur);
      printf("\n\n");

      nb_coups=6;

      while (fj == 1)
	{
	  //Le tour commence

	  jeu_demo (joueur, ordi, N, &grenier_joueur, &grenier_ordi, compteur, &affichage_nvx_plateau);
	  compteur++;


	  fj =fin_jeu(joueur,ordi,N,&grenier_joueur, &grenier_ordi, compteur,nb_coups);
	  if (fj<0)
	    {
	      printf ("\nLa partie est finie.\n") ;
	      if (fj == -1)
		{
		  printf ("\nLe nombre de coup maximal est atteint.\n");
		  if(grenier_joueur>grenier_ordi)
		    {
		      printf("\nVous avez gagne ! Felicitation !\n");
		    } else
		    {
		      if(grenier_joueur<grenier_ordi)
			{
			  printf("\nVous avez perdu...\n");
			} else
			{
			  printf("\nVous etes a egalite ! :s\n");
			}
		    }
		}
	    }
	}

      printf("\n| Tapez 3 | Jouer  \n");
      printf("| Tapez 4 | Quitter  \n");

      printf("\nChoix : ");
      scanf("%d",&menu);

      if(menu==3){
	system("clear");
	printf("La partie commence !\n");
      }
      else
	{
	  if(menu==4)
	    {
	      return 0;
	    }

    }
      }
      else {
      if (menu==3)
        {
            system("clear");
            printf("La partie commence !\n");
        }
        else
	  {
	    if(menu==4)
	      {
		return 0;
	      }
	    else {
	      printf("Merci de saisir un chiffre entre 1 et 4.");
	    }
	  }
      }
  }





    
	
  //On reinitialise les variables a leurs valeurs de depart
    grenier_joueur=0;
    grenier_ordi=0;
    fj=1;
    rejouer=1;

    
    //Le joueur choisit en compbien de coups il souhaite faire une partie

    while(rejouer==1){

	printf ("\nEn combien de coups voulez-vous jouer la partie ? ") ;
	scanf ("%d", &nb_coups); 

	//Le joueur choisit qui commence 
	printf ("\nVoulez-vous commencer ? Si oui tapez 0, sinon tapez 1.\n");
	scanf("%d", &compteur);
	if (compteur==0)
	{
        printf ("\nC'est a vous de jouer !\n");
	}
	else
	{
        printf ("\nC'est a l'ordinateur de jouer !\n");
	}


	//Initialisation et affichage du plateau de jeu
	remplir(joueur,N);
	remplir(ordi,N);

	printf("\n");
	printf("ORDI \n");
	afficher(ordi,N,&grenier_ordi);
	printf("\n");
	printf("JOUEUR \n");
	afficher(joueur,N,&grenier_joueur);
	printf("\n\n");

	while (fj == 1)
	  {
	    //Le tour commence
	    jeu (joueur, ordi, N, &grenier_joueur, &grenier_ordi, compteur, &affichage_nvx_plateau);
	    compteur++;

	    fj =fin_jeu(joueur,ordi,N,&grenier_joueur, &grenier_ordi, compteur,nb_coups);
	    if (fj<0)
	      {
		printf ("\nLa partie est finie.\n") ;
		if (fj == -1)
		  {
		    printf ("\nLe nombre de coup maximal est atteint.\n");
		    if(grenier_joueur>grenier_ordi)
		      {
			printf("\nVous avez gagne ! Felicitation !\n");
		      } else
		      {
			if(grenier_joueur<grenier_ordi)
			  {
			    printf("\nVous avez perdu...\n");
			  } else
			  {
			    printf("\nVous etes a egalite ! :s\n");
			  }
		      }
		  }
		else
		  {
		    if(fj == -2)
		      {
			printf ("\nLe grenier de l'ordinateur a atteint 25 ! Vous avez perdu.\n");
		      }
		    else
		      {
			if (fj == -3)
			  {
			    printf ("\nVotre grenier a atteint 25 ! Vous avez gagne ! Voulez-vous rejouer ?\n");
			  }
			else
			  {
			    if (fj==-4)
			      {
				printf ("\nIl y a moins de 6 graines sur le plateau !\n");
				if(grenier_joueur>grenier_ordi)
				  {
				    printf("\nVous avez gagne ! Felicitation !\n");
				  } else
				  {
				    if(grenier_joueur<grenier_ordi)
				      {
					printf("\nVous avez perdu...\n");
				      } else
				      {
					printf("\nVous etes a egalite ! :s\n");
				      }
				  }
			      }
			    else
			      {
				if (fj==-5)
				  {
				    printf ("\nLe nombre de graines sur le plateau du joueur est nul.\n");
				    if(grenier_joueur>grenier_ordi)
				      {
					printf("\nVous avez gagne ! Felicitation !\n");
				      }
				    else
				      {
					if(grenier_joueur<grenier_ordi)
					  {
					    printf("\nVous avez perdu...\n");
					  }
					else
					  {
					    printf("\nVous etes a egalite ! :s\n");
					  }

					if (fj==-6)
					  {
					    printf ("\nLe nombre de graines sur le plateau de l'ordi est nul.\n");
					    if(grenier_joueur>grenier_ordi)
					      {
						printf("\nVous avez gagne ! Felicitation !\n");
					      } else
					      {
						if(grenier_joueur<grenier_ordi)
						  {
						    printf("\nVous avez perdu...\n");
						  }
						else
						  {
						    printf("\nVous etes a egalite ! :s\n");
						  }
					      }
					  }
				      }
				  }
			      }
			  }
		      }
		  }
	      }
	  }

	printf("\nVoulez-vous rejouer ? Si oui tapez 1 sinon tapez 0.\n");
	scanf("%d",&rejouer);
	fj = 1 ;
	grenier_joueur=0;
	grenier_ordi=0;
	compteur=0;
      }

      return 0;
    }
