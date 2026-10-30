// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Native 0x004398D8 clears and destroys the red-black tree at +4 through
// its existing owners 0x00240C60 and 0x002418E2. The former hash_map view
// only matched these call operands through incorrect hashtable pins.
// The 5-byte container forwards at 0x0043985D and 0x00241C20 retain
// address-derived names until the original container identity is recovered.

class Rva00439325
{
public:
    ~Rva00439325();
    void rva00240C60();
private:
    void *m_header;
    int m_count;
};

class Rva00241C20
{
public:
    ~Rva00241C20() {}
    void rva0043985D() { m_tree.rva00240C60(); }
private:
    Rva00439325 m_tree;
};

// The base is the canonical Snapshot (vtable 0x00BBB554): the parent's unwind
// funclet 0x007881DE destroys it through the folded Snapshot destructor
// 0x0049B47C.
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva000D3FA0Map : public Snapshot
{
public:
	virtual ~Rva000D3FA0Map();

protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);

private:
	Rva00241C20 m_map;
};

// ??1Rva000D3FA0Map@@UAE@XZ
Rva000D3FA0Map::~Rva000D3FA0Map()
{
	m_map.rva0043985D();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?loadPostProcess@Rva000D3FA0Map@@MAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?crc@Rva000D3FA0Map@@MAEXPAVXfer@@@Z=?name@Rva002431A9Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:?xfer@Rva000D3FA0Map@@MAEXPAVXfer@@@Z=__purecall")
