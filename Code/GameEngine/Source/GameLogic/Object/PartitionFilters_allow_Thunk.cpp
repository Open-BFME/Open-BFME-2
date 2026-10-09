// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/Object/PartitionFilters_allow_Thunk.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: PartitionFilterPlayer::allow 0x0026137E (37B),
// PartitionFilterIrregularArea::allow 0x0026170A (25B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
// Open-BFME5: partition filter bodies whose member offsets PartitionManager.cpp
// cannot reproduce -- PartitionFilterIrregularArea::allow,
// PartitionFilterPlayer::allow, and PartitionFilterPossibleToAttack's
// constructor.
//
// All three are the Zero Hour source unchanged; only the layout differs, and
// the three of them together say the layout differs PER FILTER, not once in the
// shared base:
//
//   PartitionFilterPossibleToAttack  ctor writes +0x04, +0x08, +0x0c
//   PartitionFilterPlayer            allow reads  +0x08, +0x0c
//   PartitionFilterPlayerAffiliation allow reads  +0x08, +0x0c, +0x10
//
// ZH's PartitionFilter contributes only a vtable pointer, so the first member
// should land at +0x04 -- which is exactly what PossibleToAttack does. So the
// base is NOT four bytes wider in BFME; the two that start at +0x08 each carry
// something of their own ahead of the members ZH declares. Widening
// PartitionFilter to explain them would break this constructor.
//
// Spelled locally rather than fixed in PartitionManager.cpp, which would move
// every one of its 74 matched rows, the same way
// PartitionFilterPlayerAffiliation_allow_Thunk.cpp already does.

struct Coord3D;
class Player;

// Only needed so the constructor below mangles as retail does; no value in
// either is read by any body here.
enum AbleToAttackType { ATTACK_TYPE_UNRECONSTRUCTED };
#include "../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"

bool PointInsideArea2D(const Coord3D *pt, const Coord3D *area, int numPoints);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
 int rva0028D481() const;
 int rva0028D4C4() const;
	// Thing::getPosition() is inlined at both call sites as &m_cachedPos;
	// retail reaches it with `add edx,0x38`.
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)(m_unreconstructed_00 + 0x38);
	}

	Player *getControllingPlayer(void) const;			///< pinned at 0x00020824

private:
	unsigned char m_unreconstructed_00[0x38];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterIrregularArea
{
protected:
	virtual bool allow(Object *);

private:
	unsigned char m_unreconstructed_04[0x08 - 4];		///< vtable slot then unpinned base bytes
	const Coord3D *m_area;								///< retail this+0x08
	int m_numPointsInArea;								///< retail this+0x0C
};

// Members land at +0x04 with nothing between them and the vtable pointer --
// this is the filter that shows the shared base is a bare vptr.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterPossibleToAttack
{
public:
	PartitionFilterPossibleToAttack(AbleToAttackType attackType, const Object *source,
		CommandSourceType commandSource);

protected:
	virtual bool allow(Object *);

private:
	AbleToAttackType m_attackType;						///< retail this+0x04
	const Object *m_source;								///< retail this+0x08
	CommandSourceType m_commandSource;					///< retail this+0x0c
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterPlayer
{
protected:
	virtual bool allow(Object *);

private:
	unsigned char m_unreconstructed_04[0x08 - 4];		///< vtable slot then unpinned base bytes
	const Player *m_player;								///< retail this+0x08
	bool m_match;										///< retail this+0x0C
};

// ?allow@PartitionFilterIrregularArea@@MAE_NPAVObject@@@Z
bool PartitionFilterIrregularArea::allow(Object *other)
{

	return PointInsideArea2D(other->getPosition(), m_area, m_numPointsInArea);
}

// ?allow@PartitionFilterPlayer@@MAE_NPAVObject@@@Z
bool PartitionFilterPlayer::allow(Object *other)
{
	return ((m_player == other->getControllingPlayer()) == m_match);
}

// The matched filter users that build PartitionFilterPlayer inline name its
// class by its allow address (Rva0026137EFilter, vftable 0x00BFAD28); their
// slot-1 reference binds to this body.
#pragma comment(linker, "/alternatename:?allow@Rva0026137EFilter@@UAE_NPAVObject@@@Z=?allow@PartitionFilterPlayer@@MAE_NPAVObject@@@Z")

void iterRel001DCF20(Object *object, void *state);
enum CanEnterType { ENTER_MODE_ZERO = 0 };
class BFMEActionManager
{
public:
    bool canEnterObject(const Object *owner, const Object *target,
        CommandSourceType source, CanEnterType mode, bool options, bool *outFlag);
};
class ActionManager;
extern ActionManager *TheActionManager;
template<int N> class Rva002612C6PrefixSlots : public Rva002612C6PrefixSlots<N-1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class Rva002612C6PrefixSlots<0> {};
class Rva002612C6ReadySlot : public Rva002612C6PrefixSlots<4>
{
public:
    virtual bool ready() = 0;
};
template<int N> class Rva002612C6MiddleSlots : public Rva002612C6MiddleSlots<N-1>
{
public:
    virtual void middle(char (*)[N]) = 0;
};
template<> class Rva002612C6MiddleSlots<0> : public Rva002612C6ReadySlot {};
class Rva002612C6ContainView : public Rva002612C6MiddleSlots<63>
{
public:
    virtual void iterate(void (*callback)(Object *, void *), void *state, bool reverse) = 0;
};
struct Rva002612C6ObjectView
{
    char unknown00[0x250];
    Rva002612C6ContainView *contain;
};
struct Rva002612C6State { Object *owner; unsigned char bad; };
class Rva002612C6
{
public:
    bool rva002612C6(Object *candidate);
private:
    char unknown00[8];
    Object *owner;
    bool skipRelationship;
};
// Recovery of the complete 141-byte retail body at RVA 0x002612C6.
// Reference lead: Open-BFME-1 0bef414b52a39a3ab1ec98dca60d8a214de4260e,
// game/GameEngine/Source/Common/Gen_001DCF50.cpp, nested can-enter flow.
// Target evidence: d_002612c6.asm and WB 0x00E5CDB0 share the call graph;
// native bytes establish owner +8, flag +0xC, contain +0x250 and virtual
// slots +0x10/+0x110. The original target class/method name remains unknown.
// Both Object readers return int with their low byte tested; the established
// ActionManager provider takes a bool fifth argument. No donor ILT alias is used.
bool Rva002612C6::rva002612C6(Object *candidate)
{
    if (static_cast<unsigned char>(candidate->rva0028D481())) {
        if (static_cast<unsigned char>(candidate->rva0028D4C4())) {
            Rva002612C6ContainView *contain =
                reinterpret_cast<Rva002612C6ObjectView *>(candidate)->contain;
            if (contain) {
                if (contain->ready()) {
                    if (reinterpret_cast<BFMEActionManager *>(TheActionManager)->canEnterObject(
                            owner, candidate, CMD_FROM_AI, ENTER_MODE_ZERO, true, 0)) {
                        if (skipRelationship) return true;
                        Rva002612C6State state;
                        state.bad = 0;
                        state.owner = owner;
                        contain->iterate(iterRel001DCF20, &state, true);
                        return state.bad ? false : true;
                    }
                }
            }
        }
    }
    return false;
}
