Let's write some tests - go ahead and modify the blackjack_test.cpp file that's already in the tests folder.
---

### **Exercise 1: 🃏 Testing Card Default Constructor**  
```cpp
TEST(CardTest, DefaultConstructorInitializesCorrectly) {
    // 🧐 Hint: The default constructor initializes:
    // - `number` to 0.
    // - `suit` to `'\0'` (null character).
    // - `block` to `false`.
    // ✅ Verify that these default values are set correctly.
}
```

---

### **Exercise 2: 🛠️ Testing Card Parameterized Constructor**  
```cpp
TEST(CardTest, ParameterizedConstructorInitializesCorrectly) {
    // 🧐 Hint: Use the parameterized constructor to create a Card object with:
    // - Specific values for `number` and `suit` as `char`.
    // - ✅ Verify that `number` and `suit` are set correctly.
    // - ⚠️ Check edge cases: invalid values for `number` (e.g., negative or >13) or `suit` (non-standard characters).
}
```

---

### **Exercise 3: ♠️ Testing Suit Character Validity**  
```cpp
TEST(CardTest, AcceptsAndHandlesSuitCharacters) {
    // 🧐 Hint: Test how the Card class handles different `suit` values:
    // - ✅ Verify that it accepts 'H', 'D', 'C', and 'S' as valid suits.
    // - ⚠️ Check edge cases with invalid `char` values (e.g., 'Z', '!', or '0').
    // - 🤔 Consider how the class behaves when given invalid suits. Does it throw an exception? Set a default suit?
}
```

---

### **Exercise 4: 🃏🃏 Testing Deck Initialization**  
```cpp
TEST(DeckTest, InitializesWithCorrectCards) {
    // 🧐 Hint: When a Deck object is initialized:
    // - ✅ Verify that all 52 cards are present (correct `number` and `suit` combinations).
    // - ✅ Check that no duplicate cards exist.
    // - ♣️ Ensure suits are represented as 'H', 'D', 'C', and 'S' only.
}
```

---

### **Exercise 5: 🎨 Testing Card Printing (L1 and L2)**  
```cpp
TEST(CardTest, PrintsCardCorrectly) {
    // 🧐 Hint: Test the `printCardL1` and `printCardL2` methods:
    // - ✅ Create Card objects with various `suit` values ('H', 'D', 'C', 'S').
    // - 🖼️ Verify that the printed output matches the expected visual representation.
    // - ⚠️ Consider edge cases with invalid `suit` values and how the print functions handle them.
}
```

---

### **Exercise 6: 🔄 Testing Deck Shuffle**  
```cpp
TEST(DeckTest, ShufflesDeckRandomly) {
    // 🧐 Hint: After shuffling a Deck:
    // - ✅ Verify that all cards remain present (correct number and unique values).
    // - 🔀 Ensure that the order of cards changes after shuffling.
    // - 🔄 Run the shuffle multiple times and verify that the order is different across runs.
}
```

---

These exercises with emojis make the learning process more engaging and fun while still focusing on critical testing concepts. 🎉
