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
