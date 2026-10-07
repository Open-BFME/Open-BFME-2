// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::erase(first, last) for element types whose 51-byte
// range erase sits unclaimed in retail, plus the out-of-line helpers the erase
// calls where those are unclaimed too.  Every erase has the same shape:
//
//   pointer __i = __copy_ptrs(__last, _M_finish, __first, _TrivialAss());
//   _Destroy(__i, _M_finish);  _M_finish = __i;  return __first;
//
// __copy_ptrs is the 29-byte forwarder into __copy (iterator-category tag in a
// pushed-ecx byte, null distance) and _Destroy the 24-byte forwarder into
// __destroy_aux (__false_type tag likewise).  Retail calls both out of line.
//
// Code-generation note: retail passes the erase's empty __false_type temporary
// as lea [ebp+0Bh] with no store.  MSVC 7.1 emits that only when the
// __copy_ptrs body is visible in the unit (it then drops the zero-fill of the
// unused tag); a declaration alone gives xor/stosb zeroing or [ebp+0Fh], the
// wall earlier attempts on these addresses stopped at.  So __copy_ptrs is
// defined here (noinline: retail never inlines it) and its instantiations are
// select-any COMDATs; _Destroy is defined only for the types whose retail
// forwarder this unit lands.
//
// Element types are code-generation views: incomplete, named after an
// existing ledger/pin spelling of the same vector's helpers where that
// spelling is unique to this erase, otherwise after the erase address.  No
// element layout is claimed.  Callees named differently in the ledger are
// pinned in reverse/symbols.csv at the address the retail REL32 proves.
//
//   erase       __copy_ptrs  _Destroy    element
//   0x0004CD7C  0x0004CD20*  0x0004CD64*  RvaSmartPtr12
//   0x00056B72  0x00054E23   0x00054ED9   BfmeStringTailRecord144
//   0x00079EA1  0x0007942F*  0x00405337   Rva00079EA1Element
//   0x0007A7AA  0x0007A401   0x000798BE   basic_string<char>
//   0x000819EC  0x004F6A35   0x005F97BC*  TreeHintRef00217D4C
//   0x000C1CAE  0x000B9615*  0x000BDD08   Rva000C1CAEElement
//   0x000C4D89  0x000C47B2   0x000BD2A6   Rva00079554Record
//   0x000C690C  0x000C2483*  0x000C37E6   Rva000BEDF0Record
//   0x00150659  0x00150248   0x005A6EDA   Rva00150659Element
//   0x00152157  0x0015207E*  0x0015209B   Rva00151DAB
//   0x00153C2C  0x00153B99*  0x00153BB6   Rva00153729
//   0x001D9D24  0x001D9B87*  0x001D9CCC   BfmeStringTailRecord156
//   0x001DEF38  0x001DEE1F*  0x001DEEE0   Rva001DEF38Element
//   0x00213949  0x00211F50*  0x00212AD6   Rva00213949Element
//   0x00239EA5  0x00239B29   0x00054F94   OpaqueRefElement4
//   0x002A7644  0x000B6569   0x002A752F   BfmePod12
//   0x002BBB96  0x002BAD95   0x002BB6A5   Rva002BBB96Element
//   0x002DCFEE  0x002DC593*  0x0022C8E3   Rva002DCFEEElement
//   0x002E2690  0x002E1E9A   0x002AF4ED*  Rva002E2690Element
//   0x00319B97  0x0031968A   0x00319784   Elem003AF9E0
//   0x0032BEE8  0x0032A40E   0x0032B580   Rva0032A3A9Element
//   0x00312C44  0x003120FB*  0x0008B632   BfmeStringHeadRecord184
//   0x0033790F  0x00337533   0x003376D1   Rva003371B1
//   0x003B908A  0x003B8B44   0x003B8E13   BfmeAssignRecord104
//   0x003F5EC4  0x003F5B3E*  0x003F592A   Rva003F610FElement
//   0x003F6975  0x003F6619   0x003F6636   BfmeStringRecord00111ACF
//   0x004043AE  0x00403BD2   0x00214B09   Rva004043AEElement
//   0x0040538F  0x00404CD8*  0x00405337   Rva0040538FElement
//   0x0040DC56  0x002B4410*  0x002B61C5*  Rva0040DC56Element
//   0x00414760  0x00414403   0x004144F0   BfmeAssignRecord44
//   0x00426BB2  0x00426B29   0x0032C0CA   BfmeStringRecord00426A5B
//   0x004286AF  0x004284F5*  0x002385E6   BfmeNarrowRecord00427F75
//   0x004758F4  0x00474125   0x00470398   Rva004758F4Element
//   0x0052016A  0x00520072   0x005200F4   Rva00520211Element
//   0x00565865  0x00565601*  0x005A6EDA   Rva00565865Element
//   0x005658CB  0x005656AA*  0x0022C8E3   Rva005658CBElement
//   0x005658FE  0x005656C7*  0x0052C3BF   Rva005658FEElement
//   0x00565931  0x00565709*  0x0022C8E3   Rva00565931Element
//   0x00565964  0x005657E1*  0x00319784   Rva00565964Element
//   0x00565997  0x00565795*  0x0052C37A   Rva00565997Element
//   0x00566A42  0x00566920*  0x004E1FCC   Rva00566A42Element
//   0x00586E86  0x00586DBF   0x00586B92   Rva00586E86Element
//   0x005DC408  0x005DBDDA*  0x005A6EDA   Rva005DC408Element
//   0x005EF8FA  0x005EF53A*  0x005EF5EF   Rva005EF8FAElement
//   0x005F8620  0x005F85AB*  0x005F85C8   Rva005F8620Element
//   (* = landed from this unit as well)

namespace _STL
{

typedef int ptrdiff_t;

struct __false_type
{
};

struct random_access_iterator_tag
{
};

template <class _Tp>
class allocator
{
};

template <class _CharT>
class char_traits;

template <class _CharT, class _Traits, class _Alloc>
class basic_string;

template <class _InputIter, class _OutputIter, class _Distance>
_OutputIter __copy(_InputIter __first, _InputIter __last, _OutputIter __result,
	const random_access_iterator_tag &, _Distance *);

template <class _InputIter, class _OutputIter>
inline __declspec(noinline) _OutputIter __copy_ptrs(_InputIter __first, _InputIter __last,
	_OutputIter __result, const __false_type &)
{
	random_access_iterator_tag __category;
	return __copy(__first, __last, __result, __category, (ptrdiff_t *)0);
}

template <class _ForwardIterator>
void __destroy_aux(_ForwardIterator __first, _ForwardIterator __last, const __false_type &);

template <class _ForwardIterator>
void _Destroy(_ForwardIterator __first, _ForwardIterator __last);

template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	typedef _Tp *pointer;
	typedef _Tp *iterator;

	iterator erase(iterator __first, iterator __last)
	{
		pointer __i = __copy_ptrs(__last, this->_M_finish, __first, __false_type());
		_Destroy(__i, this->_M_finish);
		this->_M_finish = __i;
		return __first;
	}

protected:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};

}

class RvaSmartPtr12;
struct BfmeStringTailRecord144;
struct Rva00079EA1Element;
struct TreeHintRef00217D4C;
struct Rva000C1CAEElement;
struct Rva00079554Record;
struct Rva000BEDF0Record;
struct Rva00150659Element;
class Rva00151DAB;
struct Rva00153729;
class BfmeStringTailRecord156;
struct Rva001DEF38Element;
struct Rva00213949Element;
struct OpaqueRefElement4;
struct BfmePod12;
struct Rva002BBB96Element;
struct Rva002DCFEEElement;
struct Rva002E2690Element;
struct Elem003AF9E0;
class Rva0032A3A9Element;
class Rva003371B1;
struct Rva003F610FElement;
struct BfmeStringHeadRecord184;
struct BfmeAssignRecord104;
struct BfmeStringRecord00111ACF;
struct Rva004043AEElement;
struct Rva0040538FElement;
struct Rva0040DC56Element;
struct BfmeAssignRecord44;
struct BfmeStringRecord00426A5B;
struct BfmeNarrowRecord00427F75;
struct Rva004758F4Element;
struct Rva00520211Element;
struct Rva00565865Element;
struct Rva005658CBElement;
struct Rva005658FEElement;
struct Rva00565931Element;
struct Rva00565964Element;
struct Rva00565997Element;
struct Rva00566A42Element;
struct Rva00586E86Element;
struct Rva005DC408Element;
struct Rva005EF8FAElement;
struct Rva005F8620Element;

template <>
inline __declspec(noinline) void _STL::_Destroy<RvaSmartPtr12 *>(RvaSmartPtr12 *__first, RvaSmartPtr12 *__last)
{
	_STL::__false_type __trivial;
	_STL::__destroy_aux(__first, __last, __trivial);
}

template <>
inline __declspec(noinline) void _STL::_Destroy<TreeHintRef00217D4C *>(TreeHintRef00217D4C *__first, TreeHintRef00217D4C *__last)
{
	_STL::__false_type __trivial;
	_STL::__destroy_aux(__first, __last, __trivial);
}

template <>
inline __declspec(noinline) void _STL::_Destroy<Rva002E2690Element *>(Rva002E2690Element *__first, Rva002E2690Element *__last)
{
	_STL::__false_type __trivial;
	_STL::__destroy_aux(__first, __last, __trivial);
}

template <>
inline __declspec(noinline) void _STL::_Destroy<Rva0040DC56Element *>(Rva0040DC56Element *__first, Rva0040DC56Element *__last)
{
	_STL::__false_type __trivial;
	_STL::__destroy_aux(__first, __last, __trivial);
}

template RvaSmartPtr12 *_STL::vector<RvaSmartPtr12 >::erase(RvaSmartPtr12 *, RvaSmartPtr12 *);
template BfmeStringTailRecord144 *_STL::vector<BfmeStringTailRecord144 >::erase(BfmeStringTailRecord144 *, BfmeStringTailRecord144 *);
template Rva00079EA1Element *_STL::vector<Rva00079EA1Element >::erase(Rva00079EA1Element *, Rva00079EA1Element *);
template _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *_STL::vector<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > >::erase(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *, _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *);
template TreeHintRef00217D4C *_STL::vector<TreeHintRef00217D4C >::erase(TreeHintRef00217D4C *, TreeHintRef00217D4C *);
template Rva000C1CAEElement *_STL::vector<Rva000C1CAEElement >::erase(Rva000C1CAEElement *, Rva000C1CAEElement *);
template Rva00079554Record *_STL::vector<Rva00079554Record >::erase(Rva00079554Record *, Rva00079554Record *);
template Rva000BEDF0Record *_STL::vector<Rva000BEDF0Record >::erase(Rva000BEDF0Record *, Rva000BEDF0Record *);
template Rva00150659Element *_STL::vector<Rva00150659Element >::erase(Rva00150659Element *, Rva00150659Element *);
template Rva00151DAB *_STL::vector<Rva00151DAB >::erase(Rva00151DAB *, Rva00151DAB *);
template Rva00153729 *_STL::vector<Rva00153729 >::erase(Rva00153729 *, Rva00153729 *);
template BfmeStringTailRecord156 *_STL::vector<BfmeStringTailRecord156 >::erase(BfmeStringTailRecord156 *, BfmeStringTailRecord156 *);
template Rva001DEF38Element *_STL::vector<Rva001DEF38Element >::erase(Rva001DEF38Element *, Rva001DEF38Element *);
template Rva00213949Element *_STL::vector<Rva00213949Element >::erase(Rva00213949Element *, Rva00213949Element *);
template OpaqueRefElement4 *_STL::vector<OpaqueRefElement4 >::erase(OpaqueRefElement4 *, OpaqueRefElement4 *);
template BfmePod12 *_STL::vector<BfmePod12 >::erase(BfmePod12 *, BfmePod12 *);
template Rva002BBB96Element *_STL::vector<Rva002BBB96Element >::erase(Rva002BBB96Element *, Rva002BBB96Element *);
template Rva002DCFEEElement *_STL::vector<Rva002DCFEEElement >::erase(Rva002DCFEEElement *, Rva002DCFEEElement *);
template Rva002E2690Element *_STL::vector<Rva002E2690Element >::erase(Rva002E2690Element *, Rva002E2690Element *);
template Elem003AF9E0 *_STL::vector<Elem003AF9E0 >::erase(Elem003AF9E0 *, Elem003AF9E0 *);
template Rva0032A3A9Element *_STL::vector<Rva0032A3A9Element >::erase(Rva0032A3A9Element *, Rva0032A3A9Element *);
template Rva003371B1 *_STL::vector<Rva003371B1 >::erase(Rva003371B1 *, Rva003371B1 *);
template BfmeAssignRecord104 *_STL::vector<BfmeAssignRecord104 >::erase(BfmeAssignRecord104 *, BfmeAssignRecord104 *);
template BfmeStringRecord00111ACF *_STL::vector<BfmeStringRecord00111ACF >::erase(BfmeStringRecord00111ACF *, BfmeStringRecord00111ACF *);
template Rva004043AEElement *_STL::vector<Rva004043AEElement >::erase(Rva004043AEElement *, Rva004043AEElement *);
template Rva0040538FElement *_STL::vector<Rva0040538FElement >::erase(Rva0040538FElement *, Rva0040538FElement *);
template Rva0040DC56Element *_STL::vector<Rva0040DC56Element >::erase(Rva0040DC56Element *, Rva0040DC56Element *);
template BfmeAssignRecord44 *_STL::vector<BfmeAssignRecord44 >::erase(BfmeAssignRecord44 *, BfmeAssignRecord44 *);
template BfmeStringRecord00426A5B *_STL::vector<BfmeStringRecord00426A5B >::erase(BfmeStringRecord00426A5B *, BfmeStringRecord00426A5B *);
template BfmeNarrowRecord00427F75 *_STL::vector<BfmeNarrowRecord00427F75 >::erase(BfmeNarrowRecord00427F75 *, BfmeNarrowRecord00427F75 *);
template Rva004758F4Element *_STL::vector<Rva004758F4Element >::erase(Rva004758F4Element *, Rva004758F4Element *);
template Rva00520211Element *_STL::vector<Rva00520211Element >::erase(Rva00520211Element *, Rva00520211Element *);
template Rva00565865Element *_STL::vector<Rva00565865Element >::erase(Rva00565865Element *, Rva00565865Element *);
template Rva005658CBElement *_STL::vector<Rva005658CBElement >::erase(Rva005658CBElement *, Rva005658CBElement *);
template Rva005658FEElement *_STL::vector<Rva005658FEElement >::erase(Rva005658FEElement *, Rva005658FEElement *);
template Rva00565931Element *_STL::vector<Rva00565931Element >::erase(Rva00565931Element *, Rva00565931Element *);
template Rva00565964Element *_STL::vector<Rva00565964Element >::erase(Rva00565964Element *, Rva00565964Element *);
template Rva00565997Element *_STL::vector<Rva00565997Element >::erase(Rva00565997Element *, Rva00565997Element *);
template Rva00566A42Element *_STL::vector<Rva00566A42Element >::erase(Rva00566A42Element *, Rva00566A42Element *);
template Rva00586E86Element *_STL::vector<Rva00586E86Element >::erase(Rva00586E86Element *, Rva00586E86Element *);
template Rva005DC408Element *_STL::vector<Rva005DC408Element >::erase(Rva005DC408Element *, Rva005DC408Element *);
template Rva005EF8FAElement *_STL::vector<Rva005EF8FAElement >::erase(Rva005EF8FAElement *, Rva005EF8FAElement *);
template Rva005F8620Element *_STL::vector<Rva005F8620Element >::erase(Rva005F8620Element *, Rva005F8620Element *);
template Rva003F610FElement *_STL::vector<Rva003F610FElement >::erase(Rva003F610FElement *, Rva003F610FElement *);
template BfmeStringHeadRecord184 *_STL::vector<BfmeStringHeadRecord184 >::erase(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *);
struct Rva000B690BRecord;
template Rva000B690BRecord *_STL::__copy_ptrs<Rva000B690BRecord *, Rva000B690BRecord *>(Rva000B690BRecord *, Rva000B690BRecord *, Rva000B690BRecord *, const _STL::__false_type &);


// Target slot 6 in vtable VA 0x00BC68F0 is 0x0007A7DD; slots 2 and 3 are
// the independently named W3DHordeModelDraw name getter and xfer method. The
// name stays address-derived because the BFME1 donor owner is different.
// The BFME1 donor at revision 968ca36c3265b295297e6aed45a6bd89ffe59c40
// places the same 95-byte helper-lifetime body as
// Gen_00755E70::bfmeBeginYS under BFME2 /O1 settings. This is semantic donor
// evidence, not target evidence for the class name or helper member layout.
// Retail data references at this body name a 40-byte static helper at VA
// 0x00DE1FC8 and a current-helper pointer at VA 0x00DE1FB8. Keep its storage
// opaque; the existing destructor pin at 0x0007A4E6 handles its lifetime.
class Gen_00755E70;
class Gen01304B64;

class Rva007A4E6
{
public:
	~Rva007A4E6();
};

class BfmeHelperYS
{
public:
	BfmeHelperYS();
	~BfmeHelperYS()
	{
		reinterpret_cast<Rva007A4E6 *>(this)->~Rva007A4E6();
	}
	void bfmeAttachYS(Gen_00755E70 *owner);

private:
	unsigned char m_targetObservedStorage[40];
};

class Gen_00755E70
{
public:
	void bfmeFinishYS();
};

class W3DHordeModelDraw
{
public:
	void rva0007A7DD();
};

extern Gen01304B64 *g_Va01304B64;

// ?rva0007A7DD@W3DHordeModelDraw@@QAEXXZ @ 0x0007A7DD (95B).
// The function is virtual in the target vtable; this TU declares only the
// thiscall body so it does not emit a competing class vftable.
void W3DHordeModelDraw::rva0007A7DD()
{
	static BfmeHelperYS s_bfmeHelperYS;
	BfmeHelperYS *helper = &s_bfmeHelperYS;
	g_Va01304B64 = reinterpret_cast<Gen01304B64 *>(helper);
	helper->bfmeAttachYS(reinterpret_cast<Gen_00755E70 *>(this));
	reinterpret_cast<Gen_00755E70 *>(this)->bfmeFinishYS();
}
