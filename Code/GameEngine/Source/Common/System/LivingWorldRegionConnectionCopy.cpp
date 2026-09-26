// cl: /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// LivingWorldRegionConnection copy ctor.
//
// ??0LivingWorldRegionConnection@@QAE@ABV0@@Z (retail 0x003F247D, 83
// bytes): installs the vtable at 0x00C36E48, copies the region name
// through the pinned StringBase<char> copy at 0x000365F0, copies the
// count word, then copies the detour-point vector through the 0x004334D7
// helper. Two EH states (string, then vector) exactly as retail. Serves
// the vector push/grow path (0x003F309A/0x003F2B0B) which builds new
// elements through the 0x003F2980 construct helper below.

#include <vector>

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

template <typename T> class StringBase
{
public:
	StringBase(const StringBase &that);

protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString();
};

struct BfmeE8
{
	float x;
	float y;
};

class LivingWorldRegionConnection : public Snapshot
{
public:
	LivingWorldRegionConnection(const LivingWorldRegionConnection &that);
	virtual ~LivingWorldRegionConnection();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);

private:
	AsciiString m_regionName; // +0x04
	int m_numberAllowed; // +0x08
	_STL::vector<BfmeE8> m_detourPoints; // +0x0C
};

typedef char LivingWorldRegionConnectionSizeCheck[sizeof(LivingWorldRegionConnection) == 0x18 ? 1 : -1];

// ??0LivingWorldRegionConnection@@QAE@ABV0@@Z @0x3F247D
LivingWorldRegionConnection::LivingWorldRegionConnection(const LivingWorldRegionConnection &that)
	: m_regionName(that.m_regionName), m_numberAllowed(that.m_numberAllowed), m_detourPoints(that.m_detourPoints)
{
}
