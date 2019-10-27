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
struct genNode* find(int key);
struct genNode* create_leaf();
struct genNode* create_node();

#define FANOUT 100

typedef struct genNode {
    int keys[FANOUT-1];
    struct genNode *pointers[FANOUT];
    bool is_leaf;
    int num_keys;
} genNode;

struct genNode *root = NULL;


struct genNode* find(int target_key){
    //returns leaf node for the given key parameter

    genNode *currentNode = root;  //initialise current node to root node

    while (!currentNode->is_leaf)
        {
            for (int i=0; i<= FANOUT-1; i++){
                if (currentNode->keys[i] == target_key){
                    currentNode = currentNode->pointers[i+1];
                }
                else if (currentNode->keys[i] < target_key){
                    currentNode = currentNode->pointers[i];
                }
                else {
                    currentNode = currentNode->pointers[FANOUT];
                }
            }
        }
        return currentNode;
};

void insert_in_leaf(genNode* node, int key, int value){
    struct genNode* ptr_to_value ;

    printf("Inserting into leaf");
    if (key < node->keys[1]){

    }
    else{
        int i, insert_index;
        insert_index=0;
        while(insert_index < node->num_keys && node->keys[insert_index] < key){
            insert_index++;
        }

	for (i = node->num_keys; i > insert_index; i--) {
		node->keys[i] = node->keys[i - 1];
		node->pointers[i] = node->pointers[i - 1];
	}
	node->keys[insert_index] = key;
	node->pointers[insert_index] = ptr_to_value;
	node->num_keys++;
	//return leaf;        

    }

};

void insert(int key, int value){
    genNode* leafNode;

    if (root==NULL){
        //initialise empty leaf Node
       leafNode = create_leaf();
    }
    else
    {
        leafNode = find(key);
    }

    if (leafNode->num_keys<FANOUT-1){
        insert_in_leaf(leafNode, key, value);
    }
};

genNode* create_node(void){
    genNode* newNode;

    newNode = (struct genNode*) malloc(sizeof(genNode));
    if (newNode==NULL){
        perror("Node creation ");
        exit(EXIT_FAILURE);
    }

    newNode->num_keys = 0;
    newNode->is_leaf  = false;

};

genNode* create_leaf(void){
    genNode* leaf = create_node();
    leaf -> is_leaf = true;
    return leaf;
}





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