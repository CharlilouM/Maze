# Générateur de Labyrinthe avec Raylib

Ce projet est un générateur de labyrinthe en C utilisant la bibliothèque Raylib pour le rendu graphique. Il propose diverses options de résolution de labyrinthe, telles que les algorithmes A*, BFS (Breadth-First Search), et DFS (Depth-First Search), tout en affichant le temps de résolution. De plus, il inclut une simulation de deux robots : l'un se déplace dans le labyrinthe, et l'autre tente de l'attraper. Une fonctionnalité supplémentaire permet de prendre en compte l'esquive de bombes.

## Fonctionnalités

- **Génération de Labyrinthe** : Crée des labyrinthes de différentes tailles et complexités.
- **Algorithmes de Résolution** : Implémente les algorithmes A*, BFS, et DFS pour trouver le chemin dans le labyrinthe.
- **Affichage du Temps de Résolution** : Mesure et affiche le temps nécessaire pour résoudre le labyrinthe avec chaque algorithme.
- **Simulation de Robots** :
  - **Robot Explorateur** : Se déplace dans le labyrinthe pour atteindre une cible.
  - **Robot Chasseur** : Tente d'attraper le robot explorateur.
- **Esquive de Bombes** : Option pour ajouter des bombes dans le labyrinthe que les robots doivent esquiver.

## Prérequis

- Compilateur C (par exemple, GCC)
- Bibliothèque Raylib (disponible sur [raylib.com](https://www.raylib.com/))

## Installation

1. **Installer Raylib** : Suivez les instructions d'installation de Raylib pour votre système d'exploitation sur le site officiel.
2. **Cloner le Dépôt** :
   ```bash
   git clone https://github.com/CharlilouM/Maze/.git
   cd Maze
   ```
3. **Compiler le Projet** :
   ```bash
   Make
   ```
   Si cela ne compile pas, vérifiez le chemin d'accès raylib dans le makefile

## Utilisation

1. **Exécuter le Programme** :
   ```bash
   ./simu
   ```
2. **Options de Configuration** :
   - Sélectionnez l'algorithme de résolution (A*, BFS, DFS).
   - Activez ou désactivez la simulation des robots.
   - Activez ou désactivez l'option d'esquive de bombes.

