# PokeRank
A custom data algorithm modeled off of the famous Page Rank algorithm to objectively rank the Pokemon types.

## Intro/Background </br>

### Pokemon Background:</br>
For those unfamiliar with Pokemon, the video games use a type system resembling a complex version of rock paper scissors. 
There are 18 total types (such as fire, ghost, steel, etc) and each type has strengths and weaknesses.
For example, fire type is two times effective against a grass defender, but half effective against water defenders.
A full chart of type relations can be found as an excel file under the program files. 
This chart is exported as a csv file and read into the program, but more on this later 

### PageRank Background:</br>
Additionally, for those unfamiliar with Page Rank, it is an algorithm for vetting the trustworthiness of webpages. 
It was a crucial algorithm for early search engines and determining which webpages should be displayed first. 
The concept is that pages that are linked to by other pages are more trustworthy. 
From there, the links are weighted by the relative trustworthiness of the origin page. 
This is then repeated through several iterations, adjusting the score of each page and the value of their links.
###### A small example-</br>
Page 1 --hyperlink--> Page 2, Page 3 --hyperlink--> Page 2 </br>
Page2's score is then generally += Page 1's score + Page 3's score </br>
Continuing, page 1 and 3 have their own iteratively determined scores, based on pages that point to them </br>
Of course, this is far from a full description of Page Rank, but plenty more can be read online </br>

### Bringing the Concepts Together</br>
My desire for writing this project came from casually playing Pokemon Go on my bus commute(s). 
I wanted an objective ranking of the Pokemon types that was based on data and not personal bias. 
Taking a look at the type chart, you can quickly realize that some types have more strengths than others. 
However, the same types are not always considered the "best". 
The reason for this is that- just like the links in Page Rank- not all type strenghts are equal. </br>
Using relative weights and many iterations, the Pokemon types can be evaluated in a similar way to websites in page rank.
To elaborate, if after one iteration, you surmise that steel type is the best, then on the second iteration, a type strong against steel 
should have that strength valued more; since steel is the strongest, a strength against steel is more important (due to 
its higher threat and rate of use compared to weaker types). 


## Code and Results </br>

### General Structure </br>
###### Reading the data
The program first reads in the data from the spreadsheet exported as a csv through c++ built in stream objects. 
This data could have been hard coded, but doing it this way allows for easy updating of the values (say if a new type was added to the games). 
As The data is read in, Pokemon class objects are created. To allow for dynamic naming of the objects, a hashmap is used with a key->value of string->obj 
(where string is the type name, and object is the new Pokemon object). The Pokemon can then be referenced from main.cpp with PokeMap.at(type).

###### Pokemon class object
The Pokemon objects, on construction store a few things essential to the iterative algorithm- type name, a floating point "weight" value, a hashmap<string, int> with their attackvalues for each type, and finally, a "win counter" for a final ranking.
The weight value is initialized to 1.0 for all types, and higher values after n iterations generally represent stronger types. The win counter is added to after each iteration to approach a more accurate average value.

###### Algorithm 
First, the program asks the user for the number of iterations; more iterations will take longer, but give a more accurate answer. 
The main computation in each iteration is a nested loop, with each going through every type to account for all 18^2 attacker/defender combinations. 
In other words, each type loops through all defending types and adjusts the corresponding weights according to that attack value.
A switch case is used for each attackValue. 0 means normal 1x effectiveness, -2 means half effectiveness, -4 means no effectiveness, and 2 means twice effectiveness.
From there, the weights of the attacker and defender are adjusted accordingly. 
For example, on -2, the attacker weight should be subtracted by 0.2 * defenderWeight, and the defenderWeight should be added with 0.2 * attackerWeight. 
Additionally, you have to consider negative weights, so before modifying the weights, check if the opposite weight is negative. If it is, flip the sign and operand to division.
In the -2 example, if the defender currently has a negative weight, -(0.2 * defenderWeight) is a positive number, and unfairly rewards the attacker. 
The attacker should still lose weight since it has an attacking weakness, so -(-0.2 / defenderWeight) => 0.2/defenderWeight is the correct adjustment. 
In the same iteration, the defender weight is also adjusted. This way, for all 18^2 combinations, the right adjustments are applied. 
Lastly, although the weights are being adjusted during the iteration, modifying the weight only adjusts the temporary weight. 
The actual weights are locked in at the very end of the iteration with one final loop through. 
The last step of the iterative algorithm, before ranking and printing, is to reward the Pokemon with the highest weights with "win points" at the end of EACH iteration.
Since the weights tend to grow exponentially, sometimes two mutually effective types can flip flop between extremely positive and extremely negative. 
This presents a need to generate some sort of average of all the iterations.
The win point addition is a good solution to this as it rewards or punishes each weight ranking every time. 

###### Ranking and printing
The very last step of the program is to rank the final values and print them. Luckily, the "win points" step  from above already provides code for ranking the types once their weights have been calculated.
The difficulty, though, arises from the fact that the objects are stored in a hashMap and not a simple vector with a built in sort function. 
Therefore, in order to rank the types, a primitive sort is used which finds the highest value, then drops that type from consideration, and repeats until all types have been ranked. 
This algorithm repeats twice- once for the single iteration weight, and again for the win points. Again, both of these values are stored as member variables of the Pokemon class.

###### Results
Here's everything this program works torward using an example run with 10,000 iterations
"How many iterations should run? (suggested ~5-> 10,000) 10000

Ranked by point values or 'wins' from all iterations: 
1. Water with 71288 points
2. Steel with 68440 points
3. Dragon with 58472 points
4. Ghost with 56065 points
5. Fairy with 46896 points
6. Ground with 38041 points
7. Grass with 37805 points
8. Electric with 34613 points
9. Fire with 31387 points
10. Fighting with 3990 points
11. Dark with -12748 points
12. Flying with -14986 points
13. Normal with -40887 points
14. Bug with -41163 points
15. Poison with -46246 points
16. Psychic with -51775 points
17. Rock with -69240 points
18. Ice with -79952 points"


</br>

## Running on your machine </br>

This program was developed using Clion IDE. Although, all you will need on your machine is a g++ compiler. 
You can clone this repo directly, or set up a folder with the main.cpp, pokemon.h, pokemon.cpp all in the same directory. 
From there, if there are any issues opening the CSV file, make sure it is in the right directory. 
Clion auto-creates a 'cmake-build-directory', but I think that normally, without this IDE, you should just place the csv in the home directory of the main.cpp file.


