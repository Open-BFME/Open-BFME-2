// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch F. As in VslotSmallBodiesA-E, each class and method
// is address-derived and models only what its body touches; the comment above
// each gives the .rdata slot address(es) that reference it. Meanings are not
// recovered.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

// slot at VA 0x00C5CC3C: with an argument, hands its +0x38 block and the
// second argument to this object's vslot 12.
struct Rva004C31ECArg
{
	char m_pad00[0x38];
	char m_38[4];
};
class Rva004C31EC
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
	virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
	virtual void vslot06(); virtual void vslot07(); virtual void vslot08();
	virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(void *block, Int value);
	void rva004C31EC(Rva004C31ECArg *arg, Int value);
};
void Rva004C31EC::rva004C31EC(Rva004C31ECArg *arg, Int value)
{
	if (arg)
		vslot12(arg->m_38, value);
}

// slots at VA 0x00BC662C and 0x00C0883C: stores both arguments at +0x04 and
// +0x08.
class Rva004CEE7F
{
public:
	void rva004CEE7F(Int a, Int b);
private:
	char m_pad00[0x04];
	Int m_04;
	Int m_08;
};
void Rva004CEE7F::rva004CEE7F(Int a, Int b)
{
	m_04 = a;
	m_08 = b;
}

// slot at VA 0x00C63230: steps the +0x08 counter up or down.
class Rva004F5391
{
public:
	void rva004F5391(Bool up);
private:
	char m_pad00[0x08];
	Int m_08;
};
void Rva004F5391::rva004F5391(Bool up)
{
	if (up)
		m_08++;
	else
		m_08--;
}

// slot at VA 0x00C66FDC: sets the +0x27C state to 3 once the +0x284 byte is
// set, else sets the byte.
class Rva0051BF2D
{
public:
	void rva0051BF2D();
private:
	char m_pad00[0x27C];
	Int m_27C;
	char m_pad280[0x284 - 0x280];
	Bool m_284;
};
void Rva0051BF2D::rva0051BF2D()
{
	Bool *flag = &m_284;
	if (*flag)
		m_27C = 3;
	else
		*flag = true;
}

// slot at VA 0x00C67F14: a sixteen-entry table of 0x18-byte records at
// +0x48; stamps every record's +0x00 with the +0x10 object's +0x10 value
// and clears its +0x16 byte.
struct Rva0052586BSource
{
	char m_pad00[0x10];
	Int m_10;
};
struct Rva0052586BRecord
{
	Int m_00;
	char m_pad04[0x16 - 0x04];
	Bool m_16;
	char m_pad17;
};
class Rva0052586B
{
public:
	void rva0052586B();
private:
	char m_pad00[0x10];
	Rva0052586BSource *m_10;
	char m_pad14[0x48 - 0x14];
	Rva0052586BRecord m_records[16];
};
void Rva0052586B::rva0052586B()
{
	for (Int i = 0; i < 16; ++i)
	{
		m_records[i].m_00 = m_10->m_10;
		m_records[i].m_16 = false;
	}
}
// slot at VA 0x00C6808C: moves the +0x0C state from 3 to 4, setting +0x14 to 5.
class Rva005277BA
{
public:
	void rva005277BA();
private:
	char m_pad00[0x0C];
	Int m_0C;
	char m_pad10[0x14 - 0x10];
	Int m_14;
};
void Rva005277BA::rva005277BA()
{
	if (m_0C == 3)
	{
		m_14 = 5;
		m_0C = 4;
	}
}

// slot at VA 0x00C6A13C: true once TheGameLogic's frame reaches +0x04; the
// argument is unused.
class Rva00545B72
{
public:
	Bool rva00545B72(Int unused);
private:
	char m_pad00[0x04];
	UnsignedInt m_04;
};
Bool Rva00545B72::rva00545B72(Int unused)
{
	if (TheGameLogic->getFrame() < m_04)
		return false;
	return true;
}

// slots at VA 0x00C6CEC8 and 0x00C6CEEC: a function-local static id taken
// from the running counter at VA 0x00DFEE18 on first use (the same counter
// as VslotSmallBodiesD's 0x0029B1EA).
extern int g_00DFEE18;
class Rva00567793
{
public:
	Int rva00567793();
};
Int Rva00567793::rva00567793()
{
	static Int s_id = g_00DFEE18++;
	return s_id;
}

// ?GetAssociatedMessageType@@YAHH@Z, retail 0x00567700 (32 bytes).
// WorldBuilder 0x01430A50 names this helper in
// InGameToggleStanceCommandButton.cpp:95. Its caller at retail 0x005682BD
// pushes CommandButton::getStance's result and uses the returned message.
// The retail table at RVA 0x0086CE8C is exactly these three eight-byte
// stance/message records: (1,149), (2,147), (3,148). The 0..3 unsigned scan,
// success return and missing-stance zero return all byte-match; no data pin.
struct StanceMessageEntry { int stance; int message; };
static const StanceMessageEntry stanceMessages[3] = {{1,149},{2,147},{3,148}};
int GetAssociatedMessageType(int stance)
{
    for (unsigned int i = 0; i < 3; ++i)
        if (stanceMessages[i].stance == stance)
            return stanceMessages[i].message;
    return 0;
}

