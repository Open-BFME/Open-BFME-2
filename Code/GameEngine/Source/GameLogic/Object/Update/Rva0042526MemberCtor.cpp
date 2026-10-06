// cl: /MD /DNDEBUG
// ??0Rva0042526Member@@QAE@XZ retail 0x00042526 20 bytes.
// Opaque 76-byte bulk-zero member ctor (memset 0x4C through the rowed
// _memset): serves the +0xB4 condition member of GenericObjectCreationNugget
// and the +0x8 flags of ModelConditionSpecialAbilityUpdateModuleData. The
// CondStore-spelling alias pin at the same address stays for its TU; this row
// supersedes only the Rva-spelling pin.

#include <string.h>

class Rva0042526Member
{
public:
	Rva0042526Member();

private:
	unsigned char m_pad[0x4C];
};

// ??0Rva0042526Member@@QAE@XZ @0x00042526
Rva0042526Member::Rva0042526Member()
{
	memset(this, 0, 0x4C);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?init@CondStore@@QAEXXZ=??0Rva0042526Member@@QAE@XZ")
