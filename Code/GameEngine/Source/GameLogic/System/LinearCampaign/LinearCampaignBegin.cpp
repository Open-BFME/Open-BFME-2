// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "ascii_string.h"
#include <vector>
// LinearCampaign::beginCampaign: WB AF7DE0 names the function and retail
// 1ECDB3..1ECE98 is its complete229B RET0 body. The original campaign input
// unit-name array is at+0C; the runtime 0xC4 state stores its record pointer
// at+4 and carryover vector at+A4. CarryoverUnit strideAC/name+4/count+90
// agrees with the owned resize1ECCF3 and GetThingTemplate37DC52 providers.
// Template KindOf bit5A is byte+113 bit2. WB proves the record name local,
// indexed writes and intro movie at record+8; native Display vslot is+10C.
// The typed STLport carryover vector exposes the actual operator[] helper:
// it reproduces native EDI vector/EBX offset allocation without volatile.
// Every direct call retains the current ledger owner's spelling. No EH map.
class Rva0037DCA5
{
public:
	void *GetThingTemplate();	// 0x0037DC52, WB CarryoverUnit::GetThingTemplate
};

struct CarryoverUnitRecord
{
	void *m_vtable;
	AsciiString m_name;		// +0x04
	unsigned char m_pad08[0x90 - 0x08];
	int m_90;
	unsigned char m_pad94[0xAC - 0x94];
};

class Rva001EC9BDVector: public _STL::vector<CarryoverUnitRecord> {public:void resize(unsigned);};

struct BfmeAssignRecord172;

// The history vector calls the verified reserve implementation at 0x001EBE2D.
// Its record stays opaque here; the provider owns its copy and lifetime logic.
namespace _STL {
template <> void vector<BfmeAssignRecord172, allocator<BfmeAssignRecord172> >::reserve(unsigned int);
}

struct CarryoverThingTemplateView
{
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[0x14];	// +0x108
};

struct CarryoverNameVectorView
{
	int size() const { return m_finish - m_start; }
	void **m_start;
	void **m_finish;
	void **m_endOfStorage;
};

class Rva001EAFFE
{
public:
	AsciiString &rva001EAFFE(int index);	// 0x001EAFFE

	unsigned char m_pad00[0x08];
	AsciiString m_movie;			// +0x08
	CarryoverNameVectorView m_units;	// +0x0C
};

class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66();
	virtual void slot67(AsciiString movieName, int a, int b);	// +0x10C
};

extern Display *TheDisplay;

class Rva001EB456
{
public:
	void rva001EB456(int,int);
};
class LinearCampaign
{
public:
	void beginCampaign();

private:
	void *m_vtable;
	Rva001EAFFE *m_campaign;			// +0x04
	unsigned char m_pad08[0x0C - 0x08];
	int m_0c;
	unsigned char m_pad10[0xA4 - 0x10];
	Rva001EC9BDVector units;			// +0xA4
	int m_numFlaggedCarryovers;			// +0xB0
	_STL::vector<BfmeAssignRecord172> used;	// +0xB4
	unsigned char m_padC0[0xC3 - 0xC0];
	bool advanced;					// +0xC3
};

void LinearCampaign::beginCampaign()
{
	int count = m_campaign->m_units.size();
	// The TU's other views type +A4 by its element; this body reaches it as
	// the vector the 0x001ECCF3 resize forwarder takes.
	Rva001EC9BDVector &carryovers = reinterpret_cast<Rva001EC9BDVector &>(units);
	carryovers.resize(count);
	m_numFlaggedCarryovers = 0;
	for (int i = 0; i < count; ++i)
	{
		const AsciiString &name = m_campaign->rva001EAFFE(i);
		carryovers[i].m_name = name;
		carryovers[i].m_90 = 1;
		const CarryoverThingTemplateView *thing = static_cast<const CarryoverThingTemplateView *>(
			reinterpret_cast<Rva0037DCA5 *>(&carryovers[i])->GetThingTemplate());
		if (thing && (thing->m_kindOf[0x5A >> 3] & (1 << (0x5A & 7))))
			++m_numFlaggedCarryovers;
	}
	used.reserve(count);
	const AsciiString &movie = m_campaign->m_movie;
	if (!reinterpret_cast<const StringBase<char> *>(&movie)->isEmpty())
		TheDisplay->slot67(movie, 1, 0);
	m_0c = 0;
	advanced = false;
	((Rva001EB456*)this)->rva001EB456(1, 1);
}
