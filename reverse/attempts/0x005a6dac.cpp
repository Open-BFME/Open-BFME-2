// ?rva005A6DAC@Rva005A6DAC@@QAE_NIGPAH@Z
// partial score=0.97 date=2026-10-05
// ?rva005A6DAC@Rva005A6DAC@@QAE_NIGPAH@Z
// partial score=0.97 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva005A6DAC@Rva005A6DAC@@QAE_NIGPAH@Z @0x005A6DAC 206B: Transport slot binder with 1s UDP Bind retry
// Evidence: callers at 0x005A84C4 0x005A852C 0x005A8609 pass port slot vals; slot>=8 check and Transport at +4 match Transport 8-slot layout rowed 0x004D51A7; Bind pin 0x00594B56 Rva005948F5 ctor row 0x005948F5 UDPDrain dtor row 0x00594918 new 0x0002FDA0 delete 0x0002FD60 timeGetTime IAT; 0x20-byte new and 1000ms timeout loop match retail.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

class Rva005948F5
{
public:
	Rva005948F5();

private:
	char m_pad[0x20];
};

class UDP
{
public:
	int Bind(unsigned int addr, unsigned short port);
};

class UDPDrain
{
public:
	~UDPDrain();
};

class Transport
{
public:
	void clearSlot_Rva004D5133(unsigned short slot);
	void rva004D51A7(void *obj, unsigned short slot, int *vals);
};

class Rva005A6DAC
{
public:
	bool rva005A6DAC(unsigned int port, unsigned short slot, int *vals);

private:
	int m_00;
	Transport *m_04;
	char m_pad08[0x14];
	unsigned int m_1C;
};

// ?rva005A6DAC@Rva005A6DAC@@QAE_NIGPAH@Z present-unmatched
bool Rva005A6DAC::rva005A6DAC(unsigned int port, unsigned short slot, int *vals)
{
	if (slot >= 8)
		return false;
	if (m_04 == 0)
		return false;
	Rva005948F5 * volatile tmp = new Rva005948F5;
	int status = -1;
	if (tmp == 0)
		return false;
	unsigned long start = timeGetTime();
	do {
		if (timeGetTime() - start >= 1000)
			break;
		status = ((UDP *)tmp)->Bind(m_1C, port);
	} while (status != 0);
	if (status != 0) {
		((UDPDrain *)tmp)->~UDPDrain();
		operator delete((void *)tmp);
		return false;
	}
	m_04->clearSlot_Rva004D5133(slot);
	m_04->rva004D51A7(tmp, slot, vals);
	return true;
}
