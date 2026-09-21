// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Identity: ModuleFactory registers this data class under "DetachableRiderBody" (addModule
// pairs the name with this factory); formerly misnamed ChinookAIUpdateModuleData.
//
// ??0DetachableRiderBodyModuleData@@QAE@XZ, retail 0x004C1E8B, 60 bytes.
//
// The module-data half of ChinookAIUpdate: the ActiveBodyModuleData
// base (opaque here -- its ctor is pinned at 0x4BF59F and its 0x64 bytes are
// untouched by this body, so the base is empty and the derived layout pads
// to +0x64), the vtable immediate 0x00BF4028 modelled as an explicit first
// member (ToppleUpdateModuleDataCtor precedent, so no vtable is emitted),
// the rope member at +0x64 constructed through the rowed
// Rva0025342CMember::construct (OpenContainModuleDataCtor row), the 1.0f
// globals at +0x174/+0x17C, and the flag byte at +0x178. Body order is
// load-bearing (Topple precedent: the byte precedes the 1.0f store so the
// scheduler keeps retail's load/byte/store shape); /GX matches the sibling
// factory TUs. The 0x180 news size comes from the rowed 0x251740 factory.

class ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_pad[0x110];
};

class DetachableRiderBodyModuleData : public ActiveBodyModuleData
{
public:
	DetachableRiderBodyModuleData();

private:
	const void *m_vtable;
	unsigned char m_pad[0x64 - 4];
	Rva0025342CMember m_ropes;		// +0x64
	float m_174;				// +0x174
	unsigned char m_178;			// +0x178
	unsigned char m_pad178[3];
	float m_17C;				// +0x17C
};

// ??0DetachableRiderBodyModuleData@@QAE@XZ
DetachableRiderBodyModuleData::DetachableRiderBodyModuleData()
	: m_vtable( reinterpret_cast<const void *>(0x00BF4028) )
{
	m_ropes.construct();
	m_17C = 0.0f;
	m_178 = 0;
	m_174 = 1.0f;
}
