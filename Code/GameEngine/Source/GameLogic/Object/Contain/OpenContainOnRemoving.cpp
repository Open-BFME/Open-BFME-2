// cl: /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
// Substantial reference transfer from clean BFME1 34f59164
// game/GameEngine/Source/GameLogic/Object/Contain/OpenContainOnRemoving.cpp.
// The whole donor and BFME2 reference home, native 00464D02..00464EE7 and
// independently named WB 011957B0 were inspected. Native receiver is the
// contain interface (+20), with owner at -18 and module data at -1C.
// Target-specific keyed Drawable events use the canonical 136-byte prefix;
// state/name cleanup, mask bits 194..198 and timed bonus processing follow.
// The timestamp tree's key comparison is signed. Its mapped application type
// remains unresolved: use the existing signed int-word lookup operation and
// the existing four-byte-payload iterator erase operation on the same nodes.
// This avoids the pre-existing signed-pointer _M_find pin to unsigned357180;
// actual call displacements prove the two providers388F63/5530A8 instead.
// Constructor and ID-value temporaries retain the native lifetimes/stack homes.
#include <map>
#include <set>
#include "Common/BfmeAudioEventPrefix136.h"
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva002390CB {
public:
    Rva002390CB(const Rva002390CB &);
    __forceinline ~Rva002390CB() { if (ref.referent) ref.referent->Release_Ref(); }
    void *unknown00;
    OpaqueRefElement4 ref;
};
class Drawable { public: Rva002390CB rva00462DAE(); Rva002390CB rva00462DC7(); };
class Object { public: Drawable *getDrawable() const; bool addAttributeModifierToPool(const AsciiString &, int); int getID() const { return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this)+0x74); } };
struct Rva00464D02Object { char unknown00[0x74]; int id74; };
class Rva002D9531 { public: void rva002D9531(int); };
class Rva000B6253 { public: Rva000B6253(int,unsigned,unsigned,unsigned,unsigned,unsigned); unsigned words[19]; operator const int *() const { return reinterpret_cast<const int *>(this); } };
struct Rva001E42F2 { void rva001E42F2(const int *); };
struct Rva00463E09Record { char word; };
struct Rva00463D9BElement {
    Rva00463D9BElement(); Rva00463D9BElement(const Rva00463D9BElement &);
    ~Rva00463D9BElement(); Rva00463D9BElement &operator=(const Rva00463D9BElement &);
    char bytes[8];
};
bool operator<(const Rva00463D9BElement &,const Rva00463D9BElement &);
static inline const Rva00463D9BElement &opaqueKey(const int &id) { return reinterpret_cast<const Rva00463D9BElement &>(id); }
typedef _STL::_Rb_tree<int,_STL::pair<const int,Rva00463E09Record>,_STL::_Select1st<_STL::pair<const int,Rva00463E09Record> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,Rva00463E09Record> > > Rva00464D02State;
typedef _STL::_Rb_tree<Rva00463D9BElement,Rva00463D9BElement,_STL::_Identity<Rva00463D9BElement>,_STL::less<Rva00463D9BElement>,_STL::allocator<Rva00463D9BElement> > Rva00464D02Names;
// These exact operations are already supplied by their independently verified
// home units. Keep their dependencies there instead of emitting extra copies.
template<> unsigned Rva00464D02State::erase(const int &);
template<> unsigned Rva00464D02Names::erase(const Rva00463D9BElement &);
typedef _STL::map<int,int> Rva00464D02Times;
typedef _STL::map<int,void *> Rva00464D02EraseView;
template<int N> class Rva00464D02Slots:public Rva00464D02Slots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00464D02Slots<0> {};
class AudioManager:public Rva00464D02Slots<25> { public: virtual void event(const BfmeAudioEventPrefix136 *); };
extern AudioManager *TheAudio;
struct Rva00464D02Data { char unknown00[0x88]; AsciiString *bonusBegin; AsciiString *bonusEnd; void *capacity; unsigned minimumFrames; };
struct ContainModuleInterface { virtual void onRemoving(Object *) = 0; };
class OpenContain:public ContainModuleInterface {
public:
    virtual void onRemoving(Object *);
    char unknown04[0x1C-4];
    Rva00464D02State state1C;
    Rva00464D02Names names28;
    char unknown34[0xD0-0x34];
    Rva00464D02Times timesD0;
    Object *object() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this)-0x18); }
    Rva00464D02Data *data() const { return *reinterpret_cast<Rva00464D02Data *const *>(reinterpret_cast<const char *>(this)-0x1C); }
};
void OpenContain::onRemoving(Object *rider)
{
    if (object()->getDrawable()) {
        BfmeAudioEventPrefix136 sound(object()->getDrawable()->rva00462DAE().ref, 0);
        reinterpret_cast<Rva002D9531 *>(&sound)->rva002D9531(reinterpret_cast<Rva00464D02Object *>(object())->id74);
        TheAudio->event(&sound);
    }
    if (rider && rider->getDrawable()) {
        BfmeAudioEventPrefix136 sound(rider->getDrawable()->rva00462DC7().ref, 0);
        reinterpret_cast<Rva002D9531 *>(&sound)->rva002D9531(reinterpret_cast<Rva00464D02Object *>(rider)->id74);
        TheAudio->event(&sound);
        state1C.erase(rider->getID());
        names28.erase(opaqueKey(rider->getID()));
        reinterpret_cast<Rva001E42F2 *>(rider)->rva001E42F2(Rva000B6253(0,194,195,196,197,198));
        Rva00464D02Data *module = data();
        if (module->bonusBegin != module->bonusEnd && !timesD0.empty()) {
            Rva00464D02Times::iterator it; it = timesD0.find(rider->getID());
            if (it._M_node != *reinterpret_cast<_STL::_Rb_tree_node_base **>(&timesD0)) {
                unsigned entered = static_cast<unsigned>(it->second);
                Rva00464D02EraseView::iterator erased;
                erased._M_node = it._M_node;
                reinterpret_cast<Rva00464D02EraseView *>(&timesD0)->erase(erased);
                if (TheGameLogic->getFrame()-entered > module->minimumFrames)
                    for (AsciiString *bonus=module->bonusBegin; bonus!=module->bonusEnd; ++bonus)
                        rider->addAttributeModifierToPool(*bonus,-1);
            }
        }
    }
}
