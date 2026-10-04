// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Retail 0x004C888D (318 bytes): CombineHordeSpecialPower::rva004C888D, slot
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

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFAD28, allow 0x0026137E: +0x08 a player, +0x0C whether a hit
// allows.
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00C1A25C: any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask);	// 0x003959FA
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva004C888DMask
{
	Rva004C888DMask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

template <int N> class BitFlags
{
public:
	bool any() const;	// 0x0023C58B
private:
	unsigned int m_words[(N + 31) / 32];
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms) = 0;
	void rva0036EC1D(Object *obj, CommandSourceType cmdSource);	// 0x0036EC1D
};

// What precedes the AICommandInterface subobject (+0x20).
class Rva004C888DAIBase
{
public:
	virtual void rva004C888DAIBaseAnchor();
private:
	char m_pad04[0x1C];
};

class AIUpdateInterface : public Rva004C888DAIBase, public AICommandInterface
{
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
	bool isDisabled() const { return m_disabledMask.any(); }
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
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
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
	virtual void rva004C888D(unsigned int options) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void rva004C888DSlot15(float amount) = 0;
};
class SpecialPowerModule : public BehaviorModule, public BehaviorModuleInterface, public Rva004C888DIface10
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
	virtual void rva004C888D(unsigned int options);
private:
	const CombineHordeSpecialPowerModuleData *getCombineHordeSpecialPowerModuleData() const
	{
		return (const CombineHordeSpecialPowerModuleData *)m_moduleData;
	}
};

void CombineHordeSpecialPower::rva004C888D(unsigned int)
{
	Object *object = m_object;
	if (object->isDisabled())
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
