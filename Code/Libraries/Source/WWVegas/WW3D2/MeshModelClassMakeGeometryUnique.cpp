// cl: /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// MeshModelClass::Make_Geometry_Unique at 0x00172070.
//
// Gives the model private copies of its shared geometry buffers: two vertex
// arrays always, the second pair only when both exist, and the Vector4 array,
// each cloned with NEW_REF and swapped in with REF_PTR_SET / REF_PTR_RELEASE.
// This is the body Open-BFME-1 recovered; BFME 2 packs the members differently,
// with the second pair at +0x38/+0x3C rather than +0x40/+0x44 and the Vector4
// buffer at +0x48 rather than +0x50, so the reduced model below is laid out by
// BFME 2's own offsets.  /G7 is the unit's tell.

#include "sharebuf.h"
#include "vector3.h"
#include "vector4.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.h
class MeshModelClass
{
public:
	void Make_Geometry_Unique();

private:
	unsigned char m_padding00[0x30];
	ShareBufferClass<Vector3> *m_buffer30;
	ShareBufferClass<Vector3> *m_buffer34;
	ShareBufferClass<Vector3> *m_buffer38;
	ShareBufferClass<Vector3> *m_buffer3C;
	unsigned char m_padding40[8];
	ShareBufferClass<Vector4> *m_buffer48;
};

void MeshModelClass::Make_Geometry_Unique()
{
	ShareBufferClass<Vector3> *buffer30 =
		NEW_REF(ShareBufferClass<Vector3>, (*m_buffer30));
	REF_PTR_SET(m_buffer30, buffer30);
	REF_PTR_RELEASE(buffer30);

	ShareBufferClass<Vector3> *buffer38 =
		NEW_REF(ShareBufferClass<Vector3>, (*m_buffer38));
	REF_PTR_SET(m_buffer38, buffer38);
	REF_PTR_RELEASE(buffer38);

	if (m_buffer34 != 0 && m_buffer3C != 0) {
		ShareBufferClass<Vector3> *buffer34 =
			NEW_REF(ShareBufferClass<Vector3>, (*m_buffer34));
		REF_PTR_SET(m_buffer34, buffer34);
		REF_PTR_RELEASE(buffer34);

		ShareBufferClass<Vector3> *buffer3C =
			NEW_REF(ShareBufferClass<Vector3>, (*m_buffer3C));
		REF_PTR_SET(m_buffer3C, buffer3C);
		REF_PTR_RELEASE(buffer3C);
	}

	ShareBufferClass<Vector4> *buffer48 =
		NEW_REF(ShareBufferClass<Vector4>, (*m_buffer48));
	REF_PTR_SET(m_buffer48, buffer48);
	REF_PTR_RELEASE(buffer48);
}
