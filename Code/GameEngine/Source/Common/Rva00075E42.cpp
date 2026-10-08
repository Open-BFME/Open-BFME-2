// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva00075E42@@YAXXZ @ 0x00075E42 (2023B).
// Target evidence: the body memoizes a nonzero dword at 0x009E1F58, takes
// the DX8 thread lock, queries the pointer at 0x009EDA30, reads adapter vendor
// and device IDs at offsets 0x428/0x42C, then writes a chipset enum value to
// the memoized dword. If no vendor/device row matches, it queries a 0x130-byte
// capability record and classifies its pixel-shader version at offset 0xCC.
// The lock object's scope is inferred from the EH state plus matched lock and
// unlock callees. BFME1's W3DShaderManager::getChipset is a semantic lead only:
// its target-side ID sets and fallback differ, so no donor name is assigned.

#include <string.h>

extern int g_Va001FDE58;
extern void __cdecl BFME_DX8_Thread_Lock(void);
extern bool __cdecl BFME_DX8_Thread_Assert(void);

struct IDirect3D8;

class DX8Wrapper
{
	friend void rva00075E42(void);

	// The existing DX8Wrapper definition declares this protected static data
	// member; preserve its owner and type in the local view.
	protected:
	static IDirect3D8 *D3DInterface;
};

struct Rva00075E42D3D8Vtable
{
	void *m_slots00To04[5];
	long (__stdcall *m_getAdapterIdentifier)(IDirect3D8 *, unsigned, unsigned, void *);
	void *m_slots06To13[8];
	long (__stdcall *m_slot14)(IDirect3D8 *, unsigned, unsigned, void *);
};

struct IDirect3D8
{
public:
	Rva00075E42D3D8Vtable *m_vtable;
};

struct Rva00075E42DeviceLock
{
	Rva00075E42DeviceLock() { BFME_DX8_Thread_Lock(); }
	~Rva00075E42DeviceLock() { BFME_DX8_Thread_Assert(); }
};

void rva00075E42(void)
{
	if (g_Va001FDE58 != 0)
		return;

	Rva00075E42DeviceLock lock;
	IDirect3D8 *interface8 = DX8Wrapper::D3DInterface;
	if (interface8 == 0)
		return;

	unsigned char adapterIdentifier[0x44C];
	memset(adapterIdentifier, 0, sizeof(adapterIdentifier));
	interface8->m_vtable->m_getAdapterIdentifier(interface8, 0, 0, adapterIdentifier);
	unsigned vendor = *(unsigned *)(adapterIdentifier + 0x428);
	unsigned device = *(unsigned *)(adapterIdentifier + 0x42C);

	if (vendor == 0x10DE)
	{
		if (device >= 0x200 && device <= 0x203)
		{
			g_Va001FDE58 = 3;
			goto unlock;
		}
		if ((device >= 0x250 && device <= 0x253) ||
			(device >= 0x258 && device <= 0x25B) ||
			(device >= 0x280 && device <= 0x282) ||
			(device >= 0x288 && device <= 0x289))
		{
			g_Va001FDE58 = 6;
			goto unlock;
		}
		if ((device >= 0x321 && device <= 0x323) || device == 0x327 ||
			device == 0x326 || device == 0x314 || device == 0x0FC ||
			(device >= 0x32A && device <= 0x32B) || device == 0x33F)
		{
			g_Va001FDE58 = 2;
			goto checkCaps;
		}
		if ((device >= 0x311 && device <= 0x312) ||
			(device >= 0x342 && device <= 0x344) || device == 0x0FA ||
			(device >= 0x308 && device <= 0x309) || device == 0x338 ||
			device == 0x34E || (device >= 0x0FD && device <= 0x0FE))
		{
			g_Va001FDE58 = 7;
			goto unlock;
		}
		if ((device >= 0x301 && device <= 0x302) || device == 0x341 ||
			(device >= 0x330 && device <= 0x334) || device == 0x0FB)
		{
			g_Va001FDE58 = 0x0B;
			goto unlock;
		}
		if (device == 0x14F || (device >= 0x160 && device <= 0x165) ||
			device == 0x221 || (device >= 0x240 && device <= 0x242) ||
			(device >= 0x0F3 && device <= 0x0F4) || device == 0x14E)
		{
			g_Va001FDE58 = 8;
			goto unlock;
		}
		if ((device >= 0x141 && device <= 0x145) || device == 0x0F2 ||
			device == 0x0CE)
		{
			g_Va001FDE58 = 0x0E;
			goto unlock;
		}
		if (device == 0x140 || device == 0x0F1 ||
			(device >= 0x040 && device <= 0x048) ||
			(device >= 0x0C1 && device <= 0x0C3) ||
			(device >= 0x211 && device <= 0x215) || device == 0x0F9 ||
			device == 0x04E || device == 0x0CD || device == 0x0F8)
		{
			g_Va001FDE58 = 0x17;
			goto unlock;
		}
		if ((device >= 0x091 && device <= 0x092) || device == 0x09D)
		{
			g_Va001FDE58 = 0x1A;
			goto unlock;
		}
	}
	else if (vendor == 0x1002)
	{
		if (device == 0x514C || device == 0x4242 || device == 0x4966 ||
			device == 0x496E || device == 0x514D || device == 0x5834 ||
			device == 0x5854 || device == 0x5874 || device == 0x5974 ||
			device == 0x5940 || device == 0x5941 ||
			(device >= 0x5954 && device <= 0x5955) ||
			(device >= 0x5960 && device <= 0x5964) ||
			(device >= 0x5A41 && device <= 0x5A43) ||
			(device >= 0x5A61 && device <= 0x5A63) ||
			device == 0x5C41 || device == 0x5C61 || device == 0x5D44 ||
			device == 0x7834)
		{
			g_Va001FDE58 = 5;
			goto checkCaps;
		}
		else if ((device >= 0x4144 && device <= 0x4146) ||
			(device >= 0x4164 && device <= 0x4166) ||
			(device >= 0x4150 && device <= 0x4155) ||
			(device >= 0x4170 && device <= 0x4175) ||
			device == 0x4E51 || device == 0x4E71)
		{
			g_Va001FDE58 = 0x0C;
			goto unlock;
		}
		else if (device == 0x4E44 || device == 0x4E64)
		{
			g_Va001FDE58 = 0x10;
			goto unlock;
		}
		else if (device == 0x4148 || device == 0x4168 ||
			(device >= 0x4E48 && device <= 0x4E4A) ||
			(device >= 0x4E68 && device <= 0x4E6A))
		{
			g_Va001FDE58 = 0x12;
			goto unlock;
		}
		else if (device == 0x5B60 || device == 0x5B70)
		{
			g_Va001FDE58 = 0x0D;
			goto unlock;
		}
		else if (device == 0x3E50 || device == 0x3E70 || device == 0x5B62 ||
			device == 0x5B63 || device == 0x5B72 || device == 0x5B73 ||
			device == 0x5E4B || device == 0x5E4D || device == 0x5E6B ||
			device == 0x5E6D || device == 0x5E4F || device == 0x5E6F)
		{
			g_Va001FDE58 = 0x11;
			goto unlock;
		}
		else if ((device >= 0x4A49 && device <= 0x4A4B) || device == 0x4A50 ||
			device == 0x4A54 || (device >= 0x4A69 && device <= 0x4A6B) ||
			device == 0x4A70 || device == 0x4A74 ||
			(device >= 0x4B49 && device <= 0x4B4C) ||
			(device >= 0x4B69 && device <= 0x4B6C) ||
			(device >= 0x5549 && device <= 0x554F) ||
			(device >= 0x5569 && device <= 0x556F) || device == 0x5D4D ||
			device == 0x5D4F || device == 0x5D52 || device == 0x5D57 ||
			device == 0x5D6D || device == 0x5D6F || device == 0x5D72 ||
			device == 0x5D77)
		{
			g_Va001FDE58 = 0x15;
			goto unlock;
		}
		else if (device == 0x7142 || device == 0x7146 || device == 0x7162 ||
			device == 0x7166)
		{
			g_Va001FDE58 = 0x0F;
			goto unlock;
		}
		else if (device == 0x71C0 || device == 0x71C2 || device == 0x71E0 ||
			device == 0x71E2)
		{
			g_Va001FDE58 = 0x14;
			goto unlock;
		}
		else if (device == 0x7100 || device == 0x7109 || device == 0x7120 ||
			device == 0x7129)
		{
			g_Va001FDE58 = 0x19;
			goto unlock;
		}
	}
	else if (vendor == 0x8086)
	{
		g_Va001FDE58 = 1;
		goto checkCaps;
	}

checkCaps:
	if (*(volatile int *)&g_Va001FDE58 == 0)
	{
		unsigned char deviceCaps[0x130];
		memset(deviceCaps, 0, sizeof(deviceCaps));
		interface8->m_vtable->m_slot14(interface8, 0, 1, deviceCaps);
		int pixelShaderVersion = *(int *)(deviceCaps + 0xCC) & 0xFFFF;
		if (pixelShaderVersion >= 0x101)
			g_Va001FDE58 = 1;
		if (pixelShaderVersion >= 0x200)
			g_Va001FDE58 = 0x0A;
		if (pixelShaderVersion >= 0x300)
			g_Va001FDE58 = 0x16;
	}

unlock:
	return;
}
