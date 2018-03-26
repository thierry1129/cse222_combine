# Studio Questions / Replies

***Q1.1 Use the Paper Prototype to complete the Use Case. The Spokesperson should work through the case and other members of the group should observe. Is the paper prototype missing any features for this use-case? If so, update it and complete the case.***

It is missing a power buttom.

***Q1.2 What aspects of the paper prototype would change as a result of the
use-case?***

The prototype will change after we got a power buttom. So we are able to turn it on or off.

***Q2.1 Write a user story for turning the light from on at full white color (100% of Red, Green, and Blue) to off using the current paper prototype:***

User can turn the light from on at full white color (100% of Red, Green, and Blue) to off.

***Q2.2 Write a use-case for the user story:***

Description: Changing the light from full white color to off
Pre: all slider are at 100%
Steps:
1. User adjusts the red slider to 0%
2. User adjusts the green slider to 0%
3. User adjusts the blue slider to 0%
4. User hits Select Color buttom.
Post: The light is off.

***Q2.3 Test your work (Spokesperson tests, others observe)--- you'll find that it's awkward to turn the light off.  UIs should make common actions easy and one of the most common actions for an RGB light would be turning it off or on.  Update or replace the paper prototype with one that will simplify turning the light off and on as well as changing its color.  You'll need to show a TA your resulting prototype at checkout.***

***Q3 User is very energy conscious.  They will want the light to automatically turn off after it has been on too long, but they will want to ability enable or disable this feature. Create a paper prototype of another screen that supports the ability to configure the light's ability to automatically turn off. Ensure that there is a clear, obvious way to navigate back and forth among screens.***


***Q4 Briefly summarize the advantages of using paper prototypes.***

we are able to earse and replan.

***Q5.1 Using the Developer tools, inspect the entire cell containing the range slider for Red (the entire cell, not just the slider itself). Note that the cell has a `col-9` class --- it's 9 columns wide.  The class has `display: table-cell;` Highlighting that will reveal a check box that can be used to disable the property, allowing it to revert to it's default value.   What happens to the contents of the box if you allow it to revert?***

The contents will keep jumping left and right.

***Q5.2 Inspect the box that represents the "Target Color" (not the box with the label "Target Color", but the one to the right that has a white background and black border).  Using the computed properties tab, change the border color.  List the different ways you can pick colors:***
1. wirte the color name
2. wirte the hex code of the color
3. use the RGB picker

***Q7.1  You may notice the page seems incomplete. What's contained in the HTML, but not shown on the screen?:***

the slider for blue is not full length.

***Q7.2  Explain the nature of the error the validator did not catch.  Why couldn't the validator identify it?:***

the error is the class name.
