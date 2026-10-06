// ?Clone@Rva005FACC1@@QAEPAPAXPAPAX@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /Oy- /MD
struct PayloadACC1 { int v[2]; };
struct Rva005FACC1 {
  virtual void _vf() {}
  int m_ref;
  PayloadACC1 m_data;
  __forceinline Rva005FACC1(const PayloadACC1& o) : m_ref(0), m_data(o) {}
  void** Clone(void** out);
};
void** Rva005FACC1::Clone(void** out) {
  volatile int _s = 0;
  (void)_s;
  Rva005FACC1* p = new Rva005FACC1(m_data);
  *out = (void*)p;
  if (p) ++p->m_ref;
  return out;
}
