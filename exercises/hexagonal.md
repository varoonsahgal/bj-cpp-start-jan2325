Hexagonal/clean architecture - Card class
---
Let's move the console-based display code out of Card and into a new class called `ConsoleCard`.  

The `printCardL1` and `printCardL2` methods specifically should be moved.

Note of course that you don't want to break your tests, and be sure that any existing calls to those functions get updated as well.

Our goal is to make the Card class "pure-domain" in the sense that it has not dependency on the outside world.  So, it should not longer need the iostream include.

You may also need to update the CMAKELists.txt file to accomodate any new files - namely in the sections where its creating the executables.

Hexagonal/clean architecture - Game class
---
Next do the same thing for the Game class as well!  Move all console based code into a new class called `ConsoleGame`.  Then update all references as well.

This will help us build towards a Hexagonal architecture.  If you think there are other classes that need to remove any display logic then refactor those as well!

Refactoring to use the `ConsoleCard` and `ConsoleGame` classes applies several **SOLID principles**, including:

---

How does this refactoring apply SOLID principles?  Read below...

### **1. Single Responsibility Principle (SRP)**
**Principle**: A class should have only one reason to change.

- **How it's applied**:
  - Previously, the `Card` class was responsible for both representing the data of a card (e.g., its number and suit) and rendering the card to the console.
  - By introducing the `ConsoleCard` class, we separated these responsibilities:
    - **`Card`**: Focuses solely on encapsulating the card's data (number, suit, block).
    - **`ConsoleCard`**: Handles rendering and display-related logic.

- **Benefit**:
  - Changes to how cards are rendered no longer impact the `Card` class.
  - Changes to the card data structure (e.g., adding new suits) don't affect rendering logic.

---

### **2. Open/Closed Principle (OCP)**
**Principle**: Classes should be open for extension but closed for modification.

- **How it's applied**:
  - The `ConsoleCard` class encapsulates the rendering logic for `Card`. If you later decide to add another rendering method (e.g., a GUI or file-based renderer), you can do so by creating a new class without modifying either the `Card` or `ConsoleCard` classes.
    - Example: Adding a `GUICard` class for GUI rendering doesn't require changes to `ConsoleCard`.

- **Benefit**:
  - Existing code remains stable while allowing easy extension of functionality.

---

### **3. Interface Segregation Principle (ISP)**
**Principle**: A class should not be forced to implement interfaces it doesn't use.

- **How it's applied**:
  - By separating the rendering logic into `ConsoleCard`, the `Card` class no longer has unused methods like `printCardL1` and `printCardL2`.
  - Classes interacting with `Card` only deal with its core functionality (e.g., getting the number or suit) and are not burdened by methods related to rendering.

- **Benefit**:
  - Simplifies the `Card` class interface, making it more focused and easier to understand.

---

### **4. Dependency Inversion Principle (DIP)**
**Principle**: High-level modules should not depend on low-level modules; both should depend on abstractions.

- **How it's applied**:
  - While not explicitly implemented, refactoring to `ConsoleCard` lays the groundwork for applying DIP. For example, you could abstract rendering logic further into an interface (e.g., `CardRenderer`) so that the game logic or any other high-level module depends on a generic renderer, not directly on `ConsoleCard`.

    ```cpp
    class CardRenderer {
    public:
        virtual void printCardL1(const Card& card) = 0;
        virtual void printCardL2(const Card& card) = 0;
        virtual char getPrintNumber(const Card& card) = 0;
        virtual ~CardRenderer() {}
    };
    ```

- **Benefit**:
  - Encourages flexibility in swapping rendering implementations without tightly coupling high-level modules (e.g., `Game`) to a specific renderer like `ConsoleCard`.

---

### Summary of Applied Principles:
| Principle                  | How It's Applied                                                                                                                                     |
|----------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Single Responsibility**  | `Card` and `ConsoleCard` now have distinct responsibilities: data representation and rendering, respectively.                                         |
| **Open/Closed**            | Adding new rendering logic (e.g., GUI rendering) does not require modifying existing classes (`Card` or `ConsoleCard`).                              |
| **Interface Segregation**  | `Card` is no longer responsible for rendering methods, keeping its interface clean and focused on card data.                                         |
| **Dependency Inversion**   | (Partial) Rendering logic could depend on an abstraction, allowing easy substitution of rendering implementations (e.g., console, GUI, or file-based). |

This refactoring improves the design by adhering to SOLID principles, making the code more modular, maintainable, and extensible. 
