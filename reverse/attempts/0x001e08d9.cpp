// ??0TerrainScorchFXNugget@@QAE@XZ
// partial score=0.72 date=2026-09-24
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0TerrainScorchFXNugget@@QAE@XZ 60B @0x1E08D9: no-arg ctor called by
// TerrainScorchFXNugget::parse (0x001E171C) for the TerrainScorch FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDD8A0 (Type@0x148, Radius@0x14C,
// RandomRange@0x150, an ICoord2D holding min 0 / max 3) and the BFME1 donor
// (FXList.cpp: m_scorch(-1), m_radius(0)). Base 0x001DFEAA is a shared
// FXNugget-family base ctor (16 ctor-start callers with this undisplaced);
// pinned opaquely, do not name.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_nuggetType; // +4, nugget type id
	unsigned char m_pad[0x148 - 8];
};

class TerrainScorchFXNugget : public Rva001DFEAABase
{
public:
	TerrainScorchFXNugget();
private:
	int m_scorchType; // +0x148, scorch lookup, default -1 (random)
	float m_radius; // +0x14C
	int m_minRange; // +0x150
	int m_maxRange; // +0x154
};

// ??0TerrainScorchFXNugget@@QAE@XZ
TerrainScorchFXNugget::TerrainScorchFXNugget()
{
	m_scorchType |= -1;
	int maxRange = 3;
	int minRange = 0;
	m_minRange = minRange;
	*(unsigned int *)this = 0x00BDD828;
	m_radius = 0.0f;
	m_nuggetType = 7;
	m_maxRange = maxRange;
}
