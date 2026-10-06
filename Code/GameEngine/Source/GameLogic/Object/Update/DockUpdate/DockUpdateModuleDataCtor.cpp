// cl: /DNDEBUG /MD
//
// ??0DockUpdateModuleData@@QAE@XZ,
// retail 0x005896B0, 17 bytes. Dedicated TU.
// Frameless base ctor shared by SupplyWarehouseDock, SupplyCenterDock and
// MonsterDock file-units: folded vtable 0xC4ED70 plus and-zero at +8 plus
// byte 1 at +0xC. Non-virtual with an explicit leading vtable member so no
// vtable is emitted; source order matches retail (and first, no barrier).

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class DockUpdateModuleData
{
public:
	DockUpdateModuleData();

private:
	void *m_vtable;
	int m_unused04;
	int m_08;
	unsigned char m_0C;
};

// ??0DockUpdateModuleData@@QAE@XZ
DockUpdateModuleData::DockUpdateModuleData()
{
	m_08 = 0;
	m_vtable = (void *)((unsigned int)vtbl_00C4ED70);
	m_0C = 1;
}
