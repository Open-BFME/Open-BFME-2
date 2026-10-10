// ?ParseGameOptionsString@@YA_NPAVLANGameInfo@@VAsciiString@@PBXH@Z
// partial score=0.99 date=2026-10-10
// ?ParseGameOptionsString@@YA_NPAVLANGameInfo@@VAsciiString@@PBXH@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /D_CRTIMP= /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include "ascii_string.h"
#include <map>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum { MAX_SLOTS = 8 };

#include "unicode_string.h"

bool operator<(const UnicodeString&,const UnicodeString&);
namespace _STL
{
template <> struct less<UnicodeString>
{
    bool operator()(const UnicodeString &left, const UnicodeString &right) const
    {
        return left < right;
    }
};
}

typedef std::map<UnicodeString, UnicodeString> UnicodeStringMap;

// The two finds are inside a state that retail never unwinds out of, so they
// carry no EH state store: declaring them throw() is what keeps the store
// count at retail's (state 6/7 for the restores, 3 for the temporaries).
static __forceinline UnicodeStringMap::iterator findNoThrow(
    UnicodeStringMap &values, const UnicodeString &key) throw()
{
    return values.find(key);
}

// The layout view this body needs. Offsets are the ones the surrounding
// LANGameInfo TU and LANGameInfoBodies.cpp already carry: GameSlot is 0x44
// bytes, LANGameSlot adds m_user at +0x44, m_serial at +0x60 and m_lastHeard
// at +0x64, and GameInfo carries the map name at +0x3c with its CRC at +0x44.
// GameInfo's virtuals are placeholders in retail's own order: the body reads
// isInGame's flag byte directly and calls getLocalSlotNum at vtable+0x14.
class GameInfo {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual Int getLocalSlotNum() const;
 Bool isInGame() const { return m_inGame; }
 AsciiString getMap() const;
 UnsignedInt getMapCRC() const { return m_mapCRC; }
private:
 unsigned char before[0x10-4]; Bool m_inGame;
 unsigned char beforeMap[0x40-0x11]; AsciiString m_mapName; UnsignedInt m_mapCRC;
};
class LANPlayer { public: UnicodeString m_name,m_login,m_host; };
class GameSlot {
public:
 Bool isHuman() const;
 void *rva004479B1();
 LANPlayer *getUser(){return (LANPlayer*)rva004479B1();}
 const UnicodeString &getName()const{return m_name;}
private:
 unsigned char pad[0x30]; UnicodeString m_name;
};
class Rva00447773 {public: void *rva00447773(int);};
class Rva00447A5C {public: void rva00447A5C(UnicodeString);};
class Rva00447A93 {public: void rva00447A93(UnicodeString);};
class LANGameSlot:public GameSlot {public:
 unsigned char beforeHeard[0x1cc-0x34]; UnsignedInt m_lastHeard;
 void setLastHeard(UnsignedInt now){m_lastHeard=now;}
};
class LANGameInfo:public GameInfo {public:
 LANGameSlot *getLANSlot(int i){return (LANGameSlot*)((Rva00447773*)this)->rva00447773(i);}
};

// Only the two entries this body calls are named; the rest keep the retail
// order so RequestHasMap stays at +0x3c and AmIHost at +0xb8.
class LANAPI {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void RequestHasMap();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual Bool AmIHost();
};

extern LANAPI *TheLAN;
extern Bool ParseAsciiStringToGameInfo(GameInfo *, AsciiString, Bool);
// The serialized packet decoder: the BFME-only body at 0x0068EF70 (1881 B,
// cdecl (game, buffer, length) -> bool). Its real name is unproven, so it is
// called by a descriptive name and pinned at its address; the Zero Hour source
// only has the AsciiString overload.
extern Bool ByteBufferToGameInfo(GameInfo *game, const void *buffer, Int length);
extern void Rva00446A77Enable();
extern void Rva00248E98Enable();
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

static __forceinline void setSlotLogin(LANGameSlot *slot, UnicodeString value){((Rva00447A5C*)slot)->rva00447A5C(value);}
static __forceinline void setSlotHost(LANGameSlot *slot, UnicodeString value){((Rva00447A93*)slot)->rva00447A93(value);}

Bool ParseGameOptionsString(LANGameInfo *game, AsciiString options,
    const void *buffer, Int length)
{
    if (!TheLAN || !game)
        return false;

    Int oldLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
    if(oldLocalSlotNum>=MAX_SLOTS || oldLocalSlotNum< -1)return false;
    Bool wasInGame = oldLocalSlotNum >= 0;
    AsciiString oldMap = game->getMap();
    UnsignedInt oldMapCRC, newMapCRC;
    oldMapCRC = game->getMapCRC();

    UnicodeStringMap oldLogins, oldMachines;
    UnicodeStringMap::iterator mapIt;
    Int i;
    for (i = 0; i < MAX_SLOTS; ++i)
    {
        LANGameSlot *slot = game->getLANSlot(i);
        if (slot && slot->isHuman())
        {
            oldLogins[slot->getName()] = slot->getUser()->m_login;
            oldMachines[slot->getName()] = slot->getUser()->m_host;
        }
    }

    Bool parsed;
    if (buffer && length)
        parsed = ByteBufferToGameInfo(game, buffer, length);
    else
        parsed = ParseAsciiStringToGameInfo(game, options, true);

    if (parsed)
    {
        Int newLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
        Bool isInGame = newLocalSlotNum >= 0;
        if (!TheLAN->AmIHost() && isInGame)
        {
            newMapCRC = game->getMapCRC();
            if ((oldMapCRC ^ newMapCRC) || (!wasInGame && isInGame))
            {
                TheLAN->RequestHasMap();
                Rva00446A77Enable();
                Rva00248E98Enable();
            }
        }

        UnsignedInt now = timeGetTime();
        for (i = 0; i < MAX_SLOTS; ++i)
        {
            LANGameSlot *slot = game->getLANSlot(i);
            if (slot->isHuman())
            {
                slot->setLastHeard(now);
                mapIt = findNoThrow(oldLogins, slot->getName());
                if (mapIt != oldLogins.end())
                    ((Rva00447A5C*)slot)->rva00447A5C(mapIt->second);
                mapIt = findNoThrow(oldMachines, slot->getName());
                if (mapIt != oldMachines.end())
                    ((Rva00447A93*)slot)->rva00447A93(mapIt->second);
            }
        }

        return true;
    }

    return false;
}
