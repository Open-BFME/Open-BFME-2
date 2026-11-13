// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x004C888D (318 bytes): CombineHordeSpecialPower::doSpecialPower, slot
// 10 of its special-power interface vftable 0x0085E708 (+0x10 subobject;
// [ecx-8] is the Object, [ecx-0xC] the module data), beside the matched
// CombineHordeSpecialPower pool key 0x004C880D. Name by address, as
// SplitHordeSpecialPower's slot 10 (0x004C861E). Unless the object is
// disabled: the interface's slot 15 with 1.0, then the first alive object of
// kind 109, other than this one, that the controlling player's 0x0026137E
// filter accepts within the module data's +0x7C radius (BFME2's partition
// filter chain, the view AIStructureCreepTactic.cpp documents) and whose
// contain interface (Object::rva0028C197) answers slot 28 for this object
// gets the AI command 0x0036EC1D from this object's AI (CMD_FROM_AI).
#include <string.h>

class Object;
class Player;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
#include "../../../../Include/GameLogic/Rva0026119DFilter.h"

// vftable 0x00BF91BC, allow 0x002611BF.
#include "../../../../Include/GameLogic/Rva002611BFFilter.h"

// vftable 0x00BFAD28, allow 0x0026137E: +0x08 a player, +0x0C whether a hit
// allows.
#include "../../../../Include/GameLogic/Rva0026137EFilter.h"

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00C1A25C: any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask);	// 0x003959FA
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};


// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva004C888DMask
{
	Rva004C888DMask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

#include "../../../../Include/Common/BitFlagsTemplate.h"

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

// What precedes the AICommandInterface subobject (+0x20).
class Rva004C888DAIBase
{
public:
	virtual void rva004C888DAIBaseAnchor();
private:
	char m_pad04[0x1C];
};


template <int N> class Rva004C888DSlots : public Rva004C888DSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C888DSlots<0>
{
};

// The contain interface returned by Object::rva0028C197: slot 28 asks about
// an object.
class Rva004C888DContain : public Rva004C888DSlots<28>
{
public:
	virtual bool rva004C888DSlot28(Object *obj) = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void *rva0028C197() const;		// 0x0028C197
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	unsigned char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad044[0x1C8 - 0x44];
	BitFlags<11> m_disabledMask;	// +0x1C8
	unsigned char m_pad1CC[0x258 - 0x1CC];
	AIUpdateInterface *m_ai;	// +0x258
};

class ModuleData;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
template <int N> class Rva004C888DSPSlots : public Rva004C888DSPSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C888DSPSlots<0>
{
};
// The +0x10 interface: slots 0..9 placeholders, slot 10 below, slot 15 takes
// a float.
class Rva004C888DIface10 : public Rva004C888DSPSlots<10>
{
public:
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void rva004C888DSlot15(float amount) = 0;
};
class SpecialPowerModule : public BehaviorModule, public Rva004C888DIface10
{
};

struct CombineHordeSpecialPowerModuleData
{
	unsigned char m_pad00[0x7C];
	float m_7C;	// +0x7C the radius
};

class CombineHordeSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
private:
	const CombineHordeSpecialPowerModuleData *getCombineHordeSpecialPowerModuleData() const
	{
		return (const CombineHordeSpecialPowerModuleData *)m_moduleData;
	}
};

void CombineHordeSpecialPower::doSpecialPower(unsigned int)
{
	Object *object = m_object;
	if (object->m_disabledMask.any())
		return;
	rva004C888DSlot15(1.0f);

	Rva004C888DMask mask;
	mask.set(109);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(object->getPosition(), getCombineHordeSpecialPowerModuleData()->m_7C, 0,
		Rva0026137EFilter(object->getControllingPlayer(), true).link(Rva0026119DFilter()
			.link(Rva003959FA(*(BfmeFixedStorage0004543D *)&mask).link(&Rva002611BFFilter(object)))), 1);
	Object *other;
	while ((other = hits.next()) != 0) {
		Rva004C888DContain *contain = (Rva004C888DContain *)other->rva0028C197();
		if (contain && contain->rva004C888DSlot28(object)) {
			object->getAIUpdateInterface()->rva0036EC1D(other, CMD_FROM_AI);
			break;
		}
	}
}
