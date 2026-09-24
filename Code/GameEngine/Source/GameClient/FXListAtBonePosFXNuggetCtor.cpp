// cl: /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ??0FXListAtBonePosFXNugget@@QAE@XZ 78B @0x1E0A57: no-arg ctor called by
// FXListAtBonePosFXNugget::parse (0x001E1814) for the FXListAtBonePos FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDD2F8 (FX@0x148, BoneName@0x14C) and the BFME1 donor
// (m_fx NULL, m_boneName clear, m_nuggetType 10; BFME2 drops orientToBone).
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	virtual ~Rva001DFEAABase();
protected:
	int m_nuggetType; // +4, nugget type id (BFME1 FXNugget::m_nuggetType)
	unsigned char m_pad[0x148 - 8];
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();
private:
	void *m_data;
};

class FXListAtBonePosFXNugget : public Rva001DFEAABase
{
public:
	FXListAtBonePosFXNugget();
	virtual ~FXListAtBonePosFXNugget();
private:
	const char *m_fxName; // +0x148
	AsciiString m_boneName; // +0x14C
};

// ??0FXListAtBonePosFXNugget@@QAE@XZ
FXListAtBonePosFXNugget::FXListAtBonePosFXNugget()
{
	m_fxName = 0;
	m_boneName.clear();
	m_nuggetType = 10;
}
