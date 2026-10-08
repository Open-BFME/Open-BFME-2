// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /Ob2 /Ireference/shims/moduledata
// stlport
// ?rva00358333@Rva0034C5E0@@QAEXPAVOverridable@@PAVImage@@@Z @ 0x00358333 (116B).
// Lazy-init map at +0x0C then subscript-assign second arg keyed by final override of first arg.
// Evidence: cmp [esi+0x0C] null-check then push 0x0C new 0x0002FDA0 plus map ctor 0x0033C432
// with EH state 0 to -1; mov ecx [edi+4] test je mov eax edi else call 0x001E35DF then
// mov ecx [esi+0x0C] lea push subscript 0x002077D6 then store [ebp+0x0C]; ret 8 two args.
// Row 0x001E35DF types as void but body uses eax result: declared here as
// Overridable::getFinalOverride per its pin (row-type exception per taskfile).
#include <map>

#include "Common/Snapshot.h"

#include "ascii_string.h"

class Image;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

public:
	void *m_pad0;
	Overridable *m_next;
};

namespace _STL
{
template <>
class map<int, void *, less<int>, allocator<pair<const int, void *> > >
{
public:
	map();

private:
	void *m_pad[3];
};
}

typedef _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > MapIntVoid0033C432;

class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
};

class Rva0034C5E0 : public Snapshot
{
public:
	void rva00358333(Overridable *tt, Image *img);

private:
	AsciiString m_str;
	int m_val;
	MapIntVoid0033C432 *m_tree;
};

void Rva0034C5E0::rva00358333(Overridable *tt, Image *img)
{
	if (!tt)
		return;
	if (!m_tree)
		m_tree = new MapIntVoid0033C432;
	Overridable *next = tt->m_next;
	Overridable *key;
	if (next)
		key = (Overridable *)next->getFinalOverride();
	else
		key = tt;
	((ImageSubscriptMap *)m_tree)->operator[]((unsigned int)key) = img;
}
