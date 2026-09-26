// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
// ??1TerrainResourceBehaviorModuleData@@UAE@XZ @ 0x00482275 48B
// Implicit virtual dtor restoring base vtable 0x00BBB554 with no base call.
// Member at +0x18 via pinned 0x00360D26. Layout from ctor TU 0x0048202F
// (base 8 radius +8 maxIncome +0xC interval +0x10 highPri +0x14 visible +0x15
// pad +0x16 member +0x18). Vtable 0x00849440 slot 0 is ??_G 0x00482259.
// ShareExperienceBehaviorModuleDataDtor precedent.
class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
private:
	unsigned char m_data[4];
};
class TerrainResourceModuleDataBase
{
public:
	TerrainResourceModuleDataBase() {}
	virtual ~TerrainResourceModuleDataBase() {}
private:
	unsigned char m_pad[8 - 4];
};
class TerrainResourceBehaviorModuleData : public TerrainResourceModuleDataBase
{
public:
	TerrainResourceBehaviorModuleData();
// Implicit virtual dtor (never declared, never defined)
private:
	float m_radius;
	int m_maxIncome;
	int m_incomeInterval;
	bool m_highPriority;
	bool m_visible;
	unsigned char m_pad16[2];
	Rva003623E5Filter m_member18;
};
// ??0TerrainResourceBehaviorModuleData@@QAE@XZ present-unmatched
TerrainResourceBehaviorModuleData::TerrainResourceBehaviorModuleData()
{
}
void deleteTerrainResourceBehaviorModuleData(TerrainResourceBehaviorModuleData *p)
{
	delete p;
}
