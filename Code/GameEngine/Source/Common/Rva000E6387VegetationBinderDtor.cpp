// cl: /O1 /MD /EHsc
// ??1Rva000E6387@@UAE@XZ @0x000E6387 57B: destructor of the FX parameter
// binder registered as "Vegetation" (address-derived name Rva000E6387, as
// pinned). Target facts: vtable 0x00BCEA04 = { ??_G 0x000E63C0 (rowed),
// dispatcher 0x000E67E3 }; base vtable 0x00BC6F24 = { deleting dtor,
// __purecall }, the binder base modelled in the rowed Rva000E19A3Dtor.cpp
// ("Terrain"). The dtor erases its "Vegetation" registration through the
// rowed Rva001532E1Erase 0x001532E1 (same as the Terrain dtor erases
// "Terrain") and resets to the base vtable; the EH state around the erase
// covers the base subobject. Callers: rowed ??_G 0x000E63C0 and the gap
// thunk 0x007B6E18 on the singleton g_Va00DEBC98.

void __cdecl Rva001532E1Erase(const char *name);

class Rva0015354E;

// FX parameter binder base: vtable 0x00BC6F24 = { deleting dtor, __purecall }.
class Base
{
public:
	virtual ~Base() {}
	virtual void bind(const char *name, const char *handle, Rva0015354E *registry) = 0;
};

class Rva000E6387 : public Base
{
public:
	virtual ~Rva000E6387();
	virtual void bind(const char *name, const char *handle, Rva0015354E *registry);
};

Rva000E6387::~Rva000E6387()
{
	Rva001532E1Erase("Vegetation");
}
