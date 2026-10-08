// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
// Native 00462E3A..00462F34: add/remove an object from the world and recurse
// through its contained riders using primary slot 24. The whole existing
// OpenContain.cpp and WB 01192C00 were inspected; ZH/BFME1's two-argument
// addOrRemoveObjFromWorld provides purpose, while native RET12 proves this
// three-argument ABI. Only the low byte of add is tested, its full stack word
// is forwarded, and the third argument is unused. Method/class spelling is
// address-derived because the WB export names a folded BitFlags test.
// Native fields: owner8/position38, Object flag454 and module250; secondary
// slot44 returns the independently corroborated 16-byte mask, bit61 controls
// recursive slot24. Module slot70 returns two words; only its list pointer is
// used. Control-word ownership and original application type remain unknown.
// Existing provider names and the actual TheAI global replace no data pins.
#include <list>
#include "Lib/Coord3D.h"
class Drawable { public: void setDrawableHidden(bool); };
class Object {
public:
    void teleportTo(const Coord3D *, bool);
    Drawable *getDrawable() const;
    void leaveGroup();
    void rva0028DCC4();
    void rva0028BAC0();
};
class Pathfinder {
public:
    void AddObjectToPathfindMap(Object *);
    void RemoveObjectFromPathfindMap(Object *);
};
class AI { public: char unknown00[0x10]; Pathfinder *pathfinder10; };
extern AI *TheAI;
template <int N> class Rva00462E3ASlots : public Rva00462E3ASlots<N - 1> {
public: virtual void gap(char (*)[N]);
};
template <> class Rva00462E3ASlots<0> {};
struct Rva00462E3AMask {
    unsigned int words[4];
    bool test(int i) const { return (words[i / 32] >> (i % 32)) & 1; }
};
class Rva00462E3AStatus : public Rva00462E3ASlots<44> {
public: virtual Rva00462E3AMask status(int);
};
struct Rva00462E3AItems { void *control; _STL::list<Object *> *list; };
class Rva00462E3AModule : public Rva00462E3ASlots<70> {
public: virtual Rva00462E3AItems items();
};
struct Rva00462E3AObject {
    char unknown00[0x38];
    Coord3D position38;
    char unknown44[0x250 - 0x44];
    Rva00462E3AModule *module250;
    char unknown254[0x454 - 0x254];
    bool flag454;
};
class Rva00462E3A : public Rva00462E3ASlots<24> {
public:
    virtual void slot24(Object *, int, int);
    void rva00462E3A(Object *, int, int);
    void *moduleData4;
    Object *owner8;
    char unknown0C[0x20 - 0xC];
    Rva00462E3AStatus status20;
};
void Rva00462E3A::rva00462E3A(Object *object, int add, int unused)
{
    Rva00462E3AObject *view = reinterpret_cast<Rva00462E3AObject *>(object);
    if (static_cast<unsigned char>(add)) {
        object->teleportTo(&reinterpret_cast<Rva00462E3AObject *>(owner8)->position38, true);
        if (!view->flag454) object->rva0028DCC4();
        if (object->getDrawable()) object->getDrawable()->setDrawableHidden(false);
        TheAI->pathfinder10->AddObjectToPathfindMap(object);
    } else {
        object->leaveGroup();
        if (view->flag454) object->rva0028BAC0();
        if (object->getDrawable()) object->getDrawable()->setDrawableHidden(true);
        TheAI->pathfinder10->RemoveObjectFromPathfindMap(object);
    }
    Rva00462E3AModule *module = view->module250;
    if (module) {
        Rva00462E3AItems riders = module->items();
        for (_STL::list<Object *>::iterator it = riders.list->begin(); it != riders.list->end(); ++it) {
            if (status20.status(0).test(61)) slot24(*it, add, 0);
        }
    }
}
