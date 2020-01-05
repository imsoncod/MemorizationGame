## MemorizationGame
#### Clearly, the good news is that humans can stay healthy longer than ever before
#### However, there has been an increase in life expectancy, which is a worry about the aging age
#### In recent years, Korea has inferred its appearance after six years, and six years later, one in five people is 65 or older
#### Since 65, there is a disease that occurs frequently in humans, That's dementia
#### I developed a game program to prevent 'dementia' disease with this project, and the official name is Memorization Game 
#### Development used MFC and Atmega.
## Developer
#### imsoncod
## Development period
#### About 1 weeks
## Language used
#### Only C++
## Development tools
#### Visual Studio 2017
## How to play
#### 1. Connect the board, select the difficulty level and press the start game button
#### 2. After 3 seconds count, 8 LEDs blink 8 times in different locations at a speed suitable for the chosen difficulty
#### 3. Remember the position of the flashing LED
#### 4. When the blue light is on, use the switch to enter the location of the flashing LED.
#### 5. The board checks if the value you entered is correct
## Functions
* #### Dialog configuration for memorization game
* #### Counting time seconds using FND
* #### Use Piezo for contextual alerts 
  * ex) 'Ding dong dang' when the answer is correct
* #### Use random values to keep asking questions differently
  * ex ) LED blinks differently every time according to random value
* #### RGB LED output of different colors in different situations
  * ex ) Green light when correct, red light when incorrect
* #### Enter the correct answer using the switch, the number of inputs is displayed by LED
* #### Automatically determine the correct answer when eight are entered
* #### Board initialization for smooth game start and end
## Development screen
* #### Board screen
     ![image](https://user-images.githubusercontent.com/48934537/71764638-a5ce0e80-2f2d-11ea-9e5a-a6ceed194954.png)
* #### Main Dialog screen
     ![image](https://user-images.githubusercontent.com/48934537/71762777-f6863d00-2f16-11ea-8c3b-f0df90069166.png)
