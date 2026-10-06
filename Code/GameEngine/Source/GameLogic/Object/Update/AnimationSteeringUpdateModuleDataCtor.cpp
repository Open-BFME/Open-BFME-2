// cl: /DNDEBUG /MD /EHsc
// Identity: ModuleFactory registers this data class under "CivilianSpawnCollide" (addModule
// pairs the name with its factory); formerly misnamed AnimationSteeringUpdate/AnimationSteeringUpdateModuleData.
//
// ??0CivilianSpawnCollideModuleData@@QAE@XZ, retail 0x004BD651 (50 bytes).
// BFME1 donor: Code/GameEngine/Source/GameLogic/Object/Update/
// CivilianSpawnCollide.cpp (`m_transitionFrames = 0`, 25 bytes).
// BFME2 installs its vtable then constructs the +0x08 member through the
// opaque 0x3623E5 pin (a 0x94-frame SEH body whose identity is unproven;
// the pin claims only the address) and returns this with no other stores.
// The +0x08 displacement proves a member (or second base) rather than the
// primary base: the primary base contributes only the vptr plus the tag word
// (the BFME1 ModuleData shape), patched from retail like all vtable installs.
// Identity proof: reloc-named by the ModuleFactory call site; the B8+E8 head
// is the function's own __EH_prolog (scope 0xB8F889), not a shared fragment.

extern "C" const void *const vtbl_00C5AAB8[];
#pragma comment(linker, "/alternatename:_vtbl_00C5AAB8=??_7CivilianSpawnCollideModuleData@@6B@")

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	char m_data[16];
};

class ModuleDataBase
{
public:
	ModuleDataBase() {}
	~ModuleDataBase();
};

class CivilianSpawnCollideModuleData : public ModuleDataBase
{
public:
	CivilianSpawnCollideModuleData();

private:
	const void *m_vtable; // +0, retail 0x00C5AAB8
	int m_tag; // +4, untouched padding
	Rva003623E5Member m_updateMember; // +0x08
};

// ??0CivilianSpawnCollideModuleData@@QAE@XZ
CivilianSpawnCollideModuleData::CivilianSpawnCollideModuleData()
	: ModuleDataBase()
	, m_vtable(reinterpret_cast<const void *>(((unsigned int)vtbl_00C5AAB8)))
{
}
