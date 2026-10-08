// cl: /O1 /arch:SSE /G7 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_insert@?$_Rb_tree@VRva00064640Record@@V1@U?$_Identity@VRva00064640Record@@@_STL@@U?$less@VRva00064640Record@@@3@V?$allocator@VRva00064640Record@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@VRva00064640Record@@U?$_Nonconst_traits@VRva00064640Record@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABVRva00064640Record@@0@Z 0x005041F6 137B evidence: unlock Rb_tree insert via rowed create 0x005041B6 plus Rebalance; caller 0x0050456D unblocks 0x00504509; siblings Rva00500500Insert same recipe
#include <set>
// Keep the shared allocator helper declared-only; its verified owner supplies
// the out-of-line copy. Record-node erasure already emits retail direct free.
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
class Rva00064640Record
{
public:
	bool operator<(const Rva00064640Record &other) const { return m_18 < other.m_18; }
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	unsigned int m_18;
};
// Retail erases this trivial payload through free, without a size argument.
// This TU-scoped allocator specialization preserves that established path.
namespace _STL {
template <> __forceinline void allocator<_Rb_tree_node< ::Rva00064640Record > >::deallocate(_Rb_tree_node< ::Rva00064640Record > *p, size_t) const { if(p != 0) free(p); }
}
typedef _STL::_Rb_tree<Rva00064640Record, Rva00064640Record, _STL::_Identity<Rva00064640Record>, _STL::less<Rva00064640Record>, _STL::allocator<Rva00064640Record> > VRva00064640RecordSetTree;
// Declared-only: calls reach the retail-identical _M_create_node in
// stlport_rb_tree_create_nodes.cpp, dropping our wrong COMDAT copies of
// _M_create_node, _Construct and __malloc_alloc::allocate.
template <>
VRva00064640RecordSetTree::_Link_type VRva00064640RecordSetTree::_M_create_node(const VRva00064640RecordSetTree::value_type &);
template VRva00064640RecordSetTree::iterator VRva00064640RecordSetTree::insert_equal(const VRva00064640RecordSetTree::value_type &);
template VRva00064640RecordSetTree::iterator VRva00064640RecordSetTree::insert_equal(VRva00064640RecordSetTree::iterator, const VRva00064640RecordSetTree::value_type &);
template _STL::pair<VRva00064640RecordSetTree::iterator, bool> VRva00064640RecordSetTree::insert_unique(const VRva00064640RecordSetTree::value_type &);
template VRva00064640RecordSetTree::iterator VRva00064640RecordSetTree::insert_unique(VRva00064640RecordSetTree::iterator, const VRva00064640RecordSetTree::value_type &);
typedef _STL::set<Rva00064640Record, _STL::less<Rva00064640Record>, _STL::allocator<Rva00064640Record> > Rva00064640Set;
template _STL::pair<Rva00064640Set::iterator, bool> Rva00064640Set::insert(const Rva00064640Set::value_type &);
struct Rva005045C6
{
	void rva005045C6(const Rva00064640Record &v);
	Rva00064640Set m_set;
};
void Rva005045C6::rva005045C6(const Rva00064640Record &v)
{
	m_set.insert(v);
}

// The retail record transfer uses the existing seven-dword constructor and
// the serializer at 0x00503EB7; no new constructor ownership is inferred.
class Rva00064390 { public: Rva00064390(); float m_00,m_04,m_08,m_0C,m_10,m_14; unsigned int m_18; };
class Rva00503E76;
struct Rva00503E76Arg1;
Rva00503E76Arg1 *__cdecl Rva00503EB7Call(Rva00503E76Arg1 *, Rva00503E76 *);
class Xfer {
public:
 virtual void slot00() = 0;
 virtual bool isLoading() = 0;
 virtual bool isSaving() = 0;
 virtual void slot03() = 0;
 virtual void slot04() = 0;
 virtual void slot05() = 0;
 virtual void slot06() = 0;
 virtual void slot07() = 0;
 virtual void slot08() = 0;
 virtual void slot09() = 0;
 virtual void slot10() = 0;
 virtual void slot11() = 0;
 virtual void slot12() = 0;
 virtual void slot13() = 0;
 virtual void slot14() = 0;
 virtual void slot15() = 0;
 virtual void slot16() = 0;
 virtual void slot17() = 0;
 virtual void slot18() = 0;
 virtual void slot19() = 0;
 virtual void slot20() = 0;
 virtual void slot21() = 0;
 virtual void slot22() = 0;
 virtual void slot23() = 0;
 virtual void slot24() = 0;
 virtual void slot25() = 0;
 virtual void slot26() = 0;
 virtual void slot27() = 0;
 virtual void slot28() = 0;
 virtual void slot29() = 0;
 virtual void slot30() = 0;

 virtual void xferCount(int *) = 0; // retail slot 0x7C
};
class Rva005045E0 {
public:
 void rva005045E0(Xfer *xfer);
private:
 Rva00064640Set m_controlPoints;
};
// WB ControlPoint.cpp names ControlPointBlock::DoXfer. The existing
// address-derived owner preserves its established caller ABI.
void Rva005045E0::rva005045E0(Xfer *xfer) {
 if(xfer->isSaving()) {
  int count = m_controlPoints.size();
  xfer->xferCount(&count);
  for(Rva00064640Set::iterator it=m_controlPoints.begin(); it._M_node != m_controlPoints.end()._M_node; ++it)
   Rva00503EB7Call(reinterpret_cast<Rva00503E76Arg1 *>(xfer), reinterpret_cast<Rva00503E76 *>(const_cast<Rva00064640Record *>(&*it)));
 } else if(xfer->isLoading()) {
  int count;
  xfer->xferCount(&count);
  m_controlPoints.clear();
  Rva00064390 value;
  for(int i=0;i<count;++i) {
   Rva00503EB7Call(reinterpret_cast<Rva00503E76Arg1 *>(xfer), reinterpret_cast<Rva00503E76 *>(&value));
   m_controlPoints.insert(reinterpret_cast<const Rva00064640Record &>(value));
  }
 }
}
