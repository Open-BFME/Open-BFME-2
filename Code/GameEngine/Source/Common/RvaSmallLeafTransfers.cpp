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

// Whole clean BFME 1 UnclaimedSmallLeaves02.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705 emits these getters under the
// named Common O1/x87/G6 min5 sweep. Two donor address names agree per body;
// neither establishes an original target identity. Native independent 8-byte
// extents at 20EC0 and 20ED0 have INT3 padding on both sides, read the first
// stack pointer at +A/+E, and return only its byte in AL with caller cleanup.
// No direct call/jump or address references establish a richer prototype.
// Preserve unknown owner, semantic field names and original byte signedness;
// these minimal char views reproduce the actual AL bits and complete bytes.
char Rva00020EC0(const char *record)
{
    return record[0xA];
}

char Rva00020ED0(const char *record)
{
    return record[0xE];
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


// Clean BF1 f989 FXList.cpp O1/SSE2/G7 emits several hash-iterator names
// at this one placement, so no donor container identity is asserted.
// Native2B554B..2B5558 follows RET and precedes a new prologue; it takes
// stackarg4 as an output pointer, clears its first dword, writes ECX to
// its second dword, returns that output pointer in EAX, and pops4 bytes.
// Original owner, pointer meanings and hidden-return versus explicit-output
// source role remain unknown. This address-owned projection models only
// the witnessed eight output bytes and physical receiver/argument ABI.
// Native size-profile code joins the existing size-optimized leaf region;
// no new compiler override or pragma is introduced.
class Rva002B554BReceiver;
struct Rva002B554BOutput
{
    unsigned int zero;
    Rva002B554BReceiver *receiver;
};
class Rva002B554BReceiver
{
public:
    Rva002B554BOutput *writeOutput(Rva002B554BOutput *output);
};
Rva002B554BOutput *Rva002B554BReceiver::writeOutput(Rva002B554BOutput *output)
{
    output->zero = 0;
    output->receiver = this;
    return output;
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

// Whole BFME 1 UnclaimedSmallLeaves04.cpp at9cbfb551fe20dae985f91f2319d8997287b6a705
// emits this body under two opaque donor names in the named Common O1/x87/G6
// min5 sweep. Native66E460..66E467 is independently INT3-bounded and returns
// the ECX+8/+C words in EAX/EDX. No direct/address references establish an
// original owner, constness, signedness or full layout. The unsigned 64-bit
// projection preserves the witnessed bits; neighboring66E440/66E4A0 transfers
// already live in this whole-leaf donor home.
class Rva0066E460
{
public:
    unsigned __int64 readWord8() const;
private:
    char m_unmodelled0[8];
    unsigned __int64 m_word8;
};

unsigned __int64 Rva0066E460::readWord8() const
{
    return m_word8;
}

// Whole clean BF1 f989 Rva008FE900NullableField.cpp under O2/SSE2/G7
// supplies the nullable-word guide. Native135DD2..135DE0 starts immediately
// after the complete Camera::Apply RET at135DD1, ends at its own RET, and
// is followed by a distinct body. It loads receiver word0, returns pointed
// word8 when nonnull, otherwise returns FFFFFFFF in EAX with RET0.
// No original receiver, pointee, field purpose, sentinel meaning, signedness
// or constness is asserted; this consumed-prefix view preserves raw32 bits.
struct Rva00135DD2Inner
{
    char m_unmodelled0[8];
    unsigned m_word8;
};
class Rva00135DD2Field
{
public:
    unsigned get() const;
private:
    const Rva00135DD2Inner *m_data;
};
unsigned Rva00135DD2Field::get() const
{
    return m_data ? m_data->m_word8 : 0xffffffffU;
}

// Whole clean BF1 f989 MoneyGetMonetaryValueChar.cpp O2/SSE2/G7 emits this
// placement as a back-inserter postfix copy; the wide twin emits it too. No
// original template specialization or container identity is thereby proved.
// Native 0x199D0..0x199DB is INT3-bounded: ECX word0 is copied through the
// first stack pointer, that pointer returns in EAX, and RET8 discards two words.
// No native call/address xrefs refine the output's hidden-return versus
// explicit role or the ignored second word. Preserve only the physical ABI,
// raw32 transfer and unknown owner with this address-owned consumed-prefix view.
class Rva000199D0Receiver
{
public:
    unsigned int *writeWord(unsigned int *output, unsigned int) const;
private:
    unsigned int m_word0;
};
unsigned int *Rva000199D0Receiver::writeWord(unsigned int *output, unsigned int) const
{
    *output = m_word0;
    return output;
}

// Complete native 4DE536..4DE53C follows the preceding RET535 and is
// followed by the separately rowed cursor-advance leaf. Native ECX supplies
// an accessed prefix: raw DWORD+4 is copied to DWORD+0 and remains in EAX
// at RET0. No native call/address witness identifies its concrete owner.
// Clean BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d Common/Bfme/
// Rva001DB110Copy.cpp supplies the word-assignment expression. Its class
// and void source-role are donor facts only; this physical raw32 result
// view preserves the target's EAX bits without asserting a named owner,
// original prototype, field meanings, or common owner with nearby leaves.
class Rva004DE536WordPair {
public:
    unsigned int copy();
private:
    unsigned int word0;
    unsigned int word4;
};
unsigned int Rva004DE536WordPair::copy() {
    return word0 = word4;
}
