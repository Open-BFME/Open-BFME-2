// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva002B2508@@QAE@XZ @0x002B2508 (18B). Default constructor of the class derived from the
// player skill-points rank object (rowed ctor ??0Rva00380200 0x00380523, Rva00380200Getter.cpp):
// base ctor, then the derived vtable 0x00BFDFD4 (slot 0 = 0x002B3105 destructor; slots 1..3 are
// the base's rank virtuals 0x0038037C/0x0038027B/0x0038028B). No members of its own are
// initialised. Same shape as Rva00135E35Ctor.cpp; the owner of the derived class is unproven.
class Rva00380200
{
public:
	Rva00380200();
	virtual ~Rva00380200();
};

class Rva002B2508 : public Rva00380200
{
public:
	Rva002B2508();
	virtual ~Rva002B2508();
};

Rva002B2508::Rva002B2508()
{
}
