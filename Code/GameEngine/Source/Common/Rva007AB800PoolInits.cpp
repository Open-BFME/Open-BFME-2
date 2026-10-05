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
