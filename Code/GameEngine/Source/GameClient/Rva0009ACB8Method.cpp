// cl: /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva0009ACB8@Rva0009ACB8@@QAEXPAM@Z @0x0009ACB8 78B: slot 32 of the vtable
// at VA 0x00BC89C8. Copies the +0xC0 RenderObjClass position into the
// caller's three floats, or zeroes them when the subobject is null (shared
// third-store tail). Honest address-derived names; the Get_Position pin is
// rowed at 0x0013B8A0. Boundary verified (frame at 0x9ACB8, leave + ret 4).
#include "../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
class Rva0009ACB8 {
public:
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032(float *out);
	void rva0009ACB8(float *out);
private:
	unsigned char m_pad004[0xC0 - 4];
	RenderObjClass *m_pC0;
};
void Rva0009ACB8::rva0009ACB8(float *out)
{
	RenderObjClass *sub = m_pC0;
	if (sub) {
		Vector3 position = sub->Get_Position();
		out[0] = position.X;
		out[1] = position.Y;
		out[2] = position.Z;
	} else {
		out[0] = 0.0f;
		out[1] = 0.0f;
		out[2] = 0.0f;
	}
}
