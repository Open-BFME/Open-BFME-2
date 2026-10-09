// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?tryToClaimCell@TerrainResourceManager@@QAEXHHHW4ObjectID@@_NPAH2@Z
// retail 0x0035AA43..0x0035AB7F (316 bytes, ret 0x1C).
// WorldBuilder twin 0x00E619A0 is TerrainResourceManager::tryToClaimCell
// (TerrainResourceManager.cpp lines 800..879: "Trying to use uninitialized
// TerrainResourceManager!", "-1 != claimerPlayerID", "Claimed terrain
// resource cell has other than one claim!"); its callee 0x0035A4A3 is WB's
// TerrainResourceManager::isCellClaimable (pinned here under its address
// name). Retail owner layout as TerrainResourceManager::DoXfer (0x0035ABE0):
// width at +0x34 and the 16-byte cell array at +0x40 (claimant vector of
// 8-byte (player id object id) records plus a state). Its only caller is the
// functor slot at 0x0035AB7F (two counters at +0x10/+0x14). With cells it
// counts the attempt, checks isCellClaimable(... -1), resolves the object
// (rowed GameLogic::findObjectByID 0x00049DC5) and its controlling player
// (rowed 0x0028AFA9; player id at +0x54), then by cell state: 0 clears and
// becomes 2 or 3 (exclusive) and adds; 2 restarts as an exclusive 3 or adds
// the player once; 3 (exclusive only) overwrites the single claim or adds
// one. Each change except that last add counts a success. The claimant
// calls are the rowed erase(first last) 0x003FA4DB (BfmePod8 view) and
// push_back 0x00539A2E (BfmeE8 view of the same 8-byte record). Parameter
// types and the third argument's meaning are inferred.
#include <vector>
#include "../../Common/GameLogicObjectLookupView.h"

class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex; // +0x54
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

extern GameLogic *TheGameLogic;

struct BfmeE8 { int a, b; };
struct BfmePod8 { int a[2]; };

namespace _STL {
// Retail calls both out of line.
template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &);
template <> BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *first, BfmePod8 *last);
}

class Rva0035A18D
{
public:
	Rva0035A18D();
	~Rva0035A18D();
	_STL::vector<BfmePod8> values;
	int state;
};

class Rva0035A4A3
{
public:
	bool rva0035A4A3(int x, int y, int a, int id, bool exclusive, int b);
};

class TerrainResourceManager
{
public:
	void tryToClaimCell(int x, int y, int a, ObjectID id, bool exclusive, int *attempts, int *successes);

private:
	void *m_vtable00;
	unsigned char m_opaque04[0x30];
	int m_width; // +0x34
	int m_height; // +0x38
	float m_value3C;
	Rva0035A18D *m_cells; // +0x40
};

void TerrainResourceManager::tryToClaimCell(int x, int y, int a, ObjectID id, bool exclusive, int *attempts, int *successes)
{
	if (m_cells == 0)
		return;
	++*attempts;
	if (!((Rva0035A4A3 *)this)->rva0035A4A3(x, y, a, id, exclusive, -1))
		return;
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj == 0)
		return;
	Player *player = obj->getControllingPlayer();
	if (player == 0)
		return;
	int claimerPlayerID = player->m_playerIndex;
	Rva0035A18D *cell = &m_cells[y * m_width + x];
	_STL::vector<BfmeE8> *claimants = (_STL::vector<BfmeE8> *)&cell->values;
	switch (cell->state)
	{
	case 0:
	{
		cell->state = exclusive ? 3 : 2;
		cell->values.clear();
		BfmeE8 claim = { claimerPlayerID, id };
		claimants->push_back(claim);
		++*successes;
		break;
	}
	case 2:
		if (exclusive)
		{
			cell->values.clear();
			BfmeE8 claim = { claimerPlayerID, id };
			claimants->push_back(claim);
			cell->state = 3;
			++*successes;
		}
		else
		{
			bool found = false;
			for (BfmePod8 *it = cell->values.begin(); it != cell->values.end(); ++it)
			{
				if (it->a[0] == claimerPlayerID)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				BfmeE8 claim = { claimerPlayerID, id };
				claimants->push_back(claim);
				++*successes;
			}
		}
		break;
	case 3:
		if (!exclusive)
			break;
		if (cell->values.size() >= 1)
		{
			BfmePod8 &claim = cell->values[0];
			claim.a[0] = claimerPlayerID;
			claim.a[1] = id;
			++*successes;
		}
		else
		{
			BfmeE8 claim = { claimerPlayerID, id };
			claimants->push_back(claim);
		}
		break;
	}
}
