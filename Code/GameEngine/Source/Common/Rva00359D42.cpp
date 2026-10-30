// cl: /O1 /G7 /MD
// ?enumerateRegisteredClaimants@TerrainResourceManager@@QAEXHPAVCb00359D42@@@Z @0x00359D42 87B: iterate circular list at +0x14 over BfmePod12-like entries (id+8 float+0xc byte+0x10); findObjectByID via TheGameLogic; mask test 1<<Player+0x54; virtual slot0 cb(id float byte); callers 0x004E7A85 0x004E7E3A; ret 8.
// ?TheGameLogic@@3PAVGameLogic@@A present-unmatched
#include "GameLogicObjectLookupView.h"

class Player
{
public:
	int m_00[21]; // +0x00
	int m_side; // +0x54
};

class Player;
class Module;
class Rva0035A292;
enum CellShroudStatus;
enum NameKeyType { NAMEKEY_INVALID = 0 };
class Object
{
protected:
	friend class Rva0035A292;
public:
	float x38() const { return *(const float *)((const char *)this + 0x38); }
	float y3C() const { return *(const float *)((const char *)this + 0x3c); }
	unsigned int id74() const { return *(const unsigned int *)((const char *)this + 0x74); }
protected:
	Module *findModule(NameKeyType) const;
public:
	Player *getControllingPlayer() const;
	CellShroudStatus getShroudStatusForPlayer(int) const;
};


extern GameLogic *TheGameLogic;

class Cb00359D42
{
public:
	virtual void cb(int id, float val, char b);
};

struct Entry00359D42
{
	Entry00359D42 *m_next;
	Entry00359D42 *m_prev;
	int m_id;
	float m_val;
	char m_b;
	char m_pad[3];
};

struct Entry00359D42;
class Cb00359D42;
struct ResourceCell;
class TerrainResourceManager {
public:
	void enumerateRegisteredClaimants(int mask, Cb00359D42 *cb);
	void rva003598A5(int,int,int,void *);
public:
	void rva0035997F(int,int,int,void *);
public:
	float rva00359A0C(float,float,float,bool,int);
public:
	unsigned int getCellClaimant(int,int,int);
public:
	void updateMapConstantCells();
public:
	float getCellSize() const { return cell3C; }
private:
	char pad00[0x14];
	Entry00359D42 *m_list;
	char pad18[4];
private:
	float originX1C, originY20;
private:
	char pad24[0x10];
private:
	int width34,height38;
private:
	float cell3C;
private:
	ResourceCell *cells40;
public:
	void tryToClaimCell(int,int,int,ObjectID,bool,int*,int*);
public:
	bool isCellClaimable(int, int, int, int, bool, int);
public:
	void rva0035A61F(unsigned int *color, int x, int y, int claimant);
private:
	__forceinline bool isClaimable(int cx, int cy, int claimant)
	{
		return isCellClaimable(cx, cy, 0, 0, false, claimant);
	}
};

void TerrainResourceManager::enumerateRegisteredClaimants(int mask, Cb00359D42 *cb)
{
	Entry00359D42 *head = m_list;
	Entry00359D42 *cur = head->m_next;
	if (cur == head)
		return;
	do {
		Object *obj = TheGameLogic->findObjectByID((ObjectID)cur->m_id);
		if (obj != 0) {
			Player *pl = obj->getControllingPlayer();
			if (mask & (1 << pl->m_side))
				cb->cb(cur->m_id, cur->m_val, cur->m_b);
		}
		cur = cur->m_next;
	} while (cur != head);
}
