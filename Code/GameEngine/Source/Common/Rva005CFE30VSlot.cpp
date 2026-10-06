// cl: /DNDEBUG /MD
// ?rva005CFE30@Rva005CFA87@@UAEXXZ @0x005CFE30 62B.
// VSlot 1 of vtable 0x008752DC (Rva005CFA87): time-guarded setter.
// Evidence: vtable slot via donor Rva005CF9FFFlagNotifyDtors plus IAT timeGetTime plus global g_00E06640 plus new 8B vtable g_00C752A8 plus rowed 0x00575674 setter.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern unsigned int g_00E06640;
extern const void *const g_00C752A8[];
void *__cdecl operator new(unsigned int size);
class Object;
class Rva00575674
{
public:
	void rva00575674(Object *p);
};
class Rva005CF872
{
public:
	virtual ~Rva005CF872() {}
	void *m_04;
};
class Rva005CFA87 : public Rva005CF872
{
public:
	virtual void rva005CFE30();
	unsigned int m_08;
	bool m_flag;
};
void Rva005CFA87::rva005CFE30()
{
	unsigned int now = timeGetTime();
	if (now - m_08 < g_00E06640)
		return;
	void *mem = operator new(8);
	Object *obj;
	if (mem != 0)
	{
		((void **)mem)[1] = m_04;
		*(const void **)mem = (const void *)g_00C752A8;
		obj = (Object *)mem;
	}
	else
	{
		obj = 0;
	}
	((Rva00575674 *)((char *)m_04 + 0x1c))->rva00575674(obj);
}
