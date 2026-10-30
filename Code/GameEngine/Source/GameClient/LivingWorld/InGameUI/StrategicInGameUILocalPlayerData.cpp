// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// WB15E01F0, StrategicInGameUIBattlePromptDialog.cpp assertions 49..62:
// construct the local player's battle-prompt record. Native 005E9A5E..005E9B4A
// supplies the side/player lookups, field offsets, six-word payload and calls.
// The existing address-derived record and factory views retain their names.
//
// Both levels of the factory must be visible: its 50-byte body AND the
// existing 31-byte payload constructor. With the constructor merely declared,
// MSVC reuses the side spill for the returned reference (frame 34 instead of
// 38). These complete helper bodies and the caller's EH graph verify exactly.
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../../Libraries/Include/Lib/RGBColor.h"

struct TargetRef00217D4C {
    virtual void *destroy(unsigned int flags);
    int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct Rva005F918DHolder00 {
    TargetRef00217D4C *m_ptr;
    Rva005F918DHolder00() : m_ptr(0) {}
    ~Rva005F918DHolder00() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
    __declspec(noinline) Rva005F918DHolder00 &operator=(const Rva005F918DHolder00 &other) {
        if (this != &other) {
            if (other.m_ptr) ++other.m_ptr->references;
            if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
            m_ptr = other.m_ptr;
        }
        return *this;
    }
};

struct Rva005F918D {
    Rva005F918DHolder00 m_holder;
    unsigned int m_word4;
    unsigned int m_word8;
    UnicodeString m_text0C;
    __declspec(noinline) Rva005F918D() : m_word4(0), m_word8(0) {}
    Rva005F918D(const Rva005F918D &);
    ~Rva005F918D();
};

// Same one-pointer result as RvaPayloadValueFactories.cpp; conversion exposes
// its established intrusive-reference assignment without inventing a new pin.
template<class T> class RvaCloneResult {
    T *pointer;
public:
    RvaCloneResult(T *p) : pointer(p) { if (p) ++p->m_ref; }
    ~RvaCloneResult() {
        if (pointer) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)pointer);
    }
    operator const Rva005F918DHolder00 &() const {
        return *(const Rva005F918DHolder00 *)this;
    }
};

// Existing constructor view from Rva005CEB57Ctor.cpp: allocation 32, count +4,
// six copied payload words at +8. The original factory class name is unknown.
class __declspec(novtable) Rva005E9742 {
public:
    struct Payload { int v[6]; };
    __declspec(dllimport) __forceinline Rva005E9742(const Payload *) throw();
    virtual ~Rva005E9742();
    int m_ref;
    Payload m_data;
};

__declspec(dllimport) __forceinline Rva005E9742::Rva005E9742(const Payload *src) throw()
    : m_ref(0), m_data(*src) {}

inline __declspec(noinline) RvaCloneResult<Rva005E9742>
Rva005E98FDCreate(const Rva005E9742::Payload *src) {
    return RvaCloneResult<Rva005E9742>(new Rva005E9742(src));
}

class Rva005E957C {
public:
    Rva005E957C *rva005E957C(int, int, int, int, int, int);
    int words[6];
};
class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;
struct FactionView { char prefix[0x20]; AsciiString icon; };
struct LivingWorldPlayer {
    char pad00[0x1C];
    UnicodeString name;
    char pad20[0x20];
    FactionView *faction;
    char pad44[0x184 - 0x44];
    RGBColor color;
};
class LivingWorldLogic {
public:
    char prefix[0x98];
    LivingWorldPlayer *localPlayer;
};
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldBattle {
public:
    int rva003F4752(void *);
    int rva003F4FAA(int, void *);
};

namespace StrategicInGameUI {
Rva005F918D CreateLocalPlayerData(LivingWorldBattle &battle, int first, int second, int third) {
    LivingWorldPlayer *player = TheLivingWorldLogic->localPlayer;
    int side = battle.rva003F4752(player);
    int index = battle.rva003F4FAA(side, player);
    FactionView *faction = player->faction;
    Rva005F918D data;
    data.m_word4 = (unsigned int)TheMappedImageCollection->findImageByName(faction->icon);
    data.m_word8 = (unsigned int)player->color.getAsInt() | 0xFF000000;
    data.m_text0C = player->name;
    Rva005E957C payload;
    payload.rva005E957C((int)&battle, side, index, first, second, third);
    data.m_holder = Rva005E98FDCreate((const Rva005E9742::Payload *)&payload);
    return data;
}
}
