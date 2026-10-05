// cl: /O1 /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
//
// ??1BfmeStringTailRecord180@@QAE@XZ @0x000C0DA3 53B: the 180-byte (stride
// 0xB4) trailing-AsciiString record element dtor. Layout is BFME2-observed,
// never donor-ported, cross-proven by the rowed memberwise copy 0x000C0B85
// in StringContainerRecordCopyBFME2.cpp (text@0 + 3 words + values10 vector
// @0x10 + WeaponTemplateSetHead 0x4C heads @0x1C/@0x68; 0x1C+0x4C=0x68 and
// 0x68+0x4C=0xB4 close the stride) and by rowed __destroy_aux 0x000C47CF
// stepping 0xB4 per element. Teardown: values10 via rowed ??1Rva000C0456
// (63B shell -> DestroyPairs 0x32C0CA), text via inlined StringBase release
// (rowed 0x00036410); words and heads are POD and emit no calls (heads copy
// nothrow 0x4C via 0x45455 per the copy body). Empty body: reverse member
// teardown only. BFME1 donor is shape-only (DestructorThunk member-then-base
// ordering); no Snapshot base, no dtor-only opaque base, no guessed vtable.

#include "ascii_string.h"

// Minimal 12B view of the rowed values10 vector dtor. The full template view
// (_STL::vector<BfmeAsciiScalarValue8>) lives in the copy TU; teardown here
// must reach the rowed ??1Rva000C0456 shell retail calls, so this member is
// spelled with that shell's name. No identity beyond the 12B storage plus the
// dtor call it observes is claimed.
struct Rva000C0456
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva000C0456();
};

struct BfmeStringTailRecord180
{
	AsciiString m_text; // +0x00 (teardown via rowed 0x36410, inlined)
	unsigned int m_word04; // +0x04
	unsigned int m_word08; // +0x08
	unsigned int m_word0C; // +0x0C
	Rva000C0456 m_values10; // +0x10 (teardown via rowed 0xC0456)
	unsigned char m_head1C[0x4C]; // +0x1C (POD; nothrow copy via 0x45455)
	unsigned char m_head68[0x4C]; // +0x68 (POD; nothrow copy via 0x45455)
	~BfmeStringTailRecord180();
};

// ??1BfmeStringTailRecord180@@QAE@XZ @0x000C0DA3 53B. Empty body: reverse
// member teardown (values10, then text); words and heads are trivially
// destructible and emit no calls.
BfmeStringTailRecord180::~BfmeStringTailRecord180()
{
}
