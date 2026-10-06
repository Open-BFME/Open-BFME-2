// cl: /DNDEBUG /MD
// ??0Rva00360474@@QAE@XZ, retail 0x00360474, 54 bytes.
// Ctor: base Rva001DBAA4, vtable 0x00816808, +4=30 +9=1 +0xC=0 +0x10=0
// +0x14=30 +0x28=0.0f +0x2C=-1 +0x30=0. Evidence: unlock lane, vtable store
// at [this], rowed base ctor 0x001DBAA4, caller 0x003604E8.

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	int m_C;
};

class Rva00360474 : public Rva001DBAA4
{
public:
	Rva00360474();
	virtual ~Rva00360474();

private:
	int m_10;
	int m_14;
	char m_pad[16];
	float m_28;
	int m_2c;
	int m_30;
};

Rva00360474::Rva00360474() : m_10(0), m_14(30), m_2c(-1)
{
	m_4 = 30;
	m_C = 0;
	m_28 = 0.0f;
	m_9 = true;
	m_30 = 0;
}

Rva00360474::~Rva00360474()
{
	m_C = 0;
	m_30 = 0;
}

// ??0Rva00360243@@QAE@XZ, retail 0x00360243, 57 bytes.
// Sibling of 0x00360474 with vtable 0x00816778 and one more member +0x34.
// Evidence: unlock lane, same base ctor 0x001DBAA4, caller 0x003602BA.
class Rva00360243 : public Rva001DBAA4
{
public:
	Rva00360243();

private:
	int m_10;
	int m_14;
	char m_pad[16];
	float m_28;
	int m_2c;
	int m_30;
	int m_34;
};

Rva00360243::Rva00360243() : m_10(0), m_14(30), m_2c(-1)
{
	m_4 = 30;
	m_C = 0;
	m_28 = 0.0f;
	m_9 = true;
	m_30 = 0;
	m_34 = 0;
}
