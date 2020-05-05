# CS 126 Final: Word Search]

Author: [Shefali Sharma]

I am interested in working on building a word search program 
which displays a grid of randomized letters, displays a word 
bank, and displays a timer tracking how long the player takes 
to solve the puzzle.

In order to complete this project, I will use the experience 
I gained with using SQLite databases to store the words being 
used in the puzzle and using audio through cinder to play 
background music and/or let the player know if their chosen 
word in their game is correct or incorrect. Since I want to 
make this game as interactive as possible, I will also use my 
knowledge of ifstream to help the player navigate to what they 
want to do specifically while playing the game (Ex: try to solve 
the puzzle, see the solution, see instructions, etc.). I want 
to do this project to try to use as many elements I have learned 
from previous projects to build an application that contains 
impressive features and put into perspective the new tools and 
libraries I can work with and produce a functional project implementing them.

External libraries: I used SFML for my external library. SFML is a simple,
fast, cross-platform and object-oriented multimedia API. It provides access 
to windowing, graphics, audio and network. I used SFML to control a major part
of my project: the puzzle grid itself. This grid contains the inserted 
characters from the word bank, randomized characters, and helps track the 
position of the characters to highlight the grid once the user enters the 
correct word.

Timeline:

By Week 1: I plan to do research on finding a source of random words 
to be able to use it in my SQL database. I will start a foundational 
UI for displaying my grid of randomized letters and display a word bank. 
I will also display a timer tracking how long the game lasts
By Week 2: I plan to work on allowing the user to select a word they 
see within the word search by dragging a line starting from the first 
letter to the last letter. If the player selects a valid word from the 
word bank, the word should become a lighter shade, maybe grey, representing 
that it has been found. I will add sound to play if the user is correct or 
incorrect.
By Week 3: I will finalize a title screen with buttons directing to the game 
. I will try to implement a hint button as well as a way to display the 
solution to the entire puzzle. After a certain period of time, if the 
puzzle is not solved, there should be a countdown and a game over screen 
should appear. When the game ends, the screen should display the player 
name, score, and time it took to complete the game which is all being 
read from a SQL database.
If I finish the game early, I will try to improve the UI and possibly 
have the user control the letters they select by highlighting the grid 
square green. I will add a way for the user to pause the game and possibly 
add a variety of difficulty levels.