// cl: /Ivendor/stlport /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0020EAF6@Rva0020EAF6View@@QAEPAVRva0020E89C@@H@Z @0x0020EAF6 17B.
// Target evidence: Ghidra bounds FUN_0060eaf6 at 17 bytes. It loads this+8,
// returns null when that pointer is null, and otherwise tail-jumps to the
// 146-byte FUN_0060e90f with the original one-dword argument. The two views
// are address-derived; the underlying collection and entry identities remain
// unproven.

#include <vector>

class Rva0020E89C;

// Local memory view: only the key offset is proven; original type/full size unknown.
struct Rva0020E90FKeyPrefix
{
	char opaque_00[0x12c];
	int id;
};

class Rva0020E90FView
{
public:
	Rva0020E89C *rva0020E90F(int id);

private:
	char opaque_00[0x2c];
	_STL::vector<Rva0020E90FKeyPrefix *> entries;
};

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);

private:
	char m_pad00[8];
	Rva0020E90FView *m_holder;
};

Rva0020E89C *Rva0020EAF6View::rva0020EAF6(int index)
{
	if (m_holder == 0)
		return 0;
	return m_holder->rva0020E90F(index);
}

// Native 0x0020E90F..0x0020E9A1, RET4; includes both return tails.
// STLport 4.5.3 vector operations reproduce the count reloads, as in the
// matched 0x0020E9A1 sibling. Target proves key +0x12c and begin/end +0x2c/+0x30.
// The existing wrapper supplies the opaque result type; no region identity asserted.
Rva0020E89C *Rva0020E90FView::rva0020E90F(int id)
{
	if (id == -1)
		return 0;
	int first = id;
	if ((unsigned)first >= entries.size() || first < 0)
		first = 0;
	for (unsigned i = first; i < entries.size(); ++i)
	{
		if (entries[i]->id == id)
			return static_cast<Rva0020E89C *>(static_cast<void *>(entries[i]));
	}
	for (int i = 0; i < first; ++i)
	{
		if (entries[i]->id == id)
			return static_cast<Rva0020E89C *>(static_cast<void *>(entries[i]));
	}
	return 0;
}
