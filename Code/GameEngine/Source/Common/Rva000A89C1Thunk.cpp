// cl: /O1 /MD
// ?rva000A89C1@Rva00A897D@@QAEXXZ, retail 0x000A89C1, 8 bytes.
// Thunk after clear 0x000A8879; same flags. Outer Rva00A897D holds Rva000A8879 at +0x30 per dtor 0x000A897D; tail-jmp via return member clear gives add ecx 0x30 plus jmp. Caller at 0x0006102A in Rva0060FE2 dtor loads pointer at +0xB90 then calls. Jmp resolves via rowed clear. Honest address method plus pinned outer; no donor.
class Rva0073EE55;
class Rva000A8879
{
public:
  Rva0073EE55* m_ptr;
  void clear();
};
class Rva00A897D
{
public:
  char m_pad[0x30];
  Rva000A8879 m_holder;
  void rva000A89C1();
};

void Rva00A897D::rva000A89C1()
{
  return m_holder.clear();
}
