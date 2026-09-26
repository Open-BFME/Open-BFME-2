// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??1EvacuateDamageModuleData@@UAE@XZ @ 0x004BAD91 48B
// Implicit virtual dtor restoring Snapshot base vtable 0x00BBB554 with no
// base call. Member evacuation-weapon string at +0x08 via 0x00036410.
// Layout from ctor TU 0x004BAD10 (pad +4 string +0x08). Vtable 0x00859CF8
// slot 0 is ??_G 0x004BAD75. ShareExperienceBehaviorModuleDataDtor precedent.
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
private:
	void *m_data;
};
class EvacuateDamageModuleDataBase
{
public:
	virtual ~EvacuateDamageModuleDataBase() {}
};
class EvacuateDamageModuleData : public EvacuateDamageModuleDataBase
{
public:
	EvacuateDamageModuleData();
// Implicit virtual dtor (never declared, never defined)
private:
	unsigned char m_unk04[4];
	AsciiString m_weapon;
};
// ??0EvacuateDamageModuleData@@QAE@XZ present-unmatched
EvacuateDamageModuleData::EvacuateDamageModuleData()
{
}
void deleteEvacuateDamageModuleData(EvacuateDamageModuleData *p)
{
	delete p;
}
