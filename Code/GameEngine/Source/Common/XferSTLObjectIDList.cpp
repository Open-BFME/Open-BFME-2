// cl: /O1 /MD /Oy-
// ?xferSTLObjectIDList@@YAPAVXfer@@PAV1@PAVBridgeBehaviorObjectIDList@@@Z @0x00331F2D 196B
// Free ObjectID-list Xfer helper for BridgeBehaviorObjectIDList.
// Evidence: pinned name; callers BezierProjectileBehavior::xfer 0x0045CB23 ArrowStormUpdate::xfer DamageFieldUpdate::xfer RousingSpeechUpdate::xfer GloriousChargeUpdate::xfer; retail strings "std::list" "List must be empty on load"; rowed XferObjectID 0x003060B2 pin push_back 0x002A1B6F FormatText 0x0060C36E Throw 0x00629094; donor ZH Xfer::xferSTLObjectIDList plus BFME2 XferListInt 0x00206861 skeleton.
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
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_prev;
	ObjectID m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	UnsignedInt size() const
	{
		UnsignedInt n = 0;
		for (BridgeBehaviorObjectIDNode *p = m_node->m_next; p != m_node; p = p->m_next)
			++n;
		return n;
	}
	Bool empty() const
	{
		return m_node->m_next == m_node;
	}
	void push_back(const ObjectID &value);
	BridgeBehaviorObjectIDNode *m_node;
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const struct _s__ThrowInfo *pThrowInfo);

Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving()) {
		BridgeBehaviorObjectIDNode *sentinel = list->m_node;
		BridgeBehaviorObjectIDNode *node = sentinel->m_next;
		while (node != sentinel) {
			XferObjectID(xfer, &node->m_value);
			node = node->m_next;
		}
	} else {
		if (!list->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "List must be empty on load");
			_CxxThrowException(&error, (const struct _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
			__assume(0);
		}
		ObjectID value;
		while (count != 0) {
			--count;
			XferObjectID(xfer, &value);
			list->push_back(value);
		}
	}
	return xfer;
}
