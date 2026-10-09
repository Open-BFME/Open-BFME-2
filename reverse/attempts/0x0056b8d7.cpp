// ?rva0056B8D7@LivingWorldArmyIconSubObject@@QAE_NXZ
// partial score=0.85 date=2026-10-10
// cl: /MD
// ?rva0056B89F@LivingWorldArmyIconSubObject@@QAEEXZ @0x0056B89F 56B: predicate over +0xbc index and +0xac inner (+0x58 mask +0x5e flag) with +0xc0 flag, tail-jmps to Rva005C41C9::rva005C4B26. Evidence: caller 0x0056BA07 passes result to Rva005C4B56::rva005C4B96(E), tail target pin ?rva005C4B26@Rva005C41C9@@QAEEXZ, neighbour Rva0056B8F4 // cl: /O1 /Oy- /MD and Rva005C4180Refresh v17 shape.
struct Inner0056B89F
{
	char _00[0x58];
	int m_58;
	char _5C[2];
	unsigned char m_5E;
};

class Rva005C41C9
{
public:
	unsigned char rva005C4B26();
};

// The +0xC4 object: slot 10 (+0x28) answers a bool; +0x38 points at a
// record whose +0x54 is an index.
struct Record0056B88A
{
	char _00[0x54];
	int m_54;
};

class Target0056B8D7
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09();
	virtual bool s10();
	char _04[0x34];
	Record0056B88A *m_38;
};

struct Holder0056B8D7
{
	Target0056B8D7 *m_ptr;
};

class LivingWorldArmyIconSubObject;

// The visitor handed to vtable slots 1 and 2 (0x0086D810): each calls back
// with the icon.
class Visitor0056B984
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void visit4(LivingWorldArmyIconSubObject *icon);
	virtual void visit5(LivingWorldArmyIconSubObject *icon);
};

class LivingWorldArmyIconSubObject
{
private:
	char _00[0xAC];
	Inner0056B89F *m_ac;
	char _B0[0x0C];
	int m_bc;
	unsigned char m_c0;
	Holder0056B8D7 m_c4;
public:
	unsigned char rva0056B89F();
	int rva0056B88A();
	bool rva0056B8D7();
	void rva0056B984(Visitor0056B984 *visitor);
	void rva0056B993(Visitor0056B984 *visitor);
};

// @0x0056B88A 21B, vtable slot 16: the +0xC4 object's record index, or -1.
int LivingWorldArmyIconSubObject::rva0056B88A()
{
	Record0056B88A *record = m_c4.m_ptr->m_38;
	if (record)
		return record->m_54;
	return -1;
}

// @0x0056B8D7 29B, vtable slot 13: true unless the +0xC4 object exists and
// its slot 10 answers true.
bool LivingWorldArmyIconSubObject::rva0056B8D7()
{
	if (m_c4.m_ptr)
		return !m_c4.m_ptr->s10();
	return true;
}

// @0x0056B984 15B and @0x0056B993 15B, vtable slots 2 and 1.
void LivingWorldArmyIconSubObject::rva0056B984(Visitor0056B984 *visitor)
{
	visitor->visit5(this);
}

void LivingWorldArmyIconSubObject::rva0056B993(Visitor0056B984 *visitor)
{
	visitor->visit4(this);
}

unsigned char LivingWorldArmyIconSubObject::rva0056B89F()
{
	int idx = m_bc;
	if (idx == -1)
		return 0;
	Inner0056B89F *inner = m_ac;
	if ((inner->m_58 & (1 << idx)) == 0)
		return 0;
	if (inner->m_5E == 0 || m_c0 != 0)
		return ((Rva005C41C9 *)this)->rva005C4B26();
	return 0;
}
