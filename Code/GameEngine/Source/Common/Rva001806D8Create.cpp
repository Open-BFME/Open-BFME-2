// cl: /DNDEBUG /MD /EHsc
// ?Rva001806D8Create@@YAXPBDHH@Z @0x001806D8 92B
// Chain of just-landed ??0Rva001805E0 (0x001805E0): if name non-null and
// !Render_Obj_Exists(name) (rowed 0x0061F0D0), news 0x24 via rowed
// ??2@YAPAXI@Z, constructs Rva001805E0(name,a,b) on success,
// then Add_Prototype(obj) (rowed 0x0061EF90, null-tolerant). Twin of
// 0x001804CB. Caller at 0x0012CDC8 unblocks 0x0012CB67.
bool __cdecl Render_Obj_Exists(const char *name);
void *__cdecl operator new(unsigned int size) throw();
void __cdecl operator delete(void *p);
void __cdecl Add_Prototype(void *proto);

class Rva001805E0
{
	char m_pad[0x24];
public:
	Rva001805E0(const char *name, int a, int b);
};

void __cdecl Rva001806D8Create(const char *name, int a, int b)
{
	if (name == 0)
		return;
	if (Render_Obj_Exists(name))
		return;
	Rva001805E0 *obj = new Rva001805E0(name, a, b);
	Add_Prototype(obj);
}
