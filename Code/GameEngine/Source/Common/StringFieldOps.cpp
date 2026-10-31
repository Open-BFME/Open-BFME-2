// cl: /Ireference/shims/bfme2_ascii /O1 /MD
//
// String field operations: add ecx, <field>; jmp to a rowed StringBase
// member. Five clear an AsciiString field (StringBase<char>::clear, which is
// releaseBuffer 0x00036410), two assign one from a C string
// (StringBase<char>::set(const char *) 0x000055F5), one assigns a
// UnicodeString field (StringBase<unsigned short>::set 0x00037150). Receivers
// are unknown; names are per address and no referencing site was found for
// these in this pass.
#include "ascii_string.h"
#include "unicode_string.h"

#define BFME_ASCII_FIELD_CLEAR(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void clear(); \
	private: \
		char m_pad[DISP]; \
		AsciiString m_str; \
	}; \
	void NAME::clear() \
	{ \
		((StringBase<char> *)&m_str)->clear(); \
	}

#define BFME_ASCII_FIELD_SET_CSTR(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(const char *s); \
	private: \
		char m_pad[DISP]; \
		AsciiString m_str; \
	}; \
	void NAME::set(const char *s) \
	{ \
		((StringBase<char> *)&m_str)->set(s); \
	}

class Rva00225A79StringField
{
public:
	void set(const UnicodeString &s);
private:
	char m_pad[0x30];
	UnicodeString m_str;
};

void Rva00225A79StringField::set(const UnicodeString &unicodeString)
{
	((StringBase<unsigned short> *)&m_str)->set((const StringBase<unsigned short> &)unicodeString);
}

class Rva0023DC86StringField
{
public:
	~Rva0023DC86StringField();
private:
	char m_pad[0x18];
	AsciiString m_str;
};

Rva0023DC86StringField::~Rva0023DC86StringField()
{
}
BFME_ASCII_FIELD_CLEAR(Rva004B79D3StringField, 0x348)
BFME_ASCII_FIELD_CLEAR(Rva004B79DEStringField, 0x34C)
BFME_ASCII_FIELD_CLEAR(Rva006BE830StringField, 0x1C)
BFME_ASCII_FIELD_SET_CSTR(Rva000F1010StringField, 0x10)
BFME_ASCII_FIELD_SET_CSTR(Rva006007D2StringField, 0x4)
