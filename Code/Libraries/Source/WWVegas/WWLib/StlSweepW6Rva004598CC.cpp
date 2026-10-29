// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
#include <deque>
#include <memory>
#include <utility>

struct Rva004598CCElement { unsigned char words[1];bool operator<(const Rva004598CCElement&)const;bool operator==(const Rva004598CCElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva004598CCElement ** _STL::__copy_aux<Rva004598CCElement **, Rva004598CCElement **>(Rva004598CCElement **, Rva004598CCElement **, Rva004598CCElement **, _STL::__true_type);

// Native Object-vector copy1F206E passes the dispatch tag by const reference,
// as corroborated by WB B095A0. Keep the by-value shim overload above for
// its existing owner; this stock-STLport signature folds to the same complete
// 21B pointer-copy body and the same __copy_trivial REL32 at179B0.
class Object;
namespace _STL {
template<class Input,class Output> inline Output __copy_aux(Input first,Input last,Output result,const __true_type&) {
 return (Output)__copy_trivial(first,last,result);
}
}
template Object** _STL::__copy_aux<Object**,Object**>(Object**,Object**,Object**,const _STL::__true_type&);
