// ?rva004EBEB7@Rva004EBEB7@@QAE_NXZ
// partial score=0.78 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Oy- /MD
struct Rva004EBE74Item
{
 char pad[0x50];
 unsigned m_50;
};
struct Rva004EBE74Cmp
{
 bool operator()(const Rva004EBE74Item *a, const Rva004EBE74Item *b) const { return a->m_50 < b->m_50; }
};
namespace _STL
{
 template<class Iterator, class Predicate>
 void sort(Iterator first, Iterator last, Predicate predicate);
}
class Rva004EBEB7
{
public:
 bool rva004EBEB7();
 void rva004EBB58();
 char pad0[4];
 Rva004EBE74Item * volatile median;
 Rva004EBE74Item ** volatile first, ** volatile last;
 Rva004EBE74Item **capacity;
 char pad14[0x38 - 0x14];
 unsigned field38;
 char pad3C[4];
 unsigned field40;
};
bool Rva004EBEB7::rva004EBEB7()
{
 if ((unsigned)(last - first) > 1)
 {
  _STL::sort(first, last, Rva004EBE74Cmp());
  unsigned count = (unsigned)(last - first);
  Rva004EBE74Item **begin = first;
  Rva004EBE74Item **end = last;
  Rva004EBE74Item *middle = begin[count / 2];
  median = middle;
  volatile bool valid = true;
  unsigned index = (unsigned)-1;
  for (Rva004EBE74Item **p = first; p != end && valid; ++p)
  {
   if ((*p)->m_50 != ++index)
    valid = false;
  }
  if (valid)
  {
   field38 = middle->m_50;
   field40 = median->m_50;
   rva004EBB58();
   return true;
  }
 }
 return false;
}
