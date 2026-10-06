// cl: /O1 /MD /EHsc
//
// PlayerTemplate.cpp: the PlayerTemplateStore lookups retail links from this TU
// (tu_map approved), folded from two split units with these exact flags. One
// Overridable/PlayerTemplate view carries both bodies' offsets: next override
// at +0x04, name key at +0x10, vector element stride 0x1DC, vector first/last
// at +0x0C/+0x10 of the store. The override hop uses the pinned
// getFinalOverride at 0x001E35DF.

enum NameKeyType
{
	NAMEKEY_INVALID = -1,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
	int m_isOverride;
	int m_extra0C;
};

class PlayerTemplate : public Overridable
{
public:
	NameKeyType m_nameKey; // +0x10
	char m_rest[0x1DC - 0x10 - 4];
};

class PlayerTemplateVector
{
public:
	unsigned size() const { return static_cast<unsigned>(m_last - m_first); }
	const PlayerTemplate &operator[](int index) const { return m_first[index]; }

	PlayerTemplate *m_first;
	PlayerTemplate *m_last;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType namekey) const;
	const PlayerTemplate *getNthPlayerTemplate(int index) const;

private:
	char m_pad[0x0C];
	PlayerTemplateVector m_playerTemplates;
};

// ?findPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@W4NameKeyType@@@Z @0x001FD31B 45B
// BFME1 PlayerTemplate.cpp findPlayerTemplate with BFME2 Overridable final-override lookup.
// Retail vector first/last at +0x0C/+0x10 stride 0x1DC nameKey at +0x10 (PlayerTemplateGetName
// proves key at +0x10 and GetDisplayName proves display name at +0x14). Callers pass a
// NameKeyType e.g. call at 0x002B5D66 after nameToKey at 0x0009FA65.
const PlayerTemplate *PlayerTemplateStore::findPlayerTemplate(NameKeyType namekey) const
{
	for (const PlayerTemplate *it = m_playerTemplates.m_first; it != m_playerTemplates.m_last; ++it)
	{
		if (it->m_nameKey == namekey)
		{
			if (it->m_nextOverride)
				return static_cast<const PlayerTemplate *>(it->m_nextOverride->getFinalOverride());
			return it;
		}
	}
	return 0;
}

// BFME1 PlayerTemplateStore::getNthPlayerTemplate, with the retail
// 0x1DC-byte vector element and its Overridable final-override lookup.
const PlayerTemplate *PlayerTemplateStore::getNthPlayerTemplate(int index) const
{
	if (index >= 0 && static_cast<unsigned>(index) < m_playerTemplates.size()) {
		const PlayerTemplate *playerTemplate = &m_playerTemplates[index];
		const PlayerTemplate *result;
		if (playerTemplate->m_nextOverride)
			result = static_cast<const PlayerTemplate *>(playerTemplate->m_nextOverride->getFinalOverride());
		else
			result = playerTemplate;
		return result;
	}
	return 0;
}
