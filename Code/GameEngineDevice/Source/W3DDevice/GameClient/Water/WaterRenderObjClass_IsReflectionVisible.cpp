// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native0007FD89..0007FE1B RET4. Receiver vector108/10C and entry owner40
// are measured; original receiver and predicate names are unresolved.
// Existing ReflectionTexture callback80168 independently binds globals
// TheWritableGlobalData+5E and TheWaterTransparency final override+50.
// The inline Overridable::getFinalOverride compiles to the native 14B getter.
// Callee308DF0 uses ECX and RET0, returning owned pointer84 in EAX.
// Callee7FB85 uses ECX and arg8, returns AL, RET4 after polygon clipping.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataGate {char unknown00[0x5e];bool enabled;};
#include "../../../../../GameEngine/Include/GameClient/Water.h"
template<class T> class OVERRIDE {
public:
 operator const T *() const {if(!pointer)return 0;return (const T *)pointer->getFinalOverride();}
 const T *operator->() const {if(!pointer)return 0;return (const T *)pointer->getFinalOverride();}
 const T *pointer;
};
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
class Rva00308DF0Ref {public:char unknown00[0x1c];int kind;};
#include "../../../../Include/W3DDevice/GameClient/Rva00308DF0.h"
class Rva0007FD89Entry {
public:char unknown00[0x40];Rva00308DF0 *owner;
 bool rva0007FB85(void *input);
};
class WaterRenderObjClass {
public: bool IsReflectionVisible(void *input);
private:char unknown00[0x108];Rva0007FD89Entry **first,**last,**capacity;
};
bool WaterRenderObjClass::IsReflectionVisible(void *input)
{
 if(!input)return false;
 if(reinterpret_cast<GlobalDataGate *>(TheWritableGlobalData)->enabled && TheWaterTransparency && TheWaterTransparency->m_unk50) {
  for(Rva0007FD89Entry **it=first;it!=last;++it) {
   Rva0007FD89Entry *entry=*it;
   Rva00308DF0Ref *data=entry->owner->rva00308DF0();
   if(data && data->kind>=2 && entry->rva0007FB85(input))return true;
  }
 }
 return false;
}
