// cl: /O1 /G7 /arch:SSE /MD
// Native359E93..35A005370B RET16; WB E60B50 unnamed in TerrainResourceManager.
// Existing Rva0035A238 callers prove list14, Object key74 and callback identity.
// Preserve their address-derived class/name until a coordinated owner rename.
// Target accesses prove maxRadius18 origin1C/20 cell3C; getter at key74 keeps
// the native conditional mask and visitor-construction register shape.
// Constructor3598D3's callback35AB7F and the circle visitor35997F are owned.
// The existing float-store14B twin481FAF writes the module's extra scalar2C;
// no matrix identity is asserted by that call view.
// Plain float casts emit _ftol2; the established WWMath fld/fistp conversion
// reproduces the native rounding shape. Only this compiler blocker uses asm.
#include <math.h>
#include "TerrainResourceVisitorView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public: NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Rva0035A238;
class Object {
 friend class Rva0035A238;
 protected: Module *findModule(NameKeyType) const;
 public: char pad00[0x38]; Coord3D position38; char pad44[0x30];int key74;
};
struct Rva0035A238Argument {char pad00[0x74];int key74; 
// ?Rva0035A238Argument::getKey present-unmatched
int getKey() const {return key74;} };
class Rva00359835 {public: float rva00359835() const;};
class Rva00481FAFFloatSlot {public: void store(float);};
class Rva000CBA20;
class TerrainResourceManager {public: void rva0035997F(int,int,int,void*);};
class Rva0035A238 {
public:
 void rva00359E93(Rva0035A238Argument*,float,bool,bool);
 void rva00359D99(Rva000CBA20*,float);
private:
 char pad00[0x18];float maxRadius18,originX1C,originY20;char pad24[0x18];float cell3C;
};
__forceinline int cellInteger(float value)
{
 int result;
 __asm fld value
 __asm fistp result
 return result;
}

void Rva0035A238::rva00359E93(Rva0035A238Argument *argument,float radius,bool full,bool extra)
{
 static NameKeyType key=TheNameKeyGenerator->nameToKey("TerrainResourceBehavior");
 Object *object=reinterpret_cast<Object*>(argument);
 Module *module=object->findModule(key);
 if(!module) return;
 float x=object->position38.x-originX1C;
 float y=object->position38.y-originY20;
 int cellX=cellInteger((float)floor(x/cell3C+0.5f));
 int cellY=cellInteger((float)floor(y/cell3C+0.5f));
 int cellRadius=cellInteger((float)ceil(radius/cell3C));
 int mask=0;
 if(full) mask=0x7FFFF43;
 Rva003598D3 visitor((int)this,mask,argument->getKey(),extra);
 reinterpret_cast<TerrainResourceManager*>(this)->rva0035997F(cellX,cellY,cellRadius,&visitor);
 reinterpret_cast<Rva00481FAFFloatSlot*>(module)->store(reinterpret_cast<const Rva00359835*>(&visitor)->rva00359835());
 if(radius>maxRadius18) maxRadius18=radius;
 if(full) rva00359D99(reinterpret_cast<Rva000CBA20*>(argument),radius+maxRadius18);
}
