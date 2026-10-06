// ?rva00481A9E@Rva0048180C@@QAEXPAVObject@@_NPAURva00481A9EInfo@@@Z
// partial score=0.951 date=2026-10-06
// ?rva00481A9E@Rva0048180C@@QAEXPAVObject@@_NPAURva00481A9EInfo@@@Z
// partial score=0.97 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /G7 /arch:SSE
//
// ?rva00481A9E@Rva0048180C@@QAEXPAVObject@@_NPAURva00481A9EInfo@@@Z @0x00481A9E (225B).
// Chain from 0x0028FEA7 you landed: healing-benefactor forward plus body
// DamageInfo forward plus effectively-dead handling via vtable slot 15 of
// 0x00849248 (class of ??1Rva0048180C). Evidence: rowed getControllingPlayer
// 0x0028AFA9 plus rowed Player::rva002AB87D 0x002AB87D over +0x2c template
// plus rowed Rva0028ADECmpBoolField::get plus Object body at +0x254 slot 6
// plus g_Va00DBA4E4 int plus rva0028FEA7 row; neighbours 0x00481A54 and
// BitFlags 0x00481B7F share /O1.

typedef unsigned int UnsignedInt;

class Object;
class UpgradeTemplate;

class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *tmpl) const;
};

class UpgradeTemplate
{
public:
	char m_pad00[0x38];
	int m_bitIndex;
};

class Rva0028ADECmpBoolField
{
public:
	bool get() const;
};

class BodyModule
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual float f6();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva0028FEA7(float amount, const Object *source, UnsignedInt extra);
	// Retail keeps the whole 32-bit flag word live in eax across the test and the
	// set: `mov eax,[esi+0x380]` / `mov ecx,eax` / `shr ecx,8` / `test cl,1` /
	// `jne skip` / `or ah,0x1` / `mov [esi+0x380],eax`. Two facts pin the source:
	// the read-modify-write is on the WORD (a byte-view accessor collapses the
	// block to 195-216B because it drops the shared reload), and the OR is a 2-byte
	// in-place or on `ah` (an `int` shift of the word materialises
	// `or eax,0x100`, 5B, twice in this body).
	bool testWeaponBonusCondition(int bit) const
	{
		return (m_flags380 & (1 << (bit + 8))) != 0;
	}
	void setWeaponBonusCondition(int bit)
	{
		m_flags380 |= (1 << (bit + 8));
	}

	char m_pad00[0x254];
	BodyModule *m_body; // +0x254
	char m_pad258[0x380 - 0x258];
	UnsignedInt m_flags380; // +0x380
	char m_pad384[0x100];
};

struct Rva00481A9EInfo
{
	char m_pad00[0x0c];
	UnsignedInt m_extra; // +0x0c
	float m_f10; // +0x10
	char m_pad14[0x08];
	float m_f1c; // +0x1c
};

extern int g_Va00DBA4E4; // ?g_Va00DBA4E4@@3HA

class Rva0048180C
{
public:
	void rva00481A9E(Object *tgt, bool flag, Rva00481A9EInfo *info);

private:
	char m_pad00[0x08];
	Object *m_owner; // +0x08
	char m_pad0C[0x2c - 0x0c];
	const UpgradeTemplate *m_tmpl; // +0x2c
};

// ?rva00481A9E@Rva0048180C@@QAEXPAVObject@@_NPAURva00481A9EInfo@@@Z present-unmatched
void Rva0048180C::rva00481A9E(Object *tgt, bool flag, Rva00481A9EInfo *info)
{
	if (m_owner == 0)
		return;
	Player *pl = m_owner->getControllingPlayer();
	if (pl == 0)
		return;
	bool hasUpgrade;
	if (m_tmpl != 0)
		hasUpgrade = pl->rva002AB87D(m_tmpl);
	else
		hasUpgrade = false;
	if (flag) {
		if (((Rva0028ADECmpBoolField *)tgt)->get() == true) {
			if (tgt->testWeaponBonusCondition(0) == false)
				tgt->setWeaponBonusCondition(0);
			if (hasUpgrade) {
				if (tgt->testWeaponBonusCondition(7) == false)
					tgt->setWeaponBonusCondition(7);
			}
		}
		BodyModule *body = tgt->m_body;
		if (body == 0)
			return;
		float fsel;
		if (hasUpgrade)
			fsel = info->m_f1c;
		else
			fsel = info->m_f10;
		float mult = body->f6();
		// Retail ends the x87 chain with a single `fmulp st(1),st`, which pops both
		// operands; the operand order decides whether VC7 emits that pop-pair form
		// or `fmul st,st(1)` followed by a separate `fstp st(0)` to drop the
		// divisor. Only this order reaches the pop-pair form.
		tgt->rva0028FEA7(mult * (fsel / (float)g_Va00DBA4E4), m_owner, info->m_extra);
	} else {
		((unsigned char *)&tgt->m_flags380)[1] &= 0x7e;
	}
}
