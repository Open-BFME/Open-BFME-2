// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include
// stlport
// SelectionTranslator::translateGameMessage (0x0043003C, 4054 B) and the file-static
// areAllSelected helper (0x0042FA0D, 86 B), whose private EBX list-reference ABI exists
// only beside this caller.
// Donor: reference/open-bfme-1 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// game/GameEngine/Source/GameClient/MessageStream/SelectionXlat.cpp (Zero Hour shape).
// BFME2 message numbers come from MessageStreamCommandName.cpp; control paths, the
// +6/+7 translator bools and layouts were read off retail and the WorldBuilder twin
// (case 62/72 group handling, deselect/select order). The message coordinate conversion
// and the integer ID-set types remain structural inferences.
// KindOf tests go through Thing::getTemplate()->isKindOf() -> BitFlags::test returning the
// masked word (BuildAssistant.cpp spells isKindOf the same way). The one-level byte-test
// spelling compiles every other byte identically but flips the register choice in case 62's
// double-tap compare (+0xC62..0xC6F): that allocation depends on the inline-chain depth.
// KindOf bit numbers are BFME2 values read off retail (6 shrubbery, 7 structure).
// areAllSelected name/algorithm is inferred from the clean BFME1 donor and ZH
// translateGameMessage use, not a named target symbol. Layout offsets FC/274,
// template flag115.20 and selected43C are independent native accesses.
// The Object header from inputs/reference/.../GameEngine/Include/GameLogic is
// embedded below with getDrawable declaration-only: the existing target pin
// at5508E2 is used rather than the donor's wrong inline +80 field accessor.
// All other donor/header layouts are context only, not target layout claims.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#define Matrix4x4 Matrix4  // BFME renamed it
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
struct WirePoint43003C { int x, y; };
#define ICoord2D DonorICoord2D43003C
#define IRegion2D DonorIRegion2D43003C
#include "Lib/BaseType.h"
#undef IRegion2D
#undef ICoord2D
// class-gate: allow ICoord2D proved codegen view: retail builds the by-value argument of rva0029FEBB(msg->getArgument(0)->pixel) in place with the EH arg-slot save (+0x722, +0x7E5: push ecx; push ecx; mov ecx,esp; ...; mov [ebp+8],esp), which needs a user-declared converting ctor; the canonical POD ICoord2D pushes two dwords there (4034 B, 16 regions).
struct ICoord2D {
 Int x, y;
 ICoord2D() {}
 ICoord2D(const WirePoint43003C &other) : x(other.x), y(other.y) {}
 ICoord2D &operator=(const WirePoint43003C &other) { x = other.x; y = other.y; return *this; }
 Int length() const { return (Int)sqrt((double)(x*x + y*y)); }
};
#include "Lib/IRegion2D.h"
#ifndef _MESSAGE_STREAM_H_
#define _MESSAGE_STREAM_H_
#include "Common/GameCommon.h"
#include "Common/SubsystemInterface.h"
#include "Common/GameMemory.h"
enum { TRANSLATOR_ID_INVALID = -1 };
typedef UnsignedInt TranslatorID;
class Drawable;
class GameMessageList;
class MessageStream;
class CommandList;
class GameMessageArgument;
enum ObjectID;
enum DrawableID;
struct WireRegion43003C { WirePoint43003C lo, hi; };
union GameMessageArgumentType {
 Int integer;
 Real real;
 Bool boolean;
 ObjectID objectID;
 DrawableID drawableID;
 UnsignedInt teamID, squadID;
 Coord3D location;
 WirePoint43003C pixel;
 WireRegion43003C pixelRegion;
 UnsignedInt timestamp;
 WideChar wChar;
};
class GameMessage : public MemoryPoolObject {
 MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(GameMessage, "GameMessage")
public:
 enum Type { MSG_INVALID = 0, MSG_CREATE_SELECTED_GROUP_NO_SOUND = 1002 };
 Type getType() const { return m_type; }
 UnsignedByte getArgumentCount() const { return m_argCount; }
 Int getPlayerIndex() const { return m_playerIndex; }
 void appendIntegerArgument(Int);
 void appendRealArgument(Real);
 void appendBooleanArgument(Bool);
 void appendDrawableIDArgument(DrawableID);
 void appendObjectIDArgument(ObjectID);
 void appendTeamIDArgument(UnsignedInt);
 void appendLocationArgument(const Coord3D &);
 void appendPixelArgument(const ICoord2D &);
 void appendPixelRegionArgument(const IRegion2D &);
 void appendWideCharArgument(const WideChar &);
 void appendTimestampArgument(UnsignedInt);
 const GameMessageArgumentType *getArgument(Int) const;
private:
 GameMessage *m_next, *m_prev;
 GameMessageList *m_list;
 Type m_type;
 Int m_playerIndex;
 UnsignedByte m_argCount;
 GameMessageArgument *m_argList, *m_argTail;
};
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
class GameMessageTranslator {
public:
 virtual GameMessageDisposition translateGameMessage(const GameMessage *) = 0;
 virtual ~GameMessageTranslator() {}
};
extern MessageStream *TheMessageStream;
extern CommandList *TheCommandList;
extern void buildRegion(const ICoord2D *, const ICoord2D *, IRegion2D *);
#endif

#include "PreRTS.h"
#define _STLP_BFME_LOWER_BOUND_EXTERN
#include <hash_map>
#include "Common/Thing.h"
#include "Common/GameType.h"
#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_
enum DrawableStatus { DRAWABLE_STATUS_NONE = 0 };
class Drawable : public Thing {
public:
 Object *getObject() const { return *(Object *const *)((const char *)this + 0xFC); }
 DrawableID getID() const;
 const Coord3D *getPosition() const;
 Bool isSelected() const { return ((const Bool *)this)[0x43C]; }
 Drawable *getNextDrawable() const { return *(Drawable *const *)((const char *)this + 0x104); }
 Bool isSelectable() const;
 Bool isMassSelectable() const;
};
#endif

#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "Common/Thing.h"
#include "Common/Snapshot.h"
#include "Common/ObjectStatusTypes.h"
class Player;
class Object : public Thing, public Snapshot {
public:
 ObjectID getID() const { return *(const ObjectID *)((const char *)this + 0x74); }
 Drawable *getDrawable() const;
 Bool testStatus(ObjectStatusTypes) const;
 Player *getControllingPlayer() const;
 Bool isLocallyControlled() const;
 MAKE_DLINK(Object, TeamMemberList)
};
#endif


// This must go first in EVERY cpp file int the GameEngine
#include "Common/ActionManager.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/MessageStream.h"
// list<Drawable *> nodes come from the freelist pool at VA 0x00DBA5E0 (pop
// 0x002393E2), as in the rowed _List_base ctor 0x00239BB0 (see
// PlaceEventTranslator.cpp); this unit's allocator shims would otherwise emit
// a raw-allocator body for that name.
class FreelistPool
{
public:
	void *pop();
private:
	int m_00;
	void *m_04;
	void *m_head;
	void *(__cdecl *m_alloc)(int, int);
	void (__cdecl *m_free)(void *, int);
	int m_14;
};
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL
{
template <> inline
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
}
#include "Common/MiscAudio.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Squad.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Display.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Keyboard.h"
#include "GameClient/SelectionInfo.h"
#include "GameClient/SelectionXlat.h"
#include "GameClient/TerrainVisual.h"
// The list scans compare iterator nodes inline, but the generic base operator
// emits a competing out-of-line copy under this unit's flags. Keep the same
// node comparison local, as stlport_vector_stringrecord_5de651_fill_insert.cpp does.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
// Suppress this TU's non-retail copy of ?_M_set@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@IAEXPAPAX00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<void *,allocator<void *> >::_M_set(void * *,void * *,void * *); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@IAEXPAPAXABQAXABU__true_type:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<void *,allocator<void *> >::_M_insert_overflow(void * *,void * const &,__true_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ?reserve@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<void *,allocator<void *> >::reserve(unsigned int); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<void *,allocator<void *> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?capacity@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEIXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned int vector<void *,allocator<void *> >::capacity() const; }
// Suppress this TU's non-retail copy of ?end@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEPAPAXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * * vector<void *,allocator<void *> >::end(); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXPAPAXIABQAX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<void *,allocator<void *> >::_M_fill_insert(void * *,unsigned int,void * const &); }
// Suppress this TU's non-retail copy of ??R?$less@I@_STL@@QBE_NABI0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool less<unsigned int>::operator()(unsigned int const &,unsigned int const &) const; }
// Suppress this TU's non-retail copy of ?insert@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXPAPAXIABQAX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<void *,allocator<void *> >::insert(void * *,unsigned int,void * const &); }
// Suppress this TU's non-retail copy of ?get_allocator@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBE?AV?$allocator@PAX@2@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> allocator<void *> vector<void *,allocator<void *> >::get_allocator() const; }
// Suppress this TU's non-retail copy of ?begin@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEPAPAXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * * vector<void *,allocator<void *> >::begin(); }
// Suppress this TU's non-retail copy of ?begin@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEPBQAXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * const * vector<void *,allocator<void *> >::begin() const; }
// Suppress this TU's non-retail copy of ??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEAAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * & vector<void *,allocator<void *> >::operator[](unsigned int); }
// Suppress this TU's non-retail copy of ?size@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEIXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned int vector<void *,allocator<void *> >::size() const; }
// Suppress this TU's non-retail copy of ??0?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV?$allocator@PAX@1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> vector<void *,allocator<void *> >::vector(allocator<void *> const &); }
// Preserve native inline reads without emitting competing library helpers.
namespace _STL {
template <> __declspec(dllimport) __forceinline void *const &
vector<void *>::operator[](size_t n) const { return *(this->_M_start + n); }
// The allocator base is stateless; exchanging bucket storage only swaps pointers.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &a,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &b)
{
 swap(a._M_data, b._M_data);
}
}
namespace _STL

{
 extern template _Vector_base<Object *, allocator<Object *> >::_Vector_base(
 size_t, const allocator<Object *> &);

}
#ifdef _INTERNAL
#endif
#if defined(_DEBUG) || defined(_INTERNAL)
static Bool TheHurtSelectionMode = false;
static Bool TheDebugSelectionMode = false;
#endif
class NativeUI43003C { public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void slot68(Bool);
 virtual void endAreaSelectHint(const ICoord2D *);
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void createMouseoverHint(const GameMessage *);
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void setGUICommand(const CommandButton *);
 virtual Bool isScrolling();
 virtual void setSelecting(Bool);
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual const CommandButton *getGUICommand();
 virtual void s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void s54();
 virtual void s55();
 virtual void s56();
 virtual void s57();
 virtual void s58();
 virtual void s59();
 virtual void s60();
 virtual void s61();
 virtual void s62();
 virtual void s63();
 virtual void s64();
 virtual void s65();
 virtual void selectDrawable(Drawable *);
 virtual void deselectDrawable(Drawable *);
 virtual void deselectAllDrawables();
 virtual void s69();
 virtual Int getSelectCount();
 virtual void s71();
 virtual UnsignedInt slot120();
 virtual const DrawableList *getAllSelectedDrawables();
 virtual void s74();
 virtual void s75();
 virtual void s76();
 virtual void s77();
 virtual void s78();
 virtual void s79();
 virtual void s80();
 virtual void s81();
 virtual void s82();
 virtual void s83();
 virtual void s84();
 virtual void s85();
 virtual void s86();
 virtual void s87();
 virtual void s88();
 virtual void s89();
 virtual void s90();
 virtual void s91();
 virtual void s92();
 virtual void s93();
 virtual void s94();
 virtual Bool isQuitMenuVisible();
 Bool isInForceAttackMode() const { return ((const Bool *)this)[0x8B8]; }
 Bool isInPreferSelectionMode() const { return ((const Bool *)this)[0x8BA]; }

};
class NativeView43003C { public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual Drawable *pickDrawable(const ICoord2D *, Bool, PickType);
 virtual void iterateDrawablesInRegion(const IRegion2D *, Int (*)(Drawable *, void *), void *);
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void lookAt(const Coord3D *);
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void s54();
 virtual void s55();
 virtual void s56();
 virtual void s57();
 virtual void s58();
 virtual void s59();
 virtual void s60();
 virtual void s61();
 virtual void s62();
 virtual void s63();
 virtual void s64();
 virtual void s65();
 virtual void s66();
 virtual void s67();
 virtual void s68();
 virtual void s69();
 virtual void getPosition(Coord3D *);
 virtual void s71();
 virtual void s72();
 virtual void s73();
 virtual void s74();
 virtual void s75();
 virtual void s76();
 virtual void s77();
 virtual void s78();
 virtual void s79();
 virtual void s80();
 virtual void s81();
 virtual void s82();
 virtual void s83();
 virtual void s84();
 virtual void s85();
 virtual void s86();
 virtual void s87();
 virtual void s88();
 virtual void s89();
 virtual void screenToTerrain(const ICoord2D *, Coord3D *, Bool = FALSE);
 virtual void s91();
 virtual void s92();
 virtual void s93();
 virtual void s94();
 virtual void s95();
 virtual void s96();
 virtual void s97();
 virtual void s98();
 virtual void s99();
 virtual void s100();
 virtual void s101();
 virtual void s102();
 virtual void s103();
 virtual void slot1A0();
 virtual void setMouseLock(Bool);
 virtual void s106();
 virtual void s107();
 virtual void s108();
 virtual void s109();
 virtual void s110();
 virtual void s111();
 virtual void s112();
 virtual void s113();
 virtual void s114();
 virtual Bool slot1CC();

};
class Rva0030F0E2 { public:
 Rva0030F0E2();
 DrawableList *drawableListToFill;
 Bool alternate;
 Bool dragSelecting;
 unsigned char padding[2];
 unsigned char mustBe[28];
 unsigned char mustNotBe[28];
 Int bestPriority;
};
class BfmeVecAK;
class Gen_0018BC70 { public: BfmeVecAK *bfmeCompact(Bool); };
class Rva004D6BCD;
class Rva002AA191 { public: Rva004D6BCD *rva002AA176(Int); };
static Object *nativeObject43003C(const Drawable *drawable) { return *(Object *const *)((const char *)drawable + 0xFC); }
static ObjectID nativeID43003C(const Object *object) { return *(const ObjectID *)((const char *)object + 0x74); }
static DrawableID nativeID43003C(const Drawable *drawable) { return *(const DrawableID *)((const char *)drawable + 0x8); }
static Bool nativeSelected43003C(const Drawable *drawable) { return ((const Bool *)drawable)[0x43C]; }
static Drawable *nativeNext43003C(const Drawable *drawable) { return *(Drawable *const *)((const char *)drawable + 0x104); }
static Object *nativeContained43003C(const Object *object) { return *(Object *const *)((const char *)object + 0x274); }
static Team *nativeTeam43003C(const Object *object) { return *(Team *const *)((const char *)object + 0x304); }
static const ThingTemplate *nativeTemplate43003C(const Thing *thing) { return *(const ThingTemplate *const *)((const char *)thing + 4); }
struct KindOfBits43003C {
 unsigned int m_bits[7];
 UnsignedInt test(Int i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
};
class KindOfTemplate43003C { public: UnsignedInt isKindOf(Int k) const { return m_kindof.test(k); } char pad[0x108]; KindOfBits43003C m_kindof; };
class KindOfThing43003C { public: const KindOfTemplate43003C *getTemplate() const { return m_template; } UnsignedInt isKindOf(Int k) const { return getTemplate()->isKindOf(k); } void *vt; const KindOfTemplate43003C *m_template; };
class Rva0029C138 { public:
 void rva0029C138();
 int rva0029FFFF(int (*callback)(Drawable *, void *), void *);
};
Int Rva0030F14CSelect(Drawable *, void *);

class Rva0029FEBB { public: void rva0029FEBB(ICoord2D); };
UnsignedInt Rva0030F099(Bool);

extern Int BfmeLogicFramesPerSecond;
namespace _STL {
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base() throw();
}

class NativeMessageStream43003C { public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual GameMessage *appendMessage(GameMessage::Type);
};
static __forceinline Player *localPlayer43003C() { return *(Player **)((char *)ThePlayerList + 0x10); }

class NativeGameClient43003C { public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual Drawable *findDrawableByID(DrawableID);
 virtual void s17();
 virtual GameMessage::Type evaluateContextCommand(Drawable *, const Coord3D *, CommandTranslator::CommandEvaluateType);
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual Drawable *getDrawableList();
};
class NativeMouse43003C { public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void setCursor(Mouse::MouseCursor);
};

namespace _STL {
typedef pair<const int, Bool> SelectionValue43003C;
// Use the rowed table and map constructors in StlSweepW5Rva0042FFC0.cpp.
template <> hash_map<int, Bool>::hash_map();
template <> hashtable<SelectionValue43003C, int, hash<int>, _Select1st<SelectionValue43003C>, equal_to<int>, allocator<SelectionValue43003C> >::hashtable(unsigned int, const hash<int>&, const equal_to<int>&, const allocator<SelectionValue43003C>&);
template <> void hashtable<SelectionValue43003C, int, hash<int>, _Select1st<SelectionValue43003C>, equal_to<int>, allocator<SelectionValue43003C> >::clear();
template <> __declspec(dllimport) __forceinline unsigned int
hashtable<SelectionValue43003C, int, hash<int>, _Select1st<SelectionValue43003C>, equal_to<int>, allocator<SelectionValue43003C> >::_M_bkt_num_key(const int &key) const
{
 return _M_bkt_num_key(key, _M_buckets.size());
}
template <> __declspec(dllimport) __forceinline unsigned int
hashtable<SelectionValue43003C, int, hash<int>, _Select1st<SelectionValue43003C>, equal_to<int>, allocator<SelectionValue43003C> >::_M_bkt_num(const SelectionValue43003C &value) const
{
 return _M_bkt_num_key(_M_get_key(value));
}
}


static Bool currentlyLookingForSelection( )

{
 return ((NativeUI43003C *)TheInGameUI)->getGUICommand() == NULL;

}
static Bool areAllSelected(const DrawableList& listToCheck)

{
 for (DrawableList::const_iterator it = listToCheck.begin(); it != listToCheck.end(); ++it)
 {
  Drawable *draw = *it;
  if (!draw) continue;
  Object *obj = *reinterpret_cast<Object **>(reinterpret_cast<char *>(draw) + 0xFC);
  if (obj)
  {
   Object *redirect = *reinterpret_cast<Object **>(reinterpret_cast<char *>(obj) + 0x274);
   if (redirect)
   {
    const char *templ = *reinterpret_cast<const char **>(reinterpret_cast<char *>(redirect) + 4);
    if ((static_cast<unsigned char>(templ[0x115]) & 0x20) != 0)
    {
     Drawable *replacement = redirect->getDrawable();
     if (replacement) draw = replacement;

    }

   }

  }
  if (!*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(draw) + 0x43C))
  return false;

 }
 return true;

}
// ?SelectionTranslator::translateGameMessage present-unmatched  // retail 0x0043003C body is a banked partial; retained because it fixes the private EBX call ABI of the 0x0042FA0D helper
class InGameUISlot17C { public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void s54();
 virtual void s55();
 virtual void s56();
 virtual void s57();
 virtual void s58();
 virtual void s59();
 virtual void s60();
 virtual void s61();
 virtual void s62();
 virtual void s63();
 virtual void s64();
 virtual void s65();
 virtual void s66();
 virtual void s67();
 virtual void s68();
 virtual void s69();
 virtual void s70();
 virtual void s71();
 virtual void s72();
 virtual void s73();
 virtual void s74();
 virtual void s75();
 virtual void s76();
 virtual void s77();
 virtual void s78();
 virtual void s79();
 virtual void s80();
 virtual void s81();
 virtual void s82();
 virtual void s83();
 virtual void s84();
 virtual void s85();
 virtual void s86();
 virtual void s87();
 virtual void s88();
 virtual void s89();
 virtual void s90();
 virtual void s91();
 virtual void s92();
 virtual void s93();
 virtual void s94();
 virtual Bool slot95();
};
static void deselectAll()

{
 GameMessage *newMsg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)1004);
 newMsg->appendBooleanArgument(TRUE);
 ((NativeUI43003C *)TheInGameUI)->deselectAllDrawables();

}
static Bool selectSingleDrawableWithoutSound( Drawable *draw )

{
 deselectAll();
 ((NativeUI43003C *)TheInGameUI)->selectDrawable( draw );
 Object *obj = nativeObject43003C(draw);
 if (obj != NULL)
 {
  GameMessage *msg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP_NO_SOUND);
  msg->appendBooleanArgument(TRUE);
  msg->appendObjectIDArgument(nativeID43003C(obj));

 }
 return true;

}
GameMessageDisposition SelectionTranslator::translateGameMessage(const GameMessage *msg)

{
 GameMessageDisposition disp = KEEP_MESSAGE;
 //Keep the message so the other translaters (WindowXlat) can handle.
 if(	!(((const char *)TheInGameUI)[0x15] && ((const char *)TheInGameUI)[0x16] && !((InGameUISlot17C *)TheInGameUI)->slot95()) )

 {
  if( m_dragSelecting )

  {
   //Turn off drag select
   m_dragSelecting = FALSE;
   ((NativeUI43003C *)TheInGameUI)->setSelecting( FALSE );
   ((NativeUI43003C *)TheInGameUI)->endAreaSelectHint(NULL);
   ((NativeView43003C *)TheTacticalView)->setMouseLock( FALSE );

  }
  return KEEP_MESSAGE;

 }
 GameMessage::Type t = msg->getType();
 switch (t)

 {
  case ((GameMessage::Type)3):
  {
   ICoord2D pixel = msg->getArgument(0)->pixel;
   // modifier appears to be unused, and the argument doesn't exist.  jba.
   //Int modifier = msg->getArgument( 1 )->integer;
   if (m_leftMouseButtonIsDown)
   {
    if (*(const Int *)((const char *)TheMouse + 0x4F24) == 0 || *(const Int *)((const char *)TheMouse + 0x4F30) == 1)
    {
     m_leftMouseButtonIsDown = FALSE;
     ((NativeView43003C *)TheTacticalView)->setMouseLock(FALSE);
     ((NativeUI43003C *)TheInGameUI)->setSelecting(FALSE);
     ((NativeUI43003C *)TheInGameUI)->endAreaSelectHint(NULL);
     if (*(const Int *)((const char *)TheMouse + 0x4F30) == 1)
      ((Bool *)this)[7] = TRUE;
    }
   }
   if (m_leftMouseButtonIsDown)
   {
    ICoord2D delta;
    delta.x = abs(pixel.x - m_selectFeedbackAnchor.x);
    delta.y = abs(pixel.y - m_selectFeedbackAnchor.y);
    // if mouse has moved while left button is down, begin drag selection
    if (delta.x > *(const UnsignedInt *)((const char *)TheMouse + 0x12E8) || delta.y > *(const UnsignedInt *)((const char *)TheMouse + 0x12E8))
    {
     if (m_dragSelecting == FALSE)
     {
      m_dragSelecting = TRUE;
      ((Bool *)this)[6] = TRUE;
      ((NativeView43003C *)TheTacticalView)->setMouseLock(TRUE);
      ((NativeUI43003C *)TheInGameUI)->setSelecting(TRUE);
     }
    }
    // create "hint" messages defining selection region under construction
    if (m_dragSelecting)
    {
     if (((Bool *)TheInGameUI)[0x924])
     {
      ((Rva0029FEBB *)TheInGameUI)->rva0029FEBB(pixel);
      ((NativeUI43003C *)TheInGameUI)->slot68(FALSE);
     }
     else
     {
      // insert area selection "hint" message into stream
      GameMessage *hintMsg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)166);
      // build rectangular region defined by the drag selection
      IRegion2D pixelRegion;
      buildRegion(&m_selectFeedbackAnchor, &pixel, &pixelRegion);
      hintMsg->appendPixelRegionArgument(pixelRegion);
     }
    }
   }
   else //left button is not down (not drag select)
   {
    // insert Mouseover hint into stream for CommandTranslator and HintSpy to see.
    GameMessage *mouseoverMessage;
    //Kris: We want to show information such as the popup text on objects that are forceattackable even
    //      when we're not in force attackable mode!
    UnsignedInt pickType = Rva0030F099(TRUE);
    Drawable *underCursor = ((NativeView43003C *)TheTacticalView)->pickDrawable(&pixel, ((NativeUI43003C *)TheInGameUI)->isInForceAttackMode(), (PickType)pickType);
    Object *objUnderCursor = underCursor ? nativeObject43003C(underCursor) : NULL;
    Object *selectedObject = NULL;
    if (((NativeUI43003C *)TheInGameUI)->getSelectCount() == 1)
    {
     Drawable *selected = *((NativeUI43003C *)TheInGameUI)->getAllSelectedDrawables()->begin();
     selectedObject = selected ? nativeObject43003C(selected) : NULL;
    }
    if (objUnderCursor)
    {
     if (selectedObject && ((const KindOfThing43003C *)(selectedObject))->isKindOf(134))
      objUnderCursor = NULL;
    }
    if (objUnderCursor && (!(((const unsigned char *)objUnderCursor)[0x438] & 1) || ((const unsigned char *)nativeTemplate43003C(objUnderCursor))[0x632] || ((const KindOfThing43003C *)(objUnderCursor))->isKindOf(58)))
    {
     mouseoverMessage = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)162);
     mouseoverMessage->appendDrawableIDArgument(underCursor->getID());
    }
    else// else this is a mouseover terrain
    {
     Coord3D position;
     ((NativeView43003C *)TheTacticalView)->screenToTerrain(&pixel, &position);
     mouseoverMessage = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)163);
     mouseoverMessage->appendLocationArgument(position);
    }
   }
   break;
  }
  case ((GameMessage::Type)24):
   ((Bool *)this)[7] = FALSE;
   break;
/// note we are putting in a drawable id
  case ((GameMessage::Type)162):
  {
   if (((NativeUI43003C *)TheInGameUI)->isScrolling())
   {
    // dont show this now.
    break;
   }
   DrawableID id = msg->getArgument(0)->drawableID;
   Drawable *draw = ((NativeGameClient43003C *)TheGameClient)->findDrawableByID(id);
   if (!draw)
    break;
   GameMessage::Type msgType = ((NativeGameClient43003C *)TheGameClient)->evaluateContextCommand(draw, draw->getPosition(), CommandTranslator::EVALUATE_ONLY);
   if (msgType != (GameMessage::Type)0 && msgType != (GameMessage::Type)1071)
    break;
   ((NativeUI43003C *)TheInGameUI)->createMouseoverHint(msg); // this sets the cursor
   const CommandButton *command = ((NativeUI43003C *)TheInGameUI)->getGUICommand();
   if (command)
   {
    Int type = *(const Int *)((const char *)command + 0x14);
    if (type == 10 || type == 11 || type == 12 || type == 13)
    {
     //These GUI commands can take care of themselves -- don't let
     //the selection translator meddle.
     break;
    }
   }
   if (((const KindOfThing43003C *)(draw))->isKindOf(6))
    break;
   Object *obj = nativeObject43003C(draw);
   if (msgType == (GameMessage::Type)1071 && obj && ((const KindOfThing43003C *)(obj))->isKindOf(60) && !((const KindOfThing43003C *)(obj))->isKindOf(150))
   {
    ((NativeMouse43003C *)TheMouse)->setCursor((Mouse::MouseCursor)5);
    disp = DESTROY_MESSAGE;
   }
   else if (CanSelectDrawable(draw, FALSE))
   {
    ((NativeMouse43003C *)TheMouse)->setCursor((Mouse::MouseCursor)13);
    disp = DESTROY_MESSAGE;
   }
   else if (msgType == (GameMessage::Type)0)
   {
    ((NativeMouse43003C *)TheMouse)->setCursor((Mouse::MouseCursor)2);
    disp = DESTROY_MESSAGE;
   }
   break;
  }
  case ((GameMessage::Type)23):
  {
   Bool wasDragSelecting = ((Bool *)this)[6];
   ((Bool *)this)[6] = FALSE;
   if (((Bool *)this)[7])
   {
    ((Bool *)this)[7] = FALSE;
    break;
   }
   // If the quit menu is visible, we need to not process left clicks through the selection translator.
   if (((NativeUI43003C *)TheInGameUI)->isQuitMenuVisible())
   {
    disp = DESTROY_MESSAGE;
    break;
   }
   if (TheTacticalView && ((NativeView43003C *)TheTacticalView)->slot1CC())
   {
    disp = DESTROY_MESSAGE;
    break;
   }
   // Basically, we need to first determine if there are any drawables in the region of interest.
   // If there aren't then this click should move forward.
   IRegion2D selectionRegion = (*(const IRegion2D *)&msg->getArgument(0)->pixelRegion);
   Bool isPoint = selectionRegion.height() == 0 && selectionRegion.width() == 0;
   DrawableList drawablesThatWillSelect;
   Rva0030F0E2 pds;
   pds.drawableListToFill = &drawablesThatWillSelect;
   pds.dragSelecting = wasDragSelecting;
   if (((Bool *)TheInGameUI)[0x924] || !isPoint)
   {
    pds.mustNotBe[13] |= 1;
    pds.mustNotBe[9] |= 0x10;
   }
   if (((Bool *)TheInGameUI)[0x924])
   {
    ((Rva0029C138 *)TheInGameUI)->rva0029FFFF(Rva0030F14CSelect, &pds);
    ((Rva0029C138 *)TheInGameUI)->rva0029C138();
    ((Bool *)TheInGameUI)[0x924] = FALSE;
    ((Bool *)TheInGameUI)[0x8B8] = FALSE;
   }
   else
   {
    ((NativeView43003C *)TheTacticalView)->iterateDrawablesInRegion(&selectionRegion, Rva0030F14CSelect, &pds);
   }
   if (drawablesThatWillSelect.empty())
   {
    const CommandButton *command = ((NativeUI43003C *)TheInGameUI)->getGUICommand();
    Int type = command ? *(const Int *)((const char *)command + 0x14) : 0;
    Bool ignoreCommand = command && (type == 24 || type == 38 || type == 32 || type == 23 || type == 26 || type == 29 || type == 30);
    if (((const Bool *)TheGlobalData)[0x5C] && !ignoreCommand)
     deselectAll();
    break;
   }
   // if there were drawables in the region, then we should determine if there is a context
   // sensitive command that should take place. If there is, then this isn't a selection thing
   const DrawableList *currentList = ((NativeUI43003C *)TheInGameUI)->getAllSelectedDrawables();
   if (!currentlyLookingForSelection())
    break;
   SelectionInfo si;
   if (contextCommandForNewSelection(currentList, &drawablesThatWillSelect, &si, isPoint))
    break;
   // There isn't a context command, so this is a selection thing. Now, based on the keys,
   // determine whether or not we should create a new group, or append these guys to our existing
   // group.
   Bool addToGroup = ((NativeUI43003C *)TheInGameUI)->isInPreferSelectionMode();
   if (si.currentCountEnemies > 0 || si.currentCountCivilians > 0 || si.currentCountFriends > 0 || si.currentCountMineBuildings > 0)
   {
    // force a new group creation
    addToGroup = FALSE;
   }
   // If there are any of my units, then select those.
   if (si.newCountMine > 0)
   {
    si.selectMine = TRUE;
    // EXACTLY ONE CLICKED OR DRAGGED BUILDING
    if (si.newCountMine == 1 && si.newCountMineBuildings == 1)
    {
     addToGroup = FALSE;
     si.selectMineBuildings = TRUE;
    }
   }
   else if (si.newCountEnemies > 0 && si.newCountCivilians > 0 && si.newCountFriends > 0)
   {
    // No go here
    break;
   }
   else if (si.newCountEnemies == 1)
   {
    addToGroup = FALSE;
    si.selectEnemies = TRUE;
   }
   else if (si.newCountCivilians == 1)
   {
    addToGroup = FALSE;
    si.selectCivilians = TRUE;
   }
   else if (si.newCountFriends == 1)
   {
    addToGroup = FALSE;
    si.selectFriends = TRUE;
   }
   // If we're not going to select anything, just bail now.
   if (!(si.selectMine || si.selectEnemies || si.selectCivilians || si.selectFriends))
    break;
   // If we've made it here, its time to do some selecting.
   disp = DESTROY_MESSAGE;
   // Whenever we manually select something, reset the last selected group.
   m_lastGroupSelGroup = -1;
   if (((NativeUI43003C *)TheInGameUI)->isInPreferSelectionMode() && isPoint && areAllSelected(drawablesThatWillSelect))
   {
    // If this was a point, shift was pressed and we already have that unit selected, then we
    // need to deselect those units.
    GameMessage *newMsg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)1005);
    Drawable *draw = NULL;
    DrawableListIt it;
    for (it = drawablesThatWillSelect.begin(); it != drawablesThatWillSelect.end(); ++it)
    {
     draw = *it;
     if (!draw)
      continue;
     Object *objToDeselect = nativeObject43003C(draw);
     if (!objToDeselect)
      continue;
     newMsg->appendObjectIDArgument(nativeID43003C(objToDeselect));
     ((NativeUI43003C *)TheInGameUI)->deselectDrawable(draw);
    }
   }
   else
   {
    if (!addToGroup)
     ((NativeUI43003C *)TheInGameUI)->deselectAllDrawables();
    GameMessage *newMsg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)1001);
    newMsg->appendBooleanArgument(!addToGroup);
    Player *localPlayer = localPlayer43003C();
    _STL::hash_map<int, Bool> selectedIDs;
    DrawableListIt it;
    for (it = drawablesThatWillSelect.begin(); it != drawablesThatWillSelect.end(); ++it)
    {
     Drawable *draw = *it;
     if (!draw)
      continue;
     Object *obj = nativeObject43003C(draw);
     if (!obj)
      continue;
     ObjectID containerID = *(const ObjectID *)((const char *)obj + 0x78);
     if (containerID != INVALID_ID)
     {
      Object *container = TheGameLogic->findObjectByID(containerID);
      if (container && ((const KindOfThing43003C *)(container))->isKindOf(109))
      {
       if (container->testStatus((ObjectStatusTypes)3))
        continue;
       obj = container;
       draw = container->getDrawable();
      }
     }
     if (nativeContained43003C(obj) && !((const KindOfThing43003C *)(obj))->isKindOf(55))
     {
      obj = nativeContained43003C(obj);
      draw = obj->getDrawable();
     }
     if (si.selectMine && obj->isLocallyControlled())
     {
      if (((const KindOfThing43003C *)(obj))->isKindOf(7) && !si.selectMineBuildings)
       continue;
     }
     else
     {
      Relationship rel = localPlayer->getRelationship(nativeTeam43003C(obj));
      if (!(si.selectEnemies && rel == ENEMIES) && !(si.selectCivilians && rel == NEUTRAL) && !(si.selectFriends && rel == ALLIES))
       continue;
     }
     ObjectID id = nativeID43003C(obj);
     if (draw && id != INVALID_ID && selectedIDs.find((int)id) == selectedIDs.end())
     {
      newMsg->appendObjectIDArgument(id);
      ((NativeUI43003C *)TheInGameUI)->selectDrawable(draw);
      selectedIDs[(int)id] = TRUE;
     }
    }
   }
   break;
  }
  case ((GameMessage::Type)4):
  {
   if (*(const Int *)((const char *)TheMouse + 0x4F30) == 1)
   {
    ((Bool *)this)[7] = TRUE;
    break;
   }
   // cannot actually start area selection yet - have to wait for cursor to move a bit
   m_leftMouseButtonIsDown = TRUE;
   ((Rva0029C138 *)TheInGameUI)->rva0029C138();
   if (TheKeyboard->isCtrl())
   {
    ((Bool *)TheInGameUI)[0x924] = TRUE;
    ((Rva0029FEBB *)TheInGameUI)->rva0029FEBB(msg->getArgument(0)->pixel);
   }
   else
   {
    ((Bool *)TheInGameUI)[0x924] = FALSE;
    m_selectFeedbackAnchor = msg->getArgument(0)->pixel;
   }
   break;
  }
  case ((GameMessage::Type)6):
  {
   m_leftMouseButtonIsDown = FALSE;
   if (m_dragSelecting)
   {
    // Stop drag selecting now, thanks.
    m_dragSelecting = FALSE;
    if (((Bool *)TheInGameUI)[0x924])
    {
     ((NativeView43003C *)TheTacticalView)->setMouseLock(FALSE);
     ((NativeUI43003C *)TheInGameUI)->setSelecting(FALSE);
     ((Rva0029FEBB *)TheInGameUI)->rva0029FEBB(msg->getArgument(0)->pixel);
     ((NativeUI43003C *)TheInGameUI)->endAreaSelectHint(NULL);
    }
    else
    {
     ((NativeView43003C *)TheTacticalView)->setMouseLock(FALSE);
     ((NativeUI43003C *)TheInGameUI)->setSelecting(FALSE);
     ((NativeUI43003C *)TheInGameUI)->endAreaSelectHint(NULL);
     // insert area selection message into stream
     GameMessage *dragMsg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)1060);
     IRegion2D selectionRegion;
     buildRegion(&m_selectFeedbackAnchor, (const ICoord2D *)&msg->getArgument(0)->pixel, &selectionRegion);
     dragMsg->appendPixelRegionArgument(selectionRegion);
    }
   }
   break;
  }
  case ((GameMessage::Type)14):
  {
   // There are three ways in which we can ignore this as a deselect:
   // 1) 2-D position on screen
   // 2) Time has exceeded the time which we allow for this to be a click.
   // 3) 3-D camera position has changed
   m_deselectFeedbackAnchor = msg->getArgument(0)->pixel;
   m_lastClick = (UnsignedInt)msg->getArgument(2)->integer;
   ((NativeView43003C *)TheTacticalView)->getPosition(&m_deselectDownCameraPosition);
   if (m_leftMouseButtonIsDown)
   {
    m_leftMouseButtonIsDown = FALSE;
    ((NativeView43003C *)TheTacticalView)->setMouseLock(FALSE);
    ((NativeUI43003C *)TheInGameUI)->setSelecting(FALSE);
    ((NativeUI43003C *)TheInGameUI)->endAreaSelectHint(NULL);
    ((Bool *)this)[7] = TRUE;
   }
   break;
  }
  case ((GameMessage::Type)16):
  {
   ICoord2D delta, pixel;
   UnsignedInt currentTime;
   Coord3D cameraPos;
   ((NativeView43003C *)TheTacticalView)->getPosition(&cameraPos);
   cameraPos.sub(&m_deselectDownCameraPosition);
   pixel = msg->getArgument(0)->pixel;
   currentTime = (UnsignedInt)msg->getArgument(2)->integer;
   delta.x = m_deselectFeedbackAnchor.x - pixel.x;
   delta.y = m_deselectFeedbackAnchor.y - pixel.y;
   if (abs(delta.x) > *(const UnsignedInt *)((const char *)TheMouse + 0x12E8) || abs(delta.y) > *(const UnsignedInt *)((const char *)TheMouse + 0x12E8))
    break;
   if (currentTime - m_lastClick > 2 * *(const UnsignedInt *)((const char *)TheMouse + 0x12F0))
   {
    ((NativeView43003C *)TheTacticalView)->slot1A0();
    break;
   }
   if (cameraPos.length() > *(const UnsignedInt *)((const char *)TheMouse + 0x12EC))
    break;
   // right click behavior (not right drag)
   const CommandButton *command = ((NativeUI43003C *)TheInGameUI)->getGUICommand();
   const GlobalData *globalData = TheGlobalData;
   if (command && *(const Int *)((const char *)command + 0x14) != 10)
   {
    //Added support to cancel the GUI command without deselecting the unit(s) involved
    //when you right click.
    if (!((const Bool *)globalData)[0x5C])
    {
     //Cancel GUI command mode... don't deselect units.
     //With a GUI command cancel, we want no other behavior.
     disp = DESTROY_MESSAGE;
     ((NativeUI43003C *)TheInGameUI)->setGUICommand(NULL);
    }
   }
   else
   {
    //No GUI command mode, so deselect everyone if we're in regular mouse mode.
    if (!((const Bool *)globalData)[0x5C])
     deselectAll();
   }
   break;
  }
  case ((GameMessage::Type)52):
  case ((GameMessage::Type)53):
  case ((GameMessage::Type)54):
  case ((GameMessage::Type)55):
  case ((GameMessage::Type)56):
  case ((GameMessage::Type)57):
  case ((GameMessage::Type)58):
  case ((GameMessage::Type)59):
  case ((GameMessage::Type)60):
  case ((GameMessage::Type)61):

  {
   Int group = t - ((GameMessage::Type)52);
   if ( group >= 0 && group < 10 )

   {
    DEBUG_LOG(("META: create team %d\n",group));
    // Assign selected items to a group
    GameMessage *newmsg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)(((GameMessage::Type)1006) + group));
    Drawable *drawable = ((NativeGameClient43003C *)TheGameClient)->getDrawableList();
    while (drawable != NULL)

    {
     if (nativeSelected43003C(drawable) && nativeObject43003C(drawable) && nativeObject43003C(drawable)->isLocallyControlled())

     {
      newmsg->appendObjectIDArgument(nativeObject43003C(drawable)->getID());

     }
     drawable = nativeNext43003C(drawable);

    }

   }
   disp = DESTROY_MESSAGE;
   break;

  }
  case ((GameMessage::Type)62):
  case ((GameMessage::Type)63):
  case ((GameMessage::Type)64):
  case ((GameMessage::Type)65):
  case ((GameMessage::Type)66):
  case ((GameMessage::Type)67):
  case ((GameMessage::Type)68):
  case ((GameMessage::Type)69):
  case ((GameMessage::Type)70):
  case ((GameMessage::Type)71):

  {
   Int group = t - ((GameMessage::Type)62);
   if ( group >= 0 && group < 10 )

   {
    DEBUG_LOG(("META: select team %d\n",group));
    UnsignedInt now = (*(const UnsignedInt *)((const char *)TheGameLogic + 0x40));
    if ( m_lastGroupSelTime == 0 )

    {
     m_lastGroupSelTime = now;

    }
    if (m_lastGroupSelGroup >= 0)
    {
     if (((NativeUI43003C *)TheInGameUI)->slot120() > m_lastGroupSelTime)
     {
      m_lastGroupSelGroup = -1;
     }
     else
     {
      Player *player = localPlayer43003C();
      if (player)
      {
       Squad *squad = (Squad *)((Rva002AA191 *)player)->rva002AA176(m_lastGroupSelGroup);
       if (squad)
       {
        const VecObjectPtr &objects = *(const VecObjectPtr *)((Gen_0018BC70 *)squad)->bfmeCompact(FALSE);
        Int count = objects.size();
        for (Int i = 0; i < count; ++i)
        {
         Drawable *draw = objects[i]->getDrawable();
         if (draw && !nativeSelected43003C(draw))
         {
          m_lastGroupSelGroup = -1;
          break;
         }
        }
       }
       else
       {
        m_lastGroupSelGroup = -1;
       }
      }
      else
      {
       m_lastGroupSelGroup = -1;
      }
     }
    }
    // check for double-press to jump view
    if ( now - m_lastGroupSelTime < (UnsignedInt)BfmeLogicFramesPerSecond && group == m_lastGroupSelGroup )

    {
     DEBUG_LOG(("META: DOUBLETAP select team %d\n",group));
     Player *player = localPlayer43003C();
     if (player)

     {
      Squad *selectedSquad = (Squad *)((Rva002AA191 *)player)->rva002AA176(group);
      if (selectedSquad != NULL)

      {
       const VecObjectPtr &objlist = *(const VecObjectPtr *)((Gen_0018BC70 *)selectedSquad)->bfmeCompact(FALSE);
       Int numObjs = objlist.size();
       if (numObjs > 0)

       {
        // if theres someone in the group, center the camera on them.
        ((NativeView43003C *)TheTacticalView)->lookAt( objlist[numObjs-1]->getDrawable()->getPosition() );

       }

      }

     }

    }
    else

    {
     GameMessage *deselectMsg = ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)1004);
     deselectMsg->appendBooleanArgument(TRUE);
     ((NativeUI43003C *)TheInGameUI)->deselectAllDrawables();
//No need to post message because we're just creating a new group!
     ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)(((GameMessage::Type)1016) + group));
     Player *player = localPlayer43003C();
     if (player)

     {
      Squad *selectedSquad = (Squad *)((Rva002AA191 *)player)->rva002AA176(group);
      if (selectedSquad != NULL)

      {
       const VecObjectPtr &objlist = *(const VecObjectPtr *)((Gen_0018BC70 *)selectedSquad)->bfmeCompact(FALSE);
       Int numObjs = objlist.size();
       for (Int i = 0; i < numObjs; ++i)

       {
        if( objlist[i]->getControllingPlayer() == player )

        {
         ((NativeUI43003C *)TheInGameUI)->selectDrawable(objlist[i]->getDrawable());

        }

       }

      }

     }

    }
    m_lastGroupSelTime = now;
    m_lastGroupSelGroup = group;

   }
   disp = DESTROY_MESSAGE;
   break;

  }
  case ((GameMessage::Type)72):
  case ((GameMessage::Type)73):
  case ((GameMessage::Type)74):
  case ((GameMessage::Type)75):
  case ((GameMessage::Type)76):
  case ((GameMessage::Type)77):
  case ((GameMessage::Type)78):
  case ((GameMessage::Type)79):
  case ((GameMessage::Type)80):
  case ((GameMessage::Type)81):

  {
   Int group = t - ((GameMessage::Type)72);
   if ( group >= 0 && group < 10 )

   {
    DEBUG_LOG(("META: select team %d\n",group));
    UnsignedInt now = (*(const UnsignedInt *)((const char *)TheGameLogic + 0x40));
    if ( m_lastGroupSelTime == 0 )

    {
     m_lastGroupSelTime = now;

    }
    // check for double-press to jump view
    if ( now - m_lastGroupSelTime < (UnsignedInt)BfmeLogicFramesPerSecond && group == m_lastGroupSelGroup )

    {
     DEBUG_LOG(("META: DOUBLETAP select team %d\n",group));
     Player *player = localPlayer43003C();
     if (player)

     {
      Squad *selectedSquad = (Squad *)((Rva002AA191 *)player)->rva002AA176(group);
      if (selectedSquad != NULL)

      {
       const VecObjectPtr &objlist = *(const VecObjectPtr *)((Gen_0018BC70 *)selectedSquad)->bfmeCompact(FALSE);
       Int numObjs = objlist.size();
       if (numObjs > 0)

       {
        // if theres someone in the group, center the camera on them.
        ((NativeView43003C *)TheTacticalView)->lookAt( objlist[numObjs-1]->getDrawable()->getPosition() );

       }

      }

     }

    }
    else

    {
     // no need to send two messages for selecting the same group.
     ((NativeMessageStream43003C *)TheMessageStream)->appendMessage((GameMessage::Type)(((GameMessage::Type)1026) + group));
     Player *player = localPlayer43003C();
     if (player)

     {
      Squad *selectedSquad = (Squad *)((Rva002AA191 *)player)->rva002AA176(group);
      if (selectedSquad != NULL)

      {
       const VecObjectPtr &objlist = *(const VecObjectPtr *)((Gen_0018BC70 *)selectedSquad)->bfmeCompact(FALSE);
       Int numObjs = objlist.size();
       for (Int i = 0; i < numObjs; ++i)

       {
        ((NativeUI43003C *)TheInGameUI)->selectDrawable(objlist[i]->getDrawable());

       }

      }

     }

    }
    m_lastGroupSelTime = now;
    m_lastGroupSelGroup = group;

   }
   disp = DESTROY_MESSAGE;
   break;

  }
  case ((GameMessage::Type)82):
  case ((GameMessage::Type)83):
  case ((GameMessage::Type)84):
  case ((GameMessage::Type)85):
  case ((GameMessage::Type)86):
  case ((GameMessage::Type)87):
  case ((GameMessage::Type)88):
  case ((GameMessage::Type)89):
  case ((GameMessage::Type)90):
  case ((GameMessage::Type)91):

  {
   Int group = t - ((GameMessage::Type)82);
   if ( group >= 1 && group <= 10 )

   {
    DEBUG_LOG(("META: view team %d\n",group));
    Player *player = localPlayer43003C();
    if (player)

    {
     Squad *selectedSquad = (Squad *)((Rva002AA191 *)player)->rva002AA176(group);
     if (selectedSquad != NULL)

     {
      const VecObjectPtr &objlist = *(const VecObjectPtr *)((Gen_0018BC70 *)selectedSquad)->bfmeCompact(FALSE);
      Int numObjs = objlist.size();
      if (numObjs > 0)

      {
       ((NativeView43003C *)TheTacticalView)->lookAt( objlist[ numObjs-1 ]->getDrawable()->getPosition() );

      }

     }

    }

   }
   disp = DESTROY_MESSAGE;
   break;

  }
  case ((GameMessage::Type)112):

  {
   // stop drawing selection feedback, as we're going to ignore the selection.
   m_leftMouseButtonIsDown = FALSE;
   // let this message drop through, the commandXLat will show the options screen itself.
   break;

  }
#if defined(_DEBUG) || defined(_INTERNAL)
  case GameMessage::MSG_META_DEMO_TOGGLE_HAND_OF_GOD_MODE:

  {
   if ( !TheGameLogic->isInMultiplayerGame() )

   {
    m_HandOfGodSelectionMode = !m_HandOfGodSelectionMode;
    ((NativeUI43003C *)TheInGameUI)->message( UnicodeString( L"Meta Hand-Of-God Mode is %s" ), m_HandOfGodSelectionMode ? L"ON" : L"OFF" );
    disp = DESTROY_MESSAGE;

   }
   break;

  }
#endif
#if defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)
  case GameMessage::MSG_CHEAT_TOGGLE_HAND_OF_GOD_MODE://NOTICE THE DIFFERENT NAME!!!!!!!!!!!!!!!!!!!!!!!!!!ML

  {
   if ( !TheGameLogic->isInMultiplayerGame() )

   {
    m_HandOfGodSelectionMode = !m_HandOfGodSelectionMode;
    ((NativeUI43003C *)TheInGameUI)->message( UnicodeString( L"Hand-Of-God Mode is %s" ), m_HandOfGodSelectionMode ? L"ON" : L"OFF" );
    disp = DESTROY_MESSAGE;

   }
   break;

  }
#endif
#if defined(_DEBUG) || defined(_INTERNAL)
  case GameMessage::MSG_META_DEMO_TOGGLE_HURT_ME_MODE:

  {
   if ( !TheGameLogic->isInMultiplayerGame() )

   {
    TheHurtSelectionMode = !TheHurtSelectionMode;
    ((NativeUI43003C *)TheInGameUI)->message( UnicodeString( L"Hurt-Me Mode is %s" ), TheHurtSelectionMode ? L"ON" : L"OFF" );
    disp = DESTROY_MESSAGE;

   }
   break;

  }
#endif
#if defined(_DEBUG) || defined(_INTERNAL)
  case GameMessage::MSG_META_DEMO_DEBUG_SELECTION:

  {
   TheDebugSelectionMode = !TheDebugSelectionMode;
   ((NativeUI43003C *)TheInGameUI)->message( UnicodeString( L"Debug-Selected-Item Mode is %s" ), TheDebugSelectionMode ? L"ON" : L"OFF" );
		#ifdef DEBUG_OBJECT_ID_EXISTS
   TheObjectIDToDebug = INVALID_ID;
		#endif
   disp = DESTROY_MESSAGE;
   break;

  }
#endif

 }
 return disp;

}

// Earlier bank comments on superseded donor-only branches:
// What we are after here is to allow the drag select to get the building,
// make sure there is really only the one building in the list, as it may be multiply listed

// Earlier bank comments on superseded mouse branches:


// Earlier bank comments on superseded cursor branches:
// this sets the cursor

// Original bank comments on superseded declarations or branches:
///< The trigger area that the object is inside.
///< True if the object entered this trigger area this frame.
///< True if the object entered this trigger area this frame.
///< True if the object is inside this trigger area this frame.
///< unused.
///< run during TheGameLogic::destroyObject
///< Brings in properties set in the editor.
///< this object's unique ID
///< this object's unique ID
///< set drawable association. for use ONLY by GameLogic!
///< drawable (if any) bound to obj
///< become a member of the AIGroup
///< leave our current AIGroup
///< returns true if object is currently able to move
///< returns true if object currently has some kind of attack capability
///< mask/unmask object
///< Returns TRUE if object has been destroyed
///< Our locomotor will control marking us as a valid target for anti air weapons or not
///< returns true if the current locomotor is an airborne one
///< damage object as specified by the info
///< heal object as specified by the info
///< for the non-stacking healers like ambulance and propaganda
///< kill the object with an optional type of damage and death.
///< Restore max health to this Object
///< At this level, we just pass this on to our helper and do a special tint
///< At this level, we just pass this on to our helper
///< At this level, we just pass this on to our helper
///< I just killed this object.
///< I just achieved this level right this moment
///< sets the unit's team AND original team
///< sets the unit's team BUT NOT its original team
///< We need to go through our Upgrade Modules and see which should be activated
///< Upgrades I complete locally
///< does this object already have this upgrade
///< can the object even "have" this upgrade, will it do something?
///< give upgrade to this object
///< remove upgrade from this object
///< calc the "natural" starting rally point
///< We have moved a 'significant' amount, so do maintenence that can be considered 'cell-based'
///< Undo and redo all shroud actions.  Call when something has changed, like position or ownership or Death
///< How far can you see?  This is dynamic so it is in Object.
///< Access to setting someone's Vision distance
///< How far can you shroud?  Even more dynamic since it'll start at zero for everyone.
///< Access to setting someone's shrouding distance
///< How far do you clear shroud?
///< Access to setting someone's clear shroud distance
///< Change who is looking through our eyes
///< execute power
///< execute power
///< execute power
///< execute power
//Kris: a should be used for real weapons that directly inflict damage... not deploy, hack, etc.
///< Check to see if I should change my model condition.
///< Get the frame a shot was last fired on
///< Get the last victim we shot at
///< get exit interface is present
///< for special amorphous like angry mob
//< this is an object specific frame at which it's safe to enable building occlusion.
// Calculates the actual height above terrain.  Doesn't use cache.
///< object that produced us, if any
///< object that is building or has built us (dozers or workers are builders)
///< drawable (if any) for this object
///< internal name
///< status bits (see ObjectStatusMaskType)
///< if non-NULL, we are part of this group of agents
///< Where and for whom I last looked, so I can undo its effects when I stop
///< And a seperate look to reveal at a different range if so marked
///< Reference count of having units spied on by players.
///< For quick lookup and edge triggered maintenance
///< Where and for whom I last shrouded, so I can undo its effects when I stop
///< Where and for whom I last delt with threat, so I can undo its effects when I stop
///< Where and for whom I last delt with value, so I can undo its effects when I stop
///< looking range
///< looking range for shroud ONLY
///< like looking range, this is how far I shroud others' looks
///< Tracker is really a "helper" and is included NUM_SLEEP_HELPERS
// BehaviorModule, not BehaviorModuleInterface
///< ai interface (if any), cached for handy access. (duplicate of entry in the module array!)
///< physics interface (if any), cached for handy access. (duplicate of entry in the module array!)
///< our PartitionData
///< radar data
///< Manages experience, gaining levels, and value when killed
///< xfer uses IDs to store pointers and looks them up after
///< frame we were contained by m_containedBy
///< for objects being built ... this is the amount completed (0.0 to 100.0)
///< Bit field of upgrades locally completed.
///< team that is current owner of this guy
///< team that was the original ("birth") team of this guy
///< if nonzero, use this instead of controlling player's color
///< generally zero, except for special amorphous ones like angry mob
///< bits determining what kind of special abilities this object has access to.
///< who is the only other object that can give me this non-stacking heal benefit?
///< on what frame can I accept healing (thus to switch) from a new benefactor
// Layer object is pathing on.
// Layer of current path goal.
///< To allow specific object to switch command sets
///<flag used by occlusion renderer so it knows when objects have exited their production building.
///< status as set by scripting, corresponds to ORed ObjectScriptStatusBits
///< status bits that are never directly accessible to outside world
// end class Object
// this is the first building
//oops, more than one building!
////////////// SO SORRY, I KNOW THIS IS MICKEY MOUSE ///////////////////

// Context reduced without changing parent bytes or relocation records.
// Packaging evidence: reverse/attempt_support/0x0043003c-20261019-compact/readme.md.

// Preserved inline comments from omitted declarations.
//for kill()
///< Object is effectively dead
///< set to true when I defect from my team; set to false when I attack anything or when time runs out
///< set to true if I've been captured, otherwise, its false. (Note: Never becomes false once it's true)
///< set to true if I am known to be OFF the current map.
///< other Things that are members of the same team
// DEBUG_LOGGING
// _OBJECT_H_
