// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// Rva0049D1B1 (vtable 0xC5146C): 0x50-byte polymorphic class in the
// ProductionUpdate cluster. Identity unproven, so the class carries an
// opaque Rva name after its dtor address (Rva0049188D-family precedent).
//
// Evidence:
// - Ctor 0x0049D162 (79B, ghidra FUN_0089d162) installs vtable 0xC5146C and
//   zeroes +0x04..+0x4C with +0x10=1 and float zeroes at +0x14/+0x18
//   (xorps+movss, hence /arch:SSE). Pure stores, no calls.
// - Dtor 0x0049D1B1 (25B, ghidra FUN_0089d1b1) reinstalls the vtable, zeroes
//   +0x38/+0x48/+0x4C and tail-jumps the folded AsciiString dtor at
//   0x0036410 for the member at +0x40. Frameless, no EH, so the member
//   teardown is the nothrow throw() spelling.
// - ??_G 0x0049D84B (28B, abuts 0x0049D867) is vtable slot0; it calls the
//   dtor and the rowed scalar delete at 0x002FD60.
// - The vtable existing at slot0 proves a virtual dtor (UAE letter).
// - Callers allocate 0x54 via 0x002FDA0 at 0x49D912 (inside vtable slot6
//   0x49D867), 0x49DB22 (inside slot11 0x49DA34) and 0x49FB17; the 0x49FB17
//   owner links nodes through +0x48/+0x4C. Slot9 0x49CDF9 reads the +0x04
//   discriminator (==2 arm), which the 0x49D867 owner stores after
//   constructing. Upgrade-flavored callees (calcCostToBuild,
//   bfmeCanAffordUpgrade) in the 0x49D867 owner.

class AsciiString
{
public:
	~AsciiString() throw();

	void *m_data;
};

class Rva0049D1B1
{
public:
	Rva0049D1B1();
	virtual ~Rva0049D1B1();

private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	float m_14;
	float m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	unsigned char m_34;
	int m_38;
	int m_3C;
	AsciiString m_name; // +0x40
	unsigned char m_44;
	int m_48;
	int m_4C;
};

// ??0Rva0049D1B1@@QAE@XZ @0x0049D162
Rva0049D1B1::Rva0049D1B1()
{
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 1;
	m_14 = 0.0f;
	m_18 = 0.0f;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_name.m_data = 0;
	m_44 = 0;
	m_48 = 0;
	m_4C = 0;
}

// ??1Rva0049D1B1@@UAE@XZ @0x0049D1B1
Rva0049D1B1::~Rva0049D1B1()
{
	m_48 = 0;
	m_4C = 0;
	m_38 = 0;
}

// ??_GRva0049D1B1@@UAEPAXI@Z @0x0049D84B (28 bytes, vtable slot0; boundary
// proven by the ret at 0x0049D866 plus the ??_G prologue). Emitted by the
// delete helper (ProductionModifierEntry precedent); the dtor and
// operator-delete calls resolve through the row and the 0x002FD60 pin.
void deleteRva0049D1B1(Rva0049D1B1 *entry) { delete entry; }
