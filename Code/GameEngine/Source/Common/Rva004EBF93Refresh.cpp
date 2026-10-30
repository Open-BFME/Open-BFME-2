// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004EBF93@Rva004EBF93@@QAEXXZ @0x004EBF93 177B.
// Subsystem refresh from world flags: run the six rowed member sweeps
// (including AIWallBuilder::postInit 0x004E9F6E at +0xE4), then latch bytes from the
// +0x10 world block's flag bytes in retail order
// 848/849/84E/84A/84B/84C/84F. Member extents past each call site are
// spacing pads; only the call targets and flag offsets are proven.
class AIBaseBuilder
{
public:
	void postInit();
};

class AIEconomyBuilder
{
public:
	void postInit();
};

class AIWallBuilder
{
public:
	void postInit();
};

class Rva00598F24
{
public:
	void postInit();
};

class Rva00598CBC
{
public:
	void rva00598CBC();
};

class Rva002A8F24;
extern Rva002A8F24 *TheSkirmishAIManager;

struct Rva004EBF93World
{
	char m_pad[0x848];
	unsigned char m_848;
	unsigned char m_849;
	unsigned char m_84A;
	unsigned char m_84B;
	unsigned char m_84C;
	char m_pad84D;
	unsigned char m_84E;
	unsigned char m_84F;
};

struct Rva004EBF93M12C
{
	char m_pad[0x10];
	unsigned char m_10;
};

class Rva004EBF93
{
public:
	void rva004EBF93();
private:
	char m_pad00[4];
	AIBaseBuilder m_04;
	char m_pad05[0x08 - 0x05];
	unsigned char m_8;
	char m_pad09[0x38 - 0x09];
	Rva00598CBC m_38;
	char m_pad39[0x3C - 0x39];
	unsigned char m_3C;
	char m_pad3D[0x94 - 0x3D];
	unsigned char m_94;
	char m_pad95[0xB4 - 0x95];
	AIEconomyBuilder m_B4;
	char m_padB5[0xC4 - 0xB5];
	unsigned char m_C4;
	char m_padC5[0xE4 - 0xC5];
	AIWallBuilder m_E4;
	char m_padE5[0xE8 - 0xE5];
	unsigned char m_E8;
	char m_padE9[0xFC - 0xE9];
	Rva00598F24 m_FC;
	char m_padFD[0x10C - 0xFD];
	unsigned char m_10C;
	char m_pad10D[0x12C - 0x10D];
	AIEconomyBuilder *m_12C;
};

void Rva004EBF93::rva004EBF93()
{
	m_04.postInit();
	m_B4.postInit();
	m_E4.postInit();
	m_FC.postInit();
	m_38.rva00598CBC();
	m_12C->postInit();
	Rva004EBF93World *world = (Rva004EBF93World *)((char *)TheSkirmishAIManager + 0x10);
	if (world->m_848 != 0)
		m_8 = 1;
	if (world->m_849 != 0)
		m_C4 = 1;
	if (world->m_84E != 0)
		m_94 = 1;
	if (world->m_84A != 0)
		m_3C = 1;
	if (world->m_84B != 0)
		((Rva004EBF93M12C *)m_12C)->m_10 = 1;
	if (world->m_84C != 0)
		m_10C = 1;
	if (world->m_84F != 0)
		m_E8 = 1;
}
