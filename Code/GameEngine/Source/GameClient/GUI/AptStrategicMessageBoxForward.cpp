// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?method@Rva0054CBEFTarget@@QAEXH@Z retail 0x0054CBEF, 8 B, and
// ??1Rva0057417E@@QAE@XZ retail 0x0057417E, 20 B.
// Target evidence: 0x0054CBEF loads the object at +0x04 and tail-jumps to
// 0x0054C99A with the caller's argument (the pin name its callers use; they
// all call it on AptStrategicMessageBox::s_instance, 0x00A05FAC, the name
// the data ledger carries there). 0x0057417E, the pointee destructor of the
// owning-pointer reset 0x0042C1DF, makes that call with 0 when its byte at
// +0x04 is set (no null test, unlike the 0x005CF9FF siblings). The forwarder
// is noinline so the destructor calls it as retail does. The +0x04 object's
// class and the destructor's owner are address-named.
class Rva0057417E;

class AptStrategicMessageBox
{
private:
	static AptStrategicMessageBox *s_instance;	// 0x00A05FAC
	friend class Rva0057417E;
};

class Rva0054C99AImpl
{
public:
	void rva0054C99A(int arg);			// 0x0054C99A
};

class Rva0054CBEFTarget
{
public:
	__declspec(noinline) void method(int arg);

private:
	void *m_00;
	Rva0054C99AImpl *m_impl;			// +0x04
};

void Rva0054CBEFTarget::method(int arg)
{
	m_impl->rva0054C99A(arg);
}

class Rva0057417E
{
public:
	~Rva0057417E();

private:
	void *m_00;
	bool m_active;					// +0x04
};

Rva0057417E::~Rva0057417E()
{
	if (m_active)
		((Rva0054CBEFTarget *)(void *)AptStrategicMessageBox::s_instance)->method(0);
}
