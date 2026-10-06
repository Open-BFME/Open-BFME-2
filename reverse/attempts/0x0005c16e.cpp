// ?rva0005C16E@MilesAudioManager@@QAEXXZ
// partial score=0.85 date=2026-10-06
// cl: /O1 /Oy- /Oi- /Ob1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /arch:SSE2 /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0005C16E@MilesAudioManager@@QAEXXZ @0x0005C16E 206B.
// Drain the three 4-byte pending slots at +0xB48. A null slot is skipped; else
// the circular sentinel list at +0xA48 (a 4-byte _STL::list object, walked
// here by hand) is searched for the slot value, with the two goto-clear exits
// the compiler shapes as direct jne-to-clear jumps. A hit only clears the
// slot; a miss notifies rowed rva000581FA over the 5BA08 event/info layouts
// (same +0x1C/+8/+0xB8/+0x30 facts), calls pinned rva00053AFA, forwards the
// rowed rva0005A9F8 volume into the +0xC sink (rowed rva000A8AEE, pinned
// rva000A8ACC on the same subobject), appends the slot through the rowed
// list<Rva0036CA00Str> push_back, and clears. Element stride 4 confirms the
// 4-byte Rva0036CA00Str element; the reinterpret_cast push_back idiom mirrors
// MilesAudioManagerInitSamplePools. Address-derived name; identity unproven.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef float Real;

class Rva0036CA00Str
{
public:
	void *m_item;
};

struct Rva0005C16ENode
{
	Rva0005C16ENode *m_next;
	Rva0005C16ENode *m_prev;
	Rva0036CA00Str m_data;
};

struct Rva0005BA08List
{
	void *m_begin;
	void *m_end;
	bool empty() const { return m_begin == m_end; }
};

struct Rva0005BA08AudioInfo
{
	char m_pad00[0xa8];
	Real m_reverbWet;
	Real m_reverbDry;
	char m_padB0[8];
	Rva0005BA08List m_list;
};

struct Rva0005BA08InfoRef
{
	Rva0005BA08AudioInfo *m_info;
};

struct Rva0005BA08AudioEvent
{
	char m_pad00[8];
	Rva0005BA08InfoRef m_info;
	char m_pad0C[0x30 - 0x0c];
	int m_value30;
	char m_pad34[0x64 - 0x34];
	Real m_delay;
};

struct Rva0005BA08PlayingAudio
{
	char m_pad00[0x1c];
	Rva0005BA08AudioEvent *m_event;
};

class Rva000A8AEE
{
public:
	void rva000A8AEE(Real x);
	void rva000A8ACC();
};

class Rva00050D6C
{
public:
	int rva00050D6C();
};

class Rva000A8C9B
{
public:
	void clear();
};

class MilesAudioManager
{
public:
	void rva0005C16E();
	void rva00053AFA(void *slot);
	Real rva0005A9F8(void *ref, int a, int b);
	void rva000581FA(const Rva0005BA08InfoRef &info, int value);
private:
	char m_pad000[0xA48];
	_STL::list<Rva0036CA00Str> m_pendingA48;
	char m_padA4C[0xB48 - 0xA4C];
	Rva0036CA00Str m_slotsB48[3];
};

void MilesAudioManager::rva0005C16E()
{
	Rva0036CA00Str *slot = m_slotsB48;
	for (int k = 3; k > 0; k--)
	{
		if (slot->m_item != 0)
		{
			_STL::list<Rva0036CA00Str> &pending = m_pendingA48;
			Rva0005C16ENode *head = (Rva0005C16ENode *)pending._M_node._M_data;
			Rva0005C16ENode *n = head->m_next;
			bool found = false;
			if (n != head)
			{
				do
				{
					if (found)
						goto clear_slot;
					if (n->m_data.m_item == slot->m_item)
						found = true;
					n = n->m_next;
				} while (n != head);
				if (found)
					goto clear_slot;
			}
			Rva0005BA08PlayingAudio *pa =
				(Rva0005BA08PlayingAudio *)slot->m_item;
			Rva0005BA08AudioEvent *event = pa->m_event;
			Rva0005BA08InfoRef *ref = &event->m_info;
			Rva0005BA08List *lst = &ref->m_info->m_list;
			if (!lst->empty())
				rva000581FA(*ref, event->m_value30);
			rva00053AFA(slot);
			Real vol = rva0005A9F8(slot, 1, 1);
			((Rva000A8AEE *)((char *)pa + 0xC))->rva000A8AEE(vol);
			pending.push_back(*slot);
			Rva00050D6C *gate = (Rva00050D6C *)slot->m_item;
			if (!(char)gate->rva00050D6C())
				((Rva000A8AEE *)((char *)gate + 0xC))->rva000A8ACC();
		clear_slot:
			((Rva000A8C9B *)slot)->clear();
		}
		slot++;
	}
}
