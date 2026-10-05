// cl: /O1 /DNDEBUG /MD
//
// Static-initializer strip for the behavior freelist pool at VA 0x00DA60E8.
// Retail repeats one 26-byte dynamic initializer 716 times between
// 0x007AB800 and 0x007B5xxx: grow(0, -1) on the pool (a no-op that returns
// false; the native body exits early on size -1), then atexit() of a
// per-copy cleanup thunk in the 0x007B68xx..0x007B9xxx atexit strip. Each
// copy is the per-translation-unit initializer the compiler emits for a
// header-level pool object; the owning TUs are not recovered, so each copy
// keeps an honest address name. Every cleanup is already rowed in
// Rva007B6880Thunks.cpp as ?rva<addr>@@YAXXZ (ecx=pool, tail-jump to the
// pool clear 0x001EAF7B), and the pool itself is the one the matched
// Rva0029FB3BMember::init pops from.

extern "C" int __cdecl atexit(void (__cdecl *)(void));

struct Rva007AB800PoolInits;

class FreelistPool
{
	friend struct Rva007AB800PoolInits;

private:
	bool grow( int arena, int size );
};

extern FreelistPool g_freelistPool;

void __cdecl rva007B6850();
void __cdecl rva007B6AAA();
void __cdecl rva007B6AB4();
void __cdecl rva007B6ABE();
void __cdecl rva007B6AF1();
void __cdecl rva007B6AFB();
void __cdecl rva007B6B0F();
void __cdecl rva007B6B2D();
void __cdecl rva007B6B4B();
void __cdecl rva007B6B55();
void __cdecl rva007B6B5F();
void __cdecl rva007B6B69();
void __cdecl rva007B6B7D();
void __cdecl rva007B6B87();
void __cdecl rva007B6B9B();
void __cdecl rva007B6BA5();
void __cdecl rva007B6BAF();
void __cdecl rva007B6BCD();
void __cdecl rva007B6BD7();
void __cdecl rva007B6BEB();
void __cdecl rva007B6BFF();
void __cdecl rva007B6C09();
void __cdecl rva007B6C16();
void __cdecl rva007B6C20();
void __cdecl rva007B6C34();
void __cdecl rva007B6C48();
void __cdecl rva007B6C52();
void __cdecl rva007B6C5C();
void __cdecl rva007B6CA5();
void __cdecl rva007B6CB9();
void __cdecl rva007B6CC3();
void __cdecl rva007B6CCD();
void __cdecl rva007B6CD7();
void __cdecl rva007B6CEB();
void __cdecl rva007B6CF5();
void __cdecl rva007B6D13();
void __cdecl rva007B6D31();
void __cdecl rva007B6D3B();
void __cdecl rva007B6D45();
void __cdecl rva007B6D4F();
void __cdecl rva007B6D59();
void __cdecl rva007B6D63();
void __cdecl rva007B6D6D();
void __cdecl rva007B6D77();
void __cdecl rva007B6D81();
void __cdecl rva007B6D8B();
void __cdecl rva007B6D95();
void __cdecl rva007B6D9F();
void __cdecl rva007B6DAA();
void __cdecl rva007B6DB4();
void __cdecl rva007B6DBE();
void __cdecl rva007B6DC8();
void __cdecl rva007B6DD2();
void __cdecl rva007B6DDC();
void __cdecl rva007B6DE6();
void __cdecl rva007B6DF0();
void __cdecl rva007B6E04();
void __cdecl rva007B6E0E();
void __cdecl rva007B6E22();
void __cdecl rva007B6E2C();
void __cdecl rva007B6E40();
void __cdecl rva007B6E4A();
void __cdecl rva007B6E68();
void __cdecl rva007B6E86();
void __cdecl rva007B6E9A();
void __cdecl rva007B6EA4();
void __cdecl rva007B6EB8();
void __cdecl rva007B6ECC();
void __cdecl rva007B6EE0();
void __cdecl rva007B6EFE();
void __cdecl rva007B6F1C();
void __cdecl rva007B6F28();
void __cdecl rva007B6F32();
void __cdecl rva007B6F3E();
void __cdecl rva007B6F48();
void __cdecl rva007B6F52();
void __cdecl rva007B6F66();
void __cdecl rva007B6F70();
void __cdecl rva007B6F7A();
void __cdecl rva007B6F84();
void __cdecl rva007B6FA2();
void __cdecl rva007B6FAC();
void __cdecl rva007B751A();
void __cdecl rva007B7524();
void __cdecl rva007B752E();
void __cdecl rva007B7538();
void __cdecl rva007B7542();
void __cdecl rva007B754C();
void __cdecl rva007B7560();
void __cdecl rva007B756A();
void __cdecl rva007B7574();
void __cdecl rva007B757E();
void __cdecl rva007B7592();
void __cdecl rva007B75B0();
void __cdecl rva007B75BA();
void __cdecl rva007B75CE();
void __cdecl rva007B75D8();
void __cdecl rva007B75EC();
void __cdecl rva007B7600();
void __cdecl rva007B7614();
void __cdecl rva007B761E();
void __cdecl rva007B7628();
void __cdecl rva007B7646();
void __cdecl rva007B76D2();
void __cdecl rva007B76F0();
void __cdecl rva007B7722();
void __cdecl rva007B772C();
void __cdecl rva007B774A();
void __cdecl rva007B7754();
void __cdecl rva007B7772();
void __cdecl rva007B7790();
void __cdecl rva007B779A();
void __cdecl rva007B77A4();
void __cdecl rva007B77AE();
void __cdecl rva007B77C3();
void __cdecl rva007B77CE();
void __cdecl rva007B77E2();
void __cdecl rva007B77FC();
void __cdecl rva007B7806();
void __cdecl rva007B7838();
void __cdecl rva007B7888();
void __cdecl rva007B78B0();
void __cdecl rva007B78CE();
void __cdecl rva007B78D8();
void __cdecl rva007B78E2();
void __cdecl rva007B78F6();
void __cdecl rva007B790A();
void __cdecl rva007B7914();
void __cdecl rva007B791E();
void __cdecl rva007B7928();
void __cdecl rva007B7932();
void __cdecl rva007B793C();
void __cdecl rva007B7946();
void __cdecl rva007B7950();
void __cdecl rva007B795A();
void __cdecl rva007B7964();
void __cdecl rva007B79C9();
void __cdecl rva007B79D3();
void __cdecl rva007B79DD();
void __cdecl rva007B79E7();
void __cdecl rva007B79F1();
void __cdecl rva007B7A0F();
void __cdecl rva007B7A23();
void __cdecl rva007B7A2D();
void __cdecl rva007B7A4B();
void __cdecl rva007B7A73();
void __cdecl rva007B7AAF();
void __cdecl rva007B7AB9();
void __cdecl rva007B7AC3();
void __cdecl rva007B7AEB();
void __cdecl rva007B7B1E();
void __cdecl rva007B7B32();
void __cdecl rva007B7B3C();
void __cdecl rva007B7B46();
void __cdecl rva007B7B78();
void __cdecl rva007B7B96();
void __cdecl rva007B7BA0();
void __cdecl rva007B7BAA();
void __cdecl rva007B7BB4();
void __cdecl rva007B7BD2();
void __cdecl rva007B7BDC();
void __cdecl rva007B7BE6();
void __cdecl rva007B7BF0();
void __cdecl rva007B7BFA();
void __cdecl rva007B7C0E();
void __cdecl rva007B7C18();
void __cdecl rva007B7C22();
void __cdecl rva007B7C2C();
void __cdecl rva007B7C36();
void __cdecl rva007B7C4A();
void __cdecl rva007B7C54();
void __cdecl rva007B7C5E();
void __cdecl rva007B7C68();
void __cdecl rva007B7C91();
void __cdecl rva007B7C9B();
void __cdecl rva007B7CA5();
void __cdecl rva007B7CB9();
void __cdecl rva007B7CCD();
void __cdecl rva007B7CE1();
void __cdecl rva007B7CEB();
void __cdecl rva007B7CFF();
void __cdecl rva007B7D09();
void __cdecl rva007B7D13();
void __cdecl rva007B7D1D();
void __cdecl rva007B7D4F();
void __cdecl rva007B7D63();
void __cdecl rva007B7D6D();
void __cdecl rva007B7D8B();
void __cdecl rva007B7D9F();
void __cdecl rva007B7DA9();
void __cdecl rva007B7DBD();
void __cdecl rva007B7DE5();
void __cdecl rva007B7DEF();
void __cdecl rva007B7DF9();
void __cdecl rva007B7E03();
void __cdecl rva007B7E17();
void __cdecl rva007B7E2B();
void __cdecl rva007B7E35();
void __cdecl rva007B7E53();
void __cdecl rva007B7E5D();
void __cdecl rva007B7E67();
void __cdecl rva007B7E71();
void __cdecl rva007B7E7B();
void __cdecl rva007B7E85();
void __cdecl rva007B806F();
void __cdecl rva007B8079();
void __cdecl rva007B8083();
void __cdecl rva007B808D();
void __cdecl rva007B8097();
void __cdecl rva007B80AB();
void __cdecl rva007B80D3();
void __cdecl rva007B80DD();
void __cdecl rva007B80E7();
void __cdecl rva007B815F();
void __cdecl rva007B816B();
void __cdecl rva007B819D();
void __cdecl rva007B81A7();
void __cdecl rva007B81B1();
void __cdecl rva007B81BB();
void __cdecl rva007B81C5();

struct Rva007AB800PoolInits
{
	static void rva007AB800();
	static void rva007ABC1B();
	static void rva007ABC45();
	static void rva007ABC7F();
	static void rva007ABCF7();
	static void rva007ABD21();
	static void rva007ABDA7();
	static void rva007ABDD1();
	static void rva007ABDFB();
	static void rva007ABE25();
	static void rva007ABE4F();
	static void rva007ABE79();
	static void rva007ABEAF();
	static void rva007ABED9();
	static void rva007ABF0D();
	static void rva007ABF27();
	static void rva007ABF51();
	static void rva007ABF9F();
	static void rva007ABFC9();
	static void rva007ABFF8();
	static void rva007AC038();
	static void rva007AC062();
	static void rva007AC0B6();
	static void rva007AC0E0();
	static void rva007AC122();
	static void rva007AC183();
	static void rva007AC1AD();
	static void rva007AC1D7();
	static void rva007AC268();
	static void rva007AC292();
	static void rva007AC2AC();
	static void rva007AC2C6();
	static void rva007AC2E0();
	static void rva007AC327();
	static void rva007AC351();
	static void rva007AC37B();
	static void rva007AC3A5();
	static void rva007AC3CF();
	static void rva007AC3F9();
	static void rva007AC423();
	static void rva007AC44D();
	static void rva007AC477();
	static void rva007AC4A1();
	static void rva007AC4CB();
	static void rva007AC4F5();
	static void rva007AC51F();
	static void rva007AC549();
	static void rva007AC573();
	static void rva007AC59D();
	static void rva007AC5C7();
	static void rva007AC5F1();
	static void rva007AC61B();
	static void rva007AC645();
	static void rva007AC66F();
	static void rva007AC699();
	static void rva007AC6C3();
	static void rva007AC6F3();
	static void rva007AC71D();
	static void rva007AC75D();
	static void rva007AC787();
	static void rva007AC7B1();
	static void rva007AC7CB();
	static void rva007AC84C();
	static void rva007AC866();
	static void rva007AC896();
	static void rva007AC8C6();
	static void rva007AC8F6();
	static void rva007AC926();
	static void rva007AC96C();
	static void rva007AC986();
	static void rva007AC9DC();
	static void rva007ACA18();
	static void rva007ACA32();
	static void rva007ACA4C();
	static void rva007ACA66();
	static void rva007ACA80();
	static void rva007ACAC5();
	static void rva007ACAEF();
	static void rva007ACB19();
	static void rva007ACB43();
	static void rva007ACB78();
	static void rva007ACBA2();
	static void rva007AD00A();
	static void rva007AD106();
	static void rva007AD217();
	static void rva007AD256();
	static void rva007AD304();
	static void rva007AD362();
	static void rva007AD3E0();
	static void rva007AD439();
	static void rva007AD4A2();
	static void rva007AD4E1();
	static void rva007AD536();
	static void rva007AD565();
	static void rva007AD5C3();
	static void rva007AD5F2();
	static void rva007AD796();
	static void rva007AD82B();
	static void rva007AD8E0();
	static void rva007AD90F();
	static void rva007AD963();
	static void rva007AD9A2();
	static void rva007ADA61();
	static void rva007ADAE7();
	static void rva007ADB32();
	static void rva007ADBA7();
	static void rva007ADBE5();
	static void rva007ADC2E();
	static void rva007ADC72();
	static void rva007ADCDE();
	static void rva007ADD83();
	static void rva007ADDAD();
	static void rva007ADDDF();
	static void rva007ADE09();
	static void rva007ADE5E();
	static void rva007ADEB2();
	static void rva007ADEDC();
	static void rva007ADF6E();
	static void rva007ADF98();
	static void rva007AE019();
	static void rva007AE06D();
	static void rva007AE0EC();
	static void rva007AE106();
	static void rva007AE130();
	static void rva007AE184();
	static void rva007AE1C8();
	static void rva007AE20C();
	static void rva007AE226();
	static void rva007AE250();
	static void rva007AE28A();
	static void rva007AE2A4();
	static void rva007AE2DE();
	static void rva007AE308();
	static void rva007AE322();
	static void rva007AE34C();
	static void rva007AE376();
	static void rva007AE3C7();
	static void rva007AE3F1();
	static void rva007AE41B();
	static void rva007AE445();
	static void rva007AE46F();
	static void rva007AE4C3();
	static void rva007AE503();
	static void rva007AE561();
	static void rva007AE57B();
	static void rva007AE62A();
	static void rva007AE654();
	static void rva007AE67E();
	static void rva007AE6A8();
	static void rva007AE784();
	static void rva007AE81E();
	static void rva007AE848();
	static void rva007AE87C();
	static void rva007AE896();
	static void rva007AE91D();
	static void rva007AE988();
	static void rva007AE9B2();
	static void rva007AE9CC();
	static void rva007AEA02();
	static void rva007AEA50();
	static void rva007AEA6A();
	static void rva007AEA94();
	static void rva007AEABE();
	static void rva007AEAD8();
	static void rva007AEB02();
	static void rva007AEB2C();
	static void rva007AEB56();
	static void rva007AEB80();
	static void rva007AEBE6();
	static void rva007AEC00();
	static void rva007AEC2A();
	static void rva007AEC44();
	static void rva007AEC5E();
	static void rva007AECD6();
	static void rva007AED00();
	static void rva007AED47();
	static void rva007AED87();
	static void rva007AEDB1();
	static void rva007AEE41();
	static void rva007AEE95();
	static void rva007AEEBF();
	static void rva007AEEE9();
	static void rva007AEF5D();
	static void rva007AEF87();
	static void rva007AEFCB();
	static void rva007AEFF5();
	static void rva007AF01F();
	static void rva007AF049();
	static void rva007AF0BD();
	static void rva007AF0D7();
	static void rva007AF146();
	static void rva007AF170();
	static void rva007AF19A();
	static void rva007AF1B4();
	static void rva007AF22A();
	static void rva007AF26E();
	static void rva007AF298();
	static void rva007AF30A();
	static void rva007AF34F();
	static void rva007AF379();
	static void rva007AF3A3();
	static void rva007AF3BD();
	static void rva007AF431();
	static void rva007AF45B();
	static void rva007AF75B();
	static void rva007AF775();
	static void rva007AF78F();
	static void rva007AF7A9();
	static void rva007AF7C3();
	static void rva007AF819();
	static void rva007AF86F();
	static void rva007AF899();
	static void rva007AF8B3();
	static void rva007AFC3C();
	static void rva007AFCC9();
	static void rva007AFD08();
	static void rva007AFD32();
	static void rva007AFD86();
	static void rva007AFDB0();
	static void rva007AFDDA();
};

#define POOL_INIT(init, cleanup) \
	void Rva007AB800PoolInits::init() \
	{ \
		g_freelistPool.grow( 0, -1 ); \
		atexit( cleanup ); \
	}

// ?rva007AB800@Rva007AB800PoolInits@@SAXXZ @ 0x007AB800 (26B), cleanup 0x007B6850
POOL_INIT( rva007AB800, rva007B6850 )
// ?rva007ABC1B@Rva007AB800PoolInits@@SAXXZ @ 0x007ABC1B (26B), cleanup 0x007B6AAA
POOL_INIT( rva007ABC1B, rva007B6AAA )
// ?rva007ABC45@Rva007AB800PoolInits@@SAXXZ @ 0x007ABC45 (26B), cleanup 0x007B6AB4
POOL_INIT( rva007ABC45, rva007B6AB4 )
// ?rva007ABC7F@Rva007AB800PoolInits@@SAXXZ @ 0x007ABC7F (26B), cleanup 0x007B6ABE
POOL_INIT( rva007ABC7F, rva007B6ABE )
// ?rva007ABCF7@Rva007AB800PoolInits@@SAXXZ @ 0x007ABCF7 (26B), cleanup 0x007B6AF1
POOL_INIT( rva007ABCF7, rva007B6AF1 )
// ?rva007ABD21@Rva007AB800PoolInits@@SAXXZ @ 0x007ABD21 (26B), cleanup 0x007B6AFB
POOL_INIT( rva007ABD21, rva007B6AFB )
// ?rva007ABDA7@Rva007AB800PoolInits@@SAXXZ @ 0x007ABDA7 (26B), cleanup 0x007B6B0F
POOL_INIT( rva007ABDA7, rva007B6B0F )
// ?rva007ABDD1@Rva007AB800PoolInits@@SAXXZ @ 0x007ABDD1 (26B), cleanup 0x007B6B2D
POOL_INIT( rva007ABDD1, rva007B6B2D )
// ?rva007ABDFB@Rva007AB800PoolInits@@SAXXZ @ 0x007ABDFB (26B), cleanup 0x007B6B4B
POOL_INIT( rva007ABDFB, rva007B6B4B )
// ?rva007ABE25@Rva007AB800PoolInits@@SAXXZ @ 0x007ABE25 (26B), cleanup 0x007B6B55
POOL_INIT( rva007ABE25, rva007B6B55 )
// ?rva007ABE4F@Rva007AB800PoolInits@@SAXXZ @ 0x007ABE4F (26B), cleanup 0x007B6B5F
POOL_INIT( rva007ABE4F, rva007B6B5F )
// ?rva007ABE79@Rva007AB800PoolInits@@SAXXZ @ 0x007ABE79 (26B), cleanup 0x007B6B69
POOL_INIT( rva007ABE79, rva007B6B69 )
// ?rva007ABEAF@Rva007AB800PoolInits@@SAXXZ @ 0x007ABEAF (26B), cleanup 0x007B6B7D
POOL_INIT( rva007ABEAF, rva007B6B7D )
// ?rva007ABED9@Rva007AB800PoolInits@@SAXXZ @ 0x007ABED9 (26B), cleanup 0x007B6B87
POOL_INIT( rva007ABED9, rva007B6B87 )
// ?rva007ABF0D@Rva007AB800PoolInits@@SAXXZ @ 0x007ABF0D (26B), cleanup 0x007B6B9B
POOL_INIT( rva007ABF0D, rva007B6B9B )
// ?rva007ABF27@Rva007AB800PoolInits@@SAXXZ @ 0x007ABF27 (26B), cleanup 0x007B6BA5
POOL_INIT( rva007ABF27, rva007B6BA5 )
// ?rva007ABF51@Rva007AB800PoolInits@@SAXXZ @ 0x007ABF51 (26B), cleanup 0x007B6BAF
POOL_INIT( rva007ABF51, rva007B6BAF )
// ?rva007ABF9F@Rva007AB800PoolInits@@SAXXZ @ 0x007ABF9F (26B), cleanup 0x007B6BCD
POOL_INIT( rva007ABF9F, rva007B6BCD )
// ?rva007ABFC9@Rva007AB800PoolInits@@SAXXZ @ 0x007ABFC9 (26B), cleanup 0x007B6BD7
POOL_INIT( rva007ABFC9, rva007B6BD7 )
// ?rva007ABFF8@Rva007AB800PoolInits@@SAXXZ @ 0x007ABFF8 (26B), cleanup 0x007B6BEB
POOL_INIT( rva007ABFF8, rva007B6BEB )
// ?rva007AC038@Rva007AB800PoolInits@@SAXXZ @ 0x007AC038 (26B), cleanup 0x007B6BFF
POOL_INIT( rva007AC038, rva007B6BFF )
// ?rva007AC062@Rva007AB800PoolInits@@SAXXZ @ 0x007AC062 (26B), cleanup 0x007B6C09
POOL_INIT( rva007AC062, rva007B6C09 )
// ?rva007AC0B6@Rva007AB800PoolInits@@SAXXZ @ 0x007AC0B6 (26B), cleanup 0x007B6C16
POOL_INIT( rva007AC0B6, rva007B6C16 )
// ?rva007AC0E0@Rva007AB800PoolInits@@SAXXZ @ 0x007AC0E0 (26B), cleanup 0x007B6C20
POOL_INIT( rva007AC0E0, rva007B6C20 )
// ?rva007AC122@Rva007AB800PoolInits@@SAXXZ @ 0x007AC122 (26B), cleanup 0x007B6C34
POOL_INIT( rva007AC122, rva007B6C34 )
// ?rva007AC183@Rva007AB800PoolInits@@SAXXZ @ 0x007AC183 (26B), cleanup 0x007B6C48
POOL_INIT( rva007AC183, rva007B6C48 )
// ?rva007AC1AD@Rva007AB800PoolInits@@SAXXZ @ 0x007AC1AD (26B), cleanup 0x007B6C52
POOL_INIT( rva007AC1AD, rva007B6C52 )
// ?rva007AC1D7@Rva007AB800PoolInits@@SAXXZ @ 0x007AC1D7 (26B), cleanup 0x007B6C5C
POOL_INIT( rva007AC1D7, rva007B6C5C )
// ?rva007AC268@Rva007AB800PoolInits@@SAXXZ @ 0x007AC268 (26B), cleanup 0x007B6CA5
POOL_INIT( rva007AC268, rva007B6CA5 )
// ?rva007AC292@Rva007AB800PoolInits@@SAXXZ @ 0x007AC292 (26B), cleanup 0x007B6CB9
POOL_INIT( rva007AC292, rva007B6CB9 )
// ?rva007AC2AC@Rva007AB800PoolInits@@SAXXZ @ 0x007AC2AC (26B), cleanup 0x007B6CC3
POOL_INIT( rva007AC2AC, rva007B6CC3 )
// ?rva007AC2C6@Rva007AB800PoolInits@@SAXXZ @ 0x007AC2C6 (26B), cleanup 0x007B6CCD
POOL_INIT( rva007AC2C6, rva007B6CCD )
// ?rva007AC2E0@Rva007AB800PoolInits@@SAXXZ @ 0x007AC2E0 (26B), cleanup 0x007B6CD7
POOL_INIT( rva007AC2E0, rva007B6CD7 )
// ?rva007AC327@Rva007AB800PoolInits@@SAXXZ @ 0x007AC327 (26B), cleanup 0x007B6CEB
POOL_INIT( rva007AC327, rva007B6CEB )
// ?rva007AC351@Rva007AB800PoolInits@@SAXXZ @ 0x007AC351 (26B), cleanup 0x007B6CF5
POOL_INIT( rva007AC351, rva007B6CF5 )
// ?rva007AC37B@Rva007AB800PoolInits@@SAXXZ @ 0x007AC37B (26B), cleanup 0x007B6D13
POOL_INIT( rva007AC37B, rva007B6D13 )
// ?rva007AC3A5@Rva007AB800PoolInits@@SAXXZ @ 0x007AC3A5 (26B), cleanup 0x007B6D31
POOL_INIT( rva007AC3A5, rva007B6D31 )
// ?rva007AC3CF@Rva007AB800PoolInits@@SAXXZ @ 0x007AC3CF (26B), cleanup 0x007B6D3B
POOL_INIT( rva007AC3CF, rva007B6D3B )
// ?rva007AC3F9@Rva007AB800PoolInits@@SAXXZ @ 0x007AC3F9 (26B), cleanup 0x007B6D45
POOL_INIT( rva007AC3F9, rva007B6D45 )
// ?rva007AC423@Rva007AB800PoolInits@@SAXXZ @ 0x007AC423 (26B), cleanup 0x007B6D4F
POOL_INIT( rva007AC423, rva007B6D4F )
// ?rva007AC44D@Rva007AB800PoolInits@@SAXXZ @ 0x007AC44D (26B), cleanup 0x007B6D59
POOL_INIT( rva007AC44D, rva007B6D59 )
// ?rva007AC477@Rva007AB800PoolInits@@SAXXZ @ 0x007AC477 (26B), cleanup 0x007B6D63
POOL_INIT( rva007AC477, rva007B6D63 )
// ?rva007AC4A1@Rva007AB800PoolInits@@SAXXZ @ 0x007AC4A1 (26B), cleanup 0x007B6D6D
POOL_INIT( rva007AC4A1, rva007B6D6D )
// ?rva007AC4CB@Rva007AB800PoolInits@@SAXXZ @ 0x007AC4CB (26B), cleanup 0x007B6D77
POOL_INIT( rva007AC4CB, rva007B6D77 )
// ?rva007AC4F5@Rva007AB800PoolInits@@SAXXZ @ 0x007AC4F5 (26B), cleanup 0x007B6D81
POOL_INIT( rva007AC4F5, rva007B6D81 )
// ?rva007AC51F@Rva007AB800PoolInits@@SAXXZ @ 0x007AC51F (26B), cleanup 0x007B6D8B
POOL_INIT( rva007AC51F, rva007B6D8B )
// ?rva007AC549@Rva007AB800PoolInits@@SAXXZ @ 0x007AC549 (26B), cleanup 0x007B6D95
POOL_INIT( rva007AC549, rva007B6D95 )
// ?rva007AC573@Rva007AB800PoolInits@@SAXXZ @ 0x007AC573 (26B), cleanup 0x007B6D9F
POOL_INIT( rva007AC573, rva007B6D9F )
// ?rva007AC59D@Rva007AB800PoolInits@@SAXXZ @ 0x007AC59D (26B), cleanup 0x007B6DAA
POOL_INIT( rva007AC59D, rva007B6DAA )
// ?rva007AC5C7@Rva007AB800PoolInits@@SAXXZ @ 0x007AC5C7 (26B), cleanup 0x007B6DB4
POOL_INIT( rva007AC5C7, rva007B6DB4 )
// ?rva007AC5F1@Rva007AB800PoolInits@@SAXXZ @ 0x007AC5F1 (26B), cleanup 0x007B6DBE
POOL_INIT( rva007AC5F1, rva007B6DBE )
// ?rva007AC61B@Rva007AB800PoolInits@@SAXXZ @ 0x007AC61B (26B), cleanup 0x007B6DC8
POOL_INIT( rva007AC61B, rva007B6DC8 )
// ?rva007AC645@Rva007AB800PoolInits@@SAXXZ @ 0x007AC645 (26B), cleanup 0x007B6DD2
POOL_INIT( rva007AC645, rva007B6DD2 )
// ?rva007AC66F@Rva007AB800PoolInits@@SAXXZ @ 0x007AC66F (26B), cleanup 0x007B6DDC
POOL_INIT( rva007AC66F, rva007B6DDC )
// ?rva007AC699@Rva007AB800PoolInits@@SAXXZ @ 0x007AC699 (26B), cleanup 0x007B6DE6
POOL_INIT( rva007AC699, rva007B6DE6 )
// ?rva007AC6C3@Rva007AB800PoolInits@@SAXXZ @ 0x007AC6C3 (26B), cleanup 0x007B6DF0
POOL_INIT( rva007AC6C3, rva007B6DF0 )
// ?rva007AC6F3@Rva007AB800PoolInits@@SAXXZ @ 0x007AC6F3 (26B), cleanup 0x007B6E04
POOL_INIT( rva007AC6F3, rva007B6E04 )
// ?rva007AC71D@Rva007AB800PoolInits@@SAXXZ @ 0x007AC71D (26B), cleanup 0x007B6E0E
POOL_INIT( rva007AC71D, rva007B6E0E )
// ?rva007AC75D@Rva007AB800PoolInits@@SAXXZ @ 0x007AC75D (26B), cleanup 0x007B6E22
POOL_INIT( rva007AC75D, rva007B6E22 )
// ?rva007AC787@Rva007AB800PoolInits@@SAXXZ @ 0x007AC787 (26B), cleanup 0x007B6E2C
POOL_INIT( rva007AC787, rva007B6E2C )
// ?rva007AC7B1@Rva007AB800PoolInits@@SAXXZ @ 0x007AC7B1 (26B), cleanup 0x007B6E40
POOL_INIT( rva007AC7B1, rva007B6E40 )
// ?rva007AC7CB@Rva007AB800PoolInits@@SAXXZ @ 0x007AC7CB (26B), cleanup 0x007B6E4A
POOL_INIT( rva007AC7CB, rva007B6E4A )
// ?rva007AC84C@Rva007AB800PoolInits@@SAXXZ @ 0x007AC84C (26B), cleanup 0x007B6E68
POOL_INIT( rva007AC84C, rva007B6E68 )
// ?rva007AC866@Rva007AB800PoolInits@@SAXXZ @ 0x007AC866 (26B), cleanup 0x007B6E86
POOL_INIT( rva007AC866, rva007B6E86 )
// ?rva007AC896@Rva007AB800PoolInits@@SAXXZ @ 0x007AC896 (26B), cleanup 0x007B6E9A
POOL_INIT( rva007AC896, rva007B6E9A )
// ?rva007AC8C6@Rva007AB800PoolInits@@SAXXZ @ 0x007AC8C6 (26B), cleanup 0x007B6EA4
POOL_INIT( rva007AC8C6, rva007B6EA4 )
// ?rva007AC8F6@Rva007AB800PoolInits@@SAXXZ @ 0x007AC8F6 (26B), cleanup 0x007B6EB8
POOL_INIT( rva007AC8F6, rva007B6EB8 )
// ?rva007AC926@Rva007AB800PoolInits@@SAXXZ @ 0x007AC926 (26B), cleanup 0x007B6ECC
POOL_INIT( rva007AC926, rva007B6ECC )
// ?rva007AC96C@Rva007AB800PoolInits@@SAXXZ @ 0x007AC96C (26B), cleanup 0x007B6EE0
POOL_INIT( rva007AC96C, rva007B6EE0 )
// ?rva007AC986@Rva007AB800PoolInits@@SAXXZ @ 0x007AC986 (26B), cleanup 0x007B6EFE
POOL_INIT( rva007AC986, rva007B6EFE )
// ?rva007AC9DC@Rva007AB800PoolInits@@SAXXZ @ 0x007AC9DC (26B), cleanup 0x007B6F1C
POOL_INIT( rva007AC9DC, rva007B6F1C )
// ?rva007ACA18@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA18 (26B), cleanup 0x007B6F28
POOL_INIT( rva007ACA18, rva007B6F28 )
// ?rva007ACA32@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA32 (26B), cleanup 0x007B6F32
POOL_INIT( rva007ACA32, rva007B6F32 )
// ?rva007ACA4C@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA4C (26B), cleanup 0x007B6F3E
POOL_INIT( rva007ACA4C, rva007B6F3E )
// ?rva007ACA66@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA66 (26B), cleanup 0x007B6F48
POOL_INIT( rva007ACA66, rva007B6F48 )
// ?rva007ACA80@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA80 (26B), cleanup 0x007B6F52
POOL_INIT( rva007ACA80, rva007B6F52 )
// ?rva007ACAC5@Rva007AB800PoolInits@@SAXXZ @ 0x007ACAC5 (26B), cleanup 0x007B6F66
POOL_INIT( rva007ACAC5, rva007B6F66 )
// ?rva007ACAEF@Rva007AB800PoolInits@@SAXXZ @ 0x007ACAEF (26B), cleanup 0x007B6F70
POOL_INIT( rva007ACAEF, rva007B6F70 )
// ?rva007ACB19@Rva007AB800PoolInits@@SAXXZ @ 0x007ACB19 (26B), cleanup 0x007B6F7A
POOL_INIT( rva007ACB19, rva007B6F7A )
// ?rva007ACB43@Rva007AB800PoolInits@@SAXXZ @ 0x007ACB43 (26B), cleanup 0x007B6F84
POOL_INIT( rva007ACB43, rva007B6F84 )
// ?rva007ACB78@Rva007AB800PoolInits@@SAXXZ @ 0x007ACB78 (26B), cleanup 0x007B6FA2
POOL_INIT( rva007ACB78, rva007B6FA2 )
// ?rva007ACBA2@Rva007AB800PoolInits@@SAXXZ @ 0x007ACBA2 (26B), cleanup 0x007B6FAC
POOL_INIT( rva007ACBA2, rva007B6FAC )
// ?rva007AD00A@Rva007AB800PoolInits@@SAXXZ @ 0x007AD00A (26B), cleanup 0x007B751A
POOL_INIT( rva007AD00A, rva007B751A )
// ?rva007AD106@Rva007AB800PoolInits@@SAXXZ @ 0x007AD106 (26B), cleanup 0x007B7524
POOL_INIT( rva007AD106, rva007B7524 )
// ?rva007AD217@Rva007AB800PoolInits@@SAXXZ @ 0x007AD217 (26B), cleanup 0x007B752E
POOL_INIT( rva007AD217, rva007B752E )
// ?rva007AD256@Rva007AB800PoolInits@@SAXXZ @ 0x007AD256 (26B), cleanup 0x007B7538
POOL_INIT( rva007AD256, rva007B7538 )
// ?rva007AD304@Rva007AB800PoolInits@@SAXXZ @ 0x007AD304 (26B), cleanup 0x007B7542
POOL_INIT( rva007AD304, rva007B7542 )
// ?rva007AD362@Rva007AB800PoolInits@@SAXXZ @ 0x007AD362 (26B), cleanup 0x007B754C
POOL_INIT( rva007AD362, rva007B754C )
// ?rva007AD3E0@Rva007AB800PoolInits@@SAXXZ @ 0x007AD3E0 (26B), cleanup 0x007B7560
POOL_INIT( rva007AD3E0, rva007B7560 )
// ?rva007AD439@Rva007AB800PoolInits@@SAXXZ @ 0x007AD439 (26B), cleanup 0x007B756A
POOL_INIT( rva007AD439, rva007B756A )
// ?rva007AD4A2@Rva007AB800PoolInits@@SAXXZ @ 0x007AD4A2 (26B), cleanup 0x007B7574
POOL_INIT( rva007AD4A2, rva007B7574 )
// ?rva007AD4E1@Rva007AB800PoolInits@@SAXXZ @ 0x007AD4E1 (26B), cleanup 0x007B757E
POOL_INIT( rva007AD4E1, rva007B757E )
// ?rva007AD536@Rva007AB800PoolInits@@SAXXZ @ 0x007AD536 (26B), cleanup 0x007B7592
POOL_INIT( rva007AD536, rva007B7592 )
// ?rva007AD565@Rva007AB800PoolInits@@SAXXZ @ 0x007AD565 (26B), cleanup 0x007B75B0
POOL_INIT( rva007AD565, rva007B75B0 )
// ?rva007AD5C3@Rva007AB800PoolInits@@SAXXZ @ 0x007AD5C3 (26B), cleanup 0x007B75BA
POOL_INIT( rva007AD5C3, rva007B75BA )
// ?rva007AD5F2@Rva007AB800PoolInits@@SAXXZ @ 0x007AD5F2 (26B), cleanup 0x007B75CE
POOL_INIT( rva007AD5F2, rva007B75CE )
// ?rva007AD796@Rva007AB800PoolInits@@SAXXZ @ 0x007AD796 (26B), cleanup 0x007B75D8
POOL_INIT( rva007AD796, rva007B75D8 )
// ?rva007AD82B@Rva007AB800PoolInits@@SAXXZ @ 0x007AD82B (26B), cleanup 0x007B75EC
POOL_INIT( rva007AD82B, rva007B75EC )
// ?rva007AD8E0@Rva007AB800PoolInits@@SAXXZ @ 0x007AD8E0 (26B), cleanup 0x007B7600
POOL_INIT( rva007AD8E0, rva007B7600 )
// ?rva007AD90F@Rva007AB800PoolInits@@SAXXZ @ 0x007AD90F (26B), cleanup 0x007B7614
POOL_INIT( rva007AD90F, rva007B7614 )
// ?rva007AD963@Rva007AB800PoolInits@@SAXXZ @ 0x007AD963 (26B), cleanup 0x007B761E
POOL_INIT( rva007AD963, rva007B761E )
// ?rva007AD9A2@Rva007AB800PoolInits@@SAXXZ @ 0x007AD9A2 (26B), cleanup 0x007B7628
POOL_INIT( rva007AD9A2, rva007B7628 )
// ?rva007ADA61@Rva007AB800PoolInits@@SAXXZ @ 0x007ADA61 (26B), cleanup 0x007B7646
POOL_INIT( rva007ADA61, rva007B7646 )
// ?rva007ADAE7@Rva007AB800PoolInits@@SAXXZ @ 0x007ADAE7 (26B), cleanup 0x007B76D2
POOL_INIT( rva007ADAE7, rva007B76D2 )
// ?rva007ADB32@Rva007AB800PoolInits@@SAXXZ @ 0x007ADB32 (26B), cleanup 0x007B76F0
POOL_INIT( rva007ADB32, rva007B76F0 )
// ?rva007ADBA7@Rva007AB800PoolInits@@SAXXZ @ 0x007ADBA7 (26B), cleanup 0x007B7722
POOL_INIT( rva007ADBA7, rva007B7722 )
// ?rva007ADBE5@Rva007AB800PoolInits@@SAXXZ @ 0x007ADBE5 (26B), cleanup 0x007B772C
POOL_INIT( rva007ADBE5, rva007B772C )
// ?rva007ADC2E@Rva007AB800PoolInits@@SAXXZ @ 0x007ADC2E (26B), cleanup 0x007B774A
POOL_INIT( rva007ADC2E, rva007B774A )
// ?rva007ADC72@Rva007AB800PoolInits@@SAXXZ @ 0x007ADC72 (26B), cleanup 0x007B7754
POOL_INIT( rva007ADC72, rva007B7754 )
// ?rva007ADCDE@Rva007AB800PoolInits@@SAXXZ @ 0x007ADCDE (26B), cleanup 0x007B7772
POOL_INIT( rva007ADCDE, rva007B7772 )
// ?rva007ADD83@Rva007AB800PoolInits@@SAXXZ @ 0x007ADD83 (26B), cleanup 0x007B7790
POOL_INIT( rva007ADD83, rva007B7790 )
// ?rva007ADDAD@Rva007AB800PoolInits@@SAXXZ @ 0x007ADDAD (26B), cleanup 0x007B779A
POOL_INIT( rva007ADDAD, rva007B779A )
// ?rva007ADDDF@Rva007AB800PoolInits@@SAXXZ @ 0x007ADDDF (26B), cleanup 0x007B77A4
POOL_INIT( rva007ADDDF, rva007B77A4 )
// ?rva007ADE09@Rva007AB800PoolInits@@SAXXZ @ 0x007ADE09 (26B), cleanup 0x007B77AE
POOL_INIT( rva007ADE09, rva007B77AE )
// ?rva007ADE5E@Rva007AB800PoolInits@@SAXXZ @ 0x007ADE5E (26B), cleanup 0x007B77C3
POOL_INIT( rva007ADE5E, rva007B77C3 )
// ?rva007ADEB2@Rva007AB800PoolInits@@SAXXZ @ 0x007ADEB2 (26B), cleanup 0x007B77CE
POOL_INIT( rva007ADEB2, rva007B77CE )
// ?rva007ADEDC@Rva007AB800PoolInits@@SAXXZ @ 0x007ADEDC (26B), cleanup 0x007B77E2
POOL_INIT( rva007ADEDC, rva007B77E2 )
// ?rva007ADF6E@Rva007AB800PoolInits@@SAXXZ @ 0x007ADF6E (26B), cleanup 0x007B77FC
POOL_INIT( rva007ADF6E, rva007B77FC )
// ?rva007ADF98@Rva007AB800PoolInits@@SAXXZ @ 0x007ADF98 (26B), cleanup 0x007B7806
POOL_INIT( rva007ADF98, rva007B7806 )
// ?rva007AE019@Rva007AB800PoolInits@@SAXXZ @ 0x007AE019 (26B), cleanup 0x007B7838
POOL_INIT( rva007AE019, rva007B7838 )
// ?rva007AE06D@Rva007AB800PoolInits@@SAXXZ @ 0x007AE06D (26B), cleanup 0x007B7888
POOL_INIT( rva007AE06D, rva007B7888 )
// ?rva007AE0EC@Rva007AB800PoolInits@@SAXXZ @ 0x007AE0EC (26B), cleanup 0x007B78B0
POOL_INIT( rva007AE0EC, rva007B78B0 )
// ?rva007AE106@Rva007AB800PoolInits@@SAXXZ @ 0x007AE106 (26B), cleanup 0x007B78CE
POOL_INIT( rva007AE106, rva007B78CE )
// ?rva007AE130@Rva007AB800PoolInits@@SAXXZ @ 0x007AE130 (26B), cleanup 0x007B78D8
POOL_INIT( rva007AE130, rva007B78D8 )
// ?rva007AE184@Rva007AB800PoolInits@@SAXXZ @ 0x007AE184 (26B), cleanup 0x007B78E2
POOL_INIT( rva007AE184, rva007B78E2 )
// ?rva007AE1C8@Rva007AB800PoolInits@@SAXXZ @ 0x007AE1C8 (26B), cleanup 0x007B78F6
POOL_INIT( rva007AE1C8, rva007B78F6 )
// ?rva007AE20C@Rva007AB800PoolInits@@SAXXZ @ 0x007AE20C (26B), cleanup 0x007B790A
POOL_INIT( rva007AE20C, rva007B790A )
// ?rva007AE226@Rva007AB800PoolInits@@SAXXZ @ 0x007AE226 (26B), cleanup 0x007B7914
POOL_INIT( rva007AE226, rva007B7914 )
// ?rva007AE250@Rva007AB800PoolInits@@SAXXZ @ 0x007AE250 (26B), cleanup 0x007B791E
POOL_INIT( rva007AE250, rva007B791E )
// ?rva007AE28A@Rva007AB800PoolInits@@SAXXZ @ 0x007AE28A (26B), cleanup 0x007B7928
POOL_INIT( rva007AE28A, rva007B7928 )
// ?rva007AE2A4@Rva007AB800PoolInits@@SAXXZ @ 0x007AE2A4 (26B), cleanup 0x007B7932
POOL_INIT( rva007AE2A4, rva007B7932 )
// ?rva007AE2DE@Rva007AB800PoolInits@@SAXXZ @ 0x007AE2DE (26B), cleanup 0x007B793C
POOL_INIT( rva007AE2DE, rva007B793C )
// ?rva007AE308@Rva007AB800PoolInits@@SAXXZ @ 0x007AE308 (26B), cleanup 0x007B7946
POOL_INIT( rva007AE308, rva007B7946 )
// ?rva007AE322@Rva007AB800PoolInits@@SAXXZ @ 0x007AE322 (26B), cleanup 0x007B7950
POOL_INIT( rva007AE322, rva007B7950 )
// ?rva007AE34C@Rva007AB800PoolInits@@SAXXZ @ 0x007AE34C (26B), cleanup 0x007B795A
POOL_INIT( rva007AE34C, rva007B795A )
// ?rva007AE376@Rva007AB800PoolInits@@SAXXZ @ 0x007AE376 (26B), cleanup 0x007B7964
POOL_INIT( rva007AE376, rva007B7964 )
// ?rva007AE3C7@Rva007AB800PoolInits@@SAXXZ @ 0x007AE3C7 (26B), cleanup 0x007B79C9
POOL_INIT( rva007AE3C7, rva007B79C9 )
// ?rva007AE3F1@Rva007AB800PoolInits@@SAXXZ @ 0x007AE3F1 (26B), cleanup 0x007B79D3
POOL_INIT( rva007AE3F1, rva007B79D3 )
// ?rva007AE41B@Rva007AB800PoolInits@@SAXXZ @ 0x007AE41B (26B), cleanup 0x007B79DD
POOL_INIT( rva007AE41B, rva007B79DD )
// ?rva007AE445@Rva007AB800PoolInits@@SAXXZ @ 0x007AE445 (26B), cleanup 0x007B79E7
POOL_INIT( rva007AE445, rva007B79E7 )
// ?rva007AE46F@Rva007AB800PoolInits@@SAXXZ @ 0x007AE46F (26B), cleanup 0x007B79F1
POOL_INIT( rva007AE46F, rva007B79F1 )
// ?rva007AE4C3@Rva007AB800PoolInits@@SAXXZ @ 0x007AE4C3 (26B), cleanup 0x007B7A0F
POOL_INIT( rva007AE4C3, rva007B7A0F )
// ?rva007AE503@Rva007AB800PoolInits@@SAXXZ @ 0x007AE503 (26B), cleanup 0x007B7A23
POOL_INIT( rva007AE503, rva007B7A23 )
// ?rva007AE561@Rva007AB800PoolInits@@SAXXZ @ 0x007AE561 (26B), cleanup 0x007B7A2D
POOL_INIT( rva007AE561, rva007B7A2D )
// ?rva007AE57B@Rva007AB800PoolInits@@SAXXZ @ 0x007AE57B (26B), cleanup 0x007B7A4B
POOL_INIT( rva007AE57B, rva007B7A4B )
// ?rva007AE62A@Rva007AB800PoolInits@@SAXXZ @ 0x007AE62A (26B), cleanup 0x007B7A73
POOL_INIT( rva007AE62A, rva007B7A73 )
// ?rva007AE654@Rva007AB800PoolInits@@SAXXZ @ 0x007AE654 (26B), cleanup 0x007B7AAF
POOL_INIT( rva007AE654, rva007B7AAF )
// ?rva007AE67E@Rva007AB800PoolInits@@SAXXZ @ 0x007AE67E (26B), cleanup 0x007B7AB9
POOL_INIT( rva007AE67E, rva007B7AB9 )
// ?rva007AE6A8@Rva007AB800PoolInits@@SAXXZ @ 0x007AE6A8 (26B), cleanup 0x007B7AC3
POOL_INIT( rva007AE6A8, rva007B7AC3 )
// ?rva007AE784@Rva007AB800PoolInits@@SAXXZ @ 0x007AE784 (26B), cleanup 0x007B7AEB
POOL_INIT( rva007AE784, rva007B7AEB )
// ?rva007AE81E@Rva007AB800PoolInits@@SAXXZ @ 0x007AE81E (26B), cleanup 0x007B7B1E
POOL_INIT( rva007AE81E, rva007B7B1E )
// ?rva007AE848@Rva007AB800PoolInits@@SAXXZ @ 0x007AE848 (26B), cleanup 0x007B7B32
POOL_INIT( rva007AE848, rva007B7B32 )
// ?rva007AE87C@Rva007AB800PoolInits@@SAXXZ @ 0x007AE87C (26B), cleanup 0x007B7B3C
POOL_INIT( rva007AE87C, rva007B7B3C )
// ?rva007AE896@Rva007AB800PoolInits@@SAXXZ @ 0x007AE896 (26B), cleanup 0x007B7B46
POOL_INIT( rva007AE896, rva007B7B46 )
// ?rva007AE91D@Rva007AB800PoolInits@@SAXXZ @ 0x007AE91D (26B), cleanup 0x007B7B78
POOL_INIT( rva007AE91D, rva007B7B78 )
// ?rva007AE988@Rva007AB800PoolInits@@SAXXZ @ 0x007AE988 (26B), cleanup 0x007B7B96
POOL_INIT( rva007AE988, rva007B7B96 )
// ?rva007AE9B2@Rva007AB800PoolInits@@SAXXZ @ 0x007AE9B2 (26B), cleanup 0x007B7BA0
POOL_INIT( rva007AE9B2, rva007B7BA0 )
// ?rva007AE9CC@Rva007AB800PoolInits@@SAXXZ @ 0x007AE9CC (26B), cleanup 0x007B7BAA
POOL_INIT( rva007AE9CC, rva007B7BAA )
// ?rva007AEA02@Rva007AB800PoolInits@@SAXXZ @ 0x007AEA02 (26B), cleanup 0x007B7BB4
POOL_INIT( rva007AEA02, rva007B7BB4 )
// ?rva007AEA50@Rva007AB800PoolInits@@SAXXZ @ 0x007AEA50 (26B), cleanup 0x007B7BD2
POOL_INIT( rva007AEA50, rva007B7BD2 )
// ?rva007AEA6A@Rva007AB800PoolInits@@SAXXZ @ 0x007AEA6A (26B), cleanup 0x007B7BDC
POOL_INIT( rva007AEA6A, rva007B7BDC )
// ?rva007AEA94@Rva007AB800PoolInits@@SAXXZ @ 0x007AEA94 (26B), cleanup 0x007B7BE6
POOL_INIT( rva007AEA94, rva007B7BE6 )
// ?rva007AEABE@Rva007AB800PoolInits@@SAXXZ @ 0x007AEABE (26B), cleanup 0x007B7BF0
POOL_INIT( rva007AEABE, rva007B7BF0 )
// ?rva007AEAD8@Rva007AB800PoolInits@@SAXXZ @ 0x007AEAD8 (26B), cleanup 0x007B7BFA
POOL_INIT( rva007AEAD8, rva007B7BFA )
// ?rva007AEB02@Rva007AB800PoolInits@@SAXXZ @ 0x007AEB02 (26B), cleanup 0x007B7C0E
POOL_INIT( rva007AEB02, rva007B7C0E )
// ?rva007AEB2C@Rva007AB800PoolInits@@SAXXZ @ 0x007AEB2C (26B), cleanup 0x007B7C18
POOL_INIT( rva007AEB2C, rva007B7C18 )
// ?rva007AEB56@Rva007AB800PoolInits@@SAXXZ @ 0x007AEB56 (26B), cleanup 0x007B7C22
POOL_INIT( rva007AEB56, rva007B7C22 )
// ?rva007AEB80@Rva007AB800PoolInits@@SAXXZ @ 0x007AEB80 (26B), cleanup 0x007B7C2C
POOL_INIT( rva007AEB80, rva007B7C2C )
// ?rva007AEBE6@Rva007AB800PoolInits@@SAXXZ @ 0x007AEBE6 (26B), cleanup 0x007B7C36
POOL_INIT( rva007AEBE6, rva007B7C36 )
// ?rva007AEC00@Rva007AB800PoolInits@@SAXXZ @ 0x007AEC00 (26B), cleanup 0x007B7C4A
POOL_INIT( rva007AEC00, rva007B7C4A )
// ?rva007AEC2A@Rva007AB800PoolInits@@SAXXZ @ 0x007AEC2A (26B), cleanup 0x007B7C54
POOL_INIT( rva007AEC2A, rva007B7C54 )
// ?rva007AEC44@Rva007AB800PoolInits@@SAXXZ @ 0x007AEC44 (26B), cleanup 0x007B7C5E
POOL_INIT( rva007AEC44, rva007B7C5E )
// ?rva007AEC5E@Rva007AB800PoolInits@@SAXXZ @ 0x007AEC5E (26B), cleanup 0x007B7C68
POOL_INIT( rva007AEC5E, rva007B7C68 )
// ?rva007AECD6@Rva007AB800PoolInits@@SAXXZ @ 0x007AECD6 (26B), cleanup 0x007B7C91
POOL_INIT( rva007AECD6, rva007B7C91 )
// ?rva007AED00@Rva007AB800PoolInits@@SAXXZ @ 0x007AED00 (26B), cleanup 0x007B7C9B
POOL_INIT( rva007AED00, rva007B7C9B )
// ?rva007AED47@Rva007AB800PoolInits@@SAXXZ @ 0x007AED47 (26B), cleanup 0x007B7CA5
POOL_INIT( rva007AED47, rva007B7CA5 )
// ?rva007AED87@Rva007AB800PoolInits@@SAXXZ @ 0x007AED87 (26B), cleanup 0x007B7CB9
POOL_INIT( rva007AED87, rva007B7CB9 )
// ?rva007AEDB1@Rva007AB800PoolInits@@SAXXZ @ 0x007AEDB1 (26B), cleanup 0x007B7CCD
POOL_INIT( rva007AEDB1, rva007B7CCD )
// ?rva007AEE41@Rva007AB800PoolInits@@SAXXZ @ 0x007AEE41 (26B), cleanup 0x007B7CE1
POOL_INIT( rva007AEE41, rva007B7CE1 )
// ?rva007AEE95@Rva007AB800PoolInits@@SAXXZ @ 0x007AEE95 (26B), cleanup 0x007B7CEB
POOL_INIT( rva007AEE95, rva007B7CEB )
// ?rva007AEEBF@Rva007AB800PoolInits@@SAXXZ @ 0x007AEEBF (26B), cleanup 0x007B7CFF
POOL_INIT( rva007AEEBF, rva007B7CFF )
// ?rva007AEEE9@Rva007AB800PoolInits@@SAXXZ @ 0x007AEEE9 (26B), cleanup 0x007B7D09
POOL_INIT( rva007AEEE9, rva007B7D09 )
// ?rva007AEF5D@Rva007AB800PoolInits@@SAXXZ @ 0x007AEF5D (26B), cleanup 0x007B7D13
POOL_INIT( rva007AEF5D, rva007B7D13 )
// ?rva007AEF87@Rva007AB800PoolInits@@SAXXZ @ 0x007AEF87 (26B), cleanup 0x007B7D1D
POOL_INIT( rva007AEF87, rva007B7D1D )
// ?rva007AEFCB@Rva007AB800PoolInits@@SAXXZ @ 0x007AEFCB (26B), cleanup 0x007B7D4F
POOL_INIT( rva007AEFCB, rva007B7D4F )
// ?rva007AEFF5@Rva007AB800PoolInits@@SAXXZ @ 0x007AEFF5 (26B), cleanup 0x007B7D63
POOL_INIT( rva007AEFF5, rva007B7D63 )
// ?rva007AF01F@Rva007AB800PoolInits@@SAXXZ @ 0x007AF01F (26B), cleanup 0x007B7D6D
POOL_INIT( rva007AF01F, rva007B7D6D )
// ?rva007AF049@Rva007AB800PoolInits@@SAXXZ @ 0x007AF049 (26B), cleanup 0x007B7D8B
POOL_INIT( rva007AF049, rva007B7D8B )
// ?rva007AF0BD@Rva007AB800PoolInits@@SAXXZ @ 0x007AF0BD (26B), cleanup 0x007B7D9F
POOL_INIT( rva007AF0BD, rva007B7D9F )
// ?rva007AF0D7@Rva007AB800PoolInits@@SAXXZ @ 0x007AF0D7 (26B), cleanup 0x007B7DA9
POOL_INIT( rva007AF0D7, rva007B7DA9 )
// ?rva007AF146@Rva007AB800PoolInits@@SAXXZ @ 0x007AF146 (26B), cleanup 0x007B7DBD
POOL_INIT( rva007AF146, rva007B7DBD )
// ?rva007AF170@Rva007AB800PoolInits@@SAXXZ @ 0x007AF170 (26B), cleanup 0x007B7DE5
POOL_INIT( rva007AF170, rva007B7DE5 )
// ?rva007AF19A@Rva007AB800PoolInits@@SAXXZ @ 0x007AF19A (26B), cleanup 0x007B7DEF
POOL_INIT( rva007AF19A, rva007B7DEF )
// ?rva007AF1B4@Rva007AB800PoolInits@@SAXXZ @ 0x007AF1B4 (26B), cleanup 0x007B7DF9
POOL_INIT( rva007AF1B4, rva007B7DF9 )
// ?rva007AF22A@Rva007AB800PoolInits@@SAXXZ @ 0x007AF22A (26B), cleanup 0x007B7E03
POOL_INIT( rva007AF22A, rva007B7E03 )
// ?rva007AF26E@Rva007AB800PoolInits@@SAXXZ @ 0x007AF26E (26B), cleanup 0x007B7E17
POOL_INIT( rva007AF26E, rva007B7E17 )
// ?rva007AF298@Rva007AB800PoolInits@@SAXXZ @ 0x007AF298 (26B), cleanup 0x007B7E2B
POOL_INIT( rva007AF298, rva007B7E2B )
// ?rva007AF30A@Rva007AB800PoolInits@@SAXXZ @ 0x007AF30A (26B), cleanup 0x007B7E35
POOL_INIT( rva007AF30A, rva007B7E35 )
// ?rva007AF34F@Rva007AB800PoolInits@@SAXXZ @ 0x007AF34F (26B), cleanup 0x007B7E53
POOL_INIT( rva007AF34F, rva007B7E53 )
// ?rva007AF379@Rva007AB800PoolInits@@SAXXZ @ 0x007AF379 (26B), cleanup 0x007B7E5D
POOL_INIT( rva007AF379, rva007B7E5D )
// ?rva007AF3A3@Rva007AB800PoolInits@@SAXXZ @ 0x007AF3A3 (26B), cleanup 0x007B7E67
POOL_INIT( rva007AF3A3, rva007B7E67 )
// ?rva007AF3BD@Rva007AB800PoolInits@@SAXXZ @ 0x007AF3BD (26B), cleanup 0x007B7E71
POOL_INIT( rva007AF3BD, rva007B7E71 )
// ?rva007AF431@Rva007AB800PoolInits@@SAXXZ @ 0x007AF431 (26B), cleanup 0x007B7E7B
POOL_INIT( rva007AF431, rva007B7E7B )
// ?rva007AF45B@Rva007AB800PoolInits@@SAXXZ @ 0x007AF45B (26B), cleanup 0x007B7E85
POOL_INIT( rva007AF45B, rva007B7E85 )
// ?rva007AF75B@Rva007AB800PoolInits@@SAXXZ @ 0x007AF75B (26B), cleanup 0x007B806F
POOL_INIT( rva007AF75B, rva007B806F )
// ?rva007AF775@Rva007AB800PoolInits@@SAXXZ @ 0x007AF775 (26B), cleanup 0x007B8079
POOL_INIT( rva007AF775, rva007B8079 )
// ?rva007AF78F@Rva007AB800PoolInits@@SAXXZ @ 0x007AF78F (26B), cleanup 0x007B8083
POOL_INIT( rva007AF78F, rva007B8083 )
// ?rva007AF7A9@Rva007AB800PoolInits@@SAXXZ @ 0x007AF7A9 (26B), cleanup 0x007B808D
POOL_INIT( rva007AF7A9, rva007B808D )
// ?rva007AF7C3@Rva007AB800PoolInits@@SAXXZ @ 0x007AF7C3 (26B), cleanup 0x007B8097
POOL_INIT( rva007AF7C3, rva007B8097 )
// ?rva007AF819@Rva007AB800PoolInits@@SAXXZ @ 0x007AF819 (26B), cleanup 0x007B80AB
POOL_INIT( rva007AF819, rva007B80AB )
// ?rva007AF86F@Rva007AB800PoolInits@@SAXXZ @ 0x007AF86F (26B), cleanup 0x007B80D3
POOL_INIT( rva007AF86F, rva007B80D3 )
// ?rva007AF899@Rva007AB800PoolInits@@SAXXZ @ 0x007AF899 (26B), cleanup 0x007B80DD
POOL_INIT( rva007AF899, rva007B80DD )
// ?rva007AF8B3@Rva007AB800PoolInits@@SAXXZ @ 0x007AF8B3 (26B), cleanup 0x007B80E7
POOL_INIT( rva007AF8B3, rva007B80E7 )
// ?rva007AFC3C@Rva007AB800PoolInits@@SAXXZ @ 0x007AFC3C (26B), cleanup 0x007B815F
POOL_INIT( rva007AFC3C, rva007B815F )
// ?rva007AFCC9@Rva007AB800PoolInits@@SAXXZ @ 0x007AFCC9 (26B), cleanup 0x007B816B
POOL_INIT( rva007AFCC9, rva007B816B )
// ?rva007AFD08@Rva007AB800PoolInits@@SAXXZ @ 0x007AFD08 (26B), cleanup 0x007B819D
POOL_INIT( rva007AFD08, rva007B819D )
// ?rva007AFD32@Rva007AB800PoolInits@@SAXXZ @ 0x007AFD32 (26B), cleanup 0x007B81A7
POOL_INIT( rva007AFD32, rva007B81A7 )
// ?rva007AFD86@Rva007AB800PoolInits@@SAXXZ @ 0x007AFD86 (26B), cleanup 0x007B81B1
POOL_INIT( rva007AFD86, rva007B81B1 )
// ?rva007AFDB0@Rva007AB800PoolInits@@SAXXZ @ 0x007AFDB0 (26B), cleanup 0x007B81BB
POOL_INIT( rva007AFDB0, rva007B81BB )
// ?rva007AFDDA@Rva007AB800PoolInits@@SAXXZ @ 0x007AFDDA (26B), cleanup 0x007B81C5
POOL_INIT( rva007AFDDA, rva007B81C5 )
