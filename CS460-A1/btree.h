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
void print_bpt();

#define FANOUT 100

typedef struct genNode {
    int keys[FANOUT-1];
    struct genNode *node_pointers[FANOUT];
    struct valueEntry *leaf_pointers[FANOUT];
    bool is_leaf;
    int num_keys;
} genNode;

typedef struct valueEntry {
    int value;
}valueEntry;

struct genNode *root = NULL;

struct genNode* find(int target_key){
    //returns leaf node for the given key parameter

    struct genNode *currentNode = root;  //initialise current node to root node

    while (!currentNode->is_leaf)
        {
            for (int i=0; i<= (FANOUT-1); i++){
                if (currentNode->keys[i] == target_key){
                    currentNode = currentNode->node_pointers[i+1];
                }
                else if (currentNode->keys[i] < target_key){
                    currentNode = currentNode->node_pointers[i];
                }
                else {
                    currentNode = currentNode->node_pointers[FANOUT];
                }
            } 
        }
        return currentNode;
};

void insert_in_leaf(genNode *node, int key, int v){
    struct valueEntry* ptr_to_value ;
    int nkeys = node->num_keys;
    //leaf node has just values

    printf("int value -- %d \n", v);
    printf("int key -- %d \n", key);
    printf("Inserting into leaf \n");
    printf("---------------------\n");

    //if the key is less than the first value of the leaf node
    if (key < node->keys[0]){
	    for (int i = node->num_keys; i > 0; i--) {
		    node->keys[i] = node->keys[i - 1];
		    node->leaf_pointers[i] = node->leaf_pointers[i - 1];
	    }
	    node->keys[0] = key;
	    node->leaf_pointers[0] = ptr_to_value;
        node->leaf_pointers[0]->value = v;
	    node->num_keys = nkeys + 1;

    printf("leaf node value ---- %d \n", (node->leaf_pointers[0])->value);
    printf("\n");
    }
    else{
        int i, insert_index;
        insert_index=0;
        while(insert_index < node->num_keys && node->keys[insert_index] < key){
            insert_index++;
        }

	for (i = node->num_keys; i > insert_index; i--) {
		node->keys[i] = node->keys[i - 1];
		node->leaf_pointers[i] = node->leaf_pointers[i - 1];
	}
    
	node->keys[insert_index] = key;
	node->leaf_pointers[insert_index] = ptr_to_value;
    node->leaf_pointers[insert_index]->value = v;

    printf("leaf node value ---- %d \n", (node->leaf_pointers[insert_index])->value);
    printf("leaf node #num-keys ---- %d \n", node->num_keys);
    printf("\n");
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

    if (leafNode->num_keys<(FANOUT-1)){
        insert_in_leaf(leafNode, key, value);
    }
    else {
        //if node is full, split it

    }
};

genNode* create_node(void){
    genNode* newNode;

    newNode = (struct genNode*) malloc(sizeof(genNode));
    if (newNode==NULL){
        perror("Cration of the Node ");
        exit(EXIT_FAILURE);
    }

    newNode->num_keys = 0;
    newNode->is_leaf  = false;

}

genNode* create_leaf(void){
    genNode* leaf = create_node();
    leaf -> is_leaf = true;
    return leaf;
}


void print_bpt(){
    printf("printing the b+ tree");
    // for (int m=0; m<(FANOUT-1); m++){
    //     if (root->keys[m]!= 0){
    //         printf("key %d",m);
    //         printf("is %d \n", root->keys[m]);
    //     }
    // }
    printf("%d", root->leaf_pointers[0]->value);
    // printf("%d", &root->keys[FANOUT-1]);
    printf("tree done");
}

int get_split_index(int length){
    int split_index;
    if (length % 2 == 0)
        split_index = length/2;
    else
        split_index = (length+1)/2;
    
    return split_index;
}
 



#endif