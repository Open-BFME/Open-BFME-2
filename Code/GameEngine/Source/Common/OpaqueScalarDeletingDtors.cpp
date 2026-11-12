// cl: /MD /EHsc /Ireference/shims/bfme2_ascii -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
struct EmitVtableTag;

// InGameCommandButtonMovieClip::Impl (WorldBuilder name of its destructor
// 0x005C7954), whose holder clear 0x005C7CA1 deletes it below.
#include "../../Include/GameClient/InGameCommandButtonMovieClip.h"

//
// Emitted scalar deleting destructors (28B flag-test shape) for unclaimed
// destructors found by sweeping the image for the
// push-esi/mov-esi,ecx/call/test-[esp+8],1 pattern. Each dtor is pinned
// opaquely (evidence: the ??_G call site plus the body bytes at the pinned
// address); the dtor bodies themselves stay unclaimed. Each class only
// declares its destructor, so the ??_G calls out through the pin, and an
// absent-from-retail tag constructor makes this TU emit the vtable (an
// in-class placeholder destructor would emit a ??1 copy the census proves
// wrong against the rowed body). Operator delete resolves via the pinned ??3.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

#include "../../Include/Common/MiBase1.h"

class Rva0072892
{
public:
	Rva0072892(EmitVtableTag *);
	virtual ~Rva0072892();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva0072892::Rva0072892> absent-from-retail
Rva0072892::Rva0072892(EmitVtableTag *)
{
}

class Rva005333F
{
public:
	Rva005333F(EmitVtableTag *);
	virtual ~Rva005333F();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva005333F::Rva005333F> absent-from-retail
Rva005333F::Rva005333F(EmitVtableTag *)
{
}

class W3DQuadrupedDrawModuleData
{
public:
	explicit W3DQuadrupedDrawModuleData(int)
	{
	}

	virtual ~W3DQuadrupedDrawModuleData();	// row 0x00065288 in Rva00065288Destructor.cpp
};

// Anchor: the inline constructor stores the vftable, so this TU emits the
// scalar deleting destructor; the destructor is only declared here.
W3DQuadrupedDrawModuleData *Rva0065288_Anchor(int)
{
	return new W3DQuadrupedDrawModuleData(0);
}

// ??_GRva00751EF@@UAEPAXI@Z is emitted (retail-identical) and rowed in Rva00751EFDtor.cpp.

class Rva0089851
{
public:
	Rva0089851(EmitVtableTag *);
	virtual ~Rva0089851();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva0089851::Rva0089851> absent-from-retail
Rva0089851::Rva0089851(EmitVtableTag *)
{
}

class Rva0090771
{
public:
	Rva0090771(EmitVtableTag *);
	virtual ~Rva0090771();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva0090771::Rva0090771> absent-from-retail
Rva0090771::Rva0090771(EmitVtableTag *)
{
}

class Rva0090840
{
public:
	Rva0090840(EmitVtableTag *);
	virtual ~Rva0090840();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva0090840::Rva0090840> absent-from-retail
Rva0090840::Rva0090840(EmitVtableTag *)
{
}

class Rva009D6FA
{
public:
	Rva009D6FA(EmitVtableTag *);
	virtual ~Rva009D6FA();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva009D6FA::Rva009D6FA> absent-from-retail
Rva009D6FA::Rva009D6FA(EmitVtableTag *)
{
}

#include "../../Include/Common/Rva00785FD0Renderer.h"

// Anchor: deleting one emits the scalar deleting destructor ??_GRva00785FD0Renderer (it
// calls out to the destructor row); the destructor is only declared here.
void Rva0011018B_Anchor(Rva00785FD0Renderer *object)
{
	delete object;
}

class Rva00119D00
{
public:
	Rva00119D00(EmitVtableTag *);
	virtual ~Rva00119D00();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva00119D00::Rva00119D00> absent-from-retail
Rva00119D00::Rva00119D00(EmitVtableTag *)
{
}

#include "../../Include/GameClient/SubTitleWindow.h"

// Anchor: deleting one emits the scalar deleting destructor ??_GSubTitleWindow (it
// calls out to the destructor row); the destructor is only declared here.
void Rva00260A3C_Anchor(SubTitleWindow *object)
{
	delete object;
}

#include "../../../GameEngineDevice/Include/MilesAudioDevice/AudioFileCache.h"

// Anchor: deleting one emits the scalar deleting destructor ??_GAudioFileCache (it
// calls out to the destructor row); the destructor is only declared here.
void Rva00A7CF3_Anchor(AudioFileCache *object)
{
	delete object;
}

class Rva001ED70C
{
public:
	~Rva001ED70C();	// row 0x001ED840 in AudioSecondarySettingsDestructor.cpp
};

// Anchor: deleting one emits the scalar deleting destructor ??_GRva001ED70C (it
// calls out to the destructor row); the destructor is only declared here.
void Rva001ED840_Anchor(Rva001ED70C *object)
{
	delete object;
}

class W3DRoadBuffer
{
public:
	~W3DRoadBuffer();	// row 0x000DC51D in W3DRoadBuffer.cpp
};

// Anchor: deleting one emits the scalar deleting destructor ??_GW3DRoadBuffer (it
// calls out to the destructor row); the destructor is only declared here.
void Rva000DC51D_Anchor(W3DRoadBuffer *object)
{
	delete object;
}

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBufferClass.h"

// Anchor: deleting one emits the scalar deleting destructor ??_GW3DBridgeBuffer (it
// calls out to the destructor row); the destructor is only declared here.
void Rva000DE4EB_Anchor(W3DBridgeBuffer *object)
{
	delete object;
}

class W3DWaypointBuffer
{
public:
	~W3DWaypointBuffer();	// row 0x000DFDD9 in W3DWaypointBufferDestructor.cpp
};

// Anchor: deleting one emits the scalar deleting destructor ??_GW3DWaypointBuffer (it
// calls out to the destructor row); the destructor is only declared here.
void Rva000DFDD9_Anchor(W3DWaypointBuffer *object)
{
	delete object;
}

class Rva000E0AE2
{
public:
	~Rva000E0AE2();	// row 0x000E03E2 in Rva000E0AE2Constructor.cpp
};

// Anchor: deleting one emits the scalar deleting destructor ??_GRva000E0AE2 (it
// calls out to the destructor row); the destructor is only declared here.
void Rva000E03E2_Anchor(Rva000E0AE2 *object)
{
	delete object;
}

class W3DTaint
{
public:
	~W3DTaint();	// row 0x00073BFE in W3DTaintDtor.cpp
};

// Anchor: deleting one emits the scalar deleting destructor ??_GW3DTaint (it
// calls out to the destructor row); the destructor is only declared here.
void Rva00073BFE_Anchor(W3DTaint *object)
{
	delete object;
}

class Rva0072AED
{
public:
	explicit Rva0072AED(int)
	{
	}

	virtual ~Rva0072AED();	// row 0x00072AED in Rva00072AEDDtor.cpp
};

// Anchor: the inline constructor stores the vftable, so this TU emits the
// scalar deleting destructor; the destructor is only declared here.
Rva0072AED *Rva0072AED_Anchor(int)
{
	return new Rva0072AED(0);
}

class Rva0078B83
{
public:
	Rva0078B83(EmitVtableTag *);
	virtual ~Rva0078B83();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva0078B83::Rva0078B83> absent-from-retail
Rva0078B83::Rva0078B83(EmitVtableTag *)
{
}

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/WaterTracksRenderSystem.h"

// Anchor: deleting one emits the scalar deleting destructor ??_GWaterTracksRenderSystem (it
// calls out to the destructor row); the destructor is only declared here.
void Rva00FF4D6_Anchor(WaterTracksRenderSystem *object)
{
	delete object;
}

// ??_GRva0081FDD@@UAEPAXI@Z is emitted (retail-identical) and rowed in Rva00082EF5Ctor.cpp.

// ??_GRva008291D@@UAEPAXI@Z is emitted (retail-identical) and rowed in Rva00082EF5Ctor.cpp.

class Rva009A500
{
public:
	Rva009A500(EmitVtableTag *);
	virtual ~Rva009A500();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva009A500::Rva009A500> absent-from-retail
Rva009A500::Rva009A500(EmitVtableTag *)
{
}

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadowManager.h"

// Anchor: deleting one emits the scalar deleting destructor ??_GW3DVolumetricShadowManager (it
// calls out to the destructor row); the destructor is only declared here.
void Rva00F2ECB_Anchor(W3DVolumetricShadowManager *object)
{
	delete object;
}

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva0007BAD6.h"

// Anchor: deleting one emits the scalar deleting destructor ??_GRva0007BAD6 (it
// calls out to the destructor row); the destructor is only declared here.
void Rva007C0F5_Anchor(Rva0007BAD6 *object)
{
	delete object;
}

// Native A7797..A77B3 calls the complete resource cleanup at 10EDC2,
// conditionally frees storage for flag bit zero, and returns the same pointer.
// Share the recovered nonvirtual layout rather than the old three-vptr stand-in.
#include "../../Include/Common/Rva0010EDC2Resource.h"
void *Rva0010EDC2::destroy(unsigned int flags)
{
    this->~Rva0010EDC2();
    if (flags & 1)
        ::operator delete(this);
    return this;
}

class Rva005C7CA1
{
public:
	void clear();

private:
	InGameCommandButtonMovieClip::Impl *m_elem;
	int m_pad04;
};

// Ctor 0x005C802B installs the same vtable 0x00C74ACC as this dtor, so the
// dtor and its deleting wrapper carry the ctor's class name.
class Rva005C802B
{
public:
	virtual ~Rva005C802B();

private:
	Rva005C7CA1 m_member04;
};

Rva005C802B::~Rva005C802B()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005C802B_Anchor(Rva005C802B *object)
{
	object->Rva005C802B::~Rva005C802B();
}

class Rva005CD14D
{
public:
	void clear();

private:
	class Rva005CD0FEElem *m_elem;
	int m_pad04;
};

class Rva005CD1A9
{
public:
	virtual ~Rva005CD1A9();
	virtual void bfmePureSlot1() = 0; // retail table slot 1 is __purecall

private:
	Rva005CD14D m_member04;
};

Rva005CD1A9::~Rva005CD1A9()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005CD1A9_Anchor(Rva005CD1A9 *object)
{
	object->Rva005CD1A9::~Rva005CD1A9();
}

class Rva005F35D3
{
public:
	void clear();

private:
	class Rva005F2F80Elem *m_elem;
	int m_pad04;
};

class Rva005FC1CA
{
public:
	void clear();

private:
	class Rva005FBF97Elem *m_elem;
	int m_pad04;
};

class Rva0060006A
{
public:
	void clear();

private:
	class Rva005FFBCBElem *m_elem;
	int m_pad04;
};

// StrategicHUD::BattlePromptPlayerPageMovieClip: its ctor (0x00600305) stores
// table 0x00C7A5CC, whose slot 0 is this deleting dtor 0x00600092 and slots
// 1..3 the shared empty RET 4 (0x0047A69C).
namespace StrategicHUD {
class BattlePromptPlayerPageMovieClip
{
public:
	virtual ~BattlePromptPlayerPageMovieClip();
	virtual void notifySwapButtonClicked(int index);
	virtual void notifySwapButtonRollOver(int index);
	virtual void notifySwapButtonRollOut(int index);

private:
	Rva0060006A m_member04;
};
}
using StrategicHUD::BattlePromptPlayerPageMovieClip;

BattlePromptPlayerPageMovieClip::~BattlePromptPlayerPageMovieClip()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00600084_Anchor(BattlePromptPlayerPageMovieClip *object)
{
	object->BattlePromptPlayerPageMovieClip::~BattlePromptPlayerPageMovieClip();
}

class Rva0057C39C
{
public:
	void clear();

private:
	class Rva0057C2D4Elem *m_elem;
	int m_pad04;
};

// AptLoadMovieFrame (WorldBuilder's name): its one-slot vftable 0x0086F304
// holds the deleting destructor 0x0057C4E2, and the frame's constructor
// 0x0057C499 (AptLoadMovieFrame.cpp) installs it; the member at +4 owns Impl.
class AptLoadMovieFrame
{
public:
	class Impl;
	virtual ~AptLoadMovieFrame();

private:
	Rva0057C39C m_member04;
};

AptLoadMovieFrame::~AptLoadMovieFrame()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void AptLoadMovieFrame_Anchor(AptLoadMovieFrame *object)
{
	object->AptLoadMovieFrame::~AptLoadMovieFrame();
}

class Rva00589079
{
public:
	virtual ~Rva00589079();

private:
	char m_pad04[8];
};

class Rva00494A97_S1
{
public:
	virtual void f1();
};

class Rva00494A97_S2
{
public:
	virtual void f2() = 0;

private:
	char m_pad04[12];
};

class Rva00494A97_S3
{
public:
	virtual void f3() = 0;
};

class Rva00494A97_S4
{
public:
	virtual void f4() = 0;
};

class Rva00494A97 : public Rva00589079, public Rva00494A97_S1, public Rva00494A97_S2, public Rva00494A97_S3, public Rva00494A97_S4
{
public:
	virtual ~Rva00494A97()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00494A97_Anchor(Rva00494A97 *object)
{
	object->Rva00494A97::~Rva00494A97();
}

class Rva005C3EE8
{
public:
	void clear();

private:
	class Rva005C3A37Elem *m_elem;
	int m_pad04;
};

class Rva005C3F02
{
public:
	virtual ~Rva005C3F02();

private:
	Rva005C3EE8 m_member04;
};

Rva005C3F02::~Rva005C3F02()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005C3F02_Anchor(Rva005C3F02 *object)
{
	object->Rva005C3F02::~Rva005C3F02();
}

class Rva005CB892
{
public:
	void clear();

private:
	class Rva005CB4E6Elem *m_elem;
	int m_pad04;
};

class Rva005CB8D4
{
public:
	virtual ~Rva005CB8D4();
	// Retail table 0x00C74DA8 has two __purecall entries after the destructor.
	virtual void slot1() = 0;
	virtual void slot2() = 0;

private:
	Rva005CB892 m_member04;
};

Rva005CB8D4::~Rva005CB8D4()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005CB8D4_Anchor(Rva005CB8D4 *object)
{
	object->Rva005CB8D4::~Rva005CB8D4();
}

class Rva003B3204
{
public:
	void clear();

private:
	char m_pad[8];
};

class Rva003B31DF
{
public:
	void clear();

private:
	char m_pad[8];
};

class Rva003B4071
{
public:
	void clear();

private:
	Rva003B31DF *m_first;
	Rva003B3204 *m_second;
};

void Rva003B4071::clear()
{
	Rva003B3204 *second = m_second;
	if (second != 0) {
		second->clear();
		operator delete(second);
	}
	Rva003B31DF *first = m_first;
	if (first != 0) {
		first->clear();
		operator delete(first);
	}
}

class Rva003B4100
{
public:
	virtual ~Rva003B4100();

private:
	Rva003B4071 m_member04;
};

Rva003B4100::~Rva003B4100()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva003B4100_Anchor(Rva003B4100 *object)
{
	object->Rva003B4100::~Rva003B4100();
}

class Rva00787C20
{
public:
	~Rva00787C20();	// row 0x000AAE59 in Rva00787C20HashOwnerDestructor.cpp
};

// Anchor: deleting one emits the scalar deleting destructor ??_GRva00787C20 (it
// calls out to the destructor row); the destructor is only declared here.
void Rva00AAE59_Anchor(Rva00787C20 *object)
{
	delete object;
}

class Rva00AB15D
{
public:
	explicit Rva00AB15D(int)
	{
	}

	virtual ~Rva00AB15D();	// row 0x000AB15D in Rva000AAD26FamilyDtors.cpp
};

// Anchor: the inline constructor stores the vftable, so this TU emits the
// scalar deleting destructor; the destructor is only declared here.
Rva00AB15D *Rva00AB15D_Anchor(int)
{
	return new Rva00AB15D(0);
}

class Rva00B6CF1
{
public:
	Rva00B6CF1(EmitVtableTag *);
	virtual ~Rva00B6CF1();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva00B6CF1::Rva00B6CF1> absent-from-retail
Rva00B6CF1::Rva00B6CF1(EmitVtableTag *)
{
}

class Rva0073EE55
{
public:
	explicit Rva0073EE55(int)
	{
	}

	virtual ~Rva0073EE55();	// row 0x0073EE55 in Rva0073EE55Dtor.cpp
};

// Anchor: the inline constructor stores the vftable, so this TU emits the
// scalar deleting destructor; the destructor is only declared here.
Rva0073EE55 *Rva0073EE55_Anchor(int)
{
	return new Rva0073EE55(0);
}

class Rva00AAD26
{
public:
	explicit Rva00AAD26(int)
	{
	}

	virtual ~Rva00AAD26();	// row 0x000AAD26 in Rva000AAD26FamilyDtors.cpp
};

// Anchor: the inline constructor stores the vftable, so this TU emits the
// scalar deleting destructor; the destructor is only declared here.
Rva00AAD26 *Rva00AAD26_Anchor(int)
{
	return new Rva00AAD26(0);
}

// ??_GWorldHeightMap@@UAEPAXI@Z is emitted (retail-identical) and rowed in Rva00B0028Dtor.cpp.

class EventParameter
{
public:
	explicit EventParameter(int)
	{
	}

	virtual ~EventParameter();	// row 0x000B6971 in Rva000AAD26FamilyDtors.cpp
};

// Anchor: the inline constructor stores the vftable, so this TU emits the
// scalar deleting destructor; the destructor is only declared here.
EventParameter *EventParameter_Anchor(int)
{
	return new EventParameter(0);
}

class Rva00A86CE
{
public:
	explicit Rva00A86CE(int)
	{
	}

	virtual ~Rva00A86CE();	// row 0x000A86CE in Rva000A86CEDtor.cpp
};

// Anchor: the inline constructor stores the vftable, so this TU emits the
// scalar deleting destructor; the destructor is only declared here.
Rva00A86CE *Rva00A86CE_Anchor(int)
{
	return new Rva00A86CE(0);
}

class Rva00A897D
{
public:
	Rva00A897D(EmitVtableTag *);
	virtual ~Rva00A897D();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva00A897D::Rva00A897D> absent-from-retail
Rva00A897D::Rva00A897D(EmitVtableTag *)
{
}

class Rva0084CEF
{
public:
	Rva0084CEF(EmitVtableTag *);
	virtual ~Rva0084CEF();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable
// and with it the scalar deleting destructor; the destructor is only declared here.
// ?<Rva0084CEF::Rva0084CEF> absent-from-retail
Rva0084CEF::Rva0084CEF(EmitVtableTag *)
{
}

class ObjectModule_B2
{
public:
	virtual void f2() = 0;
};

// Owner proven (unlike the opaque entries above): this deleting dtor sits
// in slot 0 of the ObjectModule vtable (0xC07E1C, shared with the
// DrawableModule twin) and calls the 0x49B47C fold point through the shared
// base pin, matching retail 0x4A10FD.
class ObjectModule : public Rva0049B47C, public MiBase1, public ObjectModule_B2
{
public:
	ObjectModule(EmitVtableTag *);
	virtual ~ObjectModule();
};

// The tag constructor (no retail counterpart) makes this TU emit the vtable and with it
// the scalar deleting destructor; the destructor is only declared here (an in-class
// placeholder would emit a ??1 copy the census proves wrong against the rowed 0x49B47C).
// ?<ObjectModule::ObjectModule> absent-from-retail
ObjectModule::ObjectModule(EmitVtableTag *)
{
}

// Guarded-delete clear() batch: each owner below holds a heap element at
// +0. The retail body loads the element, nulls the slot, and on non-null
// runs the element destructor followed by the shared scalar operator
// delete (0x0002FD60). The null store compiles to AND under /O1.
class Rva0057C2D4Elem
{
public:
	~Rva0057C2D4Elem();
};

void Rva0057C39C::clear()
{
	Rva0057C2D4Elem *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

#include "../../Include/Common/Rva005C3A37Elem.h"

void Rva005C3EE8::clear()
{
	Rva005C3A37Elem *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

class InGameCommandButtonMovieClip::Impl
{
public:
	~Impl();
};

void Rva005C7CA1::clear()
{
	InGameCommandButtonMovieClip::Impl *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

class Rva005CB4E6Elem
{
public:
	~Rva005CB4E6Elem();
};

void Rva005CB892::clear()
{
	Rva005CB4E6Elem *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

class Rva005CD0FEElem
{
public:
	~Rva005CD0FEElem();
};

void Rva005CD14D::clear()
{
	Rva005CD0FEElem *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

class Rva005F2F80Elem
{
public:
	~Rva005F2F80Elem();
};

void Rva005F35D3::clear()
{
	Rva005F2F80Elem *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

class Rva005FBF97Elem
{
public:
	~Rva005FBF97Elem();
};

void Rva005FC1CA::clear()
{
	Rva005FBF97Elem *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

class Rva005FFBCB { public: ~Rva005FFBCB(); };
class Rva005FFBCBElem
{
public:
	// Destruction is the rowed ??1Rva005FFBCB, reached by a qualified call.
	__declspec(dllimport) __forceinline ~Rva005FFBCBElem() { ((Rva005FFBCB *)this)->Rva005FFBCB::~Rva005FFBCB(); }
};

void Rva0060006A::clear()
{
	Rva005FFBCBElem *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva00494A97_S1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
// ?LoadContent@Impl@AptLoadMovieFrame@@QAEXABVAsciiString@@ABUTreeHintRef00217D4C@@@Z @ 0x0057C339 91B gap via rowed AptCall TreeHintRef copy.
// Apt LoadContent loader with TreeHintRef member +0x14 flag +0x18 level +0x0 team +0x4.
// Evidence: TreeHintRef copy 0x002174A4, Version? no, AptCall 0x0050E9FE, LoadContent literal,
// empty g_Rva0107301CEmptyString, manager TheRva00222A8BTarget, caller jmp 0x0057C397.
class AsciiString;
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);
class AptLoadMovieFrame::Impl
{
public:
    void LoadContent(const AsciiString &a1, const TreeHintRef00217D4C &a2);
private:
    void *m_level;
    char *m_teamData;
    char m_pad08[0x14 - 8];
    TreeHintRef00217D4C m_hint;
    unsigned char m_flag;
};
void AptLoadMovieFrame::Impl::LoadContent(const AsciiString &asciiString, const TreeHintRef00217D4C &a2)
{
    m_hint = a2;
    const char *team1;
    const char *a1data = *(char *const *)&asciiString;
    if (a1data)
        team1 = a1data + 8;
    else
        team1 = "";
    const char *team2;
    if (m_teamData)
        team2 = m_teamData + 8;
    else
        team2 = "";
    Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, team2, "LoadContent", &team1);
    m_flag = 1;
}
// ?rva0057C394@Rva0057C394@@QAEXABVAsciiString@@ABUTreeHintRef00217D4C@@@Z @ 0x0057C394 8B gap forwarder.
// Tail jmp to rowed loader 0x0057C339 via member pointer at +4.
// Evidence: mov ecx,[ecx+4] jmp, same args ret 8 passthrough, unblocks 4.
class Rva0057C394
{
public:
    void rva0057C394(const AsciiString &a1, const TreeHintRef00217D4C &a2);
private:
    char m_pad00[4];
    AptLoadMovieFrame::Impl *m_p;
};
void Rva0057C394::rva0057C394(const AsciiString &asciiString, const TreeHintRef00217D4C &a2)
{
    return m_p->LoadContent(asciiString, a2);
}
// ??1Rva005F329E@@QAE@XZ, retail 0x005F329E, 23 bytes.
// Opaque scalar dtor deleting owned Rva005F2B22 member via pinned dtor and
// rowed operator delete. Evidence: callees pinned 0x005F2B22 rowed 0x0002FD60;
// callers at 0x005F35C1 0x007A5049; prev/next in this TU (/O1 /MD).
class Rva005F2B22
{
public:
    ~Rva005F2B22();
};
class Rva005F329E
{
public:
    ~Rva005F329E();
private:
    Rva005F2B22 *m_elem;
};
Rva005F329E::~Rva005F329E()
{
    delete m_elem;
}
#pragma comment(linker, "/alternatename:??1ObjectModule@@UAE@XZ=??1Snapshot@@UAE@XZ")

// Names the emitted vtables and deleting destructors above reference that no unit defines
// under this spelling. Each is bound to the row owning the retail address: the nine opaque
// destructors by the REL32 in their ??_G (read from retail), the Rva00494A97 secondary-base
// slots by slot 0 of its retail vftables (0x00C4E988, 0x00C4E964, 0x00C4E900). ObjectModule
// has a single vptr in retail, so ObjectModule_B2 is a stand-in base: its placeholder is
// bound to slot 1 of the ObjectModule vftable (0x00C07E1C), the empty virtual, and claims
// nothing about a retail secondary vftable.
#pragma comment(linker, "/alternatename:??1Rva00119D00@@UAE@XZ=??1Render2DClass@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva005333F@@UAE@XZ=?rva0005333F@Rva0005333FHolder@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva0072892@@UAE@XZ=??1RefCountClass@@MAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0084CEF@@UAE@XZ=??1Rva00084CEF@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0089851@@UAE@XZ=??1RunwayInfo@FlightDeckBehavior@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0090771@@UAE@XZ=??1Rva000906DE@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0090840@@UAE@XZ=??1Rva007E3C20Vp6Stream@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva009D6FA@@UAE@XZ=??1Rva0009D55BProduct@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva00B6CF1@@UAE@XZ=??1BfmeStringRecord000B94D2@@QAE@XZ")
