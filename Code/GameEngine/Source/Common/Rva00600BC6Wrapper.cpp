// cl: /O1 /MD
struct Out5 {
  int a;
  unsigned char b;
};
struct Rva00600991 {
  void rva00600991(void* out, void* arg);
  void rva00600BC6(void* out, void* arg);
};
void Rva00600991::rva00600BC6(void* out, void* arg) {
  Out5 tmp;
  rva00600991(&tmp, arg);
  ((Out5*)out)->a = tmp.a;
  ((Out5*)out)->b = tmp.b;
}
