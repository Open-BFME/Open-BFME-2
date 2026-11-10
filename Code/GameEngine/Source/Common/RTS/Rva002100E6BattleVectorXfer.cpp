// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native2100E6..2101C6 (224B), thiscall RET8. Called twice from2101C6.
// Stock BF1 LivingWorldRegionManager transfer loops supply the version/load
// skeleton; native independently proves Snapshot slot30, unsigned count7C,
// pointer vector reservation/push and0x40 default Battle constructor3F6A3A.
// ModuleData is the existing byte-proved4-byte vector carrier instantiation;
// these values are LivingWorldBattle pointers, not ModuleData identities.
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
class ModuleData;
struct XferVersion {unsigned char version,current;unsigned short padding;};
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"
#include "../../../Include/GameLogic/LivingWorldBattle.h"
namespace _STL {
 template<>void vector<const ModuleData*,allocator<const ModuleData*> >::reserve(unsigned int);
 template<>void vector<const ModuleData*,allocator<const ModuleData*> >::push_back(const ModuleData*const&);
}
#include "../../../Include/GameLogic/Rva0020EE29.h"
void Rva0020EE29::rva002100E6(void*arg,void*range){
 Xfer*xfer=(Xfer*)arg;
 _STL::vector<const ModuleData*>&battles=*(_STL::vector<const ModuleData*>*)range;
 XferVersion version;version.version=1;version.current=1;(*xfer == reinterpret_cast<Xfer::Version &>(version));
 if(xfer->IsLoading()){
  int count;(*xfer == count);
  ((_STL::vector<void*>*)&battles)->erase(((_STL::vector<void*>*)&battles)->begin(),((_STL::vector<void*>*)&battles)->end());
  battles.reserve(count);
  for(int i=0;i<count;++i){
   const ModuleData*battle=(const ModuleData*)new LivingWorldBattle;
   (*xfer == *reinterpret_cast<Snapshot *>(const_cast<ModuleData *>(battle)));battles.push_back(battle);
  }
 }else{
  int count=battles.size();(*xfer == count);
  for(int i=0;i<count;++i)(*xfer == *reinterpret_cast<Snapshot *>(const_cast<ModuleData *>(battles[i])));
 }
}
