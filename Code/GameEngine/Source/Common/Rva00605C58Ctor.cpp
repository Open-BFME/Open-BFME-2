// cl: /O1 /MD
//
// ??0Rva00605C6A@@QAE@XZ @0x00605C58 18B.
// Chain from 0x00605C91: calls rowed base ctor then stores vtable 0x0087AAE0.
// Evidence: callee 0x00605C91 ??0Rva00605C91@@QAE@XZ row, vtable VA 0x00C7AAE0,
// dtor 0x00605C6A ??1Rva00605C6A@@UAE@XZ same vtable, caller 0x00604B1F.

class ModuleData
{
public:
	ModuleData();
	virtual ~ModuleData();
};

class Rva00605C91 : public ModuleData
{
public:
	Rva00605C91();
};

extern const void *const g_00C7AAE0[];

class Rva00605C6A : public Rva00605C91
{
public:
	Rva00605C6A();
};

Rva00605C6A::Rva00605C6A()
	: Rva00605C91()
{
	*(const void **)this = g_00C7AAE0;
}
