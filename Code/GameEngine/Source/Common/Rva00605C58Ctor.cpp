// cl: /MD
//
// ??0Rva00605C6A@@QAE@XZ @0x00605C58 18B.
// Chain from 0x00605C91: calls rowed base ctor then stores vtable 0x0087AAE0.
// Evidence: callee 0x00605C91 ??0Rva00605C91@@QAE@XZ row, vtable VA 0x00C7AAE0,
// dtor 0x00605C6A ??1Rva00605C6A@@UAE@XZ same vtable, caller 0x00604B1F.

#include "../../Include/Common/LocalFile.h"

class Rva00605C91 : public LocalFile
{
public:
	Rva00605C91();
	virtual ~Rva00605C91();
};

// The verified destructor at 0x00605C6A binds the compiler table to
// native RVA 0x0087AAE0. LocalFile supplies all 18 slots.

class Rva00605C6A : public Rva00605C91
{
public:
	Rva00605C6A();
	virtual ~Rva00605C6A();
};

Rva00605C6A::Rva00605C6A()
	: Rva00605C91()
{
}
