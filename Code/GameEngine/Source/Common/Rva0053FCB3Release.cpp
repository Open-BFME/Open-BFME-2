// cl: /O1
// ?rva0053FCB3@Rva0053FCB3@@QAEXXZ @ 0x0053FCB3 12B
// Evidence: chain from rowed Release 0x0053FA32; holder at +0 per setter siblings 0x0053FC81/0x0053FC99; callers are EH funclet jmps.
class Rva0053FA0A {
public:
  void rva0053FA32();
};
class Rva0053FCB3 {
public:
  void rva0053FCB3();
private:
  Rva0053FA0A *m_ptr;
};
void Rva0053FCB3::rva0053FCB3()
{
  if (m_ptr) {
    m_ptr->rva0053FA32();
  }
}
