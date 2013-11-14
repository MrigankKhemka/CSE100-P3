#include "HCTree.hpp"



void HCTree::build(const vector<int>& freqs)
{
  std::priority_queue<HCNode*, std::vector<HCNode*>,HCNodePtrComp> pq;
  //Ordering the nodes by counts using a priority queue
  for(int i=0; i < 256; i++) {
    if (freqs[i] > 0) {
      HCNode* p = new HCNode(freqs[i],i);
      leaves[i] = p;
      pq.push(p);
    } 
  }
  
  //Constructing the tree from the priority queue
  while(pq.size() != 0) {
    if(pq.size() == 1) {
      root = pq.top();
    }
    else {
      //Highest priority
      HCNode* p1 = pq.top();
      pq.pop();
      //Second highest priority
      HCNode* p2 = pq.top();
      pq.pop();
      //Compute priority of parent
      int total = p1->count + p2->count;
      HCNode* parent = new HCNode(total,0,p1,p2);
      //Set priority of new parent node to sum of priority of children
      parent->count = total;
      //Set the 2 highest priorities as the children of the new node
      p1->p = parent;
      p2->p = parent;
      //Set the new node's children as the 2 highest priority nodes
      parent->c0 = p1;
      parent->c1 = p2;
      //Add the new node back into the priority queue
      pq.push(parent);
    }
  } 
}
