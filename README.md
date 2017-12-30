# MCS3 2018 (MCSQuizz)

Projet Middleware Client Serveur LE3 pour Centrale Lille Formation IG2I

**Des communications partout**

MCSQuizz est un projet réalisé dans le cadre des études en troisième année de la formation IG2I de Centrale Lille

Notre objectif était de réaliser un petit jeu de quiz en maximisant les communications réseaux

## Commencer

### Prérequis

Les exemples ici sont pour les systèmes basés sur GNU/Debian

- Build-Essential `# apt-get install build-essential`
- GCC `# apt-get install gcc`
- CMake `# apt-get install cmake`
- Git `# apt-get install git`
- Bibliothéque ncurses `# apt-get install libncurses5-dev`
- Bibliothéque cdk ( Version > 5.0.20161210-1 ) `# apt-get install libcdk5-dev`


### Compiler et Installer

Nous avons utilisé CMake afin de simplifier la compilation

- Installer les prérequis
- Télécharger le zip ou cloner ce repo
- Déplacer vous dans le répertoire build
- Executer `$ cmake ..` puis `$ make`

## Lancer

Le projet compilé est disponible dans le dossier build.

Lancer le avec `$ ./MCSQuizz`

## Tests

Nous avons fourni des executables afin de tester le fonctionnement du programme

Tester le projet dans le dossier build avec `$ make test`

