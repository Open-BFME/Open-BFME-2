// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ??0OrCondition@@QAE@XZ, retail 0x003B238A, 17 bytes.
// Zero Hour Scripts.h: OrCondition():m_nextOr(NULL),m_firstAnd(NULL){} - the
// two link words at +4/+8 cleared and the OrCondition vtable VA 0x00C1F3F4
// installed (the same table OrConditionParse.cpp's inline allocation writes
// as ??_7OrCondition@@6B@). Retail keeps this out-of-line copy with no
// direct caller; duplicate() and the chunk parser expand it inline. Only the
// two members the body touches are modelled; MemoryPoolObject contributes
// just the vptr here. Skeleton twin of the 0x0031454D base constructor.

#include <new.h>

class Condition;

class OrCondition
{
public:
	OrCondition();
protected:
	virtual ~OrCondition();

protected:
	OrCondition *m_nextOr;	// Next or clause.
	Condition *m_firstAnd;	// These are Anded.
};

__declspec(noinline) inline OrCondition::OrCondition() : m_nextOr(0), m_firstAnd(0)
{
}

static void anchorOrConditionCtor(void *p) { new (p) OrCondition(); }
namespace { void (*kAnchorOrConditionCtor)(void *) = &anchorOrConditionCtor; }

// vftable 0x00C1F3F4 slot 0 is the deleting dtor 0x003B331E, whose dtor call is the body at 0x003B262E.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct OrConditionNativeDeleteView { virtual void *destroy(int flags); };
OrCondition::~OrCondition()
{
	if (m_firstAnd) {
		::operator delete(((OrConditionNativeDeleteView *)m_firstAnd)->destroy(0));
		m_firstAnd = 0;
	}
	if (m_nextOr) {
		OrCondition *cur = m_nextOr;
		while (cur) {
			OrCondition *next = cur->m_nextOr;
			cur->m_nextOr = 0;
			_ReadWriteBarrier();
			::operator delete(((OrConditionNativeDeleteView *)cur)->destroy(0));
			cur = next;
		}
	}
}

