// cl: /DNDEBUG /MD
// ?rva00466C04@Rva00466C04@@QAE_NPAVObject@@I@Z 0x00466C04 144B
// Healing with frame check: DamageInfo 0x7C via rowed Rva00263895Member ctor, source from this+8 ID, damage 7 death 1, amount via body slot06 direct or divided by unsigned val, body slot01 attemptHealing, returns frame check.
// Evidence: calls rowed 0x263895 ctor; TheGameLogic+0x40 minus obj+0x27C vs val (jb); slot06 at +0x18 fstp to +0x20 then slot01 at +4; fild/fadd g_00BC26EC/fdivp unsigned val conversion; callers 0x466CEA.
class GameLogic
{
public:
	char m_pad[0x40];
	unsigned m_frame40;
};
extern GameLogic *TheGameLogic;

class Rva00263653
{
public:
	Rva00263653() throw();
	virtual void rva00263653_dummy();
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	float m_1C;
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_pad22[2];
	float m_24;
	int m_28;
	int m_2C;
	float m_30;
	float m_34;
	float m_38;
	float m_3C;
	float m_40;
	float m_44;
	float m_48;
	unsigned char m_4C;
	unsigned char m_pad4D[3];
	float m_50;
	float m_54;
	float m_58;
	float m_5C;
	float m_60;
	float m_64;
};

class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	virtual void rva00263895_dummy();
	Rva00263653 m_mem;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};

class BodyModuleInterface
{
public:
	virtual void slot00() throw();
	virtual void attemptHealing(Rva00263895Member *info) throw();
	virtual void slot02() throw();
	virtual void slot03() throw();
	virtual void slot04() throw();
	virtual void slot05() throw();
	virtual float slot06() throw();
};

class Object
{
public:
	char m_pad00[0x74];
	int m_id74;
	char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body254;
	char m_pad258[0x27C - 0x258];
	unsigned m_frame27C;
};

class Rva00466C04
{
public:
	bool rva00466C04(Object *obj, unsigned val);
private:
	char m_pad[8];
	Object *m_owner8;
};

bool Rva00466C04::rva00466C04(Object *obj, unsigned val)
{
	bool healed = false;
	Rva00263895Member dmg;
	dmg.m_mem.m_0C = 7;
	dmg.m_mem.m_18 = 1;
	dmg.m_mem.m_04 = m_owner8->m_id74;
	unsigned frameDiff = TheGameLogic->m_frame40 - obj->m_frame27C;
	BodyModuleInterface *body = obj->m_body254;
	if (frameDiff >= val)
	{
		dmg.m_mem.m_1C = body->slot06();
		body->attemptHealing(&dmg);
		healed = true;
	}
	else
	{
		dmg.m_mem.m_1C = body->slot06() / (float)val;
		body->attemptHealing(&dmg);
	}
	return healed;
}
