// cl: /DNDEBUG /MD /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00360E64@Rva00360F55@@QAE_NABV1@@Z, retail 0x00360E64, 241 bytes.
// Equality for the 0x94-byte ObjectFilter science-cluster record (ctor 0x00360F55).
// Skips refcount at +0x8C; scalars +0x80/+0x90/+0x88/+0x84, 0x1C blobs via
// Rva00360C1FEqual, ScienceType vectors at +0x30/+0x3C/+0x18/+0x24, AsciiRange
// at +0x00/+0x0C via Rva002ADD75Equal. Order follows retail early-outs.
// Evidence: unlock lane; callees 0x00360C1F 0x00360C73 0x002ADD75 rowed;
// callers 0x003617BF 0x0036238F; neighbours 0x00360D26 0x00360F55.
enum ScienceType
{
	SCIENCE_NONE = 0
};
namespace _STL
{
	template <class _Tp, class _Alloc> class vector;
	template <class _Tp> class allocator;
	template <class _Tp, class _Alloc>
	bool operator==(const vector<_Tp, _Alloc> &, const vector<_Tp, _Alloc> &);
}
struct AsciiRange002ADD75
{
	char m_data[12];
};
int Rva00360C1FEqual(const void *a, const void *b);
int Rva002ADD75Equal(const AsciiRange002ADD75 *a, const AsciiRange002ADD75 *b);
#include <vector>
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef unsigned int UnsignedInt;
typedef _STL::vector<AsciiString> AsciiStringVector;

struct BfmeAttributeBits
{
	UnsignedInt m_values[7];	// BitFlags<218>
};

namespace _STL
{
	template <> bool operator==(const vector<ScienceType, allocator<ScienceType> > &, const vector<ScienceType, allocator<ScienceType> > &);
}

class Rva00360F55
{
public:
	Rva00360F55();
	~Rva00360F55();
	bool rva00360E64(const Rva00360F55 &other);

	AsciiStringVector m_names;			// +0x00
	AsciiStringVector m_values;			// +0x0C
	AsciiStringVector m_lists[4];		// +0x18
	BfmeAttributeBits m_firstPlain;		// +0x48
	BfmeAttributeBits m_secondPlain;	// +0x64
	UnsignedInt m_kind;					// +0x80
	UnsignedInt m_relationship;			// +0x84
	bool m_enabled;						// +0x88
	unsigned char m_pad89[3];
	UnsignedInt m_useCount;				// +0x8C
	UnsignedInt m_alignment;			// +0x90
};
bool Rva00360F55::rva00360E64(const Rva00360F55 &other)
{
	if (m_kind == other.m_kind) {
	if (m_alignment == other.m_alignment) {
	if (m_enabled == other.m_enabled) {
	if (m_relationship == other.m_relationship) {
	if ((unsigned char)Rva00360C1FEqual(&m_firstPlain, &other.m_firstPlain)) {
	if ((unsigned char)Rva00360C1FEqual(&m_secondPlain, &other.m_secondPlain)) {
	typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > SciVec;
	if ((const SciVec &)m_lists[2] == (const SciVec &)other.m_lists[2]) {
	if ((const SciVec &)m_lists[3] == (const SciVec &)other.m_lists[3]) {
	if ((const SciVec &)m_lists[0] == (const SciVec &)other.m_lists[0]) {
	if ((const SciVec &)m_lists[1] == (const SciVec &)other.m_lists[1]) {
	if ((unsigned char)Rva002ADD75Equal((const AsciiRange002ADD75 *)&m_names, (const AsciiRange002ADD75 *)&other.m_names)) {
	if ((unsigned char)Rva002ADD75Equal((const AsciiRange002ADD75 *)&m_values, (const AsciiRange002ADD75 *)&other.m_values)) {
		return true;
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	return false;
}
