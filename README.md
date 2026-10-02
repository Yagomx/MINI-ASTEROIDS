# 🚀 Mini Asteroids (C++ Console Game)

A console-based arcade video game developed in **C++**, inspired by Atari's classic 1979 vector game. The project implements Object-Oriented Programming (OOP) principles, custom console buffer manipulation, and real-time keyboard interaction.

## 🛠 Technologies & Concepts
* **Language:** C++.
* **Paradigm:** Object-Oriented Programming (OOP)
* **Environment:** Console application (Windows API / ASCII graphics)
* **Key Concepts:** Classes, constructors, pointers/references, lists, collision detection, and modular architecture using header files.

## 🎯 Game Objectives & Mechanics
* **The Player:** Controls a spaceship navigating the console screen, capable of moving in multiple directions and firing projectiles.
* **The Asteroids:** Obstacles generated randomly that move downwards; players must destroy or dodge them.
* **Health & Lives System:** The ship tracks remaining lives and hit points (hearts), handling damage animations and respawn logic upon collision.

## 🧩 Architecture & Classes
The project is modularized using custom classes to separate logic and responsibilities:
1. **`NAVE` (Ship Class):** Manages player coordinates, drawing/erasing via ASCII characters, keyboard input (`kbhit`, `getch`), and health states.
2. **`asteroid` (Asteroid Class):** Handles obstacle trajectory, screen boundaries, and collision physics with the player's ship.
3. **`bala` (Bullet Class):** Controls projectile movement upwards and out-of-bounds detection.
4. **Console Utilities:** Custom functions for cursor hiding (`Ocultar_cursor`), border rendering (`pintar_limites`), and full-screen automation (`fullscreen`).

---
*Developed as part of Programming I coursework at Universidad Politécnica de San Luis Potosí (UPSLP).*
