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
should rise in its power ranking. Since, in this example, steel is the strongest, a strength against steel is more important, due to 
its higher threat and rate of use compared to weaker types. 

</br>

CODE </br>


</br>

RUNNING ON YOUR MACHINE </br>



