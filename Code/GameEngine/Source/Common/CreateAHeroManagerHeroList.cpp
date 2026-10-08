// cl: /O1 /DNDEBUG /MD
//
// ?rva0021F797@CreateAHeroManager@@QAEPAVRva0040A3F9@@XZ retail 0x0021F797,
// 16 B (the pin name its callers use). Target evidence: on
// TheCreateAHeroManager, runs 0x0021F47E (WorldBuilder names it
// CreateAHeroManager::LoadMyHeroList) and returns the address of the hero
// list at +0x174. The list's class is the callers' placeholder, so the
// member is held as raw storage and returned through a cast.
class Rva0040A3F9;

class CreateAHeroManager
{
public:
	Rva0040A3F9 *rva0021F797();
	void LoadMyHeroList();				// 0x0021F47E

private:
	unsigned char m_pad[0x174];
	unsigned char m_heroList[4];			// +0x174
};

Rva0040A3F9 *CreateAHeroManager::rva0021F797()
{
	LoadMyHeroList();
	return (Rva0040A3F9 *)m_heroList;
}
