// cl: /O1 /DNDEBUG /MD
//
// ??0SiegeAIUpdateModuleData@@QAE@XZ, retail 0x004904D9, 18 bytes.
// ModuleData ctor over the pinned TransportAIUpdateModuleData base
// (0x26E5D7): installs vtable 0x00C4B6C8 explicitly (novtable; no new
// members initialized here). Class size 0x64 proven by the SiegeAIUpdate
// data factory (news 0x64, sole caller at 0x24D4EC). Row supersedes the
// ctor pin.

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class __declspec(novtable) TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0x60 bytes); only the 0x64 size matters.
	unsigned char m_opaque[0x60];
};

class __declspec(novtable) SiegeAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	SiegeAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ??0SiegeAIUpdateModuleData@@QAE@XZ @0x004904D9
SiegeAIUpdateModuleData::SiegeAIUpdateModuleData()
	: TransportAIUpdateModuleData()
{
	*(unsigned int *)this = 0x00C4B6C8;
}

// ?buildFieldParse@SiegeAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004904EB
void SiegeAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C6BB18), 0);
}
