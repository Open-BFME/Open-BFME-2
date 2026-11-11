// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1Rva005F54DA@@QAE@XZ @0x005F54DA 93B. Dtor calling get-gated unload then three clears.
// Evidence: 2 callers incl clear@Rva005F55FA, callees rowed get@Rva0057C22FByteChaseField
// rva0057C2CC clear@Rva000AD6F4 clear@Rva005F50B9, neighbours OwnedPointerResets /O1 /MD.
#include "ascii_string.h"

class Rva005F566A;
class Rva005F54DA;
#include <new>

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
__forceinline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}


#include "../../../Libraries/Source/Apt/AptCommandTarget.h"
#include "../../Include/Common/DelegateDesc.h"

class Rva00579E47 : public TreeHintRef00217D4C
{
public:
	Rva00579E47(const DelegateDesc &desc);
	// ?Rva00579E47::~Rva00579E47 present-unmatched
	__forceinline ~Rva00579E47() {}
};

class Rva0057C22FByteChaseField
{
public:
	unsigned char get() const;
};

#include "../../Include/Common/Rva0057C2CC.h"

class Rva0057C394 : public Rva0057C2CC
{
public:
	void rva0057C394(const AsciiString &name, const TreeHintRef00217D4C &callback);
};

#include "../../Include/Common/Rva000AD6F4.h"

class Rva005F501E
{
public:
	Rva005F501E(Rva005F54DA *owner, int side, void *inputA, void *inputB);
	~Rva005F501E();
private:
	char storage[0x34];
};

class Rva005F50B9
{
public:
	__forceinline Rva005F50B9(Rva005F501E *value) : m_ptr(value) {}
	Rva005F501E *m_ptr;
	void clear();
	__declspec(noinline) ~Rva005F50B9();
};

class Object;
#include "../../Include/Common/Rva00575674.h"

struct Rva005F4EE8Source;
class Rva005F4EE8
{
public:
	Rva005F4EE8(Rva005F4EE8Source *owner, int inputA, const AsciiString &inputB);
	virtual ~Rva005F4EE8();
private:
	void *m_impl;
	Rva005F54DA *m_owner;
};

class Rva005F54DA
{
public:
	Rva005F54DA(Rva005F566A *owner, Rva0057C394 *provider,
		void *firstA, void *firstB, void *secondA, void *secondB, void *callback);
	~Rva005F54DA();
	void rva005F4EED(void *inputA, void *inputB);
	void rva005F4BB4(Rva005F501E *handler);
private:
	Rva005F566A *m_owner;
	Rva0057C394 *m_p04;
	void *m_callback;
	Rva005F50B9 m_a0c;
	Rva005F50B9 m_a10;
	Rva000AD6F4 m_b14;
	bool m_enabled;
	__forceinline void loadFrame(DelegateDesc desc)
	{
		Rva00579E47 delegate(desc);
		m_p04->rva0057C394(AsciiString("StrategicArmyUnitSwapper.swf"), delegate);
	}
};

// WB names ArmyUnitSwapperDialog::Impl. Native fields and allocation extents
// prove this layout; source argument identities beyond the provider stay opaque.
Rva005F54DA::Rva005F54DA(Rva005F566A *owner, Rva0057C394 *provider,
	void *firstA, void *firstB, void *secondA, void *secondB, void *callback)
	: m_owner(owner), m_p04(provider), m_callback(callback),
	m_a0c(new Rva005F501E(this, 0, firstA, firstB)),
	m_a10(new Rva005F501E(this, 1, secondA, secondB)), m_enabled(true)
{
	loadFrame(DelegateDesc(this, &Rva005F54DA::rva005F4EED));
}

Rva005F54DA::~Rva005F54DA()
{
	if (((const Rva0057C22FByteChaseField *)m_p04)->get())
		m_p04->rva0057C2CC();
}

// Native callback has its own 108-byte EH boundary through RET 8.
// The +14 frame holder uses the existing one-pointer setter ABI.
void Rva005F54DA::rva005F4EED(void *inputA, void *inputB)
{
	if (m_b14.m_ptr == 0)
	{
		((Rva00575674 *)&m_b14)->rva00575674((Object *)new Rva005F4EE8((Rva005F4EE8Source *)this, (int)inputA, *(const AsciiString *)inputB));
		rva005F4BB4(m_a0c.m_ptr);
		rva005F4BB4(m_a10.m_ptr);
	}
}

// Native ctor/destructor EH cleanups5F53E6/5F54DA reach5F50B9 directly.
// This complete owning-pointer destructor is the verified clear worker twin:
// detach the pointer before its destructor and scalar deallocation.
Rva005F50B9::~Rva005F50B9()
{
 Rva005F501E *p=m_ptr;
 m_ptr=0;
 if(p) { p->Rva005F501E::~Rva005F501E(); ::operator delete(p); }
}
