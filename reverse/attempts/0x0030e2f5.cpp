// ?rva0030E2F5@Rva0030E2ECFlags@@QAEXXZ
// partial score=1.0 date=2026-10-10
// Dependency bank only. BF1 575ba Common/S3FlagForwarders.cpp supplied
// the bit-clear/set purpose; target30E2EC/30E2F5 independently proves raw
// word44 and a same-ECX/no-stack-argument tail to30DEAE. Original class,
// flag meaning and application method names remain unknown.
// The actual body30DEAE is unrowed and cannot currently link.
struct BfmeNodeEYE { void bfmeRunEYE(); };
class Rva0030E2ECFlags {
public:
 void rva0030E2EC();
 void rva0030E2F5();
private:
 char prefix[0x44];
 unsigned int word44;
};
void Rva0030E2ECFlags::rva0030E2EC() {
 word44 &= ~0x10U;
 ((BfmeNodeEYE *)this)->bfmeRunEYE();
}
void Rva0030E2ECFlags::rva0030E2F5() {
 word44 |= 0x10U;
 ((BfmeNodeEYE *)this)->bfmeRunEYE();
}
