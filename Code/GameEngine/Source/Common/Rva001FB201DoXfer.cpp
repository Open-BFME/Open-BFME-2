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
	float x;
	float y;
	float z;
};

class Xfer
{
public:
	class Version;

	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


enum ObjectID { INVALID_ID=0 };
void XferParticleSystemID(Xfer*, int*);
void XferDrawableID(Xfer*, int*);
void XferObjectID(Xfer*, ObjectID*);
void Rva003062FEXfer(Xfer*, float*);
void Rva0030612AXfer(Xfer*, float*);
class Rva001FA80F { public: void rva001FA80F(int); };
namespace FXParticleSystem {
class ParticleSystemInfo { public: virtual void pad0(); virtual void pad1(); virtual void pad2(); virtual void DoXfer(Xfer&); private: char m_info[0x98]; };
class Rva001FB201 : public ParticleSystemInfo {
public: void DoXfer(Xfer&);
private:
 void *m_template; int m_fieldA0; Snapshot *m_fieldA4;
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
 xfer == *m_fieldA4;
}
}
