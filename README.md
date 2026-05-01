# Buzz Bombers (SFML 2D Game)

This is a 2D arcade-style game inspired by Buzz Bombers, implemented in C++ using SFML.

The player controls a spray gun to shoot bees, avoid obstacles, and survive through multiple levels with increasing difficulty.

IMPORTANT:
This project is designed to run on Linux (Ubuntu). Due to how the code is written (SFML setup, file paths, and linking),
it may not work correctly on Windows without modifications.

---

FEATURES

- Player vs AI-controlled bees
- Multiple enemy types (regular and fast bees)
- Shooting mechanics with limited bullets
- Collision detection system
- Obstacles (honeycombs, red combs, flowers)
- Power-ups (speed and size changes)
- Lives system
- Multiple levels including boss level
- Sound effects and background music
- Scoreboard stored in record.txt

---

REQUIREMENTS

Install SFML on Ubuntu:

sudo apt update
sudo apt install libsfml-dev

---

COMPILE

g++ buzz.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

---

RUN

./game

---

CONTROLS

Left Arrow  - Move Left
Right Arrow - Move Right
Spacebar    - Shoot
Enter       - Select
Esc         - Exit

---

GAMEPLAY

Shoot bees to earn points and prevent them from reaching the bottom.
Avoid obstacles and manage your bullets carefully.
Progress through levels with increasing difficulty.

Lose when:
- You run out of lives
- Too many obstacles reach the ground

---

FILES

buzz.cpp      -> main game code
record.txt    -> stores high scores
Textures/     -> sprites
Music/        -> background music
Sound Effects -> audio files

---

NOTES

- Works best on Ubuntu/Linux
- Requires SFML installed
- Assets must be in correct folders
- Resolution: 960 x 640
- FPS capped at 60

---

FUTURE IMPROVEMENTS

- Windows support
- Better UI
- Difficulty levels
- Multiplayer mode

---

Author: Your Name
