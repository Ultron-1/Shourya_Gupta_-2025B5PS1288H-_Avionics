# Shourya_Gupta_-2025B5PS1288H-_Avionics

**Task-1(Writing python code)**
So I will be very honest i have zero knowledge in python and i did this task totally with the help of gemini. If I do clear this round I will try to see what the commands do used in this code. We imported various libraries pandas for taking data from csv file, numpy to handle arrays, matlotlib to draw graphs

**Task 2(Keeping Watch over odysseus)**
https://www.tinkercad.com/things/91d3bJKi8Zg-athena/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2FFall

So I made a tradeoff in my mind since i am going to go totally on gemini for task one i will work on this totally from scratch without using gemini. Doing this task was definitely lot fun for me , it was my first time working with multiple sensors at the same time, so handling that part was tough since i have been learning arduino from Paul mc whorter (I am at 50 video rn btw :) ) and there we just use a single component so coding is much simpler, but here it got complex

* I used a simple lcd here instead of a i2c one(the lcd in tinkercad does not has a built in resistor so had to use an external resistor)
* So I tried to track the entire state of the system using 0 and 1, and then use that in different if else statements. First I tracked whether it was storm or charybids, then assigned state accordingly. 
* Then i used these assigned states to identify different scenarios and do lcd print with those conditions, while keeping wrecked at the priority
* Here there was no exact priority given so i gave priority to storm in the if else chain,
* During this task i learned about the importance of assigning data type, so basiccally my speed of sound was 343000, which wwas much bigger than 16 bits due to which my charybids logic was totally glitching, but on changing the data type to long it automatically
* in task one it is asked how to reduce the noise, so i think in arduino we can do that by simply using the for loop and then taking multiple reading and taking average of all those values to reduce the noise and get a much better reading
