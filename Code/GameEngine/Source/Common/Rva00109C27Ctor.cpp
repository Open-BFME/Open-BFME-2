// cl: /O1 /DNDEBUG /MD /EHsc -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// ??0Rva00109C27@@QAE@PBD@Z @0x00109C27 60B
// Native60B owner zeroes inherited NextHash at+4 and constructs StringClass at+8.
// Native state0 cleanup7645D7 calls complete7B virtual Hashable destructorEF9CF,
// which restores BCEF94. Its complete8B table is [EF9D6,purecall3B810]; the
// established13B constructorEF9C2 independently fixes the base size and field.
// Layout/semantics follow WWLib hash.h at BFME1 donor a7c38d3b2597121f178ab5190b3062478823257d.
// The original derived identity remains unknown. The native parent and complete
// EH graph are exact; caller109CDC and existing54B destructor109C7F agree.
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"
// WWLib hash.h base: native8B layout and BCEF94 table.
#include "../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"
class Rva00109C27 : public HashableClass
{
public:
	Rva00109C27(const char *src);
	virtual ~Rva00109C27();
    virtual const char *Get_Key();
private:
	StringClass m_str;
};
Rva00109C27::Rva00109C27(const char *src)
	: HashableClass()
	, m_str(src, false)
{
}
