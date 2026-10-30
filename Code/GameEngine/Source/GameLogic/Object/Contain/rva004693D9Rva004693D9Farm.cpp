// ?rva004693D9@Rva004693D9@@QAEXXZ
// ?rva004693D9@Rva004693D9@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include /Ireference/shims/bfme2_ascii
// stlport
// Native4693D9..46950D RET0; WB10B6D30 gives complete formation-center
// semantics. BFME1 f98983a7 Rva00245010RecordBuild calls the analogous helper
// 23B9F0 but carries no definition. Target establishes rank18C/name4/position8,
// kind-of11 byte109 mask8, and owner188 records28 with Coord2D positions4/C.
// If a kind11 rank exists, center on its first slot; otherwise average all
// slots. Subtract center and refresh each original position from the result.
#include <vector>
#include "Lib/Coord2D.h"
#include "ascii_string.h"
class ThingTemplate;
class ThingFactory {public: const ThingTemplate *findTemplate(const AsciiString&);};
extern ThingFactory *TheThingFactory;
class Rva002D06CA { public: void *rva002D06CA(const AsciiString*); };
struct Rva004693D9Input { float x,y; int partner,localIndex; };
template<class T> struct Rva004693D9Range {
 T *first,*finish,*limit;
 __forceinline unsigned size() const { return finish-first; }
};
struct Rva004693D9Rank {
 int key; AsciiString name; _STL::vector<Rva004693D9Input> positions;
};
struct Rva004693D9Definition {
 char opaque000[0x18c]; _STL::vector<Rva004693D9Rank*> ranks;
};
struct Rva004693D9Template { char opaque000[0x109]; unsigned char kinds109; };
struct Rva004693D9Slot { int key; Coord2D position,original; float value; int partner; };
class Rva004693D9 {
public:
 void rva004693D9();
 void *vptr; Rva004693D9Definition *definition;
 char opaque008[0x188-8]; _STL::vector<Rva004693D9Slot> slots;
};
static __forceinline Coord2D &rva4693Scale(Coord2D &vec,float f) {vec.x*=f;vec.y*=f;return vec;}
static __forceinline Coord2D &rva4693Sub(Coord2D &vec,const Coord2D &other) {vec.x-=other.x;vec.y-=other.y;return vec;}
void Rva004693D9::rva004693D9()
{
 int preferred=-1;
 const _STL::vector<Rva004693D9Rank*> &ranks=definition->ranks;
 unsigned offset=0;
 for(unsigned i=0;i<ranks.size();++i) {
  const AsciiString &name=ranks[i]->name;
  Rva004693D9Template *type=(Rva004693D9Template*)TheThingFactory->findTemplate(name);
  if(type && (type->kinds109&8)) {preferred=offset;break;}
  offset+=ranks[i]->positions.size();
 }
 float scale=0.0f;
 Coord2D center; center.x=0;center.y=0;
 int count=0,index=0;
 for(Rva004693D9Slot *slot=slots.begin();slot!=slots.end();++index,++slot) {
  center.x+=slot->position.x;center.y+=slot->position.y;++count;
  if(index==preferred) {center=slot->position;count=1;break;}
 }
 if(count) {scale=1.0f/count;rva4693Scale(center,scale);}
 for(Rva004693D9Slot *slot=slots.begin();slot!=slots.end();++slot) {
  rva4693Sub(slot->position,center);
  slot->original=slot->position;
 }
}
