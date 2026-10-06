// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva004E6935@@QAE@XZ retail 0x004E6935 72B
// Member teardown in reverse order: UnicodeString at +0xC (EH state 1),
// the ref holder at +8 released through the rowed
// ?Release_Ref@OpaqueRefCounted 0x00050ED3 when set (state 0), then the
// UnicodeString at +0. Names address-derived; identity unproven.

#include "unicode_string.h"

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva004E6935Ref
{
public:
	~Rva004E6935Ref()
	{
		if (m_item)
			m_item->Release_Ref();
	}

	OpaqueRefCounted *m_item;
};

class Rva004E6935
{
public:
	~Rva004E6935();

private:
	UnicodeString m_text; // +0x00
	int m_04;
	Rva004E6935Ref m_ref; // +0x08
	UnicodeString m_label; // +0x0C
};

Rva004E6935::~Rva004E6935()
{
}
