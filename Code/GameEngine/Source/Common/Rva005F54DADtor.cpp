// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1Rva005F54DA@@QAE@XZ @0x005F54DA 93B. Dtor calling get-gated unload then three clears.
// Evidence: 2 callers incl clear@Rva005F55FA, callees rowed get@Rva0057C22FByteChaseField
// rva0057C2CC clear@Rva000AD6F4 clear@Rva005F50B9, neighbours OwnedPointerResets /O1 /MD.
#include "ascii_string.h"

class Rva005F566A;
class Rva005F54DA;
void *__cdecl operator new(unsigned int size) throw();

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *pointer;
};

class AptCommandTarget {};
struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(void *, void *))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)),
		m_method(reinterpret_cast<void (AptCommandTarget::*)(void *, void *)>(method)) {}
	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(void *, void *);
};

class Rva00579E47 : public TreeHintRef00217D4C
{
public:
	Rva00579E47(const DelegateDesc &desc);
	// ?Rva00579E47::~Rva00579E47 present-unmatched
	__forceinline ~Rva00579E47()
	{
		if (pointer) ReleaseTreeHintRef00217D4C(pointer);
	}
};

class Rva0057C22FByteChaseField
{
public:
	unsigned char get() const;
};

class Rva0057C2CC
{
public:
	void rva0057C2CC();
};

class Rva0057C394 : public Rva0057C2CC
{
public:
	void rva0057C394(const AsciiString &name, const TreeHintRef00217D4C &callback);
};

class Rva000AD6F4
{
public:
	__forceinline Rva000AD6F4() : m_ptr(0) {}
	void clear();
	~Rva000AD6F4() { clear(); }
private:
	void *m_ptr;
};

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
	~Rva005F50B9() { clear(); }
};

class Rva005F54DA
{
public:
	Rva005F54DA(Rva005F566A *owner, Rva0057C394 *provider,
		void *firstA, void *firstB, void *secondA, void *secondB, void *callback);
	~Rva005F54DA();
	void rva005F4EED(void *inputA, void *inputB);
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
