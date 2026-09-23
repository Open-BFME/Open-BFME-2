// cl: /O1 /DNDEBUG /MD /GX
//
// FadeAndDieOrnamentUpdateModuleData file-unit (parse first; the ctor
// remains pinned for a follow-up).
//
// ?buildFieldParse@FadeAndDieOrnamentUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0025438C, 17 bytes. Single-table parse proc (table 0x00BF2358)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.
//
// ??0FadeAndDieOrnamentUpdateModuleData@@QAE@XZ, retail 0x002555AC,
// 85 bytes. MD ctor: vtable 0x00BF3740 plus AttachToTargetBone string at
// +0x08 (inline-zero plus clear through the rowed 0x36410 fold, Topple
// precedent) plus Envelope OrnamentData at +0x0C (implicit default ctor
// plus declared-only dtor arming EH state 1 plus explicit init through
// the pinned 0xC9251 leaf, then and-zero of the +0x0C/+0x24 dwords) plus
// FollowTarget at +0x34 set to true. The empty UpdateModuleData base
// (inline-empty ctor plus declared-only dtor) advances EH state 0 with no
// emitted code (Topple precedent). Field identity is the own table at
// 0x00BF2358 (AttachToTargetBone at +0x08, Envelope at +0x0C,
// FollowTarget at +0x34). The rowed factory at 0x255601 news 0x38.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();

private:
	void *m_data;
};

struct OrnamentData
{
	void init();
	~OrnamentData();

	unsigned char m_pad[0x0C];
	int m_inner0C;
	unsigned char m_pad10[0x14];
	int m_inner24;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class FadeAndDieOrnamentUpdateModuleData : public UpdateModuleData
{
public:
	FadeAndDieOrnamentUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	const void *m_vtable;
	unsigned int m_unused04;
	AsciiString m_attachToTargetBone; // +0x08
	OrnamentData m_envelope; // +0x0C
	bool m_followTarget; // +0x34
};

// ?buildFieldParse@FadeAndDieOrnamentUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0025438C
void FadeAndDieOrnamentUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BF2358), 0);
}

// ??0FadeAndDieOrnamentUpdateModuleData@@QAE@XZ @0x002555AC
FadeAndDieOrnamentUpdateModuleData::FadeAndDieOrnamentUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BF3740))
	, m_attachToTargetBone()
{
	OrnamentData *envelope = &m_envelope;
	envelope->init();
	envelope->m_inner0C &= 0;
	envelope->m_inner24 &= 0;
	m_attachToTargetBone.clear();
	m_followTarget = true;
}
