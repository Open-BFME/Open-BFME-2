// cl: /O1 /DNDEBUG /MD
//
// ??0DockUpdateModuleData@@QAE@XZ,
// retail 0x005896B0, 17 bytes. Dedicated TU.
// Frameless base ctor shared by SupplyWarehouseDock, SupplyCenterDock and
// MonsterDock file-units: folded vtable 0xC4ED70 plus and-zero at +8 plus
// byte 1 at +0xC. Non-virtual with an explicit leading vtable member so no
// vtable is emitted; source order matches retail (and first, no barrier).

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
	m_vtable = (void *)0xC4ED70;
	m_0C = 1;
}
