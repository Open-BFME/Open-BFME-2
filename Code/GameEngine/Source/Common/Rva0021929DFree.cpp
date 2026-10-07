// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva0021929D@Rva00219251@@QAEXPAPAVCreateAHeroData@@@Z @0x0021929D 35B
// TheHeroManager's release for the CreateAHeroData its allocator 0x00219251
// returns: global delete through the virtual destructor (slot 0 called with
// 0, then the rowed ??3@YAXPAX@Z 0x0002FD60), then clear the caller's pointer.
// Evidence: all seven callers (0x0037CB31, 0x0037CF61, 0x0037CFA0,
// 0x0040A166, 0x0040A1C4, 0x004CF296, 0x004CF2DA) load ECX with
// TheHeroManager (0x009FE344) before pushing the pointer's address, so this is
// a thiscall member that ignores this. It was rowed before as the __stdcall
// ?Rva0021929DFree@@YGXPAPAX@Z, which compiles to the same bytes; the old
// name cannot be called with ECX set. Honest-address name, on the class the
// allocator's row uses.

class CreateAHeroData
{
public:
	virtual ~CreateAHeroData();
};

class Rva00219251
{
public:
	void rva0021929D(CreateAHeroData **data);
};

void Rva00219251::rva0021929D(CreateAHeroData **data)
{
	::delete *data;
	*data = 0;
}
