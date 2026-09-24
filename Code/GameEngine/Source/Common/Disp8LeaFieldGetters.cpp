// Disp8 LEA getters: four-byte __thiscall members with one shape:
//
//     lea eax,[ecx+<DISP>] / ret
//
// The address of a member at a fixed displacement from `this` is returned.
// Spelled as byte-pointer arithmetic from `this`, which MSVC 7.1 folds to
// the same disp8 lea. The pointee type is unwitnessed (only an address is
// produced), so the return is an untyped pointer. Members before the
// accessed one are not spelled at all: unlike the load families, no lead
// array is needed because nothing is read.
// Identity is not recovered: every name is derived from its address, in the
// same opaque-holder convention as the neighboring Disp* families.
// No // cl: line (defaults match the frameless four-byte shape).
#define BFME_DISP8_LEA_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void *get() const; \
	}; \
	void *NAME::get() const \
	{ \
		return (char *)this + DISP; \
	}

// Negative-displacement sibling: the disp8 byte sign-extends, so a disp byte
// above 0x7F addresses *before* `this` (e.g. 9C = -100). Spelled as a
// negative byte offset from `this`, which folds to the same disp8 lea.
#define BFME_DISP8_NEG_LEA_GETTER(NAME, BACK) \
	class NAME \
	{ \
	public: \
		void *get() const; \
	}; \
	void *NAME::get() const \
	{ \
		return (char *)this - BACK; \
	}

BFME_DISP8_NEG_LEA_GETTER(Rva00305927LeaField, 100)
BFME_DISP8_NEG_LEA_GETTER(Rva0030592BLeaField, 116)
BFME_DISP8_LEA_GETTER(Rva00314046LeaField, 0x30)
BFME_DISP8_LEA_GETTER(Rva003EFDD7LeaField, 0x4C)
BFME_DISP8_LEA_GETTER(Rva0049CB82LeaField, 0x28)
BFME_DISP8_LEA_GETTER(Rva005C4AD1LeaField, 0x04)
BFME_DISP8_LEA_GETTER(Rva001D96ECLeaField, 0x50)
BFME_DISP8_LEA_GETTER(Rva001D96F0LeaField, 0x60)
BFME_DISP8_LEA_GETTER(Rva001D96F4LeaField, 0x70)
BFME_DISP8_NEG_LEA_GETTER(Rva00299C74LeaField, 108)
BFME_DISP8_NEG_LEA_GETTER(Rva00299C78LeaField, 112)
BFME_DISP8_LEA_GETTER(Rva00042287LeaField, 0x58)
BFME_DISP8_NEG_LEA_GETTER(Rva00299CBELeaField, 52)
BFME_DISP8_LEA_GETTER(Rva00306BA5LeaField, 0x06)
BFME_DISP8_LEA_GETTER(Rva00017B80LeaField, 0x48)
BFME_DISP8_LEA_GETTER(Rva0049CB86LeaField, 0x40)
BFME_DISP8_LEA_GETTER(Rva005C4AD5LeaField, 0x08)
BFME_DISP8_LEA_GETTER(Rva005C4AD9LeaField, 0x14)
BFME_DISP8_LEA_GETTER(Rva003674F6LeaField, 0x54)
BFME_DISP8_LEA_GETTER(Rva0036CBE7LeaField, 0x18)
BFME_DISP8_LEA_GETTER(Rva003EE704LeaField, 0x44)
BFME_DISP8_LEA_GETTER(Rva003F3FE4LeaField, 0x6C)
BFME_DISP8_LEA_GETTER(Rva00405972LeaField, 0x74)
BFME_DISP8_NEG_LEA_GETTER(Rva004647CDLeaField, 32)
BFME_DISP8_NEG_LEA_GETTER(Rva004B3FC7LeaField, 20)
BFME_DISP8_LEA_GETTER(Rva0066D7D0LeaField, 0x30)
BFME_DISP8_LEA_GETTER(Rva00750502LeaField, 0x10)
BFME_DISP8_LEA_GETTER(Rva0053B8E5LeaField, 0x48)
BFME_DISP8_LEA_GETTER(Rva0053998CLeaField, 0x38)
BFME_DISP8_NEG_LEA_GETTER(Rva004BF893LeaField, 16)
BFME_DISP8_LEA_GETTER(Rva00657630LeaField, 0x50)
BFME_DISP8_LEA_GETTER(Rva00657640LeaField, 0x70)
BFME_DISP8_LEA_GETTER(Rva00661E70LeaField, 0x6C)
BFME_DISP8_LEA_GETTER(Rva0066D800LeaField, 0x55)
BFME_DISP8_LEA_GETTER(Rva0066E430LeaField, 0x10)
BFME_DISP8_LEA_GETTER(Rva00723140LeaField, 0x04)
