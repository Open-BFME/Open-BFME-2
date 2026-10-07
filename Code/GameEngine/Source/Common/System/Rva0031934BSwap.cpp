// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Reconstruction of the 134B helper swapper at 0x0031934B: look the key
// up in the global bucket table, destroy-and-free the old +0x88 helper
// through its slot 0 and operator delete, then on a payload hit build a
// fresh 96-byte helper with explicit operator new plus init call under
// try/catch and store it (null otherwise), finishing with the sibling
// refresh. Callees resolve via rows and pins; the slot meanings and the
// Fresh layout are unproven beyond index, arity and size.
#include "ascii_string.h"

void *operator new(unsigned int size);
void operator delete(void *block);

class Rva002130F6
{
public:
	void *rva002130F6(const AsciiString *key);
};

// Bind to the existing data-ledger owner; keep the retail access view local.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Rva0031934BHelper
{
public:
	virtual void *slot0(int zero) = 0;
};

class Rva0031934BOwner;

class Rva003FE412Fresh
{
public:
	Rva003FE412Fresh(void *payload, Rva0031934BOwner *owner);
private:
	unsigned char m_pad[0x60];
};

class Rva0031934BOwner
{
public:
	void rva0031934B(const AsciiString *key);
	void rva00318EC0();
private:
	unsigned char m_pad[0x88];
	Rva0031934BHelper *m_88;
};

void Rva0031934BOwner::rva0031934B(const AsciiString *key)
{
	void *payload = ((Rva002130F6 *)TheLivingWorldManager)->rva002130F6(key);
	Rva0031934BHelper *helper = m_88;
	operator delete(helper != 0 ? helper->slot0(0) : 0);
	if (payload == 0)
	{
		m_88 = 0;
	}
	else
	{
		m_88 = (Rva0031934BHelper *)new Rva003FE412Fresh(payload, this);
	}
	rva00318EC0();
}
