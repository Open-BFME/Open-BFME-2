// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva000BC559Xfer@@YAPAVXfer@@PAV1@PAV?$set@HU?$less@H@_STL@@V?$allocator@H@2@@_STL@@@Z @0x000BC559 196B via set-DrawableID xfer
// Evidence: same 196B skeleton as list-ObjectID Xfer 0x0036ABAF (version 1 1 via slot 0x28 type std-set via 0x2c count via 0x78 isSaving via 0x08);
// save walks Rb nodes via rowed XferDrawableID 0x003060CA and _M_increment 0x00024250;
// load throws Set-must-be-empty via FormatText 0x0060C36E then inserts via rowed set-int insert 0x000BC15D.
#define _STLP_NO_EXCEPTIONS 1
#include <set>

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
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};


void XferDrawableID(Xfer *xfer, int *value);

typedef _STL::set<int> SetInt;

Xfer *Rva000BC559Xfer(Xfer *xfer, SetInt *set)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = set->size();
	xfer->xferTypeName("std::set").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		SetInt::iterator end = set->end();
		SetInt::iterator node = set->begin();
		while (node != end)
		{
			XferDrawableID(xfer, (int *)&*node);
			++node;
		}
	}
	else
	{
		if (!set->empty())
		{
			throw XferException(4, "Set must be empty on load");
		}

		int value;
		while (count != 0)
		{
			--count;
			XferDrawableID(xfer, &value);
			set->insert(value);
		}
	}
	return xfer;
}

// Two more set<int> transfers with this body, each moving the elements through
// another rowed per-element helper (the only difference from Rva000BC559Xfer):
// 0x002E208A through XferLivingWorldRegionBonusRuleID, 0x002F1CDD through
// XferObjectID. The Xfer slots they call are the ones modeled above.

void XferLivingWorldRegionBonusRuleID(Xfer *xfer, int *value);
enum ObjectID { INVALID_ID = 0 };
void XferObjectID(Xfer *xfer, ObjectID *value);

// ?Rva002E208AXfer@@YAPAVXfer@@PAV1@PAV?$set@HU?$less@H@_STL@@V?$allocator@H@2@@_STL@@@Z @0x002E208A 196B
Xfer *Rva002E208AXfer(Xfer *xfer, SetInt *set)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = set->size();
	xfer->xferTypeName("std::set").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		SetInt::iterator end = set->end();
		SetInt::iterator node = set->begin();
		while (node != end)
		{
			XferLivingWorldRegionBonusRuleID(xfer, (int *)&*node);
			++node;
		}
	}
	else
	{
		if (!set->empty())
		{
			throw XferException(4, "Set must be empty on load");
		}

		int value;
		while (count != 0)
		{
			--count;
			XferLivingWorldRegionBonusRuleID(xfer, &value);
			set->insert(value);
		}
	}
	return xfer;
}

// ?Rva002F1CDDXfer@@YAPAVXfer@@PAV1@PAV?$set@HU?$less@H@_STL@@V?$allocator@H@2@@_STL@@@Z @0x002F1CDD 196B
Xfer *Rva002F1CDDXfer(Xfer *xfer, SetInt *set)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = set->size();
	xfer->xferTypeName("std::set").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		SetInt::iterator end = set->end();
		SetInt::iterator node = set->begin();
		while (node != end)
		{
			XferObjectID(xfer, (ObjectID *)&*node);
			++node;
		}
	}
	else
	{
		if (!set->empty())
		{
			throw XferException(4, "Set must be empty on load");
		}

		int value;
		while (count != 0)
		{
			--count;
			XferObjectID(xfer, (ObjectID *)&value);
			set->insert(value);
		}
	}
	return xfer;
}
