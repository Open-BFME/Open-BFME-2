// ?rva00541641@Rva005418CB@@QAE_NH@Z
// partial score=0.93 date=2026-10-10
// ?rva00541641@Rva005418CB@@QAE_NH@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /Oy- /G7 /MD /DNDEBUG
// ?rva00541641@Rva005418CB@@QAE_NH@Z retail 0x00541641..0x00541709 (200 bytes)
// NEAR: the fast hint path (0x00541641..0x0054169B) and the empty/lower_bound
// call/store block match exactly; the tail differs only because cl keeps the
// key in a register across the conditional --hint store (one hoisted load
// `mov eax,[ebp+8]` before jae) where retail reloads it at each compare
// (`mov eax,[eax+edi]; cmp eax,[ebp+8]` and `mov edx,[ebp+8]` at the final
// compare). Same template as banked 0x00541579 (Pod28) and 0x0054034A (Pod40):
// this fast path (inline size()/operator[] on the +0x10 key vector) fixes
// their hint-register wall. `*(volatile int*)&key` on the final compare gets
// the tail but flips the fast path registers (hint edi instead of ecx).
struct BfmePod20 { int key; char frame[16]; };
BfmePod20 *rva0054150A(BfmePod20 *first, BfmePod20 *last, const BfmePod20 &key);
struct KeyVector
{
	unsigned int size() const { return m_end - m_begin; }
	bool empty() const { return m_begin == m_end; }
	BfmePod20 &operator[](unsigned int i) { return m_begin[i]; }
	BfmePod20 *begin() { return m_begin; }
	BfmePod20 *end() { return m_end; }
	BfmePod20 *m_begin, *m_end, *m_capacity;
};
class Rva005418CB
{
public:
	bool rva00541641(int key);
private:
	char m_list00[0x10];
	KeyVector m_keys;
	int m_hint1C;
};
bool Rva005418CB::rva00541641(int key)
{
	int h = m_hint1C;
	if (h >= 0 && (unsigned)h < m_keys.size()) {
		BfmePod20 *b = m_keys.m_begin;
		int cur = b[h].key;
		if (key >= cur && ((unsigned)(h + 1) >= (unsigned)(m_keys.m_end - b) || key < b[h + 1].key))
			return cur == key;
	}
	if (m_keys.empty())
	{
		m_hint1C = -1;
		return false;
	}
	int &hint = m_hint1C;
	BfmePod20 *b = m_keys.m_begin;
	hint = rva0054150A(b, m_keys.m_end, *reinterpret_cast<const BfmePod20 *>(&key)) - b;
	if ((unsigned)hint >= (unsigned)(m_keys.m_end - b) || (hint > 0 && b[hint].key != key))
		--hint;
	return b[hint].key == *(volatile int *)&key;
}
