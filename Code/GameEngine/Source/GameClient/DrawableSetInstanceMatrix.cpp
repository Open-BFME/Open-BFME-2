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
static __forceinline void setInstanceRow(Vector4 &instanceRow,float componentX,float componentY,float componentZ,float componentW) { instanceRow.X=componentX;instanceRow.Y=componentY;instanceRow.Z=componentZ;instanceRow.W=componentW; }
static __forceinline void setInstanceIdentity(Matrix3D &instanceMatrix) { setInstanceRow(instanceMatrix.Row[0],1.0f,0.0f,0.0f,0.0f);setInstanceRow(instanceMatrix.Row[1],0.0f,1.0f,0.0f,0.0f);setInstanceRow(instanceMatrix.Row[2],0.0f,0.0f,1.0f,0.0f); }
class GameEngine
{
public:
	unsigned char m_pad000[0x38];
	int m_frame; // +0x38
};
extern GameEngine *TheGameEngine;

#include "../../Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;

#include "../../Include/GameClient/Drawable.h"

// ?setInstanceMatrix@Drawable@@QAEXPBVMatrix3D@@_N@Z
void Drawable::setInstanceMatrix(const Matrix3D *instance, bool preservePrevious)
{
	copyInstanceMatrix(m_170, m_instance);
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
		copyInstanceMatrix(m_170, m_instance);

	Real frame = (Real)TheGameEngine->m_frame;
	frame += (Real)TheGameClient->getFrame();
	m_378 = (UnsignedInt)frame;
	m_204 = 0xffffffff;
}
