// cl: /O2 /Ob2
// ?rva00903C20DeviceQuery@@YA_NXZ @ 0x0011CC30 (36B): reads the DX8 device global
// at 0x00DEDA34 (inlined DX8Wrapper::_Get_D3D_Device8), calls vtable slot 70
// (offset 0x118) with an out-parameter, and returns whether the result was 0.
// Name is donor-derived from WW3D2 Rva00903C20DeviceQuery.cpp and is NOT proven
// by target evidence; the slot-70 interface is unidentified.
struct Rva00903C20Device;
struct Rva00903C20Vtable
{
	void *m_prior[70];
	long (__stdcall *m_slot70)(Rva00903C20Device *, unsigned *);
};
struct Rva00903C20Device
{
	Rva00903C20Vtable *m_vtable;
};

extern int g_Va00DEDA34;
// ?g_Va00DEDA34@@3HA: the global at VA 0xdeda34 is ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A.
#pragma comment(linker, "/alternatename:?g_Va00DEDA34@@3HA=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")

bool rva00903C20DeviceQuery()
{
	unsigned result = 0;
	Rva00903C20Device *device = reinterpret_cast<Rva00903C20Device *>(g_Va00DEDA34);
	return device->m_vtable->m_slot70(device, &result) == 0;
}
