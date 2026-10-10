// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z
// partial score=0.85 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O2 /EHsc /DNDEBUG /MD
//
// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z @0x0040AAF8 (~173B).
// Record-key lookup over 0x68-byte entries between +0x18/+0x1C: a pinned
// always-0 fragment call first (its found/end comparison returns early),
// then a NameKeyGenerator warming scan that rebuilds temporaries per entry
// and returns 0. Head range loads stay in registers for the fragment call
// while the loop re-reads the members; the shim AsciiString (friend of
// StringBase) copy-constructs each temporary through the rowed copy ctor
// 0x000365F0 and releases through the rowed releaseBuffer 0x00036410;
// keyToName is the rowed 0x00148C95. Unsigned index/offset/count match the
// jb/test-jbe shapes. Resolves U in 7 units.
#include "ascii_string.h"
#include <new>

enum NameKeyType
{
	DUMMY_NAME_KEY = 0
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

int Rva00080A8C(int a, int b, int c);

class Rva0040BAD0
{
public:
	int rva0040AAF8(int key);
private:
	char m_pad[0x18];
	volatile int m_begin;
	volatile int m_end;
};

int Rva0040BAD0::rva0040AAF8(int key)
{
	int found = Rva00080A8C(m_begin, m_end, (int)&key);
	if (found != m_end)
		return found;
	AsciiString first(TheNameKeyGenerator->keyToName((NameKeyType)key));
	if ((unsigned int)((m_end - m_begin) / 0x68) > 0)
	{
		unsigned int i = 0;
		unsigned int off = 0;
		do
		{
			{
				// Reuse key's dead arg slot for the per-iteration
				// temporary so the frame matches retail exactly.
				AsciiString *t = new ((void *)&key) AsciiString(
					TheNameKeyGenerator->keyToName((NameKeyType)*(int *)(m_begin + off)));
				t->~AsciiString();
			}
			++i;
			off += 0x68;
		} while (i < (unsigned int)((m_end - m_begin) / 0x68));
	}
	return 0;
}

// ================= PRIOR BANK (score 0.9, 2026-09-30, superseded in part) =================
// Kept for its layout intel (ebx/edi, s2@[ebp+8], s1@[ebp-10], single push) and sibling
// leads (0x0040AAD5, AsciiString forwarder). NOTE: its 'find 0x0040A8AC' premise is
// refuted by the current bank above (3B xor-ret tail, pinned as fragment); its keyToName
// pin note may also predate the row. Prefer the current bank's callee model.

// ?rva0040AAF8@Rva0040AAF8@@QAEPAUBfmePod104@@H@Z
// partial score=0.9 date=2026-09-30
// ?rva0040AAF8@Rva0040AAF8@@QAEPAUBfmePod104@@H@Z
// partial score=0.9 date=2026-09-30
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x0040AAF8 173B chain of find 0x0040A8AC with NameKeyGenerator fallback.
// Best attempt reaches 176B vs 173B with all 8 reloc callees correct
// (find 0x0040A8AC; keyToName 0x00148C95 pin; StringBase copy 0x000365F0;
// releaseBuffer 0x00036410) and unsigned jb/jbe branches correct.
// Remaining wall is pure register/stack allocation starting at prologue:
// retail keeps loop index in ebx and byte offset in edi with s2 reusing the
// incoming arg slot at [ebp+8] and s1 at [ebp-0x10] (single push ecx);
// this build keeps index on the stack at [ebp+8] with s1 at [ebp-0x14] and
// s2 at [ebp-0x10] (double push ecx) for +3B. Tried int vs unsigned index
// (unsigned fixes jb); pointer loop (loses idiv; 138B); if-block vs early
// return (same); unnamed temp for s2 (same); first/last locals (countdown;
// 146B). Shape-lever round-robin row 25 tried via first/last locals; failed.
// Next: force index into ebx with s2 reusing arg slot; see 0x0040AAD5 sibling
// in stlport_pod_vector_bodies.cpp and DataChunkOutputWriteNameKey.cpp for
// the AsciiString inline forwarder that routes copy to StringBase 0x365F0.
#include <vector>
#include <algorithm>
struct BfmePod104 { int a[26]; };
inline bool operator==(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] < y.a[0]; }
struct BfmeStringData
{
    unsigned short m_refCount;
    unsigned short m_numCharsAllocated;
    unsigned short m_len;
    unsigned short m_pad;
};
class AsciiString;
template <typename T>
class StringBase
{
    friend class AsciiString;
private:
    StringBase(const StringBase<T> &other);
    void releaseBuffer();
    BfmeStringData *m_data;
};
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    __forceinline ~AsciiString() { releaseBuffer(); }
};
enum NameKeyType
{
    NAMEKEY_INVALID = 0
};
class NameKeyGenerator
{
public:
    const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva0040AAF8 {
    int _pad[6];
    BfmePod104 *_first;
    BfmePod104 *_last;
public:
    BfmePod104 *rva0040AAF8(int key);
};
// ?rva0040AAF8@Rva0040AAF8@@QAEPAUBfmePod104@@H@Z present-unmatched
BfmePod104 *Rva0040AAF8::rva0040AAF8(int key)
{
    BfmePod104 *found = _STL::find(_first, _last, (const BfmePod104 &)key);
    if (found != _last)
        return found;
    AsciiString s1(TheNameKeyGenerator->keyToName((NameKeyType)key));
    for (unsigned i = 0; i < (unsigned)(_last - _first); ++i) {
        AsciiString s2(TheNameKeyGenerator->keyToName((NameKeyType)_first[i].a[0]));
    }
    return 0;
}
