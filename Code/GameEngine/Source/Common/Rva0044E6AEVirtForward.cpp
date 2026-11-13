// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0044E6AE@Rva0044E6AE@@QAEXXZ @0x0044E6AE 10B
// Virtual forward with (0 1) through slot 0x34. Retail is mov eax [ecx]
// push 1 push 0 call [eax+0x34] ret. Evidence: unlock lane; callers at
// 0x0029314E 0x0049C96F 0x0049C9BD plus jmp at 0x0049C937; unblocks 0x0049C8FC
// 0x00293105 0x0049C93F; abuts prev row 0x0044E6A7 which ends at this start;
// flags copied from next TU ModuleDataBuildFieldParseChained.cpp. Owner
// unproven so the name stays address-derived. Class extended with +0x08
// Object plus +0x40 ID plus +0x89 flag for chain caller 0x0049C8FC below
// which tail-jmps here with the same this; noinline keeps that tail as a
// jmp instead of inlining this 10B body.
//
// ?triggerAbilityEffect@Rva0044E6AE@@QAEXXZ @0x0049CA2F 296B (RF-1296-49CA2F)
// A set byte at +0x88 returns. Otherwise the base slot runs, the +0x40 id is
// resolved, and a rejected target is told to idle. An accepted target clears
// +0x89, applies the upgrade at object+0x284 through the provider slot 0x46
// or the arg-985 tint path, deselects, then runs the rowed +0x49C67E finish.
// Evidence: rowed chain caller 0x0049C8FC uses the same class view (m_obj08
// +0x40 id +0x88 +0x89); retail 0x0049CA2F..0x0049CB57 ends before the fld
// getter at 0x0049CB57; the upgrade pointer keeps a volatile home tested in
// the register, which the pair (up, upgrade) reproduces.
#include "GameLogicObjectLookupView.h"

class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

#include "../../Include/GameLogic/Module/AIUpdate.h"

#include "../../Include/Common/ThingTemplate.h"

#include "../../../Libraries/Include/Lib/RGBColor.h"

#include "../../Include/GameClient/Drawable.h"

class UpgradeTemplate;

class Object
{
public:
	void *rva0028C197() const;
	void rva00293077(const void *upgrade);
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	Drawable *getDrawable() const;

	char m_pad00[4];
	ThingTemplate *m_tmpl;		// +0x04
	char m_pad08[0x258 - 0x08];
	AIUpdateInterface *m_ai258;	// +0x258
	char m_pad25C[0x284 - 0x25C];
	int m_284;			// +0x284
	char m_pad288[0x438 - 0x288];
	unsigned char m_privateStatus;	// +0x438
};


extern GameLogic *TheGameLogic;

#include "../../Include/GameLogic/Module/Rva0026F0F0.h"

class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;

class Rva0049C5F4
{
public:
	void *rva0049C5F4(Object *arg);
};

#include "../../Include/Common/Rva0049C6E1.h"

class Rva0049C67E
{
public:
	void rva0049C67E(Object *obj);
};

class Prov46
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45();
	virtual void slot46(void *upgrade, int zero);
};

#include "../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Rva0044E6AE
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual void virt34(int a, int b);
	__declspec(noinline) void rva0044E6AE();
	void rva0049C8FC();
	void triggerAbilityEffect();
	char m_pad04[4];
	Object *m_obj08;		// +0x08
	char m_pad0C[0x40 - 0x0C];
	ObjectID m_id40;		// +0x40
	char m_pad44[0x88 - 0x44];
	unsigned char m_flag88;		// +0x88
	unsigned char m_flag89;		// +0x89
};

void Rva0044E6AE::rva0044E6AE()
{
	virt34(0, 1);
}

// ?rva0049C8FC@Rva0044E6AE@@QAEXXZ @0x0049C8FC 67B
// Chain caller of the 10B forward above with the same this (tail jmp).
// Retail finds Object via TheGameLogic at 0x00DFE78C with +0x40 ID; returns
// when null or when +0x89 flag is clear; else idles AI via +0x08 Object
// through +0x258 plus 0x20 with CMD_FROM_AI (2); clears the flag; tail-jmps
// here. Evidence: chain lane calls rowed 0x0044E6AE; caller at 0x0049478C;
// prev GiveUpgradeUpdateModuleDataDtor; flags /O1 /DNDEBUG /MD already fit.
void Rva0044E6AE::rva0049C8FC()
{
	Object *found = TheGameLogic->findObjectByID(m_id40);
	if (found == 0)
		return;
	if (m_flag89 == 0)
		return;
	m_obj08->m_ai258->aiIdle(CMD_FROM_AI);
	m_flag89 = 0;
	return rva0044E6AE();
}

// ?triggerAbilityEffect@Rva0044E6AE@@QAEXXZ @0x0049CA2F 296B
void Rva0044E6AE::triggerAbilityEffect()
{
	if (m_flag88 != 0)
		return;

	((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::triggerAbilityEffect();
	Object *obj = m_obj08;
	Object *found = TheGameLogic->findObjectByID(m_id40);
	if (found == 0 || (found->m_privateStatus & 1) != 0
		|| ((Rva0049C6E1 *)this)->rva0049C6E1(found) == 0)
	{
		obj->m_ai258->aiIdle(CMD_FROM_AI);
		return;
	}

	m_flag89 = 0;
	void *up = ((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0(&obj->m_284);
	void * volatile upgrade = up;
	if (up != 0)
	{
		void *prov = (found->m_tmpl->m_kindof[3] & (1U << 13)) != 0
			? found->rva0028C197()
			: ((Rva0049C5F4 *)this)->rva0049C5F4(found);
		if (prov != 0)
			((Prov46 *)prov)->slot46(upgrade, 0);
		else if (found->affectedByUpgrade((const UpgradeTemplate *)upgrade))
		{
			float shade = 0.99f;
			RGBColor color;
			color.red = shade;
			color.green = shade;
			color.blue = shade;
			found->rva00293077(upgrade);
			Drawable *draw = found->getDrawable();
			if (draw != 0)
				draw->colorFlash(&color, 4, 4, 0x0F);
		}
		TheGameLogic->deselectObject(obj, 0xFFFFF, 1);
	}
	((Rva0049C67E *)this)->rva0049C67E(obj);
}
