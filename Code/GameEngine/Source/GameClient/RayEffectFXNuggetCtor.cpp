// cl: /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ??0RayEffectFXNugget@@QAE@XZ 123B @0x1E01B2: no-arg ctor called by
// RayEffectFXNugget::parse (0x001E13A5) for the RayEffect FXList keyword;
// class name from BFME1. Member names and offsets from the retail FieldParse
// table 0x00BDCB58 (Name@0x148, PrimaryOffset@0x14C, SecondaryOffset@0x158)
// and the BFME1 donor (FXNugget::m_nuggetType = 2, template clear, offsets
// zeroed). Base 0x001DFEAA is a shared FXNugget-family base ctor (16
// ctor-start callers with this undisplaced); pinned opaquely, do not name.

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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class RayEffectFXNugget : public Rva001DFEAABase
{
public:
	RayEffectFXNugget();
	virtual ~RayEffectFXNugget();
private:
	AsciiString m_templateName; // +0x148
	Coord3D m_primaryOffset; // +0x14C
	Coord3D m_secondaryOffset; // +0x158
};

// ??0RayEffectFXNugget@@QAE@XZ
RayEffectFXNugget::RayEffectFXNugget()
{
	m_templateName.clear();
	m_primaryOffset.x = m_primaryOffset.y = m_primaryOffset.z = 0.0f;
	m_secondaryOffset.x = m_secondaryOffset.y = m_secondaryOffset.z = 0.0f;
	m_nuggetType = 2;
}
