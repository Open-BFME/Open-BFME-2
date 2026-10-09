// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
// Target lookup5C8176..5C81D8 RET8 proves coordinate-by-value and grid
// offsets0/4/8/C/14/18. STLport vector size/index implements native72B cells.
// WB1567380 overlap-linking twin plus named initOverlappingCells call
// establish subsystem and eight-neighbour role; original method name unknown.
// Volatile coordinates are an emitter view of target repeated reads and load
// order, not a claim about the original source qualifiers or concurrency.
// The lookup is defined first: its actual XMM0/1/2 clobbers prove caller
// XMM3/4/5 preservation. Parameter Coord2D destructor preserves native copy ABI.
struct FloatPair {
 FloatPair(){} FloatPair(const FloatPair &o):x(o.x),y(o.y){} ~FloatPair(){}
 float x,y;
};
class LargeGroupAudioGridCell {public: void rva005C879E(LargeGroupAudioGridCell **); volatile float x,y;char opaque[64];};
struct Rva005C8176Owner { char opaque[16];float scale;};
class Rva005C8176 { public:
 void *rva005C8176(FloatPair position);
 FloatPair origin;_STL::vector<LargeGroupAudioGridCell> cells;Rva005C8176Owner *owner;int columns;
 __forceinline unsigned size()const{return cells.size();}
 __forceinline LargeGroupAudioGridCell *at(int index){return &cells[index];}
};
void *Rva005C8176::rva005C8176(FloatPair position){
 position.x-=origin.x;position.y-=origin.y;
 float scale=owner->scale;
 int x=static_cast<int>(position.x/scale),y=static_cast<int>(position.y/scale);
 if(x<0 || x>=columns)return 0;
 int index=y*columns+x;
 if(index<0 || static_cast<unsigned>(index)>=size())return 0;
 return at(index);
}
class Rva005C81D8 {public:
 void rva005C81D8(Rva005C8176 *,Rva005C8176 *,Rva005C8176 *);
 char opaque[8];_STL::vector<LargeGroupAudioGridCell> cells;Rva005C8176Owner *owner;int columns;
};

void Rva005C81D8::rva005C81D8(Rva005C8176 *horizontal,Rva005C8176 *vertical,Rva005C8176 *diagonal){
 float scale=owner->scale;
 for(LargeGroupAudioGridCell *cell=cells.begin();cell!=cells.end();++cell){
  FloatPair p;p.x=0;p.y=0;
  LargeGroupAudioGridCell *neighbours[8];
  p.x=cell->x+scale/2.0f;p.y=cell->y;
  neighbours[0]=static_cast<LargeGroupAudioGridCell *>(horizontal->rva005C8176(p));
  p.x=cell->x-scale/2.0f;
  neighbours[1]=static_cast<LargeGroupAudioGridCell *>(horizontal->rva005C8176(p));
  p.y=cell->y+scale/2.0f;p.x=cell->x;
  neighbours[2]=static_cast<LargeGroupAudioGridCell *>(vertical->rva005C8176(p));
  p.y=cell->y-scale/2.0f;
  neighbours[3]=static_cast<LargeGroupAudioGridCell *>(vertical->rva005C8176(p));
  p.y=cell->y+scale/2.0f;p.x=cell->x+scale/2.0f;
  neighbours[4]=static_cast<LargeGroupAudioGridCell *>(diagonal->rva005C8176(p));
  p.y=cell->y-scale/2.0f;
  neighbours[5]=static_cast<LargeGroupAudioGridCell *>(diagonal->rva005C8176(p));
  p.x=cell->x-scale/2.0f;
  neighbours[7]=static_cast<LargeGroupAudioGridCell *>(diagonal->rva005C8176(p));
  p.y=cell->y+scale/2.0f;
  neighbours[6]=static_cast<LargeGroupAudioGridCell *>(diagonal->rva005C8176(p));
  cell->rva005C879E(neighbours);
 }
}
