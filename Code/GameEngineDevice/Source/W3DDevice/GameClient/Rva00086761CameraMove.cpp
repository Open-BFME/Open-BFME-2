// cl: /MD /EHs-c- /DNDEBUG
// Clean BFME1 W3DViewCameraModFinalMoveToBfme at6d9434269164392c5ba62aaa7c15a86b5b020d76
// guides the translation algorithm. Target Ghidra86761/177B/RET4 and
// complete raw byte equality prove guards1DC/2354, signed count22F0,
// three-float prefixes at2AC with20B stride, and iteration2 through count.
// These data offsets agree with the verified owner8990C/89971 at+280.
// Real constructor8B7CF calls owner8990C withECX=this+280. Its primary
// table BC7568 slot39/BC7604 selects this body; no direct E8/E9 callers.
// Original class/method/argument names and complete parent size unknown.
#include "../../../../GameEngine/Include/GameClient/Rva0008990CArrayOwner.h"


void Rva00086761CameraMove::rva00086761(Rva00089894Point *pLoc)
{
	if (m_doingRotateCamera) {
		return;
	}
	if (m_cameraMovementMode == 1) {
		int i;
		Rva00089894Point delta, start;
		start = m_cameraPath.m_arr255[m_cameraPath.m_numValues].m_position;
		delta = *pLoc;
		delta.x -= start.x;
		delta.y -= start.y;
		delta.z -= start.z;
		for (i = 2; i <= m_cameraPath.m_numValues; i++) {
			Rva00089894Point start;
			start.x = m_cameraPath.m_arr255[i].m_position.x;
			start.y = m_cameraPath.m_arr255[i].m_position.y;
			start.z = m_cameraPath.m_arr255[i].m_position.z;
			start.x += delta.x;
			start.y += delta.y;
			start.z += delta.z;
			m_cameraPath.m_arr255[i].m_position = start;
		}
	}
}

// Clean BFME1 Rva0073C420Set at6d943 guides this signed clamp.
// Target8690A21B is between Ghidra86812+248 and8691F; RET4.
// Same primary tableBC7568 slot32/BC75E8 selects this method. The field
// parent2A8 is canonical owner base m_28 at280+28. EAX incidentally holds
// normalized value; original return contract remains unknown.
void Rva00086761CameraMove::rva0008690A(int value)
{
 if (value<=1) value=1;
 m_cameraPath.m_28=value;
}

// Clean BFME1 W3DViewZoomCameraBfme6d943 O1/G7/SSE/MD guides duration,
// frame and interpolation setup. Target132B/RET16, primary slot59/BC7654,
// unchanged-this call to86CDA and matching fields prove the association.
// Runtime period VA DE204C has genuine zero PE storage; writer4C6C6 and
// startup7AC08C configure it. Their code is not recovered by this unit.
// Original method/global names and complete receiver size remain unknown.
int g_Va00DE204C;

void Rva00086761CameraMove::rva00088EB4(float finalValue, int milliseconds, float easeIn, float easeOut)
{
 int &duration = milliseconds;
 register Rva00086761CameraMove *view = this;
 view->m_228 = true;
 if (duration < 1) duration = 1;
 int frames = duration / g_Va00DE204C;
 if (frames < 1) frames = 1;
 view->m_208 = frames;
 view->m_210 = view->m_3C;
 view->m_214 = finalValue;
 view->m_20C = 0;
 view->m_220.rva0030E51F(easeIn, easeOut, (float)duration);
 if (duration == 1) view->rva00086CDA();
}
