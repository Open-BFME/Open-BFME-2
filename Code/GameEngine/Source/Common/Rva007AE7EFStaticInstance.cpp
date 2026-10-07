// cl: /O2 /Os /MD
// /Os makes the emitted constructor the rowed 13-byte copy while /O2
// retains constant initialization. Constructor, destructor and deleting
// destructor copies all match their existing retail owners.
// Dynamic initializer and cleanup of a file-scope Rva0030D346 object. Its
// inline constructor (vptr plus a zeroed word at +4) is folded into the
// object's static data, so the initializer only registers the cleanup, and
// the cleanup is the inlined empty virtual destructor storing the class
// table back. Target evidence: game.dat's __xc_a table points at 0x007AE7EF,
// which registers 0x007B7B09; that cleanup stores 0x00C089EC, the table the
// rowed ??_GRva0030D346@@UAEPAXI@Z (0x0030D35A) and ??0Rva0030D346@@QAE@XZ
// (0x0030D346) store, into 0x00DBDF6C, and .data already holds that table
// there with a zero word after it. The next initializer in the same unit
// (0x007AE7FB) stores 0x00DBDF70, the object's +4, into 0x00E00940, which
// Rva000ABD70Clear.cpp reads; that store is not recovered here. /O2: at /O1
// the constructor is called, not folded. RvaSmallVtableCtors.cpp carries the
// out-of-line constructor; the owning TU and the object name are not
// established.

class Rva0030D346
{
public:
	Rva0030D346() : m_4( 0 ) {}
	virtual ~Rva0030D346() {}

private:
	void *m_4;
};

static Rva0030D346 s_rva0030D346;
