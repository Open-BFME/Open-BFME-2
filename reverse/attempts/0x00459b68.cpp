// ?rva00459B68@SiegeDockingBehavior@@ABEXXZ
// partial score=0.85 date=2026-10-10
// cl: /O1 /G7 /MD /DNDEBUG /EHsc /ICode/GameEngine/Source/Common
// stlport
#include <vector>
class Object;
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum NameKeyType { INVALID_NAME_KEY=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class SiegeDockingBehavior;
class Object {friend class SiegeDockingBehavior;
protected:Module *findModule(NameKeyType)const;
public:char p00[0x74];ObjectID id;char p78[0x438-0x78];unsigned char dead;
};
#define V(n) virtual void s##n()=0;
class Rva00459B68Iface {public:
V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) 
virtual ObjectID s50()=0;
};
#undef V

struct SiegeDockEntry {char p00[0x20];ObjectID objectID;};
class SiegeDockingBehavior {
 void rva00459B68()const;
public:
 char p00[8];Object *object;char p0C[0x24-0x0C];_STL::vector<SiegeDockEntry*>entries;
};
void SiegeDockingBehavior::rva00459B68()const {
 for(_STL::vector<SiegeDockEntry*>::const_iterator i=entries.begin();i!=entries.end();++i){
 SiegeDockEntry *entry=*i;
 if(!entry || !entry->objectID)continue;
 Object *other=TheGameLogic->findObjectByID(entry->objectID);
 if(!other || (other->dead&1)){entry->objectID=INVALID_OBJECT_ID;continue;}
 static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
 Module *module=other->findModule(key);
 if(!module){entry->objectID=INVALID_OBJECT_ID;continue;}
 ObjectID mine=object->id;
 if(((Rva00459B68Iface*)((char*)module+0x24))->s50()!=mine)entry->objectID=INVALID_OBJECT_ID;
 }
}
