// cl: /DNDEBUG /MD
// ?rva0043C754@Rva0043D16F@@QAEXPAVCreateAHeroData@@PA_N@Z @0x0043C754 (30B): Rva0043D16F check via Player at +4 with bool out.
// Evidence: vtable slot 2 of 0x0083D7E8 class Rva0043D16F; mov ecx [ecx+4] then const Player::rva002AB855 @0x002AB855 row; ret 8 two args; chain from 0x002AB855.
class CreateAHeroData;
class Player
{
public:
	bool rva002AB855(CreateAHeroData *hero) const;
};

class Rva0043D16F
{
	char m_pad[4];
	Player *m_player;
public:
	void rva0043C754(CreateAHeroData *hero, bool *out);
};

void Rva0043D16F::rva0043C754(CreateAHeroData *hero, bool *out)
{
	*out = false;
	if (m_player) {
		*out = m_player->rva002AB855(hero);
	}
}
