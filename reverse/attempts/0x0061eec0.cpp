// ?bfmeBumpURB@BfmeThingURB@@QAEXXZ
// partial score=0.7 date=2026-09-22
// cl: /O1 /DNDEBUG /MD
//
// ?bfmeBumpURB@BfmeThingURB@@QAEXXZ,
// retail 0x0061EEC0, 24 bytes. Dedicated TU.
// Bumps the resource-enumerator sequence at +0x30 and captures it at +0x10.
// The global at VA 0x00E09C0C is DIR32-masked, so any extern reproduces the
// shape; the rowed bfmeGoURB caller in BfmeConv1341.cpp stays green via the
// row.

class BfmeResourceEnumerator
{
public:
	char m_pad[0x30];
	int m_nextId;
};

extern BfmeResourceEnumerator *TheResourceEnumerator;

class BfmeThingURB
{
public:
	char m_pad[4];
	int m_flags;
	char m_mid[8];
	int m_bumpId;

	void bfmeBumpURB();
};

// ?bfmeBumpURB@BfmeThingURB@@QAEXXZ
void BfmeThingURB::bfmeBumpURB()
{
	BfmeResourceEnumerator *reg = TheResourceEnumerator;
	if (reg)
	{
		int nextId = reg->m_nextId + 1;
		m_bumpId = nextId;
		reg->m_nextId = nextId;
	}
}
