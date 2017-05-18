/* 
 * Authors: Rizwan Khan, Kenton Chick
 * UCSD Email: rikhan@ucsd.edu, kchick@ucsd.edu
 * PID: A12236946, A12947178
 * CSE Login: cs100sgv, kchick
*/

#include "util.h"
#include "DictionaryTrie.h"
#include <queue>
#include <stdio.h>
#include <ctype.h>

using namespace std;

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() : root(NULL) {}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  TSTNode* curr;
  // If root does not exist, we make a root
  if (!root)
  {
    //if (word[1] != '\0')
    if (word.length() > 1)
    {
      root = new TSTNode(word[0], 0);
    }
    else
    {
      //cout << "THE ROOT NODE IS " << word[0] << endl;
      root = new TSTNode(word[0], freq);
      root->nodeCheck = true;
      root->endNode = word;
    }
    curr = root;
    /* Checks if there is more than one letter in the word, so we can insert
     * in a whole word down the middle */
    //if (word[1] != '\0')
    if (word.length() > 1)
    {
      unsigned int i = 1;
      /* Checking if we are pointing to the null character or not */
      //while (word[i] != '\0')
      while (i != word.length())
      {
        /* Make a new TSTNode and set it equal to the letter and point
         * to the appropriate parents */
        TSTNode* newNode = new TSTNode(word[i], 0);
        //if (word[i+1] == '\0')
        // Check if we are at the end of the word
        if (word.length() - 1 == i)
        {
          newNode->freq = freq;
          newNode->nodeCheck = true;
          newNode->endNode = word;

        }
        // Move forward in the tree and set up the pointers
        curr->middle = newNode;
        newNode->parent = curr;
        curr = curr->middle;
        i++;
      }
    }
    return true;
  }

  // Used for iterating through the word
  unsigned int j = 0;
  // Sets the current node to the root node
  curr = root;
  while (true)
  {
    //cout << "Word char: " << word[j] << " curr: " << curr->data << " j is: " << j << endl;
    // Inserting something is equal to the current data
    if (word[j] == curr->data)
    {
      // If the middle is null we need to start inserting in the elements into
      // middle branch
      if (curr->middle == NULL)
      {
        // Should take care of the scenario where we reach end of the word and
        // the middle is null
        if (word.length() -1 == j && curr->nodeCheck == true)
        {
          //cout << "THE CURRENT LETTER IS " << curr->data << endl;
          return false;
        }

        // Get to next letter in the word so we can start inserting nodes
        j++;
        // Loop through the word and keep adding the word down the middle branch
        for (; j < word.length(); j++)
        {
          TSTNode* newNode = new TSTNode(word[j], 0);
          curr->middle = newNode;
          newNode->parent = curr;
          curr = curr->middle;
        }

        // Finished inserting the word
        if (freq > curr->freq)
        {
          curr->freq = freq;
        }
        curr->nodeCheck = true;
        curr->endNode = word;
        break;
      }
      // Else we move down the middle to get to next node because not null
      else
      {
        // Check to see if we are at the end of the word and initialize fields
        if (word.length() - 1 == j && curr->nodeCheck == false)
        {
          //cout << " GIVE ME THE LETTER T" << endl;
          curr->freq = freq;
          curr->nodeCheck = true;
          curr->endNode = word;
          break;
        }
        // Check if we should move forward in the tree or not
        if (word.length() != 1)
        {
          curr = curr->middle;
        }
        // Go to the next letter
        j++;
      }

      // Checks if we have reached the end of a word and are trying to reinsert
      // the same word so return false;
      if (word.length() == j && curr->nodeCheck == true)
      {
        //cout << "THE CURRENT LETTER IS " << curr->data << endl;
        return false;
      }
    }

    // Inserting something that is less than
    else if (word[j] < curr->data)
    {
      // Check if there is nothing to the left of the current node
      if (curr->left == NULL)
      {
        // Making a new TSTNode to the left and setting up the pointers
        TSTNode* newNode = new TSTNode(word[j], 0);
        curr->left = newNode;
        newNode->parent = curr;
        curr = curr->left;

        j++;
        // Loop through all the other letters and add the rest of the word
        for (; j < word.length() - 1; j++)
        {
          TSTNode* newNode = new TSTNode(word[j], 0);
          curr->middle = newNode;
          newNode->parent = curr;
          curr = curr->middle;
        }
        // Setup all the fields of the node
        //if (freq > curr-freq)
        //{
        curr->freq = freq;
        //{
        curr->nodeCheck = true;
        curr->endNode = word;
        break;
      }
      // Else keep going to the left
      else
      {
        curr = curr->left;
      }
    }
    // Else if go to the right of the current word
    else if (word[j] > curr->data)
    {
      // Makes a TSTNode to the right of the current node
      if (curr->right == NULL)
      {
        // Make the test node and setup the pointers
        TSTNode* newNode = new TSTNode(word[j], 0);
        curr->right = newNode;
        newNode->parent = curr;
        curr = curr->right;

        j++;
        // Add the rest of the word down the middle branch
        for (; j < word.length() - 1; j++)
        {
          TSTNode* newNode = new TSTNode(word[j], 0);
          curr->middle = newNode;
          newNode->parent = curr;
          curr = curr->middle;
        }
        // Setup the fields of the node
        curr->freq = freq;
        curr->nodeCheck = true;
        curr->endNode = word;
        break;
      }
      // Else we go to the right of the curent node
      else
      {
        curr = curr->right;
      }
    }

  }
  return true;
  //return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  // Check existence of the root
  if (!root)
  {
    return false;
  }
  // Make a TSTNode and set it to the pointer
  TSTNode* curr = root;
  // Used to go through the word
  unsigned int i = 0;
  // While we are in the node
  while (curr)
  {
    // Check if the node data is the same as the letter
    if (word[i] == curr->data)
    {
      // If we found the word we return true
      if (word.length() - 1 == i && curr->nodeCheck == true)
      {
        return true;
      }
      // Else if we return false
      else if (word.length() - 1 == i && curr->nodeCheck == false)
      {
        return false;
      }
      // Else we go through the tree
      else
      {
        curr = curr->middle;
        i++;
      }
      //i++;
    }
    // Else if the letter is less than the current node, then go left
    else if (word[i] < curr->data)
    {
      //cout << "The 
      curr = curr->left;
      //i++;
    }
    // Else if letter is greater than current node, we go to the right
    else if (curr->data < word[i])
    {
      curr = curr->right;
      //i++;
    }
  }
  return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, 
    unsigned int num_completions)
{
  /*std::vector<std::string> words;
    return words;*/

  // Make all the necessary vectors and queues
  std::vector<TSTNode> orderVectNode;
  std::vector<int> orderVectNum;
  std::vector<string> orderVectString;
  //std::queue<TSTNode*> occQueue;
  std::priority_queue<TSTNode*> occQueue;

  //FIND METHOD
  /*if (!root)
    {
    return false;
    }*/

  // GETS TO THE LAST NODE IN THE PREFIX
  TSTNode* curr = root;
  unsigned int i = 0;
  // We are effectively reusing the find method
  while (curr)
  {

    //cout << "Inside while " << endl;

    // Check if the data is the same
    if (prefix[i] == curr->data)
    {
      // Break once we reach the end
      if (prefix.length() - 1 == i)
      {
        break;
      }
      // Else we keep going down the tree
      else
      {
        curr = curr->middle;
        i++;
      }
      //i++;
    }
    // Else if letter is less than the data go to the left
    else if (prefix[i] < curr->data)
    {
      //cout << "The 
      curr = curr->left;
      //i++;
    }
    // Else if letter is greater than data go right
    else if (curr->data < prefix[i])
    {
      curr = curr->right;
      //i++;
    }
  }

  // NOW WE ARE AT THE LAST NODE FOR CURR
  // Make a pair to store the freq and word in the queue
  // Make a priority queue to grab them in necessary order
  std::pair<int, std::string> theWord;
  //std::priority_queue<theWord> myPQ;
  std::priority_queue<pair<int, std::string>> myPQ;
  std::vector<std::string> words;
  std::string popWord = "";

  // The case for one word in the middle 
  if (curr->middle == NULL)
  {
    myPQ.push({curr->freq, curr->endNode});
    popWord = myPQ.top().second;
    words.push_back(popWord);
    myPQ.pop();
    return words;
  }

  return words;


  //occQueue.push(curr->freq, curr->endNode);
 /* while(!occQueue.empty()) {
 //   TSTNode qNode = occQueue.front();
 //   occQueue.pop();
    if(curr->left != NULL) {
      occQueue.push(curr->left->freq, curr->left->endNode);
    }
    if(curr.right != NULL) {
      occQueue.push(curr->right->freq, curr->right->endNode);
    }
  }*/


  //return words;

  // THIS IS HOW I PUSH INTO MY QUEUE
  //myPQ.push({curr->freq, curr->endNode});


  // THIS MEANS WE ARE AT OUR END WORD WE ARE LOOKING FOR
  /*if (curr->middle == NULL)
    {
    myPQ.push({curr->freq, curr->endNode});
    auto const& ps = myPQ.top();
  //cout<< "PRIORITY " << ps.int << "WORD " << ps.string << endl
  myPQ.pop();
  //return myPQ;

  }*/

  // curr = //last node;
  // vector<bool> &discovered;
  //TRAVERSE TREE

  // if(curr == NULL) {}

  //  int vectIter = 0;
  /*i = 0;
    int insertNum = 0;
    unsigned int j = 0;
    int swapNum = 0;
    string insertString = "";
    string swapString = "";*/

  // while(true) {
  /*for (; i < prefix.length(); i++)
    {
    cout << "THE PREFIX out loop LETTER IS " << prefix[i] << endl;
    cout << "THE islower LETTER IS " << (islower(prefix[i]))  << endl;
    cout << "THE isspace is LETTER IS " << (isspace(prefix[i]))  << endl;


    if(!islower(prefix[i]) || isspace(prefix[i])) {
  //if (islower(prefix[i]) || isspace(prefix[i])) {
  cout << "THE PREFIX in loop LETTER IS " << prefix[i] << endl;
  cout << "Invalid Input. Please retry with correct input" << endl;
  orderVectString.clear();
  return orderVectString;
  }
  }*/

  // BELOW WAS COMMENTED OUT BEFORE I STARTED DOING WHAT I DID
  /*  occQueue.push(curr->data);
      while(!occQueue.empty()) {
      TSTNode qNode = occQueue.front();
      occQueue.pop();
      if(qNode.occurence != 0) {
      orderVectNode.add(qNode);
      }

      if(qNode.left != NULL) {
      occQueue.push(qNode.left);
      }
      if(qNode.right != NULL) {
      occQueue.push(qNode.right);
      }
      }*/

  /*occQueue.push(curr);
    while(!occQueue.empty()) {
    if(occQueue.top()->nodeCheck == false) {
    occQueue.pop();
    }

    if(occQueue.top()->left != NULL) {
    occQueue.push(occQueue.top()->left);
    }
    if(occQueue.top()->right != NULL) {
    occQueue.push(occQueue.top()->right);
    }
    }*/



  /* for(i = 0; i < orderVectNode.size(); i++) {
     insertNum = orderVectNode[i] -> occurence;
     insertString = orderVectNode[i] -> data;*/
  /*while(!occQueue.empty()) {
    insertNum = occQueue.top()->freq;
    insertString = occQueue.top()->data;
    occQueue.pop();

    orderVectNum[0] = insertNum;
    orderVectString[0] = insertString;

    for(j = 1; j <num_completions - 1; j++) {
    if(orderVectNum[j] < insertNum) {
    swapNum =  orderVectNum[j];
    swapString = orderVectString[j];
    orderVectNum[j] = insertNum;
    orderVectString[j] = insertString;
    insertNum = swapNum;
    insertString = swapString;
    break;
    }
  // break;
  }

  }*/
  // break;
  //return orderVectString;
}



/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}

void DictionaryTrie::deleteAll(TSTNode* t)
{
  if (t)
  {
    deleteAll(t->left);
    deleteAll(t->right);
    deleteAll(t->middle);
    delete t;
  }
}

/* Constructor for the Nodes in the TST */
//TSTNode::TSTNode(char & c) : left(NULL), middle(NULL), right(NULL), parent(NULL), data(c) {}
