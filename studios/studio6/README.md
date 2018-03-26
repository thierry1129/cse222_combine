# Studio Questions / Replies

***Q1.1. What happens when people touch and release the bare end of the wire connected to `D1`?***
When you touch the free end the value printed becomes 0. If you let go it stays 1.

***Q1.2. How do your results compare to those of other groups around you?  Are they seeing the same behavior?  Different?***
Same behavior.

***Q1.3. What happens if you plug the free end of the wire to 3V3 or GND?***
Nothing happens, value is 1.

***Q2.1. Run the previous tests (touching the wire, connecting to 3V3 and GND) How has the behavior changed?***
Value is always 1. Does not change when touched or connected to ground.

***Q2.2. Change the `INPUT` to `INPUT_PULLDOWN`.  Before testing your work, how do you expect the behavior to change?***  
Should be the opposite of INPUT_PULLUP.

***Q2.3. Test your change.  Did it work as you expected?  If not, try to explain how it behaves:***
Sort of the opposite. By default the value printed is 0. If you touch it nothing changes. If you connect it to GND it changes to 1.

***Q3.1. Before testing you work, which type of pull should you use?  What will the reading be when the button is pressed and what will it be when the button is un-pressed?***
We should use INPUT_PULLUP. When it is pressed it will be 0 and when it is not pressed it will be 1.

***Q3.2. Test your work. Did it behave as you predicted?  If not, why?***
Yes. Worked like a charm.

***Q4.1. Assume someone will try to press the button for the shortest time humanly possible.  What do you think will happen each time the button is pressed?***
Each time button is pressed "count" increments.

***Q4.2. What happened?***
Count goes up by more than 1 because it's not possible to press the button for such a short time.
