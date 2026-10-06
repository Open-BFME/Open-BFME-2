// cl: /DNDEBUG /MD /EHsc
// ?rva00153664@Rva00153664@@QAEXHPBDPAVRva0015354E@@@Z @0x00153664 134B evidence: chain from 0x001535FF; slots 0x10 0x20 0x04; reuses Rva0015354E +0x10 and Rva001531E6 dec
class Rva0015354E
{
public:
	void rva001535FF(const char *name);
private:
	unsigned char m_pad00[0x10];
	void *m_store10;
};

class Rva001531E6
{
public:
	void rva001531E6();
};

struct EsiObj
{
	virtual int __stdcall s00();
	virtual int __stdcall s04();
	virtual int __stdcall s08();
	virtual int __stdcall s0C();
	virtual int __stdcall s10(const void *a, void *b);
	virtual int __stdcall s14();
	virtual int __stdcall s18();
	virtual int __stdcall s1C();
	virtual void *__stdcall s20(const void *a, int b);
};

struct QueryResult
{
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	int m1C;
	int m20;
	int m24;
	int m28;
};

struct ThisSlots
{
	virtual void t00();
	virtual void t04(int a, void *b, void *c);
};

class Rva00153664
{
public:
	void rva00153664(int arg1, const char *arg2, Rva0015354E *arg3);
};

void Rva00153664::rva00153664(int arg1, const char *arg2, Rva0015354E *arg3)
{
	if (arg1 != 0)
		return;
	EsiObj *esi = *(EsiObj **)arg3;
	QueryResult qr;
	int r = esi->s10(arg2, &qr);
	if (r < 0)
		return;
	if (qr.m08 != 5)
		return;
	arg3->rva001535FF(arg2);
	int count = qr.m20;
	if (count <= 0)
		goto done;
	for (int i = 0; i < count; i++) {
		void *found = esi->s20(arg2, i);
		if (found == 0)
			continue;
		int r2 = esi->s10(found, &qr);
		if (r2 < 0)
			continue;
		((ThisSlots *)this)->t04(qr.m00, found, arg3);
	}
done:
	((Rva001531E6 *)arg3)->rva001531E6();
}
