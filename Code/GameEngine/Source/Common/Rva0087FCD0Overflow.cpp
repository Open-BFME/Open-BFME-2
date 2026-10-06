// BFME2 0x006BF6F0/267B: non-POD 16-byte-record vector insertion overflow.
// Reference: Open-BFME-1 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/GameEngine/Source/Common/Rva0087FCD0Overflow.cpp.
// Target facts: Ghidra 267B boundary, seven native calls, 16-byte stride,
// three copied DWORDs and string at +0x0C. push_back6BF990 and setter6BFB20
// independently identify this vector slow path. Original record name unknown;
// field names and view types below preserve donor provenance and ABI only.
// Shared sibling repair: byte allocator replaces donor allocation split;
// cleanup expands string releases then free; /Ob1 restores native scheduling.
// The verified copy/fill workers use three cdecl arguments. Native pushes an
// additional unused dispatch-tag argument; aliases preserve that call ABI.
// cl: /Ob1 /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc_alloconly
// stlport
#include <memory>
#pragma comment(linker, "/alternatename:?bfmeCopyCD@@YAPAUBfmeElemCD@@PBU1@0PAU1@ABUBfmeFalseCD@@@Z=?bfmeCopyF4@@YAPAUBfmeElemF4@@PAU1@00@Z")
#pragma comment(linker, "/alternatename:?bfmeFillCD@@YAPAUBfmeElemCD@@PAU1@IABU1@ABUBfmeFalseCD@@@Z=?bfmeFillF5@@YAPAUBfmeElemF5@@PAU1@IPBU1@@Z")
#pragma comment(linker, "/alternatename:?copyFrom@BfmeTailCD@@QAEXPBU1@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?releaseBuffer@BfmeTailCD@@QAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


struct BfmeFalseCD
{
};

struct BfmeTailCD
{
	char *m_p;
	void copyFrom(const BfmeTailCD *src);
	void releaseBuffer();
};

struct BfmeElemCD
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTailCD m_0C;
};

void *__cdecl bfmeAllocLargeCD(unsigned bytes);
void *__cdecl bfmeAllocSmallCD(unsigned bytes);

BfmeElemCD *bfmeCopyCD(const BfmeElemCD *first, const BfmeElemCD *last,
	BfmeElemCD *result, const BfmeFalseCD &);
BfmeElemCD *bfmeFillCD(BfmeElemCD *result, unsigned count,
	const BfmeElemCD &value, const BfmeFalseCD &);

class BfmeVecCD
{
public:
	void overflow(BfmeElemCD *pos, const BfmeElemCD &value,
		const BfmeFalseCD &, unsigned fill, bool atEnd);
	void clear();

	BfmeElemCD *_M_start;
	BfmeElemCD *_M_finish;
	BfmeElemCD *_M_end_of_storage;
};

void BfmeVecCD::overflow(BfmeElemCD *pos, const BfmeElemCD &value,
	const BfmeFalseCD &, unsigned fill, bool atEnd)
{
	unsigned oldSize = (unsigned)(_M_finish - _M_start);
	const unsigned &growth = oldSize < fill ? fill : oldSize;
	unsigned length = growth + oldSize;

	BfmeElemCD *newStart;
	if (length)
	{
		newStart = (BfmeElemCD *)_STL::allocator<char>::allocate(length * sizeof(BfmeElemCD), 0);
	}
	else
	{
		newStart = 0;
	}

	BfmeElemCD *newFinish = bfmeCopyCD(_M_start, pos, newStart,
		reinterpret_cast<const BfmeFalseCD &>(atEnd));

	if (fill == 1)
	{
		if (newFinish)
		{
			const BfmeElemCD *v = &value;
			newFinish->m_00 = v->m_00;
			newFinish->m_04 = v->m_04;
			newFinish->m_08 = v->m_08;
			newFinish->m_0C.copyFrom(&v->m_0C);
		}
		++newFinish;
	}
	else
	{
		newFinish = bfmeFillCD(newFinish, fill, value,
			reinterpret_cast<const BfmeFalseCD &>(atEnd));
	}

	if (!atEnd)
		newFinish = bfmeCopyCD(pos, _M_finish, newFinish,
			reinterpret_cast<const BfmeFalseCD &>(atEnd));

	BfmeElemCD *last = _M_finish;
	BfmeElemCD *first = _M_start;
	for (; first != last; ++first)
		first->m_0C.releaseBuffer();
	if (_M_start != 0)
		::free(_M_start);

	_M_start = newStart;
	_M_finish = newFinish;
	_M_end_of_storage = newStart + length;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?overflow@BfmeVec50@@QAEXPAUBfmeElem50@@ABU2@ABUBfmeFalse50@@I_N@Z=?overflow@BfmeVecCD@@QAEXPAUBfmeElemCD@@ABU2@ABUBfmeFalseCD@@I_N@Z")
