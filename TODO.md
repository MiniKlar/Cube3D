# cub3D - Liste de Tâches

---

## 🕵️ Parsing (Analyse du fichier `.cub`)

- [ ] **Gestion des arguments :**
    - [ ] S'assurer que le programme prend exactement un argument.
    - [ ] Vérifier que l'argument est un fichier avec l'extension `.cub`.
- [ ] **Analyse des éléments :**
    - [ ] Lire et stocker le chemin pour la texture Nord (`NO`).
    - [ ] Lire et stocker le chemin pour la texture Sud (`SO`).
    - [ ] Lire et stocker le chemin pour la texture Ouest (`WE`).
    - [ ] Lire et stocker le chemin pour la texture Est (`E`).
    - [ ] Lire et stocker la couleur du sol (`F`) au format R,G,B.
    - [ ] Lire et stocker la couleur du plafond (`C`) au format R,G,B.
- [ ] **Flexibilité du parsing :**
    - [ ] Gérer les éléments (textures, couleurs) dans n'importe quel ordre.
    - [ ] Autoriser des lignes vides entre les éléments.
    - [ ] Autoriser des espaces entre l'identifiant (ex: `F`) et sa valeur (ex: `220,100,0`).
- [ ] **Analyse de la carte :**
    - [ ] S'assurer que la carte est le **dernier élément** du fichier.
    - [ ] Lire la carte telle qu'elle est dans le fichier.
    - [ ] Gérer les caractères autorisés : `0` (vide), `1` (mur), ` ` (espace, à gérer), et un seul `N`, `S`, `E`, ou `W` (position joueur).
- [ ] **Validation et gestion des erreurs :**
    - [ ] Vérifier que la carte est entourée/fermée par des murs (`1`).
    - [ ] En cas de configuration invalide (fichier, couleurs, carte, etc.), quitter proprement.
    - [ ] Afficher "Error\n" suivi d'un message d'erreur explicite en cas de problème.

---

## 🚀 Exécution (Logique du jeu)

- [ ] **Initialisation :**
    - [ ] Initialiser la `miniLibX` et créer une fenêtre.
    - [ ] Charger les 4 textures (Nord, Sud, Est, Ouest).
    - [ ] Initialiser la position et l'orientation du joueur (depuis `N`, `S`, `E`, ou `W`).
- [ ] **Rendu graphique (Ray-casting) :**
    - [ ] Implémenter l'algorithme de ray-casting pour afficher une vue 3D.
    - [ ] Dessiner le plafond avec la couleur `C`.
    - [ ] Dessiner le sol avec la couleur `F`.
    - [ ] Afficher les murs avec la texture correspondante (Nord, Sud, Est, Ouest) selon l'orientation.
    - [ ] Afficher l'image dans la fenêtre.
- [ ] **Gestion des événements (Contrôles) :**
    - [ ] **Déplacement :** Gérer les touches `W`, `S`, et `D` pour le mouvement.
    - [ ] **Rotation :** Gérer les flèches gauche et droite pour la rotation de la caméra.
    - [ ] **Quitter (proprement) :**
        - [ ] Touche `ESC`.
        - [ ] Clic sur la croix rouge de la fenêtre.
- [ ] **Stabilité et mémoire :**
    - [ ] Assurer une gestion fluide de la fenêtre (minimisation, etc.).
    - [ ] Libérer toute la mémoire allouée (`free`).
    - [ ] Éviter les crashs (segfault, bus error, etc.).

---

## 🌟 Bonus (Optionnel)

- [ ] Gérer les collisions avec les murs.
- [ ] Ajouter une mini-carte (minimap).
- [ ] Implémenter des portes qui s'ouvrent et se ferment.
- [ ] Ajouter des sprites animés.
- [ ] Permettre la rotation de la caméra avec la souris.
