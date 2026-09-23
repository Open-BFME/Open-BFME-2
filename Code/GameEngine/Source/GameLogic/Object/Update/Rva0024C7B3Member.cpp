// cl: /O1 /DNDEBUG /MD
//
// ??0Rva0024C7B3Member@@QAE@XZ, retail 0x0024C7B3, 20 bytes. Shared
// 0x1C-byte memset helper: it memsets this with 0 over 0x1C bytes through
// the CRT memset import thunk at 0x6291AE and returns this in eax, which is
// also the standard constructor epilogue. Six ModuleData ctor TUs
// (DemoTrap, StealthDetector, Missile, CrateCollide, PlayerHeal,
// GiantBirdSlowDeath) construct this member out of line through the pin,
// so this unit carries the byte-exact body and the row supersedes the pin.
// The address-derived name is honest: identity beyond the shared memset
// shape is not recovered, and no invented class name is claimed.

#pragma function(memset)

extern "C" void *memset(void *dst, int value, unsigned int size);

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

// ??0Rva0024C7B3Member@@QAE@XZ @0x24C7B3
Rva0024C7B3Member::Rva0024C7B3Member()
{
	memset(this, 0, 0x1C);
}
