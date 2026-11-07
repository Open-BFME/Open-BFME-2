// cl: /EHsc /MD
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva003529B0Clone.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ScriptGroup::ScriptGroup 0x003B410E (57B), ScriptGroup::rva00352a00
// 0x003B4147 (55B). Callee addresses are read off retail's call sites
// (reverse/symbols.csv). Only the placed bodies are carried; the donor's other
// definitions are omitted.
// The 0x00352A00 body allocates and copies a ScriptGroup (retail table
// 0x00C1F470, whose slot 2 getter returns "ScriptGroup"). The method name
// remains address-derived because retail exposes no named caller or vtable
// slot for this non-virtual copy operation.

class Xfer;

// The pair's two leaf chains (copy constructors and the first chain's clear
// rowed in Rva003BCopyLeaves.cpp and Rva003BClearLeaves.cpp).
class Rva003B31DF
{
public:
	Rva003B31DF(const Rva003B31DF &other);
	~Rva003B31DF() { clear(); }
	void clear();

private:
	Rva003B31DF *m_next;
	int m_a;
	int m_b;
};

class Rva003B3204
{
public:
	Rva003B3204(const Rva003B3204 &other);

private:
	Rva003B3204 *m_next;
	int m_a;
	int m_b;
};

class Rva003525E0Pair
{
public:
	Rva003525E0Pair(const Rva003525E0Pair &other);

private:
	Rva003B31DF *m_a;
	Rva003B3204 *m_b;
};

// ??0Rva003525E0Pair@@QAE@ABV0@@Z, retail 0x003B3FCD..0x003B4071 (164 bytes,
// EH, RET 4; Ghidra stops at its inline catch funclet, 108 bytes in): the
// pair copy the clone constructor 0x003B410E runs. Each chain is deep-copied
// when present; if the second copy throws, the first chain is cleared and
// freed and the exception rethrown.
Rva003525E0Pair::Rva003525E0Pair(const Rva003525E0Pair &other)
{
	m_a = other.m_a ? new Rva003B31DF(*other.m_a) : 0;
	try
	{
		m_b = other.m_b ? new Rva003B3204(*other.m_b) : 0;
	}
	catch (...)
	{
		delete m_a;
		throw;
	}
}

// ScriptGroup's pointer copy constructor 0x003B410E copies the list heads
// through 0x003B3FCD before it stores the vptr, so the heads are a
// non-virtual base under the vptr (Scripts.cpp's view, the scripts_orcondition
// shim, spells it Rva003B4071 for its teardown). Retail table 0x00C1F470: the deleting
// destructor, an empty loadPostProcess, GetSnapshotName and xfer. The
// destructor is the one Scripts.cpp emits (see the shim).
class ScriptGroup : public Rva003525E0Pair
{
public:
	ScriptGroup(const ScriptGroup *other)
		: Rva003525E0Pair(*static_cast<const Rva003525E0Pair *>(other))
	{
		m_isGroupActive = other->m_isGroupActive;
		m_isGroupSubroutine = other->m_isGroupSubroutine;
		m_hasWarnings = 0;
	}
	virtual ~ScriptGroup();

	ScriptGroup *rva00352a00() const;

protected:
	virtual void loadPostProcess() {}
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	char m_isGroupActive;		// +0x0C
	char m_isGroupSubroutine;	// +0x0D
	char m_hasWarnings;		// +0x0E
};

ScriptGroup *ScriptGroup::rva00352a00() const
{
	return new ScriptGroup(this);
}
