// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// CursorParticleSystemFXNugget's two effect slots (layout from the rowed
// constructor 0x001E0C90 and the FieldParse table 0x00BDD600):
//   ?doFXPos@...@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z, retail 0x001E0D2D..
//     0x001E0D73 (70 bytes, RET 16);
//   ?doFXObj@...@@UBEXPBVObject@@0@Z, retail 0x001E0D73..0x001E0DB9 (70
//     bytes, RET 8).
// Both ignore their arguments and hand the template name, the burst count
// and the four random variables to TheInGameUI's burst entry (rowed
// 0x002A4A0C, name by value).

#include "ascii_string.h"

struct Coord3D;
class Matrix3D;
class Object;

struct Rva002A1B1DChunk
{
	int m_words[3];
};

class InGameUI
{
public:
	void rva002A4A0C(AsciiString name, unsigned int count, const Rva002A1B1DChunk *p1, const Rva002A1B1DChunk *p2, const Rva002A1B1DChunk *p3, const Rva002A1B1DChunk *p4);
};

extern InGameUI *TheInGameUI;

class GameClientRandomVariable
{
private:
	int m_type;
	float m_low;
	float m_high;
};

class Rva001DFEAABase
{
public:
	virtual ~Rva001DFEAABase();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;
protected:
	int m_nuggetType;						// +0x04
	unsigned char m_pad[0x148 - 8];
};

class CursorParticleSystemFXNugget : public Rva001DFEAABase
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;
private:
	AsciiString m_name;						// +0x148
	int m_burstCount;						// +0x14C
	GameClientRandomVariable m_particleLife;	// +0x150
	GameClientRandomVariable m_systemLife;	// +0x15C
	GameClientRandomVariable m_driftVelX;	// +0x168
	GameClientRandomVariable m_driftVelY;	// +0x174
};

void CursorParticleSystemFXNugget::doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const
{
	TheInGameUI->rva002A4A0C(m_name, m_burstCount,
		(const Rva002A1B1DChunk *)&m_particleLife, (const Rva002A1B1DChunk *)&m_systemLife,
		(const Rva002A1B1DChunk *)&m_driftVelX, (const Rva002A1B1DChunk *)&m_driftVelY);
}

void CursorParticleSystemFXNugget::doFXObj(const Object *, const Object *) const
{
	TheInGameUI->rva002A4A0C(m_name, m_burstCount,
		(const Rva002A1B1DChunk *)&m_particleLife, (const Rva002A1B1DChunk *)&m_systemLife,
		(const Rva002A1B1DChunk *)&m_driftVelX, (const Rva002A1B1DChunk *)&m_driftVelY);
}
