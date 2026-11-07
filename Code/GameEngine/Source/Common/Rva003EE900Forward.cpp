// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva003EE900@Rva003EE900@@QAEXH@Z @0x003EE900 26B.
// Forwarder to map-dispatch notify0C at 0x004E35D5: passes static
// AsciiString at 0x00E02E7C (HomeRegionHighlight) with (arg+0x54, 0).
// Owner map-holder sits at this+8 (same layout as Rva004E35D5Notify).
// Chain of Rva004E35D5Notify (160B); retail pushes 0, arg+0x54, string.
#include <map>
#include <vector>

typedef int Int;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class Rva004E35D5
{
public:
	void rva004E35D5(const AsciiString &key, Int a, bool b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35AF
{
public:
	void rva004E35AF(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35FF
{
public:
	void rva004E35FF(const AsciiString &key, Int a, Int b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

// These six target objects occupy the zero-filled .data tail. Their matched
// DIR32 references establish each VA, and each retail dynamic initializer
// (0x007AF8E3.. 0x007AF9AF) constructs its string from the effect name it
// pushes before registering the atexit cleanup. Retail's initializers call
// the out-of-line AsciiString(const char *) at 0x0000654A rather than
// expanding it, as in Rva007AB85CAtexitInits.cpp.
#pragma inline_depth( 0 )
// VA 0x00E02E7C (.data, zero-filled tail).
AsciiString g_Rva00E02E7C("HomeRegionHighlight");
// VA 0x00E02E78 (.data, zero-filled tail).
AsciiString g_Rva00E02E78("FilledOwnershipEffect");
// VA 0x00E02E80 (.data, zero-filled tail).
AsciiString g_Rva00E02E80("RegionSelectionEffect");
// VA 0x00E02E68 (.data, zero-filled tail).
AsciiString g_Rva00E02E68("MouseoverEffectFlareup");
// VA 0x00E02E6C (.data, zero-filled tail).
AsciiString g_Rva00E02E6C("MouseoutEffectFlareup");
// VA 0x00E02E64 (.data, zero-filled tail).
AsciiString g_Rva00E02E64("BordersEffect");
// VA 0x00E02E70 and 0x00E02E74 (.data, zero-filled tail): the conquered-region effect keys,
// built by retail initializers 0x007AF934 and 0x007AF94F between MouseoutEffectFlareup's
// and FilledOwnershipEffect's. Appended here so the earlier ordinals keep their rows.
AsciiString g_Va00E02E70("ConqueredEffectEvenglow");
AsciiString g_Va00E02E74("ConqueredEffectFlareup");
#pragma inline_depth()

class Rva003EE900
{
public:
	void rva003EE900(Int arg);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

class Rva003EE966
{
public:
	void rva003EE966(Int arg);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

class Rva003EEA9D
{
public:
	void rva003EEA9D(Int arg);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

// 0x003EE884 and 0x003EE84A: LivingWorldRegionEffectsManager::SyncRegion
// (0x003EF08B) calls both on its own this.
class LivingWorldRegionEffectsManager
{
public:
	void rva003EE884(Int arg);
	void rva003EE84A(Int regionAddress, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};

void Rva003EE900::rva003EE900(Int regionArg)
{
	m_owner.rva004E35D5(g_Rva00E02E7C, (Int)((char *)regionArg + 0x54), 0);
}

void LivingWorldRegionEffectsManager::rva003EE884(Int regionArg)
{
	m_owner.rva004E35D5(g_Rva00E02E78, (Int)((char *)regionArg + 0x54), 0);
}

void Rva003EE966::rva003EE966(Int regionArg)
{
	m_owner.rva004E35D5(g_Rva00E02E80, (Int)((char *)regionArg + 0x54), 0);
}

void Rva003EEA9D::rva003EEA9D(Int regionArg)
{
	m_owner.rva004E35D5(g_Rva00E02E68, (Int)((char *)regionArg + 0x54), 0);
}

void LivingWorldRegionEffectsManager::rva003EE84A(Int regionAddress, Int b)
{
	char *regionData = (char *)regionAddress + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E78, (Int)regionData, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E78, (Int)regionData, b);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E78, 0);
}

// ?rva003EEAB7@Rva003EEAB7@@QAEXXZ retail 0x003EEAB7 8B. Chain lane: tail-jmp
// thunk adjusting this by +8 into rowed Rva004E1F62::rva004E1F62 at
// 0x004E1F62; caller at 0x002123DC. Same m_pad[8]+owner layout as the
// Rva003EE900 family above; unblocks 0x002123BE/175.
struct Rva004E1F62 {
	void rva004E1F62();
};
class Rva003EEAB7
{
public:
	void rva003EEAB7();
private:
	char m_pad[8];
	Rva004E1F62 m_owner;
};
void Rva003EEAB7::rva003EEAB7()
{
	m_owner.rva004E1F62();
}

// ?rva003EE89E@Rva003EE89E@@QAEXHH@Z retail 0x003EE89E 58B. Unlock lane: same
// three-call forward as rva003EE84A above but with string g_Rva00E02E7C;
// callers at 0x003EE8F6/0x003EF120/0x0057DD5A; unblocks 3. Prev/next are the
// Rva003EE900 family in this TU.
class Rva003EE89E
{
public:
	void rva003EE89E(Int regionAddress, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE89E::rva003EE89E(Int regionAddress, Int b)
{
	char *regionData = (char *)regionAddress + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E7C, (Int)regionData, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E7C, (Int)regionData, b);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E7C, 0);
}

// ?rva003EEA63@Rva003EEA63@@QAEXHH@Z retail 0x003EEA63 58B. Unlock lane: same
// three-call forward as rva003EE84A/89E above but with string g_Rva00E02E68;
// callers at 0x003EEBE2/0x003EEF7F; unblocks 0x003EEBC4/0x003EEF38. Prev/next
// are the Rva003EE966/A9D family in this TU.
class Rva003EEA63
{
public:
	void rva003EEA63(Int regionAddress, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEA63::rva003EEA63(Int regionAddress, Int b)
{
	char *regionData = (char *)regionAddress + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E68, (Int)regionData, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E68, (Int)regionData, b);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E68, 0);
}

// ?rva003EEBC4@Rva003EEBC4@@QAEXHH@Z retail 0x003EEBC4 43B. Chain lane: calls
// rowed 0x004E3629 with string g_Rva00E02E68 then this session's 0x003EEA63,
// stores first arg at this+0x14; callers at 0x003EEE85/0x003EEF2E.
class Rva004E3629
{
public:
	void rva004E3629(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};
class Rva003EEBC4
{
public:
	void rva003EEBC4(Int regionAddress, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
	Int m_saved;
};
void Rva003EEBC4::rva003EEBC4(Int regionAddress, Int b)
{
	((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E68, 1);
	((Rva003EEA63 *)this)->rva003EEA63(regionAddress, b);
	m_saved = regionAddress;
}

// ?rva003EEE64@Rva003EEE64@@QAEXH@Z retail 0x003EEE64 42B. Chain lane: if
// this+0x14 nonzero calls rowed 0x004E3629 with string g_Rva00E02E6C then
// this session's 0x003EEBC4 with (m_saved X); caller at 0x003EF05C.
class Rva003EEE64
{
public:
	void rva003EEE64(Int x);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
	Int m_saved;
};
void Rva003EEE64::rva003EEE64(Int x)
{
	if (m_saved != 0) {
		((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E6C, 1);
		((Rva003EEBC4 *)this)->rva003EEBC4(m_saved, x);
	}
}

// ?rva003EEFA0@Rva003EEFA0@@QAEXH@Z retail 0x003EEFA0 59B. Unlock lane: loop
// over int array at arg (begin/end) calling rowed 0x003EEA9D for each nonzero;
// caller at 0x0057D79F. Prev is 0x003EEE64 in this TU.
class Rva003EEFA0
{
public:
	void rva003EEFA0(Int regionRangeAddress);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEFA0::rva003EEFA0(Int regionRangeAddress)
{
	Int *rangeWords = (Int *)regionRangeAddress;
	for (unsigned int regionIndex = 0; regionIndex < (unsigned int)((rangeWords[1] - rangeWords[0]) >> 2); ++regionIndex) {
		Int entry = *(Int *)(rangeWords[0] + regionIndex * 4);
		if (entry != 0)
			((Rva003EEA9D *)this)->rva003EEA9D(entry);
	}
}

// ?rva003EEA1A@Rva003EEA1A@@QAEXHH@Z retail 0x003EEA1A 73B. Unlock lane: four-
// call forward with strings g_Rva00E02E6C then g_Rva00E02E68; callers at
// 0x003EEBBB/0x003EEEF8; unblocks 0x003EEB9F/0x003EEEB3. Prev/next are the
// Rva003EE966/A63 family in this TU.
class Rva003EEA1A
{
public:
	void rva003EEA1A(Int regionAddress, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEA1A::rva003EEA1A(Int regionAddress, Int b)
{
	char *regionData = (char *)regionAddress + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E6C, (Int)regionData, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E6C, (Int)regionData, b);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E6C, 1);
	m_owner.rva004E35D5(g_Rva00E02E68, (Int)regionData, 0);
}

// ?rva003EEB9F@Rva003EEB9F@@QAEXHH@Z retail 0x003EEB9F 37B. Chain lane: calls
// rowed 0x004E3629 with string g_Rva00E02E6C then this session's 0x003EEA1A;
// caller at 0x003EEEA9.
class Rva003EEB9F
{
public:
	void rva003EEB9F(Int regionAddress, Int b);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEB9F::rva003EEB9F(Int regionAddress, Int b)
{
	((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E6C, 1);
	((Rva003EEA1A *)this)->rva003EEA1A(regionAddress, b);
}

// ?rva003EE7E1@Rva003EE7E1@@QAEXH@Z retail 0x003EE7E1 105B. Unlock lane: six
// calls to rowed 0x004E35D5 with strings 64/68/6C/78/7C/80 and (arg+0x54, 0);
// caller at 0x003EEE08.
class Rva003EE7E1
{
public:
	void rva003EE7E1(Int regionAddress);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE7E1::rva003EE7E1(Int regionAddress)
{
	char *regionData = (char *)regionAddress + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E64, (Int)regionData, 0);
	m_owner.rva004E35D5(g_Rva00E02E68, (Int)regionData, 0);
	m_owner.rva004E35D5(g_Rva00E02E6C, (Int)regionData, 0);
	m_owner.rva004E35D5(g_Rva00E02E78, (Int)regionData, 0);
	m_owner.rva004E35D5(g_Rva00E02E7C, (Int)regionData, 0);
	m_owner.rva004E35D5(g_Rva00E02E80, (Int)regionData, 0);
}

// ?rva003EE91A@Rva003EE91A@@QAEXH@Z @0x003EE91A 76B chain via landed 0x003EE7CA
// Retail: tmp[3] at ebp-0xc; this->rva003EE7CA(&tmp,arg) then owner+8 three-call
// forward with string 80 and (arg+0x54,1)/(arg+0x54,&tmp)/(80,0).
class Rva003EE7CA
{
public:
	int rva003EE7CA(int a, int b);
};
class Rva003EE91A
{
public:
	void rva003EE91A(Int regionAddress);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE91A::rva003EE91A(Int regionAddress)
{
	Int values[3];
	((Rva003EE7CA *)this)->rva003EE7CA((Int)&values, regionAddress);
	char *regionData = (char *)regionAddress + 0x54;
	m_owner.rva004E35D5(g_Rva00E02E80, (Int)regionData, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E80, (Int)regionData, (Int)&values);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E80, 0);
}

// ?rva003EEEB3@Rva003EEEB3@@QAEXH@Z @0x003EEEB3 96B chain via 0x003EE7CA+0x003EEA1A loop
// Retail: map 6C/1 at owner+8 then loop over int array at arg calling
// this->rva003EE7CA(&tmp,v) and this->rva003EEA1A(v,ret); tmp[3] at ebp-0x10.
class Rva003EEEB3
{
public:
	void rva003EEEB3(Int regionRangeAddress);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEEB3::rva003EEEB3(Int regionRangeAddress)
{
	((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E6C, 1);
	Int *rangeWords = (Int *)regionRangeAddress;
	for (unsigned int regionIndex = 0; regionIndex < (unsigned int)((rangeWords[1] - rangeWords[0]) >> 2); ++regionIndex) {
		Int entry = *(Int *)(rangeWords[0] + regionIndex * 4);
		if (entry != 0) {
			Int values[3];
			((Rva003EEA1A *)this)->rva003EEA1A(entry, ((Rva003EE7CA *)this)->rva003EE7CA((Int)&values, entry));
		}
	}
}

// ?rva003EEF38@Rva003EEF38@@QAEXH@Z @0x003EEF38 104B chain via 0x003EE7CA+0x003EEA63 loop saving to +0x14
// Retail: map 68/1 at owner+8 then loop over int array; per nonzero v calls
// this->rva003EE7CA(&tmp,v) and this->rva003EEA63(v,ret) then m_saved=v.
class Rva003EEF38
{
public:
	void rva003EEF38(Int regionRangeAddress);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
	Int m_saved;
};
void Rva003EEF38::rva003EEF38(Int regionRangeAddress)
{
	((Rva004E3629 *)&m_owner)->rva004E3629(g_Rva00E02E68, 1);
	Int *rangeWords = (Int *)regionRangeAddress;
	for (unsigned int regionIndex = 0; regionIndex < (unsigned int)((rangeWords[1] - rangeWords[0]) >> 2); ++regionIndex) {
		Int entry = *(Int *)(rangeWords[0] + regionIndex * 4);
		if (entry != 0) {
			Int values[3];
			((Rva003EEA63 *)this)->rva003EEA63(entry, ((Rva003EE7CA *)this)->rva003EE7CA((Int)&values, entry));
			m_saved = entry;
		}
	}
}

// ?rva003EF041@Rva003EF041@@QAEXXZ @0x003EF041 37B
// Evidence: guard this+0x14 then this->rva003EE7CA(&tmp,m_saved) then this->rva003EEE64(ret); callees rowed; callers at 0x002B396A/0x003EF0E4; LINK BONUS via 0x003EF08B
class Rva003EF041
{
public:
	void rva003EF041();
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
	Int m_saved;
};
void Rva003EF041::rva003EF041()
{
	if (m_saved != 0) {
		Int values[3];
		((Rva003EEE64 *)this)->rva003EEE64(((Rva003EE7CA *)this)->rva003EE7CA((Int)&values, m_saved));
	}
}

// ?rva003EEE8E@Rva003EEE8E@@QAEXH@Z @0x003EEE8E 37B chain via 0x003EE7CA+0x003EEB9F
// Retail: tmp[3] at ebp-0xc; this->rva003EE7CA(&tmp,arg) then
// this->rva003EEB9F(arg,ret); prev 0x003EEE64 next 0x003EEEB3 same TU.
class Rva003EEE8E
{
public:
	void rva003EEE8E(Int regionAddress);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEE8E::rva003EEE8E(Int regionAddress)
{
	Int values[3];
	((Rva003EEB9F *)this)->rva003EEB9F(regionAddress, ((Rva003EE7CA *)this)->rva003EE7CA((Int)&values, regionAddress));
}
// ?rva003EEF13@Rva003EEF13@@QAEXH@Z @0x003EEF13 37B chain via 0x003EE7CA+0x003EEBC4
// Retail: tmp[3] at ebp-0xc; this->rva003EE7CA(&tmp,arg) then
// this->rva003EEBC4(arg,ret); prev 0x003EEEB3 next 0x003EEF38 same TU.
class Rva003EEF13
{
public:
	void rva003EEF13(Int regionAddress);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EEF13::rva003EEF13(Int regionAddress)
{
	Int values[3];
	((Rva003EEBC4 *)this)->rva003EEBC4(regionAddress, ((Rva003EE7CA *)this)->rva003EE7CA((Int)&values, regionAddress));
}
// ?rva003EE8D8@Rva003EE8D8@@QAEXH@Z @0x003EE8D8 40B chain via 0x003EE7CA+0x003EE89E
// Retail: tmp[3] at ebp-0xc; this->rva003EE7CA(&tmp,arg) then
// this->rva003EE89E(arg,&tmp); prev 0x003EE89E next 0x003EE900 same TU.
class Rva003EE8D8
{
public:
	void rva003EE8D8(Int regionAddress);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE8D8::rva003EE8D8(Int regionAddress)
{
	Int values[3];
	((Rva003EE7CA *)this)->rva003EE7CA((Int)&values, regionAddress);
	((Rva003EE89E *)this)->rva003EE89E(regionAddress, (Int)&values);
}

// Native 003EEDD6..003EEE64: 142B campaign-region range update.
// WB1037D10 confirms index-range traversal and all five call targets.
// Native reads region bool1A2 and manager bool54; manager constructor and
// RegionEffects FieldParse ShouldShowRegionBorders separately prove bool54.
// Actual function name and unconstrained region fields remain unknown.
class Rva003F0FD1 {public:void rva003F0FD1();};
struct S3CampaignRegion {char pad0[0x54];char region[0x1a2-0x54];bool border;};
struct S3CampaignRange {S3CampaignRegion **begin;S3CampaignRegion **end;};
class Rva003EEDD6 {public:void rva003EEDD6(int);char pad0[0x54];bool borders;};
void Rva003EEDD6::rva003EEDD6(int regionRangeAddress)
{
    S3CampaignRange &range=*(S3CampaignRange*)regionRangeAddress;
    for(unsigned regionIndex=0;regionIndex<(unsigned)(range.end-range.begin);++regionIndex) {
        S3CampaignRegion *region=range.begin[regionIndex];
        ((Rva003F0FD1*)region)->rva003F0FD1();
        ((Rva003EE7E1*)this)->rva003EE7E1((int)region);
        if(region->border) {
            void *regionData=region->region;
            Rva004E35D5 *effects=(Rva004E35D5*)((char*)this+8);
            effects->rva004E35D5(g_Rva00E02E64,(int)regionData,borders);
            ((Rva004E35FF*)effects)->rva004E35FF(g_Rva00E02E64,(int)regionData,(int)((char*)this+0x2c));
            ((Rva004E35AF*)effects)->rva004E35AF(g_Rva00E02E64,0);
        }
    }
}

// ?rva003EEBEF@Rva003EEBEF@@QAEXH@Z retail 0x003EEBEF 116B. Walks the
// 0x14-byte records of the vector at arg+0x3C: each record's index (+4) is
// resolved through the living-world logic's +0xB0 table (rowed 0x0020EAF6)
// and handed with the record's +8 payload to this TU's 0x003EE84A. Skipped
// when the table's holder (+8) has no gate base (holder+0x2C, null-adjusted
// pointer conversion). Record, holder and owner names are address-derived.
class Rva0020E89C;
class Rva003EEBEFHolderLead { char m_pad[0x2c]; };
class Rva003EEBEFGate { int m_gate; };
class Rva003EEBEFHolder : public Rva003EEBEFHolderLead, public Rva003EEBEFGate {};
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
	char m_pad00[8];
	Rva003EEBEFHolder *m_holder; // +0x08
};
class Rva002BA8F1Logic
{
public:
	char m_pad00[0xB0];
	Rva0020EAF6View *m_B0; // +0xB0
	Rva0020EAF6View *getLookup() const { return m_B0; }
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva003EEBEFRecord
{
	Int m_key;     // +0x00
	Int m_index;   // +0x04
	Int m_payload; // +0x08
	Int m_0C;
	Int m_10;
};
struct Rva003EEBEFArg
{
	char m_pad00[0x3c];
	_STL::vector<Rva003EEBEFRecord> m_records; // +0x3C
};
class Rva003EEBEF
{
public:
	void rva003EEBEF(Int recordSourceAddress);
};
void Rva003EEBEF::rva003EEBEF(Int recordSourceAddress)
{
	Rva003EEBEFGate *gate = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->m_B0->m_holder;
	if (gate == 0)
		return;
	Rva003EEBEFArg *regionArg = (Rva003EEBEFArg *)recordSourceAddress;
	int count = regionArg->m_records.size();
	for (int recordIndex = 0; recordIndex < count; ++recordIndex) {
		Rva0020E89C *found = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->getLookup()->rva0020EAF6(regionArg->m_records[recordIndex].m_index);
		((LivingWorldRegionEffectsManager *)this)->rva003EE84A((Int)found, (Int)&regionArg->m_records[recordIndex].m_payload);
	}
}
