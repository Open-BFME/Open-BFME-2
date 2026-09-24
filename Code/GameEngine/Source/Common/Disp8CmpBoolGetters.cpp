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

BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva004C5772CmpBoolField, 0x38, 3, ==)
BFME_DISP8_CMP_ZERO_BOOL_GETTER(Rva006105E0CmpBoolField, 0x48, !=)
BFME_DISP8_TERNARY_BOOL_GETTER(Rva000D1AABCmpBoolField, 0x0C)
