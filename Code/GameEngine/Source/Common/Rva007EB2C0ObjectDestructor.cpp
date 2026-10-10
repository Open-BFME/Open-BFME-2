// 0x007EB2C0: reset the global object and release its guarded resources.
// The barrier preserves retail's store-before-flag-read instruction order.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class T_007ea120
{
public:
	virtual void vslot0(int value);
	void m(void);
};

struct Rva0130A588State
{
	T_007ea120 *m_obj;
	char m_flagC;
	char m_flagD;
};

extern Rva0130A588State g_Va0130A588;

extern void Rva007EB830Release(void);
extern void Rva007F0060(void);

class Rva007EB2C0Object
{
public:
	Rva007EB2C0Object();
	virtual ~Rva007EB2C0Object();
};
// ??0Rva007EB2C0Object@@QAE@XZ @0x00658150 9B: the default constructor, storing the
// class's own vtable (VA 0x00CE1514) and returning this.
Rva007EB2C0Object::Rva007EB2C0Object()
{
}

Rva007EB2C0Object::~Rva007EB2C0Object()
{
	if (g_Va0130A588.m_obj)
	{
		g_Va0130A588.m_obj->m();
		if (g_Va0130A588.m_obj)
			g_Va0130A588.m_obj->vslot0(1);
		g_Va0130A588.m_obj = 0;
	}
	_ReadWriteBarrier();

	if (g_Va0130A588.m_flagD)
		Rva007EB830Release();

	if (g_Va0130A588.m_flagC)
		Rva007F0060();
}
// ?g_Va0130A588@@3URva0130A588State@@A: the global at VA 0xe09fa4 is ?g_Va0130A588@@3PAVT_007ea120@@A.
#pragma comment(linker, "/alternatename:?g_Va0130A588@@3URva0130A588State@@A=?g_Va0130A588@@3PAVT_007ea120@@A")
