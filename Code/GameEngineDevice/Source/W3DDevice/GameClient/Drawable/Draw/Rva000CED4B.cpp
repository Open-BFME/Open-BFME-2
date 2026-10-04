// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?Rva000CED4BUpdate@@YAXPAXPAVAssetList@@H@Z @0x000CED4B 150B: free update accumulating AssetLists and notifying via Rva001E11F8.
// Evidence: rowed Rva001E11F8 0x001E11F8 and StringBase isEmpty 0x00001E2F plus pinned AssetList operator<< and Rva002D06CA and notify.

#include "ascii_string.h"

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
};

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern Rva002D06CA *g_009FF000;

class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

struct Rva000CED4BArg
{
	char m_pad[8];
	AsciiString m_08;
	AsciiString m_0c;
	char m_pad10[0x10];
	Rva001E11F8 *m_20;
	Rva001E11F8 *m_24;
	AsciiString m_28;
	char m_pad2c[0x1C];
	AsciiString m_48;
	char m_pad4c[4];
	Rva001E11F8 *m_50;
};

void __cdecl Rva000CED4BUpdate(void *p, AssetList *b, int c)
{
	Rva000CED4BArg *a = (Rva000CED4BArg *)p;
	*b << a->m_08;
	*b << a->m_0c;
	if (a->m_20)
		a->m_20->rva001E11F8((int)b, c);
	if (a->m_24)
		a->m_24->rva001E11F8((int)b, c);
	if (((StringBase<char> *)&a->m_28)->isEmpty() == false)
		*b << a->m_28;
	if (((StringBase<char> *)&a->m_48)->isEmpty() == false) {
		void *t = g_009FF000->rva002D06CA(&a->m_48);
		if (t != 0)
			((Rva0020AA00Target *)t)->notify((int)b, c);
	}
	if (a->m_50)
		a->m_50->rva001E11F8((int)b, c);
}
