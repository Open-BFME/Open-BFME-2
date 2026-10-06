// cl: /EHsc /MD
// ?rva000E65B1@Rva000E6AC0@@QAEXXZ 0x000E65B1 138B
// Rva000E6AC0 reset: DX8 lock, clear texture refs at +0x38/+0x3C, reset trees
// at +0x40/+0x68 via rowed rva00170EBC(false), zero the int ranges at
// +0x10/+0x14 and +0x28/+0x2C, refresh float at +0x5BC from TheGameEngine.
// Evidence: callees rowed; callers at 0x000E701C and 0x000EA268; member offsets
// match rowed ctor 0x000E6AC0 (Rva000E6AC0Ctor.cpp).

void BFME_DX8_Thread_Lock(void);
bool BFME_DX8_Thread_Assert(void);

class BfmeResetTextureRef
{
public:
	void clear();
};

class Rva00170EBC
{
public:
	void rva00170EBC(bool b);
};

class GameEngine
{
public:
	char m_pad[0x38];
	int m_38;
};

extern GameEngine *TheGameEngine;

class Rva000E6AC0
{
public:
	void rva000E65B1();
private:
	char _pad00[0x10];
	int *_p10;
	int *_p14;
	char _pad18[0x10];
	int *_p28;
	int *_p2c;
	char _pad30[0x38 - 0x30];
	char _pad38[0x5BC - 0x38];
	float _f5bc;
};

struct DX8Guard
{
	DX8Guard() { BFME_DX8_Thread_Lock(); }
	~DX8Guard() { BFME_DX8_Thread_Assert(); }
};

void Rva000E6AC0::rva000E65B1()
{
	DX8Guard _guard;
	((BfmeResetTextureRef *)((char *)this + 0x38))->clear();
	((BfmeResetTextureRef *)((char *)this + 0x3C))->clear();
	((Rva00170EBC *)((char *)this + 0x40))->rva00170EBC(false);
	((Rva00170EBC *)((char *)this + 0x68))->rva00170EBC(false);
	int *e0 = _p14;
	for (int *p = _p10; p != e0; ++p)
		*p = 0;
	int *e1 = _p2c;
	for (int *p = _p28; p != e1; ++p)
		*p = 0;
	if (TheGameEngine != 0)
		_f5bc = (float)TheGameEngine->m_38;
}
