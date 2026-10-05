// cl: /O1 /MD
//
// ?Rva0006E5C8Set@@YGXPAVVector3@@@Z @0x0006E5C8 (61B).
// Sets shadow-manager light 0 from src then clears volumetric shadow list.
// Evidence: shadow global 0x00DE5DFC with null guard plus callee pin @0x9A587
// setLightPosition; second global 0x00DEBCD8 with null guard plus row @0xF0912;
// callers at 0x9549A 0x955B1 0x9567F in 0x953B3 and 0x983CF in 0x982F9.

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
	void setLightPosition(int lightIndex, float x, float y, float z);
};

class Rva000F0912
{
public:
	void rva000F0912();
};

extern void *W3DGCData00DE5DFC;
extern Rva000F0912 *g_00DEBCD8;

void __stdcall Rva0006E5C8Set(Vector3 *src)
{
	W3DGameClientShadowShim *shadow = (W3DGameClientShadowShim *)W3DGCData00DE5DFC;
	if (shadow == 0)
		return;
	shadow->setLightPosition(0, src->X, src->Y, src->Z);
	if (g_00DEBCD8 != 0)
		g_00DEBCD8->rva000F0912();
}
