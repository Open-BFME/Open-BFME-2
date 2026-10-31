// cl: /O1 /DNDEBUG /MD
//
// ?rva002E0648@Rva002E0648Owner@@QAEXPAX@Z @0x002E0648 32B and
// ?rva002E07CC@Rva002E0648Owner@@QAEXXZ @0x002E07CC 34B: +0x48/+0x4C member
// dispatchers (thiscall). 0x002E0648 forwards (this, arg1) to the pinned
// 0x004FB222 on the +0x4C member, then arg1 to the pinned 0x000366F0 on the
// +0x48 member. 0x002E07CC resolves the +0x48 member through the landed
// ?find@Rva002E18C3Lookup@@QAEPAVAsciiString@@ABV2@@Z row on the g_00A03140
// lookup object and, when found, forwards (this, found) to 0x004FB222 on
// +0x4C. Honest address-derived names.

class AsciiString;

class Rva002E18C3Lookup
{
public:
	AsciiString *find(AsciiString const &x);
};

template <class T> class StringBase
{
public:
	void set(const StringBase &other);
};

struct Rva004FB303Target;
class Rva004FB222Owner
{
public:
	void rva004FB222(Rva004FB303Target *target, int value);
};

struct Rva002E0648M48
{
	char m_pad[4]; // +0x48..+0x4C opaque
};

struct Rva002E0648M4C
{
};

extern class Rva002E18C3Lookup *TheLivingWorldAITemplateStore;

class Rva002E0648Owner
{
public:
	void rva002E0648(void *source);
private:
	char m_pad00[0x48]; // +0x00..+0x48 unclaimed
	Rva002E0648M48 m_m48; // +0x48
	Rva002E0648M4C m_m4C; // +0x4C
};

// ?rva002E0648@Rva002E0648Owner@@QAEXPAX@Z
void Rva002E0648Owner::rva002E0648(void *source)
{
	((Rva004FB222Owner *)&m_m4C)->rva004FB222((Rva004FB303Target *)this, (int)source);
	((StringBase<char> *)&m_m48)->set(*(const StringBase<char> *)source);
}

// ?rva002E07CC@Rva002E0648Owner@@QAEXXZ
