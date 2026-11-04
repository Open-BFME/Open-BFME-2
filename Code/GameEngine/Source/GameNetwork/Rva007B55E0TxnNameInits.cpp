// cl: /O2 /MD
//
// 62 online-service transaction records (retail .CRT$XCU entries
// 0x007B55E0..0x007B5DC0), defined as file-scope objects in retail's table
// order. Each is a 12-byte { type, name, 0 } record in .bss. It is built from
// a service type held in a const char * global ("acct", "blob", "fdbk",
// "rank", "recp", "club", "fsys") and a literal transaction name ("Login",
// "AddAccount", "GetTopN", "Hello", ...) by the 25-byte constructor at
// 0x0065D070. For each object MSVC 7.1 emits one .text$yc dynamic initializer
// _$E<n> (mov eax, [type]; push name; push eax; mov ecx, &record; call ctor;
// ret) and its .CRT$XCU entry, with the ordinals stepping by two.
// The constructor body is ICF-folded with CollisionTestClass(CastResultStruct
// *, int), which stores the same three fields. It is compiled here and
// verified as an ICF twin of the rowed collision constructor. Its sibling
// 0x0065D090 stores { type, "", code } for the msgr/thtr records
// (StaticTagInitializers.cpp), so both are constructors of one three-word
// record whose type is not recovered; the names stay address-derived.
// Native rank/UpdateStats65F2B0 reads the +4 name pointer. The original
// owning classes and record names remain unrecovered; tu_map assigns these
// records no TU.

struct Rva007B55E0TxnName
{
	__declspec(noinline) Rva007B55E0TxnName( const char *type, const char *name );

	const char *m_type;
	const char *m_name;
	int m_reserved;
};

// The target constructor stores the two supplied pointers and clears +8.
// Its 25-byte body is shared with CollisionTestClass by retail ICF.
Rva007B55E0TxnName::Rva007B55E0TxnName(const char *type, const char *name)
    : m_type(type), m_name(name), m_reserved(0)
{
}

const char * g_Va00DD7F48 = "acct";	// retail RVA 0x009D7F48 (.data), defined here	// "acct"
const char * g_Va00DD80AC = "blob";	// retail RVA 0x009D80AC (.data), defined here	// "blob"
const char * g_Va00DD80DC = "fdbk";	// retail RVA 0x009D80DC (.data), defined here	// "fdbk"
const char * g_Va00DD80EC = "rank";	// retail RVA 0x009D80EC (.data), defined here	// "rank"
const char * g_Va00DD8120 = "recp";	// retail RVA 0x009D8120 (.data), defined here	// "recp"
const char * g_Va00DD8138 = "club";	// retail RVA 0x009D8138 (.data), defined here	// "club"
const char * g_Va00DD816C = "fsys";	// retail RVA 0x009D816C (.data), defined here	// "fsys"

// "acct" (retail .CRT$XCU 0x007B55E0..)
Rva007B55E0TxnName g_Va00E09F24( g_Va00DD7F48, "Login" );	// VA 0x00E09F24
Rva007B55E0TxnName g_Va00E09F0C( g_Va00DD7F48, "AddAccount" );	// VA 0x00E09F0C
Rva007B55E0TxnName g_Va00E09EF4( g_Va00DD7F48, "AddSubAccount" );	// VA 0x00E09EF4
Rva007B55E0TxnName g_Va00E09F30( g_Va00DD7F48, "DisableSubAccount" );	// VA 0x00E09F30
Rva007B55E0TxnName g_Va00E09F3C( g_Va00DD7F48, "SendAccountName" );	// VA 0x00E09F3C
Rva007B55E0TxnName g_Va00E09F18( g_Va00DD7F48, "SendPassword" );	// VA 0x00E09F18
Rva007B55E0TxnName g_Va00E09F90( g_Va00DD7F48, "GetCountryList" );	// VA 0x00E09F90
Rva007B55E0TxnName g_Va00E09EAC( g_Va00DD7F48, "GetTos" );	// VA 0x00E09EAC
Rva007B55E0TxnName g_Va00E09ED0( g_Va00DD7F48, "SuggestScreenNames" );	// VA 0x00E09ED0
Rva007B55E0TxnName g_Va00E09F60( g_Va00DD7F48, "SuggestSubScreenNames" );	// VA 0x00E09F60
Rva007B55E0TxnName g_Va00E09F48( g_Va00DD7F48, "RegisterGame" );	// VA 0x00E09F48
Rva007B55E0TxnName g_Va00E09EB8( g_Va00DD7F48, "LoginSubAccount" );	// VA 0x00E09EB8
Rva007B55E0TxnName g_Va00E09F78( g_Va00DD7F48, "UpdatePassword" );	// VA 0x00E09F78
Rva007B55E0TxnName g_Va00E09EDC( g_Va00DD7F48, "GetAccount" );	// VA 0x00E09EDC
Rva007B55E0TxnName g_Va00E09F54( g_Va00DD7F48, "GetSubAccounts" );	// VA 0x00E09F54
Rva007B55E0TxnName g_Va00E09EC4( g_Va00DD7F48, "UpdateAccount" );	// VA 0x00E09EC4
Rva007B55E0TxnName g_Va00E09EE8( g_Va00DD7F48, "GameSpyPreAuth" );	// VA 0x00E09EE8
Rva007B55E0TxnName g_Va00E09F84( g_Va00DD7F48, "XBLLogin" );	// VA 0x00E09F84
Rva007B55E0TxnName g_Va00E09F00( g_Va00DD7F48, "XBLAddAccount" );	// VA 0x00E09F00
Rva007B55E0TxnName g_Va00E09F6C( g_Va00DD7F48, "TransactionException" );	// VA 0x00E09F6C

// "blob" (retail .CRT$XCU 0x007B58A0..)
Rva007B55E0TxnName g_Va00E09FE8( g_Va00DD80AC, "AddBlob" );	// VA 0x00E09FE8
Rva007B55E0TxnName g_Va00E0A000( g_Va00DD80AC, "RemoveBlob" );	// VA 0x00E0A000
Rva007B55E0TxnName g_Va00E0A00C( g_Va00DD80AC, "UpdateBlobInfo" );	// VA 0x00E0A00C
Rva007B55E0TxnName g_Va00E0A024( g_Va00DD80AC, "UpdateBlobContent" );	// VA 0x00E0A024
Rva007B55E0TxnName g_Va00E09FDC( g_Va00DD80AC, "UpdateBlobRating" );	// VA 0x00E09FDC
Rva007B55E0TxnName g_Va00E0A018( g_Va00DD80AC, "GetBlobInfo" );	// VA 0x00E0A018
Rva007B55E0TxnName g_Va00E0A03C( g_Va00DD80AC, "GetBlobContent" );	// VA 0x00E0A03C
Rva007B55E0TxnName g_Va00E09FF4( g_Va00DD80AC, "ListBlobInfo" );	// VA 0x00E09FF4
Rva007B55E0TxnName g_Va00E0A030( g_Va00DD80AC, "TopNBlobDownloads" );	// VA 0x00E0A030
Rva007B55E0TxnName g_Va00E09FD0( g_Va00DD80AC, "TopNBlobRatings" );	// VA 0x00E09FD0

// "fdbk" (retail .CRT$XCU 0x007B59E0..)
Rva007B55E0TxnName g_Va00E0A054( g_Va00DD80DC, "SendFeedback" );	// VA 0x00E0A054
Rva007B55E0TxnName g_Va00E0A048( g_Va00DD80DC, "GetReputationScore" );	// VA 0x00E0A048

// "rank" (retail .CRT$XCU 0x007B5A20..)
Rva007B55E0TxnName g_Va00E0A0CC( g_Va00DD80EC, "GetSessionId" );	// VA 0x00E0A0CC
Rva007B55E0TxnName g_Va00E0A060( g_Va00DD80EC, "StartReport" );	// VA 0x00E0A060
Rva007B55E0TxnName g_Va00E0A06C( g_Va00DD80EC, "EndReport" );	// VA 0x00E0A06C
Rva007B55E0TxnName g_Va00E0A078( g_Va00DD80EC, "AddGameInfo" );	// VA 0x00E0A078
// rank/UpdateStats: the record native rank/UpdateStats65F2B0 reads.
Rva007B55E0TxnName TheRankUpdateStatsTransaction( g_Va00DD80EC, "UpdateStats" );	// VA 0x00E0A0A8
Rva007B55E0TxnName g_Va00E0A084( g_Va00DD80EC, "GetStats" );	// VA 0x00E0A084
Rva007B55E0TxnName g_Va00E0A0D8( g_Va00DD80EC, "GetRankedStats" );	// VA 0x00E0A0D8
Rva007B55E0TxnName g_Va00E0A09C( g_Va00DD80EC, "GetTopN" );	// VA 0x00E0A09C
Rva007B55E0TxnName g_Va00E0A0C0( g_Va00DD80EC, "GetTopNAndStats" );	// VA 0x00E0A0C0
Rva007B55E0TxnName g_Va00E0A090( g_Va00DD80EC, "GetDateRange" );	// VA 0x00E0A090
Rva007B55E0TxnName g_Va00E0A0B4( g_Va00DD80EC, "TransactionException" );	// VA 0x00E0A0B4

// "recp" (retail .CRT$XCU 0x007B5B80..)
Rva007B55E0TxnName g_Va00E0A0E4( g_Va00DD8120, "AddRecord" );	// VA 0x00E0A0E4
Rva007B55E0TxnName g_Va00E0A0F0( g_Va00DD8120, "GetRecord" );	// VA 0x00E0A0F0
Rva007B55E0TxnName g_Va00E0A0FC( g_Va00DD8120, "UpdateRecord" );	// VA 0x00E0A0FC
Rva007B55E0TxnName g_Va00E0A108( g_Va00DD8120, "TransactionException" );	// VA 0x00E0A108

// "club" (retail .CRT$XCU 0x007B5C00..)
Rva007B55E0TxnName g_Va00E0A120( g_Va00DD8138, "AddClub" );	// VA 0x00E0A120
Rva007B55E0TxnName g_Va00E0A12C( g_Va00DD8138, "AddMember" );	// VA 0x00E0A12C
Rva007B55E0TxnName g_Va00E0A144( g_Va00DD8138, "ChangeMemberState" );	// VA 0x00E0A144
Rva007B55E0TxnName g_Va00E0A138( g_Va00DD8138, "RemoveMember" );	// VA 0x00E0A138
Rva007B55E0TxnName g_Va00E0A174( g_Va00DD8138, "UpdateMember" );	// VA 0x00E0A174
Rva007B55E0TxnName g_Va00E0A180( g_Va00DD8138, "UpdateClub" );	// VA 0x00E0A180
Rva007B55E0TxnName g_Va00E0A18C( g_Va00DD8138, "RemoveClub" );	// VA 0x00E0A18C
Rva007B55E0TxnName g_Va00E0A168( g_Va00DD8138, "ListClubs" );	// VA 0x00E0A168
Rva007B55E0TxnName g_Va00E0A15C( g_Va00DD8138, "GetClub" );	// VA 0x00E0A15C
Rva007B55E0TxnName g_Va00E0A150( g_Va00DD8138, "GetMembers" );	// VA 0x00E0A150
Rva007B55E0TxnName g_Va00E0A114( g_Va00DD8138, "TransactionException" );	// VA 0x00E0A114

// "fsys" (retail .CRT$XCU 0x007B5D60..)
Rva007B55E0TxnName g_Va00E0A1A4( g_Va00DD816C, "Hello" );	// VA 0x00E0A1A4
Rva007B55E0TxnName g_Va00E0A1BC( g_Va00DD816C, "Ping" );	// VA 0x00E0A1BC
Rva007B55E0TxnName g_Va00E0A198( g_Va00DD816C, "Goodbye" );	// VA 0x00E0A198
Rva007B55E0TxnName g_Va00E0A1B0( g_Va00DD816C, "Suicide" );	// VA 0x00E0A1B0
