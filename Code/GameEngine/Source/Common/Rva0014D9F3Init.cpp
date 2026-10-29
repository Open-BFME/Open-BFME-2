// cl: /O1 /DNDEBUG /MD /arch:SSE
class BFMETextureBaseVirtuals {
public:
  virtual void Slot_0() = 0;
  virtual void Slot_1() = 0;
  virtual void Slot_2() = 0;
  virtual void Slot_3() = 0;
  virtual void Slot_4() = 0;
  virtual void Slot_5() = 0;
  virtual void Slot_6() = 0;
  virtual void Slot_7() = 0;
  virtual void Slot_8() = 0;
  virtual void Slot_9() = 0;
  virtual bool Is_Initialized() const = 0;
  virtual void Init() = 0;
};
class TextureBaseClass {
public:
  int rva0013275A() const;
  BFMETextureBaseVirtuals *m_texture;
};
struct Float4 {
  float f[4];
};
class Rva0014D9F3Inner {
public:
  char m_pad00[0x88];
  void (__stdcall *m_fn88)(void *a, void *b, void *c);
};
class Rva0014D9F3Outer {
public:
  Rva0014D9F3Inner *m_vtable;
};
class Rva0014D9F3This {
public:
  char m_pad00[0x48];
  TextureBaseClass m_tex48;
  void rva0014D9F3(Rva0014D9F3Outer *effect, void *parameter);
};
void Rva0014D9F3This::rva0014D9F3(Rva0014D9F3Outer *effect, void *parameter) {
  Float4 buf;
  Float4 texelSize;
  if (*(void **)&m_tex48 != 0)
    goto nonzero;
  goto zero;
nonzero:
  {
    int c1 = m_tex48.rva0013275A();
    float f1 = 1.0f / (float)(unsigned int)c1;
    int c2 = m_tex48.rva0013275A();
    float f2 = 1.0f / (float)(unsigned int)c2;
    buf.f[0] = 0.0f;
    buf.f[1] = 0.0f;
    buf.f[2] = f2;
    buf.f[3] = f1;
    goto done;
  }
zero:
  buf.f[0] = 0.0f;
  buf.f[1] = 0.0f;
  buf.f[2] = 0.0f;
  buf.f[3] = 0.0f;
done:
  texelSize = buf;
  Rva0014D9F3Inner *inner = effect->m_vtable;
  inner->m_fn88(effect, parameter, &texelSize);
}
