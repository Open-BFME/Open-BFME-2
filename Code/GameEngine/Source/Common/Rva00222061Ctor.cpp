// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ??0Rva00222061@@QAE@XZ @0x00222061 95B.
// Subsystem ctor: EH baseConstruct via novtable Shell-pattern base then auto vptr then Rva0022181D at +0xC (0x1C) then int-ptr map at +0x28 then setName InGameNotificationBox.
// Evidence: calls rowed baseConstruct 0x001B4E63 rowed Rva0022181D 0x0022181D rowed map 0x0033C432 rowed StringBase 0x00037BA0 rowed setName 0x0006F3CC; vtable at +0 auto; caller 0x00222105; precedent ShellCtor EH base.
#include "ascii_string.h"
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
// bfme link decl-only end

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

// Retail's ctor unwind (state 1) destroys the +0xC member through the rowed
// ~Open2Dtor4793C0 0x002218D0.
class Open2Dtor4793C0
{
public:
	~Open2Dtor4793C0();
};

class Rva0022181D
{
public:
	Rva0022181D();
	~Rva0022181D() { ((Open2Dtor4793C0 *)this)->Open2Dtor4793C0::~Open2Dtor4793C0(); }
private:
	char m_pad[0x1C];
};


class Rva00222061 : public BFME2NativeNetworkBase
{
public:
	Rva00222061();
	virtual ~Rva00222061();
private:
	Rva0022181D m_0C;
	_STL::map<int, void *> m_28;
};

Rva00222061::Rva00222061()
	: m_0C()
	, m_28()
{
	((SubsystemInterface *)this)->setName("InGameNotificationBox");
}
