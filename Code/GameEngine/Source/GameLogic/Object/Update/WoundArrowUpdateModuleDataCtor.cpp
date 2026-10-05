// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0WoundArrowUpdateModuleData@@QAE@XZ, retail 0x004C68C1, 41 bytes.
// ModuleData ctor over the pinned SpecialAbilityUpdateModuleData base (0x44EB54, 0xC8 bytes
// per the ToggleHidden row): loads the 100.0f cap (literal pool VA
// 0xBC292C; /arch:SSE emits retail movss), clears the +0xCC word (and-RMW,
// stays first per the ScaleWall precedent), installs vtable 0x00C5F778
// explicitly (novtable; shares the ToggleHidden vtable) and stores the cap
// at +0xC8. The float local sources the literal load ahead of the stores
// (Enraged precedent). Class size 0xD0 proven by the WoundArrowUpdate data
// factory (news 0xD0, sole caller at 0x252368). Row supersedes the ctor pin.

extern "C" const void *const vtbl_00C5F778[];  // folded, 3 classes; via ??_7EvacuateGarrisonSpecialPowerModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C5F778=??_7EvacuateGarrisonSpecialPowerModuleData@@6B@")

class MultiIniFieldParse;
struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class __declspec(novtable) SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();
	virtual ~SpecialAbilityUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vptr (novtable: no compiler install here).
	// Remainder is opaque (0xC4 bytes); only the 0xC8 size matters.
	unsigned char m_opaque[0xC4];
};

class __declspec(novtable) WoundArrowUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	WoundArrowUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0xC8 cap value.
	float m_capC8;
	// +0xCC cleared word (ends at the rowed 0xD0 instance size).
	unsigned int m_wordCC;
};

// ??0WoundArrowUpdateModuleData@@QAE@XZ @0x004C68C1
WoundArrowUpdateModuleData::WoundArrowUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	float cap = 100.0f;
	m_wordCC &= 0;
	*(unsigned int *)this = ((unsigned int)vtbl_00C5F778);
	m_capC8 = cap;
}

// ?buildFieldParse@WoundArrowUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x004C68EA
void WoundArrowUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	SpecialAbilityUpdateModuleData::buildFieldParse(parse);
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5DEAC), 0);
}
