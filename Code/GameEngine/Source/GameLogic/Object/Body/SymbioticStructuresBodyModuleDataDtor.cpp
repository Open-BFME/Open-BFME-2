// cl: /O1 /MD /DNDEBUG /EHsc
//
// ??1SymbioticStructuresBodyModuleData@@UAE@XZ, retail 0x002570F9, 53 bytes.
// Virtual dtor over vtable 0x007F3EE0 (slot 0 deleting dtor at 0x002570DD
// calls this body). Destroys the +0x64 string through the pinned teardown
// at 0x00036410 then calls the rowed ActiveBodyModuleData base dtor at
// 0x00256CB0. Layout from the rowed ctor TU at 0x00256D0D (base 0x64 via
// 0x004BF59F vtable 0xBF3EE0 string +0x64 via set 0x55F5). Shape follows
// the ctor (novtable base plus derived string) with the base call
// untracked (or-minus1) exactly as retail.
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();
	virtual ~ActiveBodyModuleData();

private:
	unsigned char m_opaque[0x64 - 4];
};

class __declspec(novtable) SymbioticStructuresBodyModuleData : public ActiveBodyModuleData
{
public:
	virtual ~SymbioticStructuresBodyModuleData();

private:
	AsciiString m_string64; // +0x64
};

SymbioticStructuresBodyModuleData::~SymbioticStructuresBodyModuleData()
{
}
