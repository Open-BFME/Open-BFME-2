// cl: /MD
// ?Rva0025CEEFCheck@@YA_N_N@Z @0x0025CEEF 59B evidence: sole caller 0x0025D7B6; global VA 0x009FE720; vtable slot 10 refresh; 8-byte records +0x10/+0x14 bounds; wanted flag differs

extern class Keyboard *TheKeyboard;

struct Item0025CEEF
{
	char m_b0;
	char m_b1;
	char m_b2;
	char m_b3;
	int m_rest;
};

class Rva0025CEEFHost
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void refresh();
	char m_pad[0x0c];
	Item0025CEEF *m_begin;
	Item0025CEEF *m_end;
};

bool Rva0025CEEFCheck(bool wanted)
{
	Rva0025CEEFHost *host = (*(Rva0025CEEFHost **)&TheKeyboard);
	bool found = false;
	host->refresh();
	host = (*(Rva0025CEEFHost **)&TheKeyboard);
	Item0025CEEF *end = host->m_end;
	Item0025CEEF *it = host->m_begin;
	for (; it != end; ++it)
	{
		if (it->m_b0 == 1 && (it->m_b2 & 1) && wanted != found)
		{
			found = true;
			break;
		}
	}
	return found;
}
