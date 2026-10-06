// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva002E37E5Write@@YAXPAUTriggerArea002E37E5@@PAVDataChunkOutput@@PAVTriggerFilter002E37E5@@@Z retail 0x002E37E5 145B: writes TriggerAreas chunk with filtered count then each area strings plus int plus sub-writer.
// Evidence: push 1 plus VA 0x00C04BEC "TriggerAreas" to rowed openDataChunk; count loop via virtual slot +4 test with inc [ebp-4] then rowed writeInt; second loop rowed writeAsciiString +0x40 +0x4c plus rowed writeInt +0x44 plus rowed rva0030B2FE +8 then rowed closeDataChunk; chain from 0x0030B2FE.

#include "ascii_string.h"

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);
	void writeInt(int value);
	void writeAsciiString(const AsciiString &textValue);
	void closeDataChunk();
};

struct Rva0030B2B6
{
	void *m_begin;
	void *m_end;
};

class Rva0030B2FE
{
public:
	void rva0030B2FE(DataChunkOutput *out);
private:
	Rva0030B2B6 m_00;
	char m_pad08[0x20];
	int m_28;
};

struct TriggerArea002E37E5
{
	char m_pad00[8];
	Rva0030B2FE m_08;
	char m_pad34[8];
	TriggerArea002E37E5 *m_3c;
	AsciiString m_40;
	int m_44;
	char m_pad48[4];
	AsciiString m_4c;
};

class TriggerFilter002E37E5
{
public:
	virtual void f0();
	virtual bool test(TriggerArea002E37E5 *elem);
};

void __cdecl Rva002E37E5Write(TriggerArea002E37E5 *head, DataChunkOutput *out, TriggerFilter002E37E5 *filter)
{
	out->openDataChunk("TriggerAreas", 1);
	int count = 0;
	for (TriggerArea002E37E5 *elem = head; elem; elem = elem->m_3c)
	{
		if (filter->test(elem))
			++count;
	}
	out->writeInt(count);
	for (; head; head = head->m_3c)
	{
		if (filter->test(head))
		{
			out->writeAsciiString(head->m_40);
			out->writeAsciiString(head->m_4c);
			out->writeInt(head->m_44);
			head->m_08.rva0030B2FE(out);
		}
	}
	out->closeDataChunk();
}
