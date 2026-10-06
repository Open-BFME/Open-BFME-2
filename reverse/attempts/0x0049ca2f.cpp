// ?rva0049CA2F@Rva0049CA2F@@QAEXXZ
// partial score=0.72 date=2026-10-06
// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0049CA2F@Rva0049CA2F@@QAEXXZ @0x0049CA2F 296B.
// A set byte at +0x88 returns. Otherwise the base slot runs, the id at +0x40
// is resolved, and a rejected target is told to idle. An accepted target
// clears +0x89, applies the upgrade at object+0x284 through the provider
// slot or the arg985 tint path, deselects, then runs the rowed finish.

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_SRC_2 = 2
};

struct RGBColor
{
	float r;
	float g;
	float b;
};

class ThingTemplate
{
public:
	char m_pad[0x115];
	unsigned char m_115;
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class AIObj
{
public:
	char m_pad[0x20];
	AICommandInterface m_cmd;
};

class Drawable
{
public:
	void rva0027541E(const RGBColor *color, unsigned int a, unsigned int b, unsigned int c);
};

class Object
{
public:
	void *rva0028C197() const;
	void rva00293077(const void *upgrade);
	Drawable *getDrawable() const;

	char m_pad0[4];
	ThingTemplate *m_tmpl;
	char m_pad8[0x258 - 8];
	AIObj *m_ai;
	char m_pad25C[0x284 - 0x25C];
	int m_284;
	char m_pad288[0x438 - 0x288];
	unsigned char m_privateStatus;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void deselectObject(Object *obj, unsigned int mask, int mode);
};

extern GameLogic *TheGameLogic;

class UpgradeCenter;
extern "C" UpgradeCenter *TheUpgradeCenter;
#pragma comment(linker, "/alternatename:_TheUpgradeCenter=?TheUpgradeCenter@@3PAVUpgradeCenter@@A")

class Rva0026F0F0
{
public:
	void *rva0026F0F0(const void *mask);
};

class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
};

class Rva0049C6E1
{
public:
	bool rva0049C6E1(Object *arg);
};

class Rva0049C5F4
{
public:
	void *rva0049C5F4(Object *arg);
};

class Rva0049C67E
{
public:
	void rva0049C67E(Object *obj);
};

class BfmeArg985
{
public:
	char bfmeHas985C(int upgrade);
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

class Rva0049CA2F
{
public:
	void rva0049CA2F();

private:
	char m_pad0[8];
	Object *m_obj;
	char m_padC[0x40 - 0x0C];
	ObjectID m_40;
	char m_pad44[0x88 - 0x44];
	unsigned char m_88;
	unsigned char m_89;
};

void Rva0049CA2F::rva0049CA2F()
{
	if (m_88 != 0)
		return;

	((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::rva0045108D();
	Object *found = TheGameLogic->findObjectByID(m_40);
	Object *obj = m_obj;
	if (found == 0 || (found->m_privateStatus & 1) != 0
		|| ((Rva0049C6E1 *)this)->rva0049C6E1(found) == 0)
	{
		obj->m_ai->m_cmd.aiIdle(CMD_SRC_2);
		return;
	}

	m_89 = 0;
	void *upgrade = ((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0(&obj->m_284);
	if (upgrade != 0)
	{
		void *prov = (found->m_tmpl->m_115 & 0x20) != 0
			? found->rva0028C197()
			: ((Rva0049C5F4 *)this)->rva0049C5F4(found);
		if (prov != 0)
			((Prov46 *)prov)->slot46(upgrade, 0);
		else if (((BfmeArg985 *)found)->bfmeHas985C((int)upgrade) != 0)
		{
			float shade = 0.99f;
			RGBColor color;
			color.r = shade;
			color.g = shade;
			color.b = shade;
			found->rva00293077(upgrade);
			Drawable *draw = found->getDrawable();
			if (draw != 0)
				draw->rva0027541E(&color, 4, 4, 0x0F);
		}
		TheGameLogic->deselectObject(obj, 0xFFFFF, 1);
	}
	((Rva0049C67E *)this)->rva0049C67E(obj);
}
