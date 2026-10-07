// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
#include <hash_map>
// Native group-order serialization family: 0x00355770 invokes two 225-byte
// map serializers at 0x0035552A and 0x0035568F. Their own call sites reach
// the rowed GroupOrder factory-pair serializer 0x00355100 and the rowed
// ObjectID/pointer-pair serializer 0x0035511B, respectively. Owner and method
// names remain unknown; only the consumed ABI and target offsets are claimed.

struct XferVersion
{
	unsigned char current;
	unsigned char minimum;
};

// Same primitive ABI as the verified GroupOrderXfer.cpp provider view.
class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion &version);
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
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(unsigned int &value);
};

// Existing counter provider: GroupOrderCopyCtor.cpp owns this data symbol.
extern int g_Va00E05F74;

Xfer *Rva0035552AXfer(Xfer *xfer, void *map);
Xfer *Rva0035568FXfer(Xfer *xfer, void *map);

class Rva00355770
{
public:
	void rva00355770(Xfer *xfer);
private:
	unsigned char m_unknown00[4];
	unsigned char m_firstMap[0x14];
	unsigned char m_secondMap[0x14];
};

// Native 0x00355770..0x003557B7, RET 4; Xfer slots 10 and 30, then
// cdecl map serializers using receiver +4 and +0x18, respectively.
void Rva00355770::rva00355770(Xfer *xfer)
{
	XferVersion version = { 1, 1 };
	xfer->xferVersion(version);
	xfer->xferUnsignedInt(reinterpret_cast<unsigned int &>(g_Va00E05F74));
	Rva0035552AXfer(xfer, m_firstMap);
	Rva0035568FXfer(xfer, m_secondMap);
}

// The native cursor carries {node, table}; node fields are next +0, 32-bit
// key +4 and pointer value +8. Begin 0x427195 reads only bucket-vector
// offsets +4/+8. Increment 0x41E832 reaches the raw 32-bit identity-hash
// bucket walker 0x39FD3E. Reuse the already pinned int-key cursor ABI,
// without naming the unknown GroupOrder map's template specialization.
enum Relationship { ENEMIES = 0, NEUTRAL, ALLIES };
typedef _STL::hash_map<int, Relationship, _STL::hash<int>,
	_STL::equal_to<int> >::iterator GroupOrderMapCursor;
namespace _STL {
template <> GroupOrderMapCursor &GroupOrderMapCursor::operator++();
}

class Rva000411084;
class Rva000427195
{
public:
	void *first(Rva000411084 *cursor);
};

struct GroupOrderMapWords
{
	unsigned char m_unknown00[4];
	void **m_bucketBegin;
	void **m_bucketEnd;
	void **m_bucketCapacityEnd;
	unsigned int m_count;
};

// Rowed 0x41F4E5 consumes a 32-bit key and returns the pointer-valued
// slot at node +8. Both native serializers call that exact provider.
class Object;
class ObjectLookupMap
{
public:
	Object **findSlot(int *key);
};

class GroupOrder;
struct Rva00355100Pair
{
	int m_key;
	GroupOrder *m_order;
};
Xfer *Rva00355100Xfer(Xfer *, Rva00355100Pair *);

struct XferException
{
	char *text;
	int tag;
};
extern "C" XferException *__cdecl bfmeFormatText(XferException *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern int g_guardTargetTypeThrowInfo;

// Native 0x35552A..0x35560B: version 1, named hash-map count, save pairs;
// loading requires an empty map and reconstructs count pointer-valued slots.
Xfer *Rva0035552AXfer(Xfer *xfer, void *mapStorage)
{
	GroupOrderMapWords *map = static_cast<GroupOrderMapWords *>(mapStorage);
	XferVersion version = { 1, 1 };
	xfer->xferVersion(version);
	unsigned int count = map->m_count;
	xfer->xferTypeName("std::hash_map").xferUnsignedInt(count);

	if (xfer->isSaving()) {
		GroupOrderMapCursor cursor;
		reinterpret_cast<Rva000427195 *>(map)->first(
			reinterpret_cast<Rva000411084 *>(&cursor));
		while (cursor._M_cur != 0) {
			Rva00355100Pair item;
			item.m_key = cursor._M_cur->_M_val.first;
			item.m_order = reinterpret_cast<GroupOrder *>(cursor._M_cur->_M_val.second);
			Rva00355100Xfer(xfer, &item);
			++cursor;
		}
	} else {
		if (map->m_count != 0) {
			XferException error;
			bfmeFormatText(&error, 4, "Map must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		Rva00355100Pair item = { 0, 0 };
		while (count != 0) {
			--count;
			Rva00355100Xfer(xfer, &item);
			*reinterpret_cast<ObjectLookupMap *>(map)->findSlot(&item.m_key) =
				reinterpret_cast<Object *>(item.m_order);
		}
	}
	return xfer;
}

// Pair type is shared with the rowed ObjectID/pointer factory serializer.
enum ObjectID { INVALID_ID = 0 };
class Rva0054840A;
struct Rva0035511BPair
{
	ObjectID m_id;
	Rva0054840A *m_ptr;
};
Xfer *Rva0035511BXfer(Xfer *, Rva0035511BPair *);

// Native 0x35568F..0x355770: version 1, named hash-map count, save pairs;
// loading requires an empty map and reconstructs count pointer-valued slots.
Xfer *Rva0035568FXfer(Xfer *xfer, void *mapStorage)
{
	GroupOrderMapWords *map = static_cast<GroupOrderMapWords *>(mapStorage);
	XferVersion version = { 1, 1 };
	xfer->xferVersion(version);
	unsigned int count = map->m_count;
	xfer->xferTypeName("std::hash_map").xferUnsignedInt(count);

	if (xfer->isSaving()) {
		GroupOrderMapCursor cursor;
		reinterpret_cast<Rva000427195 *>(map)->first(
			reinterpret_cast<Rva000411084 *>(&cursor));
		while (cursor._M_cur != 0) {
			Rva0035511BPair item;
			item.m_id = static_cast<ObjectID>(cursor._M_cur->_M_val.first);
			item.m_ptr = reinterpret_cast<Rva0054840A *>(cursor._M_cur->_M_val.second);
			Rva0035511BXfer(xfer, &item);
			++cursor;
		}
	} else {
		if (map->m_count != 0) {
			XferException error;
			bfmeFormatText(&error, 4, "Map must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		Rva0035511BPair item = { INVALID_ID, 0 };
		while (count != 0) {
			--count;
			Rva0035511BXfer(xfer, &item);
			*reinterpret_cast<ObjectLookupMap *>(map)->findSlot(reinterpret_cast<int *>(&item.m_id)) =
				reinterpret_cast<Object *>(item.m_ptr);
		}
	}
	return xfer;
}
