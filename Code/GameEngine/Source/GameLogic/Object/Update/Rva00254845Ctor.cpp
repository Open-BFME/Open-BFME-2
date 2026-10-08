// cl: /MD /GX /DNDEBUG
//
// ??0Rva00254845@@QAE@XZ, retail 0x00254845, 18 bytes.
// Frameless ctor over the rowed OpenContain base (0x253487) at offset 0: calls
// the base ctor, then stores folded vtable 0x00BF2558 at +0. No own members.
extern "C" const void *const vtbl_00BF2558[];  // ??_7WeaponSetUpgradeModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BF2558=??_7WeaponSetUpgradeModuleData@@6B@")

class Rva00253487Base
{
public:
	Rva00253487Base();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class Rva00254845 : public Rva00253487Base
{
public:
	Rva00254845();
};

Rva00254845::Rva00254845()
{
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00BF2558));
}
