// cl: /O2 /MD
// Dynamic initializer of a file-scope object whose inline constructor only
// sets its vptr, so the compiler writes that vptr into the object's static
// data and the initializer keeps nothing but the atexit registration of its
// destructor. Target evidence: game.dat's __xc_a table points at 0x007B5DE0,
// which registers the matched cleanup 0x007B9B90; that cleanup is the inlined
// destructor storing the class table 0x00CE3168 into 0x00DD828C, the table
// the rowed ??_GRva006655B0@@UAEPAXI@Z stores, and .data already holds that
// table at 0x00DD828C. Rva006655E0Get (0x006655E0) returns the object's
// address. /O2: at /O1 the constructor is called, not folded. The class keeps
// the ledger's address-derived name; the owning TU and object name are not
// established.

class Rva006655B0
{
public:
	Rva006655B0() {}
	virtual ~Rva006655B0() {}
};

static Rva006655B0 s_rva006655B0;
