extern void *g_bfmeVftTQD[];
extern int vftable_01129D30;

class BfmeSinkTQD
{
public:
	virtual void bfmeV0TQD(void) = 0;
	virtual void bfmeV1TQD(void) = 0;
	virtual void bfmeV2TQD(void) = 0;
	virtual void bfmeDropTQD(void *item, int flags) = 0;
};

BfmeSinkTQD *bfmeGetTQD(void);
void bfmeFreeTQD(void *place, int size);

class BfmeThingTQD
{
public:
	BfmeThingTQD();
	void *bfmeDelTQD(unsigned char flags);
	void *m_bfmeVft;
	void *m_bfmeField4;
	unsigned int m_bfmeField8;
	void *m_bfmeItem;
	unsigned int m_bfmeField10;
};

// Retail 0x006587C0 installs the same vftable address as the matched
// BfmeThingTQD::bfmeDelTQD at 0x006587E0. That destructor reads +0xC and frees
// a 0x14-byte object, independently supporting this class and the field
// extent. The opaque +4 pointer and +8/+10 fields follow only the target
// constructor bytes. BFME1 revision a38d345e79e3bfa4417212ffa37d53ca1ccae65f
// at b1 0x007EB850 is an ICF-tied lead, not the source of these target
// identities.
//
// Retail 0x006587C0 (27 bytes); target extent is bracketed by int3 padding.
BfmeThingTQD::BfmeThingTQD()
{
	m_bfmeVft = &vftable_01129D30;
	m_bfmeField4 = reinterpret_cast<void *>(0x00A587B0);
	m_bfmeField8 = 0;
	m_bfmeItem = 0;
	m_bfmeField10 = 0;
}

// ?bfmeDelTQD@BfmeThingTQD@@QAEPAXE@Z
void *BfmeThingTQD::bfmeDelTQD(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftTQD;
	bfmeGetTQD()->bfmeDropTQD(m_bfmeItem, 0);
	if (flags & 1)
		bfmeFreeTQD(this, 0x14);
	return this;
}
// ?g_bfmeVftTQD@@3PAPAXA: the global at VA 0xce157c is ?vftable_01129D30@@3HA.
#pragma comment(linker, "/alternatename:?g_bfmeVftTQD@@3PAPAXA=?vftable_01129D30@@3HA")
