# Cube3D

A first-person 3D renderer built in C with raycasting, in the spirit of *Wolfenstein 3D*.
From a top-down grid map, it draws a real-time 3D view using the
[MLX42](https://github.com/codam-coding-college/MLX42) graphics library.

> 42 school project (cub3D). Built with the MLX42 library (GLFW backend), not the classic MiniLibX.

---

## 🇬🇧 English

### Principle

Cube3D is a **raycasting engine**. The world is a 2D grid of cells (walls and empty
space), but it is displayed as a 3D scene seen through the player's eyes.

For every vertical column of pixels on screen, the engine casts one ray from the
player's position into the map. Using a **DDA (Digital Differential Analysis)**
traversal, it walks the grid cell by cell until the ray hits a wall. The distance
to that wall determines the height of the wall slice drawn in that column: closer
walls are drawn taller, farther walls shorter — which is what creates the illusion
of depth.

Each wall slice is textured by sampling a column of the matching wall texture
(North / South / East / West, chosen from the side the ray hit), while the floor
and ceiling are filled with solid colors.

The render loop runs continuously through MLX42's `mlx_loop_hook`: it reads the
keyboard, updates the player's position and orientation, clears the frame, recasts
all rays, and presents the new image.

### .cub map format

> Note: in the current state of the project the map is **hardcoded** in
> `src/main.c` (`worldMap[24][24]`) and the textures/colors are loaded from fixed
> paths. The `.cub` parser is the next milestone (see `TODO.md`). The format below
> describes the target `.cub` configuration the engine is being built for.

A `.cub` scene file contains, in any order, the configuration elements followed by
the map (the map must come **last**):

```
NO ./path/to/north_texture.png
SO ./path/to/south_texture.png
WE ./path/to/west_texture.png
EA ./path/to/east_texture.png

F 220,100,0
C 225,30,0

111111
100001
101001
1000N1
111111
```

| Identifier | Meaning                                      |
|------------|----------------------------------------------|
| `NO`       | North wall texture path                      |
| `SO`       | South wall texture path                      |
| `WE`       | West wall texture path                       |
| `EA`       | East wall texture path                       |
| `F`        | Floor color, `R,G,B` (0–255 each)            |
| `C`        | Ceiling color, `R,G,B` (0–255 each)          |

Map characters:

| Char            | Meaning                                          |
|-----------------|--------------------------------------------------|
| `1`             | Wall                                             |
| `0`             | Empty (walkable) space                           |
| ` ` (space)     | Void / outside the map                           |
| `N` `S` `E` `W` | Player start position and facing direction (one) |

The map must be **closed / surrounded by walls** (`1`).

### Controls

| Key            | Action                       |
|----------------|------------------------------|
| `W`            | Move forward                 |
| `S`            | Move backward                |
| `Q`            | Strafe left                  |
| `D`            | Strafe right                 |
| `←` Left arrow | Rotate camera left           |
| `→` Right arrow| Rotate camera right          |
| `Esc`          | Quit                         |
| Window close   | Quit                         |

### Build & Run

**Dependencies**

- A C compiler (`cc` / `clang`), `make`, `cmake` and `git`.
- **GLFW** (required by MLX42). On macOS with Homebrew: `brew install glfw`.
  On Linux/Debian: `sudo apt install libglfw3-dev`.
- MLX42 and the project's libft (`LIB_C`) are cloned and built automatically by
  the `Makefile`.

**Build**

```bash
make
```

This fetches and builds `MLX42` and `LIB_C`, then compiles the `cube3D` binary.

**Run**

```bash
./cube3D
```

> The map is currently hardcoded, so no argument is needed. Once the `.cub`
> parser lands, the program will be launched as `./cube3D maps/scene.cub`.

**Useful Makefile targets**

| Target       | Effect                                        |
|--------------|-----------------------------------------------|
| `make`       | Build the project                             |
| `make clean` | Remove object files and cloned libraries      |
| `make fclean`| `clean` + remove the `cube3D` binary          |
| `make re`    | Full rebuild                                  |
| `make leak`  | Rebuild with `-g` and run under `leaks`       |

### What I learned

- **Raycasting**: implementing a DDA grid traversal and turning ray distances
  into perspective-correct wall heights.
- **Mathematics — trigonometry & vectors**: representing the camera as a
  direction vector plus a camera plane, and rotating both with a 2D rotation
  matrix to turn and move the player.
- **Texture rendering**: mapping the hit point on a wall to a texture column and
  sampling pixel data to texture each vertical slice.
- **Configuration parsing**: designing the `.cub` file format and the validation
  rules around it (textures, colors, closed map, single player start).
- **Graphics programming with MLX42 & the render loop**: managing windows and
  images, writing pixels directly into an image buffer, and driving everything
  from a per-frame loop hook with keyboard input.

---

## 🇫🇷 Français

### Principe

Cube3D est un **moteur de raycasting**. Le monde est une grille 2D de cases (murs
et espaces vides), mais il est affiché comme une scène 3D vue à travers les yeux
du joueur.

Pour chaque colonne verticale de pixels à l'écran, le moteur lance un rayon depuis
la position du joueur dans la carte. À l'aide d'un parcours **DDA (Digital
Differential Analysis)**, il traverse la grille case par case jusqu'à toucher un
mur. La distance à ce mur détermine la hauteur de la tranche de mur dessinée dans
cette colonne : les murs proches sont dessinés plus hauts, les murs lointains plus
courts — c'est ce qui crée l'illusion de profondeur.

Chaque tranche de mur est texturée en échantillonnant une colonne de la texture
correspondante (Nord / Sud / Est / Ouest, selon le côté touché par le rayon),
tandis que le sol et le plafond sont remplis de couleurs unies.

La boucle de rendu tourne en continu via le `mlx_loop_hook` de MLX42 : elle lit le
clavier, met à jour la position et l'orientation du joueur, efface l'image, relance
tous les rayons et affiche la nouvelle image.

### Format de carte .cub

> Remarque : dans l'état actuel du projet, la carte est **codée en dur** dans
> `src/main.c` (`worldMap[24][24]`) et les textures/couleurs sont chargées depuis
> des chemins fixes. Le parseur `.cub` est la prochaine étape (voir `TODO.md`).
> Le format ci-dessous décrit la configuration `.cub` cible visée par le moteur.

Un fichier de scène `.cub` contient, dans n'importe quel ordre, les éléments de
configuration suivis de la carte (la carte doit venir en **dernier**) :

```
NO ./chemin/vers/texture_nord.png
SO ./chemin/vers/texture_sud.png
WE ./chemin/vers/texture_ouest.png
EA ./chemin/vers/texture_est.png

F 220,100,0
C 225,30,0

111111
100001
101001
1000N1
111111
```

| Identifiant | Signification                                         |
|-------------|-------------------------------------------------------|
| `NO`        | Texture du mur Nord                                   |
| `SO`        | Texture du mur Sud                                    |
| `WE`        | Texture du mur Ouest                                  |
| `EA`        | Texture du mur Est                                    |
| `F`         | Couleur du sol, `R,G,B` (0–255 chacun)               |
| `C`         | Couleur du plafond, `R,G,B` (0–255 chacun)           |

Caractères de la carte :

| Caractère       | Signification                                              |
|-----------------|-----------------------------------------------------------|
| `1`             | Mur                                                       |
| `0`             | Espace vide (praticable)                                  |
| ` ` (espace)    | Vide / extérieur de la carte                              |
| `N` `S` `E` `W` | Position de départ et orientation du joueur (un seul)     |

La carte doit être **fermée / entourée de murs** (`1`).

### Commandes

| Touche          | Action                       |
|-----------------|------------------------------|
| `W`             | Avancer                      |
| `S`             | Reculer                      |
| `Q`             | Pas de côté à gauche         |
| `D`             | Pas de côté à droite         |
| `←` Flèche gauche | Tourner la caméra à gauche |
| `→` Flèche droite | Tourner la caméra à droite |
| `Échap`         | Quitter                      |
| Fermeture fenêtre | Quitter                    |

### Compilation & Lancement

**Dépendances**

- Un compilateur C (`cc` / `clang`), `make`, `cmake` et `git`.
- **GLFW** (requis par MLX42). Sur macOS avec Homebrew : `brew install glfw`.
  Sur Linux/Debian : `sudo apt install libglfw3-dev`.
- MLX42 et la libft du projet (`LIB_C`) sont clonées et compilées
  automatiquement par le `Makefile`.

**Compilation**

```bash
make
```

Cela récupère et compile `MLX42` et `LIB_C`, puis génère le binaire `cube3D`.

**Lancement**

```bash
./cube3D
```

> La carte est actuellement codée en dur, aucun argument n'est donc requis. Une
> fois le parseur `.cub` en place, le programme se lancera avec
> `./cube3D maps/scene.cub`.

**Cibles utiles du Makefile**

| Cible        | Effet                                              |
|--------------|----------------------------------------------------|
| `make`       | Compiler le projet                                 |
| `make clean` | Supprimer les fichiers objets et les libs clonées  |
| `make fclean`| `clean` + supprimer le binaire `cube3D`            |
| `make re`    | Recompilation complète                             |
| `make leak`  | Recompiler avec `-g` et lancer sous `leaks`        |

### Ce que ça m'a apporté

- **Le raycasting** : implémenter un parcours de grille DDA et transformer les
  distances des rayons en hauteurs de murs correctes en perspective.
- **Les mathématiques — trigonométrie & vecteurs** : représenter la caméra par un
  vecteur de direction et un plan caméra, puis les faire pivoter avec une matrice
  de rotation 2D pour tourner et déplacer le joueur.
- **Le rendu de textures** : projeter le point d'impact sur un mur vers une colonne
  de texture et échantillonner les pixels pour texturer chaque tranche verticale.
- **Le parsing de configuration** : concevoir le format de fichier `.cub` et les
  règles de validation associées (textures, couleurs, carte fermée, unique
  position de départ).
- **La programmation graphique avec MLX42 & la boucle de rendu** : gérer fenêtres
  et images, écrire directement les pixels dans un buffer image, et tout piloter
  depuis un hook de boucle exécuté à chaque frame avec la saisie clavier.
