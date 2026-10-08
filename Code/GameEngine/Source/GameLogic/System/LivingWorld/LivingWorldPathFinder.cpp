// cl: /O1 /G7 /arch:SSE /MD
// Native003F71D4..003F7209 RET8; vtable007E4340 slots00/04
// both reach this body. Entry points supply node coordinates at10/14;
// native loads the pair before subtracting the second node and calls the
// independently rowed Coord2D::length. Original metric/slot names unproven.
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
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
