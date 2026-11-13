// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Adapted from Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameClient/GUI/Gen0078D1C0Ctor.cpp.
// Native 0x00104EBF..0x00104F16: sentence at +4; following fields at
// C8, CC, D0, D4 and D5. Its matched destructor calls the sentence
// destructor at 0x00157C70 on the same +4 member.

class GameWindow;
struct Rva0010500FDrawData;
struct BfmeR1042;
struct Rva00104DE6Font;

// The base (retail table 0x00BCF7E8: five __purecall slots, then the deleting
// destructor) under this unit's stand-in name. Retail inlines its constructor
// into 0x00104EBF and keeps an out-of-line copy at 0x00104DA7, which is rowed
// in Rva00104DB0Dtor.cpp as ??0Rva00104DB0Base; the compiler emits this unit's
// copy too, so spelling the base Rva00104DB0Base here defines that symbol twice.
class Gen0078D1C0Base
{
public:
	virtual void drawBorder(GameWindow *window) = 0;
	virtual void rva0010500F(GameWindow *window, Rva0010500FDrawData *data) = 0;
	virtual void addExtents(int left, int top, int right, int bottom) = 0;
	virtual void bfmeGo1042E(BfmeR1042 *rec) = 0;
	virtual void setFont(const Rva00104DE6Font *font) = 0;
	virtual ~Gen0078D1C0Base() {}
};

#include "../../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

// Retail table 0x00BCF800 (six slots): 0x00105AF3, 0x0010500F, 0x00104E68,
// 0x00105CC7, 0x00104DE6 and the deleting destructor 0x00104F16.
class Rva00104DB0 : public Gen0078D1C0Base
{
public:
	Rva00104DB0();
	virtual void drawBorder(GameWindow *window);
	virtual void rva0010500F(GameWindow *window, Rva0010500FDrawData *data);
	virtual void addExtents(int left, int top, int right, int bottom);
	virtual void bfmeGo1042E(BfmeR1042 *rec);
	virtual void setFont(const Rva00104DE6Font *font);
	virtual ~Rva00104DB0();
private:
	Render2DSentenceClass m_sentence;
	int m_first;
	int m_second;
	unsigned int m_color;
	bool m_firstFlag;
	bool m_secondFlag;
};

Rva00104DB0::Rva00104DB0()
{
	m_second = 0;
	m_first = 0;
	m_firstFlag = false;
	m_secondFlag = false;
	m_color = 0x00FFFFFF;
}
