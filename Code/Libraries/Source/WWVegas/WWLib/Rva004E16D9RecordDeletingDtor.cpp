// ??_GRva004E16D9Record@@UAEPAXI@Z
// partial score=0.95 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/LivingWorld
// ??_GRva004E16D9Record@@UAEPAXI@Z @0x004E1BE0 (28B).
// Scalar deleting dtor slot 0 of vtable 0x00861A70; calls rowed
// ??1Rva004E16D9Record@@QAE@XZ at 0x004E1682 plus delete at 0x0002FD60.
// Evidence: vtable slot plus ??1 row plus retail call bytes; BFME1 donor none;
// pattern follows FamilyDeletingDtors_0021C7e.cpp siblings.

// stlport
#include "ascii_string.h"

struct Rva004E16D9Pair {
	float x;
	float y;
	Rva004E16D9Pair() : x(0.0f), y(0.0f) {}
};

struct EmitVtableTag;

class Rva004E16D9Record {
public:
	Rva004E16D9Record();
	Rva004E16D9Record(EmitVtableTag *);
	virtual ~Rva004E16D9Record();
private:
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	Rva004E16D9Pair m_10;
	AsciiString m_18;
	unsigned char m_1C;
	unsigned char m_1D;
	char m_pad1E[2];
	Rva004E16D9Pair m_20;
};
// ?<Rva004E16D9Record::Rva004E16D9Record> absent-from-retail
Rva004E16D9Record::Rva004E16D9Record(EmitVtableTag *) {}
