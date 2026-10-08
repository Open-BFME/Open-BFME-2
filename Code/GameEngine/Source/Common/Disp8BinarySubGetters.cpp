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
BFME_DISP8_BINARY_SUB_GETTER(Rva002C9504BinarySubField, 0x18, 0x28)
BFME_DISP8_BINARY_SUB_GETTER(Rva00306C42BinarySubField, 0x08, 0x04)
BFME_DISP8_BINARY_SUB_GETTER(Rva006DAE20BinarySubField, 0x04, 0x08)

// BF1 9cbfb551fe Common/Rva0029BC30Bump.cpp is the clean semantic donor.
// Full native leaf 0049CB66..0049CB6E ends at its own RET boundary.
// Target evidence: increment receiver24 dword; set receiver2C to all ones.
// Original owner unresolved; the address-owned type is independent of nearby classes.
class Rva0049CB66Fields {
public: void bump();
private: char unknown[0x24]; unsigned int value24; unsigned int unknown28; int value2C;
};
void Rva0049CB66Fields::bump() { ++value24; value2C = -1; }
