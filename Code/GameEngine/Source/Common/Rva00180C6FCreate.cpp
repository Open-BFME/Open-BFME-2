// cl: /DNDEBUG /MD /EHsc
// ?Rva00180C6FCreate@@YAXPBDHH@Z @0x00180C6F 92B
// Chain of just-landed ??0Rva00180B94_Prototype@@QAE@PBDHH@Z (0x00180B2B):
// if name non-null and !Render_Obj_Exists(name) (rowed 0x0061F0D0),
// news 0x24 via rowed ??2@YAPAXI@Z, constructs
// Rva00180B94_Prototype(name,a,b) on success, then Add_Prototype(obj)
// (rowed 0x0061EF90, null-tolerant). Twin of 0x001806D8/0x001809EA.
// Caller at 0x0012CD53 unblocks 0x0012CB67.
bool __cdecl Render_Obj_Exists(const char *name);
void *__cdecl operator new(unsigned int size) throw();
void __cdecl operator delete(void *p);
void __cdecl Add_Prototype(void *proto);

class Rva00180B94_Prototype
{
	char m_pad[0x24];
public:
	Rva00180B94_Prototype(const char *name, int a, int b);
};

void __cdecl Rva00180C6FCreate(const char *name, int a, int b)
{
	if (name == 0)
		return;
	if (Render_Obj_Exists(name))
		return;
	Rva00180B94_Prototype *obj = new Rva00180B94_Prototype(name, a, b);
	Add_Prototype(obj);
}
