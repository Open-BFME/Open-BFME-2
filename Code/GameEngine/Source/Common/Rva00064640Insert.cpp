// cl: /O1 /arch:SSE /G7 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport46
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
template <> __forceinline void allocator<_Rb_tree_node< ::Rva00064640Record > >::deallocate(_Rb_tree_node< ::Rva00064640Record > *p, size_t) { if(p != 0) free(p); }
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
	void addControlPoint(const Rva00064640Record &v);
	Rva00064640Set m_set;
};
void Rva005045C6::addControlPoint(const Rva00064640Record &v)
{
	m_set.insert(v);
}

// The retail record transfer uses the existing seven-dword constructor and
// the serializer at 0x00503EB7; no new constructor ownership is inferred.
class Rva00064390 { public: Rva00064390(); float m_00,m_04,m_08,m_0C,m_10,m_14; unsigned int m_18; };
class Rva00503E76;
struct Rva00503E76Arg1;
Rva00503E76Arg1 *__cdecl Rva00503EB7Call(Rva00503E76Arg1 *, Rva00503E76 *);
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"
class ControlPointBlock {
public:
 void DoXfer(Xfer *xfer);
private:
 Rva00064640Set m_controlPoints;
};
// WB ControlPoint.cpp names ControlPointBlock::DoXfer. The existing
// address-derived owner preserves its established caller ABI.
void ControlPointBlock::DoXfer(Xfer *xfer) {
 if(xfer->IsStoring()) {
  int count = m_controlPoints.size();
  (*xfer == count);
  for(Rva00064640Set::iterator it=m_controlPoints.begin(); it._M_node != m_controlPoints.end()._M_node; ++it)
   Rva00503EB7Call(reinterpret_cast<Rva00503E76Arg1 *>(xfer), reinterpret_cast<Rva00503E76 *>(const_cast<Rva00064640Record *>(&*it)));
 } else if(xfer->IsLoading()) {
  int count;
  (*xfer == count);
  m_controlPoints.clear();
  Rva00064390 value;
  for(int i=0;i<count;++i) {
   Rva00503EB7Call(reinterpret_cast<Rva00503E76Arg1 *>(xfer), reinterpret_cast<Rva00503E76 *>(&value));
   m_controlPoints.insert(reinterpret_cast<const Rva00064640Record &>(value));
  }
 }
}

// ?rva004E12BC@Rva004E12BCOwner@@QAEXABVRva00064640Record@@@Z @0x004E12BC 8B: offsets this to the Rva005045C6 embedded at +0xC and
// tail-jumps Rva005045C6::rva005045C6. Owner and name are address-derived; no
// referencing site was found in this pass.
class Rva004E12BCOwner
{
public:
	void rva004E12BC(const Rva00064640Record &v);
};

void Rva004E12BCOwner::rva004E12BC(const Rva00064640Record &v)
{
	((Rva005045C6 *)((char *)this + 0xC))->addControlPoint(v);
}

// ?rva004E149D@Rva004E149DOwner@@QAEXABVRva00064640Record@@@Z @0x004E149D 8B: offsets this to the Rva005045C6 embedded at +0x4 and
// tail-jumps Rva005045C6::rva005045C6. Owner and name are address-derived; no
// referencing site was found in this pass.
class Rva004E149DOwner
{
public:
	void rva004E149D(const Rva00064640Record &v);
};

void Rva004E149DOwner::rva004E149D(const Rva00064640Record &v)
{
	((Rva005045C6 *)((char *)this + 0x4))->addControlPoint(v);
}
