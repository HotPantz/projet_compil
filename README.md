# Calculatrice pour sommes et produits

Ce projet a été réalisé par Devan SOHIER dans le cadre du cours d'Algorithmes pour la compilation, durant l'année universitaire 2023-2024.
Description

Ce programme est une calculatrice écrite en langage C, permettant d'effectuer des opérations de sommes et de produits sur des nombres flottants. Il gère également les parenthèses dans les opérations et permet à l'utilisateur de quitter en entrant la commande "q".
Mode de fonctionnement

La calculatrice fonctionne comme un interpréteur, comprenant un analyseur lexical et un analyseur syntaxique LR. L'analyse lexicale reconnaît les flottants, tandis que l'analyse syntaxique interprète les opérations effectuées.
Utilisation

Pour utiliser la calculatrice, suivez les étapes suivantes :

-   Téléchargez les fichiers source du projet.
-   Compilez le code en utilisant la commande make.
-   Exécutez le programme en lançant l'exécutable calc.
-   Saisissez les opérations que vous souhaitez effectuer et appuyez sur Entrée.
-   Pour quitter la calculatrice, entrez la commande "q".

### Exemple d'utilisation :

shell

$ make
$ ./calc
> 5+4*3
17
> (5+4)*3
27
> 5+4*3+6*7
59
> 5.6 + 1.4e-1
5.74
> q
$ 

## Structure du projet

Le projet est organisé comme suit :

 -   src/ : répertoire contenant les fichiers source du programme.
 -   Makefile : fichier pour compiler le programme.
 -   README.md : ce fichier, contenant des informations sur le projet.
 -   rapport.pdf : rapport détaillé sur le projet, expliquant les choix d'implémentation et les structures de données utilisées.

## Rapport

Le rapport détaillé sur le projet est disponible dans le fichier rapport.pdf. Il explique les choix d'implémentation, les structures de données utilisées et les algorithmes mis en œuvre pour l'analyse lexicale et syntaxique.
Améliorations possibles

-   Gérer d'autres opérations telles que la différence, la division et le moins unaire.
-   Ajouter la prise en charge d'autres fonctions mathématiques telles que les racines carrées, les logarithmes et les exponentielles.
-   Implémenter la gestion des variables pour les affectations et les utilisations.

Pour toute question ou commentaire, n'hésitez pas à me contacter à l'adresse suivante : devan.sohier@example.com.
