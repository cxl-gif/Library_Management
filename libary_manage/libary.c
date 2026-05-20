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
// la pile pour la suppression des livres
typedef struct Pile
{
    Livre info;
    struct Pile *suivant;

} Pile;

/*================ STRUCTURE DEMANDE ================*/

typedef struct Demande
{
    char nomLecteur[30];
    char prenomLecteur[30];
    int codeLivre;

    struct Demande *suivant;

} Demande;

/*================ DECLARATION GLOBALE ================*/

// tete liste
Livre *L = NULL;
// sommet pile
Pile *P = NULL;
// tete file
Demande *F = NULL;
// queue file
Demande *Q = NULL;

/*================ AJOUTER LIVRE ================*/

Livre *ajouterLivre(Livre *L)
{
    Livre *nv;
    Livre *tmp;

    nv = (Livre *)malloc(sizeof(Livre));

    printf("Titre : ");
    scanf(" %[ ^\n]s", nv->titre);

    printf("Auteur : ");
    scanf(" %[ ^\n]s", nv->auteur);

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
// ajoute un livre dans un pile
Pile *empiler(Pile *P, Livre x)
{
    Pile *nvpile;

    nvpile = (Pile *)malloc(sizeof(Pile));

    nvpile->info = x;

    nvpile->suivant = P;

    P = nvpile;

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

    if (tmp == NULL)
    {
        printf("\nLivre non trouve\n");
        return L;
    }

    while (tmp != NULL && tmp->code != code)
    {
        prec = tmp;
        tmp = tmp->suivant;
    }

    /* sauvegarder dans pile */

    P = empiler(P, *tmp);

    /* suppression */

    // si element veut supp est le premiere elm
    if (prec == NULL)
    {

        L = tmp->suivant;
    }

    else
    {
        // precedent ghaywli ypointer 3la element suiv dyl lcourant
        prec->suivant = tmp->suivant;
    }

    free(tmp);

    printf("\nLivre supprime\n");

    return L;
}

/*================ RESTAURER ================*/

Livre *restaurerLivre(Livre *L, Pile *P)
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


void afficherDisponibles(Livre *L)
{
    Livre *tmp;
    int trouve = 0;

    if (L == NULL)
    {
        printf("\nListe vide\n");
        return;
    }

    printf("\n====== LIVRES DISPONIBLES ======\n");

    tmp = L;

    while (tmp != NULL)
    {
        if (tmp->disponible == 1)
        {
            printf("\nCode   : %d\n", tmp->code);
            printf("Titre  : %s\n", tmp->titre);
            printf("Auteur : %s\n", tmp->auteur);
            printf("Annee  : %d\n", tmp->annee);
            trouve = 1;
        }

        tmp = tmp->suivant;
    }

    if (trouve == 0)
        printf("Aucun livre disponible\n");

    printf("================================\n");
}

void trierParAnnee(Livre *L)
{
    Livre *tmp; // parcourir la liste
    Livre temp;
    int echange;

    if (L == NULL || L->suivant == NULL)
    {
        printf("\nListe trop courte pour trier\n");
        return;
    }

    do
    {
        echange = 0;
        tmp = L;

        while (tmp->suivant != NULL)
        {
            if (tmp->annee > tmp->suivant->annee)
            {
                /* hna kan  echanger le contenu des 2 noeuds */
                temp = *tmp;
                *tmp = *tmp->suivant;
                *tmp->suivant = temp;

                echange = 1;
            }

            tmp = tmp->suivant;
        }

    } while (echange);

    printf("\nLivres tries par annee\n");

    afficherLivres(L);
}

void enfilerDemande()
{
    Demande *nv;

    nv = (Demande *)malloc(sizeof(Demande));

    printf("Nom du lecteur    : ");
    scanf(" %[^\n]", nv->nomLecteur);

    printf("Prenom du lecteur : ");
    scanf(" %[^\n]", nv->prenomLecteur);

    printf("Code du livre     : ");
    scanf("%d", &nv->codeLivre);

    nv->suivant = NULL;

    if (F == NULL)
    {
        F = nv;
        Q = nv;
    }
    else
    {
        Q->suivant = nv;
        Q = nv;
    }

    printf("\nDemande de %s %s ajoutee\n", nv->prenomLecteur, nv->nomLecteur);
}

void afficherDemandes()
{
    Demande *tmp;
    int i = 1;

    if (F == NULL)
    {
        printf("\nAucune demande en attente\n");
        return;
    }

    printf("\n====== DEMANDES EN ATTENTE ======\n");

    tmp = F;

    while (tmp != NULL)
    {
        printf("\n[%d] %s %s - Livre code %d\n",
               i, tmp->prenomLecteur, tmp->nomLecteur, tmp->codeLivre);

        tmp = tmp->suivant;
        i++;
    }

    printf("=================================\n");
}

Livre *traiterDemande(Livre *L)
{
    Demande *tmpFile;
    Livre *tmp;
    int code;

    if (F == NULL)
    {
        printf("\nAucune demande a traiter\n");
        return L;
    }

    /* recuperer la premiere demande (tete de file) */
    tmpFile = F;
    code = tmpFile->codeLivre;

    printf("\nTraitement de la demande de %s %s (livre code %d)...\n",
           tmpFile->prenomLecteur, tmpFile->nomLecteur, code);

    /* kan red la tete dyal file howa le next */
    F = F->suivant;

    if (F == NULL)
        Q = NULL; /* file maintenant vide */

    free(tmpFile);

    /* chercher le livre dans la liste */
    tmp = L;

    while (tmp != NULL)
    {
        if (tmp->code == code)
        {
            if (tmp->disponible == 1)
            {
                tmp->disponible = 0;
                printf("Demande ACCEPTEE : \"%s\" est maintenant emprunte\n", tmp->titre);
            }
            else
            {
                printf("Demande REJETEE : \"%s\" est deja emprunte\n", tmp->titre);
            }

            return L;
        }

        tmp = tmp->suivant;
    }

    printf("Demande REJETEE : livre code %d introuvable\n", code);

    return L;
}

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
        printf(" 7.  Afficher les livres disponibles\n");
        printf(" 8.  Trier les livres par annee\n");
        printf(" 9.  Ajouter une demande d'emprunt\n");
        printf("10.  Afficher les demandes d'emprunt\n");
        printf("11.  Traiter une demande d'emprunt\n");
        printf("12.  Quitter le programme\n");
        printf("===================================\n");

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
            afficherDisponibles(L);
            break;

        case 8:
            trierParAnnee(L);
            break;

        case 9:
            enfilerDemande();
            break;

        case 10:
            afficherDemandes();
            break;

        case 11:
            L = traiterDemande(L);
            break;

        case 12:
            printf("\nFin du programme\n");
            break;

        default:
            printf("\nChoix invalide\n");
        }

    } while (choix != 12);

    return 0;
}
