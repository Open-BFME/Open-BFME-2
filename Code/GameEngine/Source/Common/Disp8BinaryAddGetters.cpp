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
