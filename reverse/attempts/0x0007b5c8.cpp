// ?get_far_extent@@YAXABVVector3@@0PAV1@@Z
// partial score=0.96 date=2026-09-10
// cl: /O2 /G7 /MD /arch:SSE /Oy-
//
// get_far_extent, retail 0x0007B5C8, 112 bytes.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

__forceinline bool Fast_Is_Float_Positive(const float &val)
{
	return !((*reinterpret_cast<const int *>(&val) & 0x80000000) != 0);
}

__forceinline float copy_float(float v)
{
	return v;
}

void __cdecl get_far_extent(const Vector3 &normal, const Vector3 &extent, Vector3 *posfarpt)
{
	if (Fast_Is_Float_Positive(normal.X))
		posfarpt->X = copy_float(extent.X);
	else
		posfarpt->X = -extent.X;

	if (Fast_Is_Float_Positive(normal.Y))
		posfarpt->Y = extent.Y;
	else
		posfarpt->Y = -extent.Y;

	if (Fast_Is_Float_Positive(normal.Z))
		posfarpt->Z = extent.Z;
	else
		posfarpt->Z = -extent.Z;
}
