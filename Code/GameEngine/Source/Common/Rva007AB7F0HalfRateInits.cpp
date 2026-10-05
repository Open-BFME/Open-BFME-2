// cl: /O1 /DNDEBUG /MD
//
// Static-initializer strip: half the logic frame rate into a TU-local static.
// Retail repeats one 16-byte dynamic initializer 429 times between 0x007AB7F0
// and 0x007B5xxx, each storing g_00DBA4E8 / 2 (the global is 30, the logic
// frames per second other matched rows scale by) into its own static. It is
// the per-translation-unit initializer of a header-level constant computed
// from that global; the owning TUs are unrecovered, and in these copies the
// static is never read anywhere in .text, so each copy keeps an honest address
// name and its static stays TU-local here as it was in its own unit.

extern int g_00DBA4E8;

struct Rva007AB7F0HalfRateInits
{
	static void rva007AB7F0();
	static void rva007ABC0B();
	static void rva007ABC35();
	static void rva007ABC5F();
	static void rva007ABCE7();
	static void rva007ABD11();
	static void rva007ABD3B();
	static void rva007ABDC1();
	static void rva007ABDEB();
	static void rva007ABE15();
	static void rva007ABE3F();
	static void rva007ABE69();
	static void rva007ABE9F();
	static void rva007ABEC9();
	static void rva007ABF41();
	static void rva007ABF6B();
	static void rva007ABFB9();
	static void rva007AC012();
	static void rva007AC052();
	static void rva007AC07C();
	static void rva007AC0D0();
	static void rva007AC112();
	static void rva007AC173();
	static void rva007AC19D();
	static void rva007AC1C7();
	static void rva007AC282();
	static void rva007AC317();
	static void rva007AC341();
	static void rva007AC36B();
	static void rva007AC395();
	static void rva007AC3BF();
	static void rva007AC3E9();
	static void rva007AC413();
	static void rva007AC43D();
	static void rva007AC467();
	static void rva007AC491();
	static void rva007AC4BB();
	static void rva007AC4E5();
	static void rva007AC50F();
	static void rva007AC539();
	static void rva007AC563();
	static void rva007AC58D();
	static void rva007AC5B7();
	static void rva007AC5E1();
	static void rva007AC60B();
	static void rva007AC635();
	static void rva007AC65F();
	static void rva007AC689();
	static void rva007AC6B3();
	static void rva007AC70D();
	static void rva007AC737();
	static void rva007AC777();
	static void rva007AC7A1();
	static void rva007AC7E5();
	static void rva007AC9A0();
	static void rva007ACA9A();
	static void rva007ACADF();
	static void rva007ACB09();
	static void rva007ACB33();
	static void rva007ACB92();
};

#define HALF_RATE_INIT(init) \
	static int s_##init; \
	void Rva007AB7F0HalfRateInits::init() \
	{ \
		s_##init = g_00DBA4E8 / 2; \
	}

// ?rva007AB7F0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AB7F0 (16B), static at VA 0x00DDE030
HALF_RATE_INIT( rva007AB7F0 )
// ?rva007ABC0B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABC0B (16B), static at VA 0x00DE1B1C
HALF_RATE_INIT( rva007ABC0B )
// ?rva007ABC35@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABC35 (16B), static at VA 0x00DE1B24
HALF_RATE_INIT( rva007ABC35 )
// ?rva007ABC5F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABC5F (16B), static at VA 0x00DE1B4C
HALF_RATE_INIT( rva007ABC5F )
// ?rva007ABCE7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABCE7 (16B), static at VA 0x00DE1CD0
HALF_RATE_INIT( rva007ABCE7 )
// ?rva007ABD11@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABD11 (16B), static at VA 0x00DE1CD4
HALF_RATE_INIT( rva007ABD11 )
// ?rva007ABD3B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABD3B (16B), static at VA 0x00DE1CFC
HALF_RATE_INIT( rva007ABD3B )
// ?rva007ABDC1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABDC1 (16B), static at VA 0x00DE1E50
HALF_RATE_INIT( rva007ABDC1 )
// ?rva007ABDEB@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABDEB (16B), static at VA 0x00DE1E84
HALF_RATE_INIT( rva007ABDEB )
// ?rva007ABE15@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABE15 (16B), static at VA 0x00DE1E88
HALF_RATE_INIT( rva007ABE15 )
// ?rva007ABE3F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABE3F (16B), static at VA 0x00DE1E8C
HALF_RATE_INIT( rva007ABE3F )
// ?rva007ABE69@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABE69 (16B), static at VA 0x00DE1E90
HALF_RATE_INIT( rva007ABE69 )
// ?rva007ABE9F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABE9F (16B), static at VA 0x00DE1EB0
HALF_RATE_INIT( rva007ABE9F )
// ?rva007ABEC9@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABEC9 (16B), static at VA 0x00DE1EBC
HALF_RATE_INIT( rva007ABEC9 )
// ?rva007ABF41@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABF41 (16B), static at VA 0x00DE1ED4
HALF_RATE_INIT( rva007ABF41 )
// ?rva007ABF6B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABF6B (16B), static at VA 0x00DE1F88
HALF_RATE_INIT( rva007ABF6B )
// ?rva007ABFB9@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ABFB9 (16B), static at VA 0x00DE1FBC
HALF_RATE_INIT( rva007ABFB9 )
// ?rva007AC012@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC012 (16B), static at VA 0x00DE2004
HALF_RATE_INIT( rva007AC012 )
// ?rva007AC052@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC052 (16B), static at VA 0x00DE2018
HALF_RATE_INIT( rva007AC052 )
// ?rva007AC07C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC07C (16B), static at VA 0x00DE2048
HALF_RATE_INIT( rva007AC07C )
// ?rva007AC0D0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC0D0 (16B), static at VA 0x00DE2080
HALF_RATE_INIT( rva007AC0D0 )
// ?rva007AC112@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC112 (16B), static at VA 0x00DE2094
HALF_RATE_INIT( rva007AC112 )
// ?rva007AC173@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC173 (16B), static at VA 0x00DE487C
HALF_RATE_INIT( rva007AC173 )
// ?rva007AC19D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC19D (16B), static at VA 0x00DE4884
HALF_RATE_INIT( rva007AC19D )
// ?rva007AC1C7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC1C7 (16B), static at VA 0x00DE4888
HALF_RATE_INIT( rva007AC1C7 )
// ?rva007AC282@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC282 (16B), static at VA 0x00DE5E4C
HALF_RATE_INIT( rva007AC282 )
// ?rva007AC317@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC317 (16B), static at VA 0x00DEA300
HALF_RATE_INIT( rva007AC317 )
// ?rva007AC341@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC341 (16B), static at VA 0x00DEA30C
HALF_RATE_INIT( rva007AC341 )
// ?rva007AC36B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC36B (16B), static at VA 0x00DEBB54
HALF_RATE_INIT( rva007AC36B )
// ?rva007AC395@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC395 (16B), static at VA 0x00DEBB68
HALF_RATE_INIT( rva007AC395 )
// ?rva007AC3BF@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC3BF (16B), static at VA 0x00DEBB74
HALF_RATE_INIT( rva007AC3BF )
// ?rva007AC3E9@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC3E9 (16B), static at VA 0x00DEBB80
HALF_RATE_INIT( rva007AC3E9 )
// ?rva007AC413@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC413 (16B), static at VA 0x00DEBB8C
HALF_RATE_INIT( rva007AC413 )
// ?rva007AC43D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC43D (16B), static at VA 0x00DEBB98
HALF_RATE_INIT( rva007AC43D )
// ?rva007AC467@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC467 (16B), static at VA 0x00DEBBA4
HALF_RATE_INIT( rva007AC467 )
// ?rva007AC491@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC491 (16B), static at VA 0x00DEBBB0
HALF_RATE_INIT( rva007AC491 )
// ?rva007AC4BB@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC4BB (16B), static at VA 0x00DEBBBC
HALF_RATE_INIT( rva007AC4BB )
// ?rva007AC4E5@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC4E5 (16B), static at VA 0x00DEBBC8
HALF_RATE_INIT( rva007AC4E5 )
// ?rva007AC50F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC50F (16B), static at VA 0x00DEBBD4
HALF_RATE_INIT( rva007AC50F )
// ?rva007AC539@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC539 (16B), static at VA 0x00DEBBE0
HALF_RATE_INIT( rva007AC539 )
// ?rva007AC563@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC563 (16B), static at VA 0x00DEBBEC
HALF_RATE_INIT( rva007AC563 )
// ?rva007AC58D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC58D (16B), static at VA 0x00DEBC08
HALF_RATE_INIT( rva007AC58D )
// ?rva007AC5B7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC5B7 (16B), static at VA 0x00DEBC14
HALF_RATE_INIT( rva007AC5B7 )
// ?rva007AC5E1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC5E1 (16B), static at VA 0x00DEBC28
HALF_RATE_INIT( rva007AC5E1 )
// ?rva007AC60B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC60B (16B), static at VA 0x00DEBC34
HALF_RATE_INIT( rva007AC60B )
// ?rva007AC635@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC635 (16B), static at VA 0x00DEBC3C
HALF_RATE_INIT( rva007AC635 )
// ?rva007AC65F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC65F (16B), static at VA 0x00DEBC44
HALF_RATE_INIT( rva007AC65F )
// ?rva007AC689@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC689 (16B), static at VA 0x00DEBC48
HALF_RATE_INIT( rva007AC689 )
// ?rva007AC6B3@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC6B3 (16B), static at VA 0x00DEBC4C
HALF_RATE_INIT( rva007AC6B3 )
// ?rva007AC70D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC70D (16B), static at VA 0x00DEBC8C
HALF_RATE_INIT( rva007AC70D )
// ?rva007AC737@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC737 (16B), static at VA 0x00DEBC94
HALF_RATE_INIT( rva007AC737 )
// ?rva007AC777@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC777 (16B), static at VA 0x00DEBC9C
HALF_RATE_INIT( rva007AC777 )
// ?rva007AC7A1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC7A1 (16B), static at VA 0x00DEBCB8
HALF_RATE_INIT( rva007AC7A1 )
// ?rva007AC7E5@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC7E5 (16B), static at VA 0x00DEBCF8
HALF_RATE_INIT( rva007AC7E5 )
// ?rva007AC9A0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AC9A0 (16B), static at VA 0x00DEC1C8
HALF_RATE_INIT( rva007AC9A0 )
// ?rva007ACA9A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ACA9A (16B), static at VA 0x00DEC28C
HALF_RATE_INIT( rva007ACA9A )
// ?rva007ACADF@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ACADF (16B), static at VA 0x00DEC2C8
HALF_RATE_INIT( rva007ACADF )
// ?rva007ACB09@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ACB09 (16B), static at VA 0x00DEC2D0
HALF_RATE_INIT( rva007ACB09 )
// ?rva007ACB33@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ACB33 (16B), static at VA 0x00DEC2EC
HALF_RATE_INIT( rva007ACB33 )
// ?rva007ACB92@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ACB92 (16B), static at VA 0x00DEC3BC
HALF_RATE_INIT( rva007ACB92 )
