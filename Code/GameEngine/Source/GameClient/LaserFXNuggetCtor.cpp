// cl: /O1 /DNDEBUG /MD
//
// ??0LaserFXNugget@@QAE@XZ 32B @0x1E04DE: no-arg ctor called by
// LaserFXNugget::parse (0x001E1519) for the Laser FXList keyword; class name
// from BFME1. Member names and offsets from the retail FieldParse table
// 0x00BDCFD8 (LaserName@0x148 LaserBackwards@0x14C) and the BFME1 donor.
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
private:
	unsigned char m_pad[0x148];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class LaserFXNugget : public Rva001DFEAABase
{
public:
	LaserFXNugget();
private:
	const char *m_laserName; // +0x148
	bool m_laserBackwards; // +0x14C
};

// ??0LaserFXNugget@@QAE@XZ
LaserFXNugget::LaserFXNugget()
{
	*(unsigned int *)this = 0x00BDD7B8;
	_ReadWriteBarrier();
	m_laserName = 0;
	m_laserBackwards = false;
}
