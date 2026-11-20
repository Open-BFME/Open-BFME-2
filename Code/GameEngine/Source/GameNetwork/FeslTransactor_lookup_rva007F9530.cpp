// cl: /O2 /GX- /GS-
// Retail 0x007F9530 is the FESL transactor's thiscall record lookup.  The
// same layout is reused by the adjacent slot allocator caller.

class Rva007E8810Message;
class Rva007F96C0Hub;
struct Rva007FA170Slot;
struct Rva007F9A40Key
{
 const char *m_a;
 const char *m_b;
 int m_c;
 bool matches(const Rva007F9A40Key *other) const;
};
struct Rva007F96C0Rec
{
 char m_active;
 char m_pad[3];
 Rva007F9A40Key m_key;
 void (__cdecl *fn)(Rva007E8810Message *msg, void *ctx);
 void *ctx;
};
class Rva007FA2C0
{
public:
 void rva007F95A0(Rva007FA170Slot *slot, unsigned timeout);
 bool onTxn(Rva007E8810Message *msg);
 Rva007F96C0Rec *lookup(void *key);
private:
 char m_pad00[0x10];
 int m_count;
 int m_14;
 unsigned m_watermark;
 char m_pad1C[4];
 void *m_20;
 Rva007F96C0Hub *m_hub;
 char m_pad28[0x380];
 Rva007F96C0Rec m_records[0x20];
};



Rva007F96C0Rec *Rva007FA2C0::lookup(void *rawKey)
{
	Rva007F9A40Key *key = (Rva007F9A40Key *)rawKey;
	int index = 0;
	Rva007F96C0Rec *record = key != 0 ? m_records : 0;
	while (key != 0 && index < m_count)
	{
		if (record->m_active != 0 && key->matches(&record->m_key))
			return record;
		++index;
		++record;
	}
	return 0;
}
