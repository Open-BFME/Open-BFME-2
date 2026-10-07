// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva00473FD4Xfer@@YAPAVXfer@@PAV1@PAV?$map@H_NU?$less@H@_STL@@V?$allocator@U?$pair@$$CBH_N@_STL@@@2@@_STL@@@Z 0x00473FD4 217B evidence: map<int bool> Xfer twin of rowed map<int int> Rva00470222Xfer 0x00470222; version {1,1} via slot 0x28 typename std::map via slot 0x2c count via slot 0x78 isSaving via slot 8; save loop via rowed _M_increment 0x00024250 with per-item Rva00469103Xfer 0x00469103; load throws Map must be empty on load via bfmeFormatText 0x0060C36E then per-item operator[] 0x00470353; caller 0x00474EA8
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

// Same tag as the rowed pair helper so the call resolves, but the value is
// bool rather than int: retail loads the node value with a byte mov and
// stores through operator[] with a byte mov, which needs a bool lvalue.
struct Rva00469103Pair
{
	int m_id;
	bool m_value;
};
extern Xfer &Rva00469103Xfer(Xfer *xfer, Rva00469103Pair *pair);

typedef _STL::map<int, bool> IntBoolMap;

Xfer *Rva00473FD4Xfer(Xfer *xfer, IntBoolMap *map)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = map->size();
	xfer->xferTypeName("std::map").xferUnsignedInt(&count);

	if (xfer->isSaving()) {
		IntBoolMap::iterator cur = map->begin();
		IntBoolMap::iterator last = map->end();
		for (; cur != last; ++cur) {
			Rva00469103Pair item;
			item.m_id = cur->first;
			item.m_value = cur->second;
			Rva00469103Xfer(xfer, &item);
		}
	} else {
		if (!map->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "Map must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		Rva00469103Pair item;
		item.m_id = 0;
		item.m_value = 0;
		while (count != 0) {
			--count;
			Rva00469103Xfer(xfer, &item);
			(*map)[item.m_id] = item.m_value;
		}
	}
	return xfer;
}

// ?g_guardTargetTypeThrowInfo@@3HA: rowed via Rva00470222Xfer; declare use only.
#pragma comment(linker, "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8")
