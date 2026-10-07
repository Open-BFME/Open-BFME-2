// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// 0x00470222 217B evidence: map<int int> Xfer twin of vector sister Rva0046EFDBXfer; version {1,1} via slot 0x28
// typename "std::map" via slot 0x2c count via slot 0x78 isSaving via slot 8; save loop via rowed _M_increment
// 0x0024250 with per-item Rva00469124Xfer 0x00469124; load throws "Map must be empty on load" via bfmeFormatText
// 0x0060C36E then per-item operator[] 0x0028932C; caller 0x00473F81.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void xferModuleData(const void *&value);
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);

// Same tag as the rowed pair helper so the call resolves, but the key is int
// rather than ObjectID: retail pushes &pair straight into map<int,int>::operator[](const int &),
// which needs an int lvalue (an ObjectID would force a temp copy elsewhere).
struct Rva00469124Pair
{
	int m_id;
	int m_value;
};
extern Xfer &Rva00469124Xfer(Xfer *xfer, Rva00469124Pair *pair);

typedef _STL::map<int, int> IntIntMap;

Xfer *Rva00470222Xfer(Xfer *xfer, IntIntMap *map)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = map->size();
	xfer->xferTypeName("std::map").xferUnsignedInt(&count);

	if (xfer->isSaving()) {
		IntIntMap::iterator cur = map->begin();
		IntIntMap::iterator last = map->end();
		for (; cur != last; ++cur) {
			Rva00469124Pair item;
			item.m_id = cur->first;
			item.m_value = cur->second;
			Rva00469124Xfer(xfer, &item);
		}
	} else {
		if (!map->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "Map must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		Rva00469124Pair item;
		item.m_id = 0;
		item.m_value = 0;
		while (count != 0) {
			--count;
			Rva00469124Xfer(xfer, &item);
			(*map)[item.m_id] = item.m_value;
		}
	}
	return xfer;
}

// ?g_guardTargetTypeThrowInfo@@3HA: matched references place it at VA 0xcffd18; also referenced as ?g_rva008ffd18ThrowInfo@@3HA, ?g_rva005c5100ThrowInfo@@3HA.
int g_guardTargetTypeThrowInfo = 0;
#pragma comment(linker, "/alternatename:?g_rva008ffd18ThrowInfo@@3HA=?g_guardTargetTypeThrowInfo@@3HA")
#pragma comment(linker, "/alternatename:?g_rva005c5100ThrowInfo@@3HA=?g_guardTargetTypeThrowInfo@@3HA")

// The (void *, void *) declaration above is a C++ overload, so calls spell
// ?_CxxThrowException@@YGXPAX0@Z; retail calls the MSVC 7.1 throw helper
// __CxxThrowException@8 (its import thunk at 0x00629094). Same ABI: bind the spelling.
#pragma comment(linker, "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8")
