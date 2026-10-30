// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x0043448C checks the selected saved-game name through the
// Rva0037BBED object and chooses state 17 or the existing state helper.
#include "unicode_string.h"

struct AptSaveLoadPending
{
	UnicodeString m_name;
	unsigned char m_pad04[0x24];
	int m_kind; // +0x28, also read by sibling AptSaveLoad callbacks
};

class Rva0037BBED
{
public:
	Rva0037BBED();
	virtual ~Rva0037BBED();
	bool rva0037D0EF(UnicodeString name);

private:
	unsigned char m_04[0xE78];
};

class AptSaveLoad
{
public:
	void rva0043448C();
	void rva00433FDD();

private:
	unsigned char m_pad000[0x27C];
	int m_27C;
	int m_280;
};

void AptSaveLoad::rva0043448C()
{
	if (m_280)
	{
		Rva0037BBED check;
		if (check.rva0037D0EF(((AptSaveLoadPending *)m_280)->m_name))
			m_27C = 17;
		else
			rva00433FDD();
	}
	else
	{
		m_27C = 1;
	}
}
