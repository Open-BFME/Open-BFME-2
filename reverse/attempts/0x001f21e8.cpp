// ?rva001F21E8@Rva001F21E8@@QAEXPAUCoord3D@@@Z
// partial score=0.844802 date=2026-10-10
// cl: /O1 /G7 /Ob1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
#include <vector>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
class Object;
namespace _STL {template<> inline __declspec(noinline) _STLP_alloc_proxy<Object**,Object*,allocator<Object*> >::_STLP_alloc_proxy(const allocator<Object*>&a,Object**p):allocator<Object*>(a),_M_data(p){} }
namespace _STL {template<> __forceinline _Vector_base<Object*,allocator<Object*> >::_Vector_base(const allocator<Object*>&a):_M_start(0),_M_finish(0),_M_end_of_storage(a,(Object**)0){} }
namespace _STL {template<> __forceinline vector<Object*>::vector(const allocator<Object*>&a):_Vector_base<Object*,allocator<Object*> >(a){} template<>void vector<Object*>::push_back(Object*const&);template<>vector<Object*>::~vector();}
class TerrainLogic {
public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual Object*getFirstWaypoint();};
extern TerrainLogic*TheTerrainLogic;
int GetGameLogicRandomValue(int,int,char*,int);
class Rva001F21E8 {public:void rva001F21E8(Coord3D*);private:char unknown[0x10c];StringBase<char>prefix;};
struct Rva001F21E8Waypoint {char unknown[8];StringBase<char>name;Coord3D position;char unknown18[4];Object*next;};
void Rva001F21E8::rva001F21E8(Coord3D*position){
 _STL::vector<Object*>matches;
 for(Object*node=TheTerrainLogic->getFirstWaypoint();node;node=((Rva001F21E8Waypoint*)node)->next){
  if(((Rva001F21E8Waypoint*)node)->name.startsWith(prefix))matches.push_back(node);
 }
 int count=matches.size();
 if(count>0){int index=GetGameLogicRandomValue(0,count-1,(char*)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp",1973);
  *position=((Rva001F21E8Waypoint*)matches[index])->position;
 }
}
