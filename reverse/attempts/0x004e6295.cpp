// ?rva004E6295@Rva004E6295@@QAEMXZ
// partial score=0.93 date=2026-10-07
// cl: /MD /Oy

extern const float BfmeZeroRange;

class GameLogic;
class PlayerList;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
};

// ?rva00359A0C@Rva00359A0C@@QAEMMMM_NPAX@Z, target RVA 0x00359A0C.
// The call at 0x004E6295 uses thiscall with five stack arguments; the callee's
// boundary ends in ret 0x14. The address-derived callee signature follows that
// frame and remains an inference; its owner and semantics are unknown.
class Rva00359A0C
{
public:
	float rva00359A0C(float x, float y, float z, bool flag, void *player);
};

struct Rva004E6295Data
{
	char m_pad00[8];
	float m_08;
	char m_pad0C[8];
	bool m_14;
};

class Rva004E6295
{
public:
	float rva004E6295();

private:
	char m_pad00[8];
	Drawable *m_08;
	Rva004E6295Data *m_0C;
};

// ?rva004E6295@Rva004E6295@@QAEMXZ @0x004E6295 119B.
// Target evidence: null GameLogic or its +0x170 view returns pooled 0.0f;
// otherwise the function resolves PlayerList +0x10/+0x54 and passes drawable
// position x/y with data +0x08/+0x14 to the address-derived callee at 0x00359A0C.
// The method and data owners remain address-derived.
float Rva004E6295::rva004E6295()
{
	GameLogic *logic = TheGameLogic;
	if (logic != 0) {
		void *view = *(void **)((char *)logic + 0x170);
		if (view != 0) {
			void *player = *(void **)((char *)ThePlayerList + 0x10);
			if (player != 0)
				player = *(void **)((char *)player + 0x54);
			Rva004E6295Data *data = m_0C;
			const Coord3D *position = m_08->getPosition();
			return ((Rva00359A0C *)view)->rva00359A0C(
				position->x,
				m_08->getPosition()->y,
				data->m_08,
				data->m_14,
				player);
		}
	}
	return BfmeZeroRange;
}
