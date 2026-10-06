// ?rva0014D5B0@Rva0014D5B0This@@QAEXPAVRva0014D5B0Outer@@PAX@Z
// partial score=0.7 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /arch:SSE
extern int g_Va00DEDA14;
// VA 0x00DB5F84 byte scale flag (vanilla 1); non-address name to avoid hatch growth.
unsigned char g_lightScaleFlag14D5B0;
struct Rva0014D5B0LightEnv {
  char m_pad00[0x164];
  float m_f164;
  float m_f168;
  float m_f16C;
};
class Rva0014D5B0Inner {
public:
  char m_pad00[0x88];
  void (__stdcall *m_fn88)(void *a, void *b, void *c);
};
class Rva0014D5B0Outer {
public:
  Rva0014D5B0Inner *m_body00;
};
class Rva0014D5B0This {
public:
  char m_pad00[4];
  int m_04;
  void rva0014D5B0(Rva0014D5B0Outer *o, void *b);
};
void Rva0014D5B0This::rva0014D5B0(Rva0014D5B0Outer *o, void *b) {
  float buf[4];
  Rva0014D5B0LightEnv *le = (Rva0014D5B0LightEnv *)g_Va00DEDA14;
  if (le == 0)
    goto zero;
  if (m_04 != 0)
    goto zero;
  {
    float f1 = le->m_f168;
    float f2 = le->m_f16C;
    unsigned char scale = g_lightScaleFlag14D5B0;
    float f0 = le->m_f164;
    buf[0] = f0;
    buf[1] = f1;
    buf[2] = f2;
    if (scale == 0)
      goto done;
    f0 *= 2.0f;
    f1 *= 2.0f;
    f2 *= 2.0f;
    buf[0] = f0;
    buf[1] = f1;
    buf[2] = f2;
    goto done;
  }
zero:
  buf[0] = 0.0f;
  buf[1] = 0.0f;
  buf[2] = 0.0f;
done:
  buf[3] = 0.0f;
  Rva0014D5B0Inner *inner = o->m_body00;
  inner->m_fn88(o, b, buf);
}
