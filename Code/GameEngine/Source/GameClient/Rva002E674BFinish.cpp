// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// class-gate: allow AsciiString one-pointer codegen view whose inline str() is the retail LUT-label chase
// stlport
//
// Mangled symbol: ?rva002E674B@Rva002E674B@@QAEXAAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@ABVAsciiString@@@Z
// retail 0x002E674B, 104 bytes. Filter LUT by label prefix using the
// imported strstr, pushing matches into out vector. Evidence: retail count at
// +0 plus LUT at +8 with stride 8, strstr via IAT 0x00BBA614 (so <string.h>'s
// _CRTIMP import declaration, not a static CRT call), empty string
// g_Rva0107301CEmptyString, pin push_back 0x0002DBE6, callers at
// 0x002E6809/0x002E681A, donor GameTextManager::getStringsWithLabelPrefix.
// The loop condition alone supplies the count==0 guard; a separate
// `if (m_count == 0) return;` makes /O1 materialize the count in eax.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include <string.h>


struct AsciiStringHeader
{
	int m_ref;
	unsigned short m_len;
	unsigned short m_cap;
	char m_data[1];
};

class AsciiString
{
public:
	const char *str() const { return m_data ? m_data->m_data : ""; }
private:
	AsciiStringHeader *m_data;
};

typedef _STL::vector<AsciiString> AsciiStringVec;

struct StringLookUp
{
	AsciiString *label;
	void *info;
};

class Rva002E674B
{
public:
	void rva002E674B(AsciiStringVec &out, const AsciiString &filter);
	unsigned int m_count;
	int m_pad;
	StringLookUp *m_lut;
};

void Rva002E674B::rva002E674B(AsciiStringVec &out, const AsciiString &filter)
{
	if (!m_lut)
		return;
	for (unsigned int i = 0; i < m_count; ++i) {
		if (strstr(m_lut[i].label->str(), filter.str()) == m_lut[i].label->str())
			out.push_back(*m_lut[i].label);
	}
}
