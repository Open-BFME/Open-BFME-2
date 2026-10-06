// cl: /O1 /DNDEBUG /MD /arch:SSE
float g_00DEC4F0;
float g_00DED9F8;
class Rva0014D522Inner {
public:
  char m_pad00[0x88];
  void (__stdcall *m_fn88)(void *a, void *b, void *c);
};
class Rva0014D522Outer {
public:
  Rva0014D522Inner *m_body00;
};
void __cdecl rva0014D522(void *o, void *b) {
  float buf[4];
  buf[0] = g_00DEC4F0;
  buf[1] = g_00DED9F8;
  buf[2] = 0.0f;
  buf[3] = 0.0f;
  Rva0014D522Inner *inner = ((Rva0014D522Outer *)o)->m_body00;
  inner->m_fn88(o, b, buf);
}
