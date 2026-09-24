// cl: /O1 /DNDEBUG /MD
//
// ??0SoundFXNugget@@QAE@XZ 32B @0x1E00A3: no-arg ctor called by
// SoundFXNugget::parse (0x001E1329) for the Sound FXList keyword; class name
// from BFME1. Member names and offsets from the retail FieldParse table
// 0x00BDCB18 (Name@0x148) and the BFME1 donor (FXNugget::m_field04 type id).
// Base 0x001DFEAA is a shared FXNugget-family base ctor (16 ctor-start
// callers with this undisplaced); pinned opaquely, do not name.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_field04; // +4, nugget type id (BFME1 FXNugget::m_field04)
	unsigned char m_pad[0x148 - 8];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class SoundFXNugget : public Rva001DFEAABase
{
public:
	SoundFXNugget();
private:
	const char *m_soundName; // +0x148
};

// ??0SoundFXNugget@@QAE@XZ
SoundFXNugget::SoundFXNugget()
{
	*(unsigned int *)this = 0x00BDD768;
	_ReadWriteBarrier();
	m_soundName = 0;
	m_field04 = 1;
}
