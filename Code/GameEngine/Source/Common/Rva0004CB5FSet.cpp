// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0004CB5FSet@@YAXH@Z @0x0004CB5F 20B
// Null-guarded dispatch to ParticleSystemManager (0x00DFDD04) slot 0x44.
// Evidence: global TheParticleSystemManager per INI_parseParticleSystemTemplate;
// virtual slot 17; caller 0x000E3713; unblocks 0x000E2FBD.
class ParticleSystemManager002B
{
public:
	virtual void dummy00() = 0;
	virtual void dummy01() = 0;
	virtual void dummy02() = 0;
	virtual void dummy03() = 0;
	virtual void dummy04() = 0;
	virtual void dummy05() = 0;
	virtual void dummy06() = 0;
	virtual void dummy07() = 0;
	virtual void dummy08() = 0;
	virtual void dummy09() = 0;
	virtual void dummy10() = 0;
	virtual void dummy11() = 0;
	virtual void dummy12() = 0;
	virtual void dummy13() = 0;
	virtual void dummy14() = 0;
	virtual void dummy15() = 0;
	virtual void dummy16() = 0;
	virtual void rva0004CB5FSlot44(int arg) = 0;
};

// ?TheParticleSystemManager@@3PAVParticleSystemManager002B@@A: the global at this VA is ?TheParticleSystemManager@@3PAVParticleSystemManager@@A; this name is an alias for it.
extern ParticleSystemManager002B * TheParticleSystemManager;
#pragma comment(linker, "/alternatename:?TheParticleSystemManager@@3PAVParticleSystemManager002B@@A=?TheParticleSystemManager@@3PAVParticleSystemManager@@A")

void __cdecl Rva0004CB5FSet(int arg)
{
	if (TheParticleSystemManager != 0)
		TheParticleSystemManager->rva0004CB5FSlot44(arg);
}
