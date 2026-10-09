// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva00565106@LivingWorldCampaignAct@@QAEXXZ, retail 0x00565106 (66 bytes). Same class as the rowed
// MoveArmies (Rva00565085.cpp, 0x00565085): the second record vector, 20-byte spawn requests at
// +0x38/+0x3C, each handed to LivingWorldLogic::spawnBuilding (0x002B99F8, rowed). WorldBuilder's twin
// 0x0143A8C0 is unnamed, so the method keeps its address token.
class LivingWorldLogic
{
public:
	void spawnBuilding(const struct Rva002B99F8Request *request);	// 0x002B99F8
};
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva002B99F8Request
{
	void *m_vtbl;
	unsigned char m_player[4];
	int m_templateToken;
	unsigned char m_region[4];
	bool m_captured;
};

struct Rva00565106Vector
{
	unsigned size() const { return end - begin; }
	Rva002B99F8Request *begin;
	Rva002B99F8Request *end;
	Rva002B99F8Request *storage;
};

class LivingWorldCampaignAct
{
public:
	void rva00565106();
private:
	unsigned char prefix[0x38];
	Rva00565106Vector requests;
};

void LivingWorldCampaignAct::rva00565106()
{
	for (unsigned i = 0; i < requests.size(); ++i)
		TheLivingWorldLogic->spawnBuilding(&requests.begin[i]);
}
