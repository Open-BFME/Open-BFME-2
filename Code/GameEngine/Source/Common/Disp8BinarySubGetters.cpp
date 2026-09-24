// Disp8 binary-sub getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / sub eax,[ecx+<DISP2>] / ret
//
// Two dwords are read at fixed displacements from `this`, subtracted, and
// returned. MSVC 7.1 emits the disp8 loads `8B 41 XX` + `2B 41 XX`, plus
// `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP8_BINARY_SUB_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return *(const int *)((const char *)this + (DISP1)) - *(const int *)((const char *)this + (DISP2)); \
	}

BFME_DISP8_BINARY_SUB_GETTER(Rva0049CB5FBinarySubField, 0x20, 0x24)
