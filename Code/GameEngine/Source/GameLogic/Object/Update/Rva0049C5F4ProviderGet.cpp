// cl: /DNDEBUG /MD
// ?rva0049C5F4@Rva0049C5F4@@QAEPAXPAVObject@@@Z @0x0049C5F4 48B
// Producer-provider slot31 forward. Retail takes Object arg with +0x78
// producer ID; finds producer via TheGameLogic at 0x00DFE78C through rowed
// findObjectByID; returns null when arg null or producer missing or its
// +0x250 provider null; else returns provider vtable slot 0x7C (slot31).
// Evidence: unlock lane; callers at 0x0049C70F in 0x0049C6E1 plus 0x0049CAC0;
// unblocks 0x0049C6E1; thiscall ecx passed by callers but unused so the
// class stays empty and address-derived. Flags /O1 /DNDEBUG /MD already fit.
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0049C73A_2 = 2,
	OS_3 = 3,
	OS_42 = 0x42,
	OBJECT_STATUS_RVA0049C73A_66 = 0x42
};

class Provider31
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual void *slot31();
};

class Player;
struct Coord3D;
class UpgradeTemplate;
class ThingTemplate;
class AIUpdate;
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	Object *rva002931F5(bool flag);
	Player *getControllingPlayer() const; // 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const; // 0x0004E536
	const Coord3D *getPosition() const { return &m_pos; }
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04 +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38 +0x38
	char m_pad44[0x34];
	ObjectID m_78; // +0x78 +0x78
	char m_pad7C[0x1D4];
	Provider31 *m_prov250; // +0x250
	char m_pad254[0x4];
	AIUpdate *m_ai; // +0x258
	char m_pad25C[0x18];
	int m_int274; // +0x274
	char m_pad278[0xC];
	unsigned m_284[32]; // +0x284 +0x284 the upgrade mask
	char m_pad304[0x134];
	unsigned char m_b438; // +0x438
	char m_pad439[0x3];
};


extern GameLogic *TheGameLogic;

class Rva0049C5F4
{
public:
	void *rva0049C5F4(Object *arg);
};

void *Rva0049C5F4::rva0049C5F4(Object *object)
{
	if (object == 0)
		return 0;
	Object *found = TheGameLogic->findObjectByID(object->m_78);
	if (found == 0)
		return 0;
	Provider31 *prov = found->m_prov250;
	if (prov == 0)
		return 0;
	return prov->slot31();
}
