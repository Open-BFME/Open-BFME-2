// Donor1281192f68 game/GameEngine/Source/Common/Rva007B8190InitCtor.cpp; same blob as6d943.
// Native EFD4B/44 writes words0..2C and byte30, returns this; original type unknown.
// Complete standalone ABI body between neighboring ret4 and EFD77 entry.
// No direct call or aligned data xref found. Represent only the observed initializer
// and return-this behavior; do not assert the donor constructor role in target.
// cl: /O1 /G7 /arch:SSE2 /GX- /MD

class Rva000EFD4BInitializer
{
public:
	Rva000EFD4BInitializer *rva000EFD4B();

	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
	unsigned char m_30;
};

Rva000EFD4BInitializer *Rva000EFD4BInitializer::rva000EFD4B()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0c = 0xffffffff;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2c = 0;
	m_30 = 0;
	return this;
}
