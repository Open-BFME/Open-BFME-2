// ?rva0041AB06@Rva0041A644@@QAE_NAAUBfmeNarrowRecord0041A617@@@Z
// partial score=0.94 date=2026-10-06
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target identity: slot 20 of 0x0083AD70; the same table address is stored by Rva0041A644's destructor. Retail evidence shows a mutex at +0x14 and a 16-byte-record deque at +0x44; the record is BfmeNarrowRecord0041A617.
#include <string>
#include "BfmeNarrowRecord0041A617.h"

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int wait);
		~LockClass();

	private:
		char m_pad00[4];

	public:
		bool m_locked;
	};

private:
	char m_storage[8];
};

struct Rva0041A3F7
{
	BfmeNarrowRecord0041A617 *_M_cur;
	BfmeNarrowRecord0041A617 *_M_first;
	BfmeNarrowRecord0041A617 *_M_last;
	BfmeNarrowRecord0041A617 **_M_node;
	void rva0041A4A7();
};

struct NarrowRecordDeque16
{
	Rva0041A3F7 m_begin;
	Rva0041A3F7 m_end;
	char m_mapStorage[0x10];
};

class Rva0041A644 : public GameEngineDeletingBase
{
public:
	bool rva0041AB06(BfmeNarrowRecord0041A617 &out);

private:
	MutexClass m_mutex0c;
	MutexClass m_mutex14;
	char m_otherDeque[0x28];
	NarrowRecordDeque16 m_records44;
	void *m_thread74;
	MutexClass m_mutex78;
	char m_helper80[4];
};

bool Rva0041A644::rva0041AB06(BfmeNarrowRecord0041A617 &out)
{
	MutexClass::LockClass lock(m_mutex14, 0);
	bool copied = false;
	if (!lock.m_locked)
	{
		BfmeNarrowRecord0041A617 *finish = m_records44.m_end._M_cur;
		if (finish != m_records44.m_begin._M_cur)
		{
			out = *m_records44.m_begin._M_cur;
			m_records44.m_begin.rva0041A4A7();
			copied = true;
		}
	}
	return copied;
}
