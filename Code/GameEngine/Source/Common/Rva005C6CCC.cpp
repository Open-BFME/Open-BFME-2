// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport

#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()

struct TargetRef00217D4C {
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct TreeHintRef00217D4C {
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
		if (m_ptr)
			++m_ptr->references;
	}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C() {
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

#include <map>

typedef _STL::pair<const int, TreeHintRef00217D4C> TreeHintPair;
typedef _STL::map<int, TreeHintRef00217D4C> TreeHintMap;

template TreeHintRef00217D4C &TreeHintMap::operator[](const int &);

// Native 0x003596AD is the same signed-key lookup/default-handle pattern.
// Its pair copy 0x00217607 retains the pointee at +4 and its miss-path
// cleanup calls the rowed reference release 0x0007DEEF. The application's
// action type is unresolved; keep this separate address-derived handle view.
struct TreeHintRef003596AD {
 TargetRef00217D4C *m_ptr;
 TreeHintRef003596AD() : m_ptr(0) {}
 TreeHintRef003596AD(const TreeHintRef003596AD &other) : m_ptr(other.m_ptr) {
  if (m_ptr) ++m_ptr->references;
 }
 __forceinline ~TreeHintRef003596AD() {
  if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
 }
};
typedef _STL::map<int, TreeHintRef003596AD> TreeHintMap003596AD;
typedef _STL::map<int, float> TreeHintInsert003596AD;
namespace _STL {
template<> TreeHintInsert003596AD::iterator TreeHintInsert003596AD::insert(TreeHintInsert003596AD::iterator, const TreeHintInsert003596AD::value_type &);
}
// The target's insertion forwarder is independently rowed at 0x0035926E
// with a float spelling. It forwards the iterator and eight-byte pair to
// its tree unchanged; use that proven ABI without making its inferred
// mapped type a target identity or spending another address pin.
template<> TreeHintRef003596AD &TreeHintMap003596AD::operator[](const int &key)
{
 iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  it = iterator(reinterpret_cast<iterator::_Link_type>(
   reinterpret_cast<TreeHintInsert003596AD *>(this)->insert(
    TreeHintInsert003596AD::iterator(reinterpret_cast<TreeHintInsert003596AD::iterator::_Link_type>(it._M_node)),
    reinterpret_cast<const TreeHintInsert003596AD::value_type &>(value_type(key, TreeHintRef003596AD())))._M_node));
 }
 return (*it).second;
}
template class _STL::map<int, TreeHintRef003596AD>;

// Native 0x00218787 has the same signed lookup and counted-handle lifetime
// as newly verified 0x003596AD; all four call targets agree. Earlier banked
// float-map reconstruction lost the temporary destructor and its stack slot.
// The handle layout is now established by the native retain/release pair.
struct TreeHintRef00218787 {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00218787() : m_ptr(0) {}
 TreeHintRef00218787(const TreeHintRef00218787 &other) : m_ptr(other.m_ptr) {
  if (m_ptr) ++m_ptr->references;
 }
 __forceinline ~TreeHintRef00218787() {
  if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
 }
};
typedef _STL::map<int, TreeHintRef00218787> TreeHintMap00218787;
// Reuse the same established insertion ABI as the first specialization.
template<> TreeHintRef00218787 &TreeHintMap00218787::operator[](const int &key)
{
 iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  it = iterator(reinterpret_cast<iterator::_Link_type>(
   reinterpret_cast<TreeHintInsert003596AD *>(this)->insert(
    TreeHintInsert003596AD::iterator(reinterpret_cast<TreeHintInsert003596AD::iterator::_Link_type>(it._M_node)),
    reinterpret_cast<const TreeHintInsert003596AD::value_type &>(value_type(key, TreeHintRef00218787())))._M_node));
 }
 return (*it).second;
}
template class _STL::map<int, TreeHintRef00218787>;
