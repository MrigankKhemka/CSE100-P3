//------------------------------------------------
// Filename: HCTree.cpp
// Author: Jimmy Li
// Date: 11/19/2013
// Rev-Date: 11/19/2013
//
// Description: Huffman tree class 
//
//-------------------------------------------------

#include "HCTree.hpp"

HCTree:: ~HCTree()
{
}

//------------------------------------------------------------------
// build(const vector<int>& freqs): Constructs a huffman tree 
//
// Input: const vector<int>& freqs
// Output: <none>
//-------------------------------------------------------------------

void HCTree::build(const vector<int>& freqs)
{
  std::priority_queue<HCNode*, std::vector<HCNode*>,HCNodePtrComp> pq;
  //Ordering the nodes by counts using a priority queue
  for(int i=0; i < 256; i++) {
    if (freqs[i] > 0) {
      HCNode* nodep = new HCNode(freqs[i],i);
      leaves[i] = nodep;
      pq.push(leaves[i]);
    } 
  }
  
  //Constructing the tree from the priority queue
  while(pq.size() > 1) {
    //cout << pq.size() << endl;
    //Highest priority
    HCNode* p1 = pq.top();
    pq.pop();
    //Second highest priority
    HCNode* p2 = pq.top();
    pq.pop();
    //Compute priority of parent
    int total = p1->count + p2->count;
    HCNode* parent = new HCNode(total,0,p1,p2);
    //Set the 2 highest priorities as the children of the new node
    p1->p = parent;
    p2->p = parent;
    //Add the new node back into the priority queue
    pq.push(parent);
  } 
  //The remaining node in the queue will be set as root
  if(pq.size() == 1) {
    root = pq.top();
  }


}
 //------------------------------------------------------------------
// encode(byte symbol, BitOutputStream& out) const: Encodes bit by bit
//
// Input: byte symbol, BitOutputStream& out
// Output: <none>
//-------------------------------------------------------------------

void HCTree::encode(byte symbol, BitOutputStream& out) const
{ 
  //Set current to point to the leaf containing the symbol
  HCNode* curr = leaves[symbol];  
  stack<int> treeHolder;  
  //Create stack, storing the code sequence backwards
  //Traverse up the tree from the leaf
  while(curr != root) {
    //"0" pathway if current node is left child
    if(curr == curr->p->c0) {
      treeHolder.push(0);
    }
    //"1" pathway if current node is right child
    else {
      treeHolder.push(1);
    }
    //Set current node to parent node
    curr = curr->p;
  }

  //Loop through stack and store into buffer
  while(treeHolder.size() != 0) {
    out.writeBit(treeHolder.top());
    treeHolder.pop();
  }
}

//------------------------------------------------------------------
// decode(BitInputStream& in) const: Decodes bit by bit
//
// Input:BitInputStream& in 
// Output:int 
//-------------------------------------------------------------------

int HCTree::decode(BitInputStream& in) const 
{
  //Start traversal at root
  HCNode* curr = root;
  int num;
  //Traverse down to leaf
  while(curr->c1 != 0 || curr->c0 != 0)
  {
    //Read bit by bit
    num = in.readBit();
    //Traverse left child if 0 
    if(num == 0) {
      curr = curr->c0;
    }
    //Traverse right child if 1
    else if(num == 1) {
      curr = curr->c1;
    }
  }
  //Return int representation of the symbol in the leaf
  return (int)curr->symbol;
}


//------------------------------------------------------------------
// encode(byte symbol, ofstream& out) const: Checkpoint encode method
//
// Input: byte symbol, ofstream& out
// Output: <none>
//-------------------------------------------------------------------

/* 

void HCTree::encode(byte symbol, ofstream& out) const
{
  //Set current to point to the leaf containing the symbol
  HCNode* curr = leaves[symbol];  
  stack<int> treeHolder;  
  //Create stack, storing the code sequence backwards
  while(curr != root) {
    if(curr == curr->p->c0) {
      treeHolder.push(0);
    }
    else {
      treeHolder.push(1);
    }
    curr = curr->p;
  }
  if(treeHolder.size() != 0) {
    out << treeHolder.top() << " ";
    treeHolder.pop();
  }

}


//------------------------------------------------------------------
// decode(ifstream& in) const: Checkpoint decode method
//
// Input:ifstream& in 
// Output:int 
//-------------------------------------------------------------------

int HCTree::decode(ifstream& in) const 
{
  HCNode* curr = root;
  int num;
  while(curr->c1 != 0 || curr->c0 != 0)
  {
    in >> num; 
    //cout << "num:" <<  num;
    if(num == 0) {
      curr = curr->c0;
    }
    else if(num == 1) {
      curr = curr->c1;
    }
  }
  return (int)curr->symbol;
}
*/
