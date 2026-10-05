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
