// cl: /O1 /G7 /arch:SSE /MD /Oy


class GameLogic;
class FeedbackPlayer { public: char pad00[0x54]; int index54; 
// ?FeedbackPlayer::getIndex present-unmatched
int getIndex() const {return index54;} };
class PlayerList { public: char pad00[0x10]; FeedbackPlayer *local10; 
// ?PlayerList::getLocalPlayer present-unmatched
FeedbackPlayer *getLocalPlayer() const {return local10;} };
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class TerrainResourceManager
{
public:
	float rva00359A0C(float x, float y, float radius, bool flag, int player);
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
	BFMERopeDrawable *m_08;
	Rva004E6295Data *m_0C;
};

// ?rva004E6295@Rva004E6295@@QAEMXZ @0x004E6295 119B.
// Target evidence: null GameLogic or its +0x170 view returns pooled 0.0f;
// otherwise the function resolves PlayerList +0x10/+0x54 and passes drawable
// position x/y with data +0x08/+0x14 to the owned TerrainResourceManager query at 0x00359A0C.
// WB 0x1324880 (113B) in PlaceTerrainResourceClaimantFeedback.cpp has the same
// guards, fields and callees; neighbouring named update/createPotentialClaimDecal
// establish the file. The method name and data owner remain address-derived.
// The local-player index at +0x54 is passed as int, proven by the recovered query.
// Flags reproduce retail x87 argument stores and its shared return epilogue.
float Rva004E6295::rva004E6295()
{
	GameLogic *logic = TheGameLogic;
	if (logic != 0) {
		void *view = *(void **)((char *)logic + 0x170);
		if (view != 0) {
			FeedbackPlayer *player=ThePlayerList->getLocalPlayer();
            int index=player?player->getIndex():0;
			Rva004E6295Data *data = m_0C;
			const Coord3D *position = m_08->getPosition();
			return ((TerrainResourceManager *)view)->rva00359A0C(
				position->x,
				m_08->getPosition()->y,
				data->m_08,
				data->m_14,
				index);
		}
	}
	return 0.0f;
}
