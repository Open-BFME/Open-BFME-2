// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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

class Rva00433FDD
{
public:
	void rva00433FDD();
};

class AptSaveLoad
{
public:
	void rva0043448C();

private:
	unsigned char m_pad000[0x27C];
	int m_state;
	AptSaveLoadPending *m_pending;
};

void AptSaveLoad::rva0043448C()
{
	if (m_pending)
	{
		Rva0037BBED check;
		if (check.rva0037D0EF(m_pending->m_name))
			m_state = 17;
		else
			((Rva00433FDD *)this)->rva00433FDD();
	}
	else
	{
		m_state = 1;
	}
}
