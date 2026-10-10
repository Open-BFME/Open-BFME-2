// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1Rva007E3C20Vp6Stream@@UAE@XZ, retail 0x00090840..0x000908F6 (182
// bytes, EH): the VP6 stream's destructor, called by its scalar deleting
// destructor (??_GRva0090840, call at 0x00091156; table 0x00BC7F20).
//
// Ported from Open-BFME-1's
// game/GameEngine/Source/Common/Rva007E3C20Vp6StreamDtor.cpp (reference
// @ 575ba2b04). BFME 2 target differences, each read off retail: the +0x2C
// owner is destroyed through its slot-1 virtual destructor and then the
// global operator delete (a ::delete); the +0x54 buffer is released by the
// rowed Rva00090714Free (0x00090714) and cleared under a single test; the
// audio handles at +0x5C/+0x60 go to TheAudio slot 27. The +0x1C member and
// the base keep the ledger's spellings for their bodies (rowed 0x00106A2D,
// pinned 0x0068A110). The layout is the rowed constructor 0x000907C1's.

class Gen_uwm_0068a110
{
public:
	virtual void slot0();
	~Gen_uwm_0068a110();
private:
	int m_count;
	int m_first;
	int m_second;
	int m_flags;
};

class Rva00106874Host
{
public:
	~Rva00106874Host();
private:
	int m_word0;
	int m_word1;
	int m_word2;
	int m_word3;
};

class Rva00090840Owner
{
public:
	virtual void spare();
	virtual ~Rva00090840Owner();
};

class AudioManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual void release(int handle);
};
extern AudioManager *TheAudio;

struct CodecState;
int bfmeFreeCodecJW(CodecState **p);
void Rva00090714Free(void **p);

class Rva007E3C20Vp6Stream : public Gen_uwm_0068a110
{
public:
	virtual ~Rva007E3C20Vp6Stream();

private:
	void *m_at14;
	void *m_at18;
	Rva00106874Host m_parser;
	Rva00090840Owner *m_at2c;
	int m_at30;
	int m_at34;
	unsigned char m_at38;
	int m_at3c;
	int m_at40;
	int m_at44;
	int m_at48;
	int m_at4c;
	int m_at50;
	void *m_at54;
	int m_at58;
	int m_at5c;
	int m_at60;
};

Rva007E3C20Vp6Stream::~Rva007E3C20Vp6Stream()
{
	if (m_at14 != 0) {
		bfmeFreeCodecJW((CodecState **)&m_at14);
		m_at14 = 0;
	}
	if (m_at18 != 0) {
		bfmeFreeCodecJW((CodecState **)&m_at18);
		m_at18 = 0;
	}
	if (m_at2c != 0) {
		::delete m_at2c;
		m_at2c = 0;
	}
	if (m_at54 != 0) {
		Rva00090714Free(&m_at54);
		m_at54 = 0;
	}
	if (m_at5c != 1)
		TheAudio->release(m_at5c);
	if (m_at60 != 1)
		TheAudio->release(m_at60);
}
