// ?rva004406BA@MpGameSetup@@QAEXH@Z
// partial score=0.973 date=2026-10-05
// ?rva004406BA@MpGameSetup@@QAEXH@Z draft: 792B, correct branch shape requires the isAI/local selection reset inside the local-or-host hero-list block (retail skips that test when neither is true). With the direct call at 0x00322714 resolved, the integrated TU scores 0.97258; only 19 byte encodings differ, all from heroBox/def taking edi/ebx where retail has ebx/edi. Pointer declaration order, const, reference, register, and identity-wrapper variants did not change allocation. Before integrating in MpGameSetupSlots.cpp add: GameSlot m_hasHeroData (+0x60) and m_heroData[0x0C] (+0x64); Rva0040A3F9 m_begin/m_end and int size(); Rva00219B9E::sideMask inline wrapper over rva00219F8E; opaque void Rva00322714(GameWindow*, int, bool) at direct target 0x00322714; extern int g_Va00DC8D4C (VA 0x00DC8D4C reads 0xFF808080 via RVA 0x009C8D4C). Identities remain address-derived; no permanent pin made.
// Retail 0x004406BA, 792 bytes. Name unknown. Refills a slot's hero combo
// box (+0x374). With a saved game pending (+0x2B0) it only shows the saved
// slot's hero name. Otherwise "-" (item data -1) and "GUI:Random" (-2),
// and for the local slot or on the host every listed hero from last to
// first (item data its index; "VALUE:Default" appended for +0x48 heroes),
// heroes outside the template's side mask grayed out (0x00322714); the
// listed hero is selected except that, in the local-or-host listing path,
// non-AI remote slots are reset to row 0. Then 0x0043F8B3 and the display
// limit. Callers 0x004427F0, 0x00443D22, 0x004415BE.
void MpGameSetup::rva004406BA(int slot)
{
	if (!g_00DFE344)
		return;
	GameWindow *heroBox = m_hero[slot];
	if (!heroBox)
		return;
	GadgetComboBoxReset(heroBox);
	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(-1);

	if (m_saved)
	{
		GameSlot *saved = &m_saved->m_slots[slot];
		UnicodeString text(L"-");
		const CreateAHeroName *data = saved->m_hasHeroData ? (const CreateAHeroName *)saved->m_heroData : 0;
		if (data)
			text = data->m_name;
		int row = GadgetComboBoxAddEntry(heroBox, text, def->m_color);
		GadgetComboBoxSetSelectedPos(heroBox, row, false);
		return;
	}

	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameSlot *gameSlot = game->getSlot(slot);
	if (!gameSlot)
		return;

	int currentHero = gameSlot->m_hero;
	int select = 0;
	int index = GadgetComboBoxAddEntry(heroBox, UnicodeString(L"-"), def->m_color);
	GadgetComboBoxSetItemData(heroBox, index, (void *)-1);
	index = GadgetComboBoxAddEntry(heroBox, TheGameText->fetch("GUI:Random"), def->m_color);
	GadgetComboBoxSetItemData(heroBox, index, (void *)-2);
	if (currentHero == -2)
		select = index;

	bool local = slot == game->v13();
	if (local || m_owner->v01())
	{
		int side;
		const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(gameSlot->m_playerTemplate);
		if (pt)
			side = pt->rva001FD234();
		else
			side = -1;
		Rva0040A3F9 *heroes = g_00DFE344->rva0021F797();
		int count = heroes->size();
		for (int i = count - 1; i >= 0; --i)
		{
			CreateAHeroData *hero = heroes->rva0040A32F(i);
			if (!hero)
				continue;
			Rva00219F8EMask *mask = g_00DFE344->sideMask(hero->m_0c, hero->m_10);
			bool allowed = side == -1 || mask->test(side);
			int color = allowed ? def->m_color : g_Va00DC8D4C;
			UnicodeString name = ((CreateAHeroName *)hero)->m_name;
			if (hero->m_48)
				name += TheGameText->fetch("VALUE:Default");
			int row = GadgetComboBoxAddEntry(heroBox, name, color);
			GadgetComboBoxSetItemData(heroBox, row, (void *)i);
			if (allowed)
			{
				if (currentHero == i)
					select = row;
			}
			else
				Rva00322714(heroBox, row, true);
		}
		if (!gameSlot->isAI() && !local)
			select = 0;
	}
	GadgetComboBoxSetSelectedPos(heroBox, select, false);
	rva0043F8B3(slot);
	GadgetComboBoxSetMaxDisplay(heroBox, Rva0043DDF8(slot));
}
