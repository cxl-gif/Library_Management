#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*================ STRUCTURE LIVRE ================*/

typedef struct Livre
{

    char titre[50];
    char auteur[50];
    int code;
    int annee;
    int disponible;

    struct Livre *suivant;

} Livre;

/*================ STRUCTURE PILE ================*/

typedef struct Pile
{

    Livre info;
    struct Pile *suivant;

} Pile;

/*================ DECLARATION GLOBALE ================*/

Livre *L = NULL;
Pile *P = NULL;

/*================ AJOUTER LIVRE ================*/

Livre *ajouterLivre(Livre *L)
{
    Livre *nv;
    Livre *tmp;

    nv = (Livre *)malloc(sizeof(Livre));

    printf("Titre : ");
    scanf(" %[^\n]", nv->titre);

    printf("Auteur : ");
    scanf(" %[^\n]", nv->auteur);

    printf("Code : ");
    scanf("%d", &nv->code);

    printf("Annee : ");
    scanf("%d", &nv->annee);

    nv->disponible = 1;
    nv->suivant = NULL;

    if (L == NULL)
    {
        L = nv;
    }

    else
    {
        tmp = L;

        while (tmp->suivant != NULL)
        {
            tmp = tmp->suivant;
        }

        tmp->suivant = nv;
    }

    return L;
}

/*================ RECHERCHER LIVRE ================*/

void rechercherLivre(Livre *L)
{
    int code;
    Livre *tmp;

    printf("Entrer le code : ");
    scanf("%d", &code);

    tmp = L;

    while (tmp != NULL)
    {
        if (tmp->code == code)
        {
            printf("\nLivre trouve\n");

            printf("Titre : %s\n", tmp->titre);
            printf("Auteur : %s\n", tmp->auteur);
            printf("Annee : %d\n", tmp->annee);

            return;
        }

        tmp = tmp->suivant;
    }

    printf("\nLivre introuvable\n");
}

/*================ EMPILER ================*/

Pile *empiler(Pile *P, Livre x)
{
    Pile *nv;

    nv = (Pile *)malloc(sizeof(Pile));

    nv->info = x;

    nv->suivant = P;

    P = nv;

    return P;
}

/*================ SUPPRIMER LIVRE ================*/

Livre *supprimerLivre(Livre *L)
{
    int code;

    Livre *tmp;
    Livre *prec;

    printf("Entrer le code du livre : ");
    scanf("%d", &code);

    tmp = L;
    prec = NULL;

    while (tmp != NULL && tmp->code != code)
    {
        prec = tmp;
        tmp = tmp->suivant;
    }

    if (tmp == NULL)
    {
        printf("\nLivre non trouve\n");
        return L;
    }

    /* sauvegarder dans pile */

    P = empiler(P, *tmp);

    /* suppression */

    if (prec == NULL)
    {
        L = tmp->suivant;
    }

    else
    {
        prec->suivant = tmp->suivant;
    }

    free(tmp);

    printf("\nLivre supprime\n");

    return L;
}

/*================ RESTAURER ================*/

Livre *restaurerLivre(Livre *L)
{
    Pile *tmpPile;
    Livre *nv;

    if (P == NULL)
    {
        printf("\nPile vide\n");
        return L;
    }

    tmpPile = P;

    nv = (Livre *)malloc(sizeof(Livre));

    *nv = tmpPile->info;

    nv->suivant = L;

    L = nv;

    P = P->suivant;

    free(tmpPile);

    printf("\nLivre restaure\n");

    return L;
}

/*================ MODIFIER LIVRE ================*/

void modifierLivre(Livre *L)
{
    int code;

    Livre *tmp;

    printf("Entrer le code : ");
    scanf("%d", &code);

    tmp = L;

    while (tmp != NULL)
    {
        if (tmp->code == code)
        {
            printf("Nouveau titre : ");
            scanf(" %[^\n]", tmp->titre);

            printf("Nouvel auteur : ");
            scanf(" %[^\n]", tmp->auteur);

            printf("Nouvelle annee : ");
            scanf("%d", &tmp->annee);

            printf("\nLivre modifie\n");

            return;
        }

        tmp = tmp->suivant;
    }

    printf("\nLivre introuvable\n");
}
/*================ AFFICHER LIVRES ================*/

void afficherLivres(Livre *L)
{
    Livre *tmp;

    tmp = L;

    if (L == NULL)
    {
        printf("\nListe vide\n");
        return;
    }

    while (tmp != NULL)
    {
        printf("\n-----------------\n");

        printf("Titre : %s\n", tmp->titre);
        printf("Auteur : %s\n", tmp->auteur);
        printf("Code : %d\n", tmp->code);
        printf("Annee : %d\n", tmp->annee);

        if (tmp->disponible == 1)
            printf("Disponible\n");

        else
            printf("Emprunte\n");

        tmp = tmp->suivant;
    }
}

/*================ MENU ================*/

int main()
{
    int choix;

    do
    {
        printf("\n\n========= MENU =========\n");

        printf("1. Ajouter livre\n");
        printf("2. Afficher livres\n");
        printf("3. Rechercher livre\n");
        printf("4. Supprimer livre\n");
        printf("5. Restaurer livre\n");
        printf("6. Modifier livre\n");
        printf("7. Quitter\n");

        printf("\nChoix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            L = ajouterLivre(L);
            break;

        case 2:
            afficherLivres(L);
            break;

        case 3:
            rechercherLivre(L);
            break;

        case 4:
            L = supprimerLivre(L);
            break;

        case 5:
            L = restaurerLivre(L);
            break;

        case 6:
            modifierLivre(L);
            break;

        case 7:
            printf("\nFin programme\n");
            break;

        default:
            printf("\nChoix invalide\n");
        }

    } while (choix != 7);

    return 0;
}