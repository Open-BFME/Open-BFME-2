// cl: /O2 /MD
//
// Static initializers for 62 online-service transaction names (0x007B55E0..
// 0x007B5DC0). Each constructs a 12-byte { type, name, 0 } record in .bss from
// a service type held in a const char * global ("acct", "blob", "fdbk",
// "rank", "recp", "club", "fsys") and a literal transaction name ("Login",
// "AddAccount", "GetTopN", "Hello", ...), through the 25-byte constructor at
// 0x0065D070. That body is ICF-folded with CollisionTestClass(CastResultStruct
// *, int), which stores the same three fields; the record type is not
// recovered, so it keeps an honest address name and the constructor is bound
// by an alias pin. Native rank/UpdateStats65F2B0 reads the +4 name pointer; each service's seven
// to twenty records are one owning unit's file-scope objects, unrecovered.

struct Rva007B55E0TxnName
{
	Rva007B55E0TxnName( const char *type, const char *name );
    // ?Rva007B55E0TxnName::Rva007B55E0TxnName present-unmatched
    // A no-op default construction keeps native zero-filled storage intact;
    // the existing explicit initialization below supplies the two pointers.
    Rva007B55E0TxnName() {}

	const char *m_type;
	const char *m_name;
	int m_reserved;
};

extern const char *g_Va00DD7F48;	// "acct"
extern const char *g_Va00DD80AC;	// "blob"
extern const char *g_Va00DD80DC;	// "fdbk"
extern const char *g_Va00DD80EC;	// "rank"
extern const char *g_Va00DD8120;	// "recp"
extern const char *g_Va00DD8138;	// "club"
extern const char *g_Va00DD816C;	// "fsys"

extern Rva007B55E0TxnName g_Va00E09F24;
extern Rva007B55E0TxnName g_Va00E09F0C;
extern Rva007B55E0TxnName g_Va00E09EF4;
extern Rva007B55E0TxnName g_Va00E09F30;
extern Rva007B55E0TxnName g_Va00E09F3C;
extern Rva007B55E0TxnName g_Va00E09F18;
extern Rva007B55E0TxnName g_Va00E09F90;
extern Rva007B55E0TxnName g_Va00E09EAC;
extern Rva007B55E0TxnName g_Va00E09ED0;
extern Rva007B55E0TxnName g_Va00E09F60;
extern Rva007B55E0TxnName g_Va00E09F48;
extern Rva007B55E0TxnName g_Va00E09EB8;
extern Rva007B55E0TxnName g_Va00E09F78;
extern Rva007B55E0TxnName g_Va00E09EDC;
extern Rva007B55E0TxnName g_Va00E09F54;
extern Rva007B55E0TxnName g_Va00E09EC4;
extern Rva007B55E0TxnName g_Va00E09EE8;
extern Rva007B55E0TxnName g_Va00E09F84;
extern Rva007B55E0TxnName g_Va00E09F00;
extern Rva007B55E0TxnName g_Va00E09F6C;
extern Rva007B55E0TxnName g_Va00E09FE8;
extern Rva007B55E0TxnName g_Va00E0A000;
extern Rva007B55E0TxnName g_Va00E0A00C;
extern Rva007B55E0TxnName g_Va00E0A024;
extern Rva007B55E0TxnName g_Va00E09FDC;
extern Rva007B55E0TxnName g_Va00E0A018;
extern Rva007B55E0TxnName g_Va00E0A03C;
extern Rva007B55E0TxnName g_Va00E09FF4;
extern Rva007B55E0TxnName g_Va00E0A030;
extern Rva007B55E0TxnName g_Va00E09FD0;
extern Rva007B55E0TxnName g_Va00E0A054;
extern Rva007B55E0TxnName g_Va00E0A048;
extern Rva007B55E0TxnName g_Va00E0A0CC;
extern Rva007B55E0TxnName g_Va00E0A060;
extern Rva007B55E0TxnName g_Va00E0A06C;
extern Rva007B55E0TxnName g_Va00E0A078;
// Native zero-filled12B rank/UpdateStats record; rva007B5AA0 owns its
// explicit type/name setup. The rank request shares this same provider.
Rva007B55E0TxnName TheRankUpdateStatsTransaction;
extern Rva007B55E0TxnName g_Va00E0A084;
extern Rva007B55E0TxnName g_Va00E0A0D8;
extern Rva007B55E0TxnName g_Va00E0A09C;
extern Rva007B55E0TxnName g_Va00E0A0C0;
extern Rva007B55E0TxnName g_Va00E0A090;
extern Rva007B55E0TxnName g_Va00E0A0B4;
extern Rva007B55E0TxnName g_Va00E0A0E4;
extern Rva007B55E0TxnName g_Va00E0A0F0;
extern Rva007B55E0TxnName g_Va00E0A0FC;
extern Rva007B55E0TxnName g_Va00E0A108;
extern Rva007B55E0TxnName g_Va00E0A120;
extern Rva007B55E0TxnName g_Va00E0A12C;
extern Rva007B55E0TxnName g_Va00E0A144;
extern Rva007B55E0TxnName g_Va00E0A138;
extern Rva007B55E0TxnName g_Va00E0A174;
extern Rva007B55E0TxnName g_Va00E0A180;
extern Rva007B55E0TxnName g_Va00E0A18C;
extern Rva007B55E0TxnName g_Va00E0A168;
extern Rva007B55E0TxnName g_Va00E0A15C;
extern Rva007B55E0TxnName g_Va00E0A150;
extern Rva007B55E0TxnName g_Va00E0A114;
extern Rva007B55E0TxnName g_Va00E0A1A4;
extern Rva007B55E0TxnName g_Va00E0A1BC;
extern Rva007B55E0TxnName g_Va00E0A198;
extern Rva007B55E0TxnName g_Va00E0A1B0;

struct Rva007B55E0TxnInits
{
	static void rva007B55E0();
	static void rva007B5600();
	static void rva007B5620();
	static void rva007B5640();
	static void rva007B5660();
	static void rva007B5680();
	static void rva007B56A0();
	static void rva007B56C0();
	static void rva007B56E0();
	static void rva007B5700();
	static void rva007B5720();
	static void rva007B5740();
	static void rva007B5760();
	static void rva007B5780();
	static void rva007B57A0();
	static void rva007B57C0();
	static void rva007B57E0();
	static void rva007B5800();
	static void rva007B5820();
	static void rva007B5840();
	static void rva007B58A0();
	static void rva007B58C0();
	static void rva007B58E0();
	static void rva007B5900();
	static void rva007B5920();
	static void rva007B5940();
	static void rva007B5960();
	static void rva007B5980();
	static void rva007B59A0();
	static void rva007B59C0();
	static void rva007B59E0();
	static void rva007B5A00();
	static void rva007B5A20();
	static void rva007B5A40();
	static void rva007B5A60();
	static void rva007B5A80();
	static void rva007B5AA0();
	static void rva007B5AC0();
	static void rva007B5AE0();
	static void rva007B5B00();
	static void rva007B5B20();
	static void rva007B5B40();
	static void rva007B5B60();
	static void rva007B5B80();
	static void rva007B5BA0();
	static void rva007B5BC0();
	static void rva007B5BE0();
	static void rva007B5C00();
	static void rva007B5C20();
	static void rva007B5C40();
	static void rva007B5C60();
	static void rva007B5C80();
	static void rva007B5CA0();
	static void rva007B5CC0();
	static void rva007B5CE0();
	static void rva007B5D00();
	static void rva007B5D20();
	static void rva007B5D40();
	static void rva007B5D60();
	static void rva007B5D80();
	static void rva007B5DA0();
	static void rva007B5DC0();
};

// ?rva007B55E0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B55E0 (22B): acct/Login
void Rva007B55E0TxnInits::rva007B55E0()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F24.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "Login" );
}

// ?rva007B5600@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5600 (22B): acct/AddAccount
void Rva007B55E0TxnInits::rva007B5600()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F0C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "AddAccount" );
}

// ?rva007B5620@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5620 (22B): acct/AddSubAccount
void Rva007B55E0TxnInits::rva007B5620()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09EF4.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "AddSubAccount" );
}

// ?rva007B5640@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5640 (22B): acct/DisableSubAccount
void Rva007B55E0TxnInits::rva007B5640()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F30.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "DisableSubAccount" );
}

// ?rva007B5660@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5660 (22B): acct/SendAccountName
void Rva007B55E0TxnInits::rva007B5660()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F3C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "SendAccountName" );
}

// ?rva007B5680@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5680 (22B): acct/SendPassword
void Rva007B55E0TxnInits::rva007B5680()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F18.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "SendPassword" );
}

// ?rva007B56A0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B56A0 (22B): acct/GetCountryList
void Rva007B55E0TxnInits::rva007B56A0()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F90.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetCountryList" );
}

// ?rva007B56C0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B56C0 (22B): acct/GetTos
void Rva007B55E0TxnInits::rva007B56C0()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09EAC.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetTos" );
}

// ?rva007B56E0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B56E0 (22B): acct/SuggestScreenNames
void Rva007B55E0TxnInits::rva007B56E0()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09ED0.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "SuggestScreenNames" );
}

// ?rva007B5700@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5700 (22B): acct/SuggestSubScreenNames
void Rva007B55E0TxnInits::rva007B5700()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F60.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "SuggestSubScreenNames" );
}

// ?rva007B5720@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5720 (22B): acct/RegisterGame
void Rva007B55E0TxnInits::rva007B5720()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F48.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "RegisterGame" );
}

// ?rva007B5740@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5740 (22B): acct/LoginSubAccount
void Rva007B55E0TxnInits::rva007B5740()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09EB8.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "LoginSubAccount" );
}

// ?rva007B5760@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5760 (22B): acct/UpdatePassword
void Rva007B55E0TxnInits::rva007B5760()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F78.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdatePassword" );
}

// ?rva007B5780@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5780 (22B): acct/GetAccount
void Rva007B55E0TxnInits::rva007B5780()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09EDC.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetAccount" );
}

// ?rva007B57A0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B57A0 (22B): acct/GetSubAccounts
void Rva007B55E0TxnInits::rva007B57A0()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F54.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetSubAccounts" );
}

// ?rva007B57C0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B57C0 (22B): acct/UpdateAccount
void Rva007B55E0TxnInits::rva007B57C0()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09EC4.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdateAccount" );
}

// ?rva007B57E0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B57E0 (22B): acct/GameSpyPreAuth
void Rva007B55E0TxnInits::rva007B57E0()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09EE8.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GameSpyPreAuth" );
}

// ?rva007B5800@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5800 (22B): acct/XBLLogin
void Rva007B55E0TxnInits::rva007B5800()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F84.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "XBLLogin" );
}

// ?rva007B5820@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5820 (22B): acct/XBLAddAccount
void Rva007B55E0TxnInits::rva007B5820()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F00.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "XBLAddAccount" );
}

// ?rva007B5840@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5840 (22B): acct/TransactionException
void Rva007B55E0TxnInits::rva007B5840()
{
	const char *type = g_Va00DD7F48;
	g_Va00E09F6C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "TransactionException" );
}

// ?rva007B58A0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B58A0 (22B): blob/AddBlob
void Rva007B55E0TxnInits::rva007B58A0()
{
	const char *type = g_Va00DD80AC;
	g_Va00E09FE8.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "AddBlob" );
}

// ?rva007B58C0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B58C0 (22B): blob/RemoveBlob
void Rva007B55E0TxnInits::rva007B58C0()
{
	const char *type = g_Va00DD80AC;
	g_Va00E0A000.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "RemoveBlob" );
}

// ?rva007B58E0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B58E0 (22B): blob/UpdateBlobInfo
void Rva007B55E0TxnInits::rva007B58E0()
{
	const char *type = g_Va00DD80AC;
	g_Va00E0A00C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdateBlobInfo" );
}

// ?rva007B5900@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5900 (22B): blob/UpdateBlobContent
void Rva007B55E0TxnInits::rva007B5900()
{
	const char *type = g_Va00DD80AC;
	g_Va00E0A024.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdateBlobContent" );
}

// ?rva007B5920@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5920 (22B): blob/UpdateBlobRating
void Rva007B55E0TxnInits::rva007B5920()
{
	const char *type = g_Va00DD80AC;
	g_Va00E09FDC.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdateBlobRating" );
}

// ?rva007B5940@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5940 (22B): blob/GetBlobInfo
void Rva007B55E0TxnInits::rva007B5940()
{
	const char *type = g_Va00DD80AC;
	g_Va00E0A018.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetBlobInfo" );
}

// ?rva007B5960@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5960 (22B): blob/GetBlobContent
void Rva007B55E0TxnInits::rva007B5960()
{
	const char *type = g_Va00DD80AC;
	g_Va00E0A03C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetBlobContent" );
}

// ?rva007B5980@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5980 (22B): blob/ListBlobInfo
void Rva007B55E0TxnInits::rva007B5980()
{
	const char *type = g_Va00DD80AC;
	g_Va00E09FF4.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "ListBlobInfo" );
}

// ?rva007B59A0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B59A0 (22B): blob/TopNBlobDownloads
void Rva007B55E0TxnInits::rva007B59A0()
{
	const char *type = g_Va00DD80AC;
	g_Va00E0A030.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "TopNBlobDownloads" );
}

// ?rva007B59C0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B59C0 (22B): blob/TopNBlobRatings
void Rva007B55E0TxnInits::rva007B59C0()
{
	const char *type = g_Va00DD80AC;
	g_Va00E09FD0.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "TopNBlobRatings" );
}

// ?rva007B59E0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B59E0 (22B): fdbk/SendFeedback
void Rva007B55E0TxnInits::rva007B59E0()
{
	const char *type = g_Va00DD80DC;
	g_Va00E0A054.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "SendFeedback" );
}

// ?rva007B5A00@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5A00 (22B): fdbk/GetReputationScore
void Rva007B55E0TxnInits::rva007B5A00()
{
	const char *type = g_Va00DD80DC;
	g_Va00E0A048.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetReputationScore" );
}

// ?rva007B5A20@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5A20 (22B): rank/GetSessionId
void Rva007B55E0TxnInits::rva007B5A20()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A0CC.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetSessionId" );
}

// ?rva007B5A40@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5A40 (22B): rank/StartReport
void Rva007B55E0TxnInits::rva007B5A40()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A060.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "StartReport" );
}

// ?rva007B5A60@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5A60 (22B): rank/EndReport
void Rva007B55E0TxnInits::rva007B5A60()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A06C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "EndReport" );
}

// ?rva007B5A80@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5A80 (22B): rank/AddGameInfo
void Rva007B55E0TxnInits::rva007B5A80()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A078.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "AddGameInfo" );
}

// ?rva007B5AA0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5AA0 (22B): rank/UpdateStats
void Rva007B55E0TxnInits::rva007B5AA0()
{
	const char *type = g_Va00DD80EC;
	TheRankUpdateStatsTransaction.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdateStats" );
}

// ?rva007B5AC0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5AC0 (22B): rank/GetStats
void Rva007B55E0TxnInits::rva007B5AC0()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A084.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetStats" );
}

// ?rva007B5AE0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5AE0 (22B): rank/GetRankedStats
void Rva007B55E0TxnInits::rva007B5AE0()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A0D8.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetRankedStats" );
}

// ?rva007B5B00@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5B00 (22B): rank/GetTopN
void Rva007B55E0TxnInits::rva007B5B00()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A09C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetTopN" );
}

// ?rva007B5B20@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5B20 (22B): rank/GetTopNAndStats
void Rva007B55E0TxnInits::rva007B5B20()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A0C0.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetTopNAndStats" );
}

// ?rva007B5B40@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5B40 (22B): rank/GetDateRange
void Rva007B55E0TxnInits::rva007B5B40()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A090.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetDateRange" );
}

// ?rva007B5B60@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5B60 (22B): rank/TransactionException
void Rva007B55E0TxnInits::rva007B5B60()
{
	const char *type = g_Va00DD80EC;
	g_Va00E0A0B4.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "TransactionException" );
}

// ?rva007B5B80@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5B80 (22B): recp/AddRecord
void Rva007B55E0TxnInits::rva007B5B80()
{
	const char *type = g_Va00DD8120;
	g_Va00E0A0E4.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "AddRecord" );
}

// ?rva007B5BA0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5BA0 (22B): recp/GetRecord
void Rva007B55E0TxnInits::rva007B5BA0()
{
	const char *type = g_Va00DD8120;
	g_Va00E0A0F0.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetRecord" );
}

// ?rva007B5BC0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5BC0 (22B): recp/UpdateRecord
void Rva007B55E0TxnInits::rva007B5BC0()
{
	const char *type = g_Va00DD8120;
	g_Va00E0A0FC.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdateRecord" );
}

// ?rva007B5BE0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5BE0 (22B): recp/TransactionException
void Rva007B55E0TxnInits::rva007B5BE0()
{
	const char *type = g_Va00DD8120;
	g_Va00E0A108.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "TransactionException" );
}

// ?rva007B5C00@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5C00 (22B): club/AddClub
void Rva007B55E0TxnInits::rva007B5C00()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A120.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "AddClub" );
}

// ?rva007B5C20@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5C20 (22B): club/AddMember
void Rva007B55E0TxnInits::rva007B5C20()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A12C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "AddMember" );
}

// ?rva007B5C40@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5C40 (22B): club/ChangeMemberState
void Rva007B55E0TxnInits::rva007B5C40()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A144.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "ChangeMemberState" );
}

// ?rva007B5C60@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5C60 (22B): club/RemoveMember
void Rva007B55E0TxnInits::rva007B5C60()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A138.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "RemoveMember" );
}

// ?rva007B5C80@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5C80 (22B): club/UpdateMember
void Rva007B55E0TxnInits::rva007B5C80()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A174.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdateMember" );
}

// ?rva007B5CA0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5CA0 (22B): club/UpdateClub
void Rva007B55E0TxnInits::rva007B5CA0()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A180.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "UpdateClub" );
}

// ?rva007B5CC0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5CC0 (22B): club/RemoveClub
void Rva007B55E0TxnInits::rva007B5CC0()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A18C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "RemoveClub" );
}

// ?rva007B5CE0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5CE0 (22B): club/ListClubs
void Rva007B55E0TxnInits::rva007B5CE0()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A168.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "ListClubs" );
}

// ?rva007B5D00@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5D00 (22B): club/GetClub
void Rva007B55E0TxnInits::rva007B5D00()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A15C.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetClub" );
}

// ?rva007B5D20@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5D20 (22B): club/GetMembers
void Rva007B55E0TxnInits::rva007B5D20()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A150.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "GetMembers" );
}

// ?rva007B5D40@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5D40 (22B): club/TransactionException
void Rva007B55E0TxnInits::rva007B5D40()
{
	const char *type = g_Va00DD8138;
	g_Va00E0A114.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "TransactionException" );
}

// ?rva007B5D60@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5D60 (22B): fsys/Hello
void Rva007B55E0TxnInits::rva007B5D60()
{
	const char *type = g_Va00DD816C;
	g_Va00E0A1A4.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "Hello" );
}

// ?rva007B5D80@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5D80 (22B): fsys/Ping
void Rva007B55E0TxnInits::rva007B5D80()
{
	const char *type = g_Va00DD816C;
	g_Va00E0A1BC.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "Ping" );
}

// ?rva007B5DA0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5DA0 (22B): fsys/Goodbye
void Rva007B55E0TxnInits::rva007B5DA0()
{
	const char *type = g_Va00DD816C;
	g_Va00E0A198.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "Goodbye" );
}

// ?rva007B5DC0@Rva007B55E0TxnInits@@SAXXZ @ 0x007B5DC0 (22B): fsys/Suicide
void Rva007B55E0TxnInits::rva007B5DC0()
{
	const char *type = g_Va00DD816C;
	g_Va00E0A1B0.Rva007B55E0TxnName::Rva007B55E0TxnName( type, "Suicide" );
}
