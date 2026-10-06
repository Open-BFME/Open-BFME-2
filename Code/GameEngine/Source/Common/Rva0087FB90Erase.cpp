// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// BfmeVec60::erase (retail 0x006BF590, 77 bytes), BFME1
// Rva0087FB90Erase.cpp donor verbatim in shape: copy the tail forward,
// destroy the removed tail, store the new finish, return first.
//
// The destroyed tail element releases its string at +0x1C through the folded
// teardown at 0x36410, so the element models its +0x1C member as BfmeTail60
// (same member the placed 2-arg resize at 0x6BFCB0 uses) whose release()
// resolves through the existing pin. The bulk copy resolves through the
// worker pinned at 0x6BE2E0 under this TU's spelling.
#include <vector>

// BfmeTail60 stores the same single data pointer as StringBase<char>; retail
// folds this zero-argument thiscall teardown to the matched releaseBuffer.
#pragma comment(linker, "/alternatename:?release@BfmeTail60@@QAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct BfmeTail60
{
	char *m_data;
	void release();
};

struct BfmeElem60
{
	char m_head[0x1C];
	BfmeTail60 m_tail;
	char m_extra[0x04];

	~BfmeElem60()
	{
		m_tail.release();
	}
};

class BfmeVec60
{
public:
	BfmeElem60 *erase(BfmeElem60 *first, BfmeElem60 *last);

	BfmeElem60 *_M_start;
	BfmeElem60 *_M_finish;
	BfmeElem60 *_M_end_of_storage;
};

BfmeElem60 *BfmeVec60::erase(BfmeElem60 *first, BfmeElem60 *last)
{
	BfmeElem60 *i = _STL::copy(last, _M_finish, first);
	_STL::_Destroy(i, _M_finish);
	_M_finish = i;
	return first;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?erase@BfmeVec60@@QAEXPAUBfmeElem60@@0@Z=?erase@BfmeVec60@@QAEPAUBfmeElem60@@PAU2@0@Z")
