# IFCC - Manuel Utilisateur 

Ce repository contient le compilateur de fichiers en lagage C des *Hexperts* :  **IFCC**. 

## Comment utiliser le compilateur

Le compilateur **IFCC** permet de générer de l'assembeur dans un fichier `.s` à partir d'un fichier rédigé en C (extension `.c`).

Le compilateur se lance via la commande `./ifcc`. 

```bash
./ifcc -S infile [-o outfile] [-Wall] [-h]
```

Pour la liste de toutes les options disponibles utilisez la commande `./ifcc -h`

Vous retrouverez des exemples d'utilisation et la liste des options disponibles ci-dessous.

### Exemples d'utilisation
#### Utilisation avec un fichier de sortie nommé

```bash
ifcc -S fichier_source.c -o fichier_destination.s
```

#### Utilisation avec un fichier de sortie par défaut
```bash
ifcc -S fichier_source.c
```

Le compilateur générera automatique un fichier de sortie `fichier_source.s`, avec le même nom que le fichier source mais l'extension assembleur `.s`.

### Options disponibles

Notre compilateur contient moins de paramètres que le compilateur GCC ou d'autres compilateurs de C.

Il n'est ainsi utilisable uniquement avec l'option `-S`.

#### Liste des options

- `-S` : Le compilateur génère un code assembleur dans un fichier `.s`
- `-o` : Afin de choisir le fichier de sortie du code généré par le compilateur **IFCC**.  
- `-Wall` : pour afficher la liste des warnings générés lors de la compilation du code
- `-h`: Pour lister les options disponibles

## Features disponibles 

- [x] Type de données supportées: int 32 bit 
- [x] Compiler la déclaration d'une variable (en ligne ou n'importe ou)
- [x] Compiler l’affectation vers une variable
- [x] Compiler les expressions arithmétiques 
- [x] Opérations arithmétiques de base ; +,-, *; opérations logiques bit-à-bit |, &,^; opérations de comparaison ==, !=, <, >; opérations unaires ! et -. et les opérateurs logiques
  paresseux ||, &&, et ! ; opération de shift arithmétiques <<, >>
- [x] Compiler le if ... else if ... else
- [x] Compiler les boucles while
- [x] Compiler les boucles for
- [x] Compiler les break
- [x] Compiler le retour de valeur (multiple également)
- [x] Optimisation des expressions arithmétiques dans le front end: Élimination les éléments neutres des opérateurs, transformation des expressions constantes en leur valeur
- [x] Gestion des erreurs et warnings à travers la vérification statique.
- [x] La gestion de portées pour des usages futur (continuité du projet avec des fonctions)

# Manuel Developpeur

## Environnement de développement
Le projet repose sur la techno antlr4. C'est un générateur de parser qui permet de lire le code, construire un arbre du contenu du code (AST) pour ensuite le parcourir et produire du code assembleur.

### Installation de Antlr4

L'installation est constituée de plusieurs étapes et d'un chapitre de gestion des problèmes rencontrés lors de l'installation (`Troubleshouting - Installation`).
L'installation décrite correspond ici à un environnement Linux.

1. Mettre à jour les packets installés 
```bash
sudo apt-get updates
```

2. Télécharger les fichiers d'installation  
Téléchargez `antlr4-cpp-runtime-4.7.2-source.zip` ici : https://www.antlr.org/download.html

3. Dezipper `antlr4-cpp-runtime-4.7.2-source.zip` et rendez vous dans le dossier **antlr4-cpp-runtime-4.7.2-source**

4. Executer les commandes suivantes (pour récuperer les outils nécessaires à l'installation)
    ```bash
    sudo apt install cmake
    sudo apt install uuid-dev
    sudo apt install pkg-config
    ```

5. Puis commencez l'installation avec 
    ```bash
    mkdir build && mkdir run && cd build
    cmake ..
    DESTDIR=../run make install 
    ```

6. Maintenant copier les fichiers installer dans votre **lib** locale
    ```bash
    cd ../run/usr/local/include
    sudo cp -r antlr4-runtime /usr/local/include
    cd ../lib
    sudo cp * /usr/local/lib
    sudo ldconfig 
    ```

7. Vous pouvez maintenant delete le `.zip` et le dossier  **antlr4-cpp-runtime-4.7.2-source**

8. Installer le package Antlr4 
    ```bash
    sudo apt-get install antlr4
    ```

L'installation est effectuée ! Pour tous problèmes lors de celle-ci, reférez vous à la section `Troubleshouting - Installation`.

## Structure du projet
### Fichiers source 
- `ifcc.g4` contient la grammaire au format antlr4 
- `main.cpp` contient le code C++ code appalant le antlr4-generated parser pour parser et compiler le fichier passé en paramètre.
- `visitor.h` est un visiteur de  l'arbre parsé par antlr4. Il appelera ensuite l'IR, l'AST et utilisera le CFG pour générer du code assembleur. 
- `package AST` ce package contient toutes les classes qui nous permettent de créer notre propre AST. Elles servent d'intermédiaire entre les visiteurs et les classes IR pour générer de l'assembleur. Nous avons fait le choix de redéfinir cette AST afin de factoriser le code et le rendre plus élégant ce qui rend les visiteurs bcp plus simple à implémenter et réduit leur complexité.
- `package IR`ce package comprend un sous package IRInstr qui comporte toutes les IRInstructions de bases correspondant aux mnemonics utilisées. De plus ce dernier contient les classes CFG, Basic Block, et Symbol Table qui orchestrent la génération du code assembleur.

### Structure de données 
la structure de donnée ci-dessous représente l'architecture de l'AST utilisée pour stocker les données lues et parsées par antlr4.

![Diagramme Structure de données](https://i.imgur.com/5YZ2yDk.png)

## Compiler le projet
- `Makefile` permet de compiler le parser. 
- `compile_macos.sh` compile le projet pour un environnement MacOS
- `compile_if.sh` compile le projet pour un environnement linux sur une machine du Departement Informatique
- `compile_ubuntu.sh` compile le projet pour un environnement linux 
- `compile_macos_DEBUG.sh` compile le projet pour un environnement MacOS et affiche une trace de debug du programme
- `compile_if_DEBUG.sh` compile le projet pour un environnement linux sur une machine du Departement Informatique et affiche une trace de debug du programme


## Tests

Un module de test se situe dans le dossier `tests`. 
Composé de plusieurs fichiers pour son exécution, il demande à ce que `./ifcc` soit présent dans le dossier `compiler`. *(Voir le chapitre sur la compilation du projet).*

On pourra lancer le module de test entier depuis le dossier `compiler` via la commande suivante : 
```bash
make test
```

L'ensemble des tests se lance via le fichier `test_if.sh` et utilise le script python `pld-test.py`. Le résultat des tests s'affiche dans la console et se situe dans le dossier `pld-test-outputs`.

On pourra exécuter certains tests spécifiques avec la commande 

```bash
./test_if.sh nom_du_dossier_tests
```

Par exemple 
```bash
./test_if.sh testIntegration/testAddSub
```
lancera uniquement les tests d'intégration des opérateur arithmétiques d'addition et de soustraction.`

L'ensemble des fichiers de test sont au format C et respectent une syntaxe prédéfinie.

**`NumeroDuTypeDeTest`** _ **`EtatAttendu`** _ **`NomDuTest NumerodeVariationDuTest`**.c

### Tests unitaires

Ce package contient tous les tests unitaires que nous avons réalisés pour chacune des fonctionnalités implémentées. Nous citons: 

- testAddition, testDivision, testMultiplication, testSubstraction, testModulo, testDecrement, testIncrement, testShiftLeft, testShiftRight, 
-  testAffectation (pour les tests += -= /= *=), testComparaison , testGeneral, testSignSwitch (pour la gestion des expressions de type -a, -9...), , testVariableMemory

### Tests d'intégration

Ce package comprend les tests d'intégration des différentes fonctionnalitées, il contient les packages suivants: 

- testAddSub, testMultDiv, testASMD (pour add sub mult div)
- testWhile, testFor, testIf, testBreak, testComp (pour comparaison)

### Tests de Non Régression 

Et finalement afin de vérifier que chacun des fonctionnalités implémentées n'a pas régressées une fonctionnalités qui marchaient bien avant nous avons effectués des tests de non régression dont: 

- testForIf, testForWhile, testFWI (for while if), testIfIf, testWhileIf, testWhileWhile

### Test des erreurs et warnings 

Afin de tester que notre gestion d'erreurs statiques et warnings marche bien, nous offrons un package de tests de celles ci qui reprend des programmes contenant des erreurs. 

Attention: ces tests ne sont pas à lancer avec le Framework de tests mais plutôt un par un car fin de voir les erreurs produites. 


## Troubleshooting
### Installation 

En cas d'erreurs lors de la compilation ou du lancement des tests suite à l'installation veuillez effectuer les actions ci-dessous.

#### Si erreur `clang` lors de la compilation
Installer `clang`, un outils supplémetaire nécessaire à la compilation 
```bash
sudo apt install clang
```
#### En cas d'erreurs lors de la compilation (dans les fichiers bash)
Renommez le dossier dans lequel est le projet avec un nom **sans espaces**.













