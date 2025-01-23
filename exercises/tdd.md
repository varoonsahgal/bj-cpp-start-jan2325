## TDD -  Adding an `isFaceCard` Method: A Fun TDD Adventure! 🃏✨

Let's embark on a journey to add an `isFaceCard` method to your `Card` class using **Test-Driven Development (TDD)**. Ready? Let’s dive in! 🚀

---

### Step 1: Write the Test First 🛠️  
Before we start coding the method, let’s write a test to define what `isFaceCard` should do. Imagine you're the **teacher for your code**: What questions would you ask to check if a card is a face card? Write a test that:
- ✅ Checks if Jack, Queen, and King are identified as face cards.
- ❌ Ensures non-face cards (like 10 or Ace) are NOT identified as face cards.
- ⚠️ Think about edge cases, like invalid numbers (-1 or 20).  

Remember: Your test will fail at first. That’s perfectly fine—failure is the first step to success! 🌱

---

### Step 2: Add a Placeholder Method 📄  
Now, add a **placeholder method** to your `Card` class. This is like reserving a seat at a restaurant—you're telling your code, "I’ll fill this in soon!" This will make the test compile, but it won’t do anything meaningful yet.

---

### Step 3: Run the Test and Watch It Fail 😱  
Run your tests and confirm they fail. Why fail? Because the method doesn’t work yet—it’s your reminder to **stay focused on the problem!**

---

### Step 4: Add a Simple Implementation ✨  
Write the **bare minimum code** to make your test pass. In this case, think about what makes a card a "face card" (hint: numbers 11, 12, and 13). Don’t overthink it—just enough to pass the test!

---

### Step 5: Run the Test Again 🏃‍♀️  
Did it pass? 🎉 If yes, congratulations! If not, debug and adjust your code until it does.

---

### Step 6: Add Edge Cases 🧠  
Now that the basic functionality works, it’s time to **think like a tester**:
- What happens with invalid numbers?
- Does the method work consistently for all card numbers?
- Can you break it?

Add more tests to cover these scenarios.

---

### Step 7: Refactor for Clarity 💡  
Once all your tests are passing, review your code. Is it clean and easy to read? Can you simplify anything? Refactor your implementation without breaking the tests.

---

### Step 8: Celebrate! 🎉  
You just completed a feature using TDD like a pro! Tests are your safety net, so keep adding them as you grow your project.

---

### Pro Tip: Always Ask "What’s Next?" 🧗‍♂️  
Think of another feature you could add or improve in the `Card` class. Maybe a method to check if it’s a red or black card? Use the same TDD approach to tackle it!

Keep coding and have fun! 🃏🚀
