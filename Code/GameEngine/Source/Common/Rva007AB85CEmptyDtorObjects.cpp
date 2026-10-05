// cl: /O1 /MD
// Static-initializer strip: file-scope objects whose class has an empty
// inline constructor and an empty user-declared destructor. The constructor
// leaves nothing to run, so each dynamic initializer is only
// atexit(cleanup), and the cleanup the compiler emits for the empty
// destructor is a lone `ret`. Target evidence: game.dat's __xc_a table points
// at each 12-byte initializer below; each pushes the address of a one-byte
// `ret` in the atexit-cleanup region (0x007B6xxx..0x007B9xxx) that no row
// claimed. Nothing in either body names the object, its class or its owning
// TU, so one address-named empty class stands in for every retail class and
// each object is named from its initializer's address.

struct Rva007AB85CEmptyDtor
{
	Rva007AB85CEmptyDtor() {}
	~Rva007AB85CEmptyDtor() {}
};

// 0x007AB85C (12B) registers the 1-byte cleanup 0x007B686E.
static Rva007AB85CEmptyDtor s_rva007AB85C;

// 0x007ABCDB (12B) registers the 1-byte cleanup 0x007B6AE6.
static Rva007AB85CEmptyDtor s_rva007ABCDB;

// 0x007AC09E (12B) registers the 1-byte cleanup 0x007B6C13.
static Rva007AB85CEmptyDtor s_rva007AC09E;

// 0x007AC0AA (12B) registers the 1-byte cleanup 0x007B6C14.
static Rva007AB85CEmptyDtor s_rva007AC0AA;

// 0x007ACA0C (12B) registers the 1-byte cleanup 0x007B6F26.
static Rva007AB85CEmptyDtor s_rva007ACA0C;

// 0x007ADE23 (12B) registers the 1-byte cleanup 0x007B77B8.
static Rva007AB85CEmptyDtor s_rva007ADE23;

// 0x007AECBA (12B) registers the 1-byte cleanup 0x007B7C86.
static Rva007AB85CEmptyDtor s_rva007AECBA;

// 0x007B2EDA (12B) registers the 1-byte cleanup 0x007B8E99.
static Rva007AB85CEmptyDtor s_rva007B2EDA;

// 0x007B309E (12B) registers the 1-byte cleanup 0x007B8F44.
static Rva007AB85CEmptyDtor s_rva007B309E;

// 0x007B3504 (12B) registers the 1-byte cleanup 0x007B9099.
static Rva007AB85CEmptyDtor s_rva007B3504;
