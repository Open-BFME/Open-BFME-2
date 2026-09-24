// cl: /O2 /DNDEBUG /MD
//
// ?Rva00120720CreateTexture@@YAPAXHHHHHH@Z, retail
// 0x00120720 (137 bytes). Cdecl D3DX texture creator behind the backend
// worker (sole caller 0x131170): builds the texture into a stack temp,
// maps the backend usage into a D3DX usage (1 stays 1; 0x200 survives
// unless the pool is 1; anything else passes through), then returns the
// temp, logging nonzero HRESULTs and returning NULL on failure without a
// log on the usage-1 path. Callees are the D3DXCreateTexture import plus
// the rowed Log_DX8_ErrorCode; the device comes from the 0xDEDA34 global.

extern "C" long __stdcall D3DXCreateTexture(
	void *device, unsigned width, unsigned height, unsigned mipLevels,
	unsigned long usage, int format, int pool, void **texture);

void Log_DX8_ErrorCode(unsigned code);

extern void *g_bfmeD3DDevice8;

// ?Rva00120720CreateTexture@@YAPAXHHHHHH@Z @0x120720
void *Rva00120720CreateTexture(
	int width, int height, int format, int mipLevels, int pool, int usage)
{
	void *texture = 0;
	long result;
	if (usage == 1) {
		result = D3DXCreateTexture(
			g_bfmeD3DDevice8, width, height, mipLevels, 1,
			format, pool, &texture);
		if (result < 0)
			return 0;
	} else {
		if (pool == 1 && usage == 0x200)
			usage = 0;
		result = D3DXCreateTexture(
			g_bfmeD3DDevice8, width, height, mipLevels, usage,
			format, pool, &texture);
	}
	if (result != 0)
		Log_DX8_ErrorCode(result);
	return texture;
}
