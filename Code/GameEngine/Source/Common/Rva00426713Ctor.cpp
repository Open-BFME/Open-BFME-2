// cl: /MD
// ??0Rva00426713@@QAE@XZ @0x00426713 36B evidence: baseConstruct 0x001B4E63 plus primary vtable 0x0083C408 plus secondary 0x0083C3F8 plus g_00BBB554 at +0x0C plus zero at +0x10
extern const void *const g_00BBB554[];
extern const void *const g_00C3C408[];
extern const void *const g_00C3C3F8[];

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) Rva00426713Base
{
public:
	Rva00426713Base() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual void unused();
	char m_flag;
	int m_value;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class __declspec(novtable) Rva00426713 : public Rva00426713Base
{
public:
	Rva00426713();
private:
	const void *m_0C;
	int m_10;
};

Rva00426713::Rva00426713()
{
	m_0C = (const void *)g_00BBB554;
	_ReadWriteBarrier();
	m_10 = 0;
	*(const void **)this = g_00C3C408;
	m_0C = (const void *)g_00C3C3F8;
}
