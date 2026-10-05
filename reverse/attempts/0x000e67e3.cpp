// ?Rva000E67E3Dispatch@@YGXPBD0PAX@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /EHsc /MD /arch:SSE
// ?Rva000E67E3Dispatch@@YGXPBD0PAX@Z, retail 0x000E67E3, 149 bytes.
// Dispatcher parsing property name via rowed Rva001530E9Parse then strcmpi
// chain for BaseTexture IsAlphaBlendEnabled SwayOffsets; builds rowed
// Rva00080221 temp from handler code address and calls rowed
// rva00153ACA with original value. Evidence: callees rowed; strings at
// 0x007CE5A0 0x007CEAA0 0x007CEA94; vtable slot 1 of 0x007CEA04.
void __cdecl Rva001530E9Parse(const char *src, void *volatile dstRaw);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

class Rva00080221
{
public:
	Rva00080221(const int *arg);
};

struct TreeHintRef00217D4C
{
	void *m_ptr;
};

class Rva0015354E
{
public:
	void rva00153ACA(TreeHintRef00217D4C arg, const char *name);
};

struct Rva000E67E3Parts
{
	char m_name[64];
	bool m_hasStar;
	bool m_hasBracket;
	char m_pad[2];
	int m_index;
	const char *m_ext;
};

// ?Rva000E67E3Dispatch@@YGXPBD0PAX@Z present-unmatched
void __stdcall Rva000E67E3Dispatch(const char *prop, const char *value, void *storeRaw)
{
	Rva0015354E *store = (Rva0015354E *)storeRaw;
	Rva000E67E3Parts parts;
	const char *saved;
	Rva001530E9Parse(prop, (void *)&parts);
	if (_strcmpi(parts.m_name, "BaseTexture") == 0)
	{
		saved = value;
		value = (const char *)0x004E69E6;
		store->rva00153ACA(*(const TreeHintRef00217D4C *)&Rva00080221((const int *)&value), saved);
		return;
	}
	if (_strcmpi(parts.m_name, "IsAlphaBlendEnabled") == 0)
	{
		saved = value;
		value = (const char *)0x004E6878;
		store->rva00153ACA(*(const TreeHintRef00217D4C *)&Rva00080221((const int *)&value), saved);
		return;
	}
	if (_strcmpi(parts.m_name, "SwayOffsets") == 0)
	{
		if (parts.m_hasBracket && parts.m_index != 0)
			return;
		saved = value;
		value = (const char *)0x004E68C5;
		store->rva00153ACA(*(const TreeHintRef00217D4C *)&Rva00080221((const int *)&value), saved);
		return;
	}
}
