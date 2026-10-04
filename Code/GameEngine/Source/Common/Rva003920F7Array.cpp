// cl: /O1 /MD
// ?rva003920F7@Rva003920F7@@QAEXIPBURva003920F7Src@@@Z @0x003920F7 50B unlock: if array at +8 null call pinned init 0x00392092 then bounds check index vs TheWritableGlobalData+0xA94 then copy 12B into element stride 0x1C; callers 0x00393468 etc; unblocks 0x0039321C/0x0039380F.

extern class GlobalData *TheWritableGlobalData;

class GlobalData
{
public:
	char m_pad[0xA94];
	unsigned int m_count;
};

class Rva00392092Target
{
public:
	void rva00392092();
};

struct Rva003920F7Src
{
	int a;
	int b;
	int c;
};

struct Rva003920F7Elem
{
	Rva003920F7Src head;
	char rest[16];
};

class Rva003920F7
{
public:
	void rva003920F7(unsigned int index, const Rva003920F7Src *src);
private:
	char m_pad[8];
	Rva003920F7Elem *m_array;
};

void Rva003920F7::rva003920F7(unsigned int index, const Rva003920F7Src *src)
{
	if (m_array == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index >= TheWritableGlobalData->m_count)
		return;
	m_array[index].head = *src;
}
