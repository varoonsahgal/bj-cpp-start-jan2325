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
