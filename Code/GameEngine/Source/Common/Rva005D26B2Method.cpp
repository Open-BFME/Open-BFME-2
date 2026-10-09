// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva005D26B2@Rva005D2664@@QAEXPBD@Z @0x005D26B2 268B: parse idx/name, alloc Rva005D2462, Set.
// Computes elem = this + (idx+1)*0x1C, checks [elem]==0, new 0x18 Rva005D2462
// from AfterLevel(name)/GetLevel(name) plus elem +4/+8, Set via rowed 0x00575674.
// Evidence: chain from 0x005D2505Get, retail inc/imul-0x1C/add, push-0x18/new,
// str()/AfterLevel/GetLevel order, callers none, siblings Rva005D2664Method.
// Row ??0Rva005D2462 declares (int int) but retail pushes &+4 &+8 addresses;
// declare the use as seen (addresses as ints) for byte truth.
#include "ascii_string.h"

bool __cdecl Rva005D2505Get(const char *params, int *out);
bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &out);
namespace AptUtils { const char *__cdecl SkipLevelN(const char *path); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }

class Object;

class Rva00575674
{
public:
	void rva00575674(Object *obj);
public:
	void *m_00;
	int m_04;
	int m_08;
	char m_pad0C[0x1C - 12];
};

class Rva005D2462
{
public:
	Rva005D2462(int level, const AsciiString &name, int a, int b);
private:
	char m_pad[0x18];
};

class Rva005D2664
{
public:
	void rva005D26B2(const char *params);
private:
	char m_header00[0x1C];
};

void Rva005D2664::rva005D26B2(const char *params)
{
	AsciiString name;
	Rva00575674 *elem;
	{
		int idx;
		if (!Rva005D2505Get(params, &idx) || !Rva004128F0GetParam(params, "name", name))
			return;
		elem = (Rva00575674 *)((char *)this + (idx + 1) * 0x1C);
		if (*(void **)elem)
			return;
	}
	elem->rva00575674((Object *)new Rva005D2462(AptUtils::LevelIndexFromTarget(name.str()), AsciiString(AptUtils::SkipLevelN(name.str())), (int)&elem->m_04, (int)&elem->m_08));
}

