// LivingWorldPathFinder::FindShortestPath
// partial score=0.91 date=2026-10-09
// cl: /O1 /Ob1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Native003F71D4..003F7209 RET8; vtable007E4340 slots00/04
// both reach this body. Entry points supply node coordinates at10/14;
// native loads the pair before subtracting the second node and calls the
// independently rowed Coord2D::length. Original metric/slot names unproven.
#include "../../Code/Libraries/Include/Lib/Coord2D.h"
#include <vector>
struct Rva003F71D4Point {char pad[16];float x,y;};
class Rva003F71D4Metric {
 public:
 virtual float v00(const Rva003F71D4Point *,const Rva003F71D4Point *);
 virtual float v01(const Rva003F71D4Point *,const Rva003F71D4Point *);
 virtual void v02(const Rva003F71D4Point *);
 virtual bool v03(int,int);
};
float Rva003F71D4Metric::v00(const Rva003F71D4Point *a,const Rva003F71D4Point *b) {
 Coord2D d={a->x,a->y};
 d.x-=b->x;
 d.y-=b->y;
 return d.length();
}

// Native table007E4340: slot04 repeats the distance; slot08 is RET4;
// slot0C compares the two node pointers, the independently rowed14B body.
float Rva003F71D4Metric::v01(const Rva003F71D4Point *a,const Rva003F71D4Point *b) {
 Coord2D d={a->x,a->y}; d.x-=b->x; d.y-=b->y; return d.length();
}
void Rva003F71D4Metric::v02(const Rva003F71D4Point *) {}
bool Rva003F71D4Metric::v03(int a,int b) {return a==b ? true : false;}

enum ObjectID { INVALID_ID=0 };
struct Rva003EF6A0Entry { ObjectID key;char pad04[12];float x,y;int pad18;float g,h,f;Rva003EF6A0Entry *parent;};
struct Rva003EF6A0Span { Rva003EF6A0Entry **begin,**end; };
Rva003EF6A0Entry *__stdcall Rva003EF6A0Find(Rva003EF6A0Span *,int);
struct Rva003EF9DCNode;
void __stdcall Rva003EF9DCFill(Rva003EF9DCNode *,_STL::vector<ObjectID> *);
struct Rva003EF634Node;
int __stdcall Rva003EF634Count(Rva003EF634Node *);
class LivingWorldPathFinder {
 public:
 int FindShortestPath(Rva003F71D4Metric *,int,ObjectID,ObjectID,_STL::vector<ObjectID> *,bool);
 Rva003EF6A0Entry *rva003EF6A0(Rva003EF6A0Span *,ObjectID);
 void rva003EF8E1(Rva003EF6A0Entry *,int,bool);
 private:
 _STL::vector<Rva003EF6A0Entry *> nodes;
 Rva003EF6A0Entry *start,*goal;
 _STL::vector<Rva003EF6A0Entry *> open,closed;
 Rva003F71D4Metric *metric;
};
int LivingWorldPathFinder::FindShortestPath(Rva003F71D4Metric *visit,int player,ObjectID from,ObjectID to,_STL::vector<ObjectID> *result,bool allow) {
 metric=visit;
 if(from==to) {if(result) {result->erase(result->begin(),result->end());result->push_back(from);}return 0;}
 _STL::vector<Rva003EF6A0Entry *> *active=&open;
 active->erase(active->begin(),active->end());closed.erase(closed.begin(),closed.end());
 if(result) result->erase(result->begin(),result->end());
 Rva003EF6A0Entry *first=rva003EF6A0(reinterpret_cast<Rva003EF6A0Span *>(this),from);
 start=first;
 goal=rva003EF6A0(reinterpret_cast<Rva003EF6A0Span *>(this),to);
 if(!first||!goal)return -1;
 first->g=0;first->h=0;first->f=0;start->parent=0;
 active->push_back(start);
 while(active->size()) {
  Rva003EF6A0Entry *node=active->front();active->erase(active->begin());
  metric->v02(reinterpret_cast<Rva003F71D4Point *>(node));
  if(metric->v03((int)node,(int)goal)) {
   if(result) {Rva003EF9DCFill(reinterpret_cast<Rva003EF9DCNode *>(node),result);return result->size()-1;}
   return Rva003EF634Count(reinterpret_cast<Rva003EF634Node *>(node));
  }
  rva003EF8E1(node,player,allow);
  closed.push_back(node);
 }
 return -1;
}
