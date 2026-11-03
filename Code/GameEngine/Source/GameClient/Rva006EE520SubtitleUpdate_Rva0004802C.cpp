// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient -Ireference/shims/bfme2_ascii
// BFME subtitle update body at retail RVA 0x006EE520.
// The address-qualified class keeps the unresolved original method name
// explicit while the manager and sink access views preserve unresolved callee
// identities at their retail addresses.

// stlport
#include <vector>

class Rva006EE520;

#include "unicode_string.h"

class SubtitleEntry;

// The rowed SubTitleManager accessors (0x000468AD, 0x00046973, 0x000469CB,
// 0x00046906) on the same object.
class SubTitleManager
{
public:
	bool HasBeenDisplayed(int index);
	void SetDisplayedStats(int index);
	unsigned int GetColor(int index);
	UnicodeString GetText(int index);
};

class SubtitleManager
{
public:
	int getStartFrame(int index) const;
	SubTitleManager *subTitles() { return (SubTitleManager *)this; }

	char m_pad00[0x14];
	_STL::vector<SubtitleEntry *> m_entries;
};

#include "../../Include/GameClient/SubTitleWindow.h"

class Rva006EE520
{
public:
	void update(int frame);

private:
	char m_pad00[0x184];
	SubtitleManager *m_manager;
	SubTitleWindow *m_sink;
};

void Rva006EE520::update(int frame)
{
	Rva006EE520 *self = this;
	SubtitleManager *manager = self->m_manager;
	if (!manager || !self->m_sink)
		return;

	unsigned int color;
	const int count = (int)manager->m_entries.size();
	for (int i = 0; i < count; ++i)
	{
		int startFrame = self->m_manager->getStartFrame(i);
		if (self->m_manager->subTitles()->HasBeenDisplayed(i) || frame < startFrame)
			continue;

		self->m_sink->rva00260BBF(self->m_manager->subTitles()->GetText(i),
			self->m_manager->subTitles()->GetColor(i));
		self->m_manager->subTitles()->SetDisplayedStats(i);
	}
}
