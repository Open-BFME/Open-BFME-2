// cl: /MD
//
// ?rva002D2457@Rva002D22CA@@UAE_NXZ
// RVA 0x002D2457 size 135. Slot1 init of Rva002D22CA: registers 9 tables at
// +0x0C via rva002D23ED (indices 4,0,1,2,6,7,9,10,11) then tail-jmps to the
// 0x002D22D5 duplicate-unk validator for its bool result. Evidence: vtable
// slot 1 of 0x00802A20 (ctor 0x002D22AC names Rva002D22CA); 9 call targets
// all rowed rva002D23ED; tail jmp to just-landed validator row.

// g_009FF018: matched references place it at VA 0xdff018; zero-filled at retail, sized to the
// 0xc-byte gap before the next known global there.
char g_009FF018[12];
// g_009FF00C: matched references place it at VA 0xdff00c; zero-filled at retail, sized to the
// 0xc-byte gap before the next known global there.
char g_009FF00C[12];

// The seven GUI callback tables init registers, defined here from the native
// .data words (each entry {key, name, callback}, key 0 until init fills it,
// ending in a null record). Every callback is the ledger row at the native
// address; IMECandidateWindowInput's 0x000910FB is the ICF-shared trivial body
// whose owner row is GameFileClass::Create. Existing data-ledger spellings are
// kept; the element type now carries the 12-byte record.
struct TableEntry
{
	int key;
	const char *name;
	void *func;
};

extern "C" {
void __identifier("?BeaconWindowInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?ControlBarObserverSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?ControlBarSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?GadgetCheckBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetCheckBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetComboBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetHorizontalSliderInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetHorizontalSliderSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetImageComboBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetImageComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetListBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetListBoxMultiInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetListBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetProgressBarSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetPushButtonInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetPushButtonSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetRadioButtonInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetRadioButtonSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetStaticTextInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetStaticTextSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetTabControlInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetTabControlSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetTextEntryInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetTextEntrySystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetVerticalSliderInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GadgetVerticalSliderSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GameWinBlockInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?GeneralsExpPointsSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?IMECandidateMainDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?IMECandidateTextAreaDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?IMECandidateWindowSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?IdleWorkerSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?LeftHUDInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?MapSelectMenuInit@@YAXPAVWindowLayout@@PAX@Z")();
void __identifier("?MapSelectMenuInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?MapSelectMenuShutdown@@YAXPAVWindowLayout@@PAX@Z")();
void __identifier("?MapSelectMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?MapSelectMenuUpdate@@YAXPAVWindowLayout@@PAX@Z")();
void __identifier("?MessageBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?PassMessagesToParentSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?PassSelectedButtonsToParentSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?Rva002D1E55Create@@YGPAVRva0051268C@@PAX@Z")();
void __identifier("?Rva002D1E8FCreate@@YGPAVRva00512AC8@@PAX@Z")();
void __identifier("?Rva002D1F03Create@@YGPAVRva005142B0@@PAX@Z")();
void __identifier("?Rva002D1F3DCreate@@YGPAVRva004E8B38@@PAX@Z")();
void __identifier("?Rva002D1F77Create@@YGPAVAptLanLobby@@PAX@Z")();
void __identifier("?Rva002D1FB1Create@@YGPAVRva00516211@@PAX@Z")();
void __identifier("?Rva002D1FEBCreate@@YGPAVRva004E4A45@@PAX@Z")();
void __identifier("?Rva002D2025Create@@YGPAVRva005173F8@@PAX@Z")();
void __identifier("?Rva002D205FCreate@@YGPAVRva0051A78E@@PAX@Z")();
void __identifier("?Rva002D2099Create@@YGPAVRva0051BADF@@PAX@Z")();
void __identifier("?Rva002D210DCreate@@YGPAVRva0051D1E6@@PAX@Z")();
void __identifier("?Rva002D2147Create@@YGPAVRva005202C8@@PAX@Z")();
void __identifier("?Rva002D2181Create@@YGPAVAptCampaignMenu@@PAX@Z")();
void __identifier("?Rva002D21BBCreate@@YGPAVAptSkirmish@@PAX@Z")();
void __identifier("?Rva002D21FBCreate@@YGPAVRva00523825@@PAX@Z")();
void __identifier("?Rva0043DA1BCreate@@YGPAVRva0043D686@@PAX@Z")();
void __identifier("?Rva0051104DCreate@@YGPAVRva00510FDB@@PAX@Z")();
void __identifier("?createAptScreenObjectives@@YGPAXPAX@Z")();
void __identifier("?createAptScreenQuickMatchMenu@@YGPAXPAX@Z")();
void __identifier("?createMessenger@Rva005114C6@@UAEPAVRva005114C6Messenger@@PAX@Z")();
}

// Native table RVA 0x009bc998: 2 entries and the null record (36 bytes).
TableEntry g_009BC998[3] = {
	{ 0, "IMECandidateMainDraw", (void *)&__identifier("?IMECandidateMainDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") }, // 0x00427858
	{ 0, "IMECandidateTextAreaDraw", (void *)&__identifier("?IMECandidateTextAreaDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") }, // 0x00427936
	{ 0, 0, 0 }
};

// Native table RVA 0x009bc9c0: 21 entries and the null record (264 bytes).
TableEntry g_009BC9C0[22] = {
	{ 0, "PassSelectedButtonsToParentSystem", (void *)&__identifier("?PassSelectedButtonsToParentSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x002c0978
	{ 0, "PassMessagesToParentSystem", (void *)&__identifier("?PassMessagesToParentSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x002c09df
	{ 0, "GadgetPushButtonSystem", (void *)&__identifier("?GadgetPushButtonSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00328639
	{ 0, "GadgetCheckBoxSystem", (void *)&__identifier("?GadgetCheckBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00327b46
	{ 0, "GadgetRadioButtonSystem", (void *)&__identifier("?GadgetRadioButtonSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x003277f9
	{ 0, "GadgetTabControlSystem", (void *)&__identifier("?GadgetTabControlSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00327330
	{ 0, "GadgetListBoxSystem", (void *)&__identifier("?GadgetListBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00325fbf
	{ 0, "GadgetComboBoxSystem", (void *)&__identifier("?GadgetComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00322e6d
	{ 0, "GadgetImageComboBoxSystem", (void *)&__identifier("?GadgetImageComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00323a5b
	{ 0, "GadgetHorizontalSliderSystem", (void *)&__identifier("?GadgetHorizontalSliderSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00321e5c
	{ 0, "GadgetVerticalSliderSystem", (void *)&__identifier("?GadgetVerticalSliderSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x003218b0
	{ 0, "GadgetProgressBarSystem", (void *)&__identifier("?GadgetProgressBarSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x003215cf
	{ 0, "GadgetStaticTextSystem", (void *)&__identifier("?GadgetStaticTextSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00321494
	{ 0, "GadgetTextEntrySystem", (void *)&__identifier("?GadgetTextEntrySystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x003207f5
	{ 0, "MessageBoxSystem", (void *)&__identifier("?MessageBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0044ba8b
	{ 0, "ControlBarSystem", (void *)&__identifier("?ControlBarSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00402455
	{ 0, "ControlBarObserverSystem", (void *)&__identifier("?ControlBarObserverSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0050e6a6
	{ 0, "GeneralsExpPointsSystem", (void *)&__identifier("?GeneralsExpPointsSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0050dd9f
	{ 0, "IdleWorkerSystem", (void *)&__identifier("?IdleWorkerSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0029b0a9
	{ 0, "MapSelectMenuSystem", (void *)&__identifier("?MapSelectMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0050d672
	{ 0, "IMECandidateWindowSystem", (void *)&__identifier("?IMECandidateWindowSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00427810
	{ 0, 0, 0 }
};

// Native table RVA 0x009bcac8: 18 entries and the null record (228 bytes).
TableEntry g_009BCAC8[19] = {
	{ 0, "GameWinBlockInput", (void *)&__identifier("?GameWinBlockInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0031435a
	{ 0, "GadgetPushButtonInput", (void *)&__identifier("?GadgetPushButtonInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00327e5d
	{ 0, "GadgetCheckBoxInput", (void *)&__identifier("?GadgetCheckBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00327938
	{ 0, "GadgetRadioButtonInput", (void *)&__identifier("?GadgetRadioButtonInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00327630
	{ 0, "GadgetTabControlInput", (void *)&__identifier("?GadgetTabControlInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x003273fb
	{ 0, "GadgetListBoxInput", (void *)&__identifier("?GadgetListBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00325635
	{ 0, "GadgetListBoxMultiInput", (void *)&__identifier("?GadgetListBoxMultiInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00324e92
	{ 0, "GadgetComboBoxInput", (void *)&__identifier("?GadgetComboBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00322c25
	{ 0, "GadgetImageComboBoxInput", (void *)&__identifier("?GadgetImageComboBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0032386a
	{ 0, "GadgetHorizontalSliderInput", (void *)&__identifier("?GadgetHorizontalSliderInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00321b50
	{ 0, "GadgetVerticalSliderInput", (void *)&__identifier("?GadgetVerticalSliderInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00321620
	{ 0, "GadgetStaticTextInput", (void *)&__identifier("?GadgetStaticTextInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x003213f0
	{ 0, "GadgetTextEntryInput", (void *)&__identifier("?GadgetTextEntryInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x00320da9
	{ 0, "MapSelectMenuInput", (void *)&__identifier("?MapSelectMenuInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0050d5df
	{ 0, "ControlBarInput", (void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x000d43d0
	{ 0, "LeftHUDInput", (void *)&__identifier("?LeftHUDInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x004020ce
	{ 0, "BeaconWindowInput", (void *)&__identifier("?BeaconWindowInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z") }, // 0x0050dbaa
	{ 0, "IMECandidateWindowInput", (void *)&__identifier("?Create@GameFileClass@@UAEHXZ") }, // 0x000910fb
	{ 0, 0, 0 }
};

// Native table RVA 0x009bc890: 21 entries and the null record (264 bytes).
TableEntry g_009BC890[22] = {
	{ 0, "CampaignReview.apt", (void *)&__identifier("?Rva002D1E8FCreate@@YGPAVRva00512AC8@@PAX@Z") }, // 0x002d1e8f
	{ 0, "CreateAHero.apt", (void *)&__identifier("?Rva002D1F03Create@@YGPAVRva005142B0@@PAX@Z") }, // 0x002d1f03
	{ 0, "DisconnectScreen.apt", (void *)&__identifier("?createAptScreenObjectives@@YGPAXPAX@Z") }, // 0x002d1ec9
	{ 0, "InGameChat.apt", (void *)&__identifier("?Rva002D1F3DCreate@@YGPAVRva004E8B38@@PAX@Z") }, // 0x002d1f3d
	{ 0, "LanLobby.apt", (void *)&__identifier("?Rva002D1F77Create@@YGPAVAptLanLobby@@PAX@Z") }, // 0x002d1f77
	{ 0, "LoadScreen.apt", (void *)&__identifier("?Rva002D1E55Create@@YGPAVRva0051268C@@PAX@Z") }, // 0x002d1e55
	{ 0, "MainMenu.apt", (void *)&__identifier("?Rva002D1FB1Create@@YGPAVRva00516211@@PAX@Z") }, // 0x002d1fb1
	{ 0, "Messenger.apt", (void *)&__identifier("?createMessenger@Rva005114C6@@UAEPAVRva005114C6Messenger@@PAX@Z") }, // 0x005114c6
	{ 0, "Objectives.apt", (void *)&__identifier("?Rva002D1FEBCreate@@YGPAVRva004E4A45@@PAX@Z") }, // 0x002d1feb
	{ 0, "OnlineShell.apt", (void *)&__identifier("?Rva002D2025Create@@YGPAVRva005173F8@@PAX@Z") }, // 0x002d2025
	{ 0, "Options.apt", (void *)&__identifier("?Rva002D205FCreate@@YGPAVRva0051A78E@@PAX@Z") }, // 0x002d205f
	{ 0, "PlayerStatus.apt", (void *)&__identifier("?Rva002D1FEBCreate@@YGPAVRva004E4A45@@PAX@Z") }, // 0x002d1feb
	{ 0, "PlayerTribute.apt", (void *)&__identifier("?Rva0051104DCreate@@YGPAVRva00510FDB@@PAX@Z") }, // 0x0051104d
	{ 0, "QuitMenu.apt", (void *)&__identifier("?Rva002D2099Create@@YGPAVRva0051BADF@@PAX@Z") }, // 0x002d2099
	{ 0, "SaveLoad.apt", (void *)&__identifier("?createAptScreenQuickMatchMenu@@YGPAXPAX@Z") }, // 0x002d20d3
	{ 0, "ScoreScreen.apt", (void *)&__identifier("?Rva002D210DCreate@@YGPAVRva0051D1E6@@PAX@Z") }, // 0x002d210d
	{ 0, "Skirmish.apt", (void *)&__identifier("?Rva002D21BBCreate@@YGPAVAptSkirmish@@PAX@Z") }, // 0x002d21bb
	{ 0, "SpellStore.apt", (void *)&__identifier("?Rva0043DA1BCreate@@YGPAVRva0043D686@@PAX@Z") }, // 0x0043da1b
	{ 0, "StrategicPlayerStatus.apt", (void *)&__identifier("?Rva002D21FBCreate@@YGPAVRva00523825@@PAX@Z") }, // 0x002d21fb
	{ 0, "TimeLine.apt", (void *)&__identifier("?Rva002D2147Create@@YGPAVRva005202C8@@PAX@Z") }, // 0x002d2147
	{ 0, "CampaignMenu.apt", (void *)&__identifier("?Rva002D2181Create@@YGPAVAptCampaignMenu@@PAX@Z") }, // 0x002d2181
	{ 0, 0, 0 }
};

// Native table RVA 0x009bcbac: 1 entries and the null record (24 bytes).
TableEntry g_009BCBAC[2] = {
	{ 0, "MapSelectMenuInit", (void *)&__identifier("?MapSelectMenuInit@@YAXPAVWindowLayout@@PAX@Z") }, // 0x0050d2ef
	{ 0, 0, 0 }
};

// Native table RVA 0x009bcbc4: 1 entries and the null record (24 bytes).
TableEntry g_009BCBC4[2] = {
	{ 0, "MapSelectMenuUpdate", (void *)&__identifier("?MapSelectMenuUpdate@@YAXPAVWindowLayout@@PAX@Z") }, // 0x0050d136
	{ 0, 0, 0 }
};

// Native table RVA 0x009bcbdc: 1 entries and the null record (24 bytes).
TableEntry g_009BCBDC[2] = {
	{ 0, "MapSelectMenuShutdown", (void *)&__identifier("?MapSelectMenuShutdown@@YAXPAVWindowLayout@@PAX@Z") }, // 0x0050ceab
	{ 0, 0, 0 }
};

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva002D22CA : public GameEngineDeletingBase
{
public:
	void rva002D23ED(void *table, int index);
	bool rva002D22D5();
	virtual bool rva002D2457();
};

bool Rva002D22CA::rva002D2457()
{
	rva002D23ED(g_009BC998, 4);
	rva002D23ED(g_009BC9C0, 0);
	rva002D23ED(g_009BCAC8, 1);
	rva002D23ED(g_009FF018, 2);
	rva002D23ED(g_009BC890, 6);
	rva002D23ED(g_009BCBAC, 7);
	rva002D23ED(g_009BCBC4, 9);
	rva002D23ED(g_009BCBDC, 10);
	rva002D23ED(g_009FF00C, 11);
	return rva002D22D5();
}
