// cl: /DNDEBUG /MD
//
// Dump range 1 (0x00066A9A 55B): head calls plus dual guarded tail.
// Head calls the pinned 0x00077F80 on this, then the pinned 0x0007E89C
// through the retail global at 0x00DE2000 when non-null. Tail reuses the
// proven 0x680B3 pattern: +0x3850 call plus +0x3854 tail jmp into pinned
// 0x000EA1F3/0x000E6FC8. Honest address-derived names.

extern void *W3DGCData00DE2000;

class Rva00066A9ASub
{
public:
	void headB();
	void tailA();
	void tailB();
};

class Rva00066A9AHost
{
public:
	void rva00066A9A();
	void headA();

	char m_pad[0x3850];
	Rva00066A9ASub *m_3850; // +0x3850
	Rva00066A9ASub *m_3854; // +0x3854
};

void Rva00066A9AHost::rva00066A9A()
{
	headA();
	Rva00066A9ASub *g = (Rva00066A9ASub *)W3DGCData00DE2000;
	if (g)
		g->headB();
	if (m_3850)
		m_3850->tailA();
	if (m_3854)
		m_3854->tailB();
}

// W3DShaderManager::init in GeneralsMD walks the master shader and filter
// lists. Retail's 0x77F80 does the same, then creates the Glow declaration and
// loads its vertex and pixel shaders. The two list roots and shader handles
// below are target addresses; the caller-proven method name remains headA.
class Rva00077F80Shader
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual int init();
};

class Rva00077F80Filter
{
public:
	virtual int init();
};

struct Rva00077F80VertexElement
{
	unsigned short stream;
	unsigned short offset;
	unsigned char type;
	unsigned char method;
	unsigned char usage;
	unsigned char usageIndex;
};

extern Rva00077F80Shader **g_Va00DB43A4[];
extern Rva00077F80Filter **g_Va00DB43AC[];

struct IDirect3DDevice8;
class DX8Wrapper
{
protected:
	friend void Rva00066A9AHost::headA();
	static IDirect3DDevice8 *D3DDevice;
};

struct ShaderComResourceRef;
class W3DShaderManager
{
	friend void Rva00066A9AHost::headA();
	protected:
	static ShaderComResourceRef *m_resource012F9D14;
	static ShaderComResourceRef *m_resource012F9D18;
};

struct Rva00077F80Device;
struct Rva00077F80DeviceVtbl
{
	void *reserved[0x158 / 4];
	long (__stdcall *createVertexShader)(Rva00077F80Device *device,
		const Rva00077F80VertexElement *declaration, unsigned *shader);
};

struct Rva00077F80Device
{
	Rva00077F80DeviceVtbl *vtable;
};

extern unsigned g_fvfShader;
extern void __cdecl Rva00075E42Init();
extern void __cdecl Rva000754DEInit();
extern long __cdecl Rva00077C19Load(const char *path, unsigned *shader);
extern long __cdecl Rva00077D0FLoad(const char *path, unsigned long *shader);

void Rva00066A9AHost::headA()
{
	Rva00075E42Init();
	Rva000754DEInit();

	int i, j;
	Rva00077F80Shader **shaders;
	for (i = 0; g_Va00DB43A4[i] != 0; ++i) {
		shaders = g_Va00DB43A4[i];
		for (j = 0; shaders[j] != 0; ++j) {
			if (shaders[j]->init())
				break;
		}
	}

	Rva00077F80Filter **filters;
	for (i = 0; g_Va00DB43AC[i] != 0; ++i) {
		filters = g_Va00DB43AC[i];
		for (j = 0; filters[j] != 0; ++j) {
			if (filters[j]->init())
				break;
		}
	}

	Rva00077F80VertexElement declaration[4] = {
		{ 0, 0, 3, 0, 0, 0 },
		{ 0, 16, 4, 0, 10, 0 },
		{ 0, 20, 1, 0, 5, 0 },
		{ 0xFF, 0, 17, 0, 0, 0 }
	};
	if (g_fvfShader == 0) {
		Rva00077F80Device *device =
			(Rva00077F80Device *)DX8Wrapper::D3DDevice;
		long hr = device->vtable->createVertexShader(
			device, declaration, &g_fvfShader);
		if (hr < 0)
			g_fvfShader = 0;
	}

	if (Rva00077C19Load("shaders\\Glow.vso",
		(unsigned *)&W3DShaderManager::m_resource012F9D18) < 0)
		W3DShaderManager::m_resource012F9D18 = 0;

	if (Rva00077D0FLoad("shaders\\Glow.pso",
		(unsigned long *)&W3DShaderManager::m_resource012F9D14) < 0)
		W3DShaderManager::m_resource012F9D14 = 0;
}
