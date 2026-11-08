// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// Clean donor: Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da,
// game/GameEngine/Source/GameLogic/Object/Object_getWorldspaceBestContactPoint.cpp.
// Donor supplies the contact-query algorithm and matrix-expression shape.
// Target: native002904DC..00290758 complete636B RET24; WBCCE910 independently
// names Object::getWorldspaceBestContactPoint. Target-specific template name64,
// geometryA8 and body254 are measured from native accesses; template pointer4
// is consumed directly, without BFME1's override traversal. Matrix3D receiver8,
// Coord3D canonical layout and six contact arguments match existing providers.
// Local forceinline scalar setter preserves the donor's float argument copy
// phase and permits native reuse of the dead flag-word home for world-point Z.
// GeometryInfo::getBestContactPoint identity/ABI are supported independently
// by WB6F91B0 and the complete1079B native body plus existing target bank;
// this caller gives no recovery credit to that unrowed callee.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "Lib/Coord3D.h"

static __forceinline void ContactSet(Coord3D *out,float x,float y,float z){out->x=x;out->y=y;out->z=z;}
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"


#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

__forceinline Vector3 operator *(const Matrix3D &matrix, const Vector3 &input)
{
	float firstY;
	const float firstZ = matrix.Row[2].X * input.X;
	return Vector3(
		matrix.Row[0].X * input.X + matrix.Row[0].Y * input.Y
			+ matrix.Row[0].Z * input.Z + matrix.Row[0].W,
		(firstY = matrix.Row[1].X * input.X,
			firstY + matrix.Row[1].Y * input.Y
				+ matrix.Row[1].Z * input.Z + matrix.Row[1].W),
		firstZ + matrix.Row[2].Y * input.Y
			+ matrix.Row[2].Z * input.Z + matrix.Row[2].W);
}


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

#include "../../../Include/Common/ThingTemplate.h"

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
#include "../../../Include/GameLogic/Module/BodyModule.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
#include "../../../Include/Common/Geometry.h"

extern bool g_bfmeDockingTraceActive;
extern "C" void *theLogicRandomLogFile;

extern "C" int __cdecl fprintf(void *sink, const char *format, ...);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool getWorldspaceBestContactPoint(Coord3D *pointOut,
		const Coord3D *callerPos, const char *label, Int preference,
		Int seed, Bool skipCollideTest) const;

private:
	const ThingTemplate *getTemplate() const {return m_template;}

	BodyModuleInterface *getBodyModule() const { return m_body; }

	void *m_vtable;
	const ThingTemplate *m_template;
	Matrix3D m_transform;
	unsigned char m_unreconstructed_038[0x74 - 0x38];
	UnsignedInt m_id;
	unsigned char m_unreconstructed_078[0xA8 - 0x78];
	GeometryInfo m_geometryInfo;
	unsigned char m_unreconstructed_0D0[0x254 - 0x104];
	BodyModuleInterface *m_body;
};

Bool Object::getWorldspaceBestContactPoint(Coord3D *pointOut,
	const Coord3D *callerPos, const char *label, Int preference,
	Int seed, Bool skipCollideTest) const
{
	if (g_bfmeDockingTraceActive && theLogicRandomLogFile)
	{
		const char *skipCollideTestString;
		UnsignedInt id = (skipCollideTestString =
			skipCollideTest ? "TRUE" : "FALSE", m_id);
		const ThingTemplate *thingTemplate = getTemplate();
		fprintf(theLogicRandomLogFile,
			"      Object::getWorldspaceBestContactPoint() BEGIN: Object %s(%d), callerPos=%g,%g,%g, pref=%d, seed=%d, skipCollideTest=%s",
			thingTemplate->getName().str(), id,
			callerPos->x, callerPos->y, callerPos->z,
			preference, seed, skipCollideTestString);
	}

	Vector3 localCallerVector;
	localCallerVector.X = callerPos->x;
	localCallerVector.Y = callerPos->y;
	localCallerVector.Z = callerPos->z;
	const Matrix3D *transform = &m_transform;
	Matrix3D inverseTransform;
	transform->Get_Orthogonal_Inverse(inverseTransform);
	float localY = inverseTransform.Row[1].X * localCallerVector.X
		+ inverseTransform.Row[1].Y * localCallerVector.Y
		+ inverseTransform.Row[1].Z * localCallerVector.Z
		+ inverseTransform.Row[1].W;
	float localZ = inverseTransform.Row[2].X * localCallerVector.X
		+ inverseTransform.Row[2].Y * localCallerVector.Y
		+ inverseTransform.Row[2].Z * localCallerVector.Z
		+ inverseTransform.Row[2].W;
	float localX = inverseTransform.Row[0].X * localCallerVector.X
		+ inverseTransform.Row[0].Y * localCallerVector.Y
		+ inverseTransform.Row[0].Z * localCallerVector.Z
		+ inverseTransform.Row[0].W;
	localCallerVector.X = localX;
	localCallerVector.Y = localY;
	localCallerVector.Z = localZ;

	Coord3D localPoint;
	if (!m_geometryInfo.getBestContactPoint(&localPoint,
		(const Coord3D *)&localCallerVector,
		label, preference, seed, skipCollideTest))
	{
		if (g_bfmeDockingTraceActive && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile,
				"Geometry.getBestContactPoint failed, return FALSE");
		return false;
	}

	BodyModuleInterface *body = getBodyModule();
	if (body && body->getDamageState() == BODY_RUBBLE)
		localPoint.z = m_geometryInfo.getMaxHeightAbovePosition();

	Vector3 worldPoint = *transform * *(const Vector3 *)&localPoint;
	ContactSet(pointOut,worldPoint.X,worldPoint.Y,worldPoint.Z);

	if (g_bfmeDockingTraceActive && theLogicRandomLogFile)
	{
		fprintf(theLogicRandomLogFile,
			"Geometry.getBestContactPoint succeeded, pointOut=%g,%g,%g, return TRUE",
			pointOut->x, pointOut->y, pointOut->z);
	}

	return true;
}
