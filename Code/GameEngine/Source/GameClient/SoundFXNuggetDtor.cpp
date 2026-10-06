// cl: /MD /EHsc /DNDEBUG
//
// ??1SoundFXNugget@@UAE@XZ, retail 0x001E0E07, 60 bytes.
// Target evidence: the audited scalar deleting dtor 0x001E0DEB (vtable
// 0x00BDD768 slot 0) calls this body. It releases the ref-counted pointer at
// +0x148 (inline null check, Release_Ref 0x00050ED3), then calls the nugget
// base dtor 0x001DFA48 (Rva001DFA48Owner; base extent 0x148 as in the
// BuffNugget/ParticleSystem siblings). No derived vptr store (novtable).
// SoundFXNugget spelling is donor-carried per the audited pin.

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva001DFA48Owner
{
public:
	virtual ~Rva001DFA48Owner();

private:
	unsigned char m_tail[0x148 - 4];
};

class __declspec(novtable) SoundFXNugget : public Rva001DFA48Owner
{
public:
	virtual ~SoundFXNugget();

private:
	OpaqueRefCounted *m_sound;	// +0x148
};

SoundFXNugget::~SoundFXNugget()
{
	if (m_sound)
		m_sound->Release_Ref();
}
