// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
// ??1Rva003FD3EF@@UAE@XZ @0x003FD3EF 76B
// ModuleData dtor: vtable 0x007FE024, opaque clear of the holder at +0x0C via
// rowed ?clear@Rva000A8C9B@@QAEXXZ, null-test of its referent plus rowed
// ?Release_Ref@OpaqueRefCounted@@QAEXXZ, then Snapshot base vtable 0x00BBB554.
// Same recipe as Rva003FD789Dtor, using the shared Snapshot base header;
// Rva000A8C9B carries an inline dtor (null-test plus Release_Ref) so unwind
// states are emitted while the body carries the opaque clear call.
// Unblocks ??_G at 0x002B30AE.
#include "Common/Snapshot.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

struct Rva000A8C9B
{
	OpaqueRefCounted *m_ptr;
	Rva000A8C9B() : m_ptr(0) {}
	void clear();
	~Rva000A8C9B()
	{
		if (m_ptr != 0)
			m_ptr->Release_Ref();
	}
};
class Rva003FD3EF : public Snapshot
{
public:
	Rva003FD3EF();
	virtual ~Rva003FD3EF();
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual bool slot4();
	virtual void slot5();
	virtual int getType();
private:
	char m_pad04[8];
	Rva000A8C9B m_0c;
};

Rva003FD3EF::~Rva003FD3EF()
{
	m_0c.clear();
}

// ??0Rva003FD3EF@@QAE@XZ @0x002B309B 13B: installs vtable 0x00BFE024 (slot 0
// the rowed ??_G 0x002B30AE, slot 2 the "DelayedAudioEventModule" name
// getter 0x002B30A8 directly after it) and nulls the holder at +0x0C; +4/+8
// are left untouched. Twin skeleton of ??0RadarMarkerClientUpdateModuleData.
Rva003FD3EF::Rva003FD3EF()
{
}
