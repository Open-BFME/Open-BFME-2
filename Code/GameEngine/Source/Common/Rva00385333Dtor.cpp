// cl: /MD /EHs
// ??1Rva00385333@@QAE@XZ @0x00385333 62B derived dtor: frees +0x19c via rowed
// _free 0x00030830 when non-null then base ??1Rva003844D7 at +0 rowed in
// Rva003844D7Dtor.cpp. Callers 0x3853AA 0x555FD3 unclaimed thiscall.
// No vptr store so non-virtual QAE. Precedent Rva002E1F42Dtor.cpp.
extern "C" void __cdecl free(void *p);

class Rva003844D7
{
public:
	~Rva003844D7();
private:
	char m_pad[0x190];
};

class Rva00385333 : public Rva003844D7
{
public:
	~Rva00385333();
private:
	char m_pad2[0xC];
	char *m_19c;
};

Rva00385333::~Rva00385333()
{
	if (m_19c)
		free(m_19c);
}
