# Modern C++ First-Person Raycasting Game

## 1. Project Description

This project is a **playable first-person raycasting game** developed in **modern C++ (C++11 or newer)** and designed to run on **GNU/Linux**.

While the project results in a playable game, it is intentionally treated as a **real-time software system** rather than a pure graphics or game-design exercise. The focus is on **clean architecture**, **deterministic behavior**, **explicit resource ownership**, and **maintainable code structure**.

The project is inspired by early FPS raycasting engines (e.g., Wolfenstein 3D) and by the cub3D project, but it is implemented from scratch with modern C++ design principles.

---

## 2. Core Goals

The project must demonstrate:

* Correct use of modern C++ (C++11+)
* Explicit ownership and RAII-based resource management
* Deterministic real-time behavior
* Clear separation of responsibilities
* A fully playable game with a defined objective

The final result must be **fun to play**, **stable**, and **easy to reason about**.

---

## 3. Technical Constraints

* Language: **C++11 or newer**
* Platform: **GNU/Linux**
* Compiler warnings enabled and treated as errors
* No memory leaks, data races, or undefined behavior
* Clean startup and shutdown under all conditions
* No global mutable state

---

## 4. Program Execution

### Launch

```
./game <path_to_map_file>
```

If the argument is missing or invalid, the program must:

* Print a clear error message
* Exit with a non-zero status code

---

## 5. Game Rules

### World

* The world is a 2D grid-based map loaded from a text file
* Valid map tiles:

  * `0` : empty space
  * `1` : wall
  * `P` : player spawn (exactly one required)
  * `E` : exit tile (at least one required)

### Constraints

* The map must be fully enclosed by walls
* The map must be rectangular after parsing
* Invalid maps must prevent the game from starting

---

### Player

* First-person perspective
* Movement:

  * Forward / backward
  * Strafe left / right
* View rotation left and right
* The player must not pass through walls

---

### Objective

* The game is won when the player reaches an exit tile (`E`)
* Upon success:

  * A clear success message is displayed
  * The main loop terminates cleanly

---

## 6. Mandatory Architecture

The codebase **must follow the architecture described below**. Any deviation must be justified.

```
src/
 ├── main.cpp
 ├── engine/
 │    ├── Engine.h / Engine.cpp
 │    ├── GameLoop.h / GameLoop.cpp
 │
 ├── world/
 │    ├── Map.h / Map.cpp
 │    ├── MapLoader.h / MapLoader.cpp
 │
 ├── player/
 │    ├── Player.h / Player.cpp
 │
 ├── raycasting/
 │    ├── Raycaster.h / Raycaster.cpp
 │
 ├── render/
 │    ├── Renderer.h
 │    ├── SimpleRenderer.h / SimpleRenderer.cpp
 │
 ├── input/
 │    ├── Input.h / Input.cpp
 │
 └── utils/
      ├── Time.h / Time.cpp
      ├── Logger.h / Logger.cpp
```

---

## 7. Module Responsibilities (Strict)

### Engine

* Owns the application lifecycle
* Initializes all subsystems
* Starts and stops the game
* Coordinates clean shutdown

Must not:

* Contain rendering logic
* Contain raycasting logic
* Handle input directly

---

### GameLoop

* Runs the main loop
* Enforces a fixed-timestep update
* Calls input, update, and render in the correct order

---

### Map & MapLoader

**Map**

* Stores the world grid
* Provides read-only queries (wall, exit, bounds)

**MapLoader**

* Loads the map file
* Validates all rules
* Constructs a valid `Map`

After initialization, the map is immutable.

---

### Player

* Stores player state (position, direction, FOV)
* Applies movement and rotation
* Enforces collision rules

Must not:

* Read input devices
* Perform rendering

---

### Raycaster

* Computes ray traversal for each screen column
* Determines wall hit distances and orientations

Must not:

* Perform rendering
* Read input
* Depend on windowing APIs

---

### Renderer

* Abstract rendering interface
* Consumes raycasting output
* Draws the scene

Must not:

* Contain game logic
* Modify world or player state

---

### Input

* Reads keyboard and/or mouse input
* Translates input into game actions

Must not:

* Modify player or world state directly

---

## 8. Main Loop & Timing Rules

* The simulation update must use a **fixed timestep**
* Rendering may run at a variable frame rate
* Timing must be measured using `std::chrono`
* The game must remain stable under fluctuating frame rates

---

## 9. Resource Management Rules

* All resources must be managed using RAII
* Ownership must be explicit (`std::unique_ptr`, references)
* No manual `new` / `delete`
* No global mutable state

---

## 10. Diagnostics

The program must track:

* Frames per second (FPS)
* Frame time
* Number of rays cast per frame

Diagnostics must be updated continuously and must not interfere with gameplay.

---

## 11. Optional Features (After Mandatory Part)

* Doors that open and close
* Enemies with simple AI
* Pickups or inventory
* Minimap or HUD

Optional features must respect all architectural rules.

---

## 12. Development Rules

* Implement one subsystem at a time
* Reach a playable state as early as possible
* Prefer simple, correct solutions over complex ones
* If a system cannot be explained clearly, it is too complex

---

## 13. Final Note

This project is intentionally designed to be **both fun and disciplined**.

The goal is not to build a perfect engine, but to build a **complete, playable, well-structured real-time program** that demonstrates solid C++ engineering fundamentals.
