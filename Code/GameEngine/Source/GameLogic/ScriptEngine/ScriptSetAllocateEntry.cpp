// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 003B7C47..003B7D90 full329B RET4; same receiver as rowed
// search003B573E and transfer003B7F8E. WB AB2C80 labels the operation
// ScriptSetBase<ScriptGroup>::allocateEntry and exposes integer indices,
// indexPos and the sorted index vector. Original target specialization stays
// uncertain; retain the established neutral ABI owner and record spelling.
// Target-derived record: prev0 next4 name8 releasedC refsE payload10,
// stride14, freeHead18 and tail1C. Native stores the allocated integer index
// before set(name), then passes that exact stack slot to the folded 4-byte
// insert provider. The pointer-element vector below is the existing ledger
// provider's ABI view; its words carry integer indices, not object pointers.
// Real inline insert/reserve definitions must stay visible: hiding them
// forces an unnecessary address-escaped index home or a six-byte cast temp.
// Whole329B and EH checked without aliases or new pins.
#include <vector>
// max<unsigned> only inlines here; keep it inline-only so this unit emits
// no copy against retail's 0x00013740 (body verbatim).
namespace _STL {
template <> __declspec(dllimport) __forceinline
const unsigned int &max<unsigned int>(const unsigned int &__a, const unsigned int &__b)
{ return __a < __b ? __b : __a; }
}
#include "ascii_string.h"
class ModuleData;
#include "../../../Include/Common/BfmeStringRecord003B3F78.h"
namespace _STL {


	template<> void vector<BfmeStringRecord003B3F78>::push_back(const BfmeStringRecord003B3F78 &);
}
class Rva003B573E {
	_STL::vector<const ModuleData *> m_sorted;
	_STL::vector<BfmeStringRecord003B3F78> m_records;
	int m_freeHead;
	int m_tail;
public:
	int rva003B573E(const StringBase<char> &);
	int rva003B7C47(const StringBase<char> &);
};

// ?rva003B7C47@Rva003B573E@@QAEHABV?$StringBase@D@@@Z
int Rva003B573E::rva003B7C47(const StringBase<char> &key)
{
	unsigned int position = rva003B573E(key);
	int index;
	if (position < m_sorted.size() &&
		((const StringBase<char> &)m_records[(int)m_sorted[position]].text).compare(key) == 0) {
		index = (int)m_sorted[position];
		if (!m_records[index].flag)
			return -1;
	} else {
		unsigned int wanted = m_sorted.size() + 1;
		if (wanted > m_sorted.capacity())
			m_sorted.reserve(wanted + (wanted >> 1) + 8);
		if (m_freeHead == -1) {
			int freeIndex = m_records.size();
			m_records.push_back(BfmeStringRecord003B3F78());
			m_records.back().word0 = -1;
			m_freeHead = freeIndex;
		}
		index = m_freeHead;
		BfmeStringRecord003B3F78 &record = m_records[index];
		((StringBase<char> &)record.text).set(key);
		m_sorted.insert(m_sorted.begin() + position, *reinterpret_cast<const ModuleData*const*>(&index));
		m_freeHead = record.word0;
		if (m_tail != -1)
			m_records[m_tail].word1 = index;
		record.word0 = m_tail;
		record.word1 = -1;
		m_tail = index;
		record.short0 = 0;
	}
	BfmeStringRecord003B3F78 &record = m_records[index];
	++record.short0;
	record.flag = 0;
	return index;
}
