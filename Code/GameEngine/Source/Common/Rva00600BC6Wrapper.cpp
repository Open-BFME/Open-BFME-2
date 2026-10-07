// cl: /O1 /MD
struct Rva00600991Element { const char *key; };
struct Rva00600991Pair { void *first; bool second; };
struct Rva00600991 {
  Rva00600991Pair rva00600991(const Rva00600991Element &value);
  void rva00600BC6(void* out, void* arg);
};
void Rva00600991::rva00600BC6(void* out, void* arg) {
  Rva00600991Pair tmp = rva00600991(*(Rva00600991Element *)arg);
  ((Rva00600991Pair *)out)->first = tmp.first;
  ((Rva00600991Pair *)out)->second = tmp.second;
}
