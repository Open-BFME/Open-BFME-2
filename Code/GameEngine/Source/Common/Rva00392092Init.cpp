// cl: /MD
// ?rva00392092@Rva00392092Target@@QAEXXZ 101B @0x00392092: array init allocating Rva004D9A3C array sized GlobalData count stride 0x1C via new[]. Layout count at +0 array at +8 from dtor row at 0x0039205C. Evidence: dtor call at 0x003920A2 plus GlobalData+0xA94 plus UU at 0x0002FDE0 plus LL at 0x00629512 plus LINK BONUS 5 files.
extern class GlobalData *TheWritableGlobalData;

// Without these MSVC routes new T[n] to scalar ??2 (0x0002FDA0); retail uses array ??_U (0x0002FDE0).
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

class GlobalData
{
public:
	char m_pad[0xA94];
	unsigned int m_count;
};

class Rva004D9A3C
{
public:
	Rva004D9A3C();
	~Rva004D9A3C();
private:
	char m_pad00[0x0C];
	float m_float0C;
	unsigned char m_byte10;
	char m_pad11[0x07];
	int m_int18;
};

class Rva0039205C
{
public:
	~Rva0039205C();
private:
	int m_count00;
	int m_pad04;
	Rva004D9A3C *m_array08;
};

class Rva00392092Target
{
public:
	void rva00392092();
private:
	int m_count00;
	int m_pad04;
	Rva004D9A3C *m_array08;
};

void Rva00392092Target::rva00392092()
{
	((Rva0039205C *)this)->~Rva0039205C();
	unsigned int count = TheWritableGlobalData->m_count;
	m_array08 = new Rva004D9A3C[count];
}
