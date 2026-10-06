// cl: /MD /GX
// GameClient::addIconLayer (WorldBuilder name, GameClient.cpp lines 1605..1606: push_back onto the indexed icon-layer list at +0xF8).
// was ?rva00239FCC@Rva00239FCC@@QAEXHPAVDrawable@@@Z @0x00239FCC (24B):
// indexed list push_back. Retail: eax=&arg2; push eax; eax=arg1;
// ecx=this+eax*4+0xF8; call list<Drawable*>::push_back (0x239E0B); ret 8.
// Manual index*4 arithmetic forces the scale-4 lea; the list call is a
// TU-local declaration pinned to the rowed 0x239E0B (see symbols.csv);
// address-derived outer name, no STL headers.
class Drawable
{
public:
	char m_pad[4];
};

class DrawableList
{
public:
	void pushBack(const Drawable *&d);
};

class GameClient
{
public:
	void addIconLayer(int index, Drawable *value);
private:
	char m_pad[0xF8];
};

// was ?rva00239FCC@Rva00239FCC@@QAEXHPAVDrawable@@@Z
void GameClient::addIconLayer(int index, Drawable *value)
{
	((DrawableList *)((char *)this + 0xF8 + index * 4))->pushBack((const Drawable *&)value);
}
