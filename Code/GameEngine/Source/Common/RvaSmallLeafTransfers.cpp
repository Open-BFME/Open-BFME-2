// cl: /O2 /DNDEBUG /MD /EHsc
// BFME 1 donor: UnclaimedSmallLeaves02.cpp, revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76.
// The full donor TU was compiled under BFME 2 settings and searched in game.dat.
// Each body below has a unique placement and passes full-byte verification.
// Identity is not recovered: target-address names replace donor-address names.
// Field names describe target instructions; donor structure is the source lead.
// Lead arrays preserve only witnessed access offsets, not a complete layout.

// Target 0x007588E0, 28 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x009A2940; target instructions corroborate these accesses.
class Rva007588E0
{
public:
	void set( int value );

	char m_lead[ 0xC068 ];
	int m_value;
	char m_dirty;
};

void Rva007588E0::set( int value )
{
	if ( value != m_value )
	{
		m_value = value;
		m_dirty = 1;
	}
}

// Target 0x0073A360, 15 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x008F7DC0; target instructions corroborate these accesses.
class Rva0073A360
{
public:
	void clear( int index );

	char m_lead[ 0x24 ];
	int m_slots[ 1 ];
};

void Rva0073A360::clear( int index )
{
	m_slots[ index ] = 0;
}

// Target 0x00674B60, 14 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00808C10; target instructions corroborate these accesses.
struct Rva00674B60Record
{
	char m_lead[ 0x20 ];
	unsigned int m_20;
};

void __stdcall Rva00674B60( Rva00674B60Record *record )
{
	record->m_20 = 0xC0000000;
}

// Target 0x00758CA0, 13 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x009A2F20; target instructions corroborate these accesses.
class Rva00758CA0
{
public:
	int bit0() const;

	char m_lead[ 0xC ];
	unsigned int m_c;
};

int Rva00758CA0::bit0() const
{
	return ( m_c & 1 ) == 1;
}

// Target 0x0066E440, 13 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00802180; target instructions corroborate these accesses.
class Rva0066E440
{
public:
	__int64 get() const;

	char m_lead[ 0x90 ];
	__int64 m_90;
};

__int64 Rva0066E440::get() const
{
	return m_90;
}

// Target 0x0066E4A0, 12 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x008021F0; target instructions corroborate these accesses.
class Rva0066E4A0
{
public:
	void clear();

	int m_0;
	int m_4;
	char m_lead[ 0x1C ];
	int m_24;
	int m_28;
};

void Rva0066E4A0::clear()
{
	m_4 = 0;
	m_24 = 0;
	m_28 = 0;
}

// Target 0x0066F550, 12 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00803500; target instructions corroborate these accesses.
class Rva0066F550
{
public:
	void clear();

	char m_lead[ 0xC ];
	int m_c;
	int m_10;
	int m_14;
};

void Rva0066F550::clear()
{
	m_c = 0;
	m_10 = 0;
	m_14 = 0;
}

// Target 0x00699700, 11 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00858140; target instructions corroborate these accesses.
struct Rva00699700Record
{
	char m_lead[ 0x18D4 ];
	int m_18d4;
};

int Rva00699700( const Rva00699700Record *record )
{
	return record->m_18d4;
}

// Target 0x001B6330, 11 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x009A5870; target instructions corroborate these accesses.
struct Rva001B6330Record
{
	char m_lead[ 0x244 ];
	int m_244;
};

int Rva001B6330( const Rva001B6330Record *record )
{
	return record->m_244;
}

// Target 0x00665670, 11 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x007F90D0; target instructions corroborate these accesses.
class Rva00665670
{
public:
	void clear();

	int m_0;
	int m_4;
	int m_8;
};

void Rva00665670::clear()
{
	m_4 = 0;
	m_0 = 0;
	m_8 = 0;
}

// Target 0x00661D40, 11 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x007F5520; target instructions corroborate these accesses.
class Rva00661D40
{
public:
	int get() const;

	char m_lead[ 0x28 ];
	int m_28;
	int m_2c;
};

int Rva00661D40::get() const
{
	int value = m_2c;
	if ( !value )
		value = m_28;
	return value;
}

// Target 0x006D3840, 9 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x0089DCD0; target instructions corroborate these accesses.
class Rva006D3840
{
public:
	void clear();

	short *m_target;
};

void Rva006D3840::clear()
{
	m_target[ 3 ] = 0;
}

// Target 0x0019B080, 9 bytes; preceding ret 4 and aligned entry; terminal ret and int3 padding.
// Donor b1 RVA 0x00979380; target instructions corroborate these accesses.
class Rva0019B080
{
public:
	unsigned int flag() const;

	char m_lead[ 0x10 ];
	unsigned int m_10;
};

unsigned int Rva0019B080::flag() const
{
	return m_10 & 0x100000;
}

// Target 0x00614D60, 9 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x009E1250; target instructions corroborate these accesses.
class Rva00614D60
{
public:
	unsigned int flag() const;

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

unsigned int Rva00614D60::flag() const
{
	return m_4 & 0x80000000;
}

// Target 0x00758C90, 9 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x009A2F10; target instructions corroborate these accesses.
class Rva00758C90
{
public:
	unsigned int notBit0() const;

	char m_lead[ 0xC ];
	unsigned int m_c;
};

unsigned int Rva00758C90::notBit0() const
{
	return ~m_c & 1;
}

// Target 0x00020EA0, 8 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x0084DC00; target instructions corroborate these accesses.
char *Rva00020EA0( char *record )
{
	return record + 0x18;
}

// Target 0x00020EB0, 8 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x0084DC10; target instructions corroborate these accesses.
char *Rva00020EB0( char *record )
{
	return record + 0x1D;
}

// Target 0x00020EE0, 8 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x0084DC60; target instructions corroborate these accesses.
char *Rva00020EE0( char *record )
{
	return record + 0x28;
}

// Target 0x00020EF0, 8 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x0084DC70; target instructions corroborate these accesses.
char *Rva00020EF0( char *record )
{
	return record + 0x23;
}

// Target 0x00020F00, 8 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x0084DC80; target instructions corroborate these accesses.
char Rva00020F00( const char *record )
{
	return record[ 0x34 ];
}

// Target 0x00020F10, 8 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x0084DC90; target instructions corroborate these accesses.
char Rva00020F10( const char *record )
{
	return record[ 0x30 ];
}

// Target 0x00030A20, 8 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00897230; target instructions corroborate these accesses.
char *Rva00030A20( char *block )
{
	return block - 8;
}

// Target 0x00665A30, 8 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x007F9490; target instructions corroborate these accesses.
class Rva00665A30
{
public:
	int increment();

	char m_lead[ 0xC ];
	int m_c;
};

int Rva00665A30::increment()
{
	return ++m_c;
}

// BF1 donor revision 775a0370b7, game/GameEngine/Source/Common/Rva007F90B0.cpp.
// Whole donor TU compiled; its independent first-word getter has no unique
// target placement. This unit adds only the supported copy body.
// Target-native ABI view only: ECX receiver, one four-byte stack argument,
// reads the other word at +4, writes only receiver +4, returns receiver,
// and pops 4 bytes. Original class/prototype and complete layout are unknown.
class Rva00665660
{
public:
    Rva00665660 *copyWord4(const Rva00665660 *other);
private:
    char m_unmodelled0[4];
    unsigned int m_word4;
};
Rva00665660 *Rva00665660::copyWord4(const Rva00665660 *other)
{
    m_word4 = other->m_word4;
    return this;
}

// BFME1 donor revision 775a0370b7:
// game/GameEngine/Source/GameNetwork/Rva007F4850FieldReset.cpp, full unit.
// Target 0x00661300/15 is padding-isolated: its only writes zero the four
// receiver words at +8, +C, +10 and +14. It returns without stack arguments.
// This unsigned-word ABI view preserves those bit writes only; original
// field types, owner identity and full layout are not established.
class Rva00661300
{
public:
    void clearWords8();
private:
    char m_unmodelled0[8];
    unsigned int m_words8[4];
};
void Rva00661300::clearWords8()
{
    for (int i=0;i<4;++i) m_words8[i]=0;
}

// BFME1 donor revision 775a0370b7:
// game/GameEngine/Source/Common/Rva00801040Accessors.cpp, whole unit compiled.
// Its sole supported new placement is this 0x0066D470/13 body. Native reads
// +128 into EAX and +12C into EDX, then returns; both boundaries have padding.
// An unsigned 64-bit view preserves that return bit pattern. Signedness,
// original field/owner types and full object layout remain unestablished.
class Rva0066D470
{
public:
    unsigned __int64 readWord128() const;
private:
    char m_unmodelled0[0x128];
    unsigned __int64 m_word128;
};
unsigned __int64 Rva0066D470::readWord128() const
{
    return m_word128;
}

// BFME1 775a0370b7 whole-unit leads Rva007FD000OffsetGetter.cpp and
// Bfme/Rva007FBBA0FieldGet.cpp agree on the bit operation but disagree on
// original member/static and signed/unsigned prototypes. Preserve that doubt.
// Native 0x006680B0/10 ignores ECX, reads first-stack-pointer +20 into EAX,
// then pops 4 bytes. Two retail tables reference it (CE36A8 and CE393C).
// This C-linkage callee-pop ABI view models those observed stack bytes only;
// it does not assert an original static/member identity, virtual prototype,
// field signedness or owner. The input projection describes only the read.
struct Rva006680B0WordView
{
    char m_unmodelled0[0x20];
    unsigned m_word20;
};
extern "C" unsigned __stdcall Rva006680B0(const Rva006680B0WordView *target)
{
    return target->m_word20;
}

// BFME1 775a0370b7 whole-unit lead Rva007FD010OffsetGetter.cpp.
// Native 0x00669500/13 ignores ECX and the second stack word, reads the
// first-stack-pointer +29C into EAX, and pops 8 bytes. Retail table CE3944
// references it. Preserve the unknown original virtual/member prototype.
// This C-linkage stack-ABI projection preserves only that return bit pattern;
// field signedness, input owner and complete layout are not established.
struct Rva00669500WordView
{
    char m_unmodelled0[0x29c];
    unsigned m_word29C;
};
extern "C" unsigned __stdcall Rva00669500(const Rva00669500WordView *target, unsigned)
{
    return target->m_word29C;
}

// Whole BFME1 donor: 5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/BfmeConv1047.cpp; native compiler profile.
// The donor calls its matching emitted body a word-value constructor. Target
// evidence establishes only this standalone ABI: the preceding function ends
// at 23425C; 23425D stores the low stack word through ECX, returns that receiver
// in EAX, and pops four bytes; the next body begins at 23426A. No native caller
// or address reference proves a constructor, original type, owner or lifetime.
// Preserve just the word bits and observed return in this address-based view.
class Rva0023425D
{
public:
    Rva0023425D *storeWord(unsigned short bits);
private:
    unsigned short m_word;
};
Rva0023425D *Rva0023425D::storeWord(unsigned short bits)
{
    m_word=bits;
    return this;
}

// Whole donor lead: official BFME 1 5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/Bfme5ClearsWithTails.cpp, original settings.
// Native 0x421A4B is a separate 12-byte body between the ret 8 ending at
// 0x421A4A and Ghidra's next function at 0x421A57. It loads receiver word 0,
// indexes four-byte slots with the stack word, and returns the slot bits.
// No calls or address references found. Donor vector/owned-element identities,
// pointee type, index signedness, original constness and full layout are unknown.
// This address-qualified read-only view models only those native bit accesses.
class Rva00421A4B
{
public:
    unsigned int readSlotBits(unsigned int index) const;
private:
    const unsigned int *m_slots00;
};

unsigned int Rva00421A4B::readSlotBits(unsigned int index) const
{
    return m_slots00[index];
}

// Incidental compiled lead: Rva00415A55Result's ABI-view constructor after
// the STLport insertion transfer. Target 0x5D5816/18 independently follows
// a terminal ret at 0x5D5815 and precedes a new prologue at 0x5D5828.
// It copies one full stack word to +0 and the low stack byte to +4, returning
// the receiver and ret8. No callers or address references establish original
// constructor/lifetime, word pointee, bool type or complete receiver layout.
// This minimum word/byte bit view therefore claims only those native stores.
// Local size optimization follows the emitting /O1 tree-result sibling.
#pragma optimize("s",on)
class Rva005D5816
{
public:
    Rva005D5816 *writeBits(unsigned int word,unsigned char byte);
private:
    unsigned int m_word00;
    unsigned char m_byte04;
};
Rva005D5816 *Rva005D5816::writeBits(unsigned int word,unsigned char byte)
{
    m_word00=word;
    m_byte04=byte;
    return this;
}

#pragma optimize("",on)

// Whole clean BFME 1 donor Rva00872950.cpp, GameNetwork/GameSpy,
// at 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 supplies the counter pattern.
// Native 006B2150/29 has preceding INT3s, two terminal RETs and trailing INT3;
// every absolute operand names VA E0C0EC. Target data xrefs witness exactly
// four bytes with two- and four-byte accesses; its loaded initial value is 0.
// The union records those access widths. Native EAX retains the old dword on
// both exits; original function name, declared return type and owner are unknown.
union Rva00A0C0ECStorage
{
    unsigned int m_dword;
    unsigned short m_word;
};
Rva00A0C0ECStorage g_00E0C0EC;

unsigned int Rva006B2150()
{
    unsigned int value = g_00E0C0EC.m_dword;
    if ((unsigned short)value == 0xffff)
        g_00E0C0EC.m_word = 1;
    else
        ++g_00E0C0EC.m_word;
    return value;
}

// Whole clean BFME 1 Gen_006eab10_Clamp.cpp donor at 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24.
// Native 0004538C/32 is a complete RET8 body, referenced by retail callback
// table operand 007C3DD0. It compares a signed dword at VA DE1B28, clears it
// when positive, otherwise stores the first stack word, and returns AL=1.
// Data xrefs and the loaded image establish four zero-initialized bytes.
// Callback purpose, ignored second word's original type, and global owner
// remain unknown; the donor's clamp name is not promoted to a target identity.
int g_00DE1B28;

#pragma optimize("s",on)
bool __stdcall Rva0004538C(int value, unsigned int)
{
    if (g_00DE1B28 > 0)
        g_00DE1B28 = 0;
    else
        g_00DE1B28 = value;
    return true;
}
#pragma optimize("",on)

// Whole clean BFME 1 S1InequalityPredicates.cpp donor at
// 6583b3c1ff21db4a561285717028fdafc780b7db. Whole-unit /O2 and /O1 trials
// supplied these two independently verified placements; the other donor bodies
// supplied no supported unclaimed placement. There are no calls or new pins.
// Native 0066EA40/12 is INT3-isolated on both sides. It compares receiver
// word +8 with FFFFFFFE and returns precisely 0 or 1 in EAX. Neither that
// sentinel's meaning nor the original owner/type/name is established.
class Rva0066EA40
{
public:
    bool word8DiffersFromMinusTwo() const;
private:
    char m_unmodelled0[8];
    unsigned int m_word8;
};
bool Rva0066EA40::word8DiffersFromMinusTwo() const
{
    return m_word8 != 0xfffffffeU;
}

// Native 003807AA/13 lies between the RET at 3807A9 and the next Ghidra
// entry at 3807B7. It compares the four bytes at VA DC06A0 with
// FFFFFFFF and returns precisely 0 or 1 in EAX. The loaded value is -1;
// seven native absolute operands corroborate this shared global address.
// Reuse its existing link-clean TooltipHide definition and declared pointer
// representation; no original function purpose or pointee type is claimed.
extern void *TheRva00222A8BOwner;
#pragma optimize("s",on)
bool Rva003807AASentinelDiffers()
{
    return TheRva00222A8BOwner != (void *)-1;
}
#pragma optimize("",on)
