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

extern int g_009BA4E8;

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
	static void rva007ACFE5();
	static void rva007AD0CC();
	static void rva007AD1B3();
	static void rva007AD231();
	static void rva007AD285();
	static void rva007AD3A6();
	static void rva007AD453();
	static void rva007AD4BC();
	static void rva007AD4FB();
	static void rva007AD6F3();
	static void rva007AD7B0();
	static void rva007AD929();
	static void rva007AD97D();
	static void rva007ADA3C();
	static void rva007ADAA5();
	static void rva007ADB01();
	static void rva007ADB82();
	static void rva007ADBC1();
	static void rva007ADC48();
	static void rva007ADC8C();
	static void rva007ADCF8();
	static void rva007ADD9D();
	static void rva007ADDF9();
	static void rva007ADE78();
	static void rva007ADECC();
	static void rva007ADF88();
	static void rva007ADFDF();
	static void rva007AE033();
	static void rva007AE087();
	static void rva007AE120();
	static void rva007AE14A();
	static void rva007AE19E();
	static void rva007AE1FC();
	static void rva007AE240();
	static void rva007AE2BE();
	static void rva007AE2F8();
	static void rva007AE33C();
	static void rva007AE366();
	static void rva007AE39C();
	static void rva007AE3E1();
	static void rva007AE40B();
	static void rva007AE435();
	static void rva007AE45F();
	static void rva007AE49E();
	static void rva007AE4DD();
	static void rva007AE51D();
	static void rva007AE595();
	static void rva007AE644();
	static void rva007AE66E();
	static void rva007AE698();
	static void rva007AE774();
	static void rva007AE7DF();
	static void rva007AE838();
	static void rva007AE978();
	static void rva007AE9A2();
	static void rva007AE9F2();
	static void rva007AEA1C();
	static void rva007AEA84();
	static void rva007AEAAE();
	static void rva007AEAF2();
	static void rva007AEB1C();
	static void rva007AEB46();
	static void rva007AEB70();
	static void rva007AEB9A();
	static void rva007AEC1A();
	static void rva007AECC6();
	static void rva007AECF0();
	static void rva007AED1A();
	static void rva007AED61();
	static void rva007AEDA1();
	static void rva007AEDD7();
	static void rva007AEE5B();
	static void rva007AEEAF();
	static void rva007AEED9();
	static void rva007AEF77();
	static void rva007AEFA1();
	static void rva007AEFE5();
	static void rva007AF00F();
	static void rva007AF039();
	static void rva007AF160();
	static void rva007AF18A();
	static void rva007AF1CE();
	static void rva007AF244();
	static void rva007AF288();
	static void rva007AF2B2();
	static void rva007AF324();
	static void rva007AF369();
	static void rva007AF393();
	static void rva007AF44B();
	static void rva007AF74B();
	static void rva007AF7DD();
	static void rva007AF889();
	static void rva007AFCF8();
	static void rva007AFD22();
	static void rva007AFD76();
	static void rva007AFDA0();
	static void rva007AFDCA();
	static void rva007AFDF4();
	static void rva007AFE1E();
	static void rva007AFE5D();
	static void rva007AFE87();
	static void rva007AFEE0();
	static void rva007AFF0A();
	static void rva007B0115();
	static void rva007B013F();
	static void rva007B0241();
	static void rva007B0280();
	static void rva007B03C7();
	static void rva007B03F1();
	static void rva007B041B();
	static void rva007B0489();
	static void rva007B04B3();
	static void rva007B04F7();
	static void rva007B0521();
	static void rva007B054B();
	static void rva007B05A4();
	static void rva007B05CE();
	static void rva007B0615();
	static void rva007B0685();
	static void rva007B06AF();
	static void rva007B06F3();
	static void rva007B071D();
	static void rva007B0747();
	static void rva007B078B();
	static void rva007B0834();
	static void rva007B0878();
	static void rva007B08A2();
	static void rva007B08F6();
	static void rva007B0920();
	static void rva007B094A();
	static void rva007B09A8();
	static void rva007B09EC();
	static void rva007B0A16();
	static void rva007B0A40();
	static void rva007B0B12();
	static void rva007B0B3C();
	static void rva007B0B66();
	static void rva007B0B90();
	static void rva007B0BFF();
	static void rva007B0C53();
	static void rva007B0C7D();
	static void rva007B0CA7();
	static void rva007B0D45();
	static void rva007B0D8C();
	static void rva007B0DB6();
	static void rva007B0DE0();
	static void rva007B0E24();
	static void rva007B0E4E();
	static void rva007B0E78();
	static void rva007B0EA2();
	static void rva007B0ECC();
	static void rva007B0EF6();
	static void rva007B0F20();
	static void rva007B0F4A();
	static void rva007B0F74();
	static void rva007B0FB8();
	static void rva007B0FFC();
	static void rva007B1026();
	static void rva007B1050();
	static void rva007B1094();
	static void rva007B10BE();
	static void rva007B10E8();
	static void rva007B1112();
	static void rva007B1166();
	static void rva007B1212();
	static void rva007B123C();
	static void rva007B1266();
	static void rva007B12AA();
	static void rva007B12D4();
	static void rva007B1318();
	static void rva007B136C();
	static void rva007B1396();
	static void rva007B13C0();
	static void rva007B13EA();
	static void rva007B142E();
	static void rva007B148C();
	static void rva007B14B6();
	static void rva007B14E0();
	static void rva007B150A();
	static void rva007B1534();
	static void rva007B155E();
	static void rva007B15A2();
	static void rva007B15F1();
	static void rva007B1683();
	static void rva007B16AD();
	static void rva007B170B();
	static void rva007B1735();
	static void rva007B175F();
	static void rva007B17BD();
	static void rva007B17E7();
	static void rva007B182B();
	static void rva007B18A3();
	static void rva007B18CD();
	static void rva007B18F7();
	static void rva007B1921();
	static void rva007B1965();
	static void rva007B19A9();
	static void rva007B19ED();
	static void rva007B1A17();
	static void rva007B1A52();
	static void rva007B1A7C();
	static void rva007B1AA6();
	static void rva007B1AD0();
	static void rva007B1AFA();
	static void rva007B1B24();
	static void rva007B1B4E();
	static void rva007B1B92();
	static void rva007B1BBC();
	static void rva007B1BE6();
	static void rva007B1C10();
	static void rva007B1C88();
	static void rva007B1CB2();
	static void rva007B1CF2();
	static void rva007B1D1C();
	static void rva007B1D46();
	static void rva007B1D70();
	static void rva007B1DCE();
	static void rva007B1DF8();
	static void rva007B1E22();
	static void rva007B1E4C();
	static void rva007B1E90();
	static void rva007B1ED4();
	static void rva007B1EFE();
	static void rva007B1F28();
	static void rva007B1F52();
	static void rva007B1F7C();
	static void rva007B1FA6();
	static void rva007B1FD0();
	static void rva007B1FFA();
	static void rva007B2024();
	static void rva007B204E();
	static void rva007B2078();
	static void rva007B20A2();
	static void rva007B20CC();
	static void rva007B20F6();
	static void rva007B2120();
	static void rva007B214A();
	static void rva007B2174();
	static void rva007B219E();
	static void rva007B21C8();
	static void rva007B21F2();
	static void rva007B221C();
	static void rva007B2246();
	static void rva007B2270();
	static void rva007B229A();
	static void rva007B22C4();
	static void rva007B22EE();
	static void rva007B2318();
	static void rva007B2342();
	static void rva007B236C();
	static void rva007B2396();
	static void rva007B23C0();
	static void rva007B23EA();
	static void rva007B2414();
	static void rva007B24C0();
	static void rva007B24EA();
	static void rva007B2514();
	static void rva007B253E();
	static void rva007B2568();
	static void rva007B25AC();
	static void rva007B2630();
	static void rva007B265A();
	static void rva007B26EC();
	static void rva007B274A();
	static void rva007B2774();
	static void rva007B27B8();
	static void rva007B2830();
	static void rva007B285A();
	static void rva007B2906();
	static void rva007B294A();
	static void rva007B2974();
	static void rva007B299E();
	static void rva007B29C8();
	static void rva007B29F2();
	static void rva007B2A1C();
	static void rva007B2A60();
	static void rva007B2AA4();
	static void rva007B2B36();
	static void rva007B2B60();
	static void rva007B2B8A();
	static void rva007B2BB4();
	static void rva007B2BDE();
	static void rva007B2C08();
	static void rva007B2C32();
	static void rva007B2C5C();
	static void rva007B2C86();
	static void rva007B2CB0();
	static void rva007B2CDA();
	static void rva007B2DEE();
	static void rva007B2E18();
	static void rva007B2E42();
	static void rva007B2EA0();
	static void rva007B2ECA();
	static void rva007B2F4E();
	static void rva007B2FE0();
	static void rva007B300A();
	static void rva007B3064();
	static void rva007B308E();
	static void rva007B30C4();
	static void rva007B30EE();
	static void rva007B3231();
	static void rva007B328F();
	static void rva007B32B9();
	static void rva007B32E3();
	static void rva007B3327();
	static void rva007B3351();
	static void rva007B341C();
	static void rva007B3476();
	static void rva007B3544();
	static void rva007B356E();
	static void rva007B3598();
	static void rva007B35C2();
	static void rva007B35EC();
	static void rva007B3664();
	static void rva007B368E();
	static void rva007B36D2();
	static void rva007B3716();
	static void rva007B3740();
	static void rva007B3832();
	static void rva007B385C();
	static void rva007B3886();
	static void rva007B38CA();
	static void rva007B395B();
	static void rva007B39B9();
	static void rva007B39E3();
	static void rva007B3A2E();
	static void rva007B3B26();
	static void rva007B3B7A();
	static void rva007B3BA4();
	static void rva007B3BCE();
	static void rva007B3BF8();
	static void rva007B3C22();
	static void rva007B3E06();
	static void rva007B3E4A();
	static void rva007B3E74();
	static void rva007B3ECA();
	static void rva007B3EF4();
	static void rva007B3F1E();
	static void rva007B3FF2();
	static void rva007B4194();
	static void rva007B41D8();
	static void rva007B42B8();
	static void rva007B433E();
	static void rva007B4383();
	static void rva007B43AD();
	static void rva007B43E5();
	static void rva007B4698();
	static void rva007B46F8();
	static void rva007B4722();
	static void rva007B47BF();
	static void rva007B4922();
	static void rva007B4A30();
	static void rva007B4EF4();
	static void rva007B4F1E();
	static void rva007B4F7C();
	static void rva007B4FF0();
	static void rva007B5030();
	static void rva007B505A();
	static void rva007B5197();
	static void rva007B51DB();
	static void rva007B521B();
	static void rva007B5245();
	static void rva007B526F();
	static void rva007B5333();
	static void rva007B53AA();
};

#define HALF_RATE_INIT(init) \
	static int s_##init; \
	void Rva007AB7F0HalfRateInits::init() \
	{ \
		s_##init = g_009BA4E8 / 2; \
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
// ?rva007ACFE5@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ACFE5 (16B), static at VA 0x00DFDBCC
HALF_RATE_INIT( rva007ACFE5 )
// ?rva007AD0CC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD0CC (16B), static at VA 0x00DFDBFC
HALF_RATE_INIT( rva007AD0CC )
// ?rva007AD1B3@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD1B3 (16B), static at VA 0x00DFDC34
HALF_RATE_INIT( rva007AD1B3 )
// ?rva007AD231@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD231 (16B), static at VA 0x00DFDC40
HALF_RATE_INIT( rva007AD231 )
// ?rva007AD285@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD285 (16B), static at VA 0x00DFDC68
HALF_RATE_INIT( rva007AD285 )
// ?rva007AD3A6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD3A6 (16B), static at VA 0x00DFDCA4
HALF_RATE_INIT( rva007AD3A6 )
// ?rva007AD453@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD453 (16B), static at VA 0x00DFDCC4
HALF_RATE_INIT( rva007AD453 )
// ?rva007AD4BC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD4BC (16B), static at VA 0x00DFDCD0
HALF_RATE_INIT( rva007AD4BC )
// ?rva007AD4FB@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD4FB (16B), static at VA 0x00DFDD08
HALF_RATE_INIT( rva007AD4FB )
// ?rva007AD6F3@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD6F3 (16B), static at VA 0x00DFE148
HALF_RATE_INIT( rva007AD6F3 )
// ?rva007AD7B0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD7B0 (16B), static at VA 0x00DFE170
HALF_RATE_INIT( rva007AD7B0 )
// ?rva007AD929@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD929 (16B), static at VA 0x00DFE1CC
HALF_RATE_INIT( rva007AD929 )
// ?rva007AD97D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AD97D (16B), static at VA 0x00DFE1DC
HALF_RATE_INIT( rva007AD97D )
// ?rva007ADA3C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADA3C (16B), static at VA 0x00DFE330
HALF_RATE_INIT( rva007ADA3C )
// ?rva007ADAA5@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADAA5 (16B), static at VA 0x00DFE350
HALF_RATE_INIT( rva007ADAA5 )
// ?rva007ADB01@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADB01 (16B), static at VA 0x00DFE48C
HALF_RATE_INIT( rva007ADB01 )
// ?rva007ADB82@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADB82 (16B), static at VA 0x00DFE4D0
HALF_RATE_INIT( rva007ADB82 )
// ?rva007ADBC1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADBC1 (16B), static at VA 0x00DFE714
HALF_RATE_INIT( rva007ADBC1 )
// ?rva007ADC48@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADC48 (16B), static at VA 0x00DFE780
HALF_RATE_INIT( rva007ADC48 )
// ?rva007ADC8C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADC8C (16B), static at VA 0x00DFE790
HALF_RATE_INIT( rva007ADC8C )
// ?rva007ADCF8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADCF8 (16B), static at VA 0x00DFE964
HALF_RATE_INIT( rva007ADCF8 )
// ?rva007ADD9D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADD9D (16B), static at VA 0x00DFEA24
HALF_RATE_INIT( rva007ADD9D )
// ?rva007ADDF9@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADDF9 (16B), static at VA 0x00DFEA40
HALF_RATE_INIT( rva007ADDF9 )
// ?rva007ADE78@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADE78 (16B), static at VA 0x00DFEB58
HALF_RATE_INIT( rva007ADE78 )
// ?rva007ADECC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADECC (16B), static at VA 0x00DFEB68
HALF_RATE_INIT( rva007ADECC )
// ?rva007ADF88@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADF88 (16B), static at VA 0x00DFEC58
HALF_RATE_INIT( rva007ADF88 )
// ?rva007ADFDF@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007ADFDF (16B), static at VA 0x00DFECCC
HALF_RATE_INIT( rva007ADFDF )
// ?rva007AE033@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE033 (16B), static at VA 0x00DFECD4
HALF_RATE_INIT( rva007AE033 )
// ?rva007AE087@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE087 (16B), static at VA 0x00DFEDF8
HALF_RATE_INIT( rva007AE087 )
// ?rva007AE120@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE120 (16B), static at VA 0x00DFEEEC
HALF_RATE_INIT( rva007AE120 )
// ?rva007AE14A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE14A (16B), static at VA 0x00DFEEFC
HALF_RATE_INIT( rva007AE14A )
// ?rva007AE19E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE19E (16B), static at VA 0x00DFEF0C
HALF_RATE_INIT( rva007AE19E )
// ?rva007AE1FC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE1FC (16B), static at VA 0x00DFEF14
HALF_RATE_INIT( rva007AE1FC )
// ?rva007AE240@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE240 (16B), static at VA 0x00DFEF20
HALF_RATE_INIT( rva007AE240 )
// ?rva007AE2BE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE2BE (16B), static at VA 0x00DFEFD0
HALF_RATE_INIT( rva007AE2BE )
// ?rva007AE2F8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE2F8 (16B), static at VA 0x00DFEFE4
HALF_RATE_INIT( rva007AE2F8 )
// ?rva007AE33C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE33C (16B), static at VA 0x00DFEFF8
HALF_RATE_INIT( rva007AE33C )
// ?rva007AE366@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE366 (16B), static at VA 0x00DFF008
HALF_RATE_INIT( rva007AE366 )
// ?rva007AE39C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE39C (16B), static at VA 0x00DFF02C
HALF_RATE_INIT( rva007AE39C )
// ?rva007AE3E1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE3E1 (16B), static at VA 0x00DFF06C
HALF_RATE_INIT( rva007AE3E1 )
// ?rva007AE40B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE40B (16B), static at VA 0x00DFF074
HALF_RATE_INIT( rva007AE40B )
// ?rva007AE435@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE435 (16B), static at VA 0x00DFF07C
HALF_RATE_INIT( rva007AE435 )
// ?rva007AE45F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE45F (16B), static at VA 0x00DFF094
HALF_RATE_INIT( rva007AE45F )
// ?rva007AE49E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE49E (16B), static at VA 0x00DFF0B4
HALF_RATE_INIT( rva007AE49E )
// ?rva007AE4DD@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE4DD (16B), static at VA 0x00DFF0C0
HALF_RATE_INIT( rva007AE4DD )
// ?rva007AE51D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE51D (16B), static at VA 0x00DFF0D4
HALF_RATE_INIT( rva007AE51D )
// ?rva007AE595@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE595 (16B), static at VA 0x00DFF130
HALF_RATE_INIT( rva007AE595 )
// ?rva007AE644@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE644 (16B), static at VA 0x00DFF18C
HALF_RATE_INIT( rva007AE644 )
// ?rva007AE66E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE66E (16B), static at VA 0x00DFF194
HALF_RATE_INIT( rva007AE66E )
// ?rva007AE698@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE698 (16B), static at VA 0x00DFF198
HALF_RATE_INIT( rva007AE698 )
// ?rva007AE774@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE774 (16B), static at VA 0x00DFF4AC
HALF_RATE_INIT( rva007AE774 )
// ?rva007AE7DF@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE7DF (16B), static at VA 0x00E0093C
HALF_RATE_INIT( rva007AE7DF )
// ?rva007AE838@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE838 (16B), static at VA 0x00E0094C
HALF_RATE_INIT( rva007AE838 )
// ?rva007AE978@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE978 (16B), static at VA 0x00E01CF8
HALF_RATE_INIT( rva007AE978 )
// ?rva007AE9A2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE9A2 (16B), static at VA 0x00E01D10
HALF_RATE_INIT( rva007AE9A2 )
// ?rva007AE9F2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AE9F2 (16B), static at VA 0x00E01D50
HALF_RATE_INIT( rva007AE9F2 )
// ?rva007AEA1C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEA1C (16B), static at VA 0x00E01D5C
HALF_RATE_INIT( rva007AEA1C )
// ?rva007AEA84@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEA84 (16B), static at VA 0x00E01DB4
HALF_RATE_INIT( rva007AEA84 )
// ?rva007AEAAE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEAAE (16B), static at VA 0x00E01DB8
HALF_RATE_INIT( rva007AEAAE )
// ?rva007AEAF2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEAF2 (16B), static at VA 0x00E01DC4
HALF_RATE_INIT( rva007AEAF2 )
// ?rva007AEB1C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEB1C (16B), static at VA 0x00E01DD0
HALF_RATE_INIT( rva007AEB1C )
// ?rva007AEB46@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEB46 (16B), static at VA 0x00E01DD8
HALF_RATE_INIT( rva007AEB46 )
// ?rva007AEB70@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEB70 (16B), static at VA 0x00E01DE4
HALF_RATE_INIT( rva007AEB70 )
// ?rva007AEB9A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEB9A (16B), static at VA 0x00E01E00
HALF_RATE_INIT( rva007AEB9A )
// ?rva007AEC1A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEC1A (16B), static at VA 0x00E01E24
HALF_RATE_INIT( rva007AEC1A )
// ?rva007AECC6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AECC6 (16B), static at VA 0x00E01E44
HALF_RATE_INIT( rva007AECC6 )
// ?rva007AECF0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AECF0 (16B), static at VA 0x00E01E60
HALF_RATE_INIT( rva007AECF0 )
// ?rva007AED1A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AED1A (16B), static at VA 0x00E01E64
HALF_RATE_INIT( rva007AED1A )
// ?rva007AED61@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AED61 (16B), static at VA 0x00E01E78
HALF_RATE_INIT( rva007AED61 )
// ?rva007AEDA1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEDA1 (16B), static at VA 0x00E01E90
HALF_RATE_INIT( rva007AEDA1 )
// ?rva007AEDD7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEDD7 (16B), static at VA 0x00E01EBC
HALF_RATE_INIT( rva007AEDD7 )
// ?rva007AEE5B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEE5B (16B), static at VA 0x00E01ED4
HALF_RATE_INIT( rva007AEE5B )
// ?rva007AEEAF@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEEAF (16B), static at VA 0x00E01EE0
HALF_RATE_INIT( rva007AEEAF )
// ?rva007AEED9@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEED9 (16B), static at VA 0x00E01F0C
HALF_RATE_INIT( rva007AEED9 )
// ?rva007AEF77@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEF77 (16B), static at VA 0x00E01F28
HALF_RATE_INIT( rva007AEF77 )
// ?rva007AEFA1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEFA1 (16B), static at VA 0x00E02038
HALF_RATE_INIT( rva007AEFA1 )
// ?rva007AEFE5@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AEFE5 (16B), static at VA 0x00E02294
HALF_RATE_INIT( rva007AEFE5 )
// ?rva007AF00F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF00F (16B), static at VA 0x00E02298
HALF_RATE_INIT( rva007AF00F )
// ?rva007AF039@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF039 (16B), static at VA 0x00E022BC
HALF_RATE_INIT( rva007AF039 )
// ?rva007AF160@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF160 (16B), static at VA 0x00E0269C
HALF_RATE_INIT( rva007AF160 )
// ?rva007AF18A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF18A (16B), static at VA 0x00E027AC
HALF_RATE_INIT( rva007AF18A )
// ?rva007AF1CE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF1CE (16B), static at VA 0x00E027BC
HALF_RATE_INIT( rva007AF1CE )
// ?rva007AF244@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF244 (16B), static at VA 0x00E02830
HALF_RATE_INIT( rva007AF244 )
// ?rva007AF288@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF288 (16B), static at VA 0x00E02834
HALF_RATE_INIT( rva007AF288 )
// ?rva007AF2B2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF2B2 (16B), static at VA 0x00E02848
HALF_RATE_INIT( rva007AF2B2 )
// ?rva007AF324@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF324 (16B), static at VA 0x00E028C0
HALF_RATE_INIT( rva007AF324 )
// ?rva007AF369@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF369 (16B), static at VA 0x00E028D8
HALF_RATE_INIT( rva007AF369 )
// ?rva007AF393@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF393 (16B), static at VA 0x00E028DC
HALF_RATE_INIT( rva007AF393 )
// ?rva007AF44B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF44B (16B), static at VA 0x00E02908
HALF_RATE_INIT( rva007AF44B )
// ?rva007AF74B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF74B (16B), static at VA 0x00E02D48
HALF_RATE_INIT( rva007AF74B )
// ?rva007AF7DD@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF7DD (16B), static at VA 0x00E02D60
HALF_RATE_INIT( rva007AF7DD )
// ?rva007AF889@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AF889 (16B), static at VA 0x00E02E08
HALF_RATE_INIT( rva007AF889 )
// ?rva007AFCF8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFCF8 (16B), static at VA 0x00E02EE8
HALF_RATE_INIT( rva007AFCF8 )
// ?rva007AFD22@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFD22 (16B), static at VA 0x00E02EF8
HALF_RATE_INIT( rva007AFD22 )
// ?rva007AFD76@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFD76 (16B), static at VA 0x00E02F38
HALF_RATE_INIT( rva007AFD76 )
// ?rva007AFDA0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFDA0 (16B), static at VA 0x00E02F40
HALF_RATE_INIT( rva007AFDA0 )
// ?rva007AFDCA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFDCA (16B), static at VA 0x00E02F4C
HALF_RATE_INIT( rva007AFDCA )
// ?rva007AFDF4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFDF4 (16B), static at VA 0x00E02F6C
HALF_RATE_INIT( rva007AFDF4 )
// ?rva007AFE1E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFE1E (16B), static at VA 0x00E02F7C
HALF_RATE_INIT( rva007AFE1E )
// ?rva007AFE5D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFE5D (16B), static at VA 0x00E02FA4
HALF_RATE_INIT( rva007AFE5D )
// ?rva007AFE87@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFE87 (16B), static at VA 0x00E02FAC
HALF_RATE_INIT( rva007AFE87 )
// ?rva007AFEE0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFEE0 (16B), static at VA 0x00E02FC4
HALF_RATE_INIT( rva007AFEE0 )
// ?rva007AFF0A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007AFF0A (16B), static at VA 0x00E02FCC
HALF_RATE_INIT( rva007AFF0A )
// ?rva007B0115@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0115 (16B), static at VA 0x00E030DC
HALF_RATE_INIT( rva007B0115 )
// ?rva007B013F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B013F (16B), static at VA 0x00E030EC
HALF_RATE_INIT( rva007B013F )
// ?rva007B0241@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0241 (16B), static at VA 0x00E03148
HALF_RATE_INIT( rva007B0241 )
// ?rva007B0280@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0280 (16B), static at VA 0x00E03164
HALF_RATE_INIT( rva007B0280 )
// ?rva007B03C7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B03C7 (16B), static at VA 0x00E031FC
HALF_RATE_INIT( rva007B03C7 )
// ?rva007B03F1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B03F1 (16B), static at VA 0x00E03200
HALF_RATE_INIT( rva007B03F1 )
// ?rva007B041B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B041B (16B), static at VA 0x00E03208
HALF_RATE_INIT( rva007B041B )
// ?rva007B0489@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0489 (16B), static at VA 0x00E0321C
HALF_RATE_INIT( rva007B0489 )
// ?rva007B04B3@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B04B3 (16B), static at VA 0x00E03224
HALF_RATE_INIT( rva007B04B3 )
// ?rva007B04F7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B04F7 (16B), static at VA 0x00E03228
HALF_RATE_INIT( rva007B04F7 )
// ?rva007B0521@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0521 (16B), static at VA 0x00E03230
HALF_RATE_INIT( rva007B0521 )
// ?rva007B054B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B054B (16B), static at VA 0x00E032C4
HALF_RATE_INIT( rva007B054B )
// ?rva007B05A4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B05A4 (16B), static at VA 0x00E032D4
HALF_RATE_INIT( rva007B05A4 )
// ?rva007B05CE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B05CE (16B), static at VA 0x00E032D8
HALF_RATE_INIT( rva007B05CE )
// ?rva007B0615@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0615 (16B), static at VA 0x00E032E4
HALF_RATE_INIT( rva007B0615 )
// ?rva007B0685@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0685 (16B), static at VA 0x00E03308
HALF_RATE_INIT( rva007B0685 )
// ?rva007B06AF@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B06AF (16B), static at VA 0x00E03310
HALF_RATE_INIT( rva007B06AF )
// ?rva007B06F3@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B06F3 (16B), static at VA 0x00E03344
HALF_RATE_INIT( rva007B06F3 )
// ?rva007B071D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B071D (16B), static at VA 0x00E03358
HALF_RATE_INIT( rva007B071D )
// ?rva007B0747@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0747 (16B), static at VA 0x00E03388
HALF_RATE_INIT( rva007B0747 )
// ?rva007B078B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B078B (16B), static at VA 0x00E033B8
HALF_RATE_INIT( rva007B078B )
// ?rva007B0834@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0834 (16B), static at VA 0x00E033DC
HALF_RATE_INIT( rva007B0834 )
// ?rva007B0878@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0878 (16B), static at VA 0x00E033E8
HALF_RATE_INIT( rva007B0878 )
// ?rva007B08A2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B08A2 (16B), static at VA 0x00E033F4
HALF_RATE_INIT( rva007B08A2 )
// ?rva007B08F6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B08F6 (16B), static at VA 0x00E0341C
HALF_RATE_INIT( rva007B08F6 )
// ?rva007B0920@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0920 (16B), static at VA 0x00E03428
HALF_RATE_INIT( rva007B0920 )
// ?rva007B094A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B094A (16B), static at VA 0x00E03434
HALF_RATE_INIT( rva007B094A )
// ?rva007B09A8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B09A8 (16B), static at VA 0x00E03450
HALF_RATE_INIT( rva007B09A8 )
// ?rva007B09EC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B09EC (16B), static at VA 0x00E03464
HALF_RATE_INIT( rva007B09EC )
// ?rva007B0A16@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0A16 (16B), static at VA 0x00E03470
HALF_RATE_INIT( rva007B0A16 )
// ?rva007B0A40@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0A40 (16B), static at VA 0x00E03484
HALF_RATE_INIT( rva007B0A40 )
// ?rva007B0B12@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0B12 (16B), static at VA 0x00E034BC
HALF_RATE_INIT( rva007B0B12 )
// ?rva007B0B3C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0B3C (16B), static at VA 0x00E034C8
HALF_RATE_INIT( rva007B0B3C )
// ?rva007B0B66@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0B66 (16B), static at VA 0x00E034D4
HALF_RATE_INIT( rva007B0B66 )
// ?rva007B0B90@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0B90 (16B), static at VA 0x00E03598
HALF_RATE_INIT( rva007B0B90 )
// ?rva007B0BFF@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0BFF (16B), static at VA 0x00E035C4
HALF_RATE_INIT( rva007B0BFF )
// ?rva007B0C53@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0C53 (16B), static at VA 0x00E035E4
HALF_RATE_INIT( rva007B0C53 )
// ?rva007B0C7D@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0C7D (16B), static at VA 0x00E035F8
HALF_RATE_INIT( rva007B0C7D )
// ?rva007B0CA7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0CA7 (16B), static at VA 0x00E03604
HALF_RATE_INIT( rva007B0CA7 )
// ?rva007B0D45@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0D45 (16B), static at VA 0x00E03628
HALF_RATE_INIT( rva007B0D45 )
// ?rva007B0D8C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0D8C (16B), static at VA 0x00E03650
HALF_RATE_INIT( rva007B0D8C )
// ?rva007B0DB6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0DB6 (16B), static at VA 0x00E03664
HALF_RATE_INIT( rva007B0DB6 )
// ?rva007B0DE0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0DE0 (16B), static at VA 0x00E03690
HALF_RATE_INIT( rva007B0DE0 )
// ?rva007B0E24@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0E24 (16B), static at VA 0x00E0369C
HALF_RATE_INIT( rva007B0E24 )
// ?rva007B0E4E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0E4E (16B), static at VA 0x00E036A8
HALF_RATE_INIT( rva007B0E4E )
// ?rva007B0E78@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0E78 (16B), static at VA 0x00E036B4
HALF_RATE_INIT( rva007B0E78 )
// ?rva007B0EA2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0EA2 (16B), static at VA 0x00E036F0
HALF_RATE_INIT( rva007B0EA2 )
// ?rva007B0ECC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0ECC (16B), static at VA 0x00E036FC
HALF_RATE_INIT( rva007B0ECC )
// ?rva007B0EF6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0EF6 (16B), static at VA 0x00E03710
HALF_RATE_INIT( rva007B0EF6 )
// ?rva007B0F20@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0F20 (16B), static at VA 0x00E03724
HALF_RATE_INIT( rva007B0F20 )
// ?rva007B0F4A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0F4A (16B), static at VA 0x00E03730
HALF_RATE_INIT( rva007B0F4A )
// ?rva007B0F74@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0F74 (16B), static at VA 0x00E03740
HALF_RATE_INIT( rva007B0F74 )
// ?rva007B0FB8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0FB8 (16B), static at VA 0x00E03758
HALF_RATE_INIT( rva007B0FB8 )
// ?rva007B0FFC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B0FFC (16B), static at VA 0x00E03774
HALF_RATE_INIT( rva007B0FFC )
// ?rva007B1026@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1026 (16B), static at VA 0x00E03780
HALF_RATE_INIT( rva007B1026 )
// ?rva007B1050@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1050 (16B), static at VA 0x00E0378C
HALF_RATE_INIT( rva007B1050 )
// ?rva007B1094@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1094 (16B), static at VA 0x00E037A0
HALF_RATE_INIT( rva007B1094 )
// ?rva007B10BE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B10BE (16B), static at VA 0x00E037AC
HALF_RATE_INIT( rva007B10BE )
// ?rva007B10E8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B10E8 (16B), static at VA 0x00E037B8
HALF_RATE_INIT( rva007B10E8 )
// ?rva007B1112@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1112 (16B), static at VA 0x00E037CC
HALF_RATE_INIT( rva007B1112 )
// ?rva007B1166@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1166 (16B), static at VA 0x00E037F4
HALF_RATE_INIT( rva007B1166 )
// ?rva007B1212@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1212 (16B), static at VA 0x00E03820
HALF_RATE_INIT( rva007B1212 )
// ?rva007B123C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B123C (16B), static at VA 0x00E0382C
HALF_RATE_INIT( rva007B123C )
// ?rva007B1266@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1266 (16B), static at VA 0x00E03848
HALF_RATE_INIT( rva007B1266 )
// ?rva007B12AA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B12AA (16B), static at VA 0x00E0385C
HALF_RATE_INIT( rva007B12AA )
// ?rva007B12D4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B12D4 (16B), static at VA 0x00E03868
HALF_RATE_INIT( rva007B12D4 )
// ?rva007B1318@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1318 (16B), static at VA 0x00E03884
HALF_RATE_INIT( rva007B1318 )
// ?rva007B136C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B136C (16B), static at VA 0x00E0389C
HALF_RATE_INIT( rva007B136C )
// ?rva007B1396@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1396 (16B), static at VA 0x00E038A8
HALF_RATE_INIT( rva007B1396 )
// ?rva007B13C0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B13C0 (16B), static at VA 0x00E038BC
HALF_RATE_INIT( rva007B13C0 )
// ?rva007B13EA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B13EA (16B), static at VA 0x00E038D0
HALF_RATE_INIT( rva007B13EA )
// ?rva007B142E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B142E (16B), static at VA 0x00E038F4
HALF_RATE_INIT( rva007B142E )
// ?rva007B148C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B148C (16B), static at VA 0x00E03928
HALF_RATE_INIT( rva007B148C )
// ?rva007B14B6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B14B6 (16B), static at VA 0x00E0394C
HALF_RATE_INIT( rva007B14B6 )
// ?rva007B14E0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B14E0 (16B), static at VA 0x00E03958
HALF_RATE_INIT( rva007B14E0 )
// ?rva007B150A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B150A (16B), static at VA 0x00E03964
HALF_RATE_INIT( rva007B150A )
// ?rva007B1534@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1534 (16B), static at VA 0x00E03970
HALF_RATE_INIT( rva007B1534 )
// ?rva007B155E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B155E (16B), static at VA 0x00E0397C
HALF_RATE_INIT( rva007B155E )
// ?rva007B15A2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B15A2 (16B), static at VA 0x00E03990
HALF_RATE_INIT( rva007B15A2 )
// ?rva007B15F1@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B15F1 (16B), static at VA 0x00E039A8
HALF_RATE_INIT( rva007B15F1 )
// ?rva007B1683@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1683 (16B), static at VA 0x00E039EC
HALF_RATE_INIT( rva007B1683 )
// ?rva007B16AD@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B16AD (16B), static at VA 0x00E03A10
HALF_RATE_INIT( rva007B16AD )
// ?rva007B170B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B170B (16B), static at VA 0x00E03A34
HALF_RATE_INIT( rva007B170B )
// ?rva007B1735@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1735 (16B), static at VA 0x00E03A40
HALF_RATE_INIT( rva007B1735 )
// ?rva007B175F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B175F (16B), static at VA 0x00E03A4C
HALF_RATE_INIT( rva007B175F )
// ?rva007B17BD@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B17BD (16B), static at VA 0x00E03AC8
HALF_RATE_INIT( rva007B17BD )
// ?rva007B17E7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B17E7 (16B), static at VA 0x00E03AE0
HALF_RATE_INIT( rva007B17E7 )
// ?rva007B182B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B182B (16B), static at VA 0x00E03B04
HALF_RATE_INIT( rva007B182B )
// ?rva007B18A3@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B18A3 (16B), static at VA 0x00E03B38
HALF_RATE_INIT( rva007B18A3 )
// ?rva007B18CD@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B18CD (16B), static at VA 0x00E03B44
HALF_RATE_INIT( rva007B18CD )
// ?rva007B18F7@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B18F7 (16B), static at VA 0x00E03B50
HALF_RATE_INIT( rva007B18F7 )
// ?rva007B1921@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1921 (16B), static at VA 0x00E03B70
HALF_RATE_INIT( rva007B1921 )
// ?rva007B1965@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1965 (16B), static at VA 0x00E03B7C
HALF_RATE_INIT( rva007B1965 )
// ?rva007B19A9@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B19A9 (16B), static at VA 0x00E03B90
HALF_RATE_INIT( rva007B19A9 )
// ?rva007B19ED@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B19ED (16B), static at VA 0x00E03BAC
HALF_RATE_INIT( rva007B19ED )
// ?rva007B1A17@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1A17 (16B), static at VA 0x00E03BB8
HALF_RATE_INIT( rva007B1A17 )
// ?rva007B1A52@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1A52 (16B), static at VA 0x00E03BD0
HALF_RATE_INIT( rva007B1A52 )
// ?rva007B1A7C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1A7C (16B), static at VA 0x00E03BDC
HALF_RATE_INIT( rva007B1A7C )
// ?rva007B1AA6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1AA6 (16B), static at VA 0x00E03BF8
HALF_RATE_INIT( rva007B1AA6 )
// ?rva007B1AD0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1AD0 (16B), static at VA 0x00E03C04
HALF_RATE_INIT( rva007B1AD0 )
// ?rva007B1AFA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1AFA (16B), static at VA 0x00E03C18
HALF_RATE_INIT( rva007B1AFA )
// ?rva007B1B24@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1B24 (16B), static at VA 0x00E03C2C
HALF_RATE_INIT( rva007B1B24 )
// ?rva007B1B4E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1B4E (16B), static at VA 0x00E03C40
HALF_RATE_INIT( rva007B1B4E )
// ?rva007B1B92@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1B92 (16B), static at VA 0x00E03C60
HALF_RATE_INIT( rva007B1B92 )
// ?rva007B1BBC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1BBC (16B), static at VA 0x00E03C6C
HALF_RATE_INIT( rva007B1BBC )
// ?rva007B1BE6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1BE6 (16B), static at VA 0x00E03C78
HALF_RATE_INIT( rva007B1BE6 )
// ?rva007B1C10@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1C10 (16B), static at VA 0x00E03C8C
HALF_RATE_INIT( rva007B1C10 )
// ?rva007B1C88@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1C88 (16B), static at VA 0x00E03CAC
HALF_RATE_INIT( rva007B1C88 )
// ?rva007B1CB2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1CB2 (16B), static at VA 0x00E03CD4
HALF_RATE_INIT( rva007B1CB2 )
// ?rva007B1CF2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1CF2 (16B), static at VA 0x00E03D04
HALF_RATE_INIT( rva007B1CF2 )
// ?rva007B1D1C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1D1C (16B), static at VA 0x00E03D18
HALF_RATE_INIT( rva007B1D1C )
// ?rva007B1D46@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1D46 (16B), static at VA 0x00E03D24
HALF_RATE_INIT( rva007B1D46 )
// ?rva007B1D70@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1D70 (16B), static at VA 0x00E03D38
HALF_RATE_INIT( rva007B1D70 )
// ?rva007B1DCE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1DCE (16B), static at VA 0x00E03D64
HALF_RATE_INIT( rva007B1DCE )
// ?rva007B1DF8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1DF8 (16B), static at VA 0x00E03D70
HALF_RATE_INIT( rva007B1DF8 )
// ?rva007B1E22@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1E22 (16B), static at VA 0x00E03D7C
HALF_RATE_INIT( rva007B1E22 )
// ?rva007B1E4C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1E4C (16B), static at VA 0x00E03D94
HALF_RATE_INIT( rva007B1E4C )
// ?rva007B1E90@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1E90 (16B), static at VA 0x00E03DA8
HALF_RATE_INIT( rva007B1E90 )
// ?rva007B1ED4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1ED4 (16B), static at VA 0x00E03DBC
HALF_RATE_INIT( rva007B1ED4 )
// ?rva007B1EFE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1EFE (16B), static at VA 0x00E03DC8
HALF_RATE_INIT( rva007B1EFE )
// ?rva007B1F28@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1F28 (16B), static at VA 0x00E03DD4
HALF_RATE_INIT( rva007B1F28 )
// ?rva007B1F52@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1F52 (16B), static at VA 0x00E03DE0
HALF_RATE_INIT( rva007B1F52 )
// ?rva007B1F7C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1F7C (16B), static at VA 0x00E03DEC
HALF_RATE_INIT( rva007B1F7C )
// ?rva007B1FA6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1FA6 (16B), static at VA 0x00E03DF8
HALF_RATE_INIT( rva007B1FA6 )
// ?rva007B1FD0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1FD0 (16B), static at VA 0x00E03E14
HALF_RATE_INIT( rva007B1FD0 )
// ?rva007B1FFA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B1FFA (16B), static at VA 0x00E03E20
HALF_RATE_INIT( rva007B1FFA )
// ?rva007B2024@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2024 (16B), static at VA 0x00E03E3C
HALF_RATE_INIT( rva007B2024 )
// ?rva007B204E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B204E (16B), static at VA 0x00E03E48
HALF_RATE_INIT( rva007B204E )
// ?rva007B2078@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2078 (16B), static at VA 0x00E03E54
HALF_RATE_INIT( rva007B2078 )
// ?rva007B20A2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B20A2 (16B), static at VA 0x00E03E60
HALF_RATE_INIT( rva007B20A2 )
// ?rva007B20CC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B20CC (16B), static at VA 0x00E03E6C
HALF_RATE_INIT( rva007B20CC )
// ?rva007B20F6@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B20F6 (16B), static at VA 0x00E03E78
HALF_RATE_INIT( rva007B20F6 )
// ?rva007B2120@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2120 (16B), static at VA 0x00E03E84
HALF_RATE_INIT( rva007B2120 )
// ?rva007B214A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B214A (16B), static at VA 0x00E03E90
HALF_RATE_INIT( rva007B214A )
// ?rva007B2174@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2174 (16B), static at VA 0x00E03E9C
HALF_RATE_INIT( rva007B2174 )
// ?rva007B219E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B219E (16B), static at VA 0x00E03EA8
HALF_RATE_INIT( rva007B219E )
// ?rva007B21C8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B21C8 (16B), static at VA 0x00E03EB4
HALF_RATE_INIT( rva007B21C8 )
// ?rva007B21F2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B21F2 (16B), static at VA 0x00E03EC0
HALF_RATE_INIT( rva007B21F2 )
// ?rva007B221C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B221C (16B), static at VA 0x00E03ECC
HALF_RATE_INIT( rva007B221C )
// ?rva007B2246@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2246 (16B), static at VA 0x00E03ED8
HALF_RATE_INIT( rva007B2246 )
// ?rva007B2270@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2270 (16B), static at VA 0x00E03EEC
HALF_RATE_INIT( rva007B2270 )
// ?rva007B229A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B229A (16B), static at VA 0x00E03EF8
HALF_RATE_INIT( rva007B229A )
// ?rva007B22C4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B22C4 (16B), static at VA 0x00E03F04
HALF_RATE_INIT( rva007B22C4 )
// ?rva007B22EE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B22EE (16B), static at VA 0x00E03F10
HALF_RATE_INIT( rva007B22EE )
// ?rva007B2318@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2318 (16B), static at VA 0x00E03F1C
HALF_RATE_INIT( rva007B2318 )
// ?rva007B2342@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2342 (16B), static at VA 0x00E03F28
HALF_RATE_INIT( rva007B2342 )
// ?rva007B236C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B236C (16B), static at VA 0x00E03F34
HALF_RATE_INIT( rva007B236C )
// ?rva007B2396@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2396 (16B), static at VA 0x00E03F40
HALF_RATE_INIT( rva007B2396 )
// ?rva007B23C0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B23C0 (16B), static at VA 0x00E03F4C
HALF_RATE_INIT( rva007B23C0 )
// ?rva007B23EA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B23EA (16B), static at VA 0x00E03F58
HALF_RATE_INIT( rva007B23EA )
// ?rva007B2414@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2414 (16B), static at VA 0x00E03F64
HALF_RATE_INIT( rva007B2414 )
// ?rva007B24C0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B24C0 (16B), static at VA 0x00E03FC0
HALF_RATE_INIT( rva007B24C0 )
// ?rva007B24EA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B24EA (16B), static at VA 0x00E03FD4
HALF_RATE_INIT( rva007B24EA )
// ?rva007B2514@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2514 (16B), static at VA 0x00E03FE0
HALF_RATE_INIT( rva007B2514 )
// ?rva007B253E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B253E (16B), static at VA 0x00E03FEC
HALF_RATE_INIT( rva007B253E )
// ?rva007B2568@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2568 (16B), static at VA 0x00E03FF8
HALF_RATE_INIT( rva007B2568 )
// ?rva007B25AC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B25AC (16B), static at VA 0x00E0401C
HALF_RATE_INIT( rva007B25AC )
// ?rva007B2630@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2630 (16B), static at VA 0x00E0403C
HALF_RATE_INIT( rva007B2630 )
// ?rva007B265A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B265A (16B), static at VA 0x00E04048
HALF_RATE_INIT( rva007B265A )
// ?rva007B26EC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B26EC (16B), static at VA 0x00E0406C
HALF_RATE_INIT( rva007B26EC )
// ?rva007B274A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B274A (16B), static at VA 0x00E04088
HALF_RATE_INIT( rva007B274A )
// ?rva007B2774@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2774 (16B), static at VA 0x00E04120
HALF_RATE_INIT( rva007B2774 )
// ?rva007B27B8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B27B8 (16B), static at VA 0x00E04144
HALF_RATE_INIT( rva007B27B8 )
// ?rva007B2830@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2830 (16B), static at VA 0x00E04178
HALF_RATE_INIT( rva007B2830 )
// ?rva007B285A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B285A (16B), static at VA 0x00E04194
HALF_RATE_INIT( rva007B285A )
// ?rva007B2906@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2906 (16B), static at VA 0x00E041D0
HALF_RATE_INIT( rva007B2906 )
// ?rva007B294A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B294A (16B), static at VA 0x00E04240
HALF_RATE_INIT( rva007B294A )
// ?rva007B2974@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2974 (16B), static at VA 0x00E0424C
HALF_RATE_INIT( rva007B2974 )
// ?rva007B299E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B299E (16B), static at VA 0x00E04258
HALF_RATE_INIT( rva007B299E )
// ?rva007B29C8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B29C8 (16B), static at VA 0x00E04264
HALF_RATE_INIT( rva007B29C8 )
// ?rva007B29F2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B29F2 (16B), static at VA 0x00E04270
HALF_RATE_INIT( rva007B29F2 )
// ?rva007B2A1C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2A1C (16B), static at VA 0x00E04294
HALF_RATE_INIT( rva007B2A1C )
// ?rva007B2A60@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2A60 (16B), static at VA 0x00E042B8
HALF_RATE_INIT( rva007B2A60 )
// ?rva007B2AA4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2AA4 (16B), static at VA 0x00E042CC
HALF_RATE_INIT( rva007B2AA4 )
// ?rva007B2B36@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2B36 (16B), static at VA 0x00E04308
HALF_RATE_INIT( rva007B2B36 )
// ?rva007B2B60@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2B60 (16B), static at VA 0x00E04324
HALF_RATE_INIT( rva007B2B60 )
// ?rva007B2B8A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2B8A (16B), static at VA 0x00E04330
HALF_RATE_INIT( rva007B2B8A )
// ?rva007B2BB4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2BB4 (16B), static at VA 0x00E0433C
HALF_RATE_INIT( rva007B2BB4 )
// ?rva007B2BDE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2BDE (16B), static at VA 0x00E04348
HALF_RATE_INIT( rva007B2BDE )
// ?rva007B2C08@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2C08 (16B), static at VA 0x00E04354
HALF_RATE_INIT( rva007B2C08 )
// ?rva007B2C32@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2C32 (16B), static at VA 0x00E04360
HALF_RATE_INIT( rva007B2C32 )
// ?rva007B2C5C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2C5C (16B), static at VA 0x00E04364
HALF_RATE_INIT( rva007B2C5C )
// ?rva007B2C86@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2C86 (16B), static at VA 0x00E04368
HALF_RATE_INIT( rva007B2C86 )
// ?rva007B2CB0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2CB0 (16B), static at VA 0x00E04374
HALF_RATE_INIT( rva007B2CB0 )
// ?rva007B2CDA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2CDA (16B), static at VA 0x00E04380
HALF_RATE_INIT( rva007B2CDA )
// ?rva007B2DEE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2DEE (16B), static at VA 0x00E043E4
HALF_RATE_INIT( rva007B2DEE )
// ?rva007B2E18@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2E18 (16B), static at VA 0x00E043E8
HALF_RATE_INIT( rva007B2E18 )
// ?rva007B2E42@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2E42 (16B), static at VA 0x00E043F0
HALF_RATE_INIT( rva007B2E42 )
// ?rva007B2EA0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2EA0 (16B), static at VA 0x00E04400
HALF_RATE_INIT( rva007B2EA0 )
// ?rva007B2ECA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2ECA (16B), static at VA 0x00E04404
HALF_RATE_INIT( rva007B2ECA )
// ?rva007B2F4E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2F4E (16B), static at VA 0x00E04408
HALF_RATE_INIT( rva007B2F4E )
// ?rva007B2FE0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B2FE0 (16B), static at VA 0x00E0441C
HALF_RATE_INIT( rva007B2FE0 )
// ?rva007B300A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B300A (16B), static at VA 0x00E04420
HALF_RATE_INIT( rva007B300A )
// ?rva007B3064@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3064 (16B), static at VA 0x00E04468
HALF_RATE_INIT( rva007B3064 )
// ?rva007B308E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B308E (16B), static at VA 0x00E0446C
HALF_RATE_INIT( rva007B308E )
// ?rva007B30C4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B30C4 (16B), static at VA 0x00E04470
HALF_RATE_INIT( rva007B30C4 )
// ?rva007B30EE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B30EE (16B), static at VA 0x00E04474
HALF_RATE_INIT( rva007B30EE )
// ?rva007B3231@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3231 (16B), static at VA 0x00E044A8
HALF_RATE_INIT( rva007B3231 )
// ?rva007B328F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B328F (16B), static at VA 0x00E044B4
HALF_RATE_INIT( rva007B328F )
// ?rva007B32B9@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B32B9 (16B), static at VA 0x00E044B8
HALF_RATE_INIT( rva007B32B9 )
// ?rva007B32E3@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B32E3 (16B), static at VA 0x00E044D4
HALF_RATE_INIT( rva007B32E3 )
// ?rva007B3327@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3327 (16B), static at VA 0x00E044D8
HALF_RATE_INIT( rva007B3327 )
// ?rva007B3351@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3351 (16B), static at VA 0x00E044DC
HALF_RATE_INIT( rva007B3351 )
// ?rva007B341C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B341C (16B), static at VA 0x00E04504
HALF_RATE_INIT( rva007B341C )
// ?rva007B3476@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3476 (16B), static at VA 0x00E04540
HALF_RATE_INIT( rva007B3476 )
// ?rva007B3544@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3544 (16B), static at VA 0x00E04558
HALF_RATE_INIT( rva007B3544 )
// ?rva007B356E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B356E (16B), static at VA 0x00E0455C
HALF_RATE_INIT( rva007B356E )
// ?rva007B3598@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3598 (16B), static at VA 0x00E04560
HALF_RATE_INIT( rva007B3598 )
// ?rva007B35C2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B35C2 (16B), static at VA 0x00E04570
HALF_RATE_INIT( rva007B35C2 )
// ?rva007B35EC@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B35EC (16B), static at VA 0x00E0457C
HALF_RATE_INIT( rva007B35EC )
// ?rva007B3664@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3664 (16B), static at VA 0x00E045A0
HALF_RATE_INIT( rva007B3664 )
// ?rva007B368E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B368E (16B), static at VA 0x00E045AC
HALF_RATE_INIT( rva007B368E )
// ?rva007B36D2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B36D2 (16B), static at VA 0x00E045B0
HALF_RATE_INIT( rva007B36D2 )
// ?rva007B3716@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3716 (16B), static at VA 0x00E045B4
HALF_RATE_INIT( rva007B3716 )
// ?rva007B3740@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3740 (16B), static at VA 0x00E04600
HALF_RATE_INIT( rva007B3740 )
// ?rva007B3832@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3832 (16B), static at VA 0x00E048D8
HALF_RATE_INIT( rva007B3832 )
// ?rva007B385C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B385C (16B), static at VA 0x00E048E4
HALF_RATE_INIT( rva007B385C )
// ?rva007B3886@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3886 (16B), static at VA 0x00E0490C
HALF_RATE_INIT( rva007B3886 )
// ?rva007B38CA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B38CA (16B), static at VA 0x00E04918
HALF_RATE_INIT( rva007B38CA )
// ?rva007B395B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B395B (16B), static at VA 0x00E0496C
HALF_RATE_INIT( rva007B395B )
// ?rva007B39B9@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B39B9 (16B), static at VA 0x00E049AC
HALF_RATE_INIT( rva007B39B9 )
// ?rva007B39E3@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B39E3 (16B), static at VA 0x00E049B0
HALF_RATE_INIT( rva007B39E3 )
// ?rva007B3A2E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3A2E (16B), static at VA 0x00E049F8
HALF_RATE_INIT( rva007B3A2E )
// ?rva007B3B26@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3B26 (16B), static at VA 0x00E05E18
HALF_RATE_INIT( rva007B3B26 )
// ?rva007B3B7A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3B7A (16B), static at VA 0x00E05F44
HALF_RATE_INIT( rva007B3B7A )
// ?rva007B3BA4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3BA4 (16B), static at VA 0x00E05F5C
HALF_RATE_INIT( rva007B3BA4 )
// ?rva007B3BCE@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3BCE (16B), static at VA 0x00E05F68
HALF_RATE_INIT( rva007B3BCE )
// ?rva007B3BF8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3BF8 (16B), static at VA 0x00E05F6C
HALF_RATE_INIT( rva007B3BF8 )
// ?rva007B3C22@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3C22 (16B), static at VA 0x00E05F70
HALF_RATE_INIT( rva007B3C22 )
// ?rva007B3E06@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3E06 (16B), static at VA 0x00E0608C
HALF_RATE_INIT( rva007B3E06 )
// ?rva007B3E4A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3E4A (16B), static at VA 0x00E06090
HALF_RATE_INIT( rva007B3E4A )
// ?rva007B3E74@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3E74 (16B), static at VA 0x00E06094
HALF_RATE_INIT( rva007B3E74 )
// ?rva007B3ECA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3ECA (16B), static at VA 0x00E062AC
HALF_RATE_INIT( rva007B3ECA )
// ?rva007B3EF4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3EF4 (16B), static at VA 0x00E062B0
HALF_RATE_INIT( rva007B3EF4 )
// ?rva007B3F1E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3F1E (16B), static at VA 0x00E062E8
HALF_RATE_INIT( rva007B3F1E )
// ?rva007B3FF2@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B3FF2 (16B), static at VA 0x00E062F8
HALF_RATE_INIT( rva007B3FF2 )
// ?rva007B4194@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4194 (16B), static at VA 0x00E0639C
HALF_RATE_INIT( rva007B4194 )
// ?rva007B41D8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B41D8 (16B), static at VA 0x00E063A0
HALF_RATE_INIT( rva007B41D8 )
// ?rva007B42B8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B42B8 (16B), static at VA 0x00E063B4
HALF_RATE_INIT( rva007B42B8 )
// ?rva007B433E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B433E (16B), static at VA 0x00E063D0
HALF_RATE_INIT( rva007B433E )
// ?rva007B4383@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4383 (16B), static at VA 0x00E063D8
HALF_RATE_INIT( rva007B4383 )
// ?rva007B43AD@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B43AD (16B), static at VA 0x00E063DC
HALF_RATE_INIT( rva007B43AD )
// ?rva007B43E5@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B43E5 (16B), static at VA 0x00E063E4
HALF_RATE_INIT( rva007B43E5 )
// ?rva007B4698@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4698 (16B), static at VA 0x00E06440
HALF_RATE_INIT( rva007B4698 )
// ?rva007B46F8@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B46F8 (16B), static at VA 0x00E06454
HALF_RATE_INIT( rva007B46F8 )
// ?rva007B4722@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4722 (16B), static at VA 0x00E06470
HALF_RATE_INIT( rva007B4722 )
// ?rva007B47BF@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B47BF (16B), static at VA 0x00E065A8
HALF_RATE_INIT( rva007B47BF )
// ?rva007B4922@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4922 (16B), static at VA 0x00E065E0
HALF_RATE_INIT( rva007B4922 )
// ?rva007B4A30@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4A30 (16B), static at VA 0x00E06644
HALF_RATE_INIT( rva007B4A30 )
// ?rva007B4EF4@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4EF4 (16B), static at VA 0x00E0667C
HALF_RATE_INIT( rva007B4EF4 )
// ?rva007B4F1E@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4F1E (16B), static at VA 0x00E06680
HALF_RATE_INIT( rva007B4F1E )
// ?rva007B4F7C@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4F7C (16B), static at VA 0x00E06684
HALF_RATE_INIT( rva007B4F7C )
// ?rva007B4FF0@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B4FF0 (16B), static at VA 0x00E0670C
HALF_RATE_INIT( rva007B4FF0 )
// ?rva007B5030@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B5030 (16B), static at VA 0x00E0671C
HALF_RATE_INIT( rva007B5030 )
// ?rva007B505A@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B505A (16B), static at VA 0x00E06720
HALF_RATE_INIT( rva007B505A )
// ?rva007B5197@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B5197 (16B), static at VA 0x00E06784
HALF_RATE_INIT( rva007B5197 )
// ?rva007B51DB@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B51DB (16B), static at VA 0x00E06850
HALF_RATE_INIT( rva007B51DB )
// ?rva007B521B@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B521B (16B), static at VA 0x00E068D0
HALF_RATE_INIT( rva007B521B )
// ?rva007B5245@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B5245 (16B), static at VA 0x00E068E4
HALF_RATE_INIT( rva007B5245 )
// ?rva007B526F@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B526F (16B), static at VA 0x00E068E8
HALF_RATE_INIT( rva007B526F )
// ?rva007B5333@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B5333 (16B), static at VA 0x00E06914
HALF_RATE_INIT( rva007B5333 )
// ?rva007B53AA@Rva007AB7F0HalfRateInits@@SAXXZ @ 0x007B53AA (16B), static at VA 0x00E0693C
HALF_RATE_INIT( rva007B53AA )
