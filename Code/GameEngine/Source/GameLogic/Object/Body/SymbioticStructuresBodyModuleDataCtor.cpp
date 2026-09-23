// cl: /O1 /MD /DNDEBUG /EHsc
//
// ??0SymbioticStructuresBodyModuleData@@QAE@XZ, retail 0x00256D0D (67 bytes).
// EH ModuleData ctor over the rowed ActiveBodyModuleData base (0x004BF59F,
// size 0x64): installs vtable 0x00BF3EE0, zeroes the +0x64 string member
// inline, and sets it from the "Not likely to duplicate this name, is he,
// Fred?" literal through the AsciiString set alias pin at 0x000055F5. Two
// unwind states count the base and the member for the throwing set call.
// Donor: BFME1 module_factory.cpp (ModuleFactory registers it under
// "SymbioticStructuresBody"; same inline-zero plus set shape as the
// HeroModeSpecialAbilityUpdateModuleData ctor).

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void set(const char *text);
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

class SymbioticStructuresBodyModuleData : public ActiveBodyModuleData
{
public:
	SymbioticStructuresBodyModuleData();

private:
	AsciiString m_string64;	// +0x64
};

SymbioticStructuresBodyModuleData::SymbioticStructuresBodyModuleData()
	: ActiveBodyModuleData()
{
	m_string64.set("Not likely to duplicate this name, is he, Fred?");
}
