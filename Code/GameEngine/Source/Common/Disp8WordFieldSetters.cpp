// Disp8 word setters: twelve-byte __thiscall members with one shape:
//
//     mov ax,[esp+4] / mov [ecx+<DISP>],ax / ret 4
//
// One word is taken from the stack argument slot and stored at a fixed
// displacement from `this`. Same macro as Disp8ByteFieldSetters.cpp; every
// displacement here fits disp8 (MSVC 7.1 uses disp8 whenever the offset
// fits, so every offset is below 0x80).
// Identity is not recovered: every name is derived from its address,
// following Disp8ByteFieldSetters.cpp.
// No // cl: line (defaults match the frameless twelve-byte shape).
#define BFME_DISP8_WORD_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(unsigned short value); \
		char m_lead[DISP]; \
		unsigned short m_value; \
	}; \
	void NAME::set(unsigned short value) \
	{ \
		m_value = value; \
	}

BFME_DISP8_WORD_SETTER(Rva004D5978WordSlot, 0x20)
BFME_DISP8_WORD_SETTER(Rva004D59ACWordSlot, 0x1C)

// Clean BF1 f98983a7 Rva003D4CD0SetWord.cpp and Rva003D4CF0SetWord.cpp
// are whole source leads. Their address-owned identities are donor facts.
// Each native member below follows a complete RET and has its own RET4:
// 2E6C94..2E6CA2 and 2E6CA2..2E6CB0. It reads the receiver's word0
// pointer and stores the low 16 bits of one stack argument at +12 or +10.
// All eight native sections contain zero direct call/address witnesses.
// Signedness and original owner/full object and pointee sizes are unknown;
// these independent accessed-prefix views reproduce raw word stores only.
class Rva002E6C94WordChase {
public:
    void set(unsigned short value);
private:
    void *pointee;
};
void Rva002E6C94WordChase::set(unsigned short value) {
    *(unsigned short *)((char *)pointee + 0x12) = value;
}
class Rva002E6CA2WordChase {
public:
    void set(unsigned short value);
private:
    void *pointee;
};
void Rva002E6CA2WordChase::set(unsigned short value) {
    *(unsigned short *)((char *)pointee + 0x10) = value;
}
