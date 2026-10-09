// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
// Native2B7C74..2B7D03 RET0: two owning pointer vectorsCC/D8. Actual
// STLport size/index expressions reproduce EBPwhole/EDIandESIheaders and
// zeroEAX reuse. Hand-written pointer headers emitted155B. N1 sibling
// 2B7D91 independently matches the same deleteInstance0/free/erase path;
// identity remains address-derived. Both erase calls use owned31BD55.
class Glo012F1028Entry
{
public:
	virtual void *deleteInstance(int flags);
};

class Rva002B7C74{public:void rva002B7C74();char pad[0xCC];_STL::vector<Glo012F1028Entry*,_STL::allocator<Glo012F1028Entry*> > first,second;};
void Rva002B7C74::rva002B7C74(){
 for(unsigned i=0;i<first.size();++i)::operator delete(first[i]?first[i]->deleteInstance(0):0);
 for(unsigned i=0;i<second.size();++i)::operator delete(second[i]?second[i]->deleteInstance(0):0);
 _STL::vector<void*,_STL::allocator<void*> >&a=(_STL::vector<void*,_STL::allocator<void*> >&)first;
 _STL::vector<void*,_STL::allocator<void*> >&b=(_STL::vector<void*,_STL::allocator<void*> >&)second;
 a.erase(a.begin(),a.end());b.erase(b.begin(),b.end());
}
