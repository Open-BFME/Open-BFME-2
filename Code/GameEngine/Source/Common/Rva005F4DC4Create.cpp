// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?rva005F4DC4@Rva005F4DC4@@QAE?AVRva005F4DC4Handle@@XZ,
// retail 0x005F4DC4..0x005F4E48 (132 bytes, RET 4): returns a counted handle
// to a new 0x18-byte callback action carrying the Payload005FAB16 record
// {the +0x08 holder's +0x08 context, the +0x10 input, the +0x14 observer list,
// false}: an Rva005F4C52 (vtable 0x00C794D4) when the input's +0x18 name is
// non-empty (rowed StringBase<char>::isEmpty), else an Rva005F4C70 (vtable
// 0x00C794DC). Both constructors (rowed 0x005F4C52 / 0x005F4C70) are inlined
// here, as the 0x005FADEF owner's factories inline theirs. The unrowed caller
// at 0x005F4E48 asks two such objects for their actions.

#include "string_base.h"
#include "BattlePromptCallbackPayloadView.h"

// The two actions, as Rva005FAB16Ctor.cpp lays them out; their constructors
// are inlined here.
struct Rva005F4C52
{
	virtual void _vf() {}
	int m_ref;
	Payload005FAB16 m8;
	__forceinline Rva005F4C52(const Payload005FAB16 &o) : m_ref(0), m8(o) {}
};

struct Rva005F4C70
{
	virtual void _vf() {}
	int m_ref;
	Payload005FAB16 m8;
	__forceinline Rva005F4C70(const Payload005FAB16 &o) : m_ref(0), m8(o) {}
};

// A counted handle to either action (count at +4).
class Rva005F4DC4Handle
{
public:
	template <class T> __forceinline Rva005F4DC4Handle(T *p) : m_ptr(p) { if (p) ++p->m_ref; }
	~Rva005F4DC4Handle();
private:
	void *m_ptr;
};

struct Rva005F4DC4Input
{
	char m_pad00[0x18];
	StringBase<char> m_name;				// +0x18
};

struct Rva005F4DC4Holder
{
	char m_pad00[0x08];
	int m_context08;						// +0x08
};

class Rva005F4DC4
{
public:
	Rva005F4DC4Handle rva005F4DC4();
private:
	char m_pad00[0x08];
	Rva005F4DC4Holder *m_holder08;			// +0x08
	char m_pad0C[0x10 - 0x0C];
	Rva005F4DC4Input *m_input10;			// +0x10
	void *m_observers14;					// +0x14
};

Rva005F4DC4Handle Rva005F4DC4::rva005F4DC4()
{
	Rva005F4DC4Input *input = m_input10;
	if (!input->m_name.isEmpty())
	{
		Payload005FAB16 payload;
		payload.context = m_holder08->m_context08;
		payload.input = input;
		payload.observers = &m_observers14;
		payload.flag = false;
		return Rva005F4DC4Handle(new Rva005F4C52(payload));
	}
	else
	{
		Payload005FAB16 payload;
		payload.context = m_holder08->m_context08;
		payload.input = input;
		payload.observers = &m_observers14;
		payload.flag = false;
		return Rva005F4DC4Handle(new Rva005F4C70(payload));
	}
}
