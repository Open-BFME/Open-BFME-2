// cl: /O1 /DNDEBUG /MD /GX-
// LivingWorldRegionConnection default ctor.
//
// ??0LivingWorldRegionConnection@@QAE@XZ (retail 0x003F24F3, 36 bytes):
// installs the vtable at 0x00C36E48, empties the region name, sets the
// count at +0x08 to -1, then builds the detour-point vector at +0x0C
// through the folded empty _Vector_base ctor at 0x00211E58 (ICF-fold pin
// for the BfmeE8 spelling; the detour points parse as Coord2D pairs
// through the rowed 0x002F592 into this vector). No EH frame: every
// member is trivially destructible in this TU (dtor-less string, bare
// base storage), so nothing needs unwinding.
// (vtable slot 2 at 0x003F24D0 is already rowed under a sibling TU; the
// bytes are identical so no second claim is made here.)
// Serves the Connection (0x003F348F) and ConnectsTo (0x003F341E) entries
// of the Region map table at 0x00836560 (sub-table 0x00C36FD4).

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

struct BfmeE8
{
	float x;
	float y;
};

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A = allocator<T> > struct _Vector_base
{
	_Vector_base(const A &alloc);

	void *_M_start;
	void *_M_finish;
	void *_M_end_of_storage;
};
}

struct AsciiString
{
	AsciiString() : m_data(0) {}

	char *m_data;
};

class LivingWorldRegionConnection : public Snapshot
{
public:
	LivingWorldRegionConnection();
	virtual ~LivingWorldRegionConnection();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);

private:
	AsciiString m_regionName; // +0x04
	int m_numberAllowed; // +0x08, default -1
	_STL::_Vector_base<BfmeE8, _STL::allocator<BfmeE8> > m_detourPoints; // +0x0C
};

typedef char LivingWorldRegionConnectionSizeCheck[sizeof(LivingWorldRegionConnection) == 0x18 ? 1 : -1];

// ??0LivingWorldRegionConnection@@QAE@XZ @0x3F24F3
LivingWorldRegionConnection::LivingWorldRegionConnection()
	: m_regionName(), m_numberAllowed(-1), m_detourPoints(_STL::allocator<BfmeE8>())
{
}
