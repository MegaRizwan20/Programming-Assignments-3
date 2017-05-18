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
//void HCTree::build(const vector<int>& freqs)
void HCTree::build(const vector<unsigned int>& freqs)
{
  //CODE
  // Make a vector of HCNodes
  std::vector<HCNode*> HCvec;
  // Make a priority queue that holds HCNodes, the vector of the nodes and
  // necessary ways to compare the nodes
  std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq;
  // Make new HCNodes
  //HCNode* p = new HCNode();
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
    //HCNode* p = new HCNode();
    //pq.push(p);
    //pq.push(freqs[i]);
  }

  // This loop should build the huffman tree itself
  //HCNode* left;
  //HCNode* right;
  while(pq.size() > 1)
  {
    // For having a parent connect the nodes
    //HCNode* parent;
    // Grab the left child
    HCNode* left = pq.top();
    pq.pop();
    // Grab the right child
    HCNode* right = pq.top();
    pq.pop();

    HCNode* parent = new HCNode((left->count + right->count), left->symbol);
    //HCNode* parent = new HCNode((left->count + right->count)
    
    //HCNode* parent = new HCNode((left->count + right->count), right->symbol);
    //parent->c0 = left;
    //parent->c1 = right;
    left->p = parent;
    right->p = parent;
    parent->c0 = left;
    parent->c1 = right;

    // Push the parent node that is connected to left and right back to
    // priority queue
    pq.push(parent);
  }

  //cout << " BEFORE TOPPING THE ROOT" << endl;
  root = pq.top();
}

//void HCTree::encode(byte symbol, ofstream& out) const
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  HCNode* move;
  std::stack<unsigned int> edges;
  //std::vector<unsigned int> edges;
  //std::queue<unsigned int> edges;
  move = leaves[symbol];

  if (move == root)
  {
    edges.push(1);
    //edges.push_back(1);
  }
  
  // While the node does not equal the root we will define the edges
  while(move != root)
  {
    HCNode* moveParent = move->p;
    // Check if the current nodes parent's right child is equal to move then
    // we move upwards and push in a 1
    //cout << " BEFORE CONDITION " << endl;
    //if(move->p->c1 = move)
    if (move == moveParent->c1)
    {
      //cout << " FIRST IF " << endl;
      edges.push(1);
      //edges.push_back(1);
      //move = move->p;
      move = moveParent;
      //cout << " AFTER FIRST IF " << endl;
    }
    // Else if we move up to the parent and push in a 0 into the stack
    //else if (move->p->c0 = move)
    else if (move == moveParent->c0)
    {
      //cout << " FIRST ELSE " << endl;
      edges.push(0);
      //edges.push_back(0);
      //move = move->p;
      move = moveParent;
    }
  }
  //for (int j = 0; j < edges.size(); j++)
  while (!edges.empty())
  {
    //cout << "LIES EVERYWHERE " << endl;
    //out << edges.top();
    //cout << edges.top() << endl;
    out.writeBit(edges.top());
    //out.writeBit(edges.front());
    edges.pop();
  }

  /*for (int j = edges.size() - 1; j >= 0; j--)
  {
    out.writeBit(edges[j]);
  }*/
  //out << edges << endl;
}


/*
void HCTree::encode(byte symbol, ofstream& out) const
{
  HCNode* move;
  std::stack<int> edges;
  move = leaves[symbol];

  if (move == root)
  {
    edges.push(1);
  }
  
  // While the node does not equal the root we will define the edges
  while(move != root)
  {
    HCNode* moveParent = move->p;
    // Check if the current nodes parent's right child is equal to move then
    // we move upwards and push in a 1
    //cout << " BEFORE CONDITION " << endl;
    //if(move->p->c1 = move)
    if (move == moveParent->c1)
    {
      //cout << " FIRST IF " << endl;
      edges.push(1);
      //move = move->p;
      move = moveParent;
      //cout << " AFTER FIRST IF " << endl;
    }
    // Else if we move up to the parent and push in a 0 into the stack
    //else if (move->p->c0 = move)
    else if (move == moveParent->c0)
    {
      //cout << " FIRST ELSE " << endl;
      edges.push(0);
      //move = move->p;
      move = moveParent;
    }
  }
  //for (int j = 0; j < edges.size(); j++)
  while (!edges.empty())
  {
    //cout << "LIES EVERYWHERE " << endl;
    out << edges.top();
    edges.pop();
  }
  //out << edges << endl;
}*/

//int HCTree::decode (ifstream& in) const
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
    /*if ((temp->c0 == NULL) && (temp->c1 == NULL))
    {
      numbers = temp->symbol;
      return numbers;
      //break;
    }*/

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

  //return numbers;
  return temp->symbol;
  //
  //
  // While I am reading in 1's or 0's
  //while(in.get(x) != NULL)
  /*while (in >> x)
  //while (in << x)
  {
    // Check if I read in a 1
    if (x == '1')
    {
      // Move down the right
      temp = temp->c1;
    }
    // Else if I read in a 0
    else if (x == '0')
    {
      // Move down the left
      temp = temp->c0;
    }
    // We encountered an error
    else
    {
      return -1;
    }
    
    if ((temp->c1 == NULL) && (temp->c0 == NULL))
    {
      break;
    }
  }*/
  // Return the symbol of the leaf node at the end
  //return temp->symbol;
}

/*
int HCTree::decode (ifstream& in) const
{
  // Set a new HCNode equal to the root
  HCNode* temp = root;
  char x;

  if ((temp->c1 == NULL) && (temp->c0 == NULL))
  {
    return temp->symbol;
  }
  // While I am reading in 1's or 0's
  //while(in.get(x) != NULL)
  while (in >> x)
  //while (in << x)
  {
    // Check if I read in a 1
    if (x == '1')
    {
      // Move down the right
      temp = temp->c1;
    }
    // Else if I read in a 0
    else if (x == '0')
    {
      // Move down the left
      temp = temp->c0;
    }
    // We encountered an error
    else
    {
      return -1;
    }
    
    if ((temp->c1 == NULL) && (temp->c0 == NULL))
    {
      break;
    }
  }
  // Return the symbol of the leaf node at the end
  return temp->symbol;
}
*/

// Method used to delete the tree
HCTree::~HCTree()
{
  deleteAll(root);
}

// Does the actual deleting of the tree
void HCTree::deleteAll(HCNode* n)
{
  if (n)
  {
    deleteAll(n->c0);
    deleteAll(n->c1);
    delete n;
  }
}
