// cl: /O1 /DNDEBUG /MD
//
// ?rva0049CCF0@Rva0049CCF0@@QAEXH@Z @0x0049CCF0 52B ret 4.
// When the owner at this-0x18 has a controlling player, look the argument
// up in the player's +0x738 table and pass that pointer to virtual slot
// 0x2C. The owner is reloaded for the second lookup.

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva0037E915
{
public:
	void *rva0037E915(int index);
};

class Player
{
public:
	char m_pad[0x738];
	Rva0037E915 m_table;
};

class Rva0049CCF0
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11(void *item);
	void rva0049CCF0(int arg);
};

void Rva0049CCF0::rva0049CCF0(int arg)
{
	if ((*(Object **)((char *)this - 0x18))->getControllingPlayer() != 0)
	{
		Player *player = (*(Object **)((char *)this - 0x18))->getControllingPlayer();
		s11(player->m_table.rva0037E915(arg));
	}
}
