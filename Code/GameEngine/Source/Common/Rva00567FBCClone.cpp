// stlport46
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB
#include <memory>

// Native vtable C6CED8 slot1 returns ownership of a twelve-byte copy.
// Copy ctor567CA6 and base copy567860 contain only vtable/field stores;
// declaring that nonthrowing copy keeps only the result-object EH state.
// FuncInfo D4EF88 has one cleanup through79A179 and pointer destructor2E3A80.
// A named STLport auto_ptr local supplies the exact return transfer and
// otherwise inactive return flag. Original nominal identities are unknown.
class Rva00567860 {public:Rva00567860(const Rva00567860&);virtual ~Rva00567860();};
class Rva00567847:public Rva00567860 {
public:
 Rva00567847(const Rva00567847&) throw();
 virtual _STL::auto_ptr<Rva00567860> rva00567FBC()const;
private:unsigned int first,second;
};
_STL::auto_ptr<Rva00567860> Rva00567847::rva00567FBC()const {
 _STL::auto_ptr<Rva00567860> result(new Rva00567847(*this)); return result;
}
