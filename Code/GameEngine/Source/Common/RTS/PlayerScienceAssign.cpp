// cl: /DNDEBUG /MD /EHsc
// stlport
// ?rva002AC425@Player@@QAEXABV?$vector@HV?$allocator@H@_STL@@@_STL@@@Z @0x002AC425 (26B)
// Player 4-byte-POD vector assign guard: assigns the vector at +0x2F0 (the
// ScienceVec proven by hasScience 0x002AB7D5 and addScience push_back) from
// the src vector only when src is non-empty (begin != end). Uses the int
// spelling of the folded assign (rowed as dup_0021c21b with int pin at
// 0x0021C21B for RankInfo; ScienceType and int are both 4B PODs with identical
// codegen per that row). Caller 0x0040F94F passes [edi+0x1CC] with
// this=Player from getNthPlayer.
#include <vector>

typedef std::vector<int> IntVec;

class Player
{
	char m_pad[0x2F0];
	IntVec m_vec2F0; // +0x2F0 (ScienceVec folded as int)
public:
	void rva002AC425(const IntVec &src);
};

void Player::rva002AC425(const IntVec &src)
{
	if (src.begin() != src.end())
		m_vec2F0 = src;
}
