// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /O1 /arch:SSE /G7
// stlport
// ?rva00387479@Rva00386374@@UAEXUGen_uw_00385371@@@Z 0x00387479 55B
// Evidence: vtable slot 38 of 0x00819500 class Rva00386374; calls PSPlayerAllStats operator= 0x3874B0 and Gen_uw dtor 0x385371; by-value 0x548 param ret 0x548.
typedef int Int;

#include "../../../Include/GameNetwork/Rva003844D7.h"

#include "../../../Include/GameNetwork/Rva0038454E.h"

struct Rva00385333
{
	char m_pad[0x1A8];
};

class PSPlayerAllStats
{
public:
	PSPlayerAllStats &operator=(const PSPlayerAllStats &that);
private:
	Int m_id;
	Int m_unk004;
	Rva00385333 m_tournament;
	Rva003844D7 m_open;
	Rva0038454E m_strategic;
};

struct Gen_uw_00385371 : public PSPlayerAllStats
{
	~Gen_uw_00385371();
};

class Rva00386374
{
public:
	virtual void rva00387479(Gen_uw_00385371 s);
private:
	char m_pad04[0x84 - 4];
	PSPlayerAllStats m_84;
};

void Rva00386374::rva00387479(Gen_uw_00385371 s)
{
	m_84 = s;
}

// The retail call in this body reads 0x00385371, an address the ledger already
// carries as ??1PSPlayerAllStats@@QAE@XZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??1Gen_uw_00385371@@QAE@XZ=??1PSPlayerAllStats@@QAE@XZ")
