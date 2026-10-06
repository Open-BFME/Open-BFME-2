// cl: /DNDEBUG /MD
// ?xfer@Rva0055EF39@@UAEXPAVXfer@@@Z @0x0055EF39 28B.
// Target identity evidence: the Ghidra boundary is 28 bytes; this body calls
// Xfer::Version1 at 0x000053EE, then DefaultPhysicsModuleInfo::DoXfer at
// 0x0055EECB. The enclosing class identity is unresolved, so Rva0055EF39 is
// an address-derived carrier name.
// Layout evidence: the target passes this+0x1C to the rowed DoXfer body.

class Xfer
{
public:
	void Version1();
};

namespace FXParticleSystem
{
class DefaultPhysicsModuleInfo
{
public:
	virtual void DoXfer(Xfer &xfer);
};
}

class Rva0055EF39
{
public:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad00[0x18];
	FXParticleSystem::DefaultPhysicsModuleInfo m_info;
};

void Rva0055EF39::xfer(Xfer *xfer)
{
	xfer->Version1();
	m_info.FXParticleSystem::DefaultPhysicsModuleInfo::DoXfer(*xfer);
}
