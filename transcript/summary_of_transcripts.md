# Summary of Transcripts

All of the groups interactions with any LLMs have been captured and placed in pdf files. Each pdf file contains one conversation with the LLM (in this case chatGPT). The following are summaries and the motivation for each conversation.

## Question 1
We were encountering bugs when testing the skip list implementation of the project. We suspect that this was due to memory allocation problems. We asked chatGPT if it sees issues with the code, specifically memory allocations.

## Question 2
We were encountering bugs again on the skip list implementation. We suspect that this could be because of improper usage of ```free()```, hence we asked chatGPT if we were using ```free()``` wrongly.

## Question 3
In doing the tree implementation of the list, we thought that it would be useful if we could directly see what was happening to the trees when being manipulated. We asked chatGPT to create a level order traversal print function so that we can debug much easier. We adapted the code given by chatGPT to suit the structs we had in our implementation. This modified printer function isn't present in our submission as we didn't need it anymore, since our test cases were already passing.

## Question 4
We were encountering bugs in the dynamic array implementation of the list. We asked chatGPT if it could spot any problems.

## Question 5
We asked chatGPT for test cases for the dynamic array implementation. We used this as a basis for our final test cases. We've added and modified some parts from it.

## Question 6
One of our members used chatGPT to summarize the trees implementation of the list. The summary given was used as a skeleton for the details part of the trees implementation.