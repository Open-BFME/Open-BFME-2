// cl: /DNDEBUG /MD
// platformsdk
// ?Update@Rva005CFA87@@UAEXXZ @0x005CFE30 62B.
// VSlot 1 (Update) of vtable 0x008752DC (Rva005CFA87): time-guarded setter.
// Evidence: vtable slot via donor Rva005CF9FFFlagNotifyDtors plus IAT timeGetTime plus global g_00E06640 plus new 8B vtable g_00C752A8 plus rowed 0x00575674 setter.
#include <windows.h>
#include <new>
// Owned here (its only reader); retail .data zero-initializes it (VA 0x00E06640, BSS tail).
unsigned int g_00E06640 = 0;
extern "C" const void *const __identifier("??_7Rva005CF925@@6B@")[];
class Object;
#include "../../Include/Common/Rva00575674.h"
class Rva005CF872
{
public:
	virtual ~Rva005CF872() {}
	virtual void Update() {}
	void *m_04;
};
class Rva005CFA87 : public Rva005CF872
{
public:
	virtual void Update();
	unsigned int m_08;
	bool m_flag;
};
void Rva005CFA87::Update()
{
	unsigned int now = timeGetTime();
	if (now - m_08 < g_00E06640)
		return;
	void *mem = operator new(8);
	Object *obj;
	if (mem != 0)
	{
		((void **)mem)[1] = m_04;
		*(const void **)mem = (const void *)__identifier("??_7Rva005CF925@@6B@");
		obj = (Object *)mem;
	}
	else
	{
		obj = 0;
	}
	((Rva00575674 *)((char *)m_04 + 0x1c))->rva00575674(obj);
}
