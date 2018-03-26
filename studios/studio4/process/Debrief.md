
# Summarize Highlights from Prep Material (Technician)

- Spend approximately 10-15 minutes summarizing highlights from the prep material.
- Do ***NOT*** use outside resources except where/when noted.  The answers should be based only on the group's knowledge.
- Be sure to discuss the content with your group and that everyone agrees on the answers.
- Answers can be brief/informal.

***Q1. Create code here, but don't try it yet!  Given an example of declaring an object literal (i.e., an actual object with specific values). Provide code for an object representing a computer science course, `cs1`.  It should have a property named `roll` that contains the names of students (make it contain "Ada", "Babbage", "Turing", and "Hopper") and a method called `size()` that returns the number of students in the class (don't use a constant; base it on the `roll` property):***
var cs1={
  roll : ["Ada", "Babbage", "Turing","Hopper"],
  size: function(){
    return num;
  }
}


var car = {name:"cs1", roll:{"Ada", "Babbage", "Turing", and "Hopper"}, color:"white"};
***Q2. The Technician should open a Console in a web browser and try the work entered above (copy/paste it at the prompt (`>`), then enter commands to test it at the prompt, like `cs1.size()`).  If you encounter errors, just fix them and re copy/paste the updated code, which will replace the previous value of the variable. Describe any problems that occurred or errors that had to be fixed.***


***Q3. Consider the following two examples (but don't execute them)***
```JavaScript
var sayHi = function() { console.log("Hi"); }
setTimeout(sayHi, 1000);
```
***vs:***
```JavaScript
var sayHi = function() { console.log("Hi"); }
setTimeout(sayHi(), 1000);
```
***Explain the difference in meaning between the two and how you think each will behave:***
First: pauses first then print hi
Second:  print hi first then pauses

***Q4. Have the Technician try the examples above.  If there were any errors in your answers, please explain:***
no errors

***Q5. Again, try to answer this question before running code. JavaScript's `this` has some unusual behavior. Consider:***
```JavaScript
var o = {
  name: "I'm o",
  getName: function() {
    console.log(this.name)
    return this.name;
  }
}
```
***vs.***
```JavaScript
var o = {
  name: "I'm o",
  getName: function() {
    console.log(this.name)
    var aNestedFunction = function() {
      return this.name;
    }
    return aNestedFunction();
  }
}
```
***vs.***
```JavaScript
var o = {
  name: "I'm o",
  getName: function() {
    console.log(this.name)
    var cap = this.name;
    var aNestedFunction = function() {
      return cap;
    }
    return aNestedFunction();
  }
}
```
***Explain what you expect the `var name = o.getName()` to return/do in each case (what will be printed and what will be stored in `name`):***
case1: print I'm o  stores I'm o
case2: print I'm o  stores I'm o
case3: print I'm o  stores I'm o

***Q6. The Navigator should now try the code.  Explain any discrepancies in your answer:***
case1: print I'm o
case2: print I'm o
case3: print I'm o

***Q7. Briefly explain JSON:***
Json is a data interchanged text format. Machine could easily parse and generate.
