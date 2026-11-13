struct BfmeR1042
{
	char *m_bfmeName;
};

class BfmeSub1042
{
public:
	void bfmeSet1042(char *text, int a, int b);
};


class GameWindow;
struct Rva0010500FDrawData;
struct Rva00104DE6Font;
// Retail table 0x00BCF7E8: five __purecall slots, then the deleting destructor.
class Rva00104DB0Base
{
public:
	Rva00104DB0Base() {}
	virtual void drawBorder(GameWindow *window) = 0;
	virtual void rva0010500F(GameWindow *window, Rva0010500FDrawData *data) = 0;
	virtual void addExtents(int left, int top, int right, int bottom) = 0;
	virtual void bfmeGo1042E(BfmeR1042 *rec) = 0;
	virtual void setFont(const Rva00104DE6Font *font) = 0;
	virtual ~Rva00104DB0Base() {}
};
// Retail table 0x00BCF800 (six slots); see Rva00104DB0Dtor.cpp.
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

	BfmeSub1042 m_bfmeSub;
	char m_bfmePad2[0xcf];
	char m_bfmeFlag;
};

// ?bfmeGo1042E@Rva00104DB0@@UAEXPAUBfmeR1042@@@Z
void Rva00104DB0::bfmeGo1042E(BfmeR1042 *rec)
{
	char *text;

	if (rec->m_bfmeName != 0)
		text = rec->m_bfmeName + 8;
	else
		text = (char *)L"";

	m_bfmeSub.bfmeSet1042(text, 0, 0);
	m_bfmeFlag = 1;
}
