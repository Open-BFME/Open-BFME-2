// cl: /EHsc /MD
// ??1Rva00567960@@UAE@XZ @0x00567960 60B
// Evidence: MI dtor calls second-base ??1Rva005C7CBB on +8; final store base vtable 0x007C6F20 via empty inline base; caller 0x00567D54 deleting dtor.
class Rva005C7CBB
{
public:
	virtual ~Rva005C7CBB();
};

// Two levels of base: the dtor's last store is the root's folded abstract
// vtable 0x00BC6F20 (__purecall in slot 2), while the ctor at 0x00567CCD
// builds the +0 base with 0x00C7A630, Rva00567960Base's own vtable; the
// intermediate store between the two is dead and MSVC drops it.
class Rva00567960Root
{
public:
	virtual ~Rva00567960Root() {}
};

class Rva00567960Base : public Rva00567960Root
{
public:
	virtual ~Rva00567960Base() {}
	int m_4;
};

class Rva00567960 : public Rva00567960Base, public Rva005C7CBB
{
public:
	virtual ~Rva00567960();
};

Rva00567960::~Rva00567960()
{
}
