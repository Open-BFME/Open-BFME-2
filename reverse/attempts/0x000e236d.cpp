// ?bind@Rva000E236DBinder@@UAEXPBD0PAVRva0015354E@@@Z
// partial score=0.99 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// 0x000E236D, 156B: sub-binder slot 1 of vtable 0x007CE4D0, class identity derived from the terrain FX binder's member/vtable relationship. The packet confirms its base call, parser, strings, callback targets and registry call. Function intent is binding the three shroud parameters; dispatcher naming is address-derived.
// ?bind@Rva000E236DBinder@@UAEXPBD0PAVRva0015354E@@@Z

typedef const char *D3DXHANDLE;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

void __cdecl Rva001530E9Parse(const char *name, void *volatile path);
void __cdecl Rva000E24C5ShroudTexture(void *, D3DXHANDLE);
void __cdecl Rva000E2409ScaleOffset(void *, D3DXHANDLE);
void __cdecl Rva000E249DObjectShroudStatus(void *, D3DXHANDLE);

struct Rva001530E9Path
{
	char m_name[0x48];
	const char *m_rest;
};

typedef void (*Rva000E236DCallback)(void *, D3DXHANDLE);

struct TreeHintRef00217D4C
{
	explicit TreeHintRef00217D4C(const Rva000E236DCallback *callback);
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C();
	void *m_ptr;
};

class Rva0015354E
{
public:
	void rva00153ACA(TreeHintRef00217D4C callback, const char *handle);
};

class Base
{
public:
	virtual ~Base() {}
	virtual void bind(const char *name, const char *handle, Rva0015354E *registry) = 0;
};

class Rva00153664 : public Base
{
public:
	~Rva00153664() {}
	virtual void bind(const char *name, const char *handle, Rva0015354E *registry);
};

struct Rva000E236DBinder : public Rva00153664
{
	~Rva000E236DBinder() {}
	virtual void bind(const char *name, const char *handle, Rva0015354E *registry);
};

void Rva000E236DBinder::bind(const char *name, const char *handle, Rva0015354E *registry)
{
	Rva00153664::bind(name, handle, registry);
	if (name)
	{
		Rva000E236DCallback callback;
		Rva001530E9Path path;
		Rva001530E9Parse(name, &path);
		if (_strcmpi(path.m_name, "Texture") == 0)
		{
			callback = Rva000E24C5ShroudTexture;
			registry->rva00153ACA(TreeHintRef00217D4C(&callback), handle);
		}
		else if (_strcmpi(path.m_name, "ScaleUV_OffsetUV") == 0)
		{
			callback = Rva000E2409ScaleOffset;
			registry->rva00153ACA(TreeHintRef00217D4C(&callback), handle);
		}
		else if (_strcmpi(path.m_name, "ObjectShroudStatus") == 0)
		{
			callback = Rva000E249DObjectShroudStatus;
			registry->rva00153ACA(TreeHintRef00217D4C(&callback), handle);
		}
	}
}
