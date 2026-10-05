// ?rva004422DD@MpGameSetup@@QAEXXZ
// partial score=0.4 date=2026-10-05
// ?rva004422DD@MpGameSetup@@QAEXXZ draft: 511B vs 522B, same 169-instruction shape once the map key is unsigned (retail copies each int color into a temporary for _M_find@I/operator[]); this/slot take ebx/edi where retail has edi/ebx and one extra spill remains. Needs pins for the map<unsigned,GameSlot*> ctor (0x0033C432), _M_find (0x00357180), operator[] (0x002077D6) and _Rb_tree dtor (0x0043FE62 ??1Rva0043EA9C) under this TU's instantiation names.
// Retail 0x004422DD, 522 bytes. Name unknown. On the host, finds slots
// sharing a color (a human keeps it) or seated without one (unless +0x3DC
// lets colors go unset) and gives each such slot the first offered color
// (+0x3C4) nobody holds, or -1 when colors are optional, through the
// owner's applySlotColor. Called from 0x00442A2A.
void MpGameSetup::rva004422DD()
{
	if (!m_owner->v01())
		return;
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;

	_STL::map<unsigned int, GameSlot *> used;
	bool conflict = false;
	for (unsigned int i = 0; i < 8; ++i)
	{
		GameSlot *slot = game->getSlot(i);
		if (!slot)
			continue;
		int color = slot->m_color;
		if (color < 0)
		{
			if (!m_3dc && !slot->isObserver() && slot->m_state != 1)
				conflict = true;
		}
		else
		{
			if (used.find(color) != used.end())
			{
				conflict = true;
				if (used[color]->isHuman())
					continue;
			}
			used[color] = slot;
		}
	}

	if (conflict)
	{
		for (unsigned int i = 0; i < 8; ++i)
		{
			GameSlot *slot = game->getSlot(i);
			if (!slot)
				continue;
			int color = slot->m_color;
			if (color < 0 && (m_3dc || slot->isObserver() || slot->m_state == 1))
				continue;
			if (used[color] == slot)
				continue;
			if (m_3dc)
			{
				m_owner->applySlotColor(slot, -1);
				continue;
			}
			for (int c = 0; c < m_colorsAvailable.size(); ++c)
			{
				if (m_colorsAvailable[c] && used.find(c) == used.end())
				{
					used[c] = slot;
					m_owner->applySlotColor(slot, c);
					break;
				}
			}
		}
	}
}
