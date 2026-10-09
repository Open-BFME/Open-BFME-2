// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// Four float scoring helpers of LivingWorldAIBuilder (retail 0x0059CF34
// 0x0059CFAA 0x0059D089 0x0059D1DD; thiscall RET 0x10 each). They sit between the
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

struct Rva0059CFAARegion
{
	char m_pad00[0x14];
	int m_id;
	char m_pad18[0xc];
	_STL::vector<int> m_24;
};

struct Rva0059D089Template
{
	char m_pad00[0x30];
	float m_30;
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
	float rva0059D1DD(int playerId, Rva0059D089Template *tmpl,
		Rva0059CFAACallee *armies, Rva0059CFAARegion *const &region);
private:
	int m_00;
	int m_04;
	int m_08;
};

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
		armies->rva00500659(playerId, &region->m_id, &defenders);
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
		armies->rva00500659(playerId, &region->m_id, &defenders);
		armies->rva004FFB00(playerId, &region->m_id, &distance);
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
	for (int i = 0; i < (int)region->m_24.size(); ++i)
		score *= 1.0f - 0.1f * tmpl->m_30;
	int defenders = 0;
	int distance = 0;
	armies->rva00500659(playerId, &region->m_id, &defenders);
	armies->rva004FFB00(playerId, &region->m_id, &distance);
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
	for (int i = 1; i < (int)region->m_24.size(); ++i)
		score *= 1.0f - 0.1f * tmpl->m_30;
	int defenders = 0;
	armies->rva00500659(playerId, &region->m_id, &defenders);
	if (defenders < 3)
		score *= (float)((5 - defenders) * (5 - defenders));
	else
		score = rva0059D089(playerId, tmpl, armies, region);
	return score;
}
