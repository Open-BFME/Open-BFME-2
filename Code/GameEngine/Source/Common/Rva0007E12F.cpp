// cl: /MD /EHsc
// ?rva0007E12F@Rva0007E12F@@QAEXXZ retail 0x0007E12F 76B lock DX8 thread then
// clear embedded reset-texture ref at +0xF8 and release Rva00083E5C holder
// at +0x100 via its 43B dual release. Evidence: chain calls 0x00083E5C;
// callers at 0x00066939 0x0008221E.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};
struct BfmeResetTextureRef
{
	void *m_ptr;
	void clear();
};
class Rva00083E5C
{
public:
	void rva00083E5C();
};
class Rva0007E12F
{
public:
	void rva0007E12F();
private:
	char _pad00[0xF8];
	BfmeResetTextureRef m_f8;
	char _padFC[4];
	Rva00083E5C *m_100;
};
void Rva0007E12F::rva0007E12F()
{
	BFMEDX8DeviceLock guard;
	if (m_f8.m_ptr != 0)
		m_f8.clear();
	Rva00083E5C *p = m_100;
	if (p != 0)
		p->rva00083E5C();
}
