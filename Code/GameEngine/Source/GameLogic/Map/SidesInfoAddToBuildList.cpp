// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii -Ireference/open-bfme-1/inputs/reference/shims/buildlistinfo -Ireference/open-bfme-1/inputs/reference/shims/moduledata -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Map
// ?addToBuildList@SidesInfo@@QAEXPAVBuildListInfo@@H@Z @ 0x003297FB (68B).
// Sides list nth-entry splice from BFME1 donor SidesList.cpp addToBuildList.
// Evidence: LINK BONUS caller names this mangling; donor Zero Hour and BFME1
// SidesList.cpp:188 same loop; neighbours SidesInfoSetScriptList and SidesList.

typedef int Int;

class BuildListInfo
{
public:
	char m_pad[0x2c];
	BuildListInfo *m_next;
};

class SidesInfo
{
public:
	void addToBuildList(BuildListInfo *pBuildList, Int position);
private:
	BuildListInfo *m_pBuildList;
};

void SidesInfo::addToBuildList(BuildListInfo *pBuildList, Int position)
{
	BuildListInfo *pCur = 0;
	while (position) {
		position--;
		if (pCur == 0) {
			pCur = m_pBuildList;
		} else {
			if (pCur->m_next) {
				pCur = pCur->m_next;
			} else {
				break;
			}
		}
	}
	if (pCur == 0) {
		pBuildList->m_next = m_pBuildList;
		m_pBuildList = pBuildList;
	} else {
		pBuildList->m_next = pCur->m_next;
		pCur->m_next = pBuildList;
	}
}
