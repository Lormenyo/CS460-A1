/***
 * Author: Hannah Boadiwaaa Lormenyo
 * Organization: Ashesi University
 * 
***/

#ifndef BTREE_H
#define BTREE_H

#include "data_types.h"
#include "query.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


//INITIALIZERS/FUNCTION PROTOTYPES
void insert(int key, int value);
struct nodePosition find(int key);

#define FANOUT 100

struct entry
{
   int key;
   int value;
};

struct nodePosition {
    struct node* b;
    int index;
};

struct node {
    struct entry keys[FANOUT-1];
    struct node *pointers[FANOUT];
    bool is_leaf;
    int num_keys;
    struct node *next;
    struct node *prev;
};

struct node root;

void insert(int key, int value){
    //create a new structure from the key-value pair
    struct entry newEntry;
    newEntry.key = key;
    newEntry.value = value;

    //create a pointer to the root node
    struct node *b;
    b =  &root;

    //chek if the root node is null, if so, insert the struct
    if (!b->keys){
        root.keys[0] = newEntry;
    }

    else
    {
        struct nodePosition bdata = find(key);
        if (bdata.b->num_keys == FANOUT) {
            //split node
        }
        else {
            //insert struct in node
            bdata.b->keys[bdata.index] = newEntry;
        }
        
        
    }
    

};


struct nodePosition find(int key){
    //create a pointer to the root node
    struct node *b;
    b =  &root;
    while (!b->is_leaf)
        {
            struct nodePosition bdata;
            //perform a linear search in the node key-value array to 
            //find the right one
            for (int i=0; i<= FANOUT; i++){
                if (key < (b->keys[i]).key){
                    bdata.b = b->pointers[i-1];
                    bdata.index = i;
                }
                else if ((key > (b->keys[i]).key && key <= (b->keys[i+1]).key) || key > (b->keys[i]).key ) {
                    bdata.b = b->pointers[i+1];
                    bdata.index = i;
                }
            }
            return bdata;
        }
};





/* INSERT (Chapter 10.5)
How does inserting an entry into the tree differ from finding an entry in the tree?
When you insert a key-value pair into the tree, what happens if there is no space in the leaf node? What is the overflow handling algorithm?
For Splitting B+Tree Nodes (Chapter 10.8.3)
*/

// TODO: here you will need to define INSERT related method(s) of adding key-values in your B+Tree.


/* BULK LOAD (Chapter 10.8.2)
Bulk Load is a special operation to build a B+Tree from scratch, from the bottom up, when beginning with an already known dataset.
Why might you use Bulk Load instead of a series of inserts for populating a B+Tree? Compare the cost of a Bulk Load of N data entries versus that of an insertion of N data entries? What are the tradeoffs?
*/




#endif