// cl: /DNDEBUG /MD /EHsc

// ??0OCLUpdateModuleData@@QAE@XZ at retail 0x0049B355 (26 bytes). The
// module-data half of OCLUpdate: vtable immediate 0x00C4ED70 modelled as an
// explicit first member (LifetimeUpdateModuleDataConstructor precedent, so no
// vtable is emitted and no dtor row is owed), an uninitialised word at +0x04
// retail never stores, the table-backed fields at +0x08/+0x0C/+0x10 (zeroed
// through one shared xor-ed ecx) plus the BFME2-only amount at +0x14 and the
// edge flag byte at +0x18. Field names and offsets are retail's own INI table
// at 0x00C50BA8 joined to the debug path beside it
// (...\Object\Update\OCLUpdate.cpp): OCL, MinDelay, MaxDelay, CreateAtEdge,
// Amount. Body order is load-bearing: `m_amount |= -1` emits retail's
// leading `or [eax+0x14],-1` (a plain `= -1` compiles to a trailing 7-byte
// mov), and /O1 is what keeps the independent or above the xor.
extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class OCLUpdateModuleData
{
public:
	OCLUpdateModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	unsigned int m_ocl;					// +0x08
	unsigned int m_minDelay;				// +0x0C
	unsigned int m_maxDelay;				// +0x10
	int m_amount;					// +0x14
	bool m_isCreateAtEdge;				// +0x18
};

OCLUpdateModuleData::OCLUpdateModuleData()
{
	m_amount |= -1;
	m_vtable = reinterpret_cast<const void *>(((unsigned int)vtbl_00C4ED70));
	m_ocl = 0;
	m_minDelay = 0;
	m_maxDelay = 0;
	m_isCreateAtEdge = false;
}
