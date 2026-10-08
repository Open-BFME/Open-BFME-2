// ?rva005657FE@Rva005657FEOwner@@QBEPAURva005657FEElement@@ABV?$StringBase@D@@PBURva005657FEHolder@@@Z
// partial score=0.85 date=2026-10-08
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?rva005657FE@Rva005657FEOwner@@QBEPAURva005657FEElement@@ABV?$StringBase@D@@PBURva005657FEHolder@@@Z
// @0x005657FE 103B: thiscall, two stack arguments, ret 8.
// Walks a vector of 0x58-byte records held at this+0x20 (begin) and this+0x24
// (end). For each record, the key at +0x18 compares against the first argument
// through StringBase::compare; on a match the holder's reference at +0x40 goes to
// the rowed contains helper 0x004E2CD5 and the record is returned when that
// helper accepts it. Owner, element and holder names are address-derived views;
// no field meaning is claimed beyond the bytes.
#include "string_base.h"

class Rva004E2CD5
{
public:
	bool rva004E2CD5(const StringBase<char> &val);
};

struct Rva005657FEElement
{
	char pad00[0x18];
	StringBase<char> m_key;
	char pad1C[0x58 - 0x18 - sizeof(StringBase<char>)];
};

struct Rva005657FEHolder
{
	char pad00[0x40];
	const StringBase<char> &m_40;
};

class Rva005657FEOwner
{
public:
	Rva005657FEElement *rva005657FE(const StringBase<char> &key, const Rva005657FEHolder *holder) const;
private:
	char pad00[0x20];
	Rva005657FEElement *m_begin;
	Rva005657FEElement *m_end;
};

Rva005657FEElement *Rva005657FEOwner::rva005657FE(const StringBase<char> &key, const Rva005657FEHolder *holder) const
{
	int offset = 0;
	for (int i = 0; i < (int)((char *)m_end - (char *)m_begin) / 0x58; ++i, offset += 0x58) {
		Rva005657FEElement *e = (Rva005657FEElement *)((char *)m_begin + offset);
		if (e->m_key.compare(key) == 0 && ((Rva004E2CD5 *)e)->rva004E2CD5(holder->m_40))
			return e;
	}
	return 0;
}
