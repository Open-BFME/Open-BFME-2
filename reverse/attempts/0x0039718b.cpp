// ?rva0039718B@Rva0039718B@@QAE_NPAVPlayer@@@Z
// partial score=0.65 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva0039718B@Rva0039718B@@QAE_NPAVPlayer@@@Z @0x0039718B 52B: true when the
// given player is our controlling player and its +0x94 field matches our
// pinned 0x003970E7 lookup on it. Evidence: m08 feeds the rowed
// Object::getControllingPlayer at 0x0028AFA9, twin early-false guards share
// one xor-al block ahead of the check, f94 hoisted into edi across the call,
// sbb/inc booleanize; flags and decls follow neighbouring
// Rva00396B25Receiver.cpp / Rva00396B0DForward.cpp (without its /Oy-:
// retail addresses the arg off esp).
class Player
{
public:
	char m_pad00[0x94];
	int m_field94;
};

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class Rva0039718B
{
public:
	bool rva0039718B(Player *player);
	int rva003970E7(Player *player);

private:
	char m_pad00[8];
	Object *m_object08;
};

bool Rva0039718B::rva0039718B(Player *player)
{
	Player *ours = m_object08->getControllingPlayer();
	if (player != 0) {
		if (ours == player) {
			int f94 = player->m_field94;
			return f94 == rva003970E7(player);
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
