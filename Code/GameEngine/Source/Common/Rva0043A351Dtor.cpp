// cl: /DNDEBUG /MD /EHsc /O1
// Target evidence: the deleting wrapper at 0x0043AE0C calls the dtor pinned at
// 0x0043A351; its 69-byte body installs vtable 0x00C3D478, calls the matched
// cleanup at 0x0043A31E, calls Shell at VA 0x00E01E48 with true, then calls the
// matched 0x00355D66 destructor on the same pointer. The neutral class view
// models that final call as a base at offset zero for code generation; the
// underlying class identity remains unresolved.
// The Shell method name is carried by its existing partial source and caller
// evidence; the newly admitted pin only binds that call target.

class Shell
{
public:
	void rva0035C7CF(bool flag);
};

extern Shell *TheShell;
extern void Rva0043A31ECleanup(void);

class Rva00355D66
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
};

class Rva0043A351 : public Rva00355D66
{
public:
	virtual ~Rva0043A351();
};

Rva0043A351::~Rva0043A351()
{
	Rva0043A31ECleanup();
	TheShell->rva0035C7CF(true);
}
