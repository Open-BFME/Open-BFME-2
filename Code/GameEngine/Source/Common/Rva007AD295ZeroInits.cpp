// cl: /O1 /DNDEBUG /MD
//
// Static-initializer strip: zero a 4-byte TU-local static through memset.
// Retail repeats one 18-byte dynamic initializer 63 times from 0x007AD295,
// memset(&s, 0, 4) on a per-copy static: the per-translation-unit
// initializer of a header-level object whose constructor clears itself with
// memset. In these 56 copies the static is never read anywhere in .text; the
// owning TUs are unrecovered, so each copy keeps an honest address name and
// its static stays TU-local here.

extern "C" void * __cdecl memset(void *, int, unsigned int);

struct Rva007AD295ZeroInits
{
	static void rva007AD295();
	static void rva007AD2A7();
	static void rva007AD2B9();
	static void rva007AD2CB();
	static void rva007AD2DD();
	static void rva007ADD18();
	static void rva007ADD2A();
	static void rva007ADD3C();
	static void rva007ADD4E();
	static void rva007ADD60();
	static void rva007ADF06();
	static void rva007ADF18();
	static void rva007ADF2A();
	static void rva007ADF3C();
	static void rva007ADF4E();
	static void rva007AEF03();
	static void rva007AEF15();
	static void rva007AEF27();
	static void rva007AEF39();
	static void rva007AEF4B();
	static void rva007AF063();
	static void rva007AF075();
	static void rva007AF087();
	static void rva007AF099();
	static void rva007AF0AB();
	static void rva007AF3D7();
	static void rva007AF3E9();
	static void rva007AF3FB();
	static void rva007AF40D();
	static void rva007AF41F();
	static void rva007B015F();
	static void rva007B0171();
	static void rva007B0183();
	static void rva007B0195();
	static void rva007B01A7();
	static void rva007B079B();
	static void rva007B07AD();
	static void rva007B07BF();
	static void rva007B07D1();
	static void rva007B07E3();
	static void rva007B0A6A();
	static void rva007B0A7C();
	static void rva007B0A8E();
	static void rva007B0AA0();
	static void rva007B0AB2();
	static void rva007B0CB7();
	static void rva007B0CC9();
	static void rva007B0CDB();
	static void rva007B0CED();
	static void rva007B0CFF();
	static void rva007B25BC();
	static void rva007B25CE();
	static void rva007B25E0();
	static void rva007B25F2();
	static void rva007B2604();
	static void rva007B3162();
};

#define ZERO_INIT(init) \
	static int s_##init; \
	void Rva007AD295ZeroInits::init() \
	{ \
		memset( &s_##init, 0, sizeof( s_##init ) ); \
	}

// ?rva007AD295@Rva007AD295ZeroInits@@SAXXZ @ 0x007AD295 (18B), static at VA 0x00DFDC6C
ZERO_INIT( rva007AD295 )
// ?rva007AD2A7@Rva007AD295ZeroInits@@SAXXZ @ 0x007AD2A7 (18B), static at VA 0x00DFDC70
ZERO_INIT( rva007AD2A7 )
// ?rva007AD2B9@Rva007AD295ZeroInits@@SAXXZ @ 0x007AD2B9 (18B), static at VA 0x00DFDC74
ZERO_INIT( rva007AD2B9 )
// ?rva007AD2CB@Rva007AD295ZeroInits@@SAXXZ @ 0x007AD2CB (18B), static at VA 0x00DFDC78
ZERO_INIT( rva007AD2CB )
// ?rva007AD2DD@Rva007AD295ZeroInits@@SAXXZ @ 0x007AD2DD (18B), static at VA 0x00DFDC7C
ZERO_INIT( rva007AD2DD )
// ?rva007ADD18@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADD18 (18B), static at VA 0x00DFE96C
ZERO_INIT( rva007ADD18 )
// ?rva007ADD2A@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADD2A (18B), static at VA 0x00DFE970
ZERO_INIT( rva007ADD2A )
// ?rva007ADD3C@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADD3C (18B), static at VA 0x00DFE974
ZERO_INIT( rva007ADD3C )
// ?rva007ADD4E@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADD4E (18B), static at VA 0x00DFE978
ZERO_INIT( rva007ADD4E )
// ?rva007ADD60@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADD60 (18B), static at VA 0x00DFE97C
ZERO_INIT( rva007ADD60 )
// ?rva007ADF06@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADF06 (18B), static at VA 0x00DFEB9C
ZERO_INIT( rva007ADF06 )
// ?rva007ADF18@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADF18 (18B), static at VA 0x00DFEBA0
ZERO_INIT( rva007ADF18 )
// ?rva007ADF2A@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADF2A (18B), static at VA 0x00DFEBA4
ZERO_INIT( rva007ADF2A )
// ?rva007ADF3C@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADF3C (18B), static at VA 0x00DFEBA8
ZERO_INIT( rva007ADF3C )
// ?rva007ADF4E@Rva007AD295ZeroInits@@SAXXZ @ 0x007ADF4E (18B), static at VA 0x00DFEBAC
ZERO_INIT( rva007ADF4E )
// ?rva007AEF03@Rva007AD295ZeroInits@@SAXXZ @ 0x007AEF03 (18B), static at VA 0x00E01F14
ZERO_INIT( rva007AEF03 )
// ?rva007AEF15@Rva007AD295ZeroInits@@SAXXZ @ 0x007AEF15 (18B), static at VA 0x00E01F18
ZERO_INIT( rva007AEF15 )
// ?rva007AEF27@Rva007AD295ZeroInits@@SAXXZ @ 0x007AEF27 (18B), static at VA 0x00E01F1C
ZERO_INIT( rva007AEF27 )
// ?rva007AEF39@Rva007AD295ZeroInits@@SAXXZ @ 0x007AEF39 (18B), static at VA 0x00E01F20
ZERO_INIT( rva007AEF39 )
// ?rva007AEF4B@Rva007AD295ZeroInits@@SAXXZ @ 0x007AEF4B (18B), static at VA 0x00E01F24
ZERO_INIT( rva007AEF4B )
// ?rva007AF063@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF063 (18B), static at VA 0x00E022CC
ZERO_INIT( rva007AF063 )
// ?rva007AF075@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF075 (18B), static at VA 0x00E022D0
ZERO_INIT( rva007AF075 )
// ?rva007AF087@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF087 (18B), static at VA 0x00E022D4
ZERO_INIT( rva007AF087 )
// ?rva007AF099@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF099 (18B), static at VA 0x00E022D8
ZERO_INIT( rva007AF099 )
// ?rva007AF0AB@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF0AB (18B), static at VA 0x00E022DC
ZERO_INIT( rva007AF0AB )
// ?rva007AF3D7@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF3D7 (18B), static at VA 0x00E028F0
ZERO_INIT( rva007AF3D7 )
// ?rva007AF3E9@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF3E9 (18B), static at VA 0x00E028F4
ZERO_INIT( rva007AF3E9 )
// ?rva007AF3FB@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF3FB (18B), static at VA 0x00E028F8
ZERO_INIT( rva007AF3FB )
// ?rva007AF40D@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF40D (18B), static at VA 0x00E028FC
ZERO_INIT( rva007AF40D )
// ?rva007AF41F@Rva007AD295ZeroInits@@SAXXZ @ 0x007AF41F (18B), static at VA 0x00E02900
ZERO_INIT( rva007AF41F )
// ?rva007B015F@Rva007AD295ZeroInits@@SAXXZ @ 0x007B015F (18B), static at VA 0x00E030F4
ZERO_INIT( rva007B015F )
// ?rva007B0171@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0171 (18B), static at VA 0x00E030F8
ZERO_INIT( rva007B0171 )
// ?rva007B0183@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0183 (18B), static at VA 0x00E030FC
ZERO_INIT( rva007B0183 )
// ?rva007B0195@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0195 (18B), static at VA 0x00E03100
ZERO_INIT( rva007B0195 )
// ?rva007B01A7@Rva007AD295ZeroInits@@SAXXZ @ 0x007B01A7 (18B), static at VA 0x00E03104
ZERO_INIT( rva007B01A7 )
// ?rva007B079B@Rva007AD295ZeroInits@@SAXXZ @ 0x007B079B (18B), static at VA 0x00E033BC
ZERO_INIT( rva007B079B )
// ?rva007B07AD@Rva007AD295ZeroInits@@SAXXZ @ 0x007B07AD (18B), static at VA 0x00E033C0
ZERO_INIT( rva007B07AD )
// ?rva007B07BF@Rva007AD295ZeroInits@@SAXXZ @ 0x007B07BF (18B), static at VA 0x00E033C4
ZERO_INIT( rva007B07BF )
// ?rva007B07D1@Rva007AD295ZeroInits@@SAXXZ @ 0x007B07D1 (18B), static at VA 0x00E033C8
ZERO_INIT( rva007B07D1 )
// ?rva007B07E3@Rva007AD295ZeroInits@@SAXXZ @ 0x007B07E3 (18B), static at VA 0x00E033CC
ZERO_INIT( rva007B07E3 )
// ?rva007B0A6A@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0A6A (18B), static at VA 0x00E03498
ZERO_INIT( rva007B0A6A )
// ?rva007B0A7C@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0A7C (18B), static at VA 0x00E0349C
ZERO_INIT( rva007B0A7C )
// ?rva007B0A8E@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0A8E (18B), static at VA 0x00E034A0
ZERO_INIT( rva007B0A8E )
// ?rva007B0AA0@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0AA0 (18B), static at VA 0x00E034A4
ZERO_INIT( rva007B0AA0 )
// ?rva007B0AB2@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0AB2 (18B), static at VA 0x00E034A8
ZERO_INIT( rva007B0AB2 )
// ?rva007B0CB7@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0CB7 (18B), static at VA 0x00E03608
ZERO_INIT( rva007B0CB7 )
// ?rva007B0CC9@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0CC9 (18B), static at VA 0x00E0360C
ZERO_INIT( rva007B0CC9 )
// ?rva007B0CDB@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0CDB (18B), static at VA 0x00E03610
ZERO_INIT( rva007B0CDB )
// ?rva007B0CED@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0CED (18B), static at VA 0x00E03614
ZERO_INIT( rva007B0CED )
// ?rva007B0CFF@Rva007AD295ZeroInits@@SAXXZ @ 0x007B0CFF (18B), static at VA 0x00E03618
ZERO_INIT( rva007B0CFF )
// ?rva007B25BC@Rva007AD295ZeroInits@@SAXXZ @ 0x007B25BC (18B), static at VA 0x00E04020
ZERO_INIT( rva007B25BC )
// ?rva007B25CE@Rva007AD295ZeroInits@@SAXXZ @ 0x007B25CE (18B), static at VA 0x00E04024
ZERO_INIT( rva007B25CE )
// ?rva007B25E0@Rva007AD295ZeroInits@@SAXXZ @ 0x007B25E0 (18B), static at VA 0x00E04028
ZERO_INIT( rva007B25E0 )
// ?rva007B25F2@Rva007AD295ZeroInits@@SAXXZ @ 0x007B25F2 (18B), static at VA 0x00E0402C
ZERO_INIT( rva007B25F2 )
// ?rva007B2604@Rva007AD295ZeroInits@@SAXXZ @ 0x007B2604 (18B), static at VA 0x00E04030
ZERO_INIT( rva007B2604 )
// ?rva007B3162@Rva007AD295ZeroInits@@SAXXZ @ 0x007B3162 (18B), static at VA 0x00E04480
ZERO_INIT( rva007B3162 )
