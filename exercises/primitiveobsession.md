The `suit` attribute in our `Card` class exhibits **primitive obsession**. 

This is a common code smell where primitive data types (like `char` in this case) are used to represent a concept or domain-specific information (such as a suit of a playing card). 

This can make the code less expressive, harder to maintain, and more prone to errors.

---

### Why It's Primitive Obsession:
1. **Lack of Domain Semantics**:
   - `char` is a generic type and doesn't inherently convey the idea of a "suit."
   - Someone reading the code might not immediately understand that `suit` is expected to represent one of `'C'`, `'H'`, `'D'`, or `'S'`.

2. **Validation Responsibility**:
   - You're implicitly relying on the code to handle validation (`switch` cases assume valid suits).
   - There's no guarantee that `suit` can't be set to an invalid value, like `'X'`.

3. **Repetition**:
   - You're repeating logic for suits (e.g., in `printCardL1`, `printCardL2`, etc.).
   - If you decide to add new suits or change how suits are represented, you'd have to modify multiple places.

---

### How to Refactor:
You can refactor `suit` to use a dedicated class or enum. Here's how:

#### **Option 1: Use an Enum**
Define an enum for suits:
```cpp
enum class Suit {
    Clubs,
    Hearts,
    Diamonds,
    Spades
};
```

Update the `Card` class:
```cpp
#include "headers/card.h"
#include <iostream>

Card::Card() : number(0), suit(Suit::Clubs), block(false) {}

Card::Card(int no, Suit s) : number(no), suit(s), block(false) {}

Suit Card::getSuit() {
    return suit;
}

void Card::setSuit(Suit s) {
    suit = s;
}

void Card::printCardL1() {
    switch (suit) {
        case Suit::Clubs: std::cout << "| :(): |"; break;
        case Suit::Hearts: std::cout << "| (\\/) |"; break;
        case Suit::Diamonds:
        case Suit::Spades: std::cout << "| :/\\: |"; break;
    }
}
```

#### **Option 2: Use a Suit Class**
Create a dedicated `Suit` class:
```cpp
class Suit {
private:
    char symbol; // 'C', 'H', 'D', 'S'

public:
    Suit(char s) {
        if (s != 'C' && s != 'H' && s != 'D' && s != 'S') {
            throw std::invalid_argument("Invalid suit");
        }
        symbol = s;
    }

    char getSymbol() const { return symbol; }

    void printL1() const {
        switch (symbol) {
            case 'C': std::cout << "| :(): |"; break;
            case 'H': std::cout << "| (\\/) |"; break;
            case 'D':
            case 'S': std::cout << "| :/\\: |"; break;
        }
    }
};
```

Use the `Suit` class in `Card`:
```cpp
class Card {
private:
    int number;
    Suit suit;
    bool block;

public:
    Card() : number(0), suit('C'), block(false) {}
    Card(int no, char s) : number(no), suit(s), block(false) {}

    Suit getSuit() const { return suit; }
    void setSuit(char s) { suit = Suit(s); }

    void printCardL1() {
        suit.printL1();
    }
};
```

---

### Benefits of Refactoring:
1. **Improved Readability**:
   - Code becomes more self-documenting (`Suit` is FAR more descriptive than `char`).

2. **Error Prevention**:
   - Invalid suits are caught at compile-time (using enums) or runtime (using the `Suit` class if we were to use a class instead).

3. **Encapsulation**:
   - Suit-related behavior (like printing) is encapsulated within the `Suit` enum, reducing duplication.

4. **Scalability**:
   - Adding new suits or changing suit-related logic is easier and localized.

---

### Conclusion:
Refactoring `suit` will make your code more robust and expressive, aligning it with best practices and avoiding primitive obsession. Using an `enum class` is the simpler and more common approach for this case.
