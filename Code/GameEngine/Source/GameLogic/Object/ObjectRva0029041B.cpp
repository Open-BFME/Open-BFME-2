// cl: /O1 /DNDEBUG /MD
// Object player-gated condition-bit pair at 0x0029041B / 0x00290496.
// ?rva0029041B@Object@@QAEXPAVPlayer@@@Z retail 0x0029041B 123B sets condition
// bit 138 for the controlling player and ?rva00290496@Object@@QAEXPAVPlayer@@@Z
// retail 0x00290496 70B clears it; both then notify the +0x250 provider's slot
// 31 target. The early-out tests of bits 186 and 301 read the word and shift
// (mov/shr/test al,1): written as a generic bool bit test, as retail's inline
// bit-flag test does, cl keeps that shape instead of a memory byte test.
// Evidence: neighbours ?rva002903EF@Object (0x002903EF) and ?rva0029091E@Object
// (0x0029091E); rowed callee ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ at
// 0x0028AFA9; pinned callee ?rva0028AE6D@Object@@QAEXXZ at 0x0028AE6D; 0x00290496
// callers 0x0023CA8E 0x00377C90 0x00377D00.
class Player;

class Rva0029041B_04
{
public:
	char m_pad[0x108];
	unsigned char m_flag108;
};

class Rva0029041BTarget
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
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
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
	virtual void v53(Player *p);
	virtual void v54(Player *p);
};

class Rva0029041BProvider
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void w20();
	virtual void w21();
	virtual void w22();
	virtual void w23();
	virtual void w24();
	virtual void w25();
	virtual void w26();
	virtual void w27();
	virtual void w28();
	virtual void w29();
	virtual void w30();
	virtual Rva0029041BTarget *w31();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva0028AE6D();
	void rva0029041B(Player *p);
	void rva00290496(Player *p);
	char m_pad00[4];
	Rva0029041B_04 *m_04;
	char m_pad08[0x110 - 0x8];
	class CondBits
	{
	public:
		unsigned int test(int bit) const
		{
			return m_words[bit >> 5] & (1U << (bit & 0x1f));
		}
		void set(int bit)
		{
			m_words[bit >> 5] |= 1U << (bit & 0x1f);
		}
		void clear(int bit)
		{
			m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
		}
		bool testBit(int bit) const
		{
			return ((m_words[bit >> 5] >> (bit & 0x1f)) & 1) != 0;
		}
		int get186() const
		{
			return testBit(186);
		}
		int get301() const
		{
			return testBit(301);
		}
		unsigned int m_words[10];
	} m_cond110;
	char m_pad138[0x250 - 0x138];
	Rva0029041BProvider *m_250;
};

static __forceinline void rva0029041BSetCondition(Object *object, int bit)
{
	if (object->m_cond110.test(bit) == 0)
	{
		object->m_cond110.set(bit);
		object->rva0028AE6D();
	}
}

void Object::rva0029041B(Player *player)
{
	if ((m_04->m_flag108 & 0x80) != 0)
		return;
	if (m_cond110.get186() != 0)
		return;
	if (m_cond110.get301() != 0)
		return;
	Rva0029041BTarget *target = 0;
	Rva0029041BProvider *prov = m_250;
	if (prov != 0)
		target = prov->w31();
	Player *ctrl = getControllingPlayer();
	if (player == ctrl)
	{
		rva0029041BSetCondition(this, 138);
	}
	if (target != 0)
		target->v53(player);
}

static __forceinline void rva00290496ClearCondition(Object *object, int bit)
{
	if (object->m_cond110.test(bit) != 0)
	{
		object->m_cond110.clear(bit);
		object->rva0028AE6D();
	}
}

// ?rva00290496@Object@@QAEXPAVPlayer@@@Z retail 0x00290496 70B: the clearing
// twin of 0x0029041B. When the player is the controlling one, condition bit
// 138 (+0x120 bit 10) is cleared through rva0028AE6D; then the +0x250
// provider's slot 31 target, if any, is told through its slot 54 (tail jump).
void Object::rva00290496(Player *player)
{
	if (player == getControllingPlayer())
		rva00290496ClearCondition(this, 138);
	Rva0029041BProvider *prov = m_250;
	if (prov == 0)
		return;
	Rva0029041BTarget *target = prov->w31();
	if (target == 0)
		return;
	target->v54(player);
}
