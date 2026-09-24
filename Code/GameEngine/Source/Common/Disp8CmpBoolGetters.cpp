// Disp8 compare bool getters: frameless __thiscall members in three shapes:
//
//   CMP_IMM: xor eax,eax / cmp [ecx+<DISP>],<IMM8> / setcc al / ret
//   CMP_ZERO: xor eax,eax / cmp [ecx+<DISP>],eax / setcc al / ret
//   TERNARY: cmp [ecx+<DISP>],0 / setcc al / ret (no xor)
//
// One dword is read at a fixed displacement from `this` and tested. The CMP
// forms zero eax first and return the setcc result; comparing against zero
// reuses the zeroed eax instead of an immediate. The TERNARY form spells the
// test as `m_value ? true : false`, which the compiler emits as a bare
// compare-plus-setcc with no xor (probe-proven). Identity is not recovered:
// every name is derived from its address.
// cl: /O1
#define BFME_DISP8_CMP_IMM_BOOL_GETTER(NAME, DISP, IMM, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value OP IMM; \
	}
#define BFME_DISP8_CMP_ZERO_BOOL_GETTER(NAME, DISP, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value OP 0; \
	}
#define BFME_DISP8_TERNARY_BOOL_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value ? true : false; \
	}
#define BFME_DISP8_TERNARY_CMP_BOOL_GETTER(NAME, DISP, IMM, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value OP IMM ? true : false; \
	}
#define BFME_DISP8_PTR_TERNARY_CMP_BOOL_GETTER(NAME, DISP, INNER_DISP, IMM, OP) \
	struct NAME##Inner \
	{ \
		char m_pad[INNER_DISP]; \
		int m_inner; \
	}; \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		NAME##Inner *m_ptr; \
	}; \
	bool NAME::get() const \
	{ \
		return m_ptr->m_inner OP IMM ? true : false; \
	}
#define BFME_DISP8_PTR_TERNARY_BOOL_GETTER(NAME, DISP, INNER_DISP) \
	struct NAME##Inner \
	{ \
		char m_pad[INNER_DISP]; \
		int m_inner; \
	}; \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		NAME##Inner *m_ptr; \
	}; \
	bool NAME::get() const \
	{ \
		return m_ptr->m_inner ? true : false; \
	}
#define BFME_DISP8_BYTE_CMP_BOOL_GETTER(NAME, DISP, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		unsigned char m_byte; \
	}; \
	bool NAME::get() const \
	{ \
		return m_byte OP 0; \
	}
#define BFME_DISP8_BYTE_TERNARY_BOOL_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		unsigned char m_byte; \
	}; \
	bool NAME::get() const \
	{ \
		return m_byte ? true : false; \
	}

BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva004C5772CmpBoolField, 0x38, 3, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva006105E0CmpBoolField, 0x48, !=)
BFME_DISP8_TERNARY_BOOL_GETTER(Rva000D1AABCmpBoolField, 0x0C)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00041CE9CmpBoolField, 0x110, 5, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00041CF6CmpBoolField, 0x110, 1, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00085117CmpBoolField, 0x110, 3, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva002034DCCmpBoolField, 0x114, 3, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00210C4CCmpBoolField, 0x114, 1, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00210C59CmpBoolField, 0x114, 2, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva002C67CFCmpBoolField, 0x178, -1, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0025DD1BCmpBoolField, 0x3C, -1, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0039567CCmpBoolField, 0x34, 4, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0057B94DCmpBoolField, 0x28, 2, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0057B957CmpBoolField, 0x28, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva00219095CmpBoolField, 0x114, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0028B7B5CmpBoolField, 0x354, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0050D18CmpBoolField, 0x14, <=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva002A7EA0CmpBoolField, 0x14, 0x13, <)
BFME_DISP8_TERNARY_CMP_BOOL_GETTER(Rva001DBB54CmpBoolField, 0x04, 0, <)
BFME_DISP8_PTR_TERNARY_CMP_BOOL_GETTER(Rva0058B9A9CmpBoolField, 0x18, 0x04, 0, ==)
BFME_DISP8_BYTE_CMP_BOOL_GETTER(Rva0055C428CmpBoolField, 0x80, ==)
BFME_DISP8_BYTE_CMP_BOOL_GETTER(Rva000665A4CmpBoolField, 0x3880, ==)
BFME_DISP8_BYTE_TERNARY_BOOL_GETTER(Rva0028ADECmpBoolField, 0x365)
BFME_DISP8_PTR_TERNARY_BOOL_GETTER(Rva001E3441CmpBoolField, 0x04, 0xD8)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva004CAFCCmpBoolField, 0x04, 1, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0025DC26CmpBoolField, 0x10, 1, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva005A687FCmpBoolField, 0x94C, 1, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva005B5AAFCmpBoolField, 0x14C, 1, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva005F8E03CmpBoolField, 0x28, 3, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva00782E7CmpBoolField, 0x04, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva000A7801CmpBoolField, 0x10, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva000B4536CmpBoolField, 0x274, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva000E4401CmpBoolField, 0x98, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva00111F02CmpBoolField, 0xC8, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0014D1AECmpBoolField, 0x48, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva001DFAADCmpBoolField, 0x4C4, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva001F349ECmpBoolField, 0x08, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0020E2F8CmpBoolField, 0x44, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0026224BCmpBoolField, 0x50, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0059EB27CmpBoolField, 0x2B0, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0008FF78CmpBoolField, 0x1EC, !=)

// Zero-displacement members: the compared dword is the first field, so no
// lead padding is emitted (a zero-length pad array is not legal C++).
class Rva004CB73CmpBoolField
{
public:
	bool get() const;
	int m_value;
};
bool Rva004CB73CmpBoolField::get() const
{
	return m_value != 0;
}
class Rva0050D3ECmpBoolField
{
public:
	bool get() const;
	int m_value;
};
bool Rva0050D3ECmpBoolField::get() const
{
	return m_value == 0;
}
class Rva002620FECmpBoolField
{
public:
	bool get() const;
	int m_value;
};
bool Rva002620FECmpBoolField::get() const
{
	return m_value != -1;
}
BFME_DISP8_TERNARY_BOOL_GETTER(Rva00210CDDCmpBoolField, 0xB8)
BFME_DISP8_TERNARY_BOOL_GETTER(Rva00211EF5CmpBoolField, 0x228)
BFME_DISP8_TERNARY_BOOL_GETTER(Rva003598CBCmpBoolField, 0x40)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0026FC63CmpBoolField, 0x260, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0027C1F2CmpBoolField, 0x1B4, >)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0028A842CmpBoolField, 0x28, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0028A862CmpBoolField, 0x24, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0029A378CmpBoolField, 0x1A104, >=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva002E05E2CmpBoolField, 0xBC, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva00354EB0CmpBoolField, 0x08, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva00356F54CmpBoolField, 0x30C, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva003B8ACFCmpBoolField, 0x20, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva003E3C19CmpBoolField, 0x40, >)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva003F0D9CCmpBoolField, 0x20, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0046A5E6CmpBoolField, 0x58, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0026FD20CmpBoolField, 0x0C, -1, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva002B239BCmpBoolField, 0x44, 1, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva002B23A5CmpBoolField, 0x44, 2, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva002B30FBCmpBoolField, 0x78, -1, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva002D2CC1CmpBoolField, 0x110, 6, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00327C2FCmpBoolField, 0x04, 2, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0035BCD7CmpBoolField, 0x110, 4, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0036389FCmpBoolField, 0x20, 0x7FFFFFFF, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00262186CmpBoolField, 0x20, 0x7FFFFFFF, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00313913CmpBoolField, 0x1E0, 0x8020CE, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0031393ACmpBoolField, 0x1E0, 0x727E5D, ==)
BFME_DISP8_BYTE_CMP_BOOL_GETTER(Rva0031A9E3CmpBoolField, 0x14, ==)
BFME_DISP8_BYTE_CMP_BOOL_GETTER(Rva003FE581CmpBoolField, 0x28, ==)
// Backward-chase ternary: the method runs on a subobject BACK bytes into its
// container, so the pointer member is read at a negative displacement from
// `this` and the inner byte is tested through it (probe-proven; a direct
// backward cast would fold the two offsets into one read).
#define BFME_DISP8_BACK_PTR_TERNARY_BOOL_GETTER(NAME, BACK, INNER_DISP) \
	struct NAME##Inner \
	{ \
		char m_pad[INNER_DISP]; \
		unsigned char m_b; \
	}; \
	struct NAME##Outer; \
	class NAME##Sub \
	{ \
	public: \
		bool get() const; \
	}; \
	struct NAME##Outer \
	{ \
		NAME##Inner *m_ptr; \
		char m_fill[BACK - 4]; \
		NAME##Sub m_sub; \
	}; \
	bool NAME##Sub::get() const \
	{ \
		return ((NAME##Outer *)((char *)this - BACK))->m_ptr->m_b ? true : false; \
	}
BFME_DISP8_BACK_PTR_TERNARY_BOOL_GETTER(Rva00462CD3, 0x1C, 0x86)
BFME_DISP8_BACK_PTR_TERNARY_BOOL_GETTER(Rva0047CB3F, 0x1C, 0x1A0)
BFME_DISP8_BACK_PTR_TERNARY_BOOL_GETTER(Rva0049CF9E, 0x1C, 0x4C)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva00497960CmpBoolField, 0x10, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva004A8125CmpBoolField, 0x38, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva004D374CCmpBoolField, 0x120, !=)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva004D86B1CmpBoolField, 0x28, 1, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva004D55FCCmpBoolField, 0x24, 0x448, ==)
BFME_DISP8_TERNARY_CMP_BOOL_GETTER(Rva004D393ACmpBoolField, 0x0C, 1, ==)
BFME_DISP8_PTR_TERNARY_BOOL_GETTER(Rva0036CC7ECmpBoolField, 0x04, 0x1C)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0008E112CmpBoolField, 0x110, 9, !=)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva000EFA05CmpBoolField, 0x0C, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva0018C092CmpBoolField, 0x30, !=)
