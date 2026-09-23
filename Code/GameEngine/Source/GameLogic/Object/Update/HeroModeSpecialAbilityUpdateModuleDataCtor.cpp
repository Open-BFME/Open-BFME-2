// cl: /O1 /MD /DNDEBUG /EHsc
//
// ??0HeroModeSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x0049227B
// (90 bytes). EH ModuleData ctor over the pinned Rva0044EB54 intermediate
// base (0x0044EB54, size 0xC8): installs vtable 0x00C4DF58, zeroes the
// +0xC8 string member inline, sets it from the empty literal through the
// AsciiString set alias pin at 0x000055F5, then clears the +0xCC word and
// the +0xD0/+0xD1 flags. Two unwind states count the base and the member
// for the throwing set call. Donor: BFME1
// HeroModeSpecialAbilityUpdateModuleDataCtorThunk.cpp (same shape with a
// 0x250 base and the member at +0x254; BFME2 shrinks the base to 0xC8 with
// the member at +0xC8 and calls the one-arg set).

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void set(const char *text);
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();

private:
	unsigned char m_opaque[0xC4];
};

class HeroModeSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	HeroModeSpecialAbilityUpdateModuleData();

private:
	AsciiString m_stringC8;	// +0xC8
	int m_intCC;	// +0xCC
	bool m_flagD0;	// +0xD0
	bool m_flagD1;	// +0xD1
};

HeroModeSpecialAbilityUpdateModuleData::HeroModeSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	m_stringC8.set("");
	m_intCC = 0;
	m_flagD0 = false;
	m_flagD1 = false;
}
