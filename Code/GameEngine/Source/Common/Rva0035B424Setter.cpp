// cl: /DNDEBUG /MD /GX- /Ireference/shims/bfme2_ascii
// ?rva0035B424@Rva0035B424@@QAEXH@Z retail 0x0035B424 37B
// Bounds-checked index setter over list at +0xec/+0xf0 storing to +0xfc.
// Evidence: unlock lane, callers 0x0053DB2D 0x0056833F, lea-vec shape.
#include "ascii_string.h"

struct Rva0035B424Vec
{
	AsciiString *m_begin;
	AsciiString *m_end;
};

class Rva0035B424
{
public:
	void rva0035B424(int index);

private:
	char m_pad[0xec];
	Rva0035B424Vec m_vec;
	char m_pad2[0x8];
	int m_selected;
};

void Rva0035B424::rva0035B424(int index)
{
	if (index < 0)
		return;
	Rva0035B424Vec *p = &m_vec;
	unsigned int count = (unsigned int)((p->m_end - p->m_begin));
	if ((unsigned int)index >= count)
		return;
	m_selected = index;
}
