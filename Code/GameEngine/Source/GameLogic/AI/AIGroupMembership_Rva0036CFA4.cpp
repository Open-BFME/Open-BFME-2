// cl: -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
// stlport
// Open-BFME: the four AIGroup members that ask or change who is in the group.
//
//   ?isMember@                            0x00150990,  37 bytes
//   ?containsAnyObjectsNotOwnedByPlayer@  0x001509C0,  57 bytes
//   ?remove@                              0x00151800, 104 bytes
//   ?removeAnyObjectsNotOwnedByPlayer@    0x00151890,  74 bytes
//
// Two pairs, and the pairing is the point. isMember and containsAny only ask --
// one by _STL::find over the member list, one by walking it and comparing each
// object's controlling player. remove and removeAny change it, and removeAny is
// written on top of remove: it walks, advances the iterator BEFORE calling
// remove because that call invalidates it, and stops the moment remove reports
// the group is gone.
//
// remove is the only one of the four that says what AIGroup actually looks like.
// The other three declare `unsigned char m_unmodelled_000[4]` at this+0x00 and
// stop at the member list; remove names the prefix -- a pool object's vptr at
// +0x00, the list at +0x04, the cached size at +0x08, the dirty flag at +0x10 --
// and it is the reason the four bodies agree the list is at +0x04 rather than at
// the start.
//
// Only two of those names are proved by a body in this TU: remove decrements
// +0x08 and sets +0x10. +0x0C it never touches, and the account it inherited
// called that slot m_speed. The constructor at 0x00151BF0
// (AIGroupAttackMoveOrder.cpp's flag family, so it cannot live here) settles it
// by writing every field: +0x0C is the ground path, and m_speed is at +0x24,
// past the group id at +0x14 and the seven formation floats. The name is
// corrected below; it is a void* either way, so the layout and these four bodies
// are unaffected.
//
// removeAny used to reach remove through a declaration carrying `ILT 0x000441A2`,
// because the definition was in another file. It is now a call inside one TU.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <algorithm>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Player;
class AIGroup;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Provider250
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual Player *slotE0();
};

class Object
{
public:
	Player *getControllingPlayer(void) const;		// ILT 0x00020824
	void leaveGroup(void);					// ILT 0x0001F212
	char m_pad00[0x250];
	Provider250 *m_provider250;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	void destroyGroup(AIGroup *group);			// ILT 0x00015F69
};

extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool isMember(Object *member);
	Bool containsAnyObjectsNotOwnedByPlayer(const Player *ownerPlayer);
	Bool remove(Object *member);
	Bool removeAnyObjectsNotOwnedByPlayer(const Player *ownerPlayer);
	Bool rva0036CFE5(const Player *ownerPlayer);

	Bool isEmpty(void) { return m_memberList.empty(); }

private:
	virtual ~AIGroup();					// pool object vptr, this+0x00

	_STL::list<Object *> m_memberList;			// this+0x04
	UnsignedInt m_memberListSize;				// this+0x08
	void *m_groundPath;					// this+0x0C, not m_speed
	Bool m_dirty;						// this+0x10
};

Bool AIGroup::removeAnyObjectsNotOwnedByPlayer( const Player *ownerPlayer )
{
	_STL::list<Object *>::iterator memberIterator;

	for (memberIterator = m_memberList.begin(); memberIterator != m_memberList.end(); /* empty */) {
		Object *memberObject = (*memberIterator);
		if (!memberObject) {
			continue;
		}

		if (memberObject->getControllingPlayer() != ownerPlayer) {
			// Advance the iterator first, its about to become invalid.
			++memberIterator;

			if (remove(memberObject)) {
				return true;
			}
			continue;
		}

		++memberIterator;
	}

	return false;
}

// ?rva0036CFE5@AIGroup@@QAE_NPBVPlayer@@@Z, retail 0x0036CFE5, 80 bytes.
// AIGroup member filter like removeAnyObjectsNotOwnedByPlayer but through the
// Object +0x250 provider slot 0xe0: keeps objects whose provider exists and its
// slotE0 equals the owner, otherwise advances then remove (also removes when the
// provider is null), true when remove destroys the group. Evidence: same +0x04
// list and remove 0x0036CF07 row as neighbours, same bool(PBVPlayer) ret-4 shape
// as removeAny, provider +0x250 per ObjectRva0028C197 and slot 0xe0 call site.
Bool AIGroup::rva0036CFE5(const Player *ownerPlayer)
{
	_STL::list<Object *>::iterator it;
	for (it = m_memberList.begin(); it != m_memberList.end(); /* empty */) {
		Object *obj = (*it);
		if (!obj) {
			continue;
		}
		Provider250 *p = obj->m_provider250;
		if (!p || p->slotE0() != ownerPlayer) {
			++it;
			if (remove(obj)) {
				return true;
			}
			continue;
		}
		++it;
	}
	return false;
}
