// cl: /O1 /DNDEBUG /MD /arch:SSE
extern int g_Va00DEDA14;
struct Rva0013F6F0Light {
  float m_f00;
  float m_f04;
  float m_f08;
  char m_pad0C[0x25 - 0x0C];
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
  Rva0013F6F0Light m_lights[4];
};
class Rva0014D722Inner {
public:
  char m_pad00[0x88];
  void (__stdcall *m_fn88)(void *a, void *b, void *c);
};
class Rva0014D722Outer {
public:
  Rva0014D722Inner *m_body00;
};
class Rva0014D722This {
public:
  char m_pad00[4];
  volatile int m_04;
  void rva0014D722(Rva0014D722Outer *o, void *b);
};
void Rva0014D722This::rva0014D722(Rva0014D722Outer *o, void *b) {
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
      Rva0013F6F0Light *light = &le->m_lights[idx];
      buf[0] = light->m_f00;
      buf[1] = light->m_f04;
      buf[2] = light->m_f08;
      goto done;
    }
  }
zero:
  buf[0] = 0.0f;
  buf[1] = 0.0f;
  buf[2] = 1.0f;
done:
  buf[3] = 0.0f;
  Rva0014D722Inner *inner = o->m_body00;
  inner->m_fn88(o, b, buf);
}
