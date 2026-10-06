// ?rva0014D66F@Rva0014D66FThis@@QAEXPAVRva0014D66FOuter@@PAX@Z
// partial score=0.75 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /arch:SSE
extern int g_Va00DEDA14;
// VA 0x00DB5F84 byte scale flag (vanilla 1); non-address name to avoid hatch growth.
unsigned char g_lightScaleFlag14D66F;
struct Rva0014D66FLight {
  float m_f00;
  float m_f04;
  float m_f08;
  char m_pad0C[0x18 - 0x0C];
  float m_f18;
  float m_f1C;
  float m_f20;
  char m_pad24[0x25 - 0x24];
  bool m_point;
  char m_pad26[0x54 - 0x26];
};
class Rva0013F6F0LightEnv {
public:
  int countNonPoint() const;
  int findNonPoint(int index) const;
  int m_vptr;
  int m_count;
  char m_objectCenter[0x0C];
  Rva0014D66FLight m_lights[4];
};
class Rva0014D66FInner {
public:
  char m_pad00[0x88];
  void (__stdcall *m_fn88)(void *a, void *b, void *c);
};
class Rva0014D66FOuter {
public:
  Rva0014D66FInner *m_body00;
};
class Rva0014D66FThis {
public:
  char m_pad00[4];
  volatile int m_04;
  void rva0014D66F(Rva0014D66FOuter *o, void *b);
};
void Rva0014D66FThis::rva0014D66F(Rva0014D66FOuter *o, void *b) {
  float buf[4];
  Rva0013F6F0LightEnv *le = (Rva0013F6F0LightEnv *)g_Va00DEDA14;
  if (le == 0)
    goto zero;
  if (m_04 < 0)
    goto zero;
  {
    int thisIdx = m_04;
    int cnt = le->countNonPoint();
    if (thisIdx < cnt)
      goto nonzero;
    goto zero;
nonzero:
    {
      int idx = le->findNonPoint(thisIdx);
      float *tri = (float *)((char *)le + (idx * 0x54) + 0x2C);
      float f0 = tri[0];
      float f1 = tri[1];
      float f2 = tri[2];
      buf[0] = f0;
      buf[1] = f1;
      buf[2] = f2;
      if (g_lightScaleFlag14D66F == 0)
        goto done;
      f0 *= 2.0f;
      f1 *= 2.0f;
      f2 *= 2.0f;
      buf[0] = f0;
      buf[1] = f1;
      buf[2] = f2;
      goto done;
    }
  }
zero:
  buf[0] = 0.0f;
  buf[1] = 0.0f;
  buf[2] = 0.0f;
done:
  buf[3] = 0.0f;
  Rva0014D66FInner *inner = o->m_body00;
  inner->m_fn88(o, b, buf);
}
