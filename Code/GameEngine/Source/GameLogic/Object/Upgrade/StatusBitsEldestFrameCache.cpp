// cl: /DNDEBUG /MD /GX /I.
//
// ?cacheGameLogicFrame@StatusBitsEldestFrame@@QAEPAU1@XZ, retail 0x00485975,
// 14 bytes: the +0x1C eldest-frame cache of StatusBitsUpgradeIfEldestKindof
// (ctor 0x004B4A32, its sole caller). WorldBuilder's debug body (0x011C1270,
// unnamed) stores the GameLogic frame (+0x40) into the member and returns
// 'this'; the returned pointer is what puts 'this' in eax and the GameLogic
// object in ecx in the retail bytes.

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

enum NameKeyType
{
	NK_UNKNOWN = 0
};
class Object;
struct Rva00485C19Data;
struct StatusBitsEldestFrame
{
public:
	StatusBitsEldestFrame() { m_cachedFrame = (int)TheGameLogic->getFrame(); }
	StatusBitsEldestFrame *cacheGameLogicFrame(void);
	bool rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key);
private:
	int m_cachedFrame; // +0x00
};

StatusBitsEldestFrame *StatusBitsEldestFrame::cacheGameLogicFrame(void)
{
	m_cachedFrame = (int)TheGameLogic->getFrame();
	return this;
}
