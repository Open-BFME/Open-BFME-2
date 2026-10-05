// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004A99F6@Rva004A99F6@@QAEXXZ @0x004A99F6 28B: thiscall method passing member +0xE8 to TheAudio slot 0x6C virtual then setting it to 1.
// Evidence: unlock lane; caller 0x004A9A12; TheAudio extern in use ?TheAudio@@3PAVAudioManager@@A; vtable slot 0x6C index 27; member +0xE8 proved by lea and push then dword store of 1.
class AudioManager
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
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void slot108(int x);
};

extern AudioManager *TheAudio;

class Rva004A99F6
{
public:
	void rva004A99F6();
private:
	char m_pad[0xE8];
	int m_e8;
};

void Rva004A99F6::rva004A99F6()
{
	TheAudio->slot108(m_e8);
	m_e8 = 1;
}
