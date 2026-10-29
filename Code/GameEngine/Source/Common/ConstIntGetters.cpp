// B8-imm32 const-int returners: six-byte free functions with one shape:
//
//     mov eax,<IMM32> / ret
//
// Each stands on a CC-island (int3 before and after) with no Ghidra entry
// (dead emissions) and is carried in several .rdata vtable slots, so the
// address is a genuine shared virtual implementation whose class identity
// is not witnessed anywhere. Rows are named for their own address with the
// proven return value, following Rva0073B660False.cpp and the Disp family
// (address-derived names, identity unrecoverable from 6 bytes).
// No // cl: line (defaults match the frameless 6-byte shape).

extern const int g_emptyFieldParseTable[4];
#pragma comment(linker, "/alternatename:?opaqueCall@Rva00507552@@SAPAXXZ=?Rva00507552Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?opaqueCall@Rva005088C8@@SAPAXXZ=?Rva005088C8Get@@YAHXZ")

// ?Rva001820A0Get@@YAHXZ @ 0x001820A0 (6B): returns 8. CC-island
// (4xCC before, 8xCC after), 4 vtable refs in the 0x7D49xx-0x7D55xx mapper
// family, no direct callers, no branch sources.
int Rva001820A0Get(void)
{
	return 8;
}

// ?Rva00182D20Get@@YAHXZ @ 0x00182D20 (6B): returns 12. CC-island,
// 5 vtable refs in the same 0x7D3Fxx-0x7D56xx mapper family (each carrying
// it 13 slots after Rva001820A0Get), no direct callers, no branch sources.
int Rva00182D20Get(void)
{
	return 12;
}

// ?Rva0013C650Get@@YAHXZ @ 0x0013C650 (6B): returns 3. CC-island
// (7xCC before, 10xCC after) between the 0x13C630 environment-mapper ctor
// and 0x13C660, carried by 2 .rdata slots (one Vector3Randomizer vtable).
// The value matches CLASSID_SOLIDCYLINDER but the body also sits in an
// unrelated randomizer vtable slot, so the linker folded several const-3
// returners here and no single class identity is witnessed; the row stays
// address-derived. No direct callers, no branch sources.
int Rva0013C650Get(void)
{
	return 3;
}

// ?Rva00250000Get@@YAHXZ @ 0x00250000 (6B): returns 0x81. Follows a
// leave/ret (prev C3) with a larger B8-imm function immediately after,
// 7 .rdata refs across distant tables, no direct callers, no branch
// sources. Opaque address-derived name; the value is a plain integer
// (below any image base), not an address.
int Rva00250000Get(void)
{
	return 0x81;
}

// ?Rva0000C124CGet@@YAHXZ @ 0x0000C124C (6B): returns 0x000186A0.
// Follows sibling B8-6 0xC1246 (ret 0xBC5C20, itself leave/ret-prev) with
// a B8-imm/call function after. 6 .rdata refs, no direct callers, no
// branch sources. Opaque address-derived name.
int Rva0000C124CGet(void)
{
	return 0x000186A0;
}

// 0x0000C1246 is already claimed by twin (?name@Rva000C1246Named in
// W3DDrawNameGetters.cpp, a real string getter). Always grep the ledger
// in canonical 8-digit form before serving (",0x0*<ADDR>,"); add_match
// refusal is the backstop, never the plan.

// ?Rva0013C6C0Get@@YAHXZ @ 0x0013C6C0 (6B): returns 14. CC-island,
// carried at 0x7D31F0 in the same 0x7D31xx family table as Rva0013C650Get
// (10 slots later). 1 .rdata ref, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0013C6C0Get(void)
{
	return 14;
}

// ?Rva001820B0Get@@YAHXZ @ 0x001820B0 (6B): returns 9. CC-island
// neighbor 16 bytes after Rva001820A0Get (same mapper TU region), 2
// .rdata refs, no direct callers. Opaque address-derived name.
int Rva001820B0Get(void)
{
	return 9;
}

int Rva0056B767Get(void)
{
	return (int)g_emptyFieldParseTable;
}

// ?Rva004A6563Get@@YAHXZ @ 0x004A6563 (6B): returns 0x3FFFFFFF.
// Follows a ret (0x4A6562) with a B8-imm/call function after. Carried by
// 5 .rdata slots, no direct callers, no branch sources. The value is a
// plain small integer, not an address. Opaque address-derived name.
int Rva004A6563Get(void)
{
	return 0x3FFFFFFF;
}

// ?Rva0013D320Get@@YAHXZ @ 0x0013D320 (6B): returns 16. CC-island,
// carried at 0x7D32B0 and 0x7D720C in the 0x7Dxxxx mapper family tables,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0013D320Get(void)
{
	return 16;
}

// ?Rva001874D0Get@@YAHXZ @ 0x001874D0 (6B): returns 22. CC-island,
// carried at 0x7D50DC and 0x7D58B8 in the 0x7Dxxxx mapper family tables,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva001874D0Get(void)
{
	return 22;
}

// ?Rva001A13F0Get@@YAHXZ @ 0x001A13F0 (6B): returns 15. CC-island,
// carried at 0x7D3240 and 0x7D6A04 in the 0x7Dxxxx mapper family tables,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva001A13F0Get(void)
{
	return 15;
}

// ?Rva0013C770Get@@YAHXZ @ 0x0013C770 (6B): returns 17. CC-island
// (8xCC before and after), carried at 0x7D3268 in the 0x7D32xx mapper
// family tables (sibling of Rva0013C650Get/Rva0013C6C0Get), no direct
// callers, no branch sources. Opaque address-derived name.
int Rva0013C770Get(void)
{
	return 17;
}

// ?Rva0013DA70Get@@YAHXZ @ 0x0013DA70 (6B): returns 4. CC-island
// (8xCC before and after), carried at 0x7D32D8 in the 0x7D32xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0013DA70Get(void)
{
	return 4;
}

// ?Rva00166C10Get@@YAHXZ @ 0x00166C10 (6B): returns 6. Follows a C2-04-00
// ret with CC padding, 8xCC after, carried at 0x7D3FB4 in the 0x7D3Fxx
// mapper family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00166C10Get(void)
{
	return 6;
}

// ?Rva00175750Get@@YAHXZ @ 0x00175750 (6B): returns 26. CC-island
// (8xCC before and after), carried at 0x7D495C in the 0x7D49xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00175750Get(void)
{
	return 26;
}

// ?Rva001758B0Get@@YAHXZ @ 0x001758B0 (6B): returns 27. Follows a C2-04-00
// ret with CC padding, 8xCC after, carried at 0x7D4B6C in the 0x7D4Bxx
// mapper family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva001758B0Get(void)
{
	return 27;
}

// ?Rva00182A20Get@@YAHXZ @ 0x00182A20 (6B): returns 11. CC-island
// (8xCC before and after), carried at 0x7D5660 in the 0x7D56xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00182A20Get(void)
{
	return 11;
}

// ?Rva001830C0Get@@YAHXZ @ 0x001830C0 (6B): returns 13. CC-island
// (8xCC before and after), carried at 0x7D5700 in the 0x7D57xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva001830C0Get(void)
{
	return 13;
}

// ?Rva00183400Get@@YAHXZ @ 0x00183400 (6B): returns 19. CC-island
// (8xCC before and after), carried at 0x7D5740 in the 0x7D57xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00183400Get(void)
{
	return 19;
}

// ?Rva00186790Get@@YAHXZ @ 0x00186790 (6B): returns 18. CC-island
// (8xCC before and after), carried at 0x7D57FC in the 0x7D57xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00186790Get(void)
{
	return 18;
}

// ?Rva001869A0Get@@YAHXZ @ 0x001869A0 (6B): returns 20. CC-island
// (8xCC before and after), carried at 0x7D5824 in the 0x7D58xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva001869A0Get(void)
{
	return 20;
}

// ?Rva00187400Get@@YAHXZ @ 0x00187400 (6B): returns 21. CC-island
// (8xCC before and after), carried at 0x7D5890 in the 0x7D58xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00187400Get(void)
{
	return 21;
}

// ?Rva0019F020Get@@YAHXZ @ 0x0019F020 (6B): returns 25. CC-island
// (8xCC before and after), carried at 0x7D678C in the 0x7D67xx mapper
// family tables, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva0019F020Get(void)
{
	return 25;
}

// Established native providers now replace four obsolete entry-address literals.
// Keep the original opaque getter names and integer return representation.
class Rva0051268C; Rva0051268C *__stdcall Rva002D1E55Create(void *);
class Rva005173F8; Rva005173F8 *__stdcall Rva002D2025Create(void *);
class Rva0051BADF; Rva0051BADF *__stdcall Rva002D2099Create(void *);
class Rva0051D1E6; Rva0051D1E6 *__stdcall Rva002D210DCreate(void *);

// ?Rva00510D87Get@@YAHXZ @ 0x00510D87: existing verified return representation.
int Rva00510D87Get(void)
{
 return reinterpret_cast<int>(&Rva002D1E55Create);
}

// ?Rva00517F2BGet@@YAHXZ @ 0x00517F2B: existing verified return representation.
int Rva00517F2BGet(void)
{
 return reinterpret_cast<int>(&Rva002D2025Create);
}

// ?Rva0051BF27Get@@YAHXZ @ 0x0051BF27: existing verified return representation.
int Rva0051BF27Get(void)
{
 return reinterpret_cast<int>(&Rva002D2099Create);
}

// ?Rva0051D772Get@@YAHXZ @ 0x0051D772: existing verified return representation.
int Rva0051D772Get(void)
{
 return reinterpret_cast<int>(&Rva002D210DCreate);
}

// Moved back from ConstIntGettersAddr.cpp: their constants now name the globals the
// ledger defines there (declaration-only views; no layout is asserted).
struct FieldParse { const char *token; void (*parse)(class INI *, void *, void *, const void *); const void *userData; int offset; };
extern unsigned char *g_00DFEA50;
extern unsigned char *g_00DFE794;
extern const FieldParse g_00BE2C10[];
extern const FieldParse s_rva0033A8FCFieldTableB[];
class Rva003818B0List;
extern Rva003818B0List g_00E02310;

// ?Rva00201095Get@WeatherSetting@@UAEHXZ @ 0x00201095 (6B): returns 0x00BE2C10.
// Follows a tail-jmp/ret (0x20108F-94) with a frame-style function
// after. Carried at 0x7E306C, no direct callers, no branch sources.
// Opaque address-derived name.
class WeatherSetting { public: virtual int Rva00201095Get(); };

int WeatherSetting::Rva00201095Get()
{
	return (int)g_00BE2C10;
}

// ?Rva00200BBAGet@WaterTransparencySetting@@UAEHXZ @ 0x00200BBA (6B): returns 0x00C080B0.
// Follows a leave/ret plus a sibling B8-6 (pair, 6 apart) with a
// frame-style function after. Carried at 0x7E2BA0, no direct callers,
// no branch sources. Opaque address-derived name.
class WaterTransparencySetting
{
public:
	virtual int Rva00200BBAGet();
	static const FieldParse m_waterTransparencySettingFieldParseTable[];
};

int WaterTransparencySetting::Rva00200BBAGet()
{
	return (int)WaterTransparencySetting::m_waterTransparencySettingFieldParseTable;
}

// ?Rva0033A495Get@@YAHXZ @ 0x0033A495 (6B): returns 0x00C100C0.
// A leave/ret-8 pair ends at 0x33A490 with a 4-byte jmp fragment between it
// and this getter; no branch targets this address (phase-scanned
// 0x339000-0x33B000, only 4 direct E8 callers at 0x415231/0x4CB0A1/0x4CB642
// 0x4CBC1B, all pushing an extraOffset then feeding eax to a FieldParse
// add). The value is the VoiceSelect-led response table at 0xC100C0.
// Opaque address-derived name.
int Rva0033A495Get(void)
{
	return (int)s_rva0033A8FCFieldTableB;
}

// ?Rva00381452Get@@YAHXZ @ 0x00381452 (6B): returns 0x00E02310.
// Prev C3 with a frame-style function after. 4 direct E8 callers, no
// Ghidra entry (dead emission), no branch sources. Opaque name.
int Rva00381452Get(void)
{
	return (int)&g_00E02310;
}

// Existing compiled-ledger global at VA0x00E09F9C replaces the fixed image
// address; the getter remains the complete six-byte native body.
class Rva00CE12FCMutex;
extern Rva00CE12FCMutex g_rva00CE12FCMutex;
// ?Rva00656B60Get@@YAHXZ @ 0x00656B60 (6B): returns 0x00E09F9C.
// CC-island after a double-ret (xor-eax/ret then ret), 16 direct E8
// callers, Ghidra-6. The lone byte-scan branch hit (js at 0x656B4E) is a
// false decode: capstone shows 0x656B4C is mov [eax],0xCE1078 and the 78
// is its immediate byte. Opaque address-derived name.
int Rva00656B60Get(void)
{
	return (int)&g_rva00CE12FCMutex;
}

// Existing compiled-ledger global at VA0x00DD828C replaces the fixed image
// address; the getter remains the complete six-byte native body.
extern unsigned int g_Va00DD828C;
// ?Rva006655E0Get@@YAHXZ @ 0x006655E0 (6B): returns 0x00DD828C.
// CC-island (prev C3 then 6xCC, 10xCC after) between a C7-imm setter and
// the next setter. 1 direct E8 caller (0x6579D3), Ghidra-6, no branch
// sources. Opaque address-derived name.
int Rva006655E0Get(void)
{
	return (int)&g_Va00DD828C;
}

// Named address targets let these getters rejoin their linking family.
extern unsigned int g_Va00DD8314;
extern unsigned int g_Va00DD83B4;

// ?Rva003ABD55Get@@YAHXZ @ 0x003ABD55 (6B): returns 0x00C1C59C.
// Follows a ret (0x3ABD54) with a sub/cmp-style function after. Carried
// at 0x81CE5C and 0x81D680, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva003ABD55Get(void)
{
	return (int)"DefaultModule<CAT_PHYSICS>";
}

// ?Rva003AC9A1Get@@YAHXZ @ 0x003AC9A1 (6B): returns 0x00C1C96C.
// Follows a ret (0x3AC9A0) with a sub/cmp-style function after. Carried
// at 0x81C948 and 0x81D19C, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva003AC9A1Get(void)
{
	return (int)"DefaultParticleModule<CAT_COLOR>";
}

// ?Rva00342868Get@@YAHXZ @ 0x00342868 (6B): returns 0x00C12520.
// Follows a ret-4 (0x342865-67) with a push/call-style function after.
// Carried by 4 .rdata slots, no direct callers, no branch sources.
// Opaque address-derived name.
int Rva00342868Get(void)
{
	return (int)"AIMoveAndTightenState";
}

// ?Rva004EE155Get@@YAHXZ @ 0x004EE155 (6B): returns 0x00C62A38.
// Follows a mov-word/ret (0x4EE14F-54) with a frame-style function
// after. Carried at 0x862A30, no direct callers, no branch sources.
// Opaque address-derived name.
class Xfer;
class LivingWorldScoreKeeper { public: class PerTurnStats; };
class LivingWorldScoreKeeper::PerTurnStats
{
public:
	virtual ~PerTurnStats();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
};

const char *LivingWorldScoreKeeper::PerTurnStats::GetSnapshotName() const
{
	return "LivingWorldScoreKeeper::PerTurnStats";
}



// ?Rva00668100Get@@YAHXZ @ 0x00668100 (6B): returns 0x00DD8314.
// CC-island (10xCC after) following a call/leave/ret tail. 1 direct E8
// caller (0x657A78), Ghidra-6, no branch sources. Opaque name.
int Rva00668100Get(void)
{
	return reinterpret_cast<int>(&g_Va00DD8314);
}

// ?Rva00669530Get@@YAHXZ @ 0x00669530 (6B): returns 0x00DD83B4.
// CC-island (10xCC after) following a call/leave/ret tail. 1 direct E8
// caller (0x657B48), Ghidra-6, no branch sources. Opaque name.
int Rva00669530Get(void)
{
	return reinterpret_cast<int>(&g_Va00DD83B4);
}

// The LivingWorldObject parser at 0x0021376B supplies its object in ECX;
// WorldBuilder's twin also calls this through the object. Keep the method ABI
// and the field-table pointer return; the original method name is unknown.
struct FieldParse;
extern const FieldParse LivingWorldObjectFields[];
class Rva003FA776
{
public:
	const FieldParse *rva003FA6FF();
};
const FieldParse *Rva003FA776::rva003FA6FF()
{
	return LivingWorldObjectFields;
}
