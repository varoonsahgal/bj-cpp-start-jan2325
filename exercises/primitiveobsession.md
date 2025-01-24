The `suit` attribute in our `Card` class exhibits **primitive obsession**. 

This is a common code smell where primitive data types (like `char` in this case) are used to represent a concept or domain-specific information (such as a suit of a playing card). 

This can make the code less expressive, harder to maintain, and more prone to errors.

---

### Why It's Primitive Obsession:
1. **Lack of Domain Semantics**:
   - `char` is a generic type and doesn't inherently convey the idea of a "suit."
   -  `char` also has no inherent boundaries that are relevant to our domain problem (domain == the game of Blackjack)
   - Someone reading the code might not immediately understand that `suit` is expected to represent one of `'C'`, `'H'`, `'D'`, or `'S'`.

2. **Validation Responsibility**:
   - You're implicitly relying on the code to handle validation (`switch` cases assume valid suits).
   - There's no guarantee that `suit` can't be set to an invalid value, like `'X'`.

3. **Repetition**:
   - You'll often end up repeating logic

---

### YOUR CHALLENGE EXERCISE:
Here's what you need to do:

- Refactor `suit` in the card class, to use an enum class in CPP instead of a `char`. Here's a reference on enums in CPP: https://en.cppreference.com/w/cpp/language/enum

- Define an enum for suits, then modify the constructor for the Card class to use that enum.  

- Then, update any calls to the Card constructor.  Finally, test out the project and see if it works.




---
Fixing **primitive obsession** (e.g., replacing the use of `char` for suits with a `Suit` type) applies several **SOLID principles** because it improves type safety, enhances code readability, and creates a more flexible and maintainable design. Here’s how it aligns with SOLID principles:

---

### **1. Single Responsibility Principle (SRP)**

**Principle**: A class or module should have only one reason to change.

**How It's Applied**:
- **Before Fixing**:
  - The `char` type for suits entangles multiple responsibilities:
    - Representing a card suit.
    - Encoding business rules about valid suits.
    - Converting suits to printable values.
  - Changes to how suits are represented (e.g., adding new suits) would require modifying multiple parts of the code that deal with `char`.

- **After Fixing**:
  - By introducing a dedicated `Suit` enum or class, all suit-related logic is centralized. For example:
    - Validation (`Is the suit valid?`).
    - Representation (`What are the possible suits?`).
    - Expansion (`Add a new suit easily`).

**Benefit**:
- The responsibility of representing and validating suits is now encapsulated within the `Suit` type, isolating it from other classes like `Card` or `ConsoleCard`.

---

### **2. Open/Closed Principle (OCP)**

**Principle**: A class should be open for extension but closed for modification.

**How It's Applied**:
- **Before Fixing**:
  - Using `char` for suits means that adding a new suit (e.g., `Jokers`) requires modifying every piece of code that deals with `char` values (e.g., comparisons, printing logic).

- **After Fixing**:
  - By using a `Suit` enum or class, adding a new suit involves only:
    - Extending the `Suit` definition (e.g., adding a new enum value or class constant).
    - Adding rendering or behavior logic in one centralized place if needed.
  - The existing `Card` or `ConsoleCard` classes remain unchanged.

**Benefit**:
- New functionality is added by extending the `Suit` definition, not by modifying existing code, ensuring stability.

---

### **3. Liskov Substitution Principle (LSP)**

**Principle**: Derived types must be substitutable for their base types without altering the correctness of the program.

**How It's Applied**:
- Fixing primitive obsession enables clear and consistent usage of a type. For example:
  - **Before Fixing**:
    - If `char` is used for suits, different parts of the code could use inconsistent assumptions (e.g., `'H'` vs. `'h'` for hearts, invalid values like `'X'`).
    - This can cause errors when substituting one function or module for another.
  - **After Fixing**:
    - With a `Suit` type, you enforce type constraints:
      - Only valid suits are allowed.
      - Function signatures and interfaces become more predictable and consistent.

**Benefit**:
- Type safety ensures that any code interacting with the `Suit` type behaves as expected, adhering to LSP.

---

### **4. Interface Segregation Principle (ISP)**

**Principle**: A class should not be forced to depend on methods it does not use.

**How It's Applied**:
- While the ISP primarily applies to interfaces, fixing primitive obsession indirectly contributes:
  - **Before Fixing**:
    - A `char`-based solution forces classes or functions to deal with generic string manipulation or validation logic they shouldn’t care about.
  - **After Fixing**:
    - The `Suit` type encapsulates validation and representation logic, so other classes (e.g., `Card` or `ConsoleCard`) interact only with meaningful methods.

**Benefit**:
- Classes like `Card` now depend only on a well-defined interface for suits (`Suit` enum or class) and are not forced to handle low-level validation or assumptions about `char` values.

---

### **5. Dependency Inversion Principle (DIP)**

**Principle**: High-level modules should not depend on low-level modules; both should depend on abstractions.

**How It's Applied**:
- **Before Fixing**:
  - Using `char` directly creates implicit, low-level dependencies throughout the code (e.g., comparisons to `'H'` for hearts or `'C'` for clubs).
- **After Fixing**:
  - Introducing a `Suit` abstraction decouples high-level modules (e.g., `Card`, `Game`) from low-level string operations or assumptions.

**Benefit**:
- High-level modules depend only on the `Suit` abstraction, which can be extended or changed without breaking other parts of the program.

---

### Example of Refactoring Primitive Obsession

#### **Before (Primitive Obsession with `char`):**
```cpp
class Card {
private:
    int number;    // Card number
    char suit;     // Card suit (e.g., 'H', 'C', 'S', 'D')

public:
    Card(int number, char suit) : number(number), suit(suit) {}

    char getSuit() { return suit; }
    void setSuit(char s) { suit = s; }
};
```

#### **After (Fixing Primitive Obsession with `Suit` Enum):**
```cpp
enum class Suit { Hearts, Diamonds, Clubs, Spades };

class Card {
private:
    int number;   // Card number
    Suit suit;    // Card suit

public:
    Card(int number, Suit suit) : number(number), suit(suit) {}

    Suit getSuit() { return suit; }
    void setSuit(Suit s) { suit = s; }
};
```

---

### Benefits of Fixing Primitive Obsession in SOLID Terms:
1. **Improved maintainability**: Changes to `Suit` logic are isolated, adhering to SRP and OCP.
2. **Enhanced readability**: Domain-specific terms like `Suit` make the code more expressive and self-documenting.
3. **Increased safety**: Enums enforce valid values, reducing bugs caused by invalid characters.

By fixing primitive obsession, you directly align with **SRP**, **OCP**, **LSP**, **ISP**, and **DIP**, making the design more robust and extensible. 

- You should also add a new test case to ensure the new constructor works as intended.



---

### Benefits of Refactoring:
1. **Improved Readability**:
   - Code becomes more self-documenting (`Suit` is FAR more descriptive than `char`).

2. **Error Prevention**:
   - Invalid suits are caught at compile-time (using enums) or runtime (using the `Suit` class if we were to use a class instead of an enum).

3. **Encapsulation**:
   - Suit-related behavior (like printing) could be encapsulated within the `Suit` enum, reducing duplication.

4. **Scalability**:
   - Adding new suits or changing suit-related logic is easier and localized.

---

### Conclusion:
Refactoring `suit` will make your code more robust and expressive, aligning it with best practices and avoiding primitive obsession. Using an `enum class` is the simpler and more common approach for this case.
