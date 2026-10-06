// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
// stlport
// ??1Rva0039A1CA@@UAE@XZ, retail 0x0039A1CA (123 bytes).
// Identity: virtual ModuleData-style dtor restoring Snapshot vtable g_00BBB554;
// caller is slot-0 deleting dtor 0x0039A1AE. Members in descending destroy order:
// tree +0x68 via rowed 0x00399278, vectors +0x5C/+0x50 via rowed 0x0039977A/
// 0x0039973B, filters +0x34/+0x30 via rowed 0x00360D26 twice, strings +0x14/+0x10
// via inlined AsciiString releaseBuffer 0x00036410. Layout mirrors
// StructureToppleUpdateModuleDataDtor precedent; neighbours are CastleBehavior
// ModuleData units.
#include <vector>
#include "ascii_string.h"
struct Rva00395D77
{
	~Rva00395D77();
	unsigned char m_data[12];
};
struct RvaPair0039973B
{
	~RvaPair0039973B();
	unsigned char m_data[8];
};
class Rva00397C94
{
public:
	~Rva00397C94();
};
class Rva00360D26Member
{
public:
	~Rva00360D26Member();
	int m_pad;
};
class Xfer;
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};
extern const void *const g_00BBB554[];
inline Snapshot::~Snapshot() { *(const void **)this = g_00BBB554; }
class __declspec(novtable) Rva0039A1CA : public Snapshot
{
public:
	virtual ~Rva0039A1CA();
private:
	unsigned char m_pad04[0x10 - 0x04];
	AsciiString m_str10; // +0x10
	AsciiString m_str14; // +0x14
	unsigned char m_pad18[0x30 - 0x18];
	Rva00360D26Member m_filt30; // +0x30
	Rva00360D26Member m_filt34; // +0x34
	unsigned char m_pad38[0x50 - 0x38];
	_STL::vector<struct RvaPair0039973B, _STL::allocator<struct RvaPair0039973B> > m_vec50; // +0x50
	_STL::vector<struct Rva00395D77, _STL::allocator<struct Rva00395D77> > m_vec5C; // +0x5C
	Rva00397C94 m_tree68; // +0x68
};
Rva0039A1CA::~Rva0039A1CA()
{
}
