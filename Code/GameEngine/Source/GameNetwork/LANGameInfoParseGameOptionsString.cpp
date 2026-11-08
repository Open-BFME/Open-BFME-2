// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /D_CRTIMP= /MD /EHsc /D_STLP_USE_STATIC_LIB
// platformsdk
// stlport
// LANGameInfo.cpp ParseGameOptionsString (Zero Hour GameNetwork/LANGameInfo.cpp, BFME 1 donor
// LANGameInfoParseGameOptionsString.cpp at f989): native 0x00449258..0x004494AC.
// Exact body banked by S2 (sonnet r5); landed by X1.
// The game's free has C++ linkage and may throw, so the tree destructor
// (retail 0x00448FA6) keeps an EH state around it; reach it through that
// spelling (the SidesListCastleBuildLists.cpp idiom).
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseOptionNode(void *storage)
{
	_STL::free(storage);
}
#include "ascii_string.h"
#include <map>
#include <windows.h>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

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

namespace _STL {
template<> inline void allocator<_Rb_tree_node<pair<const UnicodeString, UnicodeString> > >::deallocate(_Rb_tree_node<pair<const UnicodeString, UnicodeString> > *__p, size_type) const
{
	if (__p != 0) releaseOptionNode((void *)__p);
}
}

typedef std::map<UnicodeString, UnicodeString> UnicodeStringMap;

namespace _STL {
typedef _Rb_tree<UnicodeString, pair<const UnicodeString, UnicodeString>,
    _Select1st<pair<const UnicodeString, UnicodeString> >, less<UnicodeString>,
    allocator<pair<const UnicodeString, UnicodeString> > > UnicodeStringTree;

}

// The tree's clear is the rowed 0x00448E3B body.
class Rva00448E3B { public: void rva00448E3B(); };
namespace _STL {
template <> __declspec(dllimport) __forceinline void UnicodeStringTree::clear()
{ ((Rva00448E3B *)this)->rva00448E3B(); }

// Cache the header throughout the lower-bound search and final key check.
template <> template <> inline UnicodeStringTree::_Link_type
UnicodeStringTree::_M_find<UnicodeString>(const UnicodeString &key) const
{
    _Link_type candidate = this->_M_header._M_data;
    _Link_type header = this->_M_header._M_data;
    _Link_type node = (_Link_type)header->_M_parent;
    while (node != 0)
    {
        if (!(node->_M_value_field.first < key))
        {
            candidate = node;
            node = (_Link_type)node->_M_left;
        }
        else
            node = (_Link_type)node->_M_right;
    }
    if (candidate == header || key < candidate->_M_value_field.first)
        candidate = header;
    return candidate;
}

template <> inline UnicodeString &UnicodeStringMap::operator[](const UnicodeString &key)
{
    iterator position = lower_bound(key);
    if (position == end() || key_comp()(key, position->first))
        position = insert(position, value_type(key, UnicodeString()));
    return position->second;
}
}

// The two finds are inside a state that retail never unwinds out of, so they
// carry no EH state store: declaring them throw() is what keeps the store
// count at retail's (state 6/7 for the restores, 3 for the temporaries).
static __forceinline UnicodeStringMap::iterator findNoThrow(
    UnicodeStringMap &values, const UnicodeString &key) throw()
{
    return values.find(key);
}

// LANGameSlot extends the 0x1AC-byte GameSlot with m_lastHeard at +0x1CC;
// the slot's LAN user comes from the rowed GameSlot::rva004479B1.
#include "../../Include/GameNetwork/GameInfo.h"
#include "../../Include/GameNetwork/LANPlayerClass.h"
class Rva00447773 {public: void *getLANSlot(int);};
class Rva00447A5C {public: void rva00447A5C(UnicodeString);};
class Rva00447A93 {public: void rva00447A93(UnicodeString);};
class LANGameSlot:public GameSlot {public:
 unsigned char beforeHeard[0x1cc-0x1ac]; UnsignedInt m_lastHeard;
 void setLastHeard(UnsignedInt now){m_lastHeard=now;}
};
class LANGameInfo:public GameInfo {};

#include "../../Include/GameNetwork/LANAPI.h"

extern LANAPI *TheLAN;
extern Bool ParseAsciiStringToGameInfo(GameInfo *, AsciiString, Bool);
// The serialized packet decoder: the BFME-only body at 0x0068EF70 (1881 B,
// cdecl (game, buffer, length) -> bool). Its real name is unproven, so it is
// called by a descriptive name and pinned at its address; the Zero Hour source
// only has the AsciiString overload.
extern Bool ByteBufferToGameInfo(GameInfo *game, const void *buffer, Int length);
extern void Rva00446A77Enable();
extern void Rva00248E98Enable();

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
        LANGameSlot *slot = (LANGameSlot*)((Rva00447773*)game)->getLANSlot(i);
        if (slot && slot->isHuman())
        {
            oldLogins[slot->m_name] = ((LANPlayer*)slot->rva004479B1())->m_login;
            oldMachines[slot->m_name] = ((LANPlayer*)slot->rva004479B1())->m_host;
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
        // Retail consumes the low status byte of the native int return.
        if (!(unsigned char)TheLAN->AmIHost() && isInGame)
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
            LANGameSlot *slot = (LANGameSlot*)((Rva00447773*)game)->getLANSlot(i);
            if (slot->isHuman())
            {
                slot->setLastHeard(now);
                mapIt = findNoThrow(oldLogins, slot->m_name);
                if (mapIt != oldLogins.end())
                    ((Rva00447A5C*)slot)->rva00447A5C(mapIt->second);
                mapIt = findNoThrow(oldMachines, slot->m_name);
                if (mapIt != oldMachines.end())
                    ((Rva00447A93*)slot)->rva00447A93(mapIt->second);
            }
        }

        return true;
    }

    return false;
}
