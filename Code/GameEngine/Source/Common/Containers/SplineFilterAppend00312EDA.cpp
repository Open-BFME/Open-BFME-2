// BF1 donor9cbfb551fe20dae985f91f2319d8997287b6a705 Rva003A3A90.cpp and
// Rva003A3B50RecordAppend.cpp supply the184B record/vector semantic lead.
// Native312EDA..313008 proves this complete302B linked-input import operation:
// clear vector2C then reset/append first node; merge nodes within squared100
// into the last record otherwise append. Existing record constructor3118DF
// reset311431 assignment311537 destructor89851 and vector providers all rowed.
// Target destructor8B77D stores BC7514 with slot1=312EDA; retain its existing
// address owner. Prefix and input-node views are partial, no allocating layout.
// Input next20/count4C and coordinateC/10/14 are direct target facts; spline
// role inferred from matched184B family. Original application names unknown.
// Full bytes plus EH verified. No corresponding clean ZH spline service body.
// cl: /O1 /Oy- /arch:SSE /G7 /MD /EHs /D_STLP_USE_STATIC_LIB /DNDEBUG
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
struct Rva00311431Arg {
 unsigned unknown00,word04,word08;float x,y,z;char pad18[8];Rva00311431Arg *next20;char pad24[0x4c-0x24];int count4c;
 Rva00311431Arg *next()const{return count4c>0?next20:0;}
};
struct Rva003A35A0Element {
 Rva003A35A0Element();Rva003A35A0Element(const Rva003A35A0Element&);~Rva003A35A0Element();
 Rva003A35A0Element &operator=(const Rva003A35A0Element&);
 Rva003A35A0Element *rva00311431(const Rva00311431Arg*);
 char bytes[184];
};
class Rva008B77D {public:
 void rva00312EDA(const Rva00311431Arg*);
 char pad[0x2c];_STL::vector<Rva003A35A0Element>records;

};
void Rva008B77D::rva00312EDA(const Rva00311431Arg*node) {
 records.clear();
 if(node){
 Rva003A35A0Element temp;
 temp.rva00311431(node);records.push_back(temp);
 while(1) {
  float x=node->x,y=node->y,z=node->z;
  node=node->next();if(!node)break;
  x-=node->x;y-=node->y;z-=node->z;
  float distance=z*z+y*y+x*x;
  if(100.0f>distance)records[records.size()-1]=*temp.rva00311431(node);
  else{temp.rva00311431(node);records.push_back(temp);}
 }
 }
}
