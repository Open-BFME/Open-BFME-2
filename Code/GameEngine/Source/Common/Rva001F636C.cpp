// cl: /O1 /MD /EHsc
// ?rva001F636C@Rva001F636C@@QAEXXZ @0x001F636C 93B evidence: chain calls just-landed 0x00152D1C with 4; callers none; prev Rva001F4D22Dtor next Rva001F63C9Erase.
// Evidence: callees rowed 0x001F58D4 lock 0x00152D1C assert virtual slot2; prev/next Common WWLib.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class Rva001F58D4
{
public:
	void rva001F58D4();
};

class Rva00152D1CObj
{
public:
	void rva152d1c(int n);
};

class Rva001F636C
{
public:
	void rva001F636C();
	virtual void v00();
	virtual void v01();
	virtual void v02();
private:
	char m_pad[0x7C];
	Rva00152D1CObj *m_80;
	bool m_84;
};

void Rva001F636C::rva001F636C()
{
	((Rva001F58D4 *)this)->rva001F58D4();
	if (m_84) {
		v02();
		m_84 = 0;
	}
	Rva00152D1CObj **pp = &m_80;
	if (*pp) {
		BFMEDX8DeviceLock guard;
		(*pp)->rva152d1c(4);
	}
}
