#include "CUnit/Basic.h"
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Priority_Queue PriorityQueue;
typedef struct tree Huffman;

struct tree{
    unsigned int size_node;
    unsigned int priority;
    void* ch;
    Huffman *left;
    Huffman *right;
    Huffman *next;
};


typedef struct Priority_Queue{
  Huffman *head;
  unsigned int size_node;
}PriorityQueue;

// ************************** PRIORITY QUEUE **************************


//Create only one Priority Pointer for a Queue
void* create_priority_queue()
{
  PriorityQueue *new_queue = (PriorityQueue*) calloc(1,sizeof(PriorityQueue));
  new_queue->size_node = 0;
  new_queue->head = NULL;
  return new_queue;
}

//Create Node Huffman Tree
void* create_node_tree(unsigned char ch, unsigned int priority){
  Huffman* node = (Huffman*) calloc(1,sizeof(Huffman));
  node->priority = priority;
  node->ch = ch;
  node->left = node->right = node->next = NULL;
  return node;
}

//Checking if the Priority Queue is empty
int is_empty(PriorityQueue *pq){
  return (pq->head == NULL);
}

// Put item in the Priority Queue
void enqueue_node(PriorityQueue *pq, unsigned char ch, unsigned int priority){
  Huffman *new_node = create_node_tree(ch,priority);

    if (is_empty(pq) || pq->head->priority >= priority) {
      new_node->next = pq->head;
      pq->head = new_node;

  } else {
      Huffman *current = pq->head;
    while (current->next != NULL && current->next->priority < priority) {
      current = current->next;
    }
      new_node->next = current->next;
      current->next = new_node;
  }
  pq->size_node++;
}

// Enqueue a new dad(like a tree) for the Priority Queue
void enqueue_daddy_node(PriorityQueue *pq, Huffman * daddy_node){
  if(is_empty(pq) || pq->head->priority >= daddy_node->priority){
    daddy_node->next = pq->head;
    pq->head = daddy_node;
  }
  else{
    Huffman* current = pq->head;
    while(current->next != NULL && current->next->priority < daddy_node->priority){
      current = current->next;
    }
    daddy_node->next = current->next;
    current->next = daddy_node;
  }
  pq->size_node++;
}

// Withdraw the last in the Priority Queue
void* dequeue(PriorityQueue *pq){

  if (!(is_empty(pq))) {
    Huffman* node = pq->head;
    pq->head = pq->head->next;
    node->next = NULL;
    return node;
  }
  return NULL;
}

// ************************** TREE **************************

// Create one node of empty tree.
void* create_tree_node(){
    Huffman * a = (Huffman*)malloc(sizeof(Huffman));
    a->left = NULL;
    a->right = NULL;
    a->next = NULL;
    a->priority = 0;
    a->size_node = 0;
    return a;
}


// Create one node for new dad tree.
void* create_daddy_node(Huffman *one, Huffman *two){
  Huffman *daddy_node = (Huffman*)create_node_tree('*', one->priority + two->priority); // Save the dad sub-tree as "*"
  daddy_node->left = one;
  daddy_node->right = two;
  daddy_node->next = NULL;
  return daddy_node;
}

// Construct the Huffman Tree with Priority Queue
void* Do_Huffman(PriorityQueue *pq){
  Huffman* daddy_node = NULL;  //Create a new pointer for a node
  // While Priority Queue isn't empty
  while(pq->head->next != NULL){
    // Dequeue the first and second node and create a new dad for them
    daddy_node = (Huffman*)create_daddy_node((Huffman*)dequeue(pq),(Huffman*)dequeue(pq));
    // Enqueue the new dad to Priority Queue
    enqueue_daddy_node(pq,daddy_node);
  }
  //Return the root of Huffman Tree
  return pq->head;
}

// Checking if Huffman Tree is empty
int is_tree_empty(Huffman* tree){
  return (tree->size_node == 0);
}

//Checking if node of tree is a leaf.
int isLeaf(Huffman * tree){
    return ((tree->right == NULL) && (tree->left == NULL));
}

int tree_size(Huffman *tree, int size) {
  if (tree != NULL) {
    if (tree->left == NULL && tree->right == NULL &&
        (tree->ch == '*' || tree->ch == '\\')) {
      size++;
    }
    size++;
    size = tree_size(tree->left, size);
    size = tree_size(tree->right, size);
  }
  return size;
}

void print_preorder_tree(Huffman * tree){
    if(tree!=NULL){
        if((tree->ch=='*' || tree->ch=='\\'))
            printf("%c", tree->ch);
        else
            printf("[%c]", tree->ch);
        print_preorder_tree(tree->left);
        print_preorder_tree(tree->right);
    }
}


// ************************************************************************

int init_suite(void) { return 0; }

int clear_suite(void) { return 0; }

void test_enqueue_node() {

  PriorityQueue *test = create_priority_queue();

  unsigned char item1 = 5;
  unsigned char item2 = 4;
  unsigned char item3 = 3;
  unsigned char item4 = 2;
  unsigned char item5 = 1;

  enqueue_node(test, item3, 10);
  enqueue_node(test, item1, 15);
  enqueue_node(test, item4, 5);
  dequeue(test);

  CU_ASSERT_EQUAL(test->head->ch, item3);

  enqueue_node(test, item5, 1);
  enqueue_node(test, item2, 4);

  CU_ASSERT(test->head->left == NULL);
  CU_ASSERT(test->head->right == NULL);
}

void test_create_daddy_node(){
    PriorityQueue *test = create_priority_queue();
    Huffman* daddy_node = NULL; 

  unsigned char item1 = 5;
  unsigned char item2 = 4;
  unsigned char item3 = 3;
  unsigned char item4 = 2;
  unsigned char item5 = 1;

  enqueue_node(test, item3, 10);
  enqueue_node(test, item1, 15);
  enqueue_node(test, item4, 5);

    // Dequeue the first and second node and create a new dad for them
    daddy_node = (Huffman*)create_daddy_node((Huffman*)dequeue(test),(Huffman*)dequeue(test));
    // Enqueue the new dad to Priority Queue
    enqueue_daddy_node(test,daddy_node);

    daddy_node = dequeue(test);
    CU_ASSERT_EQUAL(test->head->priority, daddy_node->priority);

}


int main() {
  CU_pSuite pSuite = NULL;
  CU_pSuite pSuite1 = NULL; 

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  /* add a suite to the registry */
  pSuite = CU_add_suite("Test_PriorityQueue", init_suite, clear_suite);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  pSuite1 = CU_add_suite("Test_Tree", init_suite, clear_suite);
  if (NULL == pSuite1) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite, "test enqueue node", test_enqueue_node)) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if (NULL == CU_add_test(pSuite1, "test create daddy node", test_create_daddy_node)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}