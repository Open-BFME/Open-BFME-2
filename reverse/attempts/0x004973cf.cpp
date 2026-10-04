// ?rva004973CF@BannerCarrierUpdate@@QAEXXZ
// partial score=0.98 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA004973CF_2 = 2
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

template <int N> class Rva004973CFSlots : public Rva004973CFSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004973CFSlots<0>
{
};

// The horde contain interface Object::rva0028C197 returns.
class Rva004973CFContain : public Rva004973CFSlots<93>
{
public:
	virtual void rva004973CFSlot93(int arg) = 0;
	virtual unsigned rva004973CFSlot94() = 0;
	virtual unsigned rva004973CFSlot95() = 0;
	virtual void slot96() = 0;
	virtual void slot97() = 0;
	virtual unsigned rva004973CFSlot98() = 0;
	virtual Object *rva004973CFSlot99(void *what) = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	void *rva0028C197() const;	// 0x0028C197
	void bfmeRefreshPartitionCells();	// 0x0028C11A
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x08];
	char m_08[4];		// +0x08
	char m_pad00C[0x38 - 0x0C];
	Coord3D m_pos;		// +0x38
};

class BannerCarrierUpdateModuleData
{
public:
	char m_pad00[0x34];
	const FXList *m_unitSpawnFX;		// +0x34 UnitSpawnFX
	bool m_replenishNearbyHorde;		// +0x38 ReplenishNearbyHorde
	bool m_replenishAllNearbyHordes;	// +0x39 ReplenishAllNearbyHordes
	float m_scanHordeDistance;		// +0x3C ScanHordeDistance
};

class BannerCarrierUpdate
{
public:
	void rva004973CF();
private:
	const BannerCarrierUpdateModuleData *getBannerCarrierUpdateModuleData() const
	{
		return (const BannerCarrierUpdateModuleData *)m_moduleData;
	}
	void *m_vtable;
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

void BannerCarrierUpdate::rva004973CF()
{
	Player *player = m_object->getControllingPlayer();
	if (!player)
		return;
	const BannerCarrierUpdateModuleData *data = getBannerCarrierUpdateModuleData();
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(m_object->getPosition(), data->m_scanHordeDistance, 0,
		Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 109),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(&Rva00261409Filter(player, true, 2)), 1);
	Object *other;
	while ((other = hits.next()) != 0) {
		if (!other->testStatus(OBJECT_STATUS_RVA004973CF_2)) {
			Rva004973CFContain *contain = (Rva004973CFContain *)other->rva0028C197();
			if (contain) {
				unsigned maxCount = contain->rva004973CFSlot95();
				if (contain->rva004973CFSlot98() < maxCount) {
					Object *spawned = contain->rva004973CFSlot99(other->m_08);
					if (spawned) {
						spawned->bfmeRefreshPartitionCells();
						if (data->m_unitSpawnFX)
							FXList::doFXObj(data->m_unitSpawnFX, spawned, 0);
					}
					if (!data->m_replenishAllNearbyHordes)
						break;
				} else if (contain->rva004973CFSlot94() > 1) {
					contain->rva004973CFSlot93(1);
				}
			}
		}
	}
}
