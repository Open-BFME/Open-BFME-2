// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?SetPosition@Rva0014D887This@@QAEXPAVRva0014D887Outer@@PAX@Z retail 0x0014D887 135 bytes. Point-light Center callback. Evidence: same Outer Inner m_fn88 +0x88 and This m_04 +0x04 as sibling Rva0014D722This; global Light_Environment at VA 0x00DEDA14; rowed countPoint 0x0013F750 findPoint 0x0013F780; stride 0x54 lea +0x3c is getPointCenter per LightEnvironmentAccessors; SSE movss xorps; REF constant at 0x0014FEFD callback.
class LightEnvironmentClass;
class Rva0014D887This;
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
class Rva0013F6F0LightEnv
{
public:
	int countPoint() const;
	int findPoint(int index) const;
};
struct Rva0014D887Center {
	float m_x;
	float m_y;
	float m_z;
	char m_pad0C[0x54 - 0x0C];
};
class ID3DXEffectVtbl {
public:
	char m_pad00[0x88];
	void (__stdcall *m_fn88)(void *a, void *b, void *c);
};
class Rva0014D887Outer {
public:
	ID3DXEffectVtbl *m_body00;
};
class Rva0014D887This {
public:
	char m_pad00[4];
	volatile int m_04;
	void SetPosition(Rva0014D887Outer *effect, void *parameter);
};
void Rva0014D887This::SetPosition(Rva0014D887Outer *effect, void *parameter) {
	float buf[4];
	Rva0013F6F0LightEnv *le = (Rva0013F6F0LightEnv *)DX8Wrapper::Light_Environment;
	if (le == 0)
		goto zero;
	if (m_04 < 0)
		goto zero;
	{
		int thisIdx = m_04;
		int cnt = le->countPoint();
		if (thisIdx < cnt)
			goto nonzero;
		goto zero;
	nonzero:
		{
			int idx = le->findPoint(thisIdx);
			Rva0014D887Center *centers = (Rva0014D887Center *)((char *)le + 0x3c);
			Rva0014D887Center *light = &centers[idx];
			buf[0] = light->m_x;
			buf[1] = light->m_y;
			buf[2] = light->m_z;
			goto done;
		}
	}
zero:
	buf[0] = 0.0f;
	buf[1] = 0.0f;
	buf[2] = 0.0f;
done:
	buf[3] = 0.0f;
	ID3DXEffectVtbl *inner = effect->m_body00;
	inner->m_fn88(effect, parameter, buf);
}
