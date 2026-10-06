// cl: /MD
// ?rva00562945@Rva00562945@@QAEXPAVXfer@@@Z @0x00562945 28B: containing
// xfer delegating to RenderObjectDrawModuleInfo second base at +0x18 via
// rowed slot-3 xfer after rowed Version1. Tail-called from 0x3ABB8E wrapper.

class Xfer
{
public:
	void Version1();
};

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfo
{
protected:
	virtual void xfer(Xfer *xfer);
};

}

struct Pad018
{
	virtual ~Pad018();

	char m_bytes[0x18 - 4];
};

class Rva00562945 : public Pad018, public FXParticleSystem::RenderObjectDrawModuleInfo
{
public:
	void rva00562945(Xfer *xfer);
};

void Rva00562945::rva00562945(Xfer *xfer)
{
	xfer->Version1();
	RenderObjectDrawModuleInfo::xfer(xfer);
}
