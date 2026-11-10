// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// ?reactToTransformChange@W3DLightDraw@@UAEXPBVMatrix3D@@PBUCoord3D@@M@Z, retail 0x000CFDFB..0x000CFF4A
// (337B), thiscall ret 0xC. Donor (facts carried from the donor, not target): Open-BFME-1
// W3DLightDrawReactToTransformChange.cpp (BFME 1 0x00758AC0). Target evidence: module
// data +4, drawable +8, light +0xC as the rowed W3DLightDraw members; bone name string
// at module data +0x44 (BFME 1 used the same field); Drawable::getTransformMatrix
// 0x0027628E, the rowed (int,int) bone query 0x00272835 and light slot 21
// (Set_Transform). Codegen: the bone AsciiString pointer is a same-valued PHI over
// the module data pointer (keeps this in ESI, bone in EDI) and the drawable is loaded
// into a local before the call (ECX before the LEA).

#include "Coord3D.h"
#include "matrix3d.h"

#include "ascii_string.h"

class W3DLightDrawModuleData
{
private:
	char padding[0x44];

public:
	AsciiString boneName;
};

#include "../../../../../Include/W3DDevice/GameClient/Module/W3DLightDraw.h"
#include "../../../../../../GameEngine/Include/GameClient/Drawable.h"

#include "../../../../../Include/W3DDevice/GameClient/W3DDynamicLightClass.h"


// File-static matrix copy (LK3-style): the TU's copy-ctor COMDAT loses
// the link, and the rowed body below inlines the construction, so the def
// cannot just go away. The helper keeps a call in the source (regalloc
// preserved) while the copy-ctor goes unused.
static void CopyLightMatrix3D(Matrix3D &dst, const Matrix3D &src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

void W3DLightDraw::reactToTransformChange(const Matrix3D *, const Coord3D *, float)
{
	if (m_0C)
	{
		
		Matrix3D transform;
		CopyLightMatrix3D(transform, *m_drawable->getTransformMatrix());
		const W3DLightDrawModuleData *data = (const W3DLightDrawModuleData *)getModuleData();
		const AsciiString *bone = &(data ? data : data)->boneName;
		if (!bone->isEmpty())
		{
			Matrix3D boneTransform;
			const char *boneName = bone->str();
			Drawable *draw = m_drawable;
			if (draw->rva00272835((int)boneName, (int)&boneTransform))
				transform = boneTransform;
		}
		m_0C->Set_Transform(transform);
	}
}
