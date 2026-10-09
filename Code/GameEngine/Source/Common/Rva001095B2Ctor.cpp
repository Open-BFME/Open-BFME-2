// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva001095B2@@QAE@XZ @0x0010B9B7 (18B) and ??0Rva00109610@@QAE@XZ @0x0010BA71 (18B).
// Derived default constructors of the two shadow-family classes whose destructors are rowed
// at 0x001095B2 (Rva001095B2Dtor.cpp) and 0x00109610 (Rva00109610Dtor.cpp) and whose scalar
// deleting destructors are 0x0010B9C9 / 0x0010BA83. Each calls its out-of-line base ctor and
// stores its own vtable (0x007CF9F4 / 0x007CFA00): the first over Rva007B1380 (rowed ctor
// 0x00109D8C), the second over Rva000F0F2B (rowed ctor 0x000F0F2B). Bases are declared only as
// far as the ctor call and virtual dispatch need; the class-view difference to the destructor
// units (which model the base as W3DProjectedShadow with an inline destructor) is deliberate:
// the constructors name their actual ctor callees. Same pattern as Rva00135E35Ctor.cpp.
class Rva007B1380
{
public:
	Rva007B1380();
	virtual void handle();
};

class Rva001095B2 : public Rva007B1380
{
public:
	Rva001095B2();
	virtual ~Rva001095B2();
};

Rva001095B2::Rva001095B2()
{
}

class Rva000F0F2B
{
public:
	Rva000F0F2B();
	virtual void handle();
};

class Rva00109610 : public Rva000F0F2B
{
public:
	Rva00109610();
	virtual ~Rva00109610();
};

Rva00109610::Rva00109610()
{
}
