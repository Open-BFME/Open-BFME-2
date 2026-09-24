// cl: /O1 /DNDEBUG /MD
//
// ??0EvaEventFXNugget@@QAE@XZ 46B @0x1DFFFA: no-arg ctor called by
// EvaEventFXNugget::parse (0x001E12AD) for the EvaEvent FXList keyword;
// class name from BFME1. Member names and offsets from the retail FieldParse
// table 0x00BDCAD8 (EvaEventOwner@0x148 EvaEventAlly@0x14C EvaEventEnemy@0x150)
// and the BFME1 donor (FXNugget::m_field04 type id; BFME2 type is 15).
// Base 0x001DFEAA is a shared FXNugget-family base ctor; pinned opaquely.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
protected:
	unsigned int m_vtablePad; // +0, overwritten by the derived vtable store
	int m_field04; // +4, nugget type id (BFME1 FXNugget::m_field04)
	unsigned char m_pad[0x148 - 8];
};

class EvaEventFXNugget : public Rva001DFEAABase
{
public:
	EvaEventFXNugget();
private:
	int m_evaEventOwner; // +0x148
	int m_evaEventAlly; // +0x14C
	int m_evaEventEnemy; // +0x150
};

// ??0EvaEventFXNugget@@QAE@XZ
EvaEventFXNugget::EvaEventFXNugget()
{
	*(unsigned int *)this = 0x00BDD754;
	m_evaEventOwner |= -1;
	m_evaEventAlly |= -1;
	m_evaEventEnemy |= -1;
	m_field04 = 15;
}
