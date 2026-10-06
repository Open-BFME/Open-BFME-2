// cl: /DNDEBUG /MD
// ?xfer@Rva003AE928@@UAEXPAVXfer@@@Z @0x00563965 28B evidence: vtable slot 3 of 0x0081CD90 and 0x0081D588 for Rva003AE928 copy ctor @0x003AE928 and Rva003AE94E @0x003AE94E; calls rowed Version1 @0x000053EE plus rowed GpuDrawModuleInfo DoXfer @0x0056390A for member at +0x18; ghidra 28B trust ret plus int3 gate
class Xfer
{
public:
	void Version1();
};

namespace FXParticleSystem
{
class GpuDrawModuleInfo
{
public:
	virtual void DoXfer(Xfer &xfer);
};
}

class Rva003AE928
{
public:
	virtual void xfer(Xfer *xfer);
	unsigned char m_pad[0x14];
	FXParticleSystem::GpuDrawModuleInfo m_ginfo;
};

void Rva003AE928::xfer(Xfer *xfer)
{
	xfer->Version1();
	m_ginfo.GpuDrawModuleInfo::DoXfer(*xfer);
}

class Rva003AE94E
{
public:
	virtual void xfer(Xfer *xfer);
	unsigned char m_pad[0x14];
	FXParticleSystem::GpuDrawModuleInfo m_ginfo;
};

void Rva003AE94E::xfer(Xfer *xfer)
{
	xfer->Version1();
	m_ginfo.GpuDrawModuleInfo::DoXfer(*xfer);
}
