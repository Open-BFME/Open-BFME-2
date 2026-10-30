// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>
#include <vector>

struct Rva004F8C16Element { char bytes[4]; };

// The four native calls already have rowed providers. Their element names
// disagree, so use opaque pointer views of those declarations rather than
// emitting new, non-retail copies of the buffer and merge helpers. These
// views preserve the existing provider names, not an original element identity.
struct TreeHintRef00217D4C;
struct Rva004F9185Cmp {};
class AsciiString;
class Rva004F60AA
{
public:
 __declspec(dllimport) __forceinline Rva004F60AA(char *first, char *last) { rva004F77AD(first,last); }
 ~Rva004F60AA();
 Rva004F60AA *rva004F77AD(char *,char *);
 int m_00;
 int m_04;
 void *m_08;
};

namespace _STL {
template <> void __merge_without_buffer<TreeHintRef00217D4C *,int,Rva004F9185Cmp>(
 TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,int,int,Rva004F9185Cmp);
template <> void __merge_adaptive<AsciiString *,int,AsciiString *,less<AsciiString> >(
 AsciiString *,AsciiString *,AsciiString *,int,int,AsciiString *,int,less<AsciiString>);

template <> void __inplace_merge_aux<Rva004F8C16Element *,Rva004F8C16Element,int,less<Rva004F8C16Element> >(
 Rva004F8C16Element *first,Rva004F8C16Element *middle,Rva004F8C16Element *last,
 Rva004F8C16Element *,int *,less<Rva004F8C16Element> compare)
{
 int left=distance(first,middle);
 int right=distance(middle,last);
 Rva004F60AA buffer(reinterpret_cast<char*>(first),reinterpret_cast<char*>(last));
 if (!buffer.m_08)
  __merge_without_buffer(reinterpret_cast<TreeHintRef00217D4C*>(first),
   reinterpret_cast<TreeHintRef00217D4C*>(middle),reinterpret_cast<TreeHintRef00217D4C*>(last),
   left,right,reinterpret_cast<Rva004F9185Cmp&>(compare));
 else
  __merge_adaptive(reinterpret_cast<AsciiString*>(first),reinterpret_cast<AsciiString*>(middle),
   reinterpret_cast<AsciiString*>(last),left,right,static_cast<AsciiString*>(buffer.m_08),
   buffer.m_04,reinterpret_cast<less<AsciiString>&>(compare));
}
}
