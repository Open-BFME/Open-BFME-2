// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0039BF0B@Rva0039BF0B@@QAEHABV?$BitFlags@$0HE@@@0@Z @0x0039BF0B 23B.
// ScoreKeeper single-map wrapper: forwards two BitFlags<116> masks plus the
// ObjectCountMap at +0x1F0 to the rowed free helper 0x0039BEC3
// (Rva0039BEC3Count, __stdcall, ret 0xC) and returns its total. Wrapper is
// thiscall with ret 8, so the two mask references stay the caller's to clean.
// Evidence: 0x0039BF0B is one of four sibling callers of 0x0039BEC3 named in
// ScoreKeeperMapCount.cpp's header note (ecx+0x1C8/0x1D4/0x1F0/0x2EC); this one
// is the +0x1F0 map. Body is a pure forwarder: lea eax,[ecx+0x1F0]; push eax;
// push [esp+0xC]; push [esp+0xC]; call; ret 8.
//
// The map pointer is written as an explicit selection of the two spellings of
// the same member address. That is what emits retail's `lea eax,[ecx+0x1F0]`
// rather than the `add ecx,0x1F0` VC7 otherwise folds: naming `&m_map` and
// `&this->m_map` as two values keeps `this` live across the address
// computation, so the allocator must materialise the result into a scratch
// register instead of destroying ecx. Every other spelling tried (plain &m_map,
// byte-offset cast, volatile, reference binding, static_cast, helper selector,
// nested +8 member, /O1 /Os /O2 /Ot /Oi /Ob0 /Ob1 /Ob2 /Gr /G4 /G6 /G7 /Gy
// /Gw /Zc /Zp8) folds to `add ecx`.

template <int N>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;
private:
	unsigned m_words[7];
};

struct ObjectCountMap
{
	void *m_header;
	int m_pad04;
	int m_pad08;
};

int __stdcall Rva0039BEC3Count(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear, const ObjectCountMap *map);

class Rva0039BF0B
{
public:
	int rva0039BF0B(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear);
private:
	char m_pad[0x1F0];
	ObjectCountMap m_map;
};

int Rva0039BF0B::rva0039BF0B(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear)
{
	const ObjectCountMap *map = &m_map;
	const ObjectCountMap *self_map = &this->m_map;
	return Rva0039BEC3Count(mustBeSet, mustBeClear, map ? map : self_map);
}

class Rva0039BF22
{
public:
	int rva0039BF22(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear);
private:
	char m_pad[0x1C8];
	ObjectCountMap m_map;
};

int Rva0039BF22::rva0039BF22(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear)
{
	const ObjectCountMap *map = &m_map;
	const ObjectCountMap *self_map = &this->m_map;
	return Rva0039BEC3Count(mustBeSet, mustBeClear, map ? map : self_map);
}
