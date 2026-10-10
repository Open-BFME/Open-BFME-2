// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva005F3FFC@@UAE@XZ @0x005F3FFC 126B (the pin keeps the non-virtual
// spelling). Opaque dtor: when the +0x10 reference is held and the +0x08
// object's slot-3 getter (folded forwarder 0x005CB265) still answers it, that
// object is told through 0x005CB260; the +0x0C reference's target drops this
// object from its list at +8 through the rowed erase 0x002B7250; the two
// reference holders release (ReleaseTreeHintRef00217D4C) and the empty base
// dtor is inline. The +0x10 reference is read once into a local, as in
// Rva005E29CDDtor.cpp. Identity of the class is unproven.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva004F6966
{
public:
	Rva004F6966() : m_ptr(0) {}
	~Rva004F6966()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
	void *m_ptr;
};

struct Rva005F3FFCOwner
{
	char m_pad[8];
	Rva002B7250 m_holder;
};

class Rva005F3EE3
{
public:
	virtual ~Rva005F3EE3() {}
};

class Rva005F3FFC : public Rva005F3EE3
{
public:
	virtual ~Rva005F3FFC();
private:
	int m_04;
	Rva005CB265 *m_08;
	Rva004F6966 m_0C;
	Rva004F6966 m_10;
};

Rva005F3FFC::~Rva005F3FFC()
{
	void *current = m_10.m_ptr;
	if (current)
	{
		if (m_08->Rva005CB265::rva005CB265() == (int)current)
			((Rva005CB260 *)m_08)->rva005CB260();
	}
	Rva005F3FFCOwner *owner = (Rva005F3FFCOwner *)m_0C.m_ptr;
	if (owner)
		owner->m_holder.rva002B7250((CreateAHeroData *)this);
}
