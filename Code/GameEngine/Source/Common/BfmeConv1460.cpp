// cl: /Od /Ob1
// Native 276B0..27738 proves thiscall with begin/end at +0/+4 and RET12.
// BFME1 ba7ddda7 BfmeConv1460 supplies the search purpose; its historical
// inline-assembly/free-stdcall spelling does not describe the receiver ABI.
// Native five-word call to the owned find-first-of worker includes an empty
// object. The tag and class names are structural views, not recovered names.
// Force-inlined range readers reproduce the retail /Od temporary lifetimes.
struct Rva00026E40Tag {};
const char *bfmeFindFirstOfVMD(const char *, const char *, const char *, const char *, Rva00026E40Tag);

class BfmeThingPF
{
public:
 char *m_begin; // +0
 char *m_end;   // +4
 __forceinline char *begin() const { return m_begin; }
 __forceinline char *end() const { return m_end; }
 int rva000276B0(const char *s, unsigned pos, unsigned n);
};

int BfmeThingPF::rva000276B0(const char *s, unsigned pos, unsigned n)
{
 const char *found;
 Rva00026E40Tag tag;
 if (pos >= (unsigned)(m_end - m_begin))
  return -1;
 found = bfmeFindFirstOfVMD(begin() + pos, end(), s, s + n, tag);
 return found != end() ? (int)(found - begin()) : -1;
}
