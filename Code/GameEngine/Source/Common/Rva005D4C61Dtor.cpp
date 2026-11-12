// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE
// Native wrapper93 initializes16-byte listener storage at4 before the derived
// vptr and allocates the verified40-byte implementation. A nonpolymorphic
// storage base models that initialization order; original inheritance is
// structural inference. Target tableC75AAC has dtor4E06 and float callback4C48.
// Callback sends owner and float via the established two-word listener walker;
// its native unconditional collection address is owner+4. The legacy int word
// of that walker carries the32-bit owner pointer here. Both table entries have
// actual typed providers; no new pins or definition markers are introduced.
// ??1Rva005D4C61@@UAE@XZ retail 0x005D4C61 90B dtor stores vtable 0x00875AAC plus list forEach and holder clear with list free

class Rva005D4C01Listener;
#include "../../Include/Common/Rva00330757Member.h"

class Rva005D4C01Listener
{
public:
	virtual void notify(void *);
};

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#include <new>
#undef _CRTIMP

inline Rva00330757Member::~Rva00330757Member()
{
	if (field00)
		free(field00);
}

class Rva005D4C01List
{
public:
	void forEach(void (Rva005D4C01Listener::*notify)(void *), void *arg);
	Rva00330757Member storage;
};

class Rva005D4913
{
public:
	Rva005D4913(void *,int,const class AsciiString &);
 ~Rva005D4913();
 char storage[0x28];
};

class Rva005D4BE7
{
	Rva005D4913 *m_ptr;
public:
	Rva005D4BE7(Rva005D4913 *p):m_ptr(p) {}
 void rva005D4BE7();
	// Complete26B native owning-pointer destructor: clear its slot before
    // the verified54B pointee destructor and ordinary heap delete.
    __declspec(noinline) ~Rva005D4BE7()
	{
        Rva005D4913 *p = m_ptr;
        m_ptr = 0;
        if (p) { p->Rva005D4913::~Rva005D4913(); ::operator delete(p); }
	}
};

class Rva005D4C61 : public Rva005D4C01List
{
public:
	Rva005D4C61(int,const AsciiString &);
 virtual ~Rva005D4C61();
 virtual void setPosition(float);
private:
	Rva005D4BE7 m_14;
};

Rva005D4C61::~Rva005D4C61()
{
	// Retail pushes 0x001FF3A9, the slot-0 vcall thunk (mov eax,[ecx];
	// jmp [eax]): a member pointer to the listener's first virtual.
	forEach(&Rva005D4C01Listener::notify, this);
}

Rva005D4C61::Rva005D4C61(int level,const AsciiString &name):m_14(new Rva005D4913(this,level,name)) {}
class ScrollBarListenerSlots { public: virtual void slot00(); virtual void slot04(Rva005D4C61 *,float); };
#include "../../Include/Common/Rva005D48DBElem.h"
typedef void (Rva005D48DBElem::*Rva005D48DBFn)(int,float);
class Rva005D4C1FList { public: void forEach(Rva005D48DBFn,int,float); };
void Rva005D4C61::setPosition(float position) {
 reinterpret_cast<Rva005D4C1FList *>(reinterpret_cast<Rva005D4C01List *>(reinterpret_cast<char *>(this)+4))->forEach(reinterpret_cast<Rva005D48DBFn>(&ScrollBarListenerSlots::slot04),reinterpret_cast<int>(this),position);
}
