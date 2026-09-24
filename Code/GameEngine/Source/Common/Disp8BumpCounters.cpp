// Disp8 increment-and-fetch counters: eleven-byte __thiscall members with
// one shape:
//
//     lea eax,[ecx+<DISP>] / inc dword [eax] / mov eax,[eax] / ret
//
// An int field at a fixed displacement from `this` is incremented and the
// new value returned. The reference-local source keeps the field address in
// eax across the increment and the reload. Every displacement here fits
// disp8 (every offset is below 0x80). Identity is not recovered: every name
// is derived from its address.
// cl: /O1 /MD /EHsc /DNDEBUG
#define BFME_DISP8_BUMP_COUNTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int bump(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	int NAME::bump() \
	{ \
		return ++m_counter; \
	}

BFME_DISP8_BUMP_COUNTER(Rva002B315BBumpCounter, 0xA0)
