// cl: /O1 /DNDEBUG /MD /arch:SSE
// 0x009EC4F0 / 0x009ED9F8 are DX8Wrapper's protected statics ZNear and ZFar,
// defined in dx8wrapper.cpp (the data ledger's owner for both addresses); this
// unit reads them rather than defining a second global at each address.
void __cdecl rva0014D522(void *o, void *b);
class DX8Wrapper {
  friend void __cdecl rva0014D522(void *o, void *b);
protected:
  static float ZNear;
  static float ZFar;
};
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
  buf[0] = DX8Wrapper::ZNear;
  buf[1] = DX8Wrapper::ZFar;
  buf[2] = 0.0f;
  buf[3] = 0.0f;
  Rva0014D522Inner *inner = ((Rva0014D522Outer *)o)->m_body00;
  inner->m_fn88(o, b, buf);
}
