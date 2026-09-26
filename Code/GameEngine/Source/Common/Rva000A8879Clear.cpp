// cl: /O1 /MD
// ?clear@Rva000A8879@@QAEXXZ, retail 0x000A8879, 26 bytes.
// Gap between scalar deleting 0x000A883A and thunk 0x000A8A1F; same flags as OpaqueScalarDeletingDtors.
// Holder at +0x30 of Rva00A897D whose dtor at 0x000A897D calls with this+0x30 at 0x000A89A4 plus thunk at 0x000A89C1; clears single Rva0073EE55 pointer at +0 via qualified dtor plus rowed operator delete 0x0002FD60. Direct call via pin ??1Rva0073EE55. Honest Rva class and clear name; no donor.
void __cdecl operator delete(void* p);

class Rva0073EE55
{
public:
  virtual ~Rva0073EE55();
};

class Rva000A8879
{
public:
  Rva0073EE55* m_ptr;
  void clear();
};

void Rva000A8879::clear()
{
  Rva0073EE55* p = m_ptr;
  m_ptr = 0;
  if (p)
  {
    p->Rva0073EE55::~Rva0073EE55();
    ::operator delete(p);
  }
}
