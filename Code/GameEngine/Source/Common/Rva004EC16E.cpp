// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva004EC16E@Rva004EC16E@@QAEPAXM@Z @ 0x004EC16E, 96 bytes.
// Vector at +0x130/+0x134 of item pointers; each item has float virtual at
// slot 2 ([eax+8]). Returns best item whose value is below input float.
// Evidence: begin/end raw loop add edi,4; fld/fcompi float compares; two
// callers in 0x004EC700; same +0x130 family as Rva004EC276 vector.
class Item
{
public:
	virtual void v00();
	virtual void v01();
	virtual float getValue();
};

class Rva004EC16E
{
public:
	void *rva004EC16E(float x);
private:
	char m_pad[0x130];
	Item **m_begin;
	Item **m_end;
};

void *Rva004EC16E::rva004EC16E(float x)
{
	Item *best = 0;
	Item **it = m_begin;
	Item **end = m_end;
	while (it != end) {
		Item *cur = *it;
		float v = cur->getValue();
		if (!(x > v))
			goto next;
		if (best == 0) {
			best = cur;
			goto next;
		}
		{
			float curV = cur->getValue();
			float bestV = best->getValue();
			if (!(curV > bestV))
				goto next;
			best = cur;
		}
	next:
		++it;
	}
	return best;
}
