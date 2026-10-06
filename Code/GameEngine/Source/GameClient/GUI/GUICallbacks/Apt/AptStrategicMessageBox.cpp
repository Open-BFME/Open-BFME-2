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

private:
	static AptStrategicMessageBox *s_instance;
};

// AptStrategicMessageBox::AptStrategicMessageBox, retail 0x0054C770.
AptStrategicMessageBox::AptStrategicMessageBox()
	: Rva0054D2CF(13, "StrategicMessageBox")
{
	s_instance = this;
}

// AptStrategicMessageBox::CreateSingleton, retail 0x0054C7C7.
void AptStrategicMessageBox::CreateSingleton()
{
	s_instance = new AptStrategicMessageBox;
}
