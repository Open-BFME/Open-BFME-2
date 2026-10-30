// cl: /O1 /Oi /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ?rva002E6451@Rva002E6451@@QAEPAXPBD@Z @0x002E6451 74B: StringLookUp equal_range lookup via 0x002E6329 forwarder over count at +0 and base at +8 returns info+4 or 0
#include <memory.h>

void *__cdecl rva002E6329(void *, void *, void *, void *, void *) throw();

class AsciiString;
struct StringLookUp
{
public:
	AsciiString *label; // +0x00
	void *info; // +0x04
};

class Rva002E6451
{
public:
	void *rva002E6451(const char *label);
private:
	int m_count; // +0x00
	char m_pad04[0x4];
	StringLookUp *m_items; // +0x08
};

void *Rva002E6451::rva002E6451(const char *key)
{
	if (m_count == 0 || m_items == 0)
		return 0;
	struct Pair
	{
		StringLookUp *first;
		StringLookUp *second;
	} res;
	bool flag;
	memset(&flag, 0, 1);
	rva002E6329(&res, m_items, m_items + m_count, (void *)&key, *(void **)&flag);
	if (res.first != res.second)
		return (void *)((char *)res.first->info + 4);
	return 0;
}
