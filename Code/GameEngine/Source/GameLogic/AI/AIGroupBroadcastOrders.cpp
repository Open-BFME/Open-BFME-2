// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/AI/AIGroupBroadcastOrders.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// AIGroup::groupDoCommandButton 0x0036DC8D (43B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME: the AIGroup orders that walk the member list and hand the same
// instruction to every object in it.
//
//   ?groupSell@                             0x00150E90,  45 bytes
//   ?groupDoCommandButton@                  0x00150F00,  49 bytes
//   ?groupDoCommandButtonAtPosition@        0x00150F40,  54 bytes
//   ?groupDoCommandButtonAtObject@          0x00150F90,  54 bytes
//   ?setAttitude@                           0x00150FE0,  50 bytes
//   ?queueUpgrade@                          0x00151170, 146 bytes
//   ?groupSetEmoticon@                      0x001514C0,  58 bytes
//   ?groupOverrideSpecialPowerDestination@  0x00151510,  62 bytes
//
// Eight bodies, one loop. m_memberList is at this+0x04 and the walk is over the
// STLport sentinel node -- [this+4] is the node pointer, its next is begin,
// itself is end, and the member object is the node's payload at +0x08. Eight
// files each wrote that paragraph out; it is true of all eight and is stated
// once here.
//
// The bodies differ in two ways worth seeing together. Six take the plain
// `++i` walk; groupSell takes a copy of the iterator and advances BEFORE it acts,
// because selling an object removes it from the list it is walking. And most
// reach the member directly, while setAttitude, groupSetEmoticon and
// groupOverrideSpecialPowerDestination first ask the object for a sub-interface
// and skip the member when there is none.
//
// The eight declared Object eight ways and each was a slice of one class:
// nothing at all (groupSell), four ILT-pinned methods (queueUpgrade), a vptr
// chain ending at getDrawable on vtable+0x28 (groupSetEmoticon), and a flat
// 0x204-byte prefix with the AI pointer behind it (setAttitude). The last two
// look contradictory and are not -- the prefix simply swallows the vptr -- so
// the merged class carries the vtable slice AND the field, which is what says
// m_ai is at +0x204 rather than at "0x204 bytes in from wherever this starts".
//
// One callee is deliberately spelled two ways. doCommandButton takes its command
// source as a plain int and its last argument as bool: that is the row at
// 0x00296749 (`?doCommandButton@Object@@QAEXPBVCommandButton@@H_N@Z`, Object.cpp;
// this call pushes the constant 0 either way), while its AtPosition and AtObject
// siblings take W4CommandSourceType@@.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef int Int;
typedef bool Bool;

class AsciiString;
class CommandButton;
class Player;
struct Coord3D;

#include "../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
enum AttitudeType {};
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum UpgradeType { UPGRADE_TYPE_PLAYER = 0, UPGRADE_TYPE_OBJECT = 1 };
enum CanMakeType { CANMAKE_QUEUE_FULL = 4 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void setEmoticon(const AsciiString &name, Int duration);	// ILT 0x00001A3C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void setAttitude(AttitudeType tude);			// ILT 0x00030553
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h
class SpecialPowerUpdateInterface
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void setSpecialPowerOverridableDestination(const Coord3D *loc);	// vtable +0x14
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType(void) const { return m_type; }

private:
	unsigned char m_unmodelled_000[4];
	UpgradeType m_type;					// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h
class ProductionUpdateInterface
{
public:
	virtual void unusedSlot00();
	virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade);		// vtable +0x04
	virtual void unusedSlot02();
	virtual void queueUpgrade(const UpgradeTemplate *upgrade, Bool bfmeFlag);	// vtable +0x0C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual Drawable *getDrawable(void) const;		// vtable +0x28

	void doCommandButton(const CommandButton *commandButton, Int commandSource, bool bfmeArg);	// ILT 0x000063CF
	void doCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *position, CommandSourceType commandSource, Bool bfmeFlag);	// ILT 0x00026EF4
	void doCommandButtonAtObject(const CommandButton *commandButton, Object *targetObject, CommandSourceType commandSource, Bool bfmeFlag);	// ILT 0x00033AA0
	SpecialPowerUpdateInterface *findSpecialPowerWithOverridableDestinationActive(SpecialPowerType spType) const;	// ILT 0x00039766
	Player *getControllingPlayer(void) const;					// ILT 0x00020824
	Bool hasUpgrade(const UpgradeTemplate *upgrade) const;				// ILT 0x0000BA37
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;			// ILT 0x000077B6
	ProductionUpdateInterface *getProductionUpdateInterface(void);			// ILT 0x00003B52

	AIUpdateInterface *getAIUpdateInterface(void) { return m_ai; }

private:
	unsigned char m_unmodelled_004[0x204 - 4];
	AIUpdateInterface *m_ai;				// +0x204
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
class BuildAssistant
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void unusedSlot13();
	virtual void unusedSlot14();
	virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void unusedSlot17();
	virtual void sellObject(Object *obj);			// vtable +0x48
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	Bool canAffordUpgrade(Player *player, const UpgradeTemplate *upgrade, Bool bfmeFlag, Bool forceCheck) const;	// ILT 0x0001CEA9
};

extern BuildAssistant *TheBuildAssistant;
extern UpgradeCenter *TheUpgradeCenter;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupSell(CommandSourceType commandSource);
	void groupDoCommandButton(const CommandButton *commandButton, CommandSourceType commandSource);
	void groupDoCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *position, CommandSourceType commandSource);
	void groupDoCommandButtonAtObject(const CommandButton *commandButton, Object *targetObject, CommandSourceType commandSource);
	void setAttitude(AttitudeType attitude);
	void queueUpgrade(const UpgradeTemplate *upgrade, Bool bfmeFlag);
	void groupSetEmoticon(const AsciiString &name, Int duration);
	void groupOverrideSpecialPowerDestination(SpecialPowerType specialPowerType, const Coord3D *destination, CommandSourceType commandSource);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};


// The reference's body with one BFME change: the per-object command carries a
// third argument, and this loop passes it zero -- the same shape the two
// AtPosition/AtObject loops below have, one argument narrower.
void AIGroup::groupDoCommandButton( const CommandButton *commandButton, CommandSourceType commandSource )
{
	_STL::list<Object *>::iterator i;
	Object *source;

	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{

		// get object
		source = *i;

		source->doCommandButton( commandButton, commandSource, 0 );
	}  // end for, i
}


