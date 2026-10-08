// cl: /MD
//
// ?Rva0006E5A0Get@@YGXPAVVector3@@@Z @0x0006E5A0 (40B).
// Copies shadow-manager light 0 into dest via the landed getLightPosWorld.
// Evidence: shadow global 0x00DE5DFC with null guard; callee row @0x9A497;
// caller 0x95665 passes [ebx+0xE0]; member-wise Vector3 copy.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class W3DGameClientShadowShim
{
public:
	Vector3 &getLightPosWorld(int lightIndex);
};

extern class Gen0003AC38 *g_shadowManager;

void __stdcall Rva0006E5A0Get(Vector3 *dest)
{
	W3DGameClientShadowShim *shadow = (W3DGameClientShadowShim *)(*(void **)&g_shadowManager);
	if (!shadow)
		return;
	Vector3 &src = shadow->getLightPosWorld(0);
	dest->X = src.X;
	dest->Y = src.Y;
	dest->Z = src.Z;
}
