// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva0014D7D4@Rva0014D7D4This@@QAEXPAVRva0014D7D4Outer@@PAX@Z retail 0x0014D7D4 179 bytes. Point-light Diffuse callback with overbright x2. Evidence: same Outer Inner m_fn88 +0x88 and This m_04 +0x04 as siblings 0x0014D722 0x0014D887; global Light_Environment at VA 0x00DEDA14 plus ShaderOverbrightEnabled bool; rowed countPoint 0x0013F750 findPoint 0x0013F780; stride 0x54 lea +0x5c is getPointDiffuse per LightEnvironmentAccessors; float literal 2.0f; REF constant at 0x0014FF15 callback.
class LightEnvironmentClass;
class Rva0014D7D4This;
class DX8Wrapper
{
protected:
	static LightEnvironmentClass *Light_Environment;
	friend class Rva0014D7D4This;
};
extern bool ShaderOverbrightEnabled;
class Rva0013F6F0LightEnv
{
public:
	int countPoint() const;
	int findPoint(int index) const;
};
struct Rva0014D7D4Diffuse {
	float m_d00;
	float m_d04;
	float m_d08;
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
	void rva0014D7D4(Rva0014D7D4Outer *o, void *b);
};
void Rva0014D7D4This::rva0014D7D4(Rva0014D7D4Outer *o, void *b) {
	float buf[4];
	Rva0013F6F0LightEnv *le = (Rva0013F6F0LightEnv *)DX8Wrapper::Light_Environment;
	if (le != 0 && m_04 >= 0) {
		int thisIdx = m_04;
		int cnt = le->countPoint();
		if (thisIdx < cnt) {
			int idx = le->findPoint(thisIdx);
			Rva0014D7D4Diffuse *diffs = (Rva0014D7D4Diffuse *)((char *)le + 0x5c);
			Rva0014D7D4Diffuse *d = &diffs[idx];
			buf[0] = d->m_d00;
			buf[1] = d->m_d04;
			buf[2] = d->m_d08;
			if (ShaderOverbrightEnabled) {
				buf[0] *= 2.0f;
				buf[1] *= 2.0f;
				buf[2] *= 2.0f;
			}
			buf[3] = 0.0f;
			Rva0014D7D4Inner *inner = o->m_body00;
			inner->m_fn88(o, b, buf);
			return;
		}
	}
	buf[0] = 0.0f;
	buf[1] = 0.0f;
	buf[2] = 0.0f;
	buf[3] = 0.0f;
	Rva0014D7D4Inner *inner = o->m_body00;
	inner->m_fn88(o, b, buf);
}
