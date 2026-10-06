// cl: /DNDEBUG /MD /GX
//
// ??1Rva0008B470@@QAE@XZ @0x0008B470 63B: vector dtor in the
// RvaVectorDtorFamily 63B shell shape (unwind-only EH, no try/catch per
// re_attempts 8763/9472): range-Destroy call plus free plus epilog. Binds
// the in-batch provider ?Rva0008AFDCDestroy@@YAXPAX0@Z at 0x0008AFDC (24B,
// Rva0008AFDCDestroy.cpp; forwarder to pinned aux 0x0008A1FD) instead of
// emitting a duplicate. Retail bytes at 0x8B470 match the family shell
// verbatim (EH prolog 0x629188, Destroy call 0x8AFDC, free 0x30830).
// Element identity is unclaimed (void* view; stride 4 lives in the pinned
// aux via rowed ??_GRva00087A93, never asserted here). Separate TU from the
// Destroy provider so this caller sees only its declaration (fifth-pattern
// register-save rule); same split as 0x806B4 (vector) vs 0x5F97BC vs
// 0x4F72ED. Ghidra FUN_0048b470 63B; next byte is unrowed (no overlap with
// rowed 0x8B64A/0x8E4EC siblings).

extern "C" void __cdecl free(void *block);

template <class E> struct RvaVectorFamilyBase
{
	E *m_start;
	E *m_finish;
	E *m_endOfStorage;
	~RvaVectorFamilyBase()
	{
		if (m_start)
			free(m_start);
	}
};

void __cdecl Rva0008AFDCDestroy(void *first, void *last);

// ??1Rva0008B470@@QAE@XZ @0x0008B470 63B -> ?Rva0008AFDCDestroy@@YAXPAX0@Z
struct Rva0008B470 : RvaVectorFamilyBase<void>
{
	~Rva0008B470();
};

Rva0008B470::~Rva0008B470()
{
	Rva0008AFDCDestroy(m_start, m_finish);
}
