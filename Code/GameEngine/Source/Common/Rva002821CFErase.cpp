// cl: /DNDEBUG /MD /EHsc /O1 /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Retail evidence: erase 0x002821CF advances in eight-byte records, calls
// copy 0x00281AB7 and destroys the final record with Rva0027EA49::~Rva0027EA49.
// Assignment 0x0027F589 copies the first word and assigns the reference at +4
// through TreeHintRef00217D4C::operator= (0x002174A4). Its two STL copy callers
// therefore use the same record view. The previous DeliverPayloadNugget::Payload
// attribution conflicted with the donor's AsciiString-at-0, integer-at-4 layout.
// The first word's application meaning remains unknown. No donor identity is claimed.
#include <stl/_algobase.h>
struct TargetRef00217D4C;
struct TreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C&);
};
struct Rva0027EA49 {
 int m_00; TreeHintRef00217D4C m_04;
 ~Rva0027EA49();
 Rva0027EA49 &operator=(const Rva0027EA49&);
};
Rva0027EA49 &Rva0027EA49::operator=(const Rva0027EA49 &other){m_00=other.m_00;m_04=other.m_04;return *this;}
template Rva0027EA49 *_STL::__copy<const Rva0027EA49*,Rva0027EA49*,int>(const Rva0027EA49*,const Rva0027EA49*,Rva0027EA49*,const _STL::random_access_iterator_tag&,int*);
template Rva0027EA49 *_STL::__copy_ptrs<const Rva0027EA49*,Rva0027EA49*>(const Rva0027EA49*,const Rva0027EA49*,Rva0027EA49*,const _STL::__false_type&);
struct Rva002821CFElem { char m_pad[8]; };
class Rva002821CF {
public: Rva002821CFElem *erase(Rva002821CFElem*);
const Rva002821CFElem *end(){return m_finish;}
private: Rva002821CFElem *m_start;const Rva002821CFElem *m_finish;Rva002821CFElem *m_endOfStorage;
};
Rva002821CFElem *Rva002821CF::erase(Rva002821CFElem *position){
 _STL::__false_type tag;
 if(position+1!=end())_STL::__copy_ptrs((const Rva0027EA49*)(position+1),(const Rva0027EA49*)m_finish,(Rva0027EA49*)position,tag);
 --m_finish; ((Rva0027EA49*)m_finish)->~Rva0027EA49();return position;
}
