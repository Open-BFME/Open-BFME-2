// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common
// stlport
// ?Rva00206B02Xfer@@YAPAVXfer@@PAV1@PAV?$list@UBfmeSpecialPowerTimer8@@V?$allocator@UBfmeSpecialPowerTimer8@@@_STL@@@_STL@@@Z, retail 0x00206B02, 205 bytes.
// Free list<BfmeSpecialPowerTimer8> Xfer helper.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "BfmeSpecialPowerTimer8.h"
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
class Rva00203E2CA
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29();
	virtual Xfer *s30(void *p);
};
class Rva00203E2CB
{
public:
	char m_pad[4];
	unsigned int m_id;
};
void Rva00203E2CXfer(Rva00203E2CA *a, Rva00203E2CB *b);
typedef _STL::list<BfmeSpecialPowerTimer8> ListTimer;
Xfer *Rva00206B02Xfer(Xfer *xfer, ListTimer *list)
{
	UnsignedInt count;
	union
	{
		XferVersion version;
		int versionPad;
	};
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);
	count = list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);
	if (xfer->isSaving())
	{
		ListTimer::_Node *sentinel = list->_M_node._M_data;
		ListTimer::_Node *node = (ListTimer::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			Rva00203E2CXfer((Rva00203E2CA *)xfer, (Rva00203E2CB *)&node->_M_data);
			node = (ListTimer::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!list->empty())
		{
			throw XferException(4, "List must be empty on load");
		}
		BfmeSpecialPowerTimer8 value;
		value.m_templateID = 0;
		value.m_readyFrame = 0;
		while (count != 0)
		{
			--count;
			Rva00203E2CXfer((Rva00203E2CA *)xfer, (Rva00203E2CB *)&value);
			list->push_back(value);
		}
	}
	return xfer;
}
