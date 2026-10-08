// Disp blob copy setters: one __thiscall member per address, each copying a
// 128-byte (32-dword) value from its single stack argument into `this` at a
// fixed displacement and returning (ret 4). The retail shape is
//
//     mov esi,[esp+8] / lea edi,[ecx+<DISP>] / push 20h / pop ecx / rep movsd
//
// The class names are address-derived (Rva<addr>BlobSlot); identity is not
// recoverable from the 19 bytes alone. The macro is the same shape as the
// BFME_DISP_DWORD_SETTER family in DispDwordFieldSetters.cpp.
// No // cl: line (defaults match the frameless shape).

#define BFME_DISP_BLOB_SETTER(NAME, DISP) \
	struct NAME##Blob \
	{ \
		int m_words[32]; \
	}; \
	class NAME \
	{ \
	public: \
		void set(const NAME##Blob *value); \
		char m_lead[DISP]; \
		NAME##Blob m_value; \
	}; \
	void NAME::set(const NAME##Blob *value) \
	{ \
		m_value = *value; \
	}

BFME_DISP_BLOB_SETTER(Rva0028A5D5BlobSlot, 0x10)
