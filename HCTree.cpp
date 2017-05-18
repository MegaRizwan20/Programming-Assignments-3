/*
 * Author: Rizwan Khan
 * CSE100 Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

#include "HCTree.h"
#include "HCNode.h"
#include <stdio.h>
#include <ctype.h>
#include <queue>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/* Use Huffman algorithm to build Huffman coding trie.
 * freqs is a vector of ints, such that freqs[i] is the
 * frequency of occurrence of byte i in the message.
 * After all run, root points to root of trie and leaves[i]
 * points to leaf node containing byte i
 */
void HCTree::build(const vector<unsigned int>& freqs)
{
  // Make a vector of HCNodes
  std::vector<HCNode*> HCvec;
  // Make a priority queue that holds HCNodes, the vector of the nodes and
  // necessary ways to compare the nodes
  std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq;
  // Make new HCNodes
  for (unsigned int i = 0; i < freqs.size(); i++)
  {
    if (freqs[i] > 0)
    {
      // Make new HCNode based on the frequency
      HCNode* p = new HCNode(freqs[i], i);
      // Push into the priority queue
      pq.push(p);
      // Update the value of what is in the frequency to the leaves
      leaves[i] = p;
    }
  }

  // This loop should build the huffman tree itself
  while(pq.size() > 1)
  {
    // Grab the left child
    HCNode* left = pq.top();
    pq.pop();
    // Grab the right child
    HCNode* right = pq.top();
    pq.pop();

    // Make a new parent HCNode
    HCNode* parent = new HCNode((left->count + right->count), left->symbol);

    // Set up all the pointers to the parent node and children
    left->p = parent;
    right->p = parent;
    parent->c0 = left;
    parent->c1 = right;

    // Push the parent node that is connected to left and right back to
    // priority queue
    pq.push(parent);
  }

  // Get the last node in the priority queue as the root
  root = pq.top();
}

/**
 * Function: Encode
 * Parameters: byte symbol, BitOutputStream& out
 * Purpose: Used to make the actual Huffman tree and encode the edges
 * to read back the tree when we finish building it
 * */
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  // The HCNode used for going through the tree
  HCNode* move;
  // The stack we are putting the 0's and 1's into
  std::stack<unsigned int> edges;
  // Setting the HCNode equal to the leaves
  move = leaves[symbol];

  // If it is only one letter than we do this
  if (move == root)
  {
    edges.push(1);
  }
  
  // While the node does not equal the root we will define the edges
  while(move != root)
  {
    // Used to get to the parents of the node
    HCNode* moveParent = move->p;

    // Check if the current nodes parent's right child is equal to move then
    // we move upwards and push in a 1
    if (move == moveParent->c1)
    {
      edges.push(1);
      move = moveParent;
    }
    // Else if we move up to the parent and push in a 0 into the stack
    else if (move == moveParent->c0)
    {
      edges.push(0);
      move = moveParent;
    }
  }
  // While the edges are empty we go through the file write out the bit
  while (!edges.empty())
  {
    out.writeBit(edges.top());
    // Pops the element so we get to the next one in the stack
    edges.pop();
  }

}

/**
 * Function: Decode
 * Parameter: BitInputStream& in
 * Purpose: Used to decode the bits in the file based off of the header
 *
 * */
int HCTree::decode (BitInputStream& in) const
{
  // Set a new HCNode equal to the root
  HCNode* temp = root;
  // The characters we are getting
  unsigned char x;
  // The numbers we are setting the symbol to
  byte numbers;
  // The chars that are read in
  byte theChars;

  // Checking if there are no children
  if ((temp->c1 == NULL) && (temp->c0 == NULL))
  {
    return temp->symbol;
  }

  // While the temp node exists
  while (temp)
  {
    // Read in the characters
    theChars = in.readBit();

    // Making a check to see if we should go down the left
    if (temp->c0 && !theChars)
    //if (temp->c0 = '0')
    {
      temp = temp->c0;
    }
    // Checking to see if we should go down the left
    else if (temp->c1)
    //else if (temp->c1 == '1');
    {
      temp = temp->c1;
    }
    // Code fails
    else
    {
      return -1;
    }

    // Checking if we have reached the end leaf node
    if ((temp->c0 == NULL) && (temp->c1 == NULL))
    {
      numbers = temp->symbol;
      return numbers;
      //break;
    }

  }

  return temp->symbol;
}

/**
 * Function: ~HCTree()
 * Parameters: None
 * Purpose: Used to delete the tree to prevent memory leaks
 * */
HCTree::~HCTree()
{
  deleteAll(root);
}

// Does the actual deleting of the tree
/**
 * Function: deleteAll
 * Parameters: HCNode* n
 * Purpose: Recursively deletes all the nodes in a tree
 * to make sure memory leaks does not happen. It does an post
 * order deletion
 * */
void HCTree::deleteAll(HCNode* n)
{
  if (n)
  {
    deleteAll(n->c0);
    deleteAll(n->c1);
    delete n;
  }
}
