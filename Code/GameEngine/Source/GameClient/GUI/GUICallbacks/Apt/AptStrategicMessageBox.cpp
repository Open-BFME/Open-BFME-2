// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// AptStrategicMessageBox.cpp -- AptStrategicMessageBox singleton creation
// recovered from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug
// build names the function and asserts s_instance == NULL before creating it;
// retail supplies the bytes. The object is 8 bytes (operator new size) and the
// instance pointer lives at 0x00E05FAC (target evidence). The ctor passes
// 13 and the screen name "StrategicMessageBox" to its base, whose ctor
// (0x0054D286) and dtor (0x0054D2CF) are placeholder-named in the ledger.
#include "ascii_string.h"

class Rva0054D2CF
{
public:
	Rva0054D2CF(int id, const AsciiString &name);	// 0x0054D286
	virtual ~Rva0054D2CF();

private:
	int m_field04;
};

class AptStrategicMessageBox : public Rva0054D2CF
{
public:
	AptStrategicMessageBox();			// 0x0054C770
	virtual ~AptStrategicMessageBox();

	static void CreateSingleton();
	static void rva0054C729();

private:
};

extern int g_Va00E05FAC;

// Address-derived view of the virtual entry called by the singleton release
// body. Its original method identity remains unresolved.
class Rva0054C729Vtable
{
public:
	virtual void *rva0054C729VtableSlot0(unsigned int flags);
};

// AptStrategicMessageBox::AptStrategicMessageBox, retail 0x0054C770.
AptStrategicMessageBox::AptStrategicMessageBox()
	: Rva0054D2CF(13, "StrategicMessageBox")
{
	g_Va00E05FAC = (int)this;
}

// AptStrategicMessageBox::CreateSingleton, retail 0x0054C7C7.
void AptStrategicMessageBox::CreateSingleton()
{
	g_Va00E05FAC = (int)new AptStrategicMessageBox;
}

// ?rva0054C729@AptStrategicMessageBox@@SAXXZ, retail 0x0054C729. Target
// evidence: this 25-byte body releases the singleton through its vtable slot
// zero and operator delete at 0x0002FD60. The rowed dtor at 0x0054C742 clears
// the same singleton global before chaining to the base dtor. Original method
// name remains unresolved.
void AptStrategicMessageBox::rva0054C729()
{
	void *released = g_Va00E05FAC
		? ((Rva0054C729Vtable *)(void *)g_Va00E05FAC)->rva0054C729VtableSlot0(0)
		: 0;
	::operator delete(released);
}
