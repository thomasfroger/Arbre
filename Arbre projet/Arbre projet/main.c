//  main.c
//  Arbre_Projet
//  Created by thomas froger

#include <stdio.h>
#include <stdlib.h>


// On commence par la structure
typedef struct Arbre
{
    int taille_arbre;
    int *tab;
} Arbre;

//Ensuite on créer les fonctions qui nous permetteront de faire les différentes taches demandées

void afficher(Arbre *mon_arbre)
{
    if (mon_arbre == NULL )
    {
        printf("\n");
    }
    else
    {
        int i;
        printf("Votre Arbre : [");
        for (i=0; i < mon_arbre->taille_arbre-1; i++)
            printf("%d , ",mon_arbre->tab[i]);

        printf("%d]\n\n",mon_arbre->tab[mon_arbre->taille_arbre-1]);
    }
}
// creation de fonction pour creer l'arbre
Arbre* Creer_arbre(int taille)
{
    Arbre* mon_arbre = (Arbre*) malloc(sizeof(Arbre));
    mon_arbre->tab = (int*) malloc(taille*sizeof(int));
    mon_arbre->taille_arbre = taille;
    return mon_arbre;
}

Arbre* ajouter(Arbre *mon_arbre, int valeur)
{
    mon_arbre->taille_arbre++;
    mon_arbre->tab = (int*) realloc(mon_arbre->tab, mon_arbre->taille_arbre * sizeof(int));
    mon_arbre->tab[mon_arbre->taille_arbre - 1] = valeur;
    int i = (mon_arbre->taille_arbre - 1);
    int temp;

    while (mon_arbre->tab[(i-((i%2 == 0) ? 2 : 1))/2] < mon_arbre->tab[i])
    {
        int i_parent = (i-((i%2 == 0) ? 2 : 1))/2;
        temp = mon_arbre->tab[i_parent];
        mon_arbre->tab[i_parent] = mon_arbre->tab[i];
        mon_arbre->tab[i] = temp;
        i = i_parent;
    }
    return mon_arbre;
}

Arbre* supprimer_racine(Arbre *mon_arbre)
{

    mon_arbre->tab[0] = mon_arbre->tab[mon_arbre->taille_arbre - 1];

    mon_arbre->taille_arbre --;
    mon_arbre->tab = (int*) realloc(mon_arbre->tab, mon_arbre->taille_arbre * sizeof(int));

    int i = 0;
    int temp = 0;

    // (droite existe et droite > parent) ou (gauche existe et gauche > parent)
    while ((2*i+1 < mon_arbre->taille_arbre && mon_arbre->tab[2*i+1] > mon_arbre->tab[i]) || (2*i+2 < mon_arbre->taille_arbre && mon_arbre->tab[2*i+2] > mon_arbre->tab[i]))
    {
        // Si y a un membre droite
        if(2*i+2 < mon_arbre->taille_arbre)
        {
            // Si gauche > droite
            if(mon_arbre->tab[2*i+1] > mon_arbre->tab[2*i+2])
            {
                temp = mon_arbre->tab[2*i+1];
                mon_arbre->tab[2*i+1] = mon_arbre->tab[i];
                mon_arbre->tab[i] = temp;
                i = 2*i+1;
                // Si droite > gauche
            }
            else
            {
                temp = mon_arbre->tab[2*i+2];
                mon_arbre->tab[2*i+2] = mon_arbre->tab[i];
                mon_arbre->tab[i] = temp;
                i = 2*i+2;
            }
        }
        else
        {
            // Droite > parent
            temp = mon_arbre->tab[2*i+1];
            mon_arbre->tab[2*i+1] = mon_arbre->tab[i];
            mon_arbre->tab[i] = temp;
            i = 2*i+1;
        }
    }
    return mon_arbre;
}

int* Tri_1(int* tab, int taille)
{
    Arbre* mon_arbre = Creer_arbre(1);

    // Tranfere du tableau dans le tas binaire
    mon_arbre->tab[0] = tab[0];
    for(int i = 1; i < taille; i++)
        ajouter(mon_arbre, tab[i]);

    // Transfert du tas binaire dans le tableau de maniere trier
    for(int i = taille-1; i >= 0; i--)
    {
        tab[i] = mon_arbre->tab[0];
        supprimer_racine(mon_arbre);
    }

    free(mon_arbre->tab);
    free(mon_arbre);

    return tab;
}

Arbre* Tri_2(int* tab, int taille)
{
    Arbre* mon_arbre = Creer_arbre(1);

    // Tranfere du tableau dans le tas binaire
    mon_arbre->tab[0] = tab[0];
    for(int i = 1; i < taille; i++)
        ajouter(mon_arbre, tab[i]);

    // Transfert du tas binaire dans le tableau de maniere trier
    for(int i = 0; i < mon_arbre->taille_arbre; i++)
    {
        // Switch 1 ere et derniere
        int temp = mon_arbre->tab[taille-1];
        mon_arbre->tab[taille-1] = mon_arbre->tab[0];
        mon_arbre->tab[0] = temp;

        taille--;

        // (droite existe et droite > parent) ou (gauche existe et gauche > parent)
        while ((2*i+1 < taille && mon_arbre->tab[2*i+1] > mon_arbre->tab[i]) || (2*i+2 < taille && mon_arbre->tab[2*i+2] > mon_arbre->tab[i]))
        {
            // Si y a un membre droite
            if(2*i+2 < taille)
            {
                // Si gauche > droite
                if(mon_arbre->tab[2*i+1] > mon_arbre->tab[2*i+2])
                {
                    temp = mon_arbre->tab[2*i+1];
                    mon_arbre->tab[2*i+1] = mon_arbre->tab[i];
                    mon_arbre->tab[i] = temp;
                    i = 2*i+1;
                    // Si droite > gauche
                }
                else
                {
                    temp = mon_arbre->tab[2*i+2];
                    mon_arbre->tab[2*i+2] = mon_arbre->tab[i];
                    mon_arbre->tab[i] = temp;
                    i = 2*i+2;
                }
            }
            else
            {
                // Droite > parent
                temp = mon_arbre->tab[2*i+1];
                mon_arbre->tab[2*i+1] = mon_arbre->tab[i];
                mon_arbre->tab[i] = temp;
                i = 2*i+1;
            }
        }
    }

    return mon_arbre;
}

//Cette fonction sert à faire une saisie sécurisée
int secu_saisie()
{
    int x = 0;
    do {
        while(scanf("%d", &x) == 0) {
            printf("Ce n'est pas un entier.\n");
            while ((x =getchar())!='\n' && (x!=EOF));
        }

        if(x < 0)
            printf("C'est une valeur négative.\n");
    }while (x < 0);

    return x;
}

// Puis voici le main avec le menu etc
int main()
{
    Arbre* mon_arbre = NULL;
    int choix_menu;
    do
    {
        //nous devons utiliser des bibliothèque utilisant du WIN32 dans APPLE
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            system("cls");    //Fonciton Clear sur OSX
        #elif __APPLE__
            system("clear"); // Et hop elle est transvasé sur OSX système
        #endif
        printf("(_________________________MENU____________________________)\n\n");
        printf("1. - _______Pour creer un arbre___________________________ \n"
               "2. - _______Pour ajouter une valeur a celui-ci____________\n"
               "3. - _______Pour supprimer la racine______________________ \n"
               "4. - _______Pour faire le tri de notre arbre______________ \n"
               "5. - _______Pour faire le tri en place de notre arbre_____ \n"
               "6. - _______Pour quitter__________________________________ \n\n");
        afficher(mon_arbre);
        printf("Qu'elle fonction souhaitez vous exectuer ?\n");
        choix_menu = secu_saisie(); 

        // la fonction Switch nous permet de choisir les différents cas du menu
        switch(choix_menu)
        {
        // nous édifions les différents cas de 1 à 5
        case 1 :
            if(mon_arbre != NULL) {
                free(mon_arbre->tab);
                free(mon_arbre);
            }
                // A chaque fois on demande à l'utilisateur 
            printf("Quelle sera la taille maximale de votre arbre ?\n");
            int taille = secu_saisie();
            mon_arbre = Creer_arbre(1);

            // Saisie du tableau dans le tas binaire
            printf("Veuillez saisir les valeurs \n> ");
            mon_arbre->tab[0] = secu_saisie();
            for(int i = 1; i < taille; i++)
            {
                printf("> ");
                ajouter(mon_arbre, secu_saisie());
            }
            break;
        case 2 : // Nous utiliserons la commande et la biliothèque WIN32 dans tous les cas de mon menu
            if(mon_arbre == NULL)
            {
                printf("Il faut d'abord creer l'arbre\n");
                #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
                    system("pause");
                #endif
            }
            else
            {
                printf("Saisir une valeur\n");
                int valeur = secu_saisie();
                ajouter(mon_arbre,valeur);
                afficher(mon_arbre);
            }

            break;
        case 3 :
            if(mon_arbre == NULL)
            {
                printf("Il faut d'abord creer l'arbre\n");
                #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
                    system("pause");
                #endif
            }
            else
            {
                supprimer_racine(mon_arbre);
            }
            break;
        case 4 :
            if(mon_arbre == NULL)
            {
                printf("Il faut d'abord creer l'arbre\n");
                #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
                    system("pause");
                #endif
            }
            else
            {
                int* tableau = Tri_1(mon_arbre->tab,mon_arbre->taille_arbre);
                printf("Votre Tableau Trie : [");
                for (int i=0; i < mon_arbre->taille_arbre-1; i++)
                    printf("%d , ",tableau[i]);
                printf("%d]\n\n",tableau[mon_arbre->taille_arbre-1]);
            }
            break;
        case 5 :
            if(mon_arbre == NULL)
            {
                printf("Il faut d'abord creer l'arbre\n");
                #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
                    system("pause");
                #endif
            }
            else
            {
                free(mon_arbre->tab);
                free(mon_arbre);
                mon_arbre = Tri_2(mon_arbre->tab,mon_arbre->taille_arbre);
            }
            break;
        }
    } while (choix_menu != 6);
    return 0;
}
