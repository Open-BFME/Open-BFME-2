// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
// Native 00464830..0046491E, secondary contain receiver +20. Whole reference
// OpenContain.cpp and independently named WB 01193000 establish containment
// purpose; retain the existing address-derived virtual name rather than adding
// a second pin. Native adds signed-key frame recording for bonus processing.
// Owner -18, data -1C, playerMask +58 and timestamp tree +D0 are observed.
// Primary slots18/21/24 and secondary slots40/44 are separately observed;
// the returned 16-byte mask/bit61 agrees with the recovered load/world bodies.
// Bonus vector holds AsciiString as the separately recovered removal consumer
// proves; timestamp payload is a frame word, with no broader mapped-type claim.
// make_pair retains ID/frame value temporaries: direct pair construction loses
// the native one-byte register/scheduling shape. Existing insert_unique owns
// its dependencies; this caller does not emit another tree provider copy.
#include <map>
#include <vector>
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Drawable { public: char unknown00[0x43C]; bool selected43C; };
class Player { public: char unknown00[0x54]; unsigned index54; };
class Object { public: Drawable *getDrawable() const; Player *getControllingPlayer() const; void onContainedBy(Object *); int getID() const { return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this)+0x74); } };
template<int N> class Rva00464830Slots:public Rva00464830Slots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00464830Slots<0> {};
class Rva00464830OnContaining:public Rva00464830Slots<22> { public: virtual void onContaining(Object *,bool); };
struct Rva00464830Object { char unknown00[0x74]; int id74; char unknown78[0x250-0x78]; Rva00464830OnContaining *contain250; char unknown254[0x274-0x254]; Object *containedBy274; };
struct Rva00464830Mask { unsigned words[4]; bool test(int i) const { return (words[i/32]>>(i%32))&1; } };
class Rva00464830Primary:public Rva00464830Slots<18> { public: virtual void redeploy(); virtual void gap19(); virtual void gap20(); virtual void loadSound(); virtual void gap22(); virtual void gap23(); virtual void world(Object *,int,int); };
struct Rva00464830Data { char unknown00[0x88]; _STL::vector<AsciiString> bonuses; };
typedef _STL::pair<const int,int> Rva00464830Pair;
typedef _STL::_Rb_tree<int,Rva00464830Pair,_STL::_Select1st<Rva00464830Pair>,_STL::less<int>,_STL::allocator<Rva00464830Pair> > Rva00464830Tree;
namespace _STL { template<> pair<Rva00464830Tree::iterator,bool> Rva00464830Tree::insert_unique(const Rva00464830Pair &); }
class OpenContain:public Rva00464830Slots<40> {
public:
    virtual void addList(Object *);
    virtual void gap41(); virtual void gap42(); virtual void gap43();
    virtual Rva00464830Mask status(int);
    virtual void rva00464830(Object *);
    char unknown04[0x58-4]; unsigned playerMask58;
    char unknown5C[0xD0-0x5C]; Rva00464830Tree timesD0;
    Object *object() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this)-0x18); }
    Rva00464830Data *data() const { return *reinterpret_cast<Rva00464830Data *const *>(reinterpret_cast<const char *>(this)-0x1C); }
    Rva00464830Primary *primary() { return reinterpret_cast<Rva00464830Primary *>(reinterpret_cast<char *>(this)-0x20); }
};
void OpenContain::rva00464830(Object *rider)
{
    if (!rider) return;
    Drawable *draw = rider->getDrawable();
    bool selected = false;
    if (draw && draw->selected43C) selected = true;
    if (reinterpret_cast<Rva00464830Object *>(rider)->containedBy274) return;
    addList(rider);
    playerMask58 = 1U << rider->getControllingPlayer()->index54;
    Rva00464830OnContaining *contain = reinterpret_cast<Rva00464830Object *>(object())->contain250;
    if (contain) contain->onContaining(rider,selected);
    primary()->redeploy();
    rider->onContainedBy(object());
    primary()->loadSound();
    Rva00464830Data *module = data();
    if (!module->bonuses.empty()) {
        timesD0.insert_unique(_STL::make_pair(rider->getID(),TheGameLogic->getFrame()));
    }
    if (status(0).test(61)) primary()->world(rider,0,0);
}






