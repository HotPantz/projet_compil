
<Authors : Nathan LESTRADE  Selyan KABLIA>

# Calculatrice en C

Ce projet consiste en une calculatrice simple implémentée en langage C. Il prend en entrée une expression arithmétique et produit son résultat. Le code est réparti en plusieurs fichiers pour une meilleure organisation et modularité.

## Contenu du Projet

Le projet est composé des fichiers suivants :

- `main.c`: Contient la fonction `main` du programme, responsable de l'interaction avec l'utilisateur.
- `lexer.c` et `lexer.h`: Contiennent les fonctions de tokenisation pour analyser l'entrée utilisateur et générer une séquence de jetons.
- `parser.c` et `parser.h`: Implémente un analyseur syntaxique pour valider la structure de l'expression et générer un arbre syntaxique.
- `Makefile`: Automatise la compilation du projet.

## Compilation et Exécution

Pour compiler le projet, exécutez la commande suivante dans votre terminal :

```bash
make
```

Cela produira un exécutable nommé `calc`. Vous pouvez ensuite lancer le programme en tapant :

```bash
./calc
```

## Utilisation

Une fois le programme lancé, vous pouvez entrer une expression arithmétique et appuyer sur Entrée pour obtenir son résultat. Voici un exemple d'utilisation :

```plaintext
$> tar xvfz lestrade_kablia.tgz
$> cd lestrade_kablia
$> make
$> ./calc
> 10*1+2+3+4
19
> 1+3*(5+5)+2
33
> 1+(2+(3+(4+(5+(6+8)))))
29
> (3+3)*(3*3)
54
> 1*2*(3+2)*(0*0)
0 
> q
```

Pour quitter le programme, entrez simplement `q` et appuyez sur Entrée.

## Structure du Code

### Tokenisation (`lexer.c` et `lexer.h`)

La tokenisation consiste à convertir une chaîne de caractères en une séquence de jetons (tokens) représentant les différents éléments de l'expression arithmétique, tels que les nombres, les opérateurs, et les parenthèses.

### Analyse Syntaxique (`parser.c` et `parser.h`)

L'analyse syntaxique vérifie la structure grammaticale de l'expression arithmétique à l'aide d'une table d'analyse syntaxique et d'une table d'actions. Elle va également calculer le résultat de l'expression.

### Évaluation dans le Parser (`parser.c` et `parser.h`)

L'évaluation de l'expression est effectuée directement dans le fichier `parser.c`. Après avoir vérifié la structure de l'expression et généré l'arbre syntaxique, le parseur procède à l'évaluation de l'expression et affiche le résultat.

## Fonctionnement

Le fichier `main.c` contient la fonction `main` du programme, qui gère l'interaction avec l'utilisateur. Lorsque l'utilisateur entre une expression arithmétique, le programme utilise les fonctions du lexer pour tokeniser l'expression, puis passe les tokens au parser pour analyse et évaluation. Une fois l'évaluation terminée, le résultat est affiché à l'utilisateur.

## Résumé

Ce projet de calculatrice en C illustre l'implémentation des principes fondamentaux d'analyse lexicale, syntaxique et sémantique. Il fournit une base solide pour étendre les fonctionnalités de la calculatrice, telles que le support de fonctions mathématiques avancées ou l'ajout de fonctionnalités graphiques.
