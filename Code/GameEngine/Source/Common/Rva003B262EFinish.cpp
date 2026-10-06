// cl: /MD
//
// ??1Rva003B262E@@MAE@XZ 0x003B262E 68B
// Evidence: vtable 0x0081F3F4 at [this] with members at +4 Or list and +8 And ptr;
// split deleteInstance(0) plus operator delete 0x0002FD60; caller deleting dtor 0x003B331E.
// The barrier between clearing the Or node's next pointer and the virtual
// deleteInstance call is what keeps the retail store-before-vtable-load order
// (and emits no bytes).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)

class Rva003B262EAnd
{
public:
	virtual void *deleteInstance(int flags);
};

class Rva003B262EOr
{
public:
	virtual void *deleteInstance(int flags);

	Rva003B262EOr *m_next;
};

void __cdecl operator delete(void *block);

class Rva003B262E
{
protected:
	virtual ~Rva003B262E();

private:
	Rva003B262EOr *m_nextOr;
	Rva003B262EAnd *m_firstAnd;
};

Rva003B262E::~Rva003B262E()
{
	if (m_firstAnd) {
		::operator delete(m_firstAnd->deleteInstance(0));
		m_firstAnd = 0;
	}
	if (m_nextOr) {
		Rva003B262EOr *cur = m_nextOr;
		while (cur) {
			Rva003B262EOr *next = cur->m_next;
			cur->m_next = 0;
			_ReadWriteBarrier();
			::operator delete(cur->deleteInstance(0));
			cur = next;
		}
	}
}
