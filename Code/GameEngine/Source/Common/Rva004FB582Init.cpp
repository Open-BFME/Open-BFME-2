// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FB582 (126B): channel-driven init. One-time init of the channel
// object at 0x00E04508 (its first byte is the done flag), three channel
// queries off the target's +0x14 field into +0x0C/+0x10/+0x14, then a
// by-value slot call on each of the +0x68/+0x74/+0x80 subobjects. All
// seven callees are pinned, not recovered; identities unproven.

class Rva0050366B
{
public:
	void rva0050366B();
};

class Rva00501DF1
{
public:
	int rva00501DF1(int v);
};

class Rva00501813
{
public:
	int rva00501813(int v);
};

class Rva00501844
{
public:
	int rva00501844(int v);
};

struct Rva004FB582Slot
{
	int m_a;	// +0x00
	int m_b;	// +0x04
};

class Rva003FA4DB
{
public:
	void rva003FA4DB(Rva004FB582Slot v);

public:
	Rva004FB582Slot m_slot;	// +0x00
};

class Rva002BF70F
{
public:
	void rva002BF70F(Rva004FB582Slot v);

public:
	Rva004FB582Slot m_slot;	// +0x00
};

class Rva005B129F
{
public:
	void rva005B129F(Rva004FB582Slot v);

public:
	Rva004FB582Slot m_slot;	// +0x00
};

struct Rva00E04508Channel
{
	unsigned char m_initialized;	// +0x00 done flag
};

Rva00E04508Channel g_Va00E04508;

struct Rva004FB582Target
{
	char m_pad[0x14];
	int val14;	// +0x14 queried field
};

class Rva004FB582Owner
{
public:
	void rva004FB582();

private:
	Rva004FB582Target *m_00;	// +0x00 (queried target)
	char m_pad04[8];		// +0x04..0x0B
	int m_0C;			// +0x0C
	int m_10;			// +0x10
	int m_14;			// +0x14
	char m_pad18[0x50];		// +0x18..0x67
	Rva003FA4DB m_68;		// +0x68
	char m_pad70[4];		// +0x70..0x73
	Rva002BF70F m_74;		// +0x74
	char m_pad7C[4];		// +0x7C..0x7F
	Rva005B129F m_80;		// +0x80
};

void Rva004FB582Owner::rva004FB582()
{
	Rva00E04508Channel *channel = &g_Va00E04508;
	if (!channel->m_initialized)
	{
		((Rva0050366B *)channel)->rva0050366B();
		channel->m_initialized = 1;
	}
	if (m_00)
	{
		m_0C = ((Rva00501DF1 *)channel)->rva00501DF1(m_00->val14);
		m_10 = ((Rva00501813 *)channel)->rva00501813(m_00->val14);
		m_14 = ((Rva00501844 *)channel)->rva00501844(m_00->val14);
	}
	m_68.rva003FA4DB(m_68.m_slot);
	m_74.rva002BF70F(m_74.m_slot);
	m_80.rva005B129F(m_80.m_slot);
}
