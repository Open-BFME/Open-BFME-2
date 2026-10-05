// ?rva004424E7@MpGameSetup@@QAEXH@Z
// partial score=0.6 date=2026-10-05
// ?rva004424E7@MpGameSetup@@QAEXH@Z draft (whole MpGameSetupSlots.cpp TU with it appended): 731B vs 734B; same block structure (map<int,int> walk at ThePlayerTemplateStore+0x18 through a reference local, Random/Observer entries, Rva00441E4DFaction filter) but retail keeps slot in memory and gameSlot in ebx while cl puts slot in ebx and gameSlot on the stack. Tried no comboBox local, local-flag declaration order, const pointers. Needs pin ?rva0057C71F@Rva0057E3DB@@QAEPAURva0057C71FEntry@@H@Z=0x0057C71F.
// Compile inside Code/GameEngine/Source/GameClient/GUI/MpGameSetupSlots.cpp after adding:
// PlayerTemplate fields m_side (+0x18), m_150, m_151; PlayerTemplateStore with _STL::map<int,int> m_map at +0x18 (#include <map>);
// GlobalData::m_9d4 (+0x9D4) and extern TheGlobalData; Rva0057C71FEntry::m_0c (+0x0C); bool Rva00441E4DFaction(void *, const AsciiString &).
// Retail 0x004424E7, 734 bytes. Name unknown. Refills a slot's player
// template combo box (+0x334). Another player's slot only gets "-" (item
// data its template). Otherwise: "GUI:Random" unless the scenario entry
// (0x0057C71F) or TheGlobalData forbid it, every listed template the entry
// allows (Rva00441E4DFaction) and, for a human outside rules mode 1 and
// without flag 4, "GUI:Observer"; the previous choice stays selected.
// Callers 0x004427E0, 0x00443D0C, 0x00442B1B.
void MpGameSetup::rva004424E7(int slot)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameSlot *gameSlot = game->getSlot(slot);
	if (!gameSlot)
		return;
	GameWindow *comboBox = m_playerTemplate[slot];
	if (!comboBox)
		return;

	MultiplayerColorDefinition *color = TheMultiplayerSettings->getColor(-1);
	int previous = -1;
	int index = 0;
	GadgetComboBoxGetSelectedPos(comboBox, &index);
	if (index >= 0)
		previous = (int)GadgetComboBoxGetItemData(comboBox, index);
	GadgetComboBoxReset(comboBox);

	int mode = m_60.m_mode;
	bool mode1 = mode == 1;
	bool allowObserver = !gameSlot->isAI() && !(m_flags & 4) && !mode1;
	bool local = slot == game->v13();
	bool hostAI = m_owner->v01() && gameSlot->isAI();
	if (!local && !hostAI)
	{
		int playerTemplate = gameSlot->m_playerTemplate;
		index = GadgetComboBoxAddEntry(comboBox, UnicodeString(L"-"), color->m_color);
		GadgetComboBoxSetItemData(comboBox, index, (void *)playerTemplate);
		GadgetComboBoxSetSelectedPos(comboBox, 0, false);
		return;
	}

	bool addRandom = true;
	Rva0057C71FEntry *entry = m_60.rva0057C71F(slot);
	if (entry)
	{
		if (mode1)
			addRandom = false;
		else
			addRandom = entry->m_0c != 1;
	}
	if (TheGlobalData->m_9d4 & 3)
		addRandom = false;
	if (addRandom)
	{
		index = GadgetComboBoxAddEntry(comboBox, TheGameText->fetch("GUI:Random"), color->m_color);
		GadgetComboBoxSetItemData(comboBox, index, (void *)-1);
	}

	int select = 0;
	_STL::map<int, int> &templates = ThePlayerTemplateStore->m_map;
	for (_STL::map<int, int>::iterator it = templates.begin(); it != templates.end(); ++it)
	{
		int templateIndex = it->first;
		const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(templateIndex);
		if (pt && pt->m_151 && !pt->m_150)
		{
			if (!entry || Rva00441E4DFaction(entry, pt->m_side))
			{
				UnicodeString name = pt->getDisplayName();
				index = GadgetComboBoxAddEntry(comboBox, name, color->m_color);
				GadgetComboBoxSetItemData(comboBox, index, (void *)templateIndex);
				if (previous == templateIndex)
					select = index;
			}
		}
	}
	if (!entry && allowObserver)
	{
		index = GadgetComboBoxAddEntry(comboBox, TheGameText->fetch("GUI:Observer"), TheMultiplayerSettings->getColor(-2)->m_color);
		GadgetComboBoxSetItemData(comboBox, index, (void *)-2);
		if (previous == -2)
			select = index;
	}
	GadgetComboBoxSetSelectedPos(comboBox, select, false);
	GadgetComboBoxSetMaxDisplay(comboBox, Rva0043DDF8(slot));
}
