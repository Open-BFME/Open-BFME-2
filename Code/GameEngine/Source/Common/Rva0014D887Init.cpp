// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva0014D887@Rva0014D887This@@QAEXPAVRva0014D887Outer@@PAX@Z retail 0x0014D887 135 bytes. Point-light Center callback. Evidence: same Outer Inner m_fn88 +0x88 and This m_04 +0x04 as sibling Rva0014D722This; global Light_Environment at VA 0x00DEDA14; rowed countPoint 0x0013F750 findPoint 0x0013F780; stride 0x54 lea +0x3c is getPointCenter per LightEnvironmentAccessors; SSE movss xorps; REF constant at 0x0014FEFD callback.
class LightEnvironmentClass;
class Rva0014D887This;
class DX8Wrapper
{
protected:
	static LightEnvironmentClass *Light_Environment;
	friend class Rva0014D887This;
};
class Rva0013F6F0LightEnv
{
public:
	int countPoint() const;
	int findPoint(int index) const;
};
struct Rva0014D887Center {
	float m_c00;
	float m_c04;
	float m_c08;
	char m_pad0C[0x54 - 0x0C];
};
class Rva0014D887Inner {
public:
	char m_pad00[0x88];
	void (__stdcall *m_fn88)(void *a, void *b, void *c);
};
class Rva0014D887Outer {
public:
	Rva0014D887Inner *m_body00;
};
class Rva0014D887This {
public:
	char m_pad00[4];
	volatile int m_04;
	void rva0014D887(Rva0014D887Outer *o, void *b);
};
void Rva0014D887This::rva0014D887(Rva0014D887Outer *o, void *b) {
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
			buf[0] = light->m_c00;
			buf[1] = light->m_c04;
			buf[2] = light->m_c08;
			goto done;
		}
	}
zero:
	buf[0] = 0.0f;
	buf[1] = 0.0f;
	buf[2] = 0.0f;
done:
	buf[3] = 0.0f;
	Rva0014D887Inner *inner = o->m_body00;
	inner->m_fn88(o, b, buf);
}
