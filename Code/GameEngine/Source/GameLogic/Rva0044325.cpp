// flags: region default (reverse/retail_inventory/flag_regions.csv)
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime(void);
extern class View *TheTacticalView;
class Rva0044325Holder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07(bool b);
};
#define TheRva00DFEA3C (*(Rva0044325Holder **)&TheTacticalView)

class Rva0044325
{
	char m_pad[0xD8];
	bool m_flag;
	char m_pad2[3];
	unsigned int m_time;
public:
	void f();
};

void Rva0044325::f()
{
	m_flag = (m_flag == 0);
	m_time = timeGetTime();
	if (TheTacticalView)
		TheRva00DFEA3C->slot07(m_flag == 0);
}
