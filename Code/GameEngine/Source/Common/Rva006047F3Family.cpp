// cl: /O1 /MD
int __cdecl BFME2Utf8ToWide(const char* src, int srclen, unsigned short* dst, int dstlen);
struct Rva00604xx {
  virtual void _v0();
  virtual void _v1();
  virtual int Virt8(unsigned short* buf, void* a2, void* a3);
  virtual void _v3();
  virtual bool Virt10(unsigned short* buf);
  virtual void _v5();
  virtual void _v6();
  virtual void _v7();
  virtual void _v8();
  virtual int Virt24(unsigned short* buf, void* a2);
  int M7F3(const char* src, void* a2, int a3);
  bool M831(const char* src);
  int M948(const char* src, void* a2);
};
int Rva00604xx::M7F3(const char* src, void* a2, int a3) {
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt8(buf, a2, (void*)a3);
}
bool Rva00604xx::M831(const char* src) {
  if (!src) return false;
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt10(buf);
}
int Rva00604xx::M948(const char* src, void* a2) {
  unsigned short buf[260];
  BFME2Utf8ToWide(src, -1, buf, 260);
  return Virt24(buf, a2);
}
