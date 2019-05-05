#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 6


//Bibliothèque des fonctions
void afficher (int T[], int n, int *g);
void remplir(int T[], int n);
int choix_joueur(int T[], int n);
int rand_a_b(int a, int b);
int choix_ordi(int joueur[], int ordi[], int n, int niveau);
int changement_plateau_joueur (int joueur[], int ordi[], int n);
int changement_plateau_ordi (int joueur[], int ordi[], int n, int niveau);
int recolte_joueur(int joueur[], int ordi[], int n, int *grenier_joueur, int case_finale_joueur, int *affichage_nvx_plateau);
int recolte_ordi(int joueur[], int ordi[], int n, int *grenier_ordi, int case_finale_ordi, int *affichage_nvx_plateau);
void jeu(int joueur[], int ordi[], int n, int *grenier_ordi, int *grenier_joueur, int compteur, int *affichage_nvx_plateau,int niveau);
int recolte_joueur_demo(int joueur[], int ordi[], int n, int *grenier_joueur, int case_finale_joueur, int *affichage_nvx_plateau);
int recolte_ordi_demo(int joueur[], int ordi[], int n, int *grenier_ordi, int case_finale_ordi, int *affichage_nvx_plateau);
int graines_joueur(int joueur[], int n);
int graines_ordi(int joueur[], int n);
int fin_jeu(int joueur[], int ordi[], int n, int *grenier_joueur, int *grenier_ordi, int compteur,int nb_coups);
void jeu_demo(int joueur[], int ordi[], int n, int *grenier_joueur, int *grenier_ordi, int compteur, int *affichage_nvx_plateau);
int max_tab (int tableau[], int taille_tab);
int niveau1 (int joueur[], int ordi[], int taille_tab);
void semer_niveau2 (int joueur[], int ordi[], int n,int indice);
int max_matrice(int matrice[][N], int taille_tab);
int niveau2(int joueur[], int ordi[], int taille_tab);

//****************************INITIALISATION :**********************************

//Permet d'afficher le tableau et le grenier
void afficher (int T[], int n, int *g)
{
	int i ;
	for (i=0 ; i<n ; i++)
  	{
		printf ("| %d |\t", T[i]);
	}
	printf("\tGrenier : %d",*g);
	}

//On initialise le tableau avec 4 graines dans chaque case
void remplir(int T[], int n)
{
	for(int i=0 ; i<n ; i++)
  	{
		T[i]=4;
	}
}

//************************************SEMER***************************************

//Permet de faire choisir au joueur sa case
int choix_joueur(int T[], int n)
{
	int i;
	printf("Choisissez une case (attention ce doit être un chiffre entre 1 et 6) : ");
	scanf("%d",&i);

	while((i>6)||(i<1))
  	{	
		printf("Veuillez choisir une case entre 1 et 6.\nCase choisie : ");
		scanf("%d",&i);
	}

	while(T[i-1]==0)
  	{
		printf("La case que vous avez choisie est vide. Veuillez choisir une case contenant des graines.\nCase choisie : ");
		scanf("%d",&i);
	}
	system("clear");
	return i;
	//Retourne la case choisie par le joueur
}


//Fonction permettant de choisir un nombre aléatoirement compris dans l'intervalle [1;6] (utilisé pour le niveau 0)
int rand_a_b(int a, int b)
{
	return rand()%(b-a+1)+a;
}


//Choisi la case de l'ordinateur en fonction du niveau
int choix_ordi(int joueur[], int ordi[], int n, int niveau)
{
	int case_choisie;

	switch (niveau) {
		case 0: 
			srand(time(NULL));
			case_choisie = rand_a_b(1,6);

			while(ordi[case_choisie-1]==0) {
				case_choisie=rand_a_b(1,6);
			}
		break;
		case 1:
			case_choisie = niveau1(joueur, ordi,n)+1;
		break;
		case 2:
			case_choisie = niveau2(joueur,ordi,n)+1;
		break;
		default:
		case_choisie=2;
	}
return case_choisie;
//Retourne la case de l'ordinateur en fonction du niveau choisi par le joueur
}


//Permet de mettre à jour le plateau après avoir semé quand c'est le tour du joueur
int changement_plateau_joueur (int joueur[], int ordi[], int n)
{
	int graines=joueur[case_joueur-1];
	int case_joueur=choix_joueur(joueur,n); // [1,6]
	int case_depart=case_joueur-1; //[0,5]
	joueur[case_joueur-1]=0;

	while(graines!=0)
 	{
		//Remplissage tableau joueur
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
		} else
 			{
				//Remplissage tableau ordi
				while((case_joueur>0)&&(graines!=0))
  				{
					ordi[case_joueur-1]=ordi[case_joueur-1]+1;
					graines--;
					case_joueur--;
				}
				if(graines==0)
  				{
					return case_joueur++;
					//Retourne la case d'arrivee chez l'ordinateur
				}
			}
	}
}


//Permet de mettre à jour le plateau après avoir semé quand c'est le tour de l'ordinateur
int changement_plateau_ordi (int joueur[], int ordi[], int n, int niveau)
{
	int graines;
	int case_ordi=choix_ordi(joueur,ordi,n, niveau); // [1,6]
	int case_depart=case_ordi-1; //[0,5]


	printf("Case ordi : %d\n",case_ordi);
	case_ordi=case_ordi-1;
	graines=ordi[case_ordi];
	ordi[case_ordi]=0;


	while(graines!=0)
  	{
		//Remplissage tableau ordi
		// case_ordi [0,5]
		while((case_ordi>=0)&&(graines!=0))
  		{
			if(case_ordi==case_depart)
			{
				case_ordi--;
			} else
  				{
					ordi[case_ordi]=ordi[case_ordi]+1;
					graines--;
					case_ordi--;
				}
		}
		if(graines==0)
	  	{
			return -1;
		} else // graines != 0 && case_ordi = -1
	   		{
	   			case_ordi++; // case_ordi = 0
	   			//Remplissage tableau joueur
				while((case_ordi<n)&&(graines!=0)) // n = 6 case_ordi [0,5]
	  			{
					joueur[case_ordi]=joueur[case_ordi]+1;
					graines--;
					case_ordi++;
				}
			// case_ordi = 6 OU graines = 0
				if(graines==0)
	  			{
					return case_ordi;
					//Retourne la case d'arrivee chez le joueur
				} else
					{
						case_ordi--;
					}
			}
	}
}


//***********************************RECOLTE*************************************

//Permet de recolter les graines chez l'adversaire
int recolte_joueur(int joueur[], int ordi[], int n, int *grenier_joueur, int case_finale_joueur, int *affichage_nvx_plateau)
{
	int recolte = *grenier_joueur ;
	*affichage_nvx_plateau=0; //Permet d'afficher le nouveau plateau s'il y a recolte

	if (case_finale_joueur== -1) //Le joueur ne peut pas recolter car son nombre de graines ne lui permet pas de finir chez l'adversaire
  	{
		printf("\nC'est a l'ordinateur de jouer !\n\n");
	} else
  		{
			if( (ordi[case_finale_joueur]==2) || (ordi[case_finale_joueur]==3) )
  			{
  				*affichage_nvx_plateau=1;
				printf("\nVous pouvez recolter.\n");
				while( ( case_finale_joueur <= n ) && ( (ordi[case_finale_joueur]==2) || (ordi[case_finale_joueur]==3) ) )//Recolte tant que la case precedente contient 2 ou 3 graines
				{
					*grenier_joueur = *grenier_joueur + ordi[case_finale_joueur];
					ordi[case_finale_joueur]=0; //Apres recolte, on met la case a 0
					case_finale_joueur++;
				}
				recolte = *grenier_joueur - recolte ;
				printf(" \nVous avez fini de recolter. \n Vous avez recolte %d graines, voici le nouveau plateau.\n", recolte);
			} else
   				{
					printf("\nVous ne pouvez pas recolter car il n'y a pas 2 ou 3 graines. \n\n");
				}
		}
	return *grenier_joueur;
	//Retourne le grenier mis a jour
}


//Permet de recolter les graines chez l'adversaire
int recolte_ordi(int joueur[], int ordi[], int n, int *grenier_ordi, int case_finale_ordi, int *affichage_nvx_plateau)
{
	int recolte = *grenier_ordi ;
	*affichage_nvx_plateau=0 ; //Permet d'afficher le nouveau plateau s'il y a recolte
	
	if (case_finale_ordi==-1) //L'ordinateur ne peut pas recolter car son nombre de graines ne lui permet pas de finir chez l'adversaire
  	{
		printf("C'est a vous de jouer! \n");
	} else
  		{
			if(joueur[case_finale_ordi-1]==2||joueur[case_finale_ordi-1]==3)
  			{
				*affichage_nvx_plateau=1;
				printf("L'ordinateur peut recolter.\n");
				while( ( case_finale_ordi > 0 ) && ( (joueur[case_finale_ordi-1]==2) || (joueur[case_finale_ordi-1]==3) ) ) //Recolte tant que la case precedente contient 2 ou 3 graines
  				{
					*grenier_ordi = *grenier_ordi + joueur[case_finale_ordi-1];
 					joueur[case_finale_ordi-1]=0; //Apres recolte, on met la case a 0
 					case_finale_ordi--;
  				}
 				recolte = *grenier_ordi - recolte ;
 				printf("Voici le nouveau plateau.\n");
  			} else 
  				{
     				printf("\nIl ne peut pas recolter car il n'y a pas 2 ou 3 graines.\n\n");
  				}
  		}
 	return *grenier_ordi;
 	//Retourne le grenier mis a jour
}


//Lance le jeu : permet de faire jouer l'ordinateur ou l'utilisateur et qui correspond à un coup de la partie (choisir une case, semer - modifier plateau, recolte si possible-modifier plateau)
void jeu(int joueur[], int ordi[], int n, int *grenier_joueur, int *grenier_ordi, int compteur, int *affichage_nvx_plateau, int niveau)
{
	int case_finale_joueur;
	int case_finale_ordi ;

	if (compteur%2!=0) //Permet de savoir si c'est le tour du joueur : si c'est impair c'est au tour du joueur, si c'est pair c'est à l'ordinateur
    {
    	printf("\n\n\t\t|        JOUEUR        |\n\n");
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
	 		printf("\n\nORDI \n");
	 		afficher(ordi,N,grenier_ordi);
	 	 	printf("\n");
	 	 	printf("JOUEUR \n");
	 	 	afficher(joueur,N,grenier_joueur);
	 	 	printf("\n");
	 	}
    } else 
   		{
      		printf("\n\n\t\t|      ORDINATEUR      |\n\n");
      		case_finale_ordi=changement_plateau_ordi(joueur, ordi,n,niveau);
      		printf("\nORDI \n");
      		afficher(ordi,N,grenier_ordi);
      		printf("\n");
      		printf("JOUEUR \n");
      		afficher(joueur,N,grenier_joueur);
      		printf("\n");
      		*grenier_ordi=recolte_ordi(joueur,ordi,n,grenier_ordi,case_finale_ordi,affichage_nvx_plateau);
      		if ( *affichage_nvx_plateau==1)
			{
	  			printf("\n\nORDI \n");
	  			afficher(ordi,N,grenier_ordi);
	  			printf("\n");
	  			printf("JOUEUR \n");
	  			afficher(joueur,N,grenier_joueur);
	  			printf("\n");
			}
		}
}


//************************************DEMONSTRATION***************************************

//Permet de recolter les graines chez l'adversaire et d'expliquer comment se deroule la recolte au joueur
int recolte_joueur_demo(int joueur[], int ordi[], int n, int *grenier_joueur, int case_finale_joueur, int *affichage_nvx_plateau)
{
	int recolte = *grenier_joueur ;
	*affichage_nvx_plateau=0;

	if (case_finale_joueur== -1)
	{
		printf("\nVous ne pouvez pas recolter car vous etes arrive sur le plateau de l'ordinateur. C'est a l'ordinateur de jouer !\n");
	} else
  		{
			if( (ordi[case_finale_joueur]==2) || (ordi[case_finale_joueur]==3) )
  			{
				*affichage_nvx_plateau=1;
				printf("\nVous pouvez recolter car la case sur laquelle vous etes arrive contient 2 ou 3 graines.\n");
				while( ( case_finale_joueur <= n ) && ( (ordi[case_finale_joueur]==2) || (ordi[case_finale_joueur]==3) ) )
  				{
					*grenier_joueur = *grenier_joueur + ordi[case_finale_joueur];
					ordi[case_finale_joueur]=0;
					case_finale_joueur++;
				}
				recolte = *grenier_joueur - recolte ;
				printf("\nVous avez fini de recolter \n Vous avez recolte %d graines. Voici le nouveau plateau.\n", recolte);
			} else
   				{
					printf("\nVous ne pouvez pas recolter car il n'y a pas 2 ou 3 graines dans la case sur laquelle vous êtes arrivée.\n\n");
				}
		}
	return *grenier_joueur;
}


//Permet de recolter les graines chez l'adversaire et d'expliquer comment se deroule la recolte au joueur
int recolte_ordi_demo(int joueur[], int ordi[], int n, int *grenier_ordi, int case_finale_ordi, int *affichage_nvx_plateau)
{
	*affichage_nvx_plateau=0 ;
	int recolte = *grenier_ordi ;

	if (case_finale_ordi==-1)
  	{
		printf("\nL'ordinateur ne peut pas recolter car la case sur laquelle il est arrivé ne contient pas 2 ou 3 graines. C'est a vous de jouer !\n\n");
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
  			} else
   				{
     				printf("\nIl ne peut pas recolter car il n'y a pas 2 ou 3 graines sur sa case d'arrivee.\n");
   				}
  		}
 	return *grenier_ordi;
}


//Permet d'expliquer au joueur le deroulement du jeu : permet de faire jouer l'ordinateur ou l'utilisateur et qui correspond à un coup de la partie (choisir une case, semer - modifier plateau, recolte si possible-modifier plateau)
void jeu_demo(int joueur[], int ordi[], int n, int *grenier_joueur, int *grenier_ordi, int compteur, int *affichage_nvx_plateau)
{
	int case_finale_joueur;
	int case_finale_ordi ;

	if (compteur%2!=0)
    {
    	printf("\n\n\t\t|        JOUEUR        |\n\n");
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
			printf("\n\nORDI \n");
			afficher(ordi,N,grenier_ordi);
	 		printf("\n");
	  		printf("JOUEUR \n");
	  		afficher(joueur,N,grenier_joueur);
	  		printf("\n");
		}
    } else
    	{
      		printf("\n\n\t\t|      ORDINATEUR      |\n\n");
      		case_finale_ordi=changement_plateau_ordi(joueur, ordi,n,0); //on met le niveau de la demo à 0 par defaut
      		printf("\nORDI \n");
      		afficher(ordi,N,grenier_ordi);
      		printf("\n");
      		printf("JOUEUR \n");
      		afficher(joueur,N,grenier_joueur);
      		printf("\n");
     		*grenier_ordi=recolte_ordi_demo(joueur,ordi,n,grenier_ordi,case_finale_ordi,affichage_nvx_plateau);
      		if ( *affichage_nvx_plateau==1)
			{
	  			printf("\n\nORDI \n");
	  			afficher(ordi,N,grenier_ordi);
	  			printf("\n");
	  			printf("JOUEUR \n");
	  			afficher(joueur,N,grenier_joueur);
	  			printf("\n");
			}
		}
}


//Mets a jour le grenier du joueur
int graines_joueur(int joueur[], int n)
{
  int i;
  int graines_j=0;

  for(i=0;i<n;i++)
    {
      graines_j=graines_j+joueur[i];
    }
  return graines_j;
  //Retourne le grenier mis a jour
}


//Mets a jour le grenier de l'ordinateur
int graines_ordi(int ordi[], int n)
{
  int i;
  int graines_o=0;

  for(i=0;i<n;i++)
    {
      graines_o=graines_o+ordi[i];
    }
  return graines_o;
  //Retourne le grenier mis a jour
}


//*******************************FIN DU JEU*********************************

//Permet de savoir pourquoi la partie se termine
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
						} else
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


//Renvoie pour le tableau donné l'indice de la plus grande valeur qu'il contient
int max_tab (int tableau[], int taille_tab)
{
	int reference = tableau[0]; //-1
	int indice_ref = 0;
	int i;

	for (i = 0; i < taille_tab; i++)
	{
		if (reference<tableau[i])
		{
			reference = tableau[i];
			indice_ref = i;
		}
	}
	return indice_ref; 
}

//
int niveau1 (int joueur[], int ordi[], int taille_tab)
{
	int tableau_gains[] = {-1,-1,-1,-1,-1,-1};
	int i,j;


	for(i=0; i<taille_tab ; i++)
	{
		//indice d'arrivée dans le tableau joueur
		j=ordi[i]-(i+1);
		// si le  nombre de graines me permet de passer dans le tableau joueur et qu'il y a 1 ou 2 graines (car le tableau n'est pas encore rempli)
		if(ordi[i]>i && ordi[i]!=0)
		// vaut 0 si il peut pas, 1 si il peut
		{
			tableau_gains[i]=0;
			while((j>0)&&(joueur[j]==1)||(joueur[j]==2)){
				tableau_gains[i]=tableau_gains[i]+joueur[j]+1;
				// on met +1 car quand on aura rempli le tableau il y aura une graine supplementaire
				j--;
			}
		}
	}
	return max_tab(tableau_gains,taille_tab);
}

void semer_niveau2 (int joueur[], int ordi[], int n,int indice)
{
	int case_ordi = indice ;
	int graines = ordi[case_ordi] ;
	int case_depart=case_ordi; //[0,5]

	ordi[case_ordi]=0;


	while(graines!=0)
	{
	//tableau ordi
	// case_ordi [0,5]
		while((case_ordi>=0)&&(graines!=0))
  		{
			if(case_ordi==case_depart) 
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
		if(graines!=0)
 		{
			case_ordi++; // case_ordi = 0
			//tableau joueur
			while((case_ordi<n)&&(graines!=0)) // n = 6 case_ordi [0,5]
 			{
				joueur[case_ordi]=joueur[case_ordi]+1;
				graines--;
				case_ordi++;
			}
			// case_ordi = 6 OU graines = 0
			if(graines!=0)
			{
				case_ordi--;
			}
		}
	}
}


//Renvoie l'indice de la case que devrait jouer l'ordinateur pour avoir le maximum de gain possible
int max_matrice(int matrice[][N], int taille_tab)
{
	int j,o,indice=0;
	int max=matrice[0][0];

	for(j=0;j<taille_tab;j++)
	{
		for(o=0;o<taille_tab;o++)
		{
			if(max<matrice[j][o])
			{
				max=matrice[j][o];
				indice=o;
			}
		}
	}
return indice;
}


//Renvoie l'indice de la case la plus rentable
int niveau2(int joueur[], int ordi[], int taille_tab)
{
	// o correspond a la case choisie par l'ordinateur
	// j correspond a la case choisie par le joueur
	int difference_gains[taille_tab][taille_tab];
	int o,j;
	int indice_j ; //Case d'arrivée sur le plateau de l'ordinateur après le coup du joueur
	int indice_o ; //Case d'arrivée sur le plateau du joueur après le coup de l'ordinateur
	int gain_ordi;
	int gain_joueur ;
	int ordi_bis[N],joueur_bis[N]; //copie les valeurs de nos tableaux car dans cette fonction on va les modifier et donc les perdre
	int k;

	for (k=0; k<N ; k++)
	{
		joueur_bis[k]=joueur[k];
		ordi_bis[k]=ordi[k];
	}

	for( j = 0 ; j < taille_tab ; j++ )
	 {
		for( o = 0 ; o < taille_tab ; o++ )
		{
			difference_gains[j][o]=-50 ; 
		}
	 }

    for(j=0; j<taille_tab ; j++)
    {
    	for (o=0; o<taille_tab;o++)
    	{

		for (k=0; k<N ; k++)
		{
			joueur[k]=joueur_bis[k];
			ordi[k]=ordi_bis[k];
		}

    		//Calcul du gain maximal de l'ordinateur 
    		//Indice d'arrivée dans le tableau joueur
		   indice_o = ordi[o]-(o+1);
		   //Si le nombre de graines me permet de passer dans le tableau joueur et qu'il y a 1 ou 2 graines (car le tableau n'est pas encore rempli)
		   if(ordi[o]>o && ordi[o]!=0)
		   //Vaut 0 si il peut pas, 1 si il peut
			{
        	   difference_gains[j][o]=0;
        	   //L'ordi seme
        	   semer_niveau2(joueur,ordi,taille_tab,indice_o);
        	   //L'ordi recolte
				while((indice_o>0)&&((joueur[indice_o]==2)||(joueur[indice_o]==3)))
				{
					difference_gains[j][o]=difference_gains[j][o]+joueur[indice_o];
					joueur[indice_o]=0;
					indice_o--;
		   		}

		   		printf("A semé et récolté pour la case %d\n", o);
		   	}
		   	//Le joueur joue et calcule de la difference de gains : gains_ordi-gains_joueur
    		//Indice d'arrivée dans le tableau ordi
		   indice_j =2*taille_tab-joueur[j]-(j+1);
		   //Si le  nombre de graines me permet de passer dans le tableau joueur et qu'il y a 1 ou 2 graines (car le tableau n'est pas encore rempli)
		   if(joueur[j]>(taille_tab-(j+1)) && joueur[j]!=0)
		   //Vaut 0 si il peut pas, 1 si il peut
			{
				while((indice_j>0)&&(ordi[indice_j]==1)||(ordi[indice_j]==2))
				{
					difference_gains[j][o]=difference_gains[j][o]-(ordi[indice_j]+1);
					// on met +1 car quand on aura rempli le tableau il y aura une graine supplementaire			
					indice_j--;
		   		}
		   	}
		}
	}

	for (k=0; k<N ; k++)
	{
		joueur[k]=joueur_bis[k];
		ordi[k]=ordi_bis[k];
	}

	for (int x = 0; x < 6; ++x) 
	{
		printf("{");
		for (int y = 0; y < 6; ++y)
		{
			printf("%d\t ", difference_gains[x][y] );
		}
		printf("}\n");
	}

	return max_matrice(difference_gains,taille_tab);
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
  char pause;
  int choix_niveau;

  system("clear");
  printf ("\n\t\t\t \033[1;34m Bienvenue dans le jeu Awale ! \033[1;34m \n") ;
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

  /*switch (menu) {
  	case 1:
  		reading_rules()
  	break;
  	case 2:
  		demo();
  	break;
  	case 3:
  	break
  	case 4:
  	break;
  	default:
  	//
  }*/

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

    
    //Le joueur choisit en combien de coups il souhaite faire une partie

    while(rejouer==1){

	printf ("\nEn combien de coups voulez-vous jouer la partie ?\nNombre de coups choisi : ") ;
	scanf ("%d", &nb_coups); 

	printf("\n\nQuel niveau voulez-vous ? Tapez 0,1 ou 2.\nNiveau choisi : ");
	scanf("%d",&choix_niveau);

	//Le joueur choisit qui commence 
	printf ("\n\nVoulez-vous commencer ? Si oui tapez 1, sinon tapez 0.\nChoix : \n");
	scanf("%d", &compteur);
	if (compteur==1)
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
	    jeu(joueur, ordi, N, &grenier_joueur, &grenier_ordi, compteur, &affichage_nvx_plateau, choix_niveau);
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
