// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva0010ED3D@Rva0010ED3D@@QAEXH@Z at 0x0010ED3D (15B).
// Conditional max setter at +0x3C: if (v > m_val3C) m_val3C = v.
// Evidence: retail mov eax [esp+4]; cmp eax [ecx+0x3C]; jle; mov [ecx+0x3C] eax; ret 4;
// callers at 0x000A7FCF 0x000A8064 in 0x000A7EFA.
#include "../../Include/Common/Rva0010EDC2Resource.h"
extern "C" __declspec(dllimport) void __stdcall AIL_mem_free_lock(void *memory);
void operator delete[](void *memory);
class Rva0010ED3D
{
public:
	void rva0010ED3D(int v);
private:
	char m_pad[0x3C];
	int m_val3C;
};

void Rva0010ED3D::rva0010ED3D(int v)
{
	if (v > m_val3C)
		m_val3C = v;
}

// Native 10EDC2..10EE29: complete 103-byte RET body. Observe counter34;
// release payload2C through Miles AIL_mem_free_lock (PE IAT BBABB4) or array delete 2FD80;
// clear it; destroy event4C explicitly, then event44 and name00 automatically.
// The entire body and associated EH data match, including cleanups 764806/76480E.
Rva0010EDC2::~Rva0010EDC2()
{
    count34;
    if (payload2C)
    {
        if (miles40)
            AIL_mem_free_lock(payload2C);
        else
            ::operator delete[](payload2C);
        payload2C = 0;
    }
    reinterpret_cast<Rva0040EDB *>(event4C)->Rva0040EDB::~Rva0040EDB();
}
