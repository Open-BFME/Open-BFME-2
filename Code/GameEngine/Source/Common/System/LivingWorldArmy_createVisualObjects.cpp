// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/bfmealloc/stl /ICode/Libraries/Include/Lib
// stlport
// Reconstruction of the 134B helper swapper at 0x0031934B: look the key
// up in the global bucket table, destroy-and-free the old +0x88 helper
// through its slot 0 and operator delete, then on a payload hit build a
// fresh 96-byte helper with explicit operator new plus init call under
// try/catch and store it (null otherwise), finishing with the sibling
// refresh. Callees resolve via rows and pins; the slot meanings and the
// Fresh layout are unproven beyond index, arity and size.
#define _CRTIMP
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

#include <new>

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

// The 0x60 helper's constructor 0x003FE412 is rowed as Rva003FE58A(void *, void *).
class Rva003FE58A
{
public:
	Rva003FE58A(void *payload, void *owner);
private:
	unsigned char m_pad[0x60];
};

class Xfer;
struct Rva00318EC0Colors;
class Rva00318EC0Target;
struct BfmeVectorRecord00319C84
{
	virtual ~BfmeVectorRecord00319C84();
	char m_body[12];
	BfmeVectorRecord00319C84();
	BfmeVectorRecord00319C84(const BfmeVectorRecord00319C84 &);
};

struct LivingWorldArmy
{
public:
	void rva00318EC0();
	void KillSummaryEntry(int value);
	void createVisualObjects(const AsciiString *key);
	virtual void xfer(Xfer *xfer);
	char pad04[0x18 - 0x04];
	AsciiString name18;
	AsciiString name1C;
	int owner20;
	AsciiString name24;
	AsciiString name28;
	int region2C;
	int value30;
	unsigned int pos34[2];
	unsigned int pos3C[2];
	unsigned int pos44[2];
	int source4C;
	char pad50[4];
	int owner54;
	bool flag58;
	bool flag59;
	char pad5A[2];
	float value5C;
	unsigned int audio60;
	char pad64;
	bool flag65;
	char pad66[2];
	UnicodeString text68;
	UnicodeString text6C;
	int iconSize70;
	bool flag74;
	bool flag75;
	char pad76[2];
	Rva00318EC0Colors *m_colors78;
	_STL::vector<BfmeVectorRecord00319C84> records7C;
	Rva00318EC0Target *m_target88;
	int value8C;
};

void LivingWorldArmy::createVisualObjects(const AsciiString *key)
{
	void *payload = ((Rva002130F6 *)TheLivingWorldManager)->rva002130F6(key);
	Rva0031934BHelper *helper = (Rva0031934BHelper *)m_target88;
	operator delete(helper != 0 ? helper->slot0(0) : 0);
	if (payload == 0)
	{
		m_target88 = 0;
	}
	else
	{
		m_target88 = (Rva00318EC0Target *)new Rva003FE58A(payload, this);
	}
	rva00318EC0();
}
