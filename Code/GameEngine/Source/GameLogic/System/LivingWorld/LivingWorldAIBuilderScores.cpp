// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// LivingWorldAIBuilder's building-order unit, in retail order: the scoring
// helpers 0x0059CEE4 0x0059CF34 0x0059CFAA 0x0059D089 0x0059D1A9 0x0059D1C3
// 0x0059D1DD, the push_back instantiation 0x0059D2A3 and FillBuildingOrders
// 0x0059D2DA. They share one unit because FillBuildingOrders hands each
// helper its loop iterator by address yet keeps the region node in a
// register across the calls: MSVC does that only after compiling the helpers
// and seeing that they leave the iterator alone (split into separate units
// the caller reloads the node after every call).
//
// The four float scoring helpers (thiscall RET 0x10 each) sit between the
// rowed DefendHomeTerritory neighbourhood and 0x0059D2DA whose WorldBuilder
// twin is LivingWorldAIBuilder::FillBuildingOrders (LivingWorldAIBuilder.cpp
// asserts 138..156); FillBuildingOrders calls all three with its own ECX
// (mov ecx this) its player id its armies object (arg_3) and the address of
// its local region pointer. WorldBuilder twins (unnamed): 0x014FE380
// 0x014FE470 0x014FE680 with the same calls branches and constants.
//
// Evidence (target): 0x00500659 is the rowed
// Rva0059CFAACallee::rva00500659 returning vector<ObjectID> by value (the
// caller passes the hidden result address as the last push and frees the
// buffer through _free 0x00030830 afterwards: the inlined vector
// destructor); 0x004FFB00 is the thiscall RET 0xC closest-hero lookup that
// returns its entry in EAX and writes its distance through the third
// argument. The region keeps its id at +0x14 (passed by address as the
// territory key exactly like the rowed 0x004FFA6E source) and a 4-byte
// vector at +0x24; the template argument of 0x0059D089 holds a float at
// +0x30. Method names and the class views are address-derived.

#include <math.h>
#include <map>
#include <vector>

enum ObjectID
{
	INVALID_ID = 0
};

struct Rva004FFB00Hero;

class Rva0059CFAACallee
{
public:
	_STL::vector<ObjectID> rva00500659(int playerId, int *territory, int *count);
	Rva004FFB00Hero *rva004FFB00(int playerId, int *territory, int *distance);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// The armies map's per-region record (WorldBuilder's regionInfo; its
// asserts name the Castles/Armories/Farms/Barracks object-id vectors).
struct Rva0059D2DARegionInfo
{
	int m_id;	// +0x00
	char m_pad04[0x0c - 0x04];
	int m_count;	// +0x0C
	_STL::vector<int> Castles;	// +0x10
	_STL::vector<int> Armories;	// +0x1C
	_STL::vector<int> Farms;	// +0x28
	_STL::vector<int> Barracks;	// +0x34
};

// A node of the armies map: the helpers take the iterator by address.
struct Rva0059CFAARegion
{
	char m_pad00[0x14];
	Rva0059D2DARegionInfo m_info;	// +0x14
};

struct Rva0059D089Template
{
	NameKeyType m_00;	// +0x00
	NameKeyType m_04;	// +0x04
	NameKeyType m_08;	// +0x08
	NameKeyType m_0c;	// +0x0C
	char m_pad10[0x1c - 0x10];
	int m_1c;	// +0x1C
	float m_20;	// +0x20
	char m_pad24[0x30 - 0x24];
	float m_30;	// +0x30
	NameKeyType getKey(int i) const { return (&m_00)[i]; }
};

struct BfmeE16;

class Rva0059CEE4
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
public:
	float rva0059CEE4(int a1, void *a2, void **a3);
};

class LivingWorldAIBuilder
{
public:
	float rva0059CF34(int playerId, int count, Rva0059CFAACallee *armies,
		Rva0059CFAARegion *const &region);
	float rva0059CFAA(int playerId, int count, Rva0059CFAACallee *armies,
		Rva0059CFAARegion *const &region);
	float rva0059D089(int playerId, Rva0059D089Template *tmpl,
		Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region);
	float rva0059D1A9(int playerId, int count, Rva0059CFAACallee *armies,
		Rva0059CFAARegion *const &region);
	float rva0059D1C3(int playerId, int count, Rva0059CFAACallee *armies,
		Rva0059CFAARegion *const &region);
	float rva0059D1DD(int playerId, Rva0059D089Template *tmpl,
		Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region);
	void FillBuildingOrders(_STL::vector<BfmeE16> *orders, int playerId,
		Rva0059D089Template *tmpl, Rva0059CFAACallee *armies,
		int built, int budget, int limit, int *cost);
private:
	int m_00;
	int m_04;
	int m_08;
};

// ?rva0059CEE4@Rva0059CEE4@@QAEMHPAXPAPAX@Z retail 0x0059CEE4 (75 bytes):
// the builder's +0x0C weight scaled by the closest hero's distance falloff.
extern float g_Va007C26F0;
extern float g_00BC7508;
extern float g_00BC8980;
float Rva0059CEE4::rva0059CEE4(int a1, void *a2, void **a3)
{
	int out = 0;
	float y = (float)m_0c;
	int *info = (int *)((char *)*a3 + 0x14);
	((Rva0059CFAACallee *)a2)->rva004FFB00(a1, info, &out);
	float x = (float)out * g_Va007C26F0;
	return (g_00BC7508 - x * x) * (*(const volatile float *)&y * g_00BC8980);
}

// ?rva0059CF34@LivingWorldAIBuilder@@QAEMHHPAVRva0059CFAACallee@@ABQAURva0059CFAARegion@@@Z
// retail 0x0059CF34..0x0059CFAA (118 bytes; WorldBuilder twin 0x014FE300):
// m_00 (when count > 0) times the defender count times 1.5.
float LivingWorldAIBuilder::rva0059CF34(int playerId, int count,
	Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region)
{
	float score = count > 0 ? (float)m_00 : 0.0f;
	if (score > 0.0f)
	{
		int defenders = 0;
		armies->rva00500659(playerId, &region->m_info.m_id, &defenders);
		score *= defenders;
		score *= 1.5f;
	}
	return score;
}


// ?rva0059CFAA@LivingWorldAIBuilder@@QAEMHHPAVRva0059CFAACallee@@ABQAURva0059CFAARegion@@@Z
// retail 0x0059CFAA..0x0059D089 (223 bytes): m_04 (when count > 0) scaled
// by count * 5 above three or by the defender and hero-distance falloffs.
float LivingWorldAIBuilder::rva0059CFAA(int playerId, int count,
	Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region)
{
	float score = (float)(count > 0 ? m_04 : 0);
	if (score > 0.0f)
	{
		int defenders = 0;
		int distance = 0;
		armies->rva00500659(playerId, &region->m_info.m_id, &defenders);
		armies->rva004FFB00(playerId, &region->m_info.m_id, &distance);
		if (count > 3)
		{
			score *= (float)(count * 5);
		}
		else
		{
			score *= 3.0f - (defenders - 2.5f) * 0.5f * (defenders - 2.5f);
			score *= 3.0f - distance * 0.5f;
		}
	}
	return score;
}

// ?rva0059D089@LivingWorldAIBuilder@@QAEMHPAURva0059D089Template@@PAVRva0059CFAACallee@@ABQAURva0059CFAARegion@@@Z
// retail 0x0059D089..0x0059D1A9 (288 bytes): m_08 damped once per entry of
// the region's +0x24 vector then weighted by the defender count (log
// falloff below six) and the closest hero's distance. log is the msvcr71
// import thunk 0x00629B0E.
float LivingWorldAIBuilder::rva0059D089(int playerId, Rva0059D089Template *tmpl,
	Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region)
{
	float score = (float)m_08;
	for (int i = 0; i < (int)region->m_info.Castles.size(); ++i)
		score *= 1.0f - 0.1f * tmpl->m_30;
	int defenders = 0;
	int distance = 0;
	armies->rva00500659(playerId, &region->m_info.m_id, &defenders);
	armies->rva004FFB00(playerId, &region->m_info.m_id, &distance);
	if (defenders < 6)
	{
		score = defenders * log(6.0f - defenders) * score;
		if (score > 0.0f && distance > 0)
			score *= 2.0f / (distance + 1) + 0.5f;
	}
	else
	{
		score *= 0.1f;
	}
	return score;
}

// ?rva0059D1DD@LivingWorldAIBuilder@@QAEMHPAURva0059D089Template@@PAVRva0059CFAACallee@@ABQAURva0059CFAARegion@@@Z
// retail 0x0059D1DD..0x0059D2A3 (198 bytes): like 0x0059D089 but damps from
// the second entry and scales by (5 - defenders) squared below three
// defenders; otherwise defers to 0x0059D089.
float LivingWorldAIBuilder::rva0059D1DD(int playerId, Rva0059D089Template *tmpl,
	Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region)
{
	float score = (float)m_08;
	for (int i = 1; i < (int)region->m_info.Castles.size(); ++i)
		score *= 1.0f - 0.1f * tmpl->m_30;
	int defenders = 0;
	armies->rva00500659(playerId, &region->m_info.m_id, &defenders);
	if (defenders < 3)
		score *= (float)((5 - defenders) * (5 - defenders));
	else
		score = rva0059D089(playerId, tmpl, armies, region);
	return score;
}

// ?rva0059D1A9@LivingWorldAIBuilder@@QAEMHHPAVRva0059CFAACallee@@ABQAURva0059CFAARegion@@@Z
// ?rva0059D1C3@LivingWorldAIBuilder@@QAEMHHPAVRva0059CFAACallee@@ABQAURva0059CFAARegion@@@Z
// retail 0x0059D1A9 / 0x0059D1C3 (26 bytes each; WorldBuilder twins
// 0x014FE620 / 0x014FE650): the build and upgrade scores for one more.
float LivingWorldAIBuilder::rva0059D1A9(int playerId, int count,
	Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region)
{
	return rva0059CF34(playerId, count + 1, armies, region);
}

float LivingWorldAIBuilder::rva0059D1C3(int playerId, int count,
	Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region)
{
	return rva0059CFAA(playerId, count + 1, armies, region);
}

// FillBuildingOrders' vector bodies are rowed under placeholder element
// types (erase 0x002BF70F on BfmePod16, push_back 0x0059D2A3 on BfmeE16).
// The push_back instantiates here, ahead of its caller, as in retail.
struct BfmePod16 { int a[4]; };
struct BfmeE16 { float x, y, z, w; };
template <> BfmePod16 *_STL::vector<BfmePod16, _STL::allocator<BfmePod16> >::erase(BfmePod16 *first, BfmePod16 *last);

// 16-byte order: remove flag, region id, template key, object id.
struct LivingWorldBuildOrder
{
	bool m_remove;	// +0x00
	int m_region;	// +0x04
	NameKeyType m_template;	// +0x08
	int m_object;	// +0x0C
};

struct Rva004FCD6DElement
{
	short words[1];
	bool operator<(const Rva004FCD6DElement &b) const { return words[0] < b.words[0]; }
};

typedef _STL::map<Rva004FCD6DElement, int, _STL::less<Rva004FCD6DElement>, _STL::allocator<_STL::pair<Rva004FCD6DElement const, int> > > Rva005003C7Map;
typedef _STL::pair<Rva005003C7Map::const_iterator, Rva005003C7Map::const_iterator> Rva005003C7Range;

class Rva005003C7
{
public:
	Rva005003C7Range rva005003C7(Rva004FCD6DElement key) const;
};

class LivingWorldRegion
{
	char m_pad[0x170];
public:
	_STL::vector<int> m_170;	// +0x170
	int rva003F05CE();
	bool rva003F1BD3(NameKeyType key, int *out);
};

class Rva003F07CEOwner
{
public:
	bool rva003F07CE();
};

class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int id);
};

class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int playerId, unsigned int *index);
};

class LivingWorldLogic
{
	char m_pad[0xb0];
public:
	Rva0020EAF6View *m_regions;	// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

// Retail 0x0059D2DA..0x0059D74B (1137 bytes, RET 0x20); WorldBuilder twin
// 0x014FD650 (LivingWorldAIBuilder::FillBuildingOrders, asserts 138..156
// name regionInfo's Barracks/Farms/Armories/Castles). Clears the orders; for
// a known player sums its regions' barracks, splits the remaining budget
// into build and upgrade counts, then per region with free plots scores the
// four template builds and queues the best, or (a region whose plots are
// all used) weighs replacing a building and queues a removal and a build.
// Defined after the scoring helpers: retail keeps the region node in a
// register across them, which MSVC does only once it has seen that they
// leave the iterator they receive by address alone.
void LivingWorldAIBuilder::FillBuildingOrders(_STL::vector<BfmeE16> *orders, int playerId,
	Rva0059D089Template *tmpl, Rva0059CFAACallee *armies,
	int built, int budget, int limit, int *cost)
{
	reinterpret_cast<_STL::vector<BfmePod16> *>(orders)->clear();
	if (!((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId, 0))
		return;

	int slots = 0;
	Rva005003C7Range range = ((Rva005003C7 *)armies)->rva005003C7(*(Rva004FCD6DElement *)&playerId);
	for (Rva005003C7Map::const_iterator it = range.first; it != range.second; ++it)
		slots += ((Rva0059CFAARegion *)it._M_node)->m_info.Barracks.size();

	int used = (int)(slots * tmpl->m_20);
	int buildCount;
	if (built + used > budget)
		buildCount = (built + used - budget) / tmpl->m_1c;
	else
		buildCount = (limit - budget) / tmpl->m_1c;
	int upgradeCount = (int)((budget - built - used) / tmpl->m_20 + 0.5f);

	for (Rva005003C7Map::const_iterator it = range.first; it != range.second; ++it)
	{
		Rva0059CFAARegion *const &node = *(Rva0059CFAARegion **)&it._M_node;
		LivingWorldRegion *region = (LivingWorldRegion *)TheLivingWorldLogic->m_regions->rva0020EAF6(node->m_info.m_id);
		const Rva0059D2DARegionInfo &regionInfo = node->m_info;
		int count = regionInfo.m_count;
		if (region->rva003F05CE() + count < (int)region->m_170.size())
			continue;

		float buildScore = region->rva003F1BD3(tmpl->getKey(0), 0) ? rva0059CF34(playerId, buildCount, armies, node) : 0.0f;
		float upgradeScore = region->rva003F1BD3(tmpl->getKey(1), 0) ? rva0059CFAA(playerId, upgradeCount, armies, node) : 0.0f;
		float score3 = region->rva003F1BD3(tmpl->getKey(3), 0) ? ((Rva0059CEE4 *)this)->rva0059CEE4(playerId, armies, (void **)&node) : 0.0f;
		float score4 = region->rva003F1BD3(tmpl->getKey(2), 0) ? rva0059D089(playerId, tmpl, armies, node) : 0.0f;

		if (count > 0 && ((Rva003F07CEOwner *)region)->rva003F07CE())
		{
			LivingWorldBuildOrder order;
			order.m_remove = false;
			order.m_region = node->m_info.m_id;
			if (upgradeScore >= buildScore && upgradeScore >= score3 && upgradeScore >= score4)
			{
				order.m_template = tmpl->m_04;
				--upgradeCount;
			}
			else if (buildScore >= score3 && buildScore >= score4)
			{
				order.m_template = tmpl->m_00;
				*cost += tmpl->m_1c;
				--buildCount;
			}
			else if (score3 >= score4)
				order.m_template = tmpl->m_0c;
			else
				order.m_template = tmpl->m_08;
			orders->push_back(reinterpret_cast<const BfmeE16 &>(order));
		}
		else
		{
			float remove1 = regionInfo.Farms.size() > 0 ? rva0059D1A9(playerId, buildCount, armies, node) : -1.0f;
			float remove2 = regionInfo.Barracks.size() > 0 ? rva0059D1C3(playerId, upgradeCount, armies, node) : -1.0f;
			float remove3 = regionInfo.Armories.size() > 0 ? ((Rva0059CEE4 *)this)->rva0059CEE4(playerId, armies, (void **)&node) : -1.0f;
			float remove4 = regionInfo.Castles.size() > 0 ? rva0059D1DD(playerId, tmpl, armies, node) : -1.0f;

			float bestScore = _STL::max(_STL::max(_STL::max(score4, score3), upgradeScore), buildScore);
			float bestRemove = _STL::max(_STL::max(_STL::max(remove4, remove3), remove2), remove1);
			if (bestScore > bestRemove * 1.5f && bestScore > 20.0f && bestRemove >= 0.0f)
			{
				LivingWorldBuildOrder order;
				order.m_remove = true;
				order.m_region = node->m_info.m_id;
				if (remove2 >= remove1 && remove2 >= remove3 && remove2 >= remove4)
				{
					order.m_object = regionInfo.Barracks[0];
					++upgradeCount;
				}
				else if (remove1 >= remove3 && remove1 >= remove4)
				{
					order.m_object = regionInfo.Farms[0];
					*cost -= tmpl->m_1c;
					++buildCount;
				}
				else if (remove3 >= remove4)
					order.m_object = regionInfo.Armories[0];
				else
					order.m_object = regionInfo.Castles[0];
				orders->push_back(reinterpret_cast<const BfmeE16 &>(order));

				order.m_remove = false;
				if (upgradeScore >= buildScore && upgradeScore >= score3 && upgradeScore >= score4)
				{
					order.m_template = tmpl->m_04;
					--upgradeCount;
				}
				else if (buildScore >= score3 && buildScore >= score4)
				{
					order.m_template = tmpl->m_00;
					*cost += tmpl->m_1c;
					--buildCount;
				}
				else if (score3 >= score4)
					order.m_template = tmpl->m_0c;
				else
					order.m_template = tmpl->m_08;
				orders->push_back(reinterpret_cast<const BfmeE16 &>(order));
			}
		}
	}
}
