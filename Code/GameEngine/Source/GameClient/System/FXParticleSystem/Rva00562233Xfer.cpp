// cl: /MD
// ?rva00562233@Rva00562233@@QAEXPAVXfer@@@Z @0x00562233 28B: containing
// xfer (slot 3 of 0x81CF38/0x81D728) delegating to RenderObjectUpdateModuleInfo
// member at +0x1C via rowed 177B xfer after rowed Version1. Tail-called from
// 0x3ABE88 wrapper.

class Xfer
{
public:
	void Version1();
};

namespace FXParticleSystem
{

class RenderObjectUpdateModuleInfo
{
protected:
	virtual void xfer(Xfer *xfer);
};

}

struct Pad01C
{
	virtual ~Pad01C();

	char m_bytes[0x1C - 4];
};

class Rva00562233 : public Pad01C, public FXParticleSystem::RenderObjectUpdateModuleInfo
{
public:
	void rva00562233(Xfer *xfer);
};

void Rva00562233::rva00562233(Xfer *xfer)
{
	xfer->Version1();
	RenderObjectUpdateModuleInfo::xfer(xfer);
}
