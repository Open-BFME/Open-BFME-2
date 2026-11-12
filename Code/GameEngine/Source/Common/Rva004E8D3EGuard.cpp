// cl: /MD
//
// ?rva004E8D3E@Rva004E8D3E@@QAEHHHH@Z @0x004E8D3E 72B.
// Triple-guarded bool: a pinned row-test hit, two magic/zero rejects, a
// member compare, then the pinned 0x4E8820 touch all funnel to shared
// true/false tails. Retail 0x004E8D3E..0x004E8D84. Pins are honest
// address-derived candidates (0x4E8820 is an in-range target).

#include "../../Include/GameClient/_bfme_AptGameWindow.h"

// LINK: 0x004E8820 is rowed as AptInGameChat::Send(char const *) (same one-word ABI); the old int-flag call stays through a member-pointer cast.
class AptInGameChat
{
public:
	void Send(const char *text);
};
typedef void (AptInGameChat::*AptInGameChatIntShape)(int);

class Rva004E8D3E
{
public:
	int rva004E8D3E(int a, int b, int c);

private:
	char m_pad[0x284];
	int m_284;
};

// ?rva004E8D3E@Rva004E8D3E@@QAEHHHH@Z
int Rva004E8D3E::rva004E8D3E(int a, int b, int c)
{
	if (((_bfme_AptGameWindow *)this)->rva0051274F(a, b, c) == 1)
		return 1;
	if (a != 0x4031 || c != 0)
		return 0;
	if (b == m_284)
		(((AptInGameChat *)this)->*reinterpret_cast<AptInGameChatIntShape>(&AptInGameChat::Send))(0);
	return 1;
}
