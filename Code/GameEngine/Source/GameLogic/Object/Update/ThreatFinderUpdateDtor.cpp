// cl: /DNDEBUG /MD /EHsc
// ??1ThreatFinderUpdate@@UAE@XZ @0x003ECF64 (88B): virtual dtor that
// restores the primary plus +0x0C/+0x10 vtable slots via the shared
// UpdateModule base view (vptrs at +0 +0x0C +0x10 size 0x20) deletes the +0x20
// heap object through its rowed Rva003ECDB7 dtor plus rowed operator delete
// then calls the rowed UpdateModule base dtor 0x0024A797. Called by the
// matched deleting dtor 0x003ED0A8. Pool key 0x003ECCD6 plus ctor 0x003ECCA2
// prove the class.
class Rva003ECDB7Object
{
public:
	~Rva003ECDB7Object();
};

// Base view matching Common/Rva0024A797DeletingDtor.cpp: vptrs at +0, +0xC,
// +0x10; 0x20 bytes (copied from SpecialAbilityUpdateDtor.cpp).
class Rva0049B47C
{
public:
	virtual ~Rva0049B47C() throw();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class PrimaryP451F45 : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP451F45() {}
};

class Rva0024A797_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class UpdateModule : public PrimaryP451F45, public Rva0024A797_B2
{
public:
	virtual ~UpdateModule();
};

class ThreatFinderUpdate : public UpdateModule
{
public:
	virtual ~ThreatFinderUpdate();

private:
	Rva003ECDB7Object *m_heap;
};

ThreatFinderUpdate::~ThreatFinderUpdate()
{
	delete m_heap;
}
