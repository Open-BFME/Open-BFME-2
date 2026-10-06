// ??0Rva00588FFA@@QAE@PAVThing@@PBVModuleData@@@Z
// cl: /DNDEBUG /MD
//
// ??0Rva00588FFA@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00588FFA, 53 bytes.
// Behavior module base ctor over rowed BehaviorModule 0x253330. Writes the
// member at +0x10 (0x00C6FFFC, then the folded vtable slot 0x00C4A50C), and
// zeroes +0x14, then installs the folded vtable slots 0x00C700C4 at +0 and
// 0x00C70008 at +0xC. Sole caller is PillageModule ctor 0x484F0D.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Thing;
class ModuleData;

extern const void *const g_008700C4[];
extern const void *const g_00870008[];
extern const void *const g_0084A50C[];
extern const void *const g_0086FFFC[];

class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data);
private:
	unsigned char m_pad[0x10];
};

class Rva00588FFA : public BehaviorModule
{
public:
	Rva00588FFA(Thing *thing, const ModuleData *data);

private:
	const void *m_10; // +0x10, init g_0086FFFC then overwritten g_0084A50C
	int m_14; // +0x14, and-zeroed
};

Rva00588FFA::Rva00588FFA(Thing *thing, const ModuleData *data)
	: BehaviorModule(thing, data)
{
	*(volatile unsigned *)&m_10 = (unsigned)g_0086FFFC;
	_ReadWriteBarrier();
	m_14 = 0;
	*(const void **)this = g_008700C4;
	*(const void **)((char *)this + 0x0C) = g_00870008;
	*(const void **)((char *)this + 0x10) = g_0084A50C;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00870008@@3QBQBXB=??_7Rva00484F5D@@6BMiBase1@@@")
#pragma comment(linker, "/alternatename:?g_0084A50C@@3QBQBXB=??_7Rva00484EF4@@6B@")
