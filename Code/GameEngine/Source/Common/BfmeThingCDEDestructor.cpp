// cl: /O2 /DNDEBUG /MD /EHs-c- /Ob2
// ?bfmeDtorCDE@BfmeThingCDE@@QAEXXZ
//
// Ported from Open-BFME-1 Code/Libraries/Source/shroudmanager/shroudmanager_data.cpp.
// The BFME2 array runs 20 wide where the donor runs 16. The node at 0x008F7EC0
// clears the same 0x10-byte entries that this destructor passes to the
// array-delete helper. Its Ghidra body has no source row, so the member call
// uses an address pin for that helper.

struct RectCOI;
struct ShroudManagerImpl008FBA40ElementLayout
{
 RectCOI *first;
 unsigned short playerState[20][4];
 unsigned generation; // +A4 deduplicates rectangle samples
};
struct RectCOI
{
 ShroudManagerImpl008FBA40ElementLayout *cell;
 void *owner;
 RectCOI **previous;
 RectCOI *next;
};
float Cos(float angle);
float Sin(float angle);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);
// Native REAL_TO_INT uses FISTP with the current x87 rounding control;
// reuse the verified manager conversion helper rather than a truncating C++ cast.
__forceinline int rectInteger(float value)
{
 int result;
 __asm
 {
  fld [value]
  fistp [result]
 }
 return result;
}
// Native 73A54A/566 and 73A5CB/5D9 prove this generation word's role.
// The original identifier is unknown; its four loader-zero bytes are data-rowed.
unsigned ShroudCoverageVisitGeneration=0;

class ShroudManagerImpl
{
public:
 void QueueUndoShroudReveal(int x,int y,int *radii,float rotation,unsigned mask);
 char opaque00[0x1C];
 float cellSize,scale;
private:
 ShroudManagerImpl008FBA40ElementLayout *elementAtByCoord_Rva0073A1D0(float x,float y)const;
 friend class BfmeThingCDE;
};
class Gen_008F7CD0
{
public:
 void rva0073CE90(int x,int y,int radius,int counter,int amount,int mask);
};

class CDEVirtualBase
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3(void *arg);
};

class CDELeading
{
public:
	virtual void f0();
	virtual void f1();
};

class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
public:
	virtual void f0();
};

class CDELinkNode
{
public:
	void *m_00;
	char m_pad04[8];
	void *m_0c;
	char m_pad10[4];
	void *m_14;
};

struct CDEArraySlot
{
	void *activeNode;
	int unused04;
	void *prevNode;
	void *nextNode;
};

struct CDEListNode
{
	void *nextNode;
	int unused04;
	void *prevNode;
};

class BfmeThingCDE
{
public:
	bool bfmeCheckABI();
	void bfmeDtorCDE();
	void d_008f7990();
	bool DoRectFill(float x,float y,float halfX,float halfY,float angle);
	void d_008f7ec0();

	void *m_owner;
	CDEProvider *m_ptr4;
	CDEProvider *m_ptr8;
	CDELinkNode *m_link0;
	CDELinkNode *m_link1;
	CDELinkNode *m_prev;
	CDELinkNode *m_next;
	void *m_array;
	int m_count;
	int m_values[20];
	int m_slots[20];
	unsigned char m_status[20];
	int m_cellX; // +D8
	int m_cellY; // +DC
	int m_revealRadii[3]; // +E0
	unsigned m_revealMask; // +EC
	float m_rotation; // +F0
	int m_changeRadii[3]; // +F4
	int m_changeMasks[3]; // +100
	int m_changeAmounts[3]; // +10C
};

#pragma comment(linker, "/alternatename:?ArrayDeleteHelperBodyThunk@@YGXPAXII0@Z=??_M@YGXPAXIHP6EX0@Z@Z")

void __stdcall ArrayDeleteHelperBodyThunk(void *, unsigned, unsigned, void *);
extern void __cdecl operator delete[](void *);

void BfmeThingCDE::d_008f7ec0()
{
	CDEArraySlot *endSlot = (CDEArraySlot *)((char *)m_array + (m_count << 4));
	CDEArraySlot *curSlot = (CDEArraySlot *)m_array;
	if (curSlot == endSlot)
		return;
	while (curSlot != endSlot)
	{
		if (curSlot->activeNode == 0)
			return;
		void *nextNode = curSlot->nextNode;
		curSlot->activeNode = 0;
		if (nextNode != 0)
			((CDEListNode *)nextNode)->prevNode = curSlot->prevNode;
		void *prevNode = curSlot->prevNode;
		void *linkNode = curSlot->nextNode;
		curSlot = (CDEArraySlot *)((char *)curSlot + 0x10);
		((CDEListNode *)prevNode)->nextNode = linkNode;
	}
}

bool BfmeThingCDE::bfmeCheckABI()
{
	d_008f7990();

	if (m_ptr8 == 0)
		return false;

	unsigned int i = 0;
	int *value = &m_values[1];

	for (; i < 20; i += 5, value += 5)
	{
		if (m_status[i] && value[-1] == 3)
			break;
		if (m_status[i + 1] && value[0] == 3)
		{
			++i;
			break;
		}
		if (m_status[i + 2] && value[1] == 3)
		{
			i += 2;
			break;
		}
		if (m_status[i + 3] && value[2] == 3)
		{
			i += 3;
			break;
		}
		if (m_status[i + 4] && value[3] == 3)
		{
			i += 4;
			break;
		}
	}

	if (i == 20)
		return false;

	m_ptr4->f3(0);
	m_ptr4 = 0;
	((CDELeading *)m_ptr8)->f1();
	return true;
}

void BfmeThingCDE::bfmeDtorCDE()
{
	d_008f7990();
	if (m_ptr4 != 0)
		m_ptr4->f3(0);
	if (m_ptr8 != 0)
	{
		m_ptr8->f3(0);
		m_ptr8->f0();
		m_ptr8 = 0;
	}
	d_008f7ec0();
	if (m_array != 0)
	{
		void *cookie = (char *)m_array - 4;
		// Retail pushes 0x00A9E440 here; the donor's 0x00CF7BD0 is the BFME1
		// address of the same word. The bytes decide.
		ArrayDeleteHelperBodyThunk(m_array, 0x10, *(unsigned *)cookie,
			reinterpret_cast<void *>(0x00A9E440));
		::operator delete[](cookie);
	}
	if (m_prev != 0)
	{
		m_prev->m_00 = m_next;
		if (m_next != 0)
			m_next->m_14 = m_prev;
		m_prev = 0;
	}
	if (m_link1 != 0)
		m_link1->m_0c = m_link0;
	m_link0->m_00 = m_link1;
}

// ?d_008f7990@BfmeThingCDE@@QAEXXZ 133B at 0x00739F50.
// Native 739F50..739FD5 and the complete WorldBuilder undo counterpart
// establish one queued three-radius reveal and three signed circle changes.
void BfmeThingCDE::d_008f7990()
{
 if(m_revealRadii[0]>=0)
 {
  ((ShroudManagerImpl*)m_owner)->QueueUndoShroudReveal(m_cellX,m_cellY,m_revealRadii,m_rotation,m_revealMask);
  m_revealRadii[0]=-1;
 }
 for(unsigned i=0;i<3;++i)
 {
  int *radius=&m_changeRadii[i];
  if(*radius>=0 && (unsigned)m_changeAmounts[i]>0)
  {
   ((Gen_008F7CD0*)m_owner)->rva0073CE90(m_cellX,m_cellY,*radius,i,-m_changeAmounts[i],m_changeMasks[i]);
   *radius=-1;
  }
 }
}

// BFME1 575ba2b PartitionManager.cpp:1821..1876 supplies rectangle sampling.
// Full WB17DF950 names DoRectFill; native73A4A0..73A645 proves half-cell
// increments, ceil conversions, per-call generation deduplication and COI links.
// The established neutral BfmeThingCDE owner view is retained.
bool BfmeThingCDE::DoRectFill(float x,float y,float halfX,float halfY,float angle)
{
 float c=Cos(angle);
 float s=Sin(angle);
 float xdx=c*((ShroudManagerImpl*)m_owner)->cellSize*0.5f;
 float xdy=s*((ShroudManagerImpl*)m_owner)->cellSize*0.5f;
 float ydx=s*((ShroudManagerImpl*)m_owner)->cellSize*0.5f;
 float ydy=-c*((ShroudManagerImpl*)m_owner)->cellSize*0.5f;
 float scaleX=((ShroudManagerImpl*)m_owner)->scale;
 int stepsX=rectInteger((float)ceil((double)(scaleX*halfX*4.0f)));
 float scaleY=((ShroudManagerImpl*)m_owner)->scale;
 int stepsY=rectInteger((float)ceil((double)(scaleY*halfY*4.0f)));
 RectCOI *out=(RectCOI*)m_array;
 ++ShroudCoverageVisitGeneration;
 float leftX=x-halfX*c-halfY*s;
 float leftY=y+halfY*c-halfX*s;
 for(int iy=0;iy<stepsY;++iy,leftX+=ydx,leftY+=ydy)
 {
  float sampleX=leftX,sampleY=leftY;
  for(int ix=0;ix<stepsX;++ix,sampleX+=xdx,sampleY+=xdy)
  {
   ShroudManagerImpl008FBA40ElementLayout *cell=((ShroudManagerImpl*)m_owner)->elementAtByCoord_Rva0073A1D0(sampleX,sampleY);
   if(cell && ShroudCoverageVisitGeneration!=cell->generation)
   {
    cell->generation=ShroudCoverageVisitGeneration;
    out->cell=cell;
    RectCOI *next=cell->first;
    out->next=next;
    if(next)next->previous=&out->next;
    out->previous=(RectCOI**)cell;
    cell->first=out;
    ++out;
   }
  }
 }
 return true;
}
