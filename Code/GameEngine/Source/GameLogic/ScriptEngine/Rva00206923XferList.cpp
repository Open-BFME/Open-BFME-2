// ?Rva00206923XferList@@YAPAVXfer@@PAV1@PAV?$list@UBfmeSpecialPowerTimer8@@V?$allocator@UBfmeSpecialPowerTimer8@@@_STL@@@_STL@@@Z @0x00206923 205B
// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Free list<BfmeSpecialPowerTimer8> Xfer helper version {1 1} via slot 0x28 size via slots 0x2C 0x78 IsSaving via slot 0x08 saving walks timers via rowed Chain 0x00203D86 loading checks empty via FormatText plus Throw then reloads via Chain plus rowed push_back 0x004DE74D. Evidence: leaf lane 2 callers; prev 0x00206861 next 0x00206ABE; strings std::list List must be empty on load; same skeleton as rowed xferListInt 0x00206861 and Rva00207F91.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

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

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

struct BfmeSpecialPowerTimer8
{
	unsigned int m_templateID;
	unsigned int m_readyFrame;
};

typedef _STL::list<BfmeSpecialPowerTimer8> ListTimer;

class Rva00203D86A;
void Rva00203D86Chain(Rva00203D86A *a, void *b);

Xfer *Rva00206923XferList(Xfer *xfer, ListTimer *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = (UnsignedInt)list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		ListTimer::_Node *sentinel = (ListTimer::_Node *)list->_M_node._M_data;
		ListTimer::_Node *node = (ListTimer::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			Rva00203D86Chain((Rva00203D86A *)xfer, &node->_M_data);
			node = (ListTimer::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!list->empty())
		{
			XferException error;
			bfmeFormatText(&error, 4, "List must be empty on load");
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}

		BfmeSpecialPowerTimer8 value = {0, 0};
		while (count != 0)
		{
			--count;
			Rva00203D86Chain((Rva00203D86A *)xfer, &value);
			list->push_back(value);
		}
	}
	return xfer;
}
