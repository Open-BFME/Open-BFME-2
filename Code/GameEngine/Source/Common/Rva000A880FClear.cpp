// cl: /O1 /MD
// ?clear@Rva000A880F@@QAEXXZ, retail 0x000A880F, 30 bytes.
// Gap between scalar deletings 0x000A87F3 and 0x000A883A in OpaqueScalarDeletingDtors.cpp; same flags.
// Holder at +4 of Rva0073EE55 whose dtor at 0x0073EE55 calls with this+4 at 0x0073EE94; clears single pointer at +0 via third virtual taking 0 returning void* then rowed operator delete 0x0002FD60. Single shared delete epilogue with xor for null path. Honest Rva class and clear name; no donor.
void __cdecl operator delete(void* p);

struct VirtBase3
{
  virtual void f0();
  virtual void f1();
  virtual void* func(int x);
};

class Rva000A880F
{
public:
  VirtBase3* m_ptr;
  void clear();
};

void Rva000A880F::clear()
{
  VirtBase3* p = m_ptr;
  m_ptr = 0;
  void* q;
  if (p)
  {
    q = p->func(0);
  }
  else
  {
    q = 0;
  }
  ::operator delete(q);
}
