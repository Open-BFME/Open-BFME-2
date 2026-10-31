// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?groupSetEmoticon@AIGroup@@QAEXABV?$StringBase@D@@H@Z @0x0036E1C3 52B: AIGroup walk members at +0x04 calling Drawable setEmoticon via Thing getDrawable; neighbours AIGroupGetCommandButtonSourceObject Rva0036E346Count; caller 0x003C1F0A.
#include <list>
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
	void groupSetEmoticon(const StringBase<char> &name, int val);
private:
	std::list<Object *> m_memberList;
};

// ?getDrawable@Thing@@QBEPAVDrawable@@XZ present-unmatched
// ?setEmoticon@Drawable@@QAEXABV?$StringBase@D@@H@Z present-unmatched
void AIGroup::groupSetEmoticon(const StringBase<char> &name, int val)
{
	for (std::list<Object *>::iterator it = m_memberList.begin(); it != m_memberList.end(); ++it) {
		Drawable *drawable = (*it)->getDrawable();
		if (drawable != 0)
			drawable->setEmoticon(name, val);
	}
}
