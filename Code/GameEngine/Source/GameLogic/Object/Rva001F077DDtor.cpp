// cl: /O1 /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
// ??1Rva001F077D@@QAE@XZ, retail 0x001F077D, 59 bytes.
// Implicit-dtor teardown: AsciiString at +0x10 (inline ~AsciiString splices
// to a direct StringBase<D> releaseBuffer call 0x00036410, which is why no
// out-of-line member-dtor call appears) destroyed first under EH state 0,
// then the malloc'd buffer holder at +0x0 (inline null-checked free via
// _free 0x00030830) runs stateless last. The single and/or [ebp-4] pair and
// the __EH_prolog frame come from the one non-trivial member teardown.
// Matches the sibling ??1AnimSet pattern (three inlined releaseBuffers with
// counting states, no member-dtor calls). Found via 3 direct callers
// (0x1F097D deleting-dtor-shaped wrapper plus two in 0x1F0996); no vtable
// carries it, so the class keeps an honest address-derived name.
// The 28B wrapper at 0x001F097A (dtor call plus flag-gated operator delete
// 0x0002FD60) is not claimed here.
#include "ascii_string.h"

extern "C" void __cdecl free(void *block);

struct Rva001F077DBuf
{
	char *m_ptr;
	~Rva001F077DBuf()
	{
		if (m_ptr)
			free(m_ptr);
	}
};

struct Rva001F077D
{
	Rva001F077DBuf m_buf;
	char m_pad04[12];
	AsciiString m_str;
};

// Anchor forces the implicit dtor out of line under its own name; the anchor
// itself is not retail code.
// ?_bfmeRva001F077DDtorAnchor@@YAXXZ absent-from-retail
void _bfmeRva001F077DDtorAnchor()
{
	static_cast<Rva001F077D *>(0)->Rva001F077D::~Rva001F077D();
}
