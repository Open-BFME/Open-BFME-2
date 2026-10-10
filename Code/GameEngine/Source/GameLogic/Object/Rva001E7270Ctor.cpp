// Native001E7270..001E72B4 RET0; WBADC820141B confirms subsystem construction.
// Existing vtable BDE970 and its scalar deleting dtor1E7EAE establish the
// address-derived class Rva001E72B4. Base12B is native SubsystemInterface.
// Map atC and pointer vector at18; destructor1E72B4 indexes the latter by4.
// Object* is only the existing folded four-byte-pointer constructor ABI view;
// the concrete pointee and map payload identities remain unresolved.
// Sibling Rva001F092ACtor.cpp supplies the verified map/vector transfer pattern.
// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <vector>
class Object;
class __declspec(novtable) SubsystemInterface {public:SubsystemInterface();virtual ~SubsystemInterface();private:virtual void unused()=0;char flag;int value;};
class Rva001E72B4:public SubsystemInterface {public:Rva001E72B4();private:_STL::map<int,void*> map;_STL::vector<Object*> entries;};
Rva001E72B4::Rva001E72B4(){}
