// ?rva000BBE86@Rva000BBE86@@QAEXPAVRva000BBE86Arg@@@Z
// partial score=0.28 date=2026-10-07
// cl: /O1 /DNDEBUG /MD
// ?rva000BBE86@Rva000BBE86@@QAEXPAVRva000BBE86Arg@@@Z @0x000BBE86 197B.
// One pass over the first 0x18-byte record at +0xD0. setFPMode then the
// 0x000B4A9F string, and rowed flag/isEmpty checks before the map lookup.

template<class T>
class StringBase
{
public:
	bool isEmpty() const;
};

void setFPMode();
int Rva000B2CBDGet();

class Rva000BBE86Arg
{
public:
	void *rva000BBDDF(void *key, int *slot);
};

struct Rva000BBE86Rec
{
	void *m_key0;
	void *m_key4;
	char m_pad[8];
	int m_slot10;
	int m_slot14;
};

class Rva000BBE86
{
public:
	void rva000BBE86(Rva000BBE86Arg *arg);
	StringBase<char> *rva000B4A9F();

	char m_pad[0xD0];
	char *m_begin;
	char *m_end;
	char m_padD8[0xF5 - 0xD8];
	unsigned char m_flag;
};

void Rva000BBE86::rva000BBE86(Rva000BBE86Arg *arg)
{
	if (m_flag)
		return;
	setFPMode();
	StringBase<char> *text = rva000B4A9F();
	unsigned index = 0;
	int offset = 0;
again:
	int count = (m_end - m_begin) / 0x18;
	if (index >= (unsigned)count)
		goto done;
	{
		Rva000BBE86Rec *rec = (Rva000BBE86Rec *)(m_begin + offset);
		if ((unsigned char)Rva000B2CBDGet() == 0 || text->isEmpty())
			goto clear_both;
		if (!rec->m_key0)
			goto zero10;
		{
			void *found = arg->rva000BBDDF(rec->m_key0, &rec->m_slot10);
			if (!found)
				rec->m_slot10 = 0;
		}
		goto key4;
zero10:
		rec->m_slot10 = 0;
key4:
		if (!rec->m_key4)
			goto zero14;
		{
			void *found = arg->rva000BBDDF(rec->m_key4, &rec->m_slot14);
			if (!found)
				rec->m_slot14 = 0;
		}
		goto step;
clear_both:
		rec->m_slot10 = 0;
zero14:
		rec->m_slot14 = 0;
step:
		offset += 0x18;
		++index;
		if (offset < 0x18)
			goto again;
	}
done:
	m_flag = 1;
}
