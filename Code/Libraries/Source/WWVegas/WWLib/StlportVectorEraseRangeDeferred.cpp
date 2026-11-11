// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// Blocked instantiations rehomed unchanged from StlportVectorEraseRangeFamily.cpp.
// Their helper/provider prerequisites remain unresolved; no new identity is claimed.
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
//   0x00414760  0x00414403   0x004144F0   ScoredKillTracker
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

// Native copy dispatcher passes all five cdecl arguments (2B4410 -> 2B442D).
// The range's opaque four-byte elements use the existing holder-copy provider.
// This does not establish an original element or class name.
struct Rva0040DC56Element;
class Rva002B2F97;
// Native 4286AF destroys its opaque 24-byte records through 2385E6.
// The generic narrow-record copy instead binds destructor22CCEF and is not
// a relocation twin of this range. Keep this call on its actual provider.
struct BfmeNarrowRecord00427F75;
void __cdecl destroyVersionRecords(void *, void *);
namespace _STL {
// ?_STL::_Destroy absent-from-retail
static __forceinline void _Destroy(BfmeNarrowRecord00427F75 *first,
    BfmeNarrowRecord00427F75 *last)
{
    destroyVersionRecords(first, last);
}
}

namespace _STL { struct random_access_iterator_tag; }
Rva002B2F97 * __cdecl Rva002B442DCopy(Rva002B2F97 *, Rva002B2F97 *,
    Rva002B2F97 *, const _STL::random_access_iterator_tag &, int *);
namespace _STL {
// ?_STL::__copy absent-from-retail
static __forceinline Rva0040DC56Element *__copy(Rva0040DC56Element *first,
    Rva0040DC56Element *last, Rva0040DC56Element *dest,
    const random_access_iterator_tag &category, int *distance)
{
    return reinterpret_cast<Rva0040DC56Element *>(Rva002B442DCopy(
        reinterpret_cast<Rva002B2F97 *>(first),
        reinterpret_cast<Rva002B2F97 *>(last),
        reinterpret_cast<Rva002B2F97 *>(dest), category, distance));
}
}

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
	void push_back(const _Tp &);

	iterator erase(iterator __first, iterator __last)
	{
		pointer __i = __copy_ptrs(__last, this->_M_finish, __first, __false_type());
		_Destroy(__i, this->_M_finish);
		this->_M_finish = __i;
		return __first;
	}

	void clear()
	{
		erase(_M_start, _M_finish);
	}

protected:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};

}

namespace _STL
{

template <class _Key>
struct less
{
};

template <class _T1, class _T2>
struct pair
{
};

template <class _Key, class _Tp, class _Compare = less<_Key>,
	class _Alloc = allocator<pair<const _Key, _Tp> > >
class map
{
public:
	_Tp &operator[](const _Key &);
};

}

struct Rva000B690BRecord;
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
class ScoredKillTracker;
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

// Retail calls each of these helpers out of line at an address the ledger
// already rows under another spelling; each forwarder reaches that row with
// the call shape of the helper it replaces (generated from the retail REL32s).
class BfmeStringTailRecord156;
class BuildListInfo;
class DynamicAudioEventRTS;
class Object;
template <class T> class Rva001EB984PoolAllocator;
namespace _STL { template <class _Tp, class _Alloc> class list; }
// Native 4758F4 -> 474125 -> 4703B1 reaches the pooled Object-list copy,
// not the withdrawn GameWindow view. Keep the existing opaque element ABI.
typedef _STL::list<Object *,Rva001EB984PoolAllocator<Object *> > Rva004758F4PoolList;
class Rva0004CCFF;
class Rva000A8CAE;
class Rva000B9AAA;
class Rva001DE727;
class Rva002111C8;
class Rva00214ADC;
class Rva002A73B8;
class Rva002B2F49;
class Rva002E0D93;
class Rva002E9E70;
class Rva0032A3A9Element;
class Rva003371B1;
class Rva003AC980;
class Rva003AD070;
class Rva003AD0A0;
class Rva003B3080;
class Rva00403927;
class Rva00585B16;
class Rva005EEFD2;
class Rva00752630;
class RvaSmartPtr12;
struct BfmeNarrowRecord00079C23;
struct BfmeNarrowRecord00427F75;
struct BfmePod12;
struct BfmeVectorRecord000C0BEC;
struct Elem003AF9E0;
struct Rva00079554Record;
struct Rva00079EA1Element;
struct Rva000B978ARecord;
struct Rva000BEDF0Record;
struct Rva000C1CAEElement;
struct Rva0014F718;
struct Rva00150659Element;
struct Rva001DEF38Element;
struct Rva001EB63C;
struct Rva002115C5;
struct Rva00213949Element;
struct Rva002B91BBElement;
struct Rva002BBB96Element;
struct Rva002DBF66Elem;
struct Rva002DCFEEElement;
struct Rva002E2690Element;
struct Rva003F610FElement;
struct Rva004043AEElement;
struct Rva0040538FElement;
struct Rva0040DC56Element;
struct Rva0042830DElement;
struct Rva004758F4Element;
struct Rva004E1AD5Item;
struct Rva004FAFF2;
struct Rva0051FC54Element;
struct Rva00520211Element;
struct Rva0052BF33Elem;
struct Rva0052BF67Elem;
struct Rva0052BF9BElem;
struct Rva0052BFB5Elem;
struct Rva00565865Element;
struct Rva005658CBElement;
struct Rva005658FEElement;
struct Rva00565931Element;
struct Rva00565964Element;
struct Rva00565997Element;
struct Rva00566A42Element;
struct Rva00586D2AElement;
struct Rva00586E86Element;
struct Rva005DC408Element;
struct Rva005EF8FAElement;
struct Rva005F0647;
struct Rva005F8536;
struct Rva005F8620Element;
void __cdecl Rva002A752FDestroy(Rva002A73B8 *,Rva002A73B8 *);
void __cdecl Rva00405337Clear(void *,void *);
void __cdecl Rva000BDD08Destroy(Rva000B9AAA *,Rva000B9AAA *);
void __cdecl Rva005A6EDADestroyRange(Rva0052BF33Elem *,Rva0052BF33Elem *);
void __cdecl Rva00212AD6Get(Rva002115C5 *,Rva002115C5 *);
void __cdecl Rva0022C8E3DestroyRange(Rva0052BF9BElem *,Rva0052BF9BElem *);
namespace _STL { template <> void _Destroy<class Rva00214ADC *>(Rva00214ADC *,Rva00214ADC *); }
void __cdecl Rva0052C3BFDestroyRange(Rva0052BF67Elem *,Rva0052BF67Elem *);
namespace _STL { template <> void _Destroy<struct Elem003AF9E0 *>(Elem003AF9E0 *,Elem003AF9E0 *); }
void __cdecl Rva0052C37ADestroyRange(Rva0052BFB5Elem *,Rva0052BFB5Elem *);
void __cdecl Rva004E1FCCGet(Rva004E1AD5Item *,Rva004E1AD5Item *);
void __cdecl Rva00586B92Destroy(Rva00585B16 *,Rva00585B16 *);
void __cdecl Rva005EF5EFClear(Rva005F0647 *,Rva005F0647 *);
namespace _STL { template <> Rva0042830DElement * __copy<struct Rva0042830DElement *,struct Rva0042830DElement *,int>(Rva0042830DElement *,Rva0042830DElement *,Rva0042830DElement *,_STL::random_access_iterator_tag const &,int *); }
namespace _STL { template <> BfmeNarrowRecord00079C23 * __copy<struct BfmeNarrowRecord00079C23 const *,struct BfmeNarrowRecord00079C23 *,int>(BfmeNarrowRecord00079C23 const *,BfmeNarrowRecord00079C23 const *,BfmeNarrowRecord00079C23 *,_STL::random_access_iterator_tag const &,int *); }
Rva00752630 * __cdecl Rva000791EDCopy(Rva00752630 *,Rva00752630 *,Rva00752630 *);
BfmeVectorRecord000C0BEC * __cdecl Rva000C0CE1Copy(BfmeVectorRecord000C0BEC *,BfmeVectorRecord000C0BEC *,BfmeVectorRecord000C0BEC *);
namespace _STL { template <> Rva000B978ARecord * __copy<struct Rva000B978ARecord *,struct Rva000B978ARecord *,int>(Rva000B978ARecord *,Rva000B978ARecord *,Rva000B978ARecord *,_STL::random_access_iterator_tag const &,int *); }
Rva0014F718 * __cdecl Rva0014FA62Copy(Rva0014F718 *,Rva0014F718 *,Rva0014F718 *,void *,int);
Rva001DE727 * __cdecl Rva001DE906Copy(Rva001DE727 *,Rva001DE727 *,Rva001DE727 *);
Rva002111C8 * __cdecl Rva00211EAACopy(Rva002111C8 *,Rva002111C8 *,Rva002111C8 *);
namespace _STL { template <> Rva002B91BBElement * __copy<struct Rva002B91BBElement *,struct Rva002B91BBElement *,int>(Rva002B91BBElement *,Rva002B91BBElement *,Rva002B91BBElement *,_STL::random_access_iterator_tag const &,int *); }
Rva002DBF66Elem * __cdecl Rva002DBF66Copy(Rva002DBF66Elem *,Rva002DBF66Elem *,Rva002DBF66Elem *);
Rva002E0D93 * __cdecl Rva002E17A0Copy(Rva002E0D93 *,Rva002E0D93 *,Rva002E0D93 *);
char * __cdecl Rva003F58F8Copy(char *,char *,char *);
namespace _STL { template <> Rva00403927 * __copy<class Rva00403927 *,class Rva00403927 *,int>(Rva00403927 *,Rva00403927 *,Rva00403927 *,_STL::random_access_iterator_tag const &,int *); }
namespace _STL { template <> Rva004758F4PoolList * __copy<Rva004758F4PoolList *,Rva004758F4PoolList *,int>(Rva004758F4PoolList *,Rva004758F4PoolList *,Rva004758F4PoolList *,_STL::random_access_iterator_tag const &,int *); }
namespace _STL { template <> Rva0051FC54Element * __copy<struct Rva0051FC54Element *,struct Rva0051FC54Element *,int>(Rva0051FC54Element *,Rva0051FC54Element *,Rva0051FC54Element *,_STL::random_access_iterator_tag const &,int *); }
DynamicAudioEventRTS * __cdecl Rva00564CA5Copy(DynamicAudioEventRTS *,DynamicAudioEventRTS *,DynamicAudioEventRTS *);
Rva003B3080 * __cdecl Rva00564D06Copy(Rva003B3080 *,Rva003B3080 *,Rva003B3080 *);
Rva003AC980 * __cdecl Rva00564D38Copy(Rva003AC980 *,Rva003AC980 *,Rva003AC980 *);
Rva003AD0A0 * __cdecl Rva00564D67Copy(Rva003AD0A0 *,Rva003AD0A0 *,Rva003AD0A0 *);
void * __cdecl Rva005657B2Copy(void *,void *,void *);
Rva003AD070 * __cdecl Rva00564D99Copy(Rva003AD070 *,Rva003AD070 *,Rva003AD070 *);
Rva004FAFF2 * __cdecl Rva00566663Copy(Rva004FAFF2 *,Rva004FAFF2 *,Rva004FAFF2 *);
namespace _STL { template <> Rva00586D2AElement * __copy<struct Rva00586D2AElement *,struct Rva00586D2AElement *,int>(Rva00586D2AElement *,Rva00586D2AElement *,Rva00586D2AElement *,_STL::random_access_iterator_tag const &,int *); }
Rva005EEFD2 * __cdecl Rva005EF4C0Copy(Rva005EEFD2 *,Rva005EEFD2 *,Rva005EEFD2 *);
Rva005F8536 * __cdecl Rva005F8573Copy(Rva005F8536 *,Rva005F8536 *,Rva005F8536 *);
Rva000A8CAE * __cdecl Rva001D9BA4Copy(Rva000A8CAE *,Rva000A8CAE *,Rva000A8CAE *);
namespace _STL { template <> BuildListInfo * __copy<class BuildListInfo *,class BuildListInfo *,int>(BuildListInfo *,BuildListInfo *,BuildListInfo *,_STL::random_access_iterator_tag const &,int *); }
Rva002E9E70 * __cdecl uninitializedCopy(Rva002E9E70 *,Rva002E9E70 *,Rva002E9E70 *);
namespace _STL { template <> void __destroy_aux<struct Rva001EB63C *>(Rva001EB63C *,Rva001EB63C *,_STL::__false_type const &); }
void __cdecl Rva002B44C1Destroy(Rva002B2F49 *,Rva002B2F49 *);
void __cdecl Rva0004CD49Destroy(Rva0004CCFF *,Rva0004CCFF *);
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct BfmePod12 *>(BfmePod12 * a0, BfmePod12 * a1)
{ ((void (__cdecl *)(BfmePod12 *,BfmePod12 *))(void (__cdecl *)(Rva002A73B8 *,Rva002A73B8 *))&Rva002A752FDestroy)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00079EA1Element *>(Rva00079EA1Element * a0, Rva00079EA1Element * a1)
{ ((void (__cdecl *)(Rva00079EA1Element *,Rva00079EA1Element *))(void (__cdecl *)(void *,void *))&Rva00405337Clear)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva000C1CAEElement *>(Rva000C1CAEElement * a0, Rva000C1CAEElement * a1)
{ ((void (__cdecl *)(Rva000C1CAEElement *,Rva000C1CAEElement *))(void (__cdecl *)(Rva000B9AAA *,Rva000B9AAA *))&Rva000BDD08Destroy)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00150659Element *>(Rva00150659Element * a0, Rva00150659Element * a1)
{ ((void (__cdecl *)(Rva00150659Element *,Rva00150659Element *))(void (__cdecl *)(Rva0052BF33Elem *,Rva0052BF33Elem *))&Rva005A6EDADestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00213949Element *>(Rva00213949Element * a0, Rva00213949Element * a1)
{ ((void (__cdecl *)(Rva00213949Element *,Rva00213949Element *))(void (__cdecl *)(Rva002115C5 *,Rva002115C5 *))&Rva00212AD6Get)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva002DCFEEElement *>(Rva002DCFEEElement * a0, Rva002DCFEEElement * a1)
{ ((void (__cdecl *)(Rva002DCFEEElement *,Rva002DCFEEElement *))(void (__cdecl *)(Rva0052BF9BElem *,Rva0052BF9BElem *))&Rva0022C8E3DestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva004043AEElement *>(Rva004043AEElement * a0, Rva004043AEElement * a1)
{ ((void (__cdecl *)(Rva004043AEElement *,Rva004043AEElement *))(void (__cdecl *)(Rva00214ADC *,Rva00214ADC *))&_STL::_Destroy<Rva00214ADC *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva0040538FElement *>(Rva0040538FElement * a0, Rva0040538FElement * a1)
{ ((void (__cdecl *)(Rva0040538FElement *,Rva0040538FElement *))(void (__cdecl *)(void *,void *))&Rva00405337Clear)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00565865Element *>(Rva00565865Element * a0, Rva00565865Element * a1)
{ ((void (__cdecl *)(Rva00565865Element *,Rva00565865Element *))(void (__cdecl *)(Rva0052BF33Elem *,Rva0052BF33Elem *))&Rva005A6EDADestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva005658CBElement *>(Rva005658CBElement * a0, Rva005658CBElement * a1)
{ ((void (__cdecl *)(Rva005658CBElement *,Rva005658CBElement *))(void (__cdecl *)(Rva0052BF9BElem *,Rva0052BF9BElem *))&Rva0022C8E3DestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva005658FEElement *>(Rva005658FEElement * a0, Rva005658FEElement * a1)
{ ((void (__cdecl *)(Rva005658FEElement *,Rva005658FEElement *))(void (__cdecl *)(Rva0052BF67Elem *,Rva0052BF67Elem *))&Rva0052C3BFDestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00565931Element *>(Rva00565931Element * a0, Rva00565931Element * a1)
{ ((void (__cdecl *)(Rva00565931Element *,Rva00565931Element *))(void (__cdecl *)(Rva0052BF9BElem *,Rva0052BF9BElem *))&Rva0022C8E3DestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00565964Element *>(Rva00565964Element * a0, Rva00565964Element * a1)
{ ((void (__cdecl *)(Rva00565964Element *,Rva00565964Element *))(void (__cdecl *)(Elem003AF9E0 *,Elem003AF9E0 *))&_STL::_Destroy<Elem003AF9E0 *>)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00565997Element *>(Rva00565997Element * a0, Rva00565997Element * a1)
{ ((void (__cdecl *)(Rva00565997Element *,Rva00565997Element *))(void (__cdecl *)(Rva0052BFB5Elem *,Rva0052BFB5Elem *))&Rva0052C37ADestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00566A42Element *>(Rva00566A42Element * a0, Rva00566A42Element * a1)
{ ((void (__cdecl *)(Rva00566A42Element *,Rva00566A42Element *))(void (__cdecl *)(Rva004E1AD5Item *,Rva004E1AD5Item *))&Rva004E1FCCGet)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva00586E86Element *>(Rva00586E86Element * a0, Rva00586E86Element * a1)
{ ((void (__cdecl *)(Rva00586E86Element *,Rva00586E86Element *))(void (__cdecl *)(Rva00585B16 *,Rva00585B16 *))&Rva00586B92Destroy)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva005DC408Element *>(Rva005DC408Element * a0, Rva005DC408Element * a1)
{ ((void (__cdecl *)(Rva005DC408Element *,Rva005DC408Element *))(void (__cdecl *)(Rva0052BF33Elem *,Rva0052BF33Elem *))&Rva005A6EDADestroyRange)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<struct Rva005EF8FAElement *>(Rva005EF8FAElement * a0, Rva005EF8FAElement * a1)
{ ((void (__cdecl *)(Rva005EF8FAElement *,Rva005EF8FAElement *))(void (__cdecl *)(Rva005F0647 *,Rva005F0647 *))&Rva005EF5EFClear)(a0, a1); } }
namespace _STL { template <> __declspec(dllimport) __forceinline BfmeNarrowRecord00427F75 * __copy<struct BfmeNarrowRecord00427F75 *,struct BfmeNarrowRecord00427F75 *,int>(BfmeNarrowRecord00427F75 * a0, BfmeNarrowRecord00427F75 * a1, BfmeNarrowRecord00427F75 * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((BfmeNarrowRecord00427F75 * (__cdecl *)(BfmeNarrowRecord00427F75 *,BfmeNarrowRecord00427F75 *,BfmeNarrowRecord00427F75 *,_STL::random_access_iterator_tag const &,int *))(Rva0042830DElement * (__cdecl *)(Rva0042830DElement *,Rva0042830DElement *,Rva0042830DElement *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<Rva0042830DElement *,Rva0042830DElement *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00079554Record * __copy<struct Rva00079554Record *,struct Rva00079554Record *,int>(Rva00079554Record * a0, Rva00079554Record * a1, Rva00079554Record * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00079554Record * (__cdecl *)(Rva00079554Record *,Rva00079554Record *,Rva00079554Record *,_STL::random_access_iterator_tag const &,int *))(BfmeNarrowRecord00079C23 * (__cdecl *)(BfmeNarrowRecord00079C23 const *,BfmeNarrowRecord00079C23 const *,BfmeNarrowRecord00079C23 *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<BfmeNarrowRecord00079C23 const *,BfmeNarrowRecord00079C23 *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00079EA1Element * __copy<struct Rva00079EA1Element *,struct Rva00079EA1Element *,int>(Rva00079EA1Element * a0, Rva00079EA1Element * a1, Rva00079EA1Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00079EA1Element * (__cdecl *)(Rva00079EA1Element *,Rva00079EA1Element *,Rva00079EA1Element *,_STL::random_access_iterator_tag const &,int *))(Rva00752630 * (__cdecl *)(Rva00752630 *,Rva00752630 *,Rva00752630 *))&Rva000791EDCopy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva000BEDF0Record * __copy<struct Rva000BEDF0Record *,struct Rva000BEDF0Record *,int>(Rva000BEDF0Record * a0, Rva000BEDF0Record * a1, Rva000BEDF0Record * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva000BEDF0Record * (__cdecl *)(Rva000BEDF0Record *,Rva000BEDF0Record *,Rva000BEDF0Record *,_STL::random_access_iterator_tag const &,int *))(BfmeVectorRecord000C0BEC * (__cdecl *)(BfmeVectorRecord000C0BEC *,BfmeVectorRecord000C0BEC *,BfmeVectorRecord000C0BEC *))&Rva000C0CE1Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva000C1CAEElement * __copy<struct Rva000C1CAEElement *,struct Rva000C1CAEElement *,int>(Rva000C1CAEElement * a0, Rva000C1CAEElement * a1, Rva000C1CAEElement * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva000C1CAEElement * (__cdecl *)(Rva000C1CAEElement *,Rva000C1CAEElement *,Rva000C1CAEElement *,_STL::random_access_iterator_tag const &,int *))(Rva000B978ARecord * (__cdecl *)(Rva000B978ARecord *,Rva000B978ARecord *,Rva000B978ARecord *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<Rva000B978ARecord *,Rva000B978ARecord *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00150659Element * __copy<struct Rva00150659Element *,struct Rva00150659Element *,int>(Rva00150659Element * a0, Rva00150659Element * a1, Rva00150659Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00150659Element * (__cdecl *)(Rva00150659Element *,Rva00150659Element *,Rva00150659Element *,_STL::random_access_iterator_tag const &,int *))(Rva0014F718 * (__cdecl *)(Rva0014F718 *,Rva0014F718 *,Rva0014F718 *,void *,int))&Rva0014FA62Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva001DEF38Element * __copy<struct Rva001DEF38Element *,struct Rva001DEF38Element *,int>(Rva001DEF38Element * a0, Rva001DEF38Element * a1, Rva001DEF38Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva001DEF38Element * (__cdecl *)(Rva001DEF38Element *,Rva001DEF38Element *,Rva001DEF38Element *,_STL::random_access_iterator_tag const &,int *))(Rva001DE727 * (__cdecl *)(Rva001DE727 *,Rva001DE727 *,Rva001DE727 *))&Rva001DE906Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00213949Element * __copy<struct Rva00213949Element *,struct Rva00213949Element *,int>(Rva00213949Element * a0, Rva00213949Element * a1, Rva00213949Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00213949Element * (__cdecl *)(Rva00213949Element *,Rva00213949Element *,Rva00213949Element *,_STL::random_access_iterator_tag const &,int *))(Rva002111C8 * (__cdecl *)(Rva002111C8 *,Rva002111C8 *,Rva002111C8 *))&Rva00211EAACopy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva002BBB96Element * __copy<struct Rva002BBB96Element *,struct Rva002BBB96Element *,int>(Rva002BBB96Element * a0, Rva002BBB96Element * a1, Rva002BBB96Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva002BBB96Element * (__cdecl *)(Rva002BBB96Element *,Rva002BBB96Element *,Rva002BBB96Element *,_STL::random_access_iterator_tag const &,int *))(Rva002B91BBElement * (__cdecl *)(Rva002B91BBElement *,Rva002B91BBElement *,Rva002B91BBElement *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<Rva002B91BBElement *,Rva002B91BBElement *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva002DCFEEElement * __copy<struct Rva002DCFEEElement *,struct Rva002DCFEEElement *,int>(Rva002DCFEEElement * a0, Rva002DCFEEElement * a1, Rva002DCFEEElement * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva002DCFEEElement * (__cdecl *)(Rva002DCFEEElement *,Rva002DCFEEElement *,Rva002DCFEEElement *,_STL::random_access_iterator_tag const &,int *))(Rva002DBF66Elem * (__cdecl *)(Rva002DBF66Elem *,Rva002DBF66Elem *,Rva002DBF66Elem *))&Rva002DBF66Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva002E2690Element * __copy<struct Rva002E2690Element *,struct Rva002E2690Element *,int>(Rva002E2690Element * a0, Rva002E2690Element * a1, Rva002E2690Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva002E2690Element * (__cdecl *)(Rva002E2690Element *,Rva002E2690Element *,Rva002E2690Element *,_STL::random_access_iterator_tag const &,int *))(Rva002E0D93 * (__cdecl *)(Rva002E0D93 *,Rva002E0D93 *,Rva002E0D93 *))&Rva002E17A0Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva003F610FElement * __copy<struct Rva003F610FElement *,struct Rva003F610FElement *,int>(Rva003F610FElement * a0, Rva003F610FElement * a1, Rva003F610FElement * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva003F610FElement * (__cdecl *)(Rva003F610FElement *,Rva003F610FElement *,Rva003F610FElement *,_STL::random_access_iterator_tag const &,int *))(char * (__cdecl *)(char *,char *,char *))&Rva003F58F8Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva004043AEElement * __copy<struct Rva004043AEElement *,struct Rva004043AEElement *,int>(Rva004043AEElement * a0, Rva004043AEElement * a1, Rva004043AEElement * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva004043AEElement * (__cdecl *)(Rva004043AEElement *,Rva004043AEElement *,Rva004043AEElement *,_STL::random_access_iterator_tag const &,int *))(Rva00403927 * (__cdecl *)(Rva00403927 *,Rva00403927 *,Rva00403927 *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<Rva00403927 *,Rva00403927 *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva004758F4Element * __copy<struct Rva004758F4Element *,struct Rva004758F4Element *,int>(Rva004758F4Element * a0, Rva004758F4Element * a1, Rva004758F4Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva004758F4Element * (__cdecl *)(Rva004758F4Element *,Rva004758F4Element *,Rva004758F4Element *,_STL::random_access_iterator_tag const &,int *))(Rva004758F4PoolList * (__cdecl *)(Rva004758F4PoolList *,Rva004758F4PoolList *,Rva004758F4PoolList *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<Rva004758F4PoolList *,Rva004758F4PoolList *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00520211Element * __copy<struct Rva00520211Element *,struct Rva00520211Element *,int>(Rva00520211Element * a0, Rva00520211Element * a1, Rva00520211Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00520211Element * (__cdecl *)(Rva00520211Element *,Rva00520211Element *,Rva00520211Element *,_STL::random_access_iterator_tag const &,int *))(Rva0051FC54Element * (__cdecl *)(Rva0051FC54Element *,Rva0051FC54Element *,Rva0051FC54Element *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<Rva0051FC54Element *,Rva0051FC54Element *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00565865Element * __copy<struct Rva00565865Element *,struct Rva00565865Element *,int>(Rva00565865Element * a0, Rva00565865Element * a1, Rva00565865Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00565865Element * (__cdecl *)(Rva00565865Element *,Rva00565865Element *,Rva00565865Element *,_STL::random_access_iterator_tag const &,int *))(DynamicAudioEventRTS * (__cdecl *)(DynamicAudioEventRTS *,DynamicAudioEventRTS *,DynamicAudioEventRTS *))&Rva00564CA5Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva005658CBElement * __copy<struct Rva005658CBElement *,struct Rva005658CBElement *,int>(Rva005658CBElement * a0, Rva005658CBElement * a1, Rva005658CBElement * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva005658CBElement * (__cdecl *)(Rva005658CBElement *,Rva005658CBElement *,Rva005658CBElement *,_STL::random_access_iterator_tag const &,int *))(Rva003B3080 * (__cdecl *)(Rva003B3080 *,Rva003B3080 *,Rva003B3080 *))&Rva00564D06Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva005658FEElement * __copy<struct Rva005658FEElement *,struct Rva005658FEElement *,int>(Rva005658FEElement * a0, Rva005658FEElement * a1, Rva005658FEElement * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva005658FEElement * (__cdecl *)(Rva005658FEElement *,Rva005658FEElement *,Rva005658FEElement *,_STL::random_access_iterator_tag const &,int *))(Rva003AC980 * (__cdecl *)(Rva003AC980 *,Rva003AC980 *,Rva003AC980 *))&Rva00564D38Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00565931Element * __copy<struct Rva00565931Element *,struct Rva00565931Element *,int>(Rva00565931Element * a0, Rva00565931Element * a1, Rva00565931Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00565931Element * (__cdecl *)(Rva00565931Element *,Rva00565931Element *,Rva00565931Element *,_STL::random_access_iterator_tag const &,int *))(Rva003AD0A0 * (__cdecl *)(Rva003AD0A0 *,Rva003AD0A0 *,Rva003AD0A0 *))&Rva00564D67Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00565964Element * __copy<struct Rva00565964Element *,struct Rva00565964Element *,int>(Rva00565964Element * a0, Rva00565964Element * a1, Rva00565964Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00565964Element * (__cdecl *)(Rva00565964Element *,Rva00565964Element *,Rva00565964Element *,_STL::random_access_iterator_tag const &,int *))(void * (__cdecl *)(void *,void *,void *))&Rva005657B2Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00565997Element * __copy<struct Rva00565997Element *,struct Rva00565997Element *,int>(Rva00565997Element * a0, Rva00565997Element * a1, Rva00565997Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00565997Element * (__cdecl *)(Rva00565997Element *,Rva00565997Element *,Rva00565997Element *,_STL::random_access_iterator_tag const &,int *))(Rva003AD070 * (__cdecl *)(Rva003AD070 *,Rva003AD070 *,Rva003AD070 *))&Rva00564D99Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00566A42Element * __copy<struct Rva00566A42Element *,struct Rva00566A42Element *,int>(Rva00566A42Element * a0, Rva00566A42Element * a1, Rva00566A42Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00566A42Element * (__cdecl *)(Rva00566A42Element *,Rva00566A42Element *,Rva00566A42Element *,_STL::random_access_iterator_tag const &,int *))(Rva004FAFF2 * (__cdecl *)(Rva004FAFF2 *,Rva004FAFF2 *,Rva004FAFF2 *))&Rva00566663Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva00586E86Element * __copy<struct Rva00586E86Element *,struct Rva00586E86Element *,int>(Rva00586E86Element * a0, Rva00586E86Element * a1, Rva00586E86Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva00586E86Element * (__cdecl *)(Rva00586E86Element *,Rva00586E86Element *,Rva00586E86Element *,_STL::random_access_iterator_tag const &,int *))(Rva00586D2AElement * (__cdecl *)(Rva00586D2AElement *,Rva00586D2AElement *,Rva00586D2AElement *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<Rva00586D2AElement *,Rva00586D2AElement *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva005EF8FAElement * __copy<struct Rva005EF8FAElement *,struct Rva005EF8FAElement *,int>(Rva005EF8FAElement * a0, Rva005EF8FAElement * a1, Rva005EF8FAElement * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva005EF8FAElement * (__cdecl *)(Rva005EF8FAElement *,Rva005EF8FAElement *,Rva005EF8FAElement *,_STL::random_access_iterator_tag const &,int *))(Rva005EEFD2 * (__cdecl *)(Rva005EEFD2 *,Rva005EEFD2 *,Rva005EEFD2 *))&Rva005EF4C0Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva005F8620Element * __copy<struct Rva005F8620Element *,struct Rva005F8620Element *,int>(Rva005F8620Element * a0, Rva005F8620Element * a1, Rva005F8620Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva005F8620Element * (__cdecl *)(Rva005F8620Element *,Rva005F8620Element *,Rva005F8620Element *,_STL::random_access_iterator_tag const &,int *))(Rva005F8536 * (__cdecl *)(Rva005F8536 *,Rva005F8536 *,Rva005F8536 *))&Rva005F8573Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline BfmeStringTailRecord156 * __copy<class BfmeStringTailRecord156 *,class BfmeStringTailRecord156 *,int>(BfmeStringTailRecord156 * a0, BfmeStringTailRecord156 * a1, BfmeStringTailRecord156 * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((BfmeStringTailRecord156 * (__cdecl *)(BfmeStringTailRecord156 *,BfmeStringTailRecord156 *,BfmeStringTailRecord156 *,_STL::random_access_iterator_tag const &,int *))(Rva000A8CAE * (__cdecl *)(Rva000A8CAE *,Rva000A8CAE *,Rva000A8CAE *))&Rva001D9BA4Copy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva0032A3A9Element * __copy<class Rva0032A3A9Element *,class Rva0032A3A9Element *,int>(Rva0032A3A9Element * a0, Rva0032A3A9Element * a1, Rva0032A3A9Element * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva0032A3A9Element * (__cdecl *)(Rva0032A3A9Element *,Rva0032A3A9Element *,Rva0032A3A9Element *,_STL::random_access_iterator_tag const &,int *))(BuildListInfo * (__cdecl *)(BuildListInfo *,BuildListInfo *,BuildListInfo *,_STL::random_access_iterator_tag const &,int *))&_STL::__copy<BuildListInfo *,BuildListInfo *,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline Rva003371B1 * __copy<class Rva003371B1 *,class Rva003371B1 *,int>(Rva003371B1 * a0, Rva003371B1 * a1, Rva003371B1 * a2, _STL::random_access_iterator_tag const & a3, int * a4)
{ return ((Rva003371B1 * (__cdecl *)(Rva003371B1 *,Rva003371B1 *,Rva003371B1 *,_STL::random_access_iterator_tag const &,int *))(Rva002E9E70 * (__cdecl *)(Rva002E9E70 *,Rva002E9E70 *,Rva002E9E70 *))&uninitializedCopy)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void __destroy_aux<struct Rva002E2690Element *>(Rva002E2690Element * a0, Rva002E2690Element * a1, _STL::__false_type const & a2)
{ ((void (__cdecl *)(Rva002E2690Element *,Rva002E2690Element *,_STL::__false_type const &))(void (__cdecl *)(Rva001EB63C *,Rva001EB63C *,_STL::__false_type const &))&_STL::__destroy_aux<Rva001EB63C *>)(a0, a1, a2); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void __destroy_aux<struct Rva0040DC56Element *>(Rva0040DC56Element * a0, Rva0040DC56Element * a1, _STL::__false_type const & a2)
{ ((void (__cdecl *)(Rva0040DC56Element *,Rva0040DC56Element *,_STL::__false_type const &))(void (__cdecl *)(Rva002B2F49 *,Rva002B2F49 *))&Rva002B44C1Destroy)(a0, a1, a2); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void __destroy_aux<class RvaSmartPtr12 *>(RvaSmartPtr12 * a0, RvaSmartPtr12 * a1, _STL::__false_type const & a2)
{ ((void (__cdecl *)(RvaSmartPtr12 *,RvaSmartPtr12 *,_STL::__false_type const &))(void (__cdecl *)(Rva0004CCFF *,Rva0004CCFF *))&Rva0004CD49Destroy)(a0, a1, a2); } }

// 0x003B908A's range destroy is retail 0x003B8E13, rowed as Rva003B8E13DestroyRange;
// binding it here keeps this unit off the template copy another unit keeps.
struct Rva003B8B61Elem;
void __cdecl Rva003B8E13DestroyRange(Rva003B8B61Elem *, Rva003B8B61Elem *);
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<BfmeAssignRecord104 *>(BfmeAssignRecord104 *a0, BfmeAssignRecord104 *a1)
{ ((void (__cdecl *)(BfmeAssignRecord104 *,BfmeAssignRecord104 *))(void (__cdecl *)(Rva003B8B61Elem *,Rva003B8B61Elem *))&Rva003B8E13DestroyRange)(a0, a1); } }

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
template Rva00079EA1Element *_STL::vector<Rva00079EA1Element >::erase(Rva00079EA1Element *, Rva00079EA1Element *);
template Rva000C1CAEElement *_STL::vector<Rva000C1CAEElement >::erase(Rva000C1CAEElement *, Rva000C1CAEElement *);
template Rva00079554Record *_STL::vector<Rva00079554Record >::erase(Rva00079554Record *, Rva00079554Record *);
template Rva000BEDF0Record *_STL::vector<Rva000BEDF0Record >::erase(Rva000BEDF0Record *, Rva000BEDF0Record *);
template Rva00150659Element *_STL::vector<Rva00150659Element >::erase(Rva00150659Element *, Rva00150659Element *);
template Rva00151DAB *_STL::vector<Rva00151DAB >::erase(Rva00151DAB *, Rva00151DAB *);
template Rva00153729 *_STL::vector<Rva00153729 >::erase(Rva00153729 *, Rva00153729 *);
template BfmeStringTailRecord156 *_STL::vector<BfmeStringTailRecord156 >::erase(BfmeStringTailRecord156 *, BfmeStringTailRecord156 *);
template Rva001DEF38Element *_STL::vector<Rva001DEF38Element >::erase(Rva001DEF38Element *, Rva001DEF38Element *);
template Rva00213949Element *_STL::vector<Rva00213949Element >::erase(Rva00213949Element *, Rva00213949Element *);
template BfmePod12 *_STL::vector<BfmePod12 >::erase(BfmePod12 *, BfmePod12 *);
template Rva002BBB96Element *_STL::vector<Rva002BBB96Element >::erase(Rva002BBB96Element *, Rva002BBB96Element *);
template Rva002DCFEEElement *_STL::vector<Rva002DCFEEElement >::erase(Rva002DCFEEElement *, Rva002DCFEEElement *);
template Rva002E2690Element *_STL::vector<Rva002E2690Element >::erase(Rva002E2690Element *, Rva002E2690Element *);
template Rva0032A3A9Element *_STL::vector<Rva0032A3A9Element >::erase(Rva0032A3A9Element *, Rva0032A3A9Element *);
template Rva003371B1 *_STL::vector<Rva003371B1 >::erase(Rva003371B1 *, Rva003371B1 *);
template BfmeAssignRecord104 *_STL::vector<BfmeAssignRecord104 >::erase(BfmeAssignRecord104 *, BfmeAssignRecord104 *);
template Rva004043AEElement *_STL::vector<Rva004043AEElement >::erase(Rva004043AEElement *, Rva004043AEElement *);
template Rva0040538FElement *_STL::vector<Rva0040538FElement >::erase(Rva0040538FElement *, Rva0040538FElement *);
template Rva0040DC56Element *_STL::vector<Rva0040DC56Element >::erase(Rva0040DC56Element *, Rva0040DC56Element *);
template BfmeNarrowRecord00427F75 *_STL::vector<BfmeNarrowRecord00427F75 >::erase(BfmeNarrowRecord00427F75 *, BfmeNarrowRecord00427F75 *);
template Rva004758F4Element *_STL::vector<Rva004758F4Element >::erase(Rva004758F4Element *, Rva004758F4Element *);
template Rva00520211Element *_STL::vector<Rva00520211Element >::erase(Rva00520211Element *, Rva00520211Element *);
template Rva00565865Element *_STL::vector<Rva00565865Element >::erase(Rva00565865Element *, Rva00565865Element *);
template Rva005658CBElement *_STL::vector<Rva005658CBElement >::erase(Rva005658CBElement *, Rva005658CBElement *);
template Rva005658FEElement *_STL::vector<Rva005658FEElement >::erase(Rva005658FEElement *, Rva005658FEElement *);
template Rva00565931Element *_STL::vector<Rva00565931Element >::erase(Rva00565931Element *, Rva00565931Element *);
template Rva00565964Element *_STL::vector<Rva00565964Element >::erase(Rva00565964Element *, Rva00565964Element *);
template Rva00565997Element *_STL::vector<Rva00565997Element >::erase(Rva00565997Element *, Rva00565997Element *);
template void _STL::vector<Rva005658CBElement >::clear();
template void _STL::vector<Rva005658FEElement >::clear();
template void _STL::vector<Rva00565931Element >::clear();
template void _STL::vector<Rva00565964Element >::clear();
template void _STL::vector<Rva00565997Element >::clear();
template Rva00566A42Element *_STL::vector<Rva00566A42Element >::erase(Rva00566A42Element *, Rva00566A42Element *);
template Rva00586E86Element *_STL::vector<Rva00586E86Element >::erase(Rva00586E86Element *, Rva00586E86Element *);
template Rva005DC408Element *_STL::vector<Rva005DC408Element >::erase(Rva005DC408Element *, Rva005DC408Element *);
template Rva005EF8FAElement *_STL::vector<Rva005EF8FAElement >::erase(Rva005EF8FAElement *, Rva005EF8FAElement *);
template Rva005F8620Element *_STL::vector<Rva005F8620Element >::erase(Rva005F8620Element *, Rva005F8620Element *);
template Rva003F610FElement *_STL::vector<Rva003F610FElement >::erase(Rva003F610FElement *, Rva003F610FElement *);
