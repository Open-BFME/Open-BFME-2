// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva00575125@@QAE@HPAX@Z retail 0x00575125 86B
// MI ctor: base Rva005746AF (rowed 0x005746AF) at +0 plus second base at +0x10 with member at +0x14.
// Evidence: calls rowed base 0x005746AF with first int arg; stores vtables 0x00C6E360 then 0x00C6E4C4 and 0x00C6E4C0; second arg stored at +0x14; rowed append 0x005A0B4C with this=second arg+4 and arg=sub at +0x10; ret 8 two args; unblocks 0x005751ED; caller 0x00575237.
// Honest Rva name. Links via rowed base and append; vtables DIR32 patched by gate.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
#include "../../Include/Common/Rva005746AF.h"

struct Rva002BA8F1Listener
{
	char opaque[4];
};
#include "../../Include/Common/Rva005A0B4CList.h"

#include "../../Include/Common/Rva00575125Second.h"
inline Rva00575125Second::~Rva00575125Second() {}
class Rva00575125 : public Rva005746AF, public Rva00575125Second
{
public:
	~Rva00575125();
	virtual void slot0(int); // defined by the destructor unit
	Rva00575125(int a, void *mgr);
private:
	void *m_14;
};

Rva00575125::Rva00575125(int a, void *mgr)
	: Rva005746AF(a)
	, Rva00575125Second()
	, m_14(mgr)
{
	((Rva005A0B4CList *)((char *)mgr + 4))->append((Rva002BA8F1Listener *)((char *)this + 0x10));
}
