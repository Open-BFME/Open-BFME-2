// cl: /O1 /arch:SSE /G7 /MD
// Native 0030BEA2..0030BEE6 RET8: a hidden output pointer and signed index.
// This view points 28 bytes past a 16-byte-element vector. Index zero uses
// the first pair; indices 1..count use each element's second pair, then the
// first pairs are visited backwards. Element/layout identities are open.
// The existing BfmeE16 vector indexer supplies only its proven stride ABI.
struct BfmeE16 { float x, y, z, w; };
namespace _STL
{
 template<class T> class allocator;
 template<class T, class A> class vector
 {
 public:
  T &operator[](unsigned index);
  T *first, *last, *capacity;
 };
}
struct Rva0030BEA2Point
{
 float x, y;
 Rva0030BEA2Point(const Rva0030BEA2Point &other) : x(other.x), y(other.y) {}
};
class Rva0030BEA2
{
public:
 Rva0030BEA2Point rva0030BEA2(int index);
};

Rva0030BEA2Point Rva0030BEA2::rva0030BEA2(int index)
{
 typedef _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > Elements;
 Elements *elements = (Elements *)((char *)this - 0x28);
 int count = elements->last - elements->first;
 const Rva0030BEA2Point *point;
 if (index == 0)
  point = (const Rva0030BEA2Point *)&(*elements)[index];
 else if (--index < count)
  point = (const Rva0030BEA2Point *)((const char *)&(*elements)[index] + 8);
 else
  point = (const Rva0030BEA2Point *)&(*elements)[count * 2 - index - 1];
 return *point;
}
