// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ?setInstanceMatrix@Drawable@@QAEXPBVMatrix3D@@_N@Z, retail 0x002711C6, 605 bytes.
// Identity: the two-argument BFME setInstanceMatrix. Callers pass a Drawable
// from Object::getDrawable (0x005508E2): FloatUpdate::update with false,
// StructureCollapseUpdate (0x004A47FA and siblings) with true and
// SwayClientUpdate (0x004C94CE), the same callers BFME 1 shows. Donor: BFME 1's
// matched reference/open-bfme-1/game/GameEngine/Source/GameClient/
// DrawableSetInstanceMatrixBFME.cpp, over Zero Hour's one-argument
// Drawable::setInstanceMatrix (the instance copy or identity plus the identity
// flag). BFME 2 offsets measured from retail: previous instance +0x170,
// instance +0x1A0 (the pair the rowed interpolator 0x00271423 lerps), the
// interpolation stamp +0x204, the instance frame +0x378, the identity flag
// +0x43F; TheGameEngine's frame int is at +0x38 and the client time is
// TheGameClient slot 0x7C (as in 0x00271423). The Matrix3D and Vector4
// members are WWMath's WWINLINE (__forceinline); plain inline leaves the
// assignment out of line at /O1.

typedef unsigned int UnsignedInt;
typedef float Real;

#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"


static __forceinline void copyInstanceMatrix(Matrix3D &dst,const Matrix3D &src) {dst.Row[0].X=src.Row[0].X;dst.Row[0].Y=src.Row[0].Y;dst.Row[0].Z=src.Row[0].Z;dst.Row[0].W=src.Row[0].W;dst.Row[1].X=src.Row[1].X;dst.Row[1].Y=src.Row[1].Y;dst.Row[1].Z=src.Row[1].Z;dst.Row[1].W=src.Row[1].W;dst.Row[2].X=src.Row[2].X;dst.Row[2].Y=src.Row[2].Y;dst.Row[2].Z=src.Row[2].Z;dst.Row[2].W=src.Row[2].W;}
static __forceinline void setInstanceRow(Vector4 &r,float x,float y,float z,float w) { r.X=x;r.Y=y;r.Z=z;r.W=w; }
static __forceinline void setInstanceIdentity(Matrix3D &m) { setInstanceRow(m.Row[0],1.0f,0.0f,0.0f,0.0f);setInstanceRow(m.Row[1],0.0f,1.0f,0.0f,0.0f);setInstanceRow(m.Row[2],0.0f,0.0f,1.0f,0.0f); }
class GameEngine
{
public:
	unsigned char m_pad000[0x38];
	int m_frame; // +0x38
};
extern GameEngine *TheGameEngine;

class GameClient
{
public:
#define CLIENT_SLOT(n) virtual void slot##n();
	CLIENT_SLOT(00) CLIENT_SLOT(01) CLIENT_SLOT(02) CLIENT_SLOT(03) CLIENT_SLOT(04)
	CLIENT_SLOT(05) CLIENT_SLOT(06) CLIENT_SLOT(07) CLIENT_SLOT(08) CLIENT_SLOT(09)
	CLIENT_SLOT(10) CLIENT_SLOT(11) CLIENT_SLOT(12) CLIENT_SLOT(13) CLIENT_SLOT(14)
	CLIENT_SLOT(15) CLIENT_SLOT(16) CLIENT_SLOT(17) CLIENT_SLOT(18) CLIENT_SLOT(19)
	CLIENT_SLOT(20) CLIENT_SLOT(21) CLIENT_SLOT(22) CLIENT_SLOT(23) CLIENT_SLOT(24)
	CLIENT_SLOT(25) CLIENT_SLOT(26) CLIENT_SLOT(27) CLIENT_SLOT(28) CLIENT_SLOT(29)
	CLIENT_SLOT(30)
#undef CLIENT_SLOT
	virtual UnsignedInt getFrame(); // slot 0x7C
};
extern GameClient *TheGameClient;

class Drawable
{
public:
	void setInstanceMatrix(const Matrix3D *instance, bool preservePrevious);

private:
	unsigned char m_pad000[0x170];
	Matrix3D m_previousInstance; // +0x170
	Matrix3D m_instance; // +0x1A0
	unsigned char m_pad1d0[0x204 - 0x1D0];
	UnsignedInt m_expirationDate; // +0x204
	unsigned char m_pad208[0x378 - 0x208];
	UnsignedInt m_frame; // +0x378
	unsigned char m_pad37c[0x43F - 0x37C];
	bool m_instanceIsIdentity; // +0x43F
};

// ?setInstanceMatrix@Drawable@@QAEXPBVMatrix3D@@_N@Z
void Drawable::setInstanceMatrix(const Matrix3D *instance, bool preservePrevious)
{
	copyInstanceMatrix(m_previousInstance, m_instance);
	if (instance)
	{
		copyInstanceMatrix(m_instance, *instance);
		m_instanceIsIdentity = false;
	}
	else
	{
		setInstanceIdentity(m_instance);
		m_instanceIsIdentity = true;
	}

	if (preservePrevious)
		copyInstanceMatrix(m_previousInstance, m_instance);

	Real frame = (Real)TheGameEngine->m_frame;
	frame += (Real)TheGameClient->getFrame();
	m_frame = (UnsignedInt)frame;
	m_expirationDate = 0xffffffff;
}
