// cl: /O1 /MD /arch:SSE /Ireference/shims/bfme2_ascii
// ?DoXfer@ParticleSystemInfo@FXParticleSystem@@UAEXAAVXfer@@@Z @0x001F4F5A 354B: ParticleSystemInfo DoXfer slot 3.
// Evidence: vtable 0x007BB5C8 slot 0xC; IsLightCRC early-out slot 0x10; version 1/3 via slot 0x28; helpers XferParticleShaderType XferParticleType xferRandomVariable XferParticlePriorityType rowed; slots 0x90 0x6c 0x78 0x60 0x24; version gates 2/3 for +0x40 +0x98 +0x84; layout from ParticleSystemInfoCtor.

#include "ascii_string.h"

class AsciiString;
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

	Xfer();
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

void XferParticleShaderType(Xfer *xfer, int *value);
void XferParticleType(Xfer *xfer, int *value);
void XferParticlePriorityType(Xfer *xfer, int *value);

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &v);

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual const char *GetSnapshotName() = 0;
	virtual void LoadPostProcess() = 0;
	virtual void DoXfer(Xfer &xfer) = 0;
};

namespace FXParticleSystem
{

class ParticleSystemInfo : public Snapshot
{
public:
	ParticleSystemInfo();
	virtual ~ParticleSystemInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

private:
	bool m_isOneShot;
	unsigned int m_shaderType;
	unsigned int m_particleType;
	AsciiString m_particleTypeName;
	GameClientRandomVariable m_angleZ;
	unsigned int m_systemLifetime;
	unsigned int m_volumeParticleDepth;
	GameClientRandomVariable m_angularRateZ;
	GameClientRandomVariable m_angularDamping;
	unsigned int m_windMotion;
	GameClientRandomVariable m_velDamping;
	GameClientRandomVariable m_lifetime;
	GameClientRandomVariable m_startSize;
	AsciiString m_slaveSystemName;
	Coord3DBase m_slavePosOffset;
	AsciiString m_attachedSystemName;
	unsigned int m_emissionVelocityType;
	bool m_isEmissionVolumeHollow;
	bool m_isGroundAligned;
	bool m_isEmitAboveGroundOnly;
	bool m_isParticleUpTowardsEmitter;
	bool m_windMotionMovingToEndAngle;
	struct Region2DHolder
	{
		float x_min;
		float y_min;
		float x_max;
		float y_max;
	} m_uv;
	unsigned int m_unknown98;
};

}

void FXParticleSystem::ParticleSystemInfo::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;
	Xfer::Version version(1, 3);
	xfer == version;
	xfer == m_isOneShot;
	XferParticleShaderType(&xfer, (int *)&m_shaderType);
	XferParticleType(&xfer, (int *)&m_particleType);
	xfer == m_particleTypeName;
	xferRandomVariable(xfer, m_angleZ);
	xfer == m_systemLifetime;
	xfer == m_volumeParticleDepth;
	xferRandomVariable(xfer, m_angularRateZ);
	xferRandomVariable(xfer, m_angularDamping);
	xferRandomVariable(xfer, m_velDamping);
	xferRandomVariable(xfer, m_lifetime);
	xferRandomVariable(xfer, m_startSize);
	xfer == m_slaveSystemName;
	xfer == m_slavePosOffset;
	xfer == m_attachedSystemName;
	XferParticlePriorityType(&xfer, (int *)&m_emissionVelocityType);
	xfer == m_isEmissionVolumeHollow;
	xfer == m_isGroundAligned;
	xfer == m_isEmitAboveGroundOnly;
	xfer == m_isParticleUpTowardsEmitter;
	if (version.m_minimum >= 2)
	{
		xfer == m_windMotion;
		xfer.XferRawBytes(&m_unknown98, 4);
	}
	if (version.m_minimum >= 3)
	{
		xfer == m_windMotionMovingToEndAngle;
	}
}
