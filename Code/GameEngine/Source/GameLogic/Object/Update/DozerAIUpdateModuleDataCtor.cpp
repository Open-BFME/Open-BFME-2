// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0DozerAIUpdateModuleData@@QAE@XZ, retail 0x00488A81, 36 bytes.
// ModuleData ctor over the pinned TransportAIUpdateModuleData base
// (0x26E5D7, 0x64 bytes per the SiegeAI row): installs vtable 0x00C4B6C8
// explicitly (novtable) and zeroes three floats at +0x64/+0x68/+0x6C via an
// xmm0-homed fzero local (/arch:SSE emits retail xorps+movss). Class size
// 0x70 proven by the DozerAIUpdate data factory (news 0x70, sole caller at
// 0x24CDD9). Row supersedes the ctor pin.

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

class __declspec(novtable) DozerAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	DozerAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x64/+0x68/+0x6C float zeros (end at the rowed 0x70 instance size).
	float m_64;
	float m_68;
	float m_6C;
};

// ??0DozerAIUpdateModuleData@@QAE@XZ @0x00488A81
DozerAIUpdateModuleData::DozerAIUpdateModuleData()
	: TransportAIUpdateModuleData()
{
	float fzero = 0.0f;
	*(unsigned int *)this = 0x00C4B6C8;
	m_64 = fzero;
	m_68 = fzero;
	m_6C = fzero;
}

// ?buildFieldParse@DozerAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x00488AA5
void DozerAIUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	TransportAIUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C4B748), 0);
}
