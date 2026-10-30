// cl: /O1 /Oy- /MD /Ireference/shims/bfme2_ascii
// Target 001FB201: inherited ParticleSystemInfo snapshot then CRC guard;
// field transfer sequence follows ZH ParticleSys.cpp::xfer at donor 9cbfb551fe20.
// Target offsets and version 3 branches are taken from the retail body.
// Original concrete class identity is not established; retain its RVA name.
#include "ascii_string.h"
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

struct Coord3DBase
{
public:
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
};

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	__declspec(dllimport) __forceinline Version(unsigned char current, unsigned char minimum) // Native two-byte version initialization.
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


enum ObjectID { INVALID_ID=0 };
void XferParticleSystemID(Xfer*, int*);
void XferDrawableID(Xfer*, int*);
void XferObjectID(Xfer*, ObjectID*);
Xfer *Rva003062FEXfer(Xfer*, float*);
void Rva0030612AXfer(Xfer*, float*);
class Rva001FA80F { public: void rva001FA80F(int); };
namespace FXParticleSystem {
class ParticleSystemInfo { public: virtual void pad0(); virtual void pad1(); virtual void pad2(); virtual void DoXfer(Xfer&); private: char m_info[0x98]; };
class Rva001FB201 : public ParticleSystemInfo {
public: void DoXfer(Xfer&);
private:
 void *m_template; int m_fieldA0; Snapshot *m_snapshot;
 int m_systemID; float m_fieldAC; int m_attachedToDrawableID; ObjectID m_attachedToObjectID;
 AsciiString m_fieldB8; float m_localTransform[12]; float m_transform[12];
 unsigned m_burstDelayLeft, m_delayLeft, m_startTimestamp, m_systemLifetimeLeft, m_personalityStore;
 Coord3DBase m_velCoeff; float m_countCoeff, m_delayCoeff;
 Coord3DBase m_pos, m_lastPos; int m_field15C, m_field160, m_field164;
 int m_slaveSystemID, m_field16C, m_field170, m_field174, m_masterSystemID;
 float m_sizeCoeff, m_accumulatedSizeBonus, m_field184; float m_field188[3];
 bool m_field194; char m_gap195[11];
 bool m_isLocalIdentity, m_isIdentity, m_isForever, m_isStopped, m_field1A4, m_isFirstPos, m_field1A6, m_field1A7, m_field1A8;
 char m_gap1A9[3]; Rva001FA80F m_field1AC;
};
void Rva001FB201::DoXfer(Xfer &xfer) {
 ParticleSystemInfo::DoXfer(xfer);
 if(xfer.IsCRC()) return;
 Xfer::Version version(3,3); xfer == version;
 m_field1AC.rva001FA80F((int)&xfer);
 XferParticleSystemID(&xfer,&m_systemID);
 XferDrawableID(&xfer,&m_attachedToDrawableID);
 XferObjectID(&xfer,&m_attachedToObjectID);
 xfer == m_isLocalIdentity;
 Rva003062FEXfer(&xfer,m_localTransform);
 xfer == m_isIdentity;
 Rva003062FEXfer(&xfer,m_transform);
 xfer == m_burstDelayLeft; xfer == m_delayLeft; xfer == m_startTimestamp;
 xfer == m_systemLifetimeLeft; xfer == m_personalityStore;
 xfer == m_isForever; xfer == m_accumulatedSizeBonus; xfer == m_isStopped;
 if(version.m_minimum >= 2) { xfer == m_fieldB8; xfer == m_field1A7; xfer == m_field1A8; }
 xfer == m_velCoeff; xfer == m_countCoeff; xfer == m_delayCoeff;
 xfer == m_sizeCoeff; xfer == m_field184; xfer == m_field194;
 Rva0030612AXfer(&xfer,m_field188);
 xfer == m_pos; xfer == m_lastPos; xfer == m_isFirstPos;
 XferParticleSystemID(&xfer,&m_slaveSystemID);
 XferParticleSystemID(&xfer,&m_masterSystemID);
 xfer == *m_snapshot;
}
}
