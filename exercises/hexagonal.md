Hexagonal/clean architecture - Card class
---
Let's move the console-based display code out of Card and into a new class called `ConsoleCard`.  

The `printCardL1` and `printCardL2` methods specifically should be moved.

Note of course that you don't want to break your tests, and be sure that any existing calls to those functions get updated as well.

Hexagonal/clean architecture - Game class
---
Next do the same thing for the Game class as well!  Move all console based code into a new class called `ConsoleGame`.



This will help us build towards a Hexagonal architecture.

