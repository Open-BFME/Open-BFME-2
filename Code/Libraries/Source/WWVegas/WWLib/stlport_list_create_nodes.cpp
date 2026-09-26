// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Batch _M_create_node family recovery (generated): one explicit
// specialization per sibling, each proven by its own retail call
// displacement to a rowed _Construct plus the allocate size fixing
// the value size. Custom No-exceptions MALLOC shape from
// stlport_rb_tree_hint_asciistring_set (no allocation-cleanup catch
// path); each _Construct is declared only so its call resolves
// through its own row.
#include <map>
#include <set>
#include <list>
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

class Rva0036CA00Str { public: unsigned char m_data[4]; };
struct BfmeStringRecord000B75AE { public: unsigned char m_data[32]; };
struct BfmeStringRecord000B757D { public: unsigned char m_data[20]; };
struct BfmeFloat4Record00469C61 { public: unsigned char m_data[16]; };
struct BfmeStringRecord001EA478 { public: unsigned char m_data[8]; };
class RvaSmartPtr12 { public: unsigned char m_data[12]; };
struct BfmeStringRecord00239B46 { public: unsigned char m_data[8]; };
struct BfmeStringRecord002B4DC1 { public: unsigned char m_data[12]; };
struct BfmeStringRecord00415F34 { public: unsigned char m_data[24]; };
struct BfmeContainerRecord00462D62 { public: unsigned char m_data[32]; };
struct BfmeStringRecord005BC576 { public: unsigned char m_data[28]; };

// ?_M_create_node@?$list@VRva0036CA00Str@@V?$allocator@VRva0036CA00Str@@@_STL@@@_STL@@IAEPAU?$_List_node@VRva0036CA00Str@@@2@ABVRva0036CA00Str@@@Z
namespace _STL {
template <> void _Construct<Rva0036CA00Str>(Rva0036CA00Str *, Rva0036CA00Str const &);
}
template <>
_STL::_List_node<Rva0036CA00Str> *_STL::list<Rva0036CA00Str, _STL::allocator<Rva0036CA00Str> >::_M_create_node(Rva0036CA00Str const &__x)
{
	_STL::_List_node<Rva0036CA00Str> *__p =
		(_STL::_List_node<Rva0036CA00Str> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<Rva0036CA00Str>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<Rva0036CA00Str> *_STL::list<Rva0036CA00Str, _STL::allocator<Rva0036CA00Str> >::_M_create_node(Rva0036CA00Str const &);

// ?_M_create_node@?$list@UBfmeStringRecord000B75AE@@V?$allocator@UBfmeStringRecord000B75AE@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeStringRecord000B75AE@@@2@ABUBfmeStringRecord000B75AE@@@Z
namespace _STL {
template <> void _Construct<BfmeStringRecord000B75AE>(BfmeStringRecord000B75AE *, BfmeStringRecord000B75AE const &);
}
template <>
_STL::_List_node<BfmeStringRecord000B75AE> *_STL::list<BfmeStringRecord000B75AE, _STL::allocator<BfmeStringRecord000B75AE> >::_M_create_node(BfmeStringRecord000B75AE const &__x)
{
	_STL::_List_node<BfmeStringRecord000B75AE> *__p =
		(_STL::_List_node<BfmeStringRecord000B75AE> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeStringRecord000B75AE>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeStringRecord000B75AE> *_STL::list<BfmeStringRecord000B75AE, _STL::allocator<BfmeStringRecord000B75AE> >::_M_create_node(BfmeStringRecord000B75AE const &);

// ?_M_create_node@?$list@UBfmeStringRecord000B757D@@V?$allocator@UBfmeStringRecord000B757D@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeStringRecord000B757D@@@2@ABUBfmeStringRecord000B757D@@@Z
namespace _STL {
template <> void _Construct<BfmeStringRecord000B757D>(BfmeStringRecord000B757D *, BfmeStringRecord000B757D const &);
}
template <>
_STL::_List_node<BfmeStringRecord000B757D> *_STL::list<BfmeStringRecord000B757D, _STL::allocator<BfmeStringRecord000B757D> >::_M_create_node(BfmeStringRecord000B757D const &__x)
{
	_STL::_List_node<BfmeStringRecord000B757D> *__p =
		(_STL::_List_node<BfmeStringRecord000B757D> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeStringRecord000B757D>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeStringRecord000B757D> *_STL::list<BfmeStringRecord000B757D, _STL::allocator<BfmeStringRecord000B757D> >::_M_create_node(BfmeStringRecord000B757D const &);

// ?_M_create_node@?$list@UBfmeFloat4Record00469C61@@V?$allocator@UBfmeFloat4Record00469C61@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeFloat4Record00469C61@@@2@ABUBfmeFloat4Record00469C61@@@Z
namespace _STL {
template <> void _Construct<BfmeFloat4Record00469C61>(BfmeFloat4Record00469C61 *, BfmeFloat4Record00469C61 const &);
}
template <>
_STL::_List_node<BfmeFloat4Record00469C61> *_STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::_M_create_node(BfmeFloat4Record00469C61 const &__x)
{
	_STL::_List_node<BfmeFloat4Record00469C61> *__p =
		(_STL::_List_node<BfmeFloat4Record00469C61> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeFloat4Record00469C61>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeFloat4Record00469C61> *_STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::_M_create_node(BfmeFloat4Record00469C61 const &);

// ?_M_create_node@?$list@UBfmeStringRecord001EA478@@V?$allocator@UBfmeStringRecord001EA478@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeStringRecord001EA478@@@2@ABUBfmeStringRecord001EA478@@@Z
namespace _STL {
template <> void _Construct<BfmeStringRecord001EA478>(BfmeStringRecord001EA478 *, BfmeStringRecord001EA478 const &);
}
template <>
_STL::_List_node<BfmeStringRecord001EA478> *_STL::list<BfmeStringRecord001EA478, _STL::allocator<BfmeStringRecord001EA478> >::_M_create_node(BfmeStringRecord001EA478 const &__x)
{
	_STL::_List_node<BfmeStringRecord001EA478> *__p =
		(_STL::_List_node<BfmeStringRecord001EA478> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeStringRecord001EA478>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeStringRecord001EA478> *_STL::list<BfmeStringRecord001EA478, _STL::allocator<BfmeStringRecord001EA478> >::_M_create_node(BfmeStringRecord001EA478 const &);

// ?_M_create_node@?$list@VRvaSmartPtr12@@V?$allocator@VRvaSmartPtr12@@@_STL@@@_STL@@IAEPAU?$_List_node@VRvaSmartPtr12@@@2@ABVRvaSmartPtr12@@@Z
namespace _STL {
template <> void _Construct<RvaSmartPtr12>(RvaSmartPtr12 *, RvaSmartPtr12 const &);
}
template <>
_STL::_List_node<RvaSmartPtr12> *_STL::list<RvaSmartPtr12, _STL::allocator<RvaSmartPtr12> >::_M_create_node(RvaSmartPtr12 const &__x)
{
	_STL::_List_node<RvaSmartPtr12> *__p =
		(_STL::_List_node<RvaSmartPtr12> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<RvaSmartPtr12>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<RvaSmartPtr12> *_STL::list<RvaSmartPtr12, _STL::allocator<RvaSmartPtr12> >::_M_create_node(RvaSmartPtr12 const &);

// ?_M_create_node@?$list@UBfmeStringRecord00239B46@@V?$allocator@UBfmeStringRecord00239B46@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeStringRecord00239B46@@@2@ABUBfmeStringRecord00239B46@@@Z
namespace _STL {
template <> void _Construct<BfmeStringRecord00239B46>(BfmeStringRecord00239B46 *, BfmeStringRecord00239B46 const &);
}
template <>
_STL::_List_node<BfmeStringRecord00239B46> *_STL::list<BfmeStringRecord00239B46, _STL::allocator<BfmeStringRecord00239B46> >::_M_create_node(BfmeStringRecord00239B46 const &__x)
{
	_STL::_List_node<BfmeStringRecord00239B46> *__p =
		(_STL::_List_node<BfmeStringRecord00239B46> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeStringRecord00239B46>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeStringRecord00239B46> *_STL::list<BfmeStringRecord00239B46, _STL::allocator<BfmeStringRecord00239B46> >::_M_create_node(BfmeStringRecord00239B46 const &);

// ?_M_create_node@?$list@UBfmeStringRecord002B4DC1@@V?$allocator@UBfmeStringRecord002B4DC1@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeStringRecord002B4DC1@@@2@ABUBfmeStringRecord002B4DC1@@@Z
namespace _STL {
template <> void _Construct<BfmeStringRecord002B4DC1>(BfmeStringRecord002B4DC1 *, BfmeStringRecord002B4DC1 const &);
}
template <>
_STL::_List_node<BfmeStringRecord002B4DC1> *_STL::list<BfmeStringRecord002B4DC1, _STL::allocator<BfmeStringRecord002B4DC1> >::_M_create_node(BfmeStringRecord002B4DC1 const &__x)
{
	_STL::_List_node<BfmeStringRecord002B4DC1> *__p =
		(_STL::_List_node<BfmeStringRecord002B4DC1> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeStringRecord002B4DC1>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeStringRecord002B4DC1> *_STL::list<BfmeStringRecord002B4DC1, _STL::allocator<BfmeStringRecord002B4DC1> >::_M_create_node(BfmeStringRecord002B4DC1 const &);

// ?_M_create_node@?$list@UBfmeStringRecord00415F34@@V?$allocator@UBfmeStringRecord00415F34@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeStringRecord00415F34@@@2@ABUBfmeStringRecord00415F34@@@Z
namespace _STL {
template <> void _Construct<BfmeStringRecord00415F34>(BfmeStringRecord00415F34 *, BfmeStringRecord00415F34 const &);
}
template <>
_STL::_List_node<BfmeStringRecord00415F34> *_STL::list<BfmeStringRecord00415F34, _STL::allocator<BfmeStringRecord00415F34> >::_M_create_node(BfmeStringRecord00415F34 const &__x)
{
	_STL::_List_node<BfmeStringRecord00415F34> *__p =
		(_STL::_List_node<BfmeStringRecord00415F34> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeStringRecord00415F34>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeStringRecord00415F34> *_STL::list<BfmeStringRecord00415F34, _STL::allocator<BfmeStringRecord00415F34> >::_M_create_node(BfmeStringRecord00415F34 const &);

// ?_M_create_node@?$list@UBfmeContainerRecord00462D62@@V?$allocator@UBfmeContainerRecord00462D62@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeContainerRecord00462D62@@@2@ABUBfmeContainerRecord00462D62@@@Z
namespace _STL {
template <> void _Construct<BfmeContainerRecord00462D62>(BfmeContainerRecord00462D62 *, BfmeContainerRecord00462D62 const &);
}
template <>
_STL::_List_node<BfmeContainerRecord00462D62> *_STL::list<BfmeContainerRecord00462D62, _STL::allocator<BfmeContainerRecord00462D62> >::_M_create_node(BfmeContainerRecord00462D62 const &__x)
{
	_STL::_List_node<BfmeContainerRecord00462D62> *__p =
		(_STL::_List_node<BfmeContainerRecord00462D62> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeContainerRecord00462D62>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeContainerRecord00462D62> *_STL::list<BfmeContainerRecord00462D62, _STL::allocator<BfmeContainerRecord00462D62> >::_M_create_node(BfmeContainerRecord00462D62 const &);

// ?_M_create_node@?$list@PAXV?$allocator@PAX@_STL@@@_STL@@IAEPAU?$_List_node@PAX@2@ABQAX@Z
namespace _STL {
template <> void _Construct<void *>(void * *, void * const &);
}
template <>
_STL::_List_node<void *> *_STL::list<void *, _STL::allocator<void *> >::_M_create_node(void * const &__x)
{
	_STL::_List_node<void *> *__p =
		(_STL::_List_node<void *> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<void *>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<void *> *_STL::list<void *, _STL::allocator<void *> >::_M_create_node(void * const &);

// ?_M_create_node@?$list@UBfmeStringRecord005BC576@@V?$allocator@UBfmeStringRecord005BC576@@@_STL@@@_STL@@IAEPAU?$_List_node@UBfmeStringRecord005BC576@@@2@ABUBfmeStringRecord005BC576@@@Z
namespace _STL {
template <> void _Construct<BfmeStringRecord005BC576>(BfmeStringRecord005BC576 *, BfmeStringRecord005BC576 const &);
}
template <>
_STL::_List_node<BfmeStringRecord005BC576> *_STL::list<BfmeStringRecord005BC576, _STL::allocator<BfmeStringRecord005BC576> >::_M_create_node(BfmeStringRecord005BC576 const &__x)
{
	_STL::_List_node<BfmeStringRecord005BC576> *__p =
		(_STL::_List_node<BfmeStringRecord005BC576> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<BfmeStringRecord005BC576>), 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}
template _STL::_List_node<BfmeStringRecord005BC576> *_STL::list<BfmeStringRecord005BC576, _STL::allocator<BfmeStringRecord005BC576> >::_M_create_node(BfmeStringRecord005BC576 const &);
