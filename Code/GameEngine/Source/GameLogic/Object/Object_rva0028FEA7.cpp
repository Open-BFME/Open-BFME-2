// cl: /DNDEBUG /MD
//
// ?rva0028FEA7@Object@@QAE_NMPBV1@I@Z @0x0028FEA7 (247B).
// Object healing-benefactor update plus body DamageInfo forward plus
// effectively-dead handling. Evidence: neighbours Object_attemptHealing
// 0x0028FE55 and Object_healCompletely 0x0028FF9E prove Object class and
// DamageInfo 0x7C shape with type 7 death 1 via pinned ctor 0x263895 and
// body slot 1; TheGameLogic frame at +0x40 with benefactor at +0x3B8 and
// expiration at +0x3BC via getSoleHealingBenefactor 0x0028B204; template
// flags at +0x108 bit 0x8000 and +0x632 plus status at +0x10c bits 0x20/0x10
// and +0x438 bit 0 plus rva0028AE6D and setEffectivelyDead pins from retail.

typedef unsigned int UnsignedInt;
typedef int ObjectID;

class GameLogic
{
public:
	char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

class ObjectTemplate
{
public:
	char m_pad00[0x108];
	UnsignedInt m_flags108; // +0x108
	char m_pad10C[0x632 - 0x10C];
	unsigned char m_flag632; // +0x632
};

class Rva00263895Member
{
public:
	Rva00263895Member();
	char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
	char m_pad0C[0x04];
	int m_damageType; // +0x10
	char m_pad14[0x08];
	int m_deathType; // +0x1C
	float m_amount; // +0x20
	char m_pad24[0x7C - 0x24];
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void attemptHealing(Rva00263895Member *info);
};

class Object
{
public:
	bool rva0028FEA7(float amount, const Object *source, UnsignedInt extra);
	void rva0028AE6D();
	void setEffectivelyDead(bool dead);

private:
	void *m_vptr; // +0x00
	ObjectTemplate *m_template; // +0x04
	char m_pad08[0x74 - 0x08];
	int m_id; // +0x74
  char m_pad78[0x10C - 0x78];
  union {
    volatile UnsignedInt m_flags10C; // +0x10C
    volatile unsigned char m_flags10C_byte; // low byte of +0x10C for byte test
  };
	char m_pad110[0x254 - 0x110];
	BodyModuleInterface *m_body; // +0x254
	char m_pad258[0x3B8 - 0x258];
	ObjectID m_benefactor; // +0x3B8
	UnsignedInt m_expiration; // +0x3BC
	char m_pad3C0[0x438 - 0x3C0];
	unsigned char m_flag438; // +0x438
};

bool Object::rva0028FEA7(float amount, const Object *source, UnsignedInt extra)
{
	if (!source)
		return false;
  UnsignedInt curFrame = TheGameLogic->m_frame;
  ObjectID earlyID = source->m_id;
  if (curFrame <= m_expiration) {
    if (m_benefactor == earlyID)
      goto update_done;
    if ((source->m_template->m_flags108 & 0x8000) == 0)
      return false;
  update_done:;
  }
	if ((source->m_template->m_flags108 & 0x8000) == 0) {
		m_benefactor = earlyID;
		m_expiration = curFrame + extra;
	}
	BodyModuleInterface *body = m_body;
	if (body) {
		Rva00263895Member damageInfo;
		damageInfo.m_sourceID = source->m_id;
		damageInfo.m_damageType = 7;
		damageInfo.m_deathType = 1;
		damageInfo.m_amount = amount;
		body->attemptHealing(&damageInfo);
	}
	if (m_template->m_flag632 == 0)
		return true;
  if (m_flags10C_byte & 0x20) {
    m_flags10C &= (UnsignedInt)~0x20;
    rva0028AE6D();
  }
	if ((m_flag438 & 1) == 0)
		return true;
  if ((m_flags10C_byte & 0x10) == 0) {
    m_flags10C |= 0x10;
    rva0028AE6D();
  }
	setEffectivelyDead(false);
	return true;
}
