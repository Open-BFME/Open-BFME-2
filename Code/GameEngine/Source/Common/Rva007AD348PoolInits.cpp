// cl: /O1 /DNDEBUG /MD
//
// Static-initializer copies for three more freelist pools, the siblings of the
// behavior pool strip in Rva007AB800PoolInits.cpp: 0xDB8FEC (popped by the
// matched Rva001EB984Member::init), 0xDBBD2C (Rva002AC026Member::init) and
// 0xDBA5E0. Each per-TU copy is a 26-byte initializer, grow(0, -1) on its
// pool then atexit of its own 10-byte cleanup (ecx=pool, tail-jump to the
// pool clear 0x001EAF7B). Neither half had a row; the owning TUs are
// unrecovered, so both keep honest address names, the initializers as
// members of a friend holder and the cleanups as free functions in the
// style of Rva007B6880Thunks.cpp.

extern "C" int __cdecl atexit(void (__cdecl *)(void));

struct Rva007AD348PoolInits;

class FreelistPool
{
	friend struct Rva007AD348PoolInits;

private:
	bool grow( int arena, int size );
};

class Rva001EAF7B
{
public:
	bool rva001EAF7B();
};

extern FreelistPool g_freelistPool009BBD2C;
extern FreelistPool g_freelistPool00DB8FEC;
extern FreelistPool g_freelistPool00DBA5E0;
FreelistPool g_freelistPool009BBD2C;
FreelistPool g_freelistPool00DB8FEC;
FreelistPool g_freelistPool00DBA5E0;

struct Rva007AD348PoolInits
{
	static void rva007AD348();
	static void rva007ADC58();
	static void rva007ADCC4();
	static void rva007ADE98();
	static void rva007AE053();
	static void rva007AE0B8();
	static void rva007AE0D2();
	static void rva007AE1AE();
	static void rva007AE1E2();
	static void rva007AE862();
	static void rva007AEBCC();
	static void rva007AEE7B();
	static void rva007AEFB1();
	static void rva007AF210();
	static void rva007AF254();
	static void rva007AFEAC();
	static void rva007B030B();
	static void rva007B043B();
	static void rva007B04C3();
	static void rva007B055B();
	static void rva007B0757();
	static void rva007B0800();
	static void rva007B0844();
	static void rva007B08C2();
	static void rva007B0AC4();
	static void rva007B0DF0();
	static void rva007B1190();
	static void rva007B143E();
	static void rva007B16BD();
	static void rva007B1931();
	static void rva007B2784();
	static void rva007B2EE6();
	static void rva007B2F78();
	static void rva007B32F3();
	static void rva007B3D36();
};

#define POOL_CLEANUP(cleanup, pool) \
	void __cdecl cleanup() \
	{ \
		( (Rva001EAF7B *)&pool )->rva001EAF7B(); \
	}

#define POOL_INIT(init, pool, cleanup) \
	void Rva007AD348PoolInits::init() \
	{ \
		pool.grow( 0, -1 ); \
		atexit( cleanup ); \
	}

// ?rva007B7556@@YAXXZ @ 0x007B7556 (10B) and ?rva007AD348@Rva007AD348PoolInits@@SAXXZ @ 0x007AD348 (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B7556, g_freelistPool00DB8FEC )
POOL_INIT( rva007AD348, g_freelistPool00DB8FEC, rva007B7556 )
// ?rva007B775E@@YAXXZ @ 0x007B775E (10B) and ?rva007ADC58@Rva007AD348PoolInits@@SAXXZ @ 0x007ADC58 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B775E, g_freelistPool00DBA5E0 )
POOL_INIT( rva007ADC58, g_freelistPool00DBA5E0, rva007B775E )
// ?rva007B777C@@YAXXZ @ 0x007B777C (10B) and ?rva007ADCC4@Rva007AD348PoolInits@@SAXXZ @ 0x007ADCC4 (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B777C, g_freelistPool00DB8FEC )
POOL_INIT( rva007ADCC4, g_freelistPool00DB8FEC, rva007B777C )
// ?rva007B77D8@@YAXXZ @ 0x007B77D8 (10B) and ?rva007ADE98@Rva007AD348PoolInits@@SAXXZ @ 0x007ADE98 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B77D8, g_freelistPool00DBA5E0 )
POOL_INIT( rva007ADE98, g_freelistPool00DBA5E0, rva007B77D8 )
// ?rva007B7892@@YAXXZ @ 0x007B7892 (10B) and ?rva007AE053@Rva007AD348PoolInits@@SAXXZ @ 0x007AE053 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B7892, g_freelistPool00DBA5E0 )
POOL_INIT( rva007AE053, g_freelistPool00DBA5E0, rva007B7892 )
// ?rva007B78C4@@YAXXZ @ 0x007B78C4 (10B) and ?rva007AE0B8@Rva007AD348PoolInits@@SAXXZ @ 0x007AE0B8 (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B78C4, g_freelistPool00DB8FEC )
POOL_INIT( rva007AE0B8, g_freelistPool00DB8FEC, rva007B78C4 )
// ?rva007B78BA@@YAXXZ @ 0x007B78BA (10B) and ?rva007AE0D2@Rva007AD348PoolInits@@SAXXZ @ 0x007AE0D2 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B78BA, g_freelistPool00DBA5E0 )
POOL_INIT( rva007AE0D2, g_freelistPool00DBA5E0, rva007B78BA )
// ?rva007B7900@@YAXXZ @ 0x007B7900 (10B) and ?rva007AE1AE@Rva007AD348PoolInits@@SAXXZ @ 0x007AE1AE (26B), pool VA 0x00DBBD2C
POOL_CLEANUP( rva007B7900, g_freelistPool009BBD2C )
POOL_INIT( rva007AE1AE, g_freelistPool009BBD2C, rva007B7900 )
// ?rva007B78EC@@YAXXZ @ 0x007B78EC (10B) and ?rva007AE1E2@Rva007AD348PoolInits@@SAXXZ @ 0x007AE1E2 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B78EC, g_freelistPool00DBA5E0 )
POOL_INIT( rva007AE1E2, g_freelistPool00DBA5E0, rva007B78EC )
// ?rva007B7B28@@YAXXZ @ 0x007B7B28 (10B) and ?rva007AE862@Rva007AD348PoolInits@@SAXXZ @ 0x007AE862 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B7B28, g_freelistPool00DBA5E0 )
POOL_INIT( rva007AE862, g_freelistPool00DBA5E0, rva007B7B28 )
// ?rva007B7C40@@YAXXZ @ 0x007B7C40 (10B) and ?rva007AEBCC@Rva007AD348PoolInits@@SAXXZ @ 0x007AEBCC (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B7C40, g_freelistPool00DBA5E0 )
POOL_INIT( rva007AEBCC, g_freelistPool00DBA5E0, rva007B7C40 )
// ?rva007B7CF5@@YAXXZ @ 0x007B7CF5 (10B) and ?rva007AEE7B@Rva007AD348PoolInits@@SAXXZ @ 0x007AEE7B (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B7CF5, g_freelistPool00DB8FEC )
POOL_INIT( rva007AEE7B, g_freelistPool00DB8FEC, rva007B7CF5 )
// ?rva007B7D59@@YAXXZ @ 0x007B7D59 (10B) and ?rva007AEFB1@Rva007AD348PoolInits@@SAXXZ @ 0x007AEFB1 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B7D59, g_freelistPool00DBA5E0 )
POOL_INIT( rva007AEFB1, g_freelistPool00DBA5E0, rva007B7D59 )
// ?rva007B7E0D@@YAXXZ @ 0x007B7E0D (10B) and ?rva007AF210@Rva007AD348PoolInits@@SAXXZ @ 0x007AF210 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B7E0D, g_freelistPool00DBA5E0 )
POOL_INIT( rva007AF210, g_freelistPool00DBA5E0, rva007B7E0D )
// ?rva007B7E21@@YAXXZ @ 0x007B7E21 (10B) and ?rva007AF254@Rva007AD348PoolInits@@SAXXZ @ 0x007AF254 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B7E21, g_freelistPool00DBA5E0 )
POOL_INIT( rva007AF254, g_freelistPool00DBA5E0, rva007B7E21 )
// ?rva007B81F7@@YAXXZ @ 0x007B81F7 (10B) and ?rva007AFEAC@Rva007AD348PoolInits@@SAXXZ @ 0x007AFEAC (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B81F7, g_freelistPool00DB8FEC )
POOL_INIT( rva007AFEAC, g_freelistPool00DB8FEC, rva007B81F7 )
// ?rva007B82BF@@YAXXZ @ 0x007B82BF (10B) and ?rva007B030B@Rva007AD348PoolInits@@SAXXZ @ 0x007B030B (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B82BF, g_freelistPool00DB8FEC )
POOL_INIT( rva007B030B, g_freelistPool00DB8FEC, rva007B82BF )
// ?rva007B8323@@YAXXZ @ 0x007B8323 (10B) and ?rva007B043B@Rva007AD348PoolInits@@SAXXZ @ 0x007B043B (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B8323, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B043B, g_freelistPool00DBA5E0, rva007B8323 )
// ?rva007B834B@@YAXXZ @ 0x007B834B (10B) and ?rva007B04C3@Rva007AD348PoolInits@@SAXXZ @ 0x007B04C3 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B834B, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B04C3, g_freelistPool00DBA5E0, rva007B834B )
// ?rva007B837D@@YAXXZ @ 0x007B837D (10B) and ?rva007B055B@Rva007AD348PoolInits@@SAXXZ @ 0x007B055B (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B837D, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B055B, g_freelistPool00DBA5E0, rva007B837D )
// ?rva007B843B@@YAXXZ @ 0x007B843B (10B) and ?rva007B0757@Rva007AD348PoolInits@@SAXXZ @ 0x007B0757 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B843B, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B0757, g_freelistPool00DBA5E0, rva007B843B )
// ?rva007B844F@@YAXXZ @ 0x007B844F (10B) and ?rva007B0800@Rva007AD348PoolInits@@SAXXZ @ 0x007B0800 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B844F, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B0800, g_freelistPool00DBA5E0, rva007B844F )
// ?rva007B8463@@YAXXZ @ 0x007B8463 (10B) and ?rva007B0844@Rva007AD348PoolInits@@SAXXZ @ 0x007B0844 (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B8463, g_freelistPool00DB8FEC )
POOL_INIT( rva007B0844, g_freelistPool00DB8FEC, rva007B8463 )
// ?rva007B8481@@YAXXZ @ 0x007B8481 (10B) and ?rva007B08C2@Rva007AD348PoolInits@@SAXXZ @ 0x007B08C2 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B8481, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B08C2, g_freelistPool00DBA5E0, rva007B8481 )
// ?rva007B84F9@@YAXXZ @ 0x007B84F9 (10B) and ?rva007B0AC4@Rva007AD348PoolInits@@SAXXZ @ 0x007B0AC4 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B84F9, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B0AC4, g_freelistPool00DBA5E0, rva007B84F9 )
// ?rva007B85B8@@YAXXZ @ 0x007B85B8 (10B) and ?rva007B0DF0@Rva007AD348PoolInits@@SAXXZ @ 0x007B0DF0 (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B85B8, g_freelistPool00DB8FEC )
POOL_INIT( rva007B0DF0, g_freelistPool00DB8FEC, rva007B85B8 )
// ?rva007B8697@@YAXXZ @ 0x007B8697 (10B) and ?rva007B1190@Rva007AD348PoolInits@@SAXXZ @ 0x007B1190 (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B8697, g_freelistPool00DB8FEC )
POOL_INIT( rva007B1190, g_freelistPool00DB8FEC, rva007B8697 )
// ?rva007B8769@@YAXXZ @ 0x007B8769 (10B) and ?rva007B143E@Rva007AD348PoolInits@@SAXXZ @ 0x007B143E (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B8769, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B143E, g_freelistPool00DBA5E0, rva007B8769 )
// ?rva007B881D@@YAXXZ @ 0x007B881D (10B) and ?rva007B16BD@Rva007AD348PoolInits@@SAXXZ @ 0x007B16BD (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B881D, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B16BD, g_freelistPool00DBA5E0, rva007B881D )
// ?rva007B88D1@@YAXXZ @ 0x007B88D1 (10B) and ?rva007B1931@Rva007AD348PoolInits@@SAXXZ @ 0x007B1931 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B88D1, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B1931, g_freelistPool00DBA5E0, rva007B88D1 )
// ?rva007B8C7D@@YAXXZ @ 0x007B8C7D (10B) and ?rva007B2784@Rva007AD348PoolInits@@SAXXZ @ 0x007B2784 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B8C7D, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B2784, g_freelistPool00DBA5E0, rva007B8C7D )
// ?rva007B8EA4@@YAXXZ @ 0x007B8EA4 (10B) and ?rva007B2EE6@Rva007AD348PoolInits@@SAXXZ @ 0x007B2EE6 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B8EA4, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B2EE6, g_freelistPool00DBA5E0, rva007B8EA4 )
// ?rva007B8ED6@@YAXXZ @ 0x007B8ED6 (10B) and ?rva007B2F78@Rva007AD348PoolInits@@SAXXZ @ 0x007B2F78 (26B), pool VA 0x00DBA5E0
POOL_CLEANUP( rva007B8ED6, g_freelistPool00DBA5E0 )
POOL_INIT( rva007B2F78, g_freelistPool00DBA5E0, rva007B8ED6 )
// ?rva007B9003@@YAXXZ @ 0x007B9003 (10B) and ?rva007B32F3@Rva007AD348PoolInits@@SAXXZ @ 0x007B32F3 (26B), pool VA 0x00DBBD2C
POOL_CLEANUP( rva007B9003, g_freelistPool009BBD2C )
POOL_INIT( rva007B32F3, g_freelistPool009BBD2C, rva007B9003 )
// ?rva007B9388@@YAXXZ @ 0x007B9388 (10B) and ?rva007B3D36@Rva007AD348PoolInits@@SAXXZ @ 0x007B3D36 (26B), pool VA 0x00DB8FEC
POOL_CLEANUP( rva007B9388, g_freelistPool00DB8FEC )
POOL_INIT( rva007B3D36, g_freelistPool00DB8FEC, rva007B9388 )
