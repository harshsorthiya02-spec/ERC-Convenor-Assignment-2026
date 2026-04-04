# Question 1: LED Memory Game 

## - Project Overview
This project is an interactive **LED Memory Game** built using a microcontroller.  
The system generates a sequence of LED patterns which the player must remember and reproduce using buttons.

With each level, the difficulty increases by:
- Increasing the pattern length
- Decreasing the LED blink time

The game also includes **sound feedback** and a **score display**, making it engaging and beginner-friendly.

---


## Working Principle

1. The system generates a random LED sequence.
2. LEDs glow one by one to display the pattern.
3. The player must press corresponding buttons in the same order within a limited time.
4. If the player is too slow:
   - A warning message ("Hurry Up!") is shown
   - Buzzer gives alert feedback
5. If correct:
   - Level increases
   - Pattern becomes longer
   - Speed increases
6. If wrong OR time runs out:
   - Buzzer alerts
   - Game resets
7. Score is displayed on the LCD screen.

---



## How to Play

1. Power the circuit.
2. Watch the LED sequence carefully.
3. Repeat the pattern using the buttons **within the given time**.
4. If you take too long:
   - A "Hurry Up!" warning will be displayed
   - Buzzer will alert you
5. Enter the correct sequence to move to the next level.
6. With each level:
   - Pattern length increases
   - Speed increases
7. The game ends if:
   - You press the wrong button
   - You run out of time
8. Try to achieve the highest score displayed on the LCD.

---
# Resources Given
1. BOM ( bill of material ).
2. circuit and schematic diagram.
3. Code for Arduino.  
