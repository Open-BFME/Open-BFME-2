// Disp8 binary-add getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / add eax,[ecx+<DISP2>] / ret
//
// Two dwords are read at fixed displacements from `this`, added, and
// returned. MSVC 7.1 emits the disp8 loads `8B 41 XX` + `03 41 XX`, plus
// `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP8_BINARY_ADD_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(const int *)((const char *)this + (DISP1)) + *(const int *)((const char *)this + (DISP2)); \
	}

BFME_DISP8_BINARY_ADD_GETTER(Rva00108B46BinaryAddField, 0x0C, 0x04)

// BF1 9cb Render2DSentenceClass_ctor.cpp Zero2 is a structural lead only.
// Complete target 108B37..108B46 follows the preceding RET: zero two float
// slots and return the receiver. Original class identity and extent unknown.
struct Rva00108B37Pair
{
    float first, second;
    Rva00108B37Pair *clear();
};
Rva00108B37Pair *Rva00108B37Pair::clear()
{
    first = 0.0f;
    second = 0.0f;
    return this;
}
