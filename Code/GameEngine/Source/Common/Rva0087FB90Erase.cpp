// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// BfmeVec60::erase (retail 0x006BF590, 77 bytes), BFME1
// Rva0087FB90Erase.cpp donor verbatim in shape: copy the tail forward,
// destroy the removed tail, store the new finish, return first.
//
// Element layout from siblings Rva006BE2E0Copy/Rva0087EAA0Fill: 7 ints,
// single-pointer string at +0x1C (set at 0x366F0) plus trailing bytes at
// +0x20/+0x21. The explicit operator= makes the STL bulk copy emit retail's
// element-wise worker at 0x6BE2E0; the tail teardown calls releaseBuffer.
#include <vector>
#include "ascii_string.h"

// BfmeTail60 stores the same single data pointer as StringBase<char>; retail
// folds this zero-argument thiscall teardown to the matched releaseBuffer.
#pragma comment(linker, "/alternatename:?release@BfmeTail60@@QAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct BfmeTail60
{
	char *m_data;
	void release();
};

struct BfmeCoord60
{
	int m_x;
	int m_y;
	int m_z;
};

struct BfmeElem60
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoord60 m_10;
	BfmeTail60 m_1C;
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_pad[2];

	~BfmeElem60()
	{
		m_1C.release();
	}

	BfmeElem60 &operator=(const BfmeElem60 &o)
	{
		m_00 = o.m_00;
		m_04 = o.m_04;
		m_08 = o.m_08;
		m_0C = o.m_0C;
		m_10 = o.m_10;
		((StringBase<char> &)m_1C).set((const StringBase<char> &)o.m_1C);
		m_20 = o.m_20;
		m_21 = o.m_21;
		return *this;
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
