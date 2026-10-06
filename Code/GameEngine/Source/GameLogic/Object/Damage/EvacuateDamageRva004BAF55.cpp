// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?onDamage@EvacuateDamage@@UAEXPAUDamageInfo@@@Z @ 0x004BAF55 144B
// EvacuateDamage onDamage with evacuation record and threshold. Evidence:
// BFME1 donor EvacuateDamage_onDamage.cpp (same shape, DamageInfo +0x08
// source +0x10 type +0x20 amount, moduleData +0x0C type +0x10 scale,
// list at +0x14, TheGameLogic frame +0x40, BodyModule getHealth slot 0x18,
// rowed list<BfmeSpecialPowerTimer8>::push_back 0x004DE74D, rowed sum
// 0x004BADC1, rowed findObjectByID 0x00049DC5, rowed rva004BAF2D 0x004BAF2D);
// 8B record is list<BfmeSpecialPowerTimer8>, amount bitcast to m_templateID
// per Rva004E5344 precedent; sole caller 0x004BB0AF in 0x004BAFE5;
#define _STLP_NO_EXCEPTIONS 1
#include <list>

enum ObjectID
{
	OBJECTID_NONE = 0
};

struct DamageInfo
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceObject;
	unsigned char m_pad0C[0x04];
	int m_damageType;
	unsigned char m_pad14[0x0C];
	float m_amount;
};

class BodyModule
{
public:
	virtual void s0() = 0;
	virtual void s1() = 0;
	virtual void s2() = 0;
	virtual void s3() = 0;
	virtual void s4() = 0;
	virtual void s5() = 0;
	virtual float getHealth() = 0;
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

struct WeaponTemplate;

class Weapon
{
public:
	unsigned char m_pad[4];
	WeaponTemplate *m_template;   // +4 (retail loads it, name string at +8)
};

class Rva004BAFE5Iface;

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	unsigned char m_pad[0x250];
	Rva004BAFE5Iface *m_iface;   // +0x250 (retail vcalls slots 29/32/70)
	BodyModule *m_body;
};

class EvacuateDamageModuleData
{
public:
	unsigned char m_pad[0x0C];
	int m_damageType;
	float m_evacuationScale;
};

class GameLogic
{
public:
	unsigned char m_pad[0x40];
	int m_frame;
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct BfmeSpecialPowerTimer8
{
	unsigned int m_templateID;
	unsigned int m_readyFrame;
};

class EvacuateDamage
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	void rva004BAF2D(void *obj);
	float rva004BADC1();
private:
	EvacuateDamageModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[8];
	_STL::list<BfmeSpecialPowerTimer8> m_pendingEvacuations;
};

void EvacuateDamage::onDamage(DamageInfo *damageInfo)
{
	if (damageInfo == 0)
		return;
	int damageType = damageInfo->m_damageType;
	EvacuateDamageModuleData *moduleData = m_moduleData;
	if (moduleData->m_damageType != damageType)
		return;
	if (m_object->m_body == 0)
		return;
	BfmeSpecialPowerTimer8 record;
	*(float *)&record.m_templateID = damageInfo->m_amount;
	record.m_readyFrame = TheGameLogic->m_frame;
	m_pendingEvacuations.push_back(record);
	float health = m_object->m_body->getHealth();
	if (rva004BADC1() >= health * moduleData->m_evacuationScale)
	{
		Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceObject);
		if (source != 0)
			rva004BAF2D(source);
	}
}

// Included late so the pragma inside cannot perturb the landed row above.
// Shared one-pointer AsciiString + StringBase<char> (compare row 0x000069D6).
#include "ascii_string.h"

struct WeaponTemplate
{
	unsigned char m_pad[8];
	AsciiString m_name;   // +8 (compared against our data name)
};

struct Rva004BAFE5Data
{
	unsigned char m_pad[8];
	AsciiString m_name;   // +8 (weapon name to match)
	int m_damageType;     // +0xC
};

class Rva004BAFE5Iface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual int v29();
	virtual void v30();
	virtual void v31();
	virtual void v32(int);
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70(void *);
};

struct Rva004BAFE5State
{
	unsigned char m_pad[0x115];
	unsigned char m_flags;   // +0x115 (retail tests 0x20)
	unsigned char m_pad2[0x258 - 0x116];
	void *m_unused;
};

struct Rva004BAFE5Team
{
	void *m_unk0;
	Rva004BAFE5State *m_state;   // +4
	unsigned char m_pad[0x258 - 8];
	void *m_aicBase;            // +0x258 (AICommandInterface at +0x20)
};

struct Rva004BAFE5Node
{
	Rva004BAFE5Node *m_next;     // +0
	void *m_unk04;              // +4 (retail skips it)
	Rva004BAFE5Team *m_team;    // +8
};

struct Rva004BAFE5Out
{
	void *m_unk0;
	Rva004BAFE5Node **m_ppHead;  // +4
};

enum CommandSourceType
{
	CMDSRC_UNKNOWN = 0
};

class AICommandInterface
{
public:
	void rva0037379B(Object *obj, CommandSourceType src);
	void aiExit(Object *obj, CommandSourceType src);
};

class Rva004BAFE5
{
public:
	void rva004BAFE5(DamageInfo *d);
private:
	// No declared members: retail addresses the owning damage object with
	// explicit (char *)this - N arithmetic (evac at -0x10, data at -0xC,
	// object at -8), reproduced below.
};

//
// ?rva004BAFE5@Rva004BAFE5@@QAEXPAUDamageInfo@@@Z @ 0x004BAFE5 214B
// Chain from ?onDamage@EvacuateDamage@@UAEXPAUDamageInfo@@@Z (called at
// 0x004BB0AF with ecx = this - 0x10). When the damage source's current
// weapon template name matches our data name, the team at object +0x250 is
// walked (v29/v32/v70) and each entry is ordered to attack or exit via rowed
// AICommandInterface 0x0037379B/0x0036F39B; otherwise a damage-type match
// delegates to EvacuateDamage::onDamage. Evidence: rowed findObjectByID
// 0x00049DC5, getCurrentWeapon 0x0028AEBD, StringBase compare 0x000069D6,
// AI calls rowed, vtable slots from retail, prev/next Damage neighbours.
void Rva004BAFE5::rva004BAFE5(DamageInfo *d)
{
	Rva004BAFE5Data *data = *(Rva004BAFE5Data **)((char *)this - 12);
	Object *src = TheGameLogic->findObjectByID(d->m_sourceObject);
	if (src == 0)
		return;
	const Weapon *w = src->getCurrentWeapon((WeaponSlotType *)0);
	if (w == 0)
		return;
	AsciiString *wname = (AsciiString *)((char *)w->m_template + 8);
	if (((const StringBase<char> &)data->m_name).compare((const StringBase<char> &)*wname) == 0)
	{
		Rva004BAFE5Iface *ifc = (*(Object **)((char *)this - 8))->m_iface;
		if (ifc == 0)
			return;
		if (ifc->v29() == 0)
		{
			ifc->v32(2);
			return;
		}
		Rva004BAFE5Out out;
		ifc->v70(&out);
		Rva004BAFE5Node *n = (*out.m_ppHead)->m_next;
		if (n == *out.m_ppHead)
			return;
		do
		{
			Rva004BAFE5Team *team = n->m_team;
			Rva004BAFE5State *st = team->m_state;
			if ((st->m_flags & 0x20) != 0)
			{
				char *aicBase = (char *)team->m_aicBase;
				((AICommandInterface *)(aicBase + 0x20))->rva0037379B(
					*(Object **)((char *)this - 8), (CommandSourceType)2);
			}
			else
			{
				char *aicBase = (char *)team->m_aicBase;
				((AICommandInterface *)(aicBase + 0x20))->aiExit(
					*(Object **)((char *)this - 8), (CommandSourceType)2);
			}
			n = n->m_next;
		} while (n != *out.m_ppHead);
		return;
	}
	if (data->m_damageType != d->m_damageType)
		return;
	((EvacuateDamage *)((char *)this - 0x10))->EvacuateDamage::onDamage(d);
}
