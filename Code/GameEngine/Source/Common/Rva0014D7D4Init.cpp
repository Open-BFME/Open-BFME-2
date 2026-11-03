// cl: /O1 /DNDEBUG /MD /arch:SSE C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva0014D7D4@Rva0014D7D4This@@QAEXPAVRva0014D7D4Outer@@PAX@Z retail 0x0014D7D4 179 bytes. Point-light Diffuse callback with overbright x2. Evidence: same Outer Inner m_fn88 +0x88 and This m_04 +0x04 as siblings 0x0014D722 0x0014D887; global Light_Environment at VA 0x00DEDA14 plus ShaderOverbrightEnabled bool; rowed countPoint 0x0013F750 findPoint 0x0013F780; stride 0x54 lea +0x5c is getPointDiffuse per LightEnvironmentAccessors; float literal 2.0f; REF constant at 0x0014FF15 callback.
class LightEnvironmentClass;
class Rva0014D7D4This;
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
extern bool ShaderOverbrightEnabled;
class Rva0013F6F0LightEnv
{
public:
	int countPoint() const;
	int findPoint(int index) const;
};
struct Rva0014D7D4Diffuse {
	float m_red;
	float m_green;
	float m_blue;
	char m_pad0C[0x54 - 0x0C];
};
class Rva0014D7D4Inner {
public:
	char m_pad00[0x88];
	void (__stdcall *m_fn88)(void *a, void *b, void *c);
};
class Rva0014D7D4Outer {
public:
	Rva0014D7D4Inner *m_body00;
};
class Rva0014D7D4This {
public:
	char m_pad00[4];
	volatile int m_04;
	void rva0014D7D4(Rva0014D7D4Outer *o, void *parameter);
};
void Rva0014D7D4This::rva0014D7D4(Rva0014D7D4Outer *o, void *parameter) {
	float buf[4];
	Rva0013F6F0LightEnv *le = (Rva0013F6F0LightEnv *)DX8Wrapper::Light_Environment;
	if (le != 0 && m_04 >= 0) {
		int thisIdx = m_04;
		int cnt = le->countPoint();
		if (thisIdx < cnt) {
			int idx = le->findPoint(thisIdx);
			Rva0014D7D4Diffuse *diffs = (Rva0014D7D4Diffuse *)((char *)le + 0x5c);
			Rva0014D7D4Diffuse *lightDiffuse = &diffs[idx];
			buf[0] = lightDiffuse->m_red;
			buf[1] = lightDiffuse->m_green;
			buf[2] = lightDiffuse->m_blue;
			if (ShaderOverbrightEnabled) {
				buf[0] *= 2.0f;
				buf[1] *= 2.0f;
				buf[2] *= 2.0f;
			}
			buf[3] = 0.0f;
			Rva0014D7D4Inner *inner = o->m_body00;
			inner->m_fn88(o, parameter, buf);
			return;
		}
	}
	buf[0] = 0.0f;
	buf[1] = 0.0f;
	buf[2] = 0.0f;
	buf[3] = 0.0f;
	Rva0014D7D4Inner *inner = o->m_body00;
	inner->m_fn88(o, parameter, buf);
}
