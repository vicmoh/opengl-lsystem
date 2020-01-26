# L-System for Computer Graphics

## Author

* Name: Vicky Mohammad
* Email: mohammav@uoguelph.com
* ID: 0895381

## About

An L-system or Lindenmayer system is a parallel rewriting system 
and a type of formal grammar. An L-system consists of an alphabet 
of symbols that can be used to make strings, a collection of production 
rules that expand each symbol into some larger string of symbols, 
an initial "axiom" string from which to begin construction, 
and a mechanism for translating the generated 
strings into geometric structures.

## How to run

* For example, by typing `make FILE="./assets/sample1.txt"`.
It will run the the program with the "txt" that contains the string
of the l-systems.
* `FILE` must contain an argument. If not argument is pass
for the l-system string, it will segfault and does not compile.

## Control

### Camera Control

Mouse control is used for controlling the zoom scoped level to
zoom or zoom out of the object.
* Camera `zoom in`: If mouse is click and move up.
* Camera `zoom out`: If mouse is click and move down.

You can also change the x, y axis to control camera by pressing:
* Move camera `up on y-axis`: Press `up arrow` key on keyboard.
* Move camera `down on y-axis`: Press `down arrow` key on keyboard.
* Move camera `left on x-axis`: Press `left arrow` key on keyboard.
* Move camera `right on x-axis`: Press `right arrow` key on keyboard.

### Material changes

If you want to change the material of the object. 
Press the number key from 1 to 5:
* Show `line vector`: Press 1.
* Show `coloured material`: Press 2.
* Show `shader`: Press 3.
* show `smooth shader`: Press 4.
* Show `texture`: Press 5.


