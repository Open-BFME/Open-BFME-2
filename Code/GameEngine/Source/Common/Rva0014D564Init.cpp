// cl: /O1 /DNDEBUG /MD
extern int g_Va00DEC3CC;
class Rva0014D564Inner {
public:
  char m_pad00[0x78];
  void (__stdcall *m_fn78)(void *a, void *b, float c);
};
class Rva0014D564Outer {
public:
  Rva0014D564Inner *m_body00;
};
void __cdecl rva0014D564(void *o, void *b) {
  float f = (float)(unsigned int)g_Va00DEC3CC * 0.001f;
  Rva0014D564Inner *inner = ((Rva0014D564Outer *)o)->m_body00;
  inner->m_fn78(o, b, f);
}
