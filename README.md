# Cub3D
![norminette](https://github.com/Chloekkk/minishell/workflows/norminette/badge.svg)

### First-person 3D representation of a maze using raycasting, similar to Wolfenstein 3D (1992)

## 💻 DONE

##### It's just a game template. You can simply walk around the map, control on/off lamp and break barrels with your body.

 ![Cub3D](https://github.com/Cleonia21/Cub3d/raw/88f066af53fabc5c04cb5a5ecb832e778909fc74/preview.png)

#### You can now create your own map by following this norm:

| Object         | Code          |
| -------------  |:-------------:|
| `NO`           | path to xpm texture file|
| `SO`           | path to xpm texture file|
| `WE`           | path to xpm texture file|
| `EA`           | path to xpm texture file|
| `F`            | numeric encoding in the format R,G,B for floor|
| `C`            | numeric encoding in the format R,G,B for ceiling|
| `1`            | wall          |
| `0`            | empty         |
| `N`/`E`/`W`/`S`| player initial position + orientation|

#### Commands

| KEY           | Action        |
| ------------- |:-------------:|
| `ESC`         | exit game     |
| `A`           | move left     |
| `D`           | move right    |
| `W`           | move forward  |
| `S`           | move backward |
| `MOUSE`       | turn right    |
| `MOUSE`       | turn left     |
| `ENTER`       | fog           |
| `SPACE`       | lamp control  |

## 📦 Installation
  ```shell
  git clone https://github.com/mlagranzh/cub3d
  ```

## 🚀 Run
  ```shell
  make bonus && ./cub3d_bonus maps/map.cub
  ```

## 📖 Wiki
- ### [raycasting_wiki](https://lodev.org/cgtutor/raycasting.html)

## 💼 Do with
- ### [Cleonia](https://github.com/Cleonia21/)
