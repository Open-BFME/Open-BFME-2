// cl: /O1 /DNDEBUG /MD
// Native RVA0x0010BA2C /25B: address-derived resource-owner constructor.
// The previous VictoryConditions identity is refuted by target evidence:
// factory0x10BB11 allocates0x118 and reuses owners through+0x114; the separate
// donor-designated VictoryConditions creator0x41DFB allocates0xC4 and calls4CDCD.
// Constructor and destructor0x1092B9 install the same tableVA0xBCF9E0:
// deleting wrapper0x10BA45; common0xB3FD0; manager forwarder0x109DA6.
// The next words are -3.2/+3.2 floats. Neither108895 nor10BA61 is a table slot.
// Forwarder109DA6 reaches the graphics resource manager; destructor releases
// retained objects at+0x68/+0x70 then restores base tableBCEFA0.
// Native direct calls prove the rowed base ctorF0F2B and ordinary no-arg
// member108895 ABI. Full original class name/extent remain unknown.
// Minimal receiver view; no inherited semantic name or invented virtual slots.
class Rva000F0F2B
{
public:
    Rva000F0F2B();
};
extern const void *const g_00BCF9E0[];
class Rva0010BA2COwner : public Rva000F0F2B
{
public:
    Rva0010BA2COwner();
    void rva00108895();
};
Rva0010BA2COwner::Rva0010BA2COwner()
{
    *(const void *const **)this = g_00BCF9E0;
    rva00108895();
}
