// cl: /O1 /DNDEBUG /MD
//
// ??0AttachedModelFXNugget@@QAE@XZ 46B @0x1E084A: no-arg ctor called by
// AttachedModelFXNugget::parse (0x001E168D) for the AttachedModel FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDD118 (Modelname@0x148, RandomlyRotate@0x14C,
// ExpireTimer@0x150); parse TU notes news 0x154 and builder 0x001DFBE8.
// Base 0x001DFEAA is a shared FXNugget-family base ctor (16 ctor-start
// callers with this undisplaced); pinned opaquely, do not name.

#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
private:
	unsigned char m_pad[0x148];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AttachedModelFXNugget : public Rva001DFEAABase
{
public:
	AttachedModelFXNugget();
private:
	const char *m_modelName; // +0x148
	bool m_randomlyRotate; // +0x14C
	int m_expireTimer; // +0x150, default LogicFramesPerSecond * 8
};

// ??0AttachedModelFXNugget@@QAE@XZ
AttachedModelFXNugget::AttachedModelFXNugget()
{
	*(unsigned int *)this = 0x00BDD814;
	_ReadWriteBarrier();
	m_modelName = 0;
	m_randomlyRotate = false;
	m_expireTimer = LogicFramesPerSecond * 8;
}
