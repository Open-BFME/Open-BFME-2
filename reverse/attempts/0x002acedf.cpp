// ?rva002ACEDF@Player@@QAEXPAX@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /MD /GX- /Oy-
// stlport
// ?rva002ACEDF@Player@@QAEXH@Z @0x002ACEDF 35B
// Player short-list append. Evidence: this+0x700 list<short> push_back via rowed 0x002AC00C word at arg+0x5D8 callers 0x003BD062 0x003C60D4 unlocks 2.
#include <list>
class Player
{
public:
	void rva002ACEDF(void *src);
private:
	char m_pad[0x700];
	_STL::list<short> m_list700;
};
// ?rva002ACEDF@Player@@QAEXPAX@Z present-unmatched
void Player::rva002ACEDF(void *src)
{
	*(short *)&src = *(short *)((char *)src + 0x5D8);
	m_list700.push_back(*(short *)&src);
}
