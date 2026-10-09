// _VP6_BuildHuffTree
// partial score=0.7 date=2026-10-09
// cl: /O2 /G6 /MD
// Clean-room: specs/001c69e0.md and specs/001c6980.md, plus retail.
union HuffEdge {
 unsigned int value;
 struct { unsigned int leaf:1, index:7, unused:24; } bits;
};
struct HuffNode { HuffEdge left, right; unsigned char probability; };
struct HuffSort { int next, weight; HuffEdge edge; };
static void InsertSorted(HuffSort *records, int item, int *head)
{
 int current=*head;
 int previous=current;
 while(current!=-1 && records[item].weight>records[current].weight) {
  previous=current;
  current=records[current].next;
 }
 if(current==*head) *head=item;
 else records[previous].next=item;
 records[item].next=current;
}
extern "C" void VP6_BuildHuffTree(HuffNode *nodes, int *weights, int count)
{
 HuffSort records[64];
 int head=0;
 int nodeCount=count-1;
 for(int i=0;i<count;++i) {
  records[i].edge.bits.index=i;
  records[i].edge.bits.leaf=1;
  if(weights[i]==0) weights[i]=1;
  records[i].weight=weights[i];
  records[i].next=-1;
 }
 int item=count;
 for(int i=1;i<count;++i) InsertSorted(records,i,&head);
 while(records[head].next!=-1) {
  int second=records[head].next;
  int weight=records[head].weight+records[second].weight;
  --nodeCount;
  nodes[nodeCount].left=records[head].edge;
  nodes[nodeCount].right=records[second].edge;
  nodes[nodeCount].probability=(records[head].weight*256)/weight;
  records[item].weight=weight;
  records[item].next=-1;
  records[item].edge.bits.index=nodeCount;
  records[item].edge.bits.leaf=0;
  head=records[second].next;
  InsertSorted(records,item,&head);
  ++item;
 }
}
