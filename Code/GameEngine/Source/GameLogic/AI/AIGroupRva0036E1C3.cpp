// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva0036E1C3@AIGroup@@QAEXABV?$StringBase@D@@H@Z @0x0036E1C3 52B: AIGroup walk members at +0x04 calling Drawable setEmoticon via Thing getDrawable; neighbours AIGroupGetCommandButtonSourceObject Rva0036E346Count; caller 0x003C1F0A.
#include "ascii_string.h"

class Drawable
{
public:
	void setEmoticon(const StringBase<char> &name, int val);
};

class Thing
{
public:
	class Drawable *getDrawable() const;
};

class Object : public Thing
{
};

struct ObjectListNode
{
	ObjectListNode *m_next;
	ObjectListNode *m_prev;
	Object *m_data;
};

class AIGroup
{
public:
	void rva0036E1C3(const StringBase<char> &name, int val);
private:
	int m_00;
	ObjectListNode *m_memberList;
};

// ?getDrawable@Thing@@QBEPAVDrawable@@XZ present-unmatched
// ?setEmoticon@Drawable@@QAEXABV?$StringBase@D@@H@Z present-unmatched
void AIGroup::rva0036E1C3(const StringBase<char> &name, int val)
{
	for (ObjectListNode *it = m_memberList->m_next; it != m_memberList; it = it->m_next) {
		Drawable *d = it->m_data->getDrawable();
		if (d != 0)
			d->setEmoticon(name, val);
	}
}
