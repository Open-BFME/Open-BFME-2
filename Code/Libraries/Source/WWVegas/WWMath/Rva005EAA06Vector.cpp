// cl: /DNDEBUG /MD /EHs-c-
// ?rva005EAA06@Rva005EAA06@@QAEXHHH@Z @0x005EAA06 53B vector-like allocate fill chain from 0x005EA1B1
// allocate via rowed _STL allocator for 4B elements then fill float from int
struct BfmeE12;
namespace _STL {
template<class T> class allocator
{
public:
  T *allocate(unsigned int n, const void *hint) const;
};
}
float *Rva005EA1B1Fill(float *dest, int count, const int &value);
class Rva005EAA06
{
public:
  void rva005EAA06(int n, int val, int unused);
private:
  float *m_start;
  float *m_finish;
  float *m_end;
};
void Rva005EAA06::rva005EAA06(int n, int val, int unused)
{
  _STL::allocator<BfmeE12 *> *alloc = (_STL::allocator<BfmeE12 *> *)&m_end;
  float *start = (float *)alloc->allocate(n, 0);
  m_end = start + n;
  m_start = start;
  m_finish = Rva005EA1B1Fill(start, n, val);
}
