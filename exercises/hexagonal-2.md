Implementing the **Ports and Adapters (Hexagonal Architecture)** pattern involves creating a **port** as an abstraction for database interactions, ensuring that domain classes like `Game`, `Player`, or `Hand` do not depend directly on the database. Here's a detailed breakdown and all the code required to implement this in the Blackjack game:

---

## **1. Define the Goal**
- **Objective**: Allow the Blackjack game to interact with a database (e.g., saving/loading game state) without coupling the domain logic (e.g., `Game`, `Player`, `Hand`) to the database.
- **Approach**: Use an interface (port) to define the database operations and implement it in an adapter class. The `Game` class will interact with the database via this port.

---

## **2. Plan the Structure**
### **Core Concepts**
1. **Port**: Defines the operations the database must support (e.g., `saveGame`, `loadGame`).
2. **Adapter**: Implements the port, providing the actual database logic (e.g., interacting with a file-based database).
3. **Dependency Injection**: The `Game` class depends on the port, allowing the adapter to be injected at runtime.

---

## **3. Implement the Port**
### **File**: `database_port.hpp`
Defines the database operations.

```cpp
#ifndef DATABASE_PORT_HPP
#define DATABASE_PORT_HPP

#include "player.hpp"
#include "dealer.hpp"
#include "hand.hpp"
#include <string>

class DatabasePort {
public:
    virtual ~DatabasePort() = default;

    // Save the current game state
    virtual void saveGame(const Player& player, const Dealer& dealer, const Hand& deck, const std::string& filename) = 0;

    // Load a saved game state
    virtual bool loadGame(Player& player, Dealer& dealer, Hand& deck, const std::string& filename) = 0;
};

#endif
```

**Talking Points**:
- The port is an abstract interface, ensuring no direct database dependency in domain classes.

---

## **4. Implement the Adapter**
### **File**: `file_database_adapter.hpp`
Implements `DatabasePort` using a simple file-based database.

```cpp
#ifndef FILE_DATABASE_ADAPTER_HPP
#define FILE_DATABASE_ADAPTER_HPP

#include "database_port.hpp"
#include <fstream>
#include <stdexcept>

class FileDatabaseAdapter : public DatabasePort {
public:
    void saveGame(const Player& player, const Dealer& dealer, const Hand& deck, const std::string& filename) override {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file for saving.");
        }

        // Save player data
        savePlayer(file, player);

        // Save dealer data
        saveDealer(file, dealer);

        // Save deck data
        saveDeck(file, deck);

        file.close();
    }

    bool loadGame(Player& player, Dealer& dealer, Hand& deck, const std::string& filename) override {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            return false; // File not found
        }

        // Load player data
        loadPlayer(file, player);

        // Load dealer data
        loadDealer(file, dealer);

        // Load deck data
        loadDeck(file, deck);

        file.close();
        return true;
    }

private:
    void savePlayer(std::ofstream& file, const Player& player) {
        int cash = player.getCash();
        int wins = player.getWins();
        int loses = player.getLoses();
        size_t nameLength = player.getName().size();

        file.write(reinterpret_cast<char*>(&cash), sizeof(cash));
        file.write(reinterpret_cast<char*>(&wins), sizeof(wins));
        file.write(reinterpret_cast<char*>(&loses), sizeof(loses));
        file.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        file.write(player.getName().data(), nameLength);
    }

    void loadPlayer(std::ifstream& file, Player& player) {
        int cash, wins, loses;
        size_t nameLength;
        std::string name;

        file.read(reinterpret_cast<char*>(&cash), sizeof(cash));
        file.read(reinterpret_cast<char*>(&wins), sizeof(wins));
        file.read(reinterpret_cast<char*>(&loses), sizeof(loses));
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

        name.resize(nameLength);
        file.read(&name[0], nameLength);

        player.setName(name);
        player.addCash(cash - player.getCash()); // Adjust cash
        player.incrementWins(); // Increment wins if needed
        player.incrementLoses(); // Increment loses if needed
    }

    void saveDealer(std::ofstream& file, const Dealer& dealer) {
        const auto& cards = dealer.getCards();
        size_t cardCount = cards.size();
        file.write(reinterpret_cast<char*>(&cardCount), sizeof(cardCount));
        for (const auto& card : cards) {
            file.write(reinterpret_cast<const char*>(&card), sizeof(card));
        }
    }

    void loadDealer(std::ifstream& file, Dealer& dealer) {
        size_t cardCount;
        file.read(reinterpret_cast<char*>(&cardCount), sizeof(cardCount));
        for (size_t i = 0; i < cardCount; ++i) {
            Card card;
            file.read(reinterpret_cast<char*>(&card), sizeof(card));
            dealer.addCard(card);
        }
    }

    void saveDeck(std::ofstream& file, const Hand& deck) {
        const auto& cards = deck.getCards();
        size_t cardCount = cards.size();
        file.write(reinterpret_cast<char*>(&cardCount), sizeof(cardCount));
        for (const auto& card : cards) {
            file.write(reinterpret_cast<const char*>(&card), sizeof(card));
        }
    }

    void loadDeck(std::ifstream& file, Hand& deck) {
        size_t cardCount;
        file.read(reinterpret_cast<char*>(&cardCount), sizeof(cardCount));
        for (size_t i = 0; i < cardCount; ++i) {
            Card card;
            file.read(reinterpret_cast<char*>(&card), sizeof(card));
            deck.addCard(card);
        }
    }
};

#endif
```

---

## **5. Update the `Game` Class**
Inject the `DatabasePort` dependency into the `Game` class.

**Changes to `game.hpp`**:
```cpp
class Game {
private:
    Player player;
    Dealer dealer;
    Deck deck;
    DatabasePort& database; // Injected dependency

public:
    Game(DatabasePort& db) : database(db) {}

    void saveGame(const std::string& filename) {
        database.saveGame(player, dealer, deck, filename);
    }

    void loadGame(const std::string& filename) {
        if (!database.loadGame(player, dealer, deck, filename)) {
            throw std::runtime_error("Failed to load game.");
        }
    }
};
```

---

## **6. Example Usage**
### **Main File**
```cpp
#include "file_database_adapter.hpp"
#include "game.hpp"

int main() {
    FileDatabaseAdapter dbAdapter;
    Game game(dbAdapter);

    // Save game state
    game.saveGame("game_state.dat");

    // Load game state
    try {
        game.loadGame("game_state.dat");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
```

---

## **Benefits of This Approach**
1. **Decoupling**: Domain classes (`Game`, `Player`, etc.) do not directly interact with the database.
2. **Testability**: You can mock `DatabasePort` for unit tests.
3. **Flexibility**: Swap the adapter (e.g., file-based, SQL database) without modifying domain logic.


---

### **SOLID Principles Applied**
Implementing the **Ports and Adapters** pattern in your Blackjack game ensures the architecture adheres to several **SOLID** principles:

---

#### **1. Single Responsibility Principle (SRP)**
**Definition**: A class should have only one reason to change.

- **Application**:
  - The `DatabasePort` interface defines what database operations are required, but it does not handle the specifics of implementation.
  - The `FileDatabaseAdapter` class handles only the specifics of interacting with the file-based database.
  - The `Game` class focuses on domain-specific game logic and delegates database operations to the port.

- **Benefit**:
  - Changes to the database logic (e.g., switching to an SQL database) do not require changes in the `Game`, `Player`, or `Dealer` classes.

---

#### **2. Open/Closed Principle (OCP)**
**Definition**: Classes should be open for extension but closed for modification.

- **Application**:
  - The `Game` class depends on the `DatabasePort` interface, allowing the database implementation to be swapped out without modifying the `Game` class.
  - For example, replacing `FileDatabaseAdapter` with an `SQLDatabaseAdapter` requires no changes to `Game`.

- **Benefit**:
  - You can extend the system with new database adapters without modifying existing code.

---

#### **3. Liskov Substitution Principle (LSP)**
**Definition**: Subtypes must be substitutable for their base types.

- **Application**:
  - The `FileDatabaseAdapter` class is a concrete implementation of `DatabasePort`. It can be substituted with any other adapter implementing `DatabasePort` (e.g., `SQLDatabaseAdapter`) without breaking the `Game` class.

- **Benefit**:
  - Ensures consistency and prevents runtime errors when using different database implementations.

---

#### **4. Interface Segregation Principle (ISP)**
**Definition**: A class should not be forced to depend on methods it does not use.

- **Application**:
  - The `DatabasePort` interface is designed to include only the methods necessary for database interactions (`saveGame` and `loadGame`). It does not include unrelated functionality.
  - The `Game` class interacts only with the specific methods it needs via `DatabasePort`.

- **Benefit**:
  - Promotes a clean separation of responsibilities and ensures minimal coupling between components.

---

#### **5. Dependency Inversion Principle (DIP)**
**Definition**: High-level modules should not depend on low-level modules but on abstractions.

- **Application**:
  - The `Game` class depends on the `DatabasePort` abstraction rather than a specific database implementation like `FileDatabaseAdapter`.
  - The actual database implementation is injected into the `Game` class at runtime.

- **Benefit**:
  - Decouples the `Game` class from specific database implementations, making the system more flexible and testable.

---

### **Law of Demeter (LoD)**
**Definition**: A class should only interact with its immediate dependencies and avoid "talking to strangers."

**Application**:
- By using a port (`DatabasePort`), the `Game` class interacts with a single dependency to perform database operations, rather than directly interacting with low-level database code (e.g., file I/O or SQL queries).
- Instead of:
  ```cpp
  file.open("data.dat", std::ios::binary);
  // Logic to save/load directly in Game
  ```
  The `Game` class delegates the responsibility:
  ```cpp
  database.saveGame(player, dealer, deck, "data.dat");
  ```

**Benefit**:
- This minimizes coupling and ensures the `Game` class adheres to the **Law of Demeter**, as it only communicates with its direct dependency (`DatabasePort`) and not with the low-level implementation (`FileDatabaseAdapter`).

---

### **Summary of SOLID and LoD**
1. **SRP**: Each class has a clear responsibility.
2. **OCP**: New adapters can be added without modifying existing classes.
3. **LSP**: Any adapter implementing `DatabasePort` can replace `FileDatabaseAdapter`.
4. **ISP**: `DatabasePort` is focused only on necessary methods.
5. **DIP**: High-level domain classes depend on an abstraction (`DatabasePort`) instead of a specific implementation.

By adhering to these principles and factoring in the **Law of Demeter**, your code becomes:
- **More modular**: Components are easier to test, reuse, and replace.
- **More maintainable**: Changes to one part of the system have minimal impact on others.
- **Extensible**: New database implementations can be added without altering domain logic.


