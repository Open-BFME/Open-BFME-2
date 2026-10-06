// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?rva005C3C0B@Rva005C3C0B@@QAEXPBD@Z @0x005C3C0B 340B.
// Callback parses index/name and fills an empty 12-byte record. The stored
// callback address and field offsets are target evidence; member meanings and
// class identity remain structural inferences from those uses.
#include "ascii_string.h"

#include <stdlib.h>

bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &out);
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

class Object;

class Rva00575674
{
public:
	void rva00575674(Object *obj);
	void *m_00;
	int m_04;
	int m_08;
};

class Rva005C3975
{
public:
	Rva005C3975(int owner, int level, const AsciiString &name);
	char m_pad[0x14];
};

class Rva005C3C0B
{
public:
	void rva005C3C0B(const char *params);

private:
	char m_pad00[0x1c];
	int m_count;
	char m_records[12];
};

void Rva005C3C0B::rva005C3C0B(const char *params)
{
	AsciiString index;
	if (!Rva004128F0GetParam(params, "index", index))
		return;
	int indexValue = atoi(index.str());
	if (indexValue < 0 || indexValue >= m_count)
		return;
	char *record = (char *)this + 0x20 + indexValue * 0xc;
	Rva00575674 *elem = (Rva00575674 *)(record + 4);
	if (elem->m_00 || !*(void **)record)
		return;
	AsciiString name;
	if (!Rva004128F0GetParam(params, "name", name))
		return;
	elem->rva00575674((Object *)new Rva005C3975((int)this, Rva004128BBGetLevel(name.str()),
		AsciiString(Rva00412845AfterLevel(name.str()))));
}
