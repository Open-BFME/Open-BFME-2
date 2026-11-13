// cl: /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??1Rva00104DB0@@UAE@XZ, retail 0x00104DB0, 54 bytes.
// Evidence: leaf lane pin dtor, callers in Rva00104E03Dtor and deleting dtor, callee Render2DSentenceClass dtor pin 0x00157C70.
#include "../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

class GameWindow;
struct Rva0010500FDrawData;
struct BfmeR1042;
struct Rva00104DE6Font;

// Retail table 0x00BCF7E8: five __purecall slots, then the deleting destructor.
class Rva00104DB0Base
{
public:
	Rva00104DB0Base();
	virtual void drawBorder(GameWindow *window) = 0;
	virtual void rva0010500F(GameWindow *window, Rva0010500FDrawData *data) = 0;
	virtual void addExtents(int left, int top, int right, int bottom) = 0;
	virtual void bfmeGo1042E(BfmeR1042 *rec) = 0;
	virtual void setFont(const Rva00104DE6Font *font) = 0;
	virtual ~Rva00104DB0Base() {}
};
// ??0Rva00104DB0Base@@QAE@XZ @0x00104DA7 9B: the default constructor, storing the
// class's own vtable (VA 0x00BCF7E8) and returning this.
Rva00104DB0Base::Rva00104DB0Base()
{
}

// Retail table 0x00BCF800 (six slots): 0x00105AF3, 0x0010500F, 0x00104E68,
// 0x00105CC7, 0x00104DE6 and the deleting destructor 0x00104F16.
class Rva00104DB0 : public Rva00104DB0Base
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

Rva00104DB0::~Rva00104DB0()
{
}
