#include "HCTree.hpp"

HCTree:: ~HCTree()
{
}

void HCTree::build(const vector<int>& freqs)
{
  std::priority_queue<HCNode*, std::vector<HCNode*>,HCNodePtrComp> pq;
  //Ordering the nodes by counts using a priority queue
  for(int i=0; i < 256; i++) {
    if (freqs[i] > 0) {
      HCNode* nodep = new HCNode(freqs[i],i);
      leaves[i] = nodep;
      pq.push(nodep);
    } 
  }
  
  //Constructing the tree from the priority queue
  while(pq.size() > 1) {
    cout << pq.size() << endl;
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
  if(pq.size() == 1) {
    root = pq.top();
  }


}
 
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

int HCTree::decode(BitInputStream& in) const 
{
  HCNode* curr = root;
  int num;
  while(curr->c1 != 0 || curr->c0 != 0)
  {
    num = in.readBit(); 
    if(num == 0) {
      curr = curr->c0;
    }
    else if(num == 1) {
      curr = curr->c1;
    }
  }
  return (int)curr->symbol;
}



/* Checkpoint methods

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
