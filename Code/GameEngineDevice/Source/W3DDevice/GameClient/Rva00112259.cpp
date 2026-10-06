// cl: /DNDEBUG /MD /EHsc /Ob2
//
// Target facts from retail 0x00112259: the 56-byte Ghidra interval begins
// with the MSVC EH prolog call, locks through 0x0011F520, calls the rowed
// clear helper at 0x00111F0E on the same this pointer, stores 1 at this+0x62,
// and releases through 0x00120F50. The body ends with leave/ret at 0x00112290;
// the next Ghidra start is 0x00112291. The preceding 41-byte neighbor ends at
// 0x00112258.
//
// The lock object's scope is a structural inference from the EH state and
// lock/release sequence. The owning class and method purpose remain unknown;
// names and the +0x62 field label are address-derived.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

struct Rva00112259DeviceLock
{
	Rva00112259DeviceLock() { BFME_DX8_Thread_Lock(); }
	~Rva00112259DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class Rva00111F0E
{
public:
	void rva00111F0E();
};

class Rva00112259
{
public:
	void rva00112259();

private:
	char m_pad00[0x62];
	bool m_62;
};

void Rva00112259::rva00112259()
{
	Rva00112259DeviceLock lock;
	((Rva00111F0E *)this)->rva00111F0E();
	m_62 = true;
}
