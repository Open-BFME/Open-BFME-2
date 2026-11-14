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

extern T_007ea120 *g_Va0130A588;
// Retail reads the one-byte flags at 0x00A09FA9 and 0x00A09FA8 (0x0065828F, 0x0065829D); they are their own
// globals (Rva007EB270Shutdown.cpp, verified data rows), not bytes of g_Va0130A588 (0x00A09FA4, 4 bytes).
extern unsigned char g_createdDefaultAllocator;
extern unsigned char g_createdDefaultDiagReporter;

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
	if (g_Va0130A588)
	{
		g_Va0130A588->m();
		if (g_Va0130A588)
			g_Va0130A588->vslot0(1);
		g_Va0130A588 = 0;
	}
	_ReadWriteBarrier();

	if (g_createdDefaultDiagReporter)
		Rva007EB830Release();

	if (g_createdDefaultAllocator)
		Rva007F0060();
}
