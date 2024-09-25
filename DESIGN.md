For the hashtable itself, I beleive I can make good use of the tutorial from class by implementing Dan Bernstein's hash function and make tweaks to it if needed. From there we can make the structs of the hash table and hash values. 

## add
I can refer to the class tutorial for this and make a similar function that allocates a new node, goes to the right bucket, and puts the information there or replacing if something exists already. 

## lookup
For this I can refer to the strucutre from the corresponding class tutorial function but essentially go to that bucket and retrieve the information there.

## delete
For this I would need to go through the hash table looking for the prompted email and then before freeing it I would need to point the node in front of it to the one that this deleted node was pointing at. 

## list
This can ideally be done recursively that goes through every bucket returning the node values until a NULL node is reached. If there is a specific size of the hash table then that could be a way to track the traversing as well.

## save 
For this function I would open the customer.tsv file to write and then traversing the hash table and printing each node's values that gets traversed in the desired format.

## quit
For this I would need to go through the hash table and free up every node and its values before freeing the hash table itself. I believe exiting the program would be exit(0) too.

## Makefile
This should just have the standard flags for my classes. I will also compare to previous Makefiles and make sure mine is of similar structure.

## tests
For now i think having a test file would be ideal to see if I can run all of the functions above. Last homework taught me how to write some test cases so I'm sure I can reapply that knowledge here.
