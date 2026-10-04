// cl: /O1 /DNDEBUG /MD /GX
//
// PillageModuleData file-unit (parse + ctor).
//
// ?buildFieldParse@PillageModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x00253869, 33 bytes. Double-table parse proc (tables 0x00C6BB18
// and 0x00BF0620) through the rowed MultiIniFieldParse::add at 0x2BC6E.
// Row supersedes the parse pin (factory rowed at 0x25388A in
// UpdateModuleDataFriendNew.cpp; ModuleFactory registers it under
// "PillageModule").
//
// ??0PillageModuleData@@QAE@XZ, retail 0x00253830, 57 bytes.
// Pillage module data ctor: PillageAmount at +8 and NumDamageEventsPerPillage
// at +0xC clear, PillageFilter at +0x10 builds through the opaque 0x3623E5
// pin (Bloodthirsty precedent: Rva003623E5Member, 4 bytes, declared dtor).
// Table 0x00BF0620 proves the three fields at identical offsets; factory
// 0x25388A (news 0x14, sole caller) proves the class size. Row supersedes
// the ctor pin.

class MultiIniFieldParse;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	static void dup_002EF72(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
// Retail VA 0x00BF0620 (.rdata): 3 field records and a zero sentinel.
extern const FieldParse g_00BF0620[] = {
	{ "PillageAmount", &INI::dup_002EF72, 0, 0x8 },
	{ "NumDamageEventsPerPillage", &INI::dup_002EF72, 0, 0xC },
	{ "PillageFilter", &iniParseObjectFilter, 0, 0x10 },
	{ 0, 0, 0, 0 }
};
extern const int g_emptyFieldParseTable[4];

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

	unsigned char m_data[4];
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class PillageModuleData : public UpdateModuleData
{
public:
	PillageModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vtable (init-list store lands between the implicit base call
	// and the implicit member call per the GiantBird precedent).
	const void *m_vtable;
	// +0x04 unstored gap.
	unsigned int m_unused04;
	// +0x08 PillageAmount (table offset).
	int m_pillageAmount;
	// +0x0C NumDamageEventsPerPillage (table offset).
	int m_numDamageEvents;
	// +0x10 PillageFilter (table offset, via opaque 0x3623E5).
	Rva003623E5Member m_pillageFilter;
};

// ??0PillageModuleData@@QAE@XZ @0x00253830
PillageModuleData::PillageModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BF0568))
	, m_pillageAmount(0)
	, m_numDamageEvents(0)
{
}

// ?buildFieldParse@PillageModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00253869
void PillageModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
	parse.add(g_00BF0620, 0);
}
