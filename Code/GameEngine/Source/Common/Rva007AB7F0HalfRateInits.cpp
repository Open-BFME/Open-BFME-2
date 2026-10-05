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
