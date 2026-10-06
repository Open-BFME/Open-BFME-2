// cl: /DNDEBUG /MD
//
// ?rva0020276C@Rva0020276C@@QAE_NH@Z @0x0020276C 36B. Change-detecting setter at
// +0x176c rejecting -1 then rowed LOD apply helper.
// Evidence: retail mov edx [esp+4] plus cmp edx -1 je plus lea eax [ecx+0x176c]
// plus cmp [eax] edx je plus mov [eax] edx plus call 0x00202633 rowed plus
// mov al 1 plus xor al al plus ret 4; caller 0x00043FF5.
class Rva0020276C
{
public:
	bool rva0020276C(int v);
	char m_pad[0x176c];
	int m_176c;
};

class Rva00202633
{
public:
	void rva00202633(int level);
};

bool Rva0020276C::rva0020276C(int v)
{
	if (v != -1) {
		if (m_176c != v) {
			m_176c = v;
			((Rva00202633 *)this)->rva00202633(v);
			return true;
		}
	}
	return false;
}
