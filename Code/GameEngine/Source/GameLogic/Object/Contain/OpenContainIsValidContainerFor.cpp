// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// BFME1 9cbfb551fe20 OpenContainIsValidContainerFor.cpp supplies the clean
// reference semantics. BFME2 adds statuses62/94/93 and filter-forbidden kind9.
// WB01196690 independently names OpenContain::isValidContainerFor; existing
// BFME2 Garrison forwarding callers prove interface20 and three stack slots.
// Native00462977..00462B4A RET12 supplies all target-specific flags and offsets.
// Keep the existing mutable three-argument ABI view; both trailing flags are
// unused in this base implementation. Only consumed ABI prefixes are described;
// no instances or vtables are emitted. Primary module/owner fields4/8 and the
// secondary interface20 are independently proven by the native calls and loads.
// PassengerFilter40 and relationship flags7C..7F follow native data accesses.
// Body slot28 returns the owned template-name string; filter calls and cleanup
// preserve its lifetime. Kind masks use the raw-mask form of matched siblings;
// their boolean use is unchanged. Model condition214 uses a boolean bit test.
#include "ascii_string.h"
class Player;
enum Relationship { ENEMIES,NEUTRAL,ALLIES };
enum ObjectStatusTypes { STATUS_38=38,STATUS_62=62,STATUS_93=93,STATUS_94=94 };
enum KindOfType { RVA_KIND_9=9 };
class ThingTemplate { public:
    char unknown00[0x108]; unsigned kindOf[7];
    __forceinline unsigned kindBit(unsigned bit) const { return kindOf[bit>>5]&(1U<<(bit&31)); }
};
template<int N> class Rva00462977Slots:public Rva00462977Slots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00462977Slots<0> {};
template<> class Rva00462977Slots<1> { public: virtual void gap(char (*)[1]); };
class Rva00462977Body:public Rva00462977Slots<28> { public: virtual AsciiString slot28(); };
class Object { public:
    Player *getControllingPlayer() const;
    bool testStatus(ObjectStatusTypes) const;
    Relationship getRelationship(const Object *) const;
    __forceinline const ThingTemplate *getTemplate() const { return type; }
    __forceinline unsigned kindBit(unsigned bit) const { return getTemplate()->kindBit(bit); }
    __forceinline bool condition214() const { return (reinterpret_cast<const unsigned *>(reinterpret_cast<const char *>(this)+0x124)[0]>>22)&1; }
    char unknown00[4]; const ThingTemplate *type;
    char unknown08[0x254-8]; Rva00462977Body *body;
};
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
extern ThingFactory *TheThingFactory;
class ObjectFilter { public:
    bool isForbidden(KindOfType);
    bool testTemplate(const ThingTemplate *,const Player *,const Player *);
    int index;
};
class Rva2225E0Filter:public ObjectFilter { public: bool accepts(Object *,Player *); };
struct Rva00462977Data {
    char unknown00[0x40]; Rva2225E0Filter passenger;
    char unknown44[0x7C-0x44]; unsigned char own,allies,enemies,neutral;
    inline Rva2225E0Filter &passengerFilter() const { return const_cast<Rva2225E0Filter &>(passenger); }
};
class Rva00462977Primary:public Rva00462977Slots<20> { public:
    virtual bool slot20(Object *);
    Rva00462977Data *module;
    Object *owner;
    char unknown0C[0x20-0x0C];
    Object *object() const { return owner; }
    Rva00462977Data *data() const { return module; }
};
class Rva00462977Interface:public Rva00462977Slots<38> { public: virtual bool isValidContainerFor(Object *,bool,bool); };
class OpenContain:public Rva00462977Primary, public Rva00462977Interface {
public:
    virtual bool isValidContainerFor(Object *,bool,bool);
    char unknown24[0xDE-0x24]; bool enabled;
    __forceinline bool isEnabled() const { return enabled; }
};
bool OpenContain::isValidContainerFor(Object *rider,bool,bool)
{
    Object *owner=object();
    Rva00462977Data *module=data();
    if ((reinterpret_cast<const unsigned char *>(rider)[0x94]&1) || rider->testStatus(STATUS_62) || rider->testStatus(STATUS_94) || !isEnabled()) return false;
    if (rider->kindBit(110) && !owner->kindBit(118) && !owner->kindBit(135)) return false;
    if (rider->kindBit(132) || rider->kindBit(136)) {
        AsciiString name=rider->body->slot28();
        const unsigned char *header=*reinterpret_cast<const unsigned char *const *>(&name);
        if (header && *reinterpret_cast<const unsigned short *>(header+4)!=0) {
            const ThingTemplate *type=TheThingFactory->findTemplate(name);
            if (type && module->passengerFilter().testTemplate(type,rider->getControllingPlayer(),owner->getControllingPlayer())) goto accepted;
        }
        return false;
    }
    if (!module->passengerFilter().accepts(rider,owner->getControllingPlayer())) return false;
accepted:
    if (module->passengerFilter().isForbidden(RVA_KIND_9) && rider->condition214()) return false;
    if (rider->testStatus(STATUS_93)) return true;
    switch (rider->getRelationship(owner)) {
    case ENEMIES: if (module->enemies) return true; break;
    case NEUTRAL: if (module->neutral) return true; break;
    case ALLIES:
        if (rider->getControllingPlayer()==owner->getControllingPlayer() && module->own) return true;
        if (module->allies) return true;
        if (rider->testStatus(STATUS_38) && slot20(rider)) return true;
        break;
    }
    return false;
}

