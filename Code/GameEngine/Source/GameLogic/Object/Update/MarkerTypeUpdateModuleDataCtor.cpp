// cl: /O1 /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "RadarMarkerClientUpdate" (addModule
// pairs the name with this factory); formerly misnamed MarkerTypeUpdateModuleData.
//
// ??0RadarMarkerClientUpdateModuleData@@QAE@XZ, retail 0x004C9C98, 13 bytes.
//
// The module-data half of MarkerType: the ModuleData base carries the vtable
// immediate 0x00C5EDF8 (inline base ctor, so no vtable is emitted and no dtor
// row is owed) plus the tag key at +0x04 retail never stores, and the derived
// dword at +0x08 is the MarkerType INI field (table 0x00C5ED98, single entry
// "MarkerType" at offset +0x08) zeroed in the body. Class identity is the
// rowed RadarMarkerClientUpdateModuleData::buildFieldParse proc pushed by the rowed
// 0x252B11 factory, whose sole call to this address is the pin this row
// supersedes. Frameless leaf; the factory's 0x0C news size fits vptr plus tag
// plus the +0x08 word.
//
// Load-bearing: the zero store selects the short AND form under /O1, and the
// scheduler hoists AND-mem above MOV-mem in every spelling (base-init, body,
// init-list, explicit &=, MI, virtual — all probed AND-first). The
// _ReadWriteBarrier intrinsic (zero bytes, BFME2NativeNetworkBaseConstruct
// precedent) pins the vtable MOV ahead of the AND. Retail order is
// mov-eax-ecx, mov-[eax]-vtable, and-[eax+8]-0, ret.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class ModuleData
{
public:
	ModuleData() : m_vtable( reinterpret_cast<const void *>(0x00C5EDF8) ) {}

protected:
	const void *m_vtable;			// +0x00
	unsigned int m_moduleTagNameKey;	// +0x04
};

class RadarMarkerClientUpdateModuleData : public ModuleData
{
public:
	RadarMarkerClientUpdateModuleData();

private:
	int m_markerType;			// +0x08, INI field "MarkerType"
};

// ??0RadarMarkerClientUpdateModuleData@@QAE@XZ
RadarMarkerClientUpdateModuleData::RadarMarkerClientUpdateModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C5EDF8);
	_ReadWriteBarrier();
	m_markerType = 0;
}
