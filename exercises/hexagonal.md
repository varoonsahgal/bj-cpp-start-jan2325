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

This will help us build towards a Hexagonal architecture.

