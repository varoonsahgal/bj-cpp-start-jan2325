### **Refactoring Exercise: Extract a Hand Class**

---

#### **Objective**
Refactor the existing codebase to extract a `Hand` class. The `Hand` class will encapsulate logic related to managing a collection of cards (e.g., adding, clearing, calculating total values) and printing the hand.

---

### **Setup**
Assume you are starting with the original code you uploaded, where:
- The `Human` class directly manages a `std::vector<Card>` (referred to as `hand`).

---

### **Instructions**
Follow these steps to extract a `Hand` class while preserving the existing functionality:

#### **1. Create a `Hand` Class**
1. **Encapsulate the `hand` vector**:
   - Move the `std::vector<Card>` from the `Human` class to the `Hand` class.
   - Add methods to manage cards (e.g., adding, clearing).
   - Include a method to calculate the total value of the cards.

2. **Define a `print` method**:
   - Move the card printing logic from `Human` to `Hand`.
   - Ensure the `Hand` class handles all the card printing details.

#### **2. Update the `Human` Class**
1. **Replace `std::vector<Card>` with `Hand`**:
   - Replace all occurrences of `std::vector<Card>` in `Human` with the new `Hand` class.
   - Update any methods that interact with `hand` (e.g., adding or clearing cards) to delegate these responsibilities to the `Hand` class.

2. **Remove Redundant Logic**:
   - Eliminate logic for printing cards and managing card totals from the `Human` class.

---

### **Requirements for the Hand Class**
#### **Public Methods**
- `void addCard(const Card& card)`  
  Add a card to the hand.

- `void clear()`  
  Clear all cards from the hand.

- `int getTotalValue() const`  
  Return the total value of the hand.

- `void print() const`  
  Print the hand, using card details (reproduce the existing formatting).

- `const std::vector<Card>& getCards() const`  
  Return the collection of cards in the hand (optional, for future extensibility).

#### **Private Data Members**
- `std::vector<Card> cards`: Stores the collection of cards in the hand.
- `int totalValue`: Cached total value of the cards in the hand.

---

### **Example Scenarios**
1. **Adding a Card**:
   ```cpp
   Hand hand;
   Card card(10, 'H'); // Ten of Hearts
   hand.addCard(card);
   ```

2. **Clearing the Hand**:
   ```cpp
   hand.clear();
   ```

3. **Printing the Hand**:
   ```cpp
   hand.print();
   ```

---

### **Exercise Tasks**
1. **Define the `Hand` Class**:
   - Create a `Hand` header and implementation file.
   - Move the `std::vector<Card>` and related operations from `Human` to `Hand`.

2. **Refactor the `Human` Class**:
   - Replace direct management of the `hand` vector with a `Hand` instance.
   - Delegate all hand-related responsibilities (e.g., adding cards, calculating totals, printing) to the `Hand` class.

3. **Test Your Refactor**:
   - Ensure all existing functionalities work as before.
   - Verify that `Human` no longer handles any hand-related operations directly.

---

### **Reflection Questions**
1. How did encapsulating the `hand` vector in the `Hand` class improve code readability and maintainability?
2. What additional functionalities could you now add to the `Hand` class without modifying `Human` or `Card`?
3. How might this refactoring support the **Single Responsibility Principle** and **Open/Closed Principle**?

---

### **Expected Outcome**
By the end of the exercise, you should have a `Hand` class that encapsulates all card-related operations for a hand, making the `Human` class simpler and adhering to better design principles.
