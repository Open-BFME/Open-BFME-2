// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ?rva0030A3E4@Rva0030A3E4@@QAEXPBVMatrix3D@@@Z 0x0030A3E4 200B evidence: Thing layout +8 m_transform +38 cachedPos +44 angle +5c flags; Get_Z_Rotation and Coord3D equals rowed; vslot 0x18 conditional; callers UNCLAIMED
#define Coord3D ZH_Coord3D
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#undef Coord3D

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	bool equals(const Coord3DBase &that) const;
};

class BFMERetailVTable
{
public:
	virtual Real calculateHeightAboveTerrain() const = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle) = 0;
	virtual void slot6() = 0;
};

// Owner unknown: TU-local layout matching retail offsets.
class Rva0030A3E4
{
public:
	void *m_vptr;
	unsigned char m_pad0[4];
	Matrix3D m_transform;
	Coord3D m_cachedPos;
	Real m_cachedAngle;
	unsigned char m_pad1[0x5c - 0x48];
	int m_cacheFlags;
	void rva0030A3E4(const Matrix3D *mx);
};

void Rva0030A3E4::rva0030A3E4(const Matrix3D *mx)
{
	Real oldAngle = m_cachedAngle;
	const Coord3D &cachedPos = m_cachedPos;
	Coord3D oldPos;
	oldPos.x = cachedPos.x;
	oldPos.y = cachedPos.y;
	oldPos.z = cachedPos.z;

	m_transform = *mx;
	m_cachedPos.x = m_transform.Get_X_Translation();
	m_cachedPos.y = m_transform.Get_Y_Translation();
	m_cachedPos.z = m_transform.Get_Z_Translation();
	m_cachedAngle = m_transform.Get_Z_Rotation();
	m_cacheFlags = 0;

	if (oldAngle != m_cachedAngle || !oldPos.equals(m_cachedPos))
	{
		reinterpret_cast<BFMERetailVTable *>(this)->slot6();
	}
}
