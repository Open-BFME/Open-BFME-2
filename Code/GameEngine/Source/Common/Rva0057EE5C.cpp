// cl: /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
#include <vector>
enum ObjectID{INVALID_OBJECT_ID=0};
// Native170B ctor57EDB2 and matched150B sibling57F486 establish the
// novtable base58 forwarding initializer2D2C34/destructor5248D0 pair.
// Retail proves reference58 counters5C/60 three12B vector controls64/70/7C
// flags88/89 rules descriptor8C and vectorB4. Element int in the three
// empty controls is a storage inference; ObjectID for B4 is carried from
// its independently owned fill-constructor provider57ED87. All members
// and all existing destructor/refresh bodies are verified together.
// ??1Rva0057EE5C@@UAE@XZ @0x0057EE5C 141B
// Evidence: unlock dtor stores vtable 0x0086F4F0 frees +0xB4 +0x7C +0x70 +0x64 via rowed _free 0x00030830 releases +0x58 via rowed fastcall ReleaseTreeHintRef 0x0007DEEF then pinned base dtor 0x005248D0. Callers 0x0044227B 0x0057EEF1 0x0043DAC3. Prev VectorObjectIDFillInsert next Rva0057F2DE.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"

struct FreeHolder0057EE5C
{
	char *m_ptr;
	~FreeHolder0057EE5C()
	{
		if (m_ptr)
			free(m_ptr);
	}
};

struct ReleaseHolder0057EE5C
{
	TargetRef00217D4C *m_ptr;
 ReleaseHolder0057EE5C(TargetRef00217D4C*p):m_ptr(p){if(p)++p->references;}
	~ReleaseHolder0057EE5C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

#include "../../Include/GameClient/Rva005248D0.h"

class Rva0057EE5C : public Rva005248D0
{
public:
	Rva0057EE5C(TargetRef00217D4C*);
 virtual ~Rva0057EE5C();
	virtual void vslot1(int a, int b) = 0;	// slot 1 of 0x00C6F4F0 is __purecall
	void rva0057F002(int arg);
private:
ReleaseHolder0057EE5C m_58;
int m_5C,m_60;
_STL::vector<int> m_64,m_70,m_7C;
bool m_88,m_89;char pad8A[2];
int m_8C;char pad90[0xB4-0x90];
_STL::vector<ObjectID> m_B4;
};

Rva0057EE5C::~Rva0057EE5C()
{
}

class UnicodeString;
#include "../../Include/Common/MpGameRules.h"

class AptMpGameRules
{
public:
	void rva0057EF18();
};

void Rva0057EE5C::rva0057F002(int arg)
{
	if (m_60 == arg) {
		return;
	}
	m_60 = arg;
	MpGameRules::GetDefaults(arg, &m_8C);
	vslot1(10, 0);
	reinterpret_cast<AptMpGameRules *>(this)->rva0057EF18();
}
