// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?first@Gen_00943CF0@@AAEXPAXPAH11@Z -- retail 0x00140FA0, 266 bytes, ret 0x10.
// BFME1 donor Gen_00943CF0_First.cpp (0x009432B0 240B) adapted: BFME2 vtable +4
// (Get_Obj_Space_Bounding_Sphere at +0x10c, extent getter at +0x11c).
#include "rendobj.h"
#include "sphere.h"

class Gen_009431F0
{
public:
	int map_x(float x);
	int map_y(float y);
};

class Gen_00943CF0 : public Gen_009431F0
{
	void first(void *value, int *xOut, int *yOut, int *diffOut);
};

void Gen_00943CF0::first(void *value, int *xOut, int *yOut, int *diffOut)
{
	RenderObjClass *robj = (RenderObjClass *)value;
	Vector3 center = robj->Get_Transform_No_Validity_Check().Get_Translation();
	SphereClass sphere;
	robj->Get_Obj_Space_Bounding_Sphere(sphere);
	float extent = robj->_bfme_get_float_84() + sphere.Radius;

	*xOut = map_x(center[0] - extent);
	*yOut = map_y(center[1] - extent);
	*diffOut = (map_y(center[1] + extent) ^ *yOut) | (map_x(center[0] + extent) ^ *xOut);
	if (*diffOut != 0) {
		unsigned int v = *diffOut;
		int bit = 0;
		if ((v & 0xff00) != 0) {
			v >>= 8;
			bit |= 8;
		}
		if ((v & 0xf0) != 0) {
			v >>= 4;
			bit |= 4;
		}
		if ((v & 0x0c) != 0) {
			v >>= 2;
			bit |= 2;
		}
		if ((v & 2) != 0)
			bit |= 1;
		int keep = ~(1 << bit);
		*xOut &= keep;
		*yOut &= keep;
	}
}
