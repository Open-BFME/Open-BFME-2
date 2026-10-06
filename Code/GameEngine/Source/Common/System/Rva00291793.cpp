// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX
// ?rva00291793@Rva00291793@@QAEHXZ
// 0x00291793 19B unlock circular list count via +4 holder.
// Evidence: thiscall reads ecx+4 then [eax] then [edx]; loop mov ecx [ecx] inc eax cmp ecx edx; callers 0x002949E6 0x0046AACB 0x005087B3; prev AsciiStringRvoGetters.

struct Rva00291793Node
{
	Rva00291793Node *m_next;
};

struct Rva00291793List
{
	Rva00291793Node *m_head;
};

class Rva00291793
{
public:
	int rva00291793();
private:
	char m_pad00[4];
	Rva00291793List *m_p04;
};

int Rva00291793::rva00291793()
{
	Rva00291793Node *head = m_p04->m_head;
	Rva00291793Node *cur = head->m_next;
	int n = 0;
	while (cur != head) {
		cur = cur->m_next;
		++n;
	}
	return n;
}
