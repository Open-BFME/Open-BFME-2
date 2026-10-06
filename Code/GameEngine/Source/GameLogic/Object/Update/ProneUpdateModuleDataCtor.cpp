// cl: /DNDEBUG /MD /EHsc

// ??0ProneUpdateModuleData@@QAE@XZ at retail 0x0049FEDF (16 bytes). The
// module-data half of ProneUpdate: vtable immediate 0x00C4ED70 modelled as an
// explicit first member (LifetimeUpdateModuleDataConstructor precedent, so no
// vtable is emitted and no dtor row is owed), an uninitialised word at +0x04
// retail never stores, and the single table-backed ratio at +0x08 (1.0f from
// the shared literal at 0x00BBB8D8). Field identity is retail's own one-entry
// INI table at 0x00C51964 joined to the Zero Hour ProneUpdate donor
// (DamageToFramesRatio, parseReal).
extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class ProneUpdateModuleData
{
public:
	ProneUpdateModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	float m_damageToFramesRatio;				// +0x08
};

ProneUpdateModuleData::ProneUpdateModuleData()
	: m_vtable( reinterpret_cast<const void *>(((unsigned int)vtbl_00C4ED70)) ),
	  m_damageToFramesRatio( 1.0f )
{
}
