#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 6

//Bibliothèque des fonctions
void afficher (int T[], int n, int g);
void remplir(int T[], int n);
int choix_joueur(int T[], int n);
int rand_a_b(int a, int b);
int choix_ordi(int T[], int n);
int changement_plateau_joueur (int joueur[], int ordi[], int n);
int changement_plateau_ordi (int joueur[], int ordi[], int n);
int recolte_joueur(int joueur[], int ordi[], int n, int grenier_joueur, int case_finale_joueur);
int recolte_ordi(int joueur[], int ordi[], int n, int grenier_ordi, int case_finale_ordi);
void jeu(int joueur[], int ordi[], int n, int grenier_ordi, int grenier_joueur, int compteur);
int graines_joueur(int joueur[], int n);
int graines_ordi(int joueur[], int n);
int fin_jeu(int joueur[], int ordi[], int n, int grenier_joueur, int grenier_ordi, int compteur,int nb_coups);


//INITIALISATION
void afficher (int T[], int n, int g)
{
  int i ;
  for (i=0 ; i<n ; i++)
  {
    printf ("| %d |\t", T[i]);
  }
  printf("\tGrenier : %d",g);
}

void remplir(int T[], int n)
{
  int i;
  for(i=0 ; i<n ; i++)
  {
    T[i]=4;
  }
}

//SEMER

int choix_joueur(int T[], int n)
{
  int i;
  printf("C'est a vous de jouer !\nChoisissez une case :");
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

  while(T[nb_alea]==0)
  {
    nb_alea=rand_a_b(1,6);
  }

  return nb_alea;
}

int changement_plateau_joueur (int joueur[], int ordi[], int n)
{
  int graines;
  int case_joueur=choix_joueur(joueur,n);
  int i=n-1;
  
  graines=joueur[case_joueur-1];
  joueur[case_joueur-1]=0;

  while(graines!=0)
  {
      //tableau joueur
    while((case_joueur<n)&&(graines!=0))
    {
     joueur[case_joueur]=joueur[case_joueur]+1;
     graines--;
     case_joueur++;
   }
   if(graines==0)
   {
    printf ("Vous n'avez plus graine et vous etes sur votre plateau. \n");
    return -1;
  }
  else
  {
	  //tableau ordi
   while((i>0)&&(graines!=0))
   {
     ordi[i]=ordi[i]+1;
     graines--;
     i--;
   }
   if(graines==0)
   {
     return i+2;
   }
   
   else
   {
     i=n;
     case_joueur=0;
   }
 }
}
}

int changement_plateau_ordi (int joueur[], int ordi[], int n)
{
  int graines;
  int case_ordi=choix_ordi(ordi,n);
  int i=0;
  printf("Case ordi : %d\n",case_ordi);
  case_ordi=case_ordi-1;
  graines=ordi[case_ordi];
  ordi[case_ordi]=0;
  case_ordi=case_ordi-1;

  while(graines!=0)
  {
      //tableau ordi
    while((case_ordi>=0)&&(graines!=0))
    {
     ordi[case_ordi]=ordi[case_ordi]+1;
     graines--;
     case_ordi--;
   }
   if(graines==0)
   {
    
     return -1;
   }
   else
   {
	  //tableau joueur
     while((i<n)&&(graines!=0))
     {
       joueur[i]=joueur[i]+1;
       graines--;
       i++;
     }
     if(graines==0)
     {
       
       return i;
     }
     else
     {
       i=0;
       case_ordi=n-1;
     } 
   }
 } 
}

int recolte_joueur(int joueur[], int ordi[], int n, int grenier_joueur, int case_finale_joueur)
{
  int recolte = grenier_joueur ;
  if (case_finale_joueur== -1)
  {
    printf("Vous ne pouvez pas recolter. C'est a l'ordinateur de jouer !");
  } else
  {
    
    if( (ordi[case_finale_joueur-1]==2) || (ordi[case_finale_joueur-1]==3) )
    {
      printf("Vous pouvez recolter \n");
      while( ( case_finale_joueur-1 < n ) && ( (ordi[case_finale_joueur-1]==2) || (ordi[case_finale_joueur-1]==3) ) )
      {
        grenier_joueur = grenier_joueur + ordi[case_finale_joueur-1];
        ordi[case_finale_joueur-1]=0;
        case_finale_joueur++;
      }
      recolte = grenier_joueur - recolte ;
      printf("Vous avez fini de recolter \n Vous avez recolte %d graines, voici le nouveau plateau\n", recolte);
    }
    else 
    {
      printf("Vous ne pouvez pas recolter car il n'y a pas 2 ou 3 graines \n");
    }
  }
  return grenier_joueur;
}

int recolte_ordi(int joueur[], int ordi[], int n, int grenier_ordi, int case_finale_ordi)
{
  int recolte = grenier_ordi ;
  if (case_finale_ordi==-1)
  {
    printf("L'ordinateur ne peut pas recolter. C'est a vous de jouer!");
  } else
  {
    
    if(joueur[case_finale_ordi-1]==2||joueur[case_finale_ordi-1]==3)
    { 
      printf("Vous pouvez recolter \n");
      while( ( case_finale_ordi-1 < n ) && ( (joueur[case_finale_ordi-1]==2) || (ordi[case_finale_ordi-1]==3) ) )
      {
        grenier_ordi = grenier_ordi + joueur[case_finale_ordi-1];
        joueur[case_finale_ordi-1]=0;
        case_finale_ordi--;
      }
      recolte = grenier_ordi - recolte ;
      printf("L'ordinateur a fini de recolter \nIl a recolte %d graines, voici le nouveau plateau\n", recolte);
    }
    else 
    {
      printf("Il ne peut pas recolter car il n'y a pas 2 ou 3 graines \n");
    }
  }
  return grenier_ordi;
}

void jeu(int joueur[], int ordi[], int n, int grenier_joueur, int grenier_ordi, int compteur)
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
  
  grenier_joueur=recolte_joueur(joueur,ordi,n,grenier_joueur,case_finale_joueur);
} else
{
  case_finale_ordi=changement_plateau_ordi(joueur, ordi,n);
  printf("\nORDI \n");
  afficher(ordi,N,grenier_ordi);
  printf("\n");
  printf("JOUEUR \n");
  afficher(joueur,N,grenier_joueur);
  printf("\n");
  grenier_ordi=recolte_ordi(joueur,ordi,n,grenier_ordi,case_finale_ordi);
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

int fin_jeu(int joueur[], int ordi[], int n, int grenier_joueur, int grenier_ordi, int compteur,int nb_coups)
{
  int graines_j=graines_joueur(joueur,n);
  int graines_o=graines_ordi(ordi,n);
  int graines_plateau=graines_j+graines_o;

  if(compteur>nb_coups)
  {
    return -1;
  } else
  {
    if (grenier_ordi>25) 
    {
      return -2;
    } else
    {
      if (grenier_joueur>25)
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
  int a, p;
  int case_ordi;
  int grenier_joueur=0;
  int grenier_ordi=0;
  int compteur =0 ;
  int fj=1;
  int nb_coups ;
  int rejouer=1;

    /*Le joueur choisit qui commence
    printf ("Voulez-vous commencer ? Si oui tapez 0, sinon tapez 1 \n");
    scanf("%d", &p);
    if (p==0)
    {
      printf ("C'est a vous de jouer !  \n");
    }
  else
    {
      printf ("C'est a l'ordinateur de jouer !  \n");
    }*/

    //Le joueur choisit en compbien de coups il souhaite faire une partie 
  while(rejouer==1){

    printf ("En combien de coups voulez-vous jouer la partie ?") ;
    scanf ("%d", &nb_coups);
    
    //Initialisation et affichage du plateau de jeu
    remplir(joueur,N);
    remplir(ordi,N);
    
      printf("\n");
      printf("ORDI \n");
      afficher(ordi,N,grenier_ordi);
      printf("\n");
      printf("JOUEUR \n");
      afficher(joueur,N,grenier_joueur);
      printf("\n\n");
      while (fj == 1)
    {
   //Le tour commence
      jeu (joueur, ordi, N, grenier_joueur, grenier_ordi, compteur);

      
      
      compteur++;
      
      fj =fin_jeu(joueur,ordi,N,grenier_joueur, grenier_ordi, compteur,nb_coups);
      if (fj<0)
      {
        printf ("Le jeu est fini mon ami ! \n") ;
        if (fj == -1)
        {
          printf ("Le nombre de coup maximal est atteint ! \n");
        }
        else 
        {
          if(fj == -2)
          {
            printf ("Le grenier de l'ordinateur a atteint 25 ! Il a gagné :) Veux-tu rejouer ?");
          }
          else 
          {
            if (fj == -3)
            {
              printf ("Ton grenier a atteint 25 ! Tu as gagné :) Veux-tu rejouer ?");
            }
            else 
            {
              if (fj==-4)
              {
                printf ("Il y a moins de 6 graines sur le plateau, vous êtes tous les deux nuls");
              }
              else 
              {
                if (fj==-5)
                {
                  printf ("Le nombre de graines sur le plateau du joueur est nul \n");
                } else
                {
                  if (fj==-6)
                  {
                    printf ("Le nombre de graines sur le plateau de l'ordi est nul \n");
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  
  return 0;
}


