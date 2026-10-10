// cl: /O1 /EHsc /MD /D_CRTIMP=
// Native18C533..18C54E,27B. STLport copy category dispatch guide.
// Four native argument channels are forwarded to owned18C3C9; its fourth
// metadata argument is unused. Input nodes and destination are opaque at
// this boundary; no application record or original template name is asserted.
namespace _STL {struct __false_type {};}
struct Rva0018C2E7Node;
short *__cdecl Rva0018C3C9Copy(Rva0018C2E7Node*,Rva0018C2E7Node*,short*,const _STL::__false_type&);
struct Rva0018C533Input;
struct Rva0018C533Output;
Rva0018C533Output *__cdecl Rva0018C533RangeForward(Rva0018C533Input *first,Rva0018C533Input *last,Rva0018C533Output *result) {
 _STL::__false_type category;
 return reinterpret_cast<Rva0018C533Output*>(Rva0018C3C9Copy(reinterpret_cast<Rva0018C2E7Node*>(first),reinterpret_cast<Rva0018C2E7Node*>(last),reinterpret_cast<short*>(result),category));
}
