// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// The 103-byte method appends one two-int record to the shared result payload.
// The constructor at 0x009F39F0 establishes the three vector pointers and the
// cursor at offset 0x0C. Callers at 0x009F6600 and 0x009F4130 provide the two
// record values, while the overflow call reaches the converted OCL vector body.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class OCLSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		int m_bfmeFirst;
		int m_bfmeSecond;
	};
};

struct Rva009F39F0Payload
{
	_STL::vector<OCLSpecialPowerModuleData::Upgrades> m_upgrades;
	void *m_cursor;
	int m_refCount;
};

#include "../../../../GameEngine/Include/Common/Rva009F39F0Result.h"

__declspec(noinline) void Rva009F39F0Result::append(int first, int second)
{
	m_value->m_upgrades.push_back();

	m_value->m_upgrades.end()[-1].m_bfmeFirst = first;
	m_value->m_upgrades.end()[-1].m_bfmeSecond = second;
	m_value->m_cursor = m_value->m_upgrades.begin();
}

// BfmeWideResult view (m_value at +0, rva00626630 declared) is canonical in
// PartitionRangeQueryCallView.h; the twin below reuses this TU's payload.
#include "../../../../GameEngine/Source/Common/PartitionRangeQueryCallView.h"

// ICF-folded twin of append above (same 103 bytes at 0x00626630): the
// BfmeWideResult (Object *, float) spelling stores the same two 4-byte
// record fields, so it reuses this payload and instantiation bit-for-bit.
__declspec(noinline) void BfmeWideResult::rva00626630(Object *obj, float distance)
{
	((Rva009F39F0Payload *)m_value)->m_upgrades.push_back();

	((Rva009F39F0Payload *)m_value)->m_upgrades.end()[-1].m_bfmeFirst = (int)obj;
	((Rva009F39F0Payload *)m_value)->m_upgrades.end()[-1].m_bfmeSecond = *(int *)&distance;
	((Rva009F39F0Payload *)m_value)->m_cursor = ((Rva009F39F0Payload *)m_value)->m_upgrades.begin();
}
