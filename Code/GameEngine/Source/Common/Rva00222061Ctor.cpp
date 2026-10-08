// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ??0Rva00222061@@QAE@XZ @0x00222061 95B.
// Subsystem ctor: EH baseConstruct via novtable Shell-pattern base then auto vptr then Rva0022181D at +0xC (0x1C) then int-ptr map at +0x28 then setName InGameNotificationBox.
// Evidence: calls rowed baseConstruct 0x001B4E63 rowed Rva0022181D 0x0022181D rowed map 0x0033C432 rowed StringBase 0x00037BA0 rowed setName 0x0006F3CC; vtable at +0 auto; caller 0x00222105; precedent ShellCtor EH base.
#include "ascii_string.h"
#include <map>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

class Rva0022181D
{
public:
	Rva0022181D();
	~Rva0022181D();
private:
	char m_pad[0x1C];
};

class SubsystemInterface
{
public:
	void setName(AsciiString name);
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
