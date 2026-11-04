// cl: /O2 /Ob0
//
// File-scope records of two online services, in retail's .CRT$XCU order.
// Each record is three words { service type, name, code }. The out-of-line
// (int, int) constructor at 0x0065D090 (Rva007F0210Set.cpp) stores a service
// type global and a four-character code and leaves the name "".
// Its sibling at 0x0065D070 stores (type, name) and a zero code
// (Rva007B55E0TxnNameInits.cpp).
//
// For each object MSVC 7.1 emits one .text$yc dynamic initializer _$E<n>
// (mov eax, [type]; push code; push eax; mov ecx, &record; call ctor; ret)
// and a .CRT$XCU entry. Retail's table runs:
// - "msgr": 0x007B5E10..0x007B6170, after AUTH (StaticTagInitializerC6D010.cpp);
// - "thtr": 0x007B61A0..0x007B65E0.
// That is also the order of each service's record table (0x00DD8298 msgr,
// 0x00DD8320 thtr), so the objects are defined in it and the ordinals follow.
//
// The Open-BFME-1 donor (10af19f44a, StaticTagInitializers.cpp, b1
// 0x00C6D010..0x00C6D800) carried the same bodies as plain functions. tu_map
// assigns these records no TU, so the address-derived names stay.

class Rva007F0210
{
    int m_00;
    int m_04;
    int m_08;

public:
    Rva007F0210(int a, int b);
};

// The "msgr" service type, defined beside the msgr codec object in
// Rva007B5DE0StaticInstance.cpp.
extern int bfmeRva012C3B38TagValue;

Rva007F0210 bfmeRva0130A968TagSlot(bfmeRva012C3B38TagValue, 'DISC');	// VA 0x00E0A380
Rva007F0210 bfmeRva0130A8E4TagSlot(bfmeRva012C3B38TagValue, 'USCH');	// VA 0x00E0A2FC
Rva007F0210 bfmeRva0130A89CTagSlot(bfmeRva012C3B38TagValue, 'USER');	// VA 0x00E0A2B4
Rva007F0210 bfmeRva0130A938TagSlot(bfmeRva012C3B38TagValue, 'PADD');	// VA 0x00E0A350
Rva007F0210 bfmeRva0130A908TagSlot(bfmeRva012C3B38TagValue, 'PDEL');	// VA 0x00E0A320
Rva007F0210 bfmeRva0130A9A4TagSlot(bfmeRva012C3B38TagValue, 'PSET');	// VA 0x00E0A3BC
Rva007F0210 bfmeRva0130A920TagSlot(bfmeRva012C3B38TagValue, 'PGET');	// VA 0x00E0A338
Rva007F0210 bfmeRva0130A8CCTagSlot(bfmeRva012C3B38TagValue, 'RADD');	// VA 0x00E0A2E4
Rva007F0210 bfmeRva0130A878TagSlot(bfmeRva012C3B38TagValue, 'RADM');	// VA 0x00E0A290
Rva007F0210 bfmeRva0130A854TagSlot(bfmeRva012C3B38TagValue, 'RRSP');	// VA 0x00E0A26C
Rva007F0210 bfmeRva0130A914TagSlot(bfmeRva012C3B38TagValue, 'RDEL');	// VA 0x00E0A32C
Rva007F0210 bfmeRva0130A95CTagSlot(bfmeRva012C3B38TagValue, 'RDEM');	// VA 0x00E0A374
Rva007F0210 bfmeRva0130A92CTagSlot(bfmeRva012C3B38TagValue, 'RNOT');	// VA 0x00E0A344
Rva007F0210 bfmeRva0130A884TagSlot(bfmeRva012C3B38TagValue, 'RGET');	// VA 0x00E0A29C
Rva007F0210 bfmeRva0130A950TagSlot(bfmeRva012C3B38TagValue, 'ROST');	// VA 0x00E0A368
Rva007F0210 bfmeRva0130A980TagSlot(bfmeRva012C3B38TagValue, 'MLST');	// VA 0x00E0A398
Rva007F0210 bfmeRva0130A8D8TagSlot(bfmeRva012C3B38TagValue, 'TCKL');	// VA 0x00E0A2F0
Rva007F0210 bfmeRva0130A944TagSlot(bfmeRva012C3B38TagValue, 'GINV');	// VA 0x00E0A35C
Rva007F0210 bfmeRva0130A890TagSlot(bfmeRva012C3B38TagValue, 'GRSP');	// VA 0x00E0A2A8
Rva007F0210 bfmeRva0130A8B4TagSlot(bfmeRva012C3B38TagValue, 'GRVK');	// VA 0x00E0A2CC
Rva007F0210 bfmeRva0130A8C0TagSlot(bfmeRva012C3B38TagValue, 'GNOT');	// VA 0x00E0A2D8
Rva007F0210 bfmeRva0130A998TagSlot(bfmeRva012C3B38TagValue, 'SEND');	// VA 0x00E0A3B0
Rva007F0210 bfmeRva0130A974TagSlot(bfmeRva012C3B38TagValue, 'RECV');	// VA 0x00E0A38C
Rva007F0210 bfmeRva0130A860TagSlot(bfmeRva012C3B38TagValue, 'BRDC');	// VA 0x00E0A278
Rva007F0210 bfmeRva0130A8F0TagSlot(bfmeRva012C3B38TagValue, 'EPST');	// VA 0x00E0A308
Rva007F0210 bfmeRva0130A86CTagSlot(bfmeRva012C3B38TagValue, 'EPGT');	// VA 0x00E0A284
Rva007F0210 bfmeRva0130A8FCTagSlot(bfmeRva012C3B38TagValue, 'ADMN');	// VA 0x00E0A314
Rva007F0210 bfmeRva0130A8A8TagSlot(bfmeRva012C3B38TagValue, 'PING');	// VA 0x00E0A2C0

// The "thtr" service type: retail .data VA 0x00DD8318 holds 13514444 (VA 0x00CE36CC, "thtr").
int bfmeRva012C3BC0TagValue = 13514444;

Rva007F0210 bfmeRva0130A9C8TagSlot(bfmeRva012C3BC0TagValue, 'CONN');	// VA 0x00E0A3E0
Rva007F0210 bfmeRva0130AA1CTagSlot(bfmeRva012C3BC0TagValue, 'USER');	// VA 0x00E0A434
Rva007F0210 bfmeRva0130AAF4TagSlot(bfmeRva012C3BC0TagValue, 'RLST');	// VA 0x00E0A50C
Rva007F0210 bfmeRva0130A9D4TagSlot(bfmeRva012C3BC0TagValue, 'RDAT');	// VA 0x00E0A3EC
Rva007F0210 bfmeRva0130A9BCTagSlot(bfmeRva012C3BC0TagValue, 'LLST');	// VA 0x00E0A3D4
Rva007F0210 bfmeRva0130A9F8TagSlot(bfmeRva012C3BC0TagValue, 'LDAT');	// VA 0x00E0A410
Rva007F0210 bfmeRva0130AB48TagSlot(bfmeRva012C3BC0TagValue, 'GLST');	// VA 0x00E0A560
Rva007F0210 bfmeRva0130AAACTagSlot(bfmeRva012C3BC0TagValue, 'GDAT');	// VA 0x00E0A4C4
Rva007F0210 bfmeRva0130AAA0TagSlot(bfmeRva012C3BC0TagValue, 'GDET');	// VA 0x00E0A4B8
Rva007F0210 bfmeRva0130AA58TagSlot(bfmeRva012C3BC0TagValue, 'PDAT');	// VA 0x00E0A470
Rva007F0210 bfmeRva0130AADCTagSlot(bfmeRva012C3BC0TagValue, 'CGAM');	// VA 0x00E0A4F4
Rva007F0210 bfmeRva0130AA28TagSlot(bfmeRva012C3BC0TagValue, 'UGAM');	// VA 0x00E0A440
Rva007F0210 bfmeRva0130AAB8TagSlot(bfmeRva012C3BC0TagValue, 'UGDE');	// VA 0x00E0A4D0
Rva007F0210 bfmeRva0130AA10TagSlot(bfmeRva012C3BC0TagValue, 'UPLA');	// VA 0x00E0A428
Rva007F0210 bfmeRva0130AB3CTagSlot(bfmeRva012C3BC0TagValue, 'UBRA');	// VA 0x00E0A554
Rva007F0210 bfmeRva0130AA4CTagSlot(bfmeRva012C3BC0TagValue, 'EGAM');	// VA 0x00E0A464
Rva007F0210 bfmeRva0130AB30TagSlot(bfmeRva012C3BC0TagValue, 'EGEG');	// VA 0x00E0A548
Rva007F0210 bfmeRva0130AA34TagSlot(bfmeRva012C3BC0TagValue, 'ECNL');	// VA 0x00E0A44C
Rva007F0210 bfmeRva0130AB18TagSlot(bfmeRva012C3BC0TagValue, 'EGRQ');	// VA 0x00E0A530
Rva007F0210 bfmeRva0130AA64TagSlot(bfmeRva012C3BC0TagValue, 'EGRS');	// VA 0x00E0A47C
Rva007F0210 bfmeRva0130AB00TagSlot(bfmeRva012C3BC0TagValue, 'QLEN');	// VA 0x00E0A518
Rva007F0210 bfmeRva0130AAC4TagSlot(bfmeRva012C3BC0TagValue, 'PENT');	// VA 0x00E0A4DC
Rva007F0210 bfmeRva0130AA94TagSlot(bfmeRva012C3BC0TagValue, 'PLVT');	// VA 0x00E0A4AC
Rva007F0210 bfmeRva0130AA04TagSlot(bfmeRva012C3BC0TagValue, 'RGAM');	// VA 0x00E0A41C
Rva007F0210 bfmeRva0130AA88TagSlot(bfmeRva012C3BC0TagValue, 'PING');	// VA 0x00E0A4A0
Rva007F0210 bfmeRva0130AB0CTagSlot(bfmeRva012C3BC0TagValue, 'HOMG');	// VA 0x00E0A524
Rva007F0210 bfmeRva0130AAE8TagSlot(bfmeRva012C3BC0TagValue, 'HMRQ');	// VA 0x00E0A500
Rva007F0210 bfmeRva0130AB24TagSlot(bfmeRva012C3BC0TagValue, 'KICK');	// VA 0x00E0A53C
Rva007F0210 bfmeRva0130AA7CTagSlot(bfmeRva012C3BC0TagValue, 'GREM');	// VA 0x00E0A494
Rva007F0210 bfmeRva0130A9ECTagSlot(bfmeRva012C3BC0TagValue, 'KGAM');	// VA 0x00E0A404
Rva007F0210 bfmeRva0130AA40TagSlot(bfmeRva012C3BC0TagValue, 'ABUS');	// VA 0x00E0A458
Rva007F0210 bfmeRva0130AA70TagSlot(bfmeRva012C3BC0TagValue, 'DISC');	// VA 0x00E0A488
Rva007F0210 bfmeRva0130AAD0TagSlot(bfmeRva012C3BC0TagValue, 'RESV');	// VA 0x00E0A4E8
Rva007F0210 bfmeRva0130A9B0TagSlot(bfmeRva012C3BC0TagValue, 'KEEP');	// VA 0x00E0A3C8
Rva007F0210 bfmeRva0130A9E0TagSlot(bfmeRva012C3BC0TagValue, 'HGAM');	// VA 0x00E0A3F8
