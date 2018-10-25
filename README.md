# magnet-fish-spectacular
for IOT Hack Day 2018 (https://iothackday2018.devpost.com/)

<h2>GOALS:</h2>

* What the player should see when they catch a fish: (a) hear a splash from the speaker followed by the fish saying something, (b) see the fish's name appear on the oled screen with how many points it's worth, (c) the oled screen should then show how many total points the player has earned as its default state.

<h2>STEPS:</h2>

* Test out sample audio playing through speaker using Teensy Prop Sheild (Try using this tutorial that explains how to load a raw audio file onto the Teensy's flash memory: https://learn.sparkfun.com/tutorials/vox-imperium-stormtrooper-voice-changer?_ga=1.151591033.1557711872.1477327445)

* Make hardcoded fish name show up on the first line of oled screen, followed by hardcoded number of points earned on the second line of the oled screen

* Find audio sample for splash sound effect and use this as default sound effect for fish being caught until we figure out customized audio recordings for each of the big fish.

* Sew up decoy fish, starfish, octopus with embedded stuffed toy stuffing and RFID card with magnets. (Would like to make twenty total decoy sea creatures).

* Program the motor driving the spinning of the circular wooden platform.

* Test the spinning platform with the incline underneath and while the fish are inside their slots. Do the fish open and close their mouths when they enter and exit the incline?

* Figure out a scoring system for different fish sizes.

* Catching a fish, win condition: when the RFID sensor with magnets (embedded inside the fishing rod tip) makes contact with the opposite polarity magnet inside the fishing mouth, it will read the code on the RFID card. When this code is read, plus the gyroscope/accelerometer detect a tilt in the rod soon after, then that means the fish was caught and a win condition is triggered.

<h2>GAMEPLAY:</h2>

* Players will have a total of x amount of minutes to play before we stop the game and everyone says how many points they got to see who earned the most amount of points. 

* Team members will need to set up for the next game and make sure all of the rods have had their reset buttons pressed before the new game starts.

<h2>PARTS:</h2>

* Teensy 3.2V

* Teensy Prop Sheild

* MPU (has gyroscope and accelerometer)

* OLED Screen

* RFID Sensor

* RFID Card

* Ceramic magnets (weaker magnets)

* Neodymium magnets (strong magnets)

<h2>MEET THE FISH:</h2>

* CLIDE - It's like Clyde with one "I" (eye) is a cyclops who makes watches as a jeweler.

* HENRY - Has 6 kids who all live at home and he's supremely stressed out.

* GUS - Is from East Europe and refuses to shave his unibrow because it reminds him of his mother.

* Peter - Plays video games and probably needs glasses because he squints all the time.

* Rufus - Wears his glasses but does his own repairs on them.

* Margaret just finished her masters in business analysis and vacations with her family in Bermuda.

* Lord Scenturio - A frog god with weather magic and mad SkeeBall skills.

* Portia - likes planning parties and kareoke but she doesn't like drinking beer. She does like wearing pink.
