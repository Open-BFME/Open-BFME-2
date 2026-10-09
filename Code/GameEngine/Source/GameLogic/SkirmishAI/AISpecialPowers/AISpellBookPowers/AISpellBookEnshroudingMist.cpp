// cl: /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
// WB1596140 names AISpellBookEnshroudingMist::shouldActivate, line31.
// Native5D7B65..5D7C05 iterates the existing combat collector's 4-byte
// Object-pointer slots and offers the first template520==1 position38.
// The owned ModuleData vector is the provider's established opaque slot
// ABI; casts do not establish ModuleData semantics for the Object pointers.
#include <vector>
#include "Lib/Coord3D.h"
class Player;
struct MistTemplateView { char unknown00[0x520]; int type520; };
class Object {
public:
    Player *getControllingPlayer() const;
    __forceinline MistTemplateView *templateView() const { return type4; }
    char unknown00[4]; MistTemplateView *type4;
    char unknown08[0x30]; Coord3D position38;
};
class ModuleData;
class AISpellBookBase { public:
    void findUnitInCombat(_STL::vector<const ModuleData *> *,Player *);
};
class Rva005EE816 { public: bool rva005EE8DD(const Coord3D *,Object *); };
class AISpellBookEnshroudingMist { public:
    virtual bool shouldActivate(Object *);
    char unknown00[0x24]; AISpellBookBase finder28;
};
bool AISpellBookEnshroudingMist::shouldActivate(Object *source)
{
    _STL::vector<const ModuleData *> objects;
    finder28.findUnitInCombat(&objects,source->getControllingPlayer());
    if(!objects.empty()) {
        for(const ModuleData **it=objects.begin();it!=objects.end();++it) {
            if(reinterpret_cast<const Object *>(*it)->templateView()->type520==1)
                return reinterpret_cast<Rva005EE816 *>(this)->rva005EE8DD(
                    &reinterpret_cast<const Object *>(*it)->position38,source);
        }
    }
    return false;
}
