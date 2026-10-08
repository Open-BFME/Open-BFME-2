// cl: /MD /EHsc
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??1Rva00B6CF1@@QAE@XZ=??1Rva00B6CF1@@UAE@XZ")

//
// Emitted scalar deleting destructors (28B flag-test shape) for unclaimed
// destructors found by sweeping the image for the
// push-esi/mov-esi,ecx/call/test-[esp+8],1 pattern. Each dtor is pinned
// opaquely (evidence: the ??_G call site plus the body bytes at the pinned
// address); the dtor bodies themselves stay unclaimed. The emitting classes
// below use a three-vptr MI model so the in-class destructor is too big to
// inline and the ??_G calls out through the pin (a single-vptr dtor would
// inline into the ??_G instead). Operator delete resolves via the pinned ??3.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva0065D52_B2
{
public:
	virtual void f2();
};

class Rva0065D52 : public Rva0049B47C, public MiBase1, public Rva0065D52_B2
{
public:
	virtual ~Rva0065D52()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0065D52_Anchor(Rva0065D52 *p)
{
	p->Rva0065D52::~Rva0065D52();
}

class Rva0049FCB_B2
{
public:
	virtual void f2();
};

class Rva0049FCB : public Rva0049B47C, public MiBase1, public Rva0049FCB_B2
{
public:
	virtual ~Rva0049FCB()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0049FCB_Anchor(Rva0049FCB *p)
{
	p->Rva0049FCB::~Rva0049FCB();
}

class Rva009023C_B2
{
public:
	virtual void f2();
};

class Rva009023C : public Rva0049B47C, public MiBase1, public Rva009023C_B2
{
public:
	virtual ~Rva009023C()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva009023C_Anchor(Rva009023C *p)
{
	p->Rva009023C::~Rva009023C();
}

class Rva0050B2A_B2
{
public:
	virtual void f2();
};

class GeometryInfo : public Rva0049B47C, public MiBase1, public Rva0050B2A_B2
{
public:
	virtual ~GeometryInfo()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0050B2A_Anchor(GeometryInfo *p)
{
	p->GeometryInfo::~GeometryInfo();
}

class Rva0072892_B2
{
public:
	virtual void f2();
};

class Rva0072892 : public Rva0049B47C, public MiBase1, public Rva0072892_B2
{
public:
	virtual ~Rva0072892()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0072892_Anchor(Rva0072892 *p)
{
	p->Rva0072892::~Rva0072892();
}

class Rva005333F_B2
{
public:
	virtual void f2();
};

class Rva005333F : public Rva0049B47C, public MiBase1, public Rva005333F_B2
{
public:
	virtual ~Rva005333F()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005333F_Anchor(Rva005333F *p)
{
	p->Rva005333F::~Rva005333F();
}

class Rva0065288_B2
{
public:
	virtual void f2();
};

class Rva0065288 : public Rva0049B47C, public MiBase1, public Rva0065288_B2
{
public:
	virtual ~Rva0065288()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0065288_Anchor(Rva0065288 *p)
{
	p->Rva0065288::~Rva0065288();
}

class Rva007280A_B2
{
public:
	virtual void f2();
};

class BfmeOwnerCC : public Rva0049B47C, public MiBase1, public Rva007280A_B2
{
public:
	virtual ~BfmeOwnerCC()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva007280A_Anchor(BfmeOwnerCC *p)
{
	p->BfmeOwnerCC::~BfmeOwnerCC();
}

class Rva00751EF_B2
{
public:
	virtual void f2();
};

class Rva00751EF : public Rva0049B47C, public MiBase1, public Rva00751EF_B2
{
public:
	virtual ~Rva00751EF()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00751EF_Anchor(Rva00751EF *p)
{
	p->Rva00751EF::~Rva00751EF();
}

class Rva0078393_B2
{
public:
	virtual void f2();
};

class W3DFileSystem : public Rva0049B47C, public MiBase1, public Rva0078393_B2
{
public:
	virtual ~W3DFileSystem()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0078393_Anchor(W3DFileSystem *p)
{
	p->W3DFileSystem::~W3DFileSystem();
}

class Rva007BB16_B2
{
public:
	virtual void f2();
};

class Rva007BB16 : public Rva0049B47C, public MiBase1, public Rva007BB16_B2
{
public:
	virtual ~Rva007BB16()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva007BB16_Anchor(Rva007BB16 *p)
{
	p->Rva007BB16::~Rva007BB16();
}

class Rva007EC44_B2
{
public:
	virtual void f2();
};

class Rva007EC44 : public Rva0049B47C, public MiBase1, public Rva007EC44_B2
{
public:
	virtual ~Rva007EC44()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva007EC44_Anchor(Rva007EC44 *p)
{
	p->Rva007EC44::~Rva007EC44();
}

class Rva0084096_B2
{
public:
	virtual void f2();
};

class Rva0084096 : public Rva0049B47C, public MiBase1, public Rva0084096_B2
{
public:
	virtual ~Rva0084096()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0084096_Anchor(Rva0084096 *p)
{
	p->Rva0084096::~Rva0084096();
}

class Rva0089851_B2
{
public:
	virtual void f2();
};

class Rva0089851 : public Rva0049B47C, public MiBase1, public Rva0089851_B2
{
public:
	virtual ~Rva0089851()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0089851_Anchor(Rva0089851 *p)
{
	p->Rva0089851::~Rva0089851();
}

class Rva008B77D_B2
{
public:
	virtual void f2();
};

class Rva008B77D : public Rva0049B47C, public MiBase1, public Rva008B77D_B2
{
public:
	virtual ~Rva008B77D()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva008B77D_Anchor(Rva008B77D *p)
{
	p->Rva008B77D::~Rva008B77D();
}

class Rva009045E_B2
{
public:
	virtual void f2();
};

class Rva00090360 : public Rva0049B47C, public MiBase1, public Rva009045E_B2
{
public:
	virtual ~Rva00090360()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva009045E_Anchor(Rva00090360 *p)
{
	p->Rva00090360::~Rva00090360();
}

class Rva0090771_B2
{
public:
	virtual void f2();
};

class Rva0090771 : public Rva0049B47C, public MiBase1, public Rva0090771_B2
{
public:
	virtual ~Rva0090771()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0090771_Anchor(Rva0090771 *p)
{
	p->Rva0090771::~Rva0090771();
}

class Rva0090840_B2
{
public:
	virtual void f2();
};

class Rva0090840 : public Rva0049B47C, public MiBase1, public Rva0090840_B2
{
public:
	virtual ~Rva0090840()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0090840_Anchor(Rva0090840 *p)
{
	p->Rva0090840::~Rva0090840();
}

class Rva0094F38_B2
{
public:
	virtual void f2();
};

class BfmeB1137 : public Rva0049B47C, public MiBase1, public Rva0094F38_B2
{
public:
	virtual ~BfmeB1137()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0094F38_Anchor(BfmeB1137 *p)
{
	p->BfmeB1137::~BfmeB1137();
}

class Rva0095360_B2
{
public:
	virtual void f2();
};

class Gen006E2310 : public Rva0049B47C, public MiBase1, public Rva0095360_B2
{
public:
	virtual ~Gen006E2310()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0095360_Anchor(Gen006E2310 *p)
{
	p->Gen006E2310::~Gen006E2310();
}

class Rva0098477_B2
{
public:
	virtual void f2();
};

class Rva0098477 : public Rva0049B47C, public MiBase1, public Rva0098477_B2
{
public:
	virtual ~Rva0098477()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0098477_Anchor(Rva0098477 *p)
{
	p->Rva0098477::~Rva0098477();
}

class Rva00986E7_B2
{
public:
	virtual void f2();
};

class Rva00986E7 : public Rva0049B47C, public MiBase1, public Rva00986E7_B2
{
public:
	virtual ~Rva00986E7()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00986E7_Anchor(Rva00986E7 *p)
{
	p->Rva00986E7::~Rva00986E7();
}

class Rva0098D9E_B2
{
public:
	virtual void f2();
};

class MouseThreadClass : public Rva0049B47C, public MiBase1, public Rva0098D9E_B2
{
public:
	virtual ~MouseThreadClass()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0098D9E_Anchor(MouseThreadClass *p)
{
	p->MouseThreadClass::~MouseThreadClass();
}

class Rva0099927_B2
{
public:
	virtual void f2();
};

class Rva0099927 : public Rva0049B47C, public MiBase1, public Rva0099927_B2
{
public:
	virtual ~Rva0099927()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0099927_Anchor(Rva0099927 *p)
{
	p->Rva0099927::~Rva0099927();
}

class Rva009D6FA_B2
{
public:
	virtual void f2();
};

class Rva009D6FA : public Rva0049B47C, public MiBase1, public Rva009D6FA_B2
{
public:
	virtual ~Rva009D6FA()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva009D6FA_Anchor(Rva009D6FA *p)
{
	p->Rva009D6FA::~Rva009D6FA();
}

class Rva00A6454_B2
{
public:
	virtual void f2();
};

class W3DSmudgeManager : public Rva0049B47C, public MiBase1, public Rva00A6454_B2
{
public:
	virtual ~W3DSmudgeManager()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00A6454_Anchor(W3DSmudgeManager *p)
{
	p->W3DSmudgeManager::~W3DSmudgeManager();
}

// Native A8E0A..A8E79: audio deletion notification and three members.
// The notification callee is the byte-verified PlayingAudio cleanup in
// MilesAudioManager; keep the existing address-derived owner spelling.
struct PlayingAudio;
class AudioManager;
extern AudioManager *TheAudio;
class MilesAudioManager {public: void onPlayingAudioDeleted(PlayingAudio &);};
class OpaqueRefCounted {public: void Release_Ref();};
struct Rva00A8E0AEvent {char unknown00[0x88]; OpaqueRefCounted ref88;};
struct Rva00A8E0AEventHolder {
 Rva00A8E0AEvent *event;
 ~Rva00A8E0AEventHolder() {if (event) event->ref88.Release_Ref();}
};
class BfmeStringTailRecord156 {public: ~BfmeStringTailRecord156(); private: void *pointer;};
class Rva00690FF0Handle {public: ~Rva00690FF0Handle(); private: void *pointer;};
class Rva00051E4D {public: virtual ~Rva00051E4D() {}};
class Rva00A8E0A : public Rva00051E4D {
public: virtual ~Rva00A8E0A();
private:
 char unknown04[8];
 BfmeStringTailRecord156 member0C;
 char unknown10[12];
 Rva00A8E0AEventHolder event1C;
 Rva00690FF0Handle file20;
};
Rva00A8E0A::~Rva00A8E0A() {
 if (TheAudio)
  reinterpret_cast<MilesAudioManager *>(TheAudio)->onPlayingAudioDeleted(*reinterpret_cast<PlayingAudio *>(this));
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00A8E0A_Anchor(Rva00A8E0A *p)
{
	p->Rva00A8E0A::~Rva00A8E0A();
}

class Rva0011018B_B2
{
public:
	virtual void f2();
};

class Rva0011018B : public Rva0049B47C, public MiBase1, public Rva0011018B_B2
{
public:
	virtual ~Rva0011018B()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0011018B_Anchor(Rva0011018B *p)
{
	p->Rva0011018B::~Rva0011018B();
}

class Rva00A9CC7_B2
{
public:
	virtual void f2();
};

class Rva00A9CC7 : public Rva0049B47C, public MiBase1, public Rva00A9CC7_B2
{
public:
	virtual ~Rva00A9CC7()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00A9CC7_Anchor(Rva00A9CC7 *p)
{
	p->Rva00A9CC7::~Rva00A9CC7();
}

class Rva00111B25_B2
{
public:
	virtual void f2();
};

class Rva00111B25 : public Rva0049B47C, public MiBase1, public Rva00111B25_B2
{
public:
	virtual ~Rva00111B25()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00111B25_Anchor(Rva00111B25 *p)
{
	p->Rva00111B25::~Rva00111B25();
}

class Rva00419E3_B2
{
public:
	virtual void f2();
};

class Rva00419E3 : public Rva0049B47C, public MiBase1, public Rva00419E3_B2
{
public:
	virtual ~Rva00419E3()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00419E3_Anchor(Rva00419E3 *p)
{
	p->Rva00419E3::~Rva00419E3();
}

class Rva004CA13_B2
{
public:
	virtual void f2();
};

class Rva004CA13 : public Rva0049B47C, public MiBase1, public Rva004CA13_B2
{
public:
	virtual ~Rva004CA13()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva004CA13_Anchor(Rva004CA13 *p)
{
	p->Rva004CA13::~Rva004CA13();
}

class Rva00628FD_B2
{
public:
	virtual void f2();
};

class Rva00628FD : public Rva0049B47C, public MiBase1, public Rva00628FD_B2
{
public:
	virtual ~Rva00628FD()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00628FD_Anchor(Rva00628FD *p)
{
	p->Rva00628FD::~Rva00628FD();
}

class Rva008FCA3_B2
{
public:
	virtual void f2();
};

class Rva008FCA3 : public Rva0049B47C, public MiBase1, public Rva008FCA3_B2
{
public:
	virtual ~Rva008FCA3()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva008FCA3_Anchor(Rva008FCA3 *p)
{
	p->Rva008FCA3::~Rva008FCA3();
}

class Rva0090034_B2
{
public:
	virtual void f2();
};

class Rva0090034 : public Rva0049B47C, public MiBase1, public Rva0090034_B2
{
public:
	virtual ~Rva0090034()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0090034_Anchor(Rva0090034 *p)
{
	p->Rva0090034::~Rva0090034();
}

class Rva0090088_B2
{
public:
	virtual void f2();
};

class Rva0090088 : public Rva0049B47C, public MiBase1, public Rva0090088_B2
{
public:
	virtual ~Rva0090088()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0090088_Anchor(Rva0090088 *p)
{
	p->Rva0090088::~Rva0090088();
}

class Rva009111B_B2
{
public:
	virtual void f2();
};

class Rva009111B : public Rva0049B47C, public MiBase1, public Rva009111B_B2
{
public:
	virtual ~Rva009111B()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva009111B_Anchor(Rva009111B *p)
{
	p->Rva009111B::~Rva009111B();
}

class Rva00938C4_B2
{
public:
	virtual void f2();
};

class Rva00938C4 : public Rva0049B47C, public MiBase1, public Rva00938C4_B2
{
public:
	virtual ~Rva00938C4()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00938C4_Anchor(Rva00938C4 *p)
{
	p->Rva00938C4::~Rva00938C4();
}

class Rva009519B_B2
{
public:
	virtual void f2();
};

class Rva009519B : public Rva0049B47C, public MiBase1, public Rva009519B_B2
{
public:
	virtual ~Rva009519B()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva009519B_Anchor(Rva009519B *p)
{
	p->Rva009519B::~Rva009519B();
}

class Rva00985E4_B2
{
public:
	virtual void f2();
};

class Rva00985E4 : public Rva0049B47C, public MiBase1, public Rva00985E4_B2
{
public:
	virtual ~Rva00985E4()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00985E4_Anchor(Rva00985E4 *p)
{
	p->Rva00985E4::~Rva00985E4();
}

class Rva002C0C0_B2
{
public:
	virtual void f2();
};

class Rva002C0C0 : public Rva0049B47C, public MiBase1, public Rva002C0C0_B2
{
public:
	virtual ~Rva002C0C0()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva002C0C0_Anchor(Rva002C0C0 *p)
{
	p->Rva002C0C0::~Rva002C0C0();
}

class Rva0041E9F_B2
{
public:
	virtual void f2();
};

class Rva0041E9F : public Rva0049B47C, public MiBase1, public Rva0041E9F_B2
{
public:
	virtual ~Rva0041E9F()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0041E9F_Anchor(Rva0041E9F *p)
{
	p->Rva0041E9F::~Rva0041E9F();
}

class Rva00119D00_B2
{
public:
	virtual void f2();
};

class Rva00119D00 : public Rva0049B47C, public MiBase1, public Rva00119D00_B2
{
public:
	virtual ~Rva00119D00()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00119D00_Anchor(Rva00119D00 *p)
{
	p->Rva00119D00::~Rva00119D00();
}

class Rva00260A3C_B2
{
public:
	virtual void f2();
};

class Rva00260A3C : public Rva0049B47C, public MiBase1, public Rva00260A3C_B2
{
public:
	virtual ~Rva00260A3C()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00260A3C_Anchor(Rva00260A3C *p)
{
	p->Rva00260A3C::~Rva00260A3C();
}

class Rva00A7CF3_B2
{
public:
	virtual void f2();
};

class Rva00A7CF3 : public Rva0049B47C, public MiBase1, public Rva00A7CF3_B2
{
public:
	virtual ~Rva00A7CF3()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00A7CF3_Anchor(Rva00A7CF3 *p)
{
	p->Rva00A7CF3::~Rva00A7CF3();
}

class Rva001ED840_B2
{
public:
	virtual void f2();
};

class Rva001ED840 : public Rva0049B47C, public MiBase1, public Rva001ED840_B2
{
public:
	virtual ~Rva001ED840()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva001ED840_Anchor(Rva001ED840 *p)
{
	p->Rva001ED840::~Rva001ED840();
}

class Rva00543F5_B2
{
public:
	virtual void f2();
};

class Rva00543F5 : public Rva0049B47C, public MiBase1, public Rva00543F5_B2
{
public:
	virtual ~Rva00543F5()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00543F5_Anchor(Rva00543F5 *p)
{
	p->Rva00543F5::~Rva00543F5();
}

class Rva000DC51D_B2
{
public:
	virtual void f2();
};

class Rva000DC51D : public Rva0049B47C, public MiBase1, public Rva000DC51D_B2
{
public:
	virtual ~Rva000DC51D()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva000DC51D_Anchor(Rva000DC51D *p)
{
	p->Rva000DC51D::~Rva000DC51D();
}

class Rva000DE4EB_B2
{
public:
	virtual void f2();
};

class Rva000DE4EB : public Rva0049B47C, public MiBase1, public Rva000DE4EB_B2
{
public:
	virtual ~Rva000DE4EB()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva000DE4EB_Anchor(Rva000DE4EB *p)
{
	p->Rva000DE4EB::~Rva000DE4EB();
}

class Rva000DFDD9_B2
{
public:
	virtual void f2();
};

class Rva000DFDD9 : public Rva0049B47C, public MiBase1, public Rva000DFDD9_B2
{
public:
	virtual ~Rva000DFDD9()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva000DFDD9_Anchor(Rva000DFDD9 *p)
{
	p->Rva000DFDD9::~Rva000DFDD9();
}

class Rva000E03E2_B2
{
public:
	virtual void f2();
};

class Rva000E03E2 : public Rva0049B47C, public MiBase1, public Rva000E03E2_B2
{
public:
	virtual ~Rva000E03E2()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva000E03E2_Anchor(Rva000E03E2 *p)
{
	p->Rva000E03E2::~Rva000E03E2();
}

class Rva0007311B_B2
{
public:
	virtual void f2();
};

class Rva0007311B : public Rva0049B47C, public MiBase1, public Rva0007311B_B2
{
public:
	virtual ~Rva0007311B()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0007311B_Anchor(Rva0007311B *p)
{
	p->Rva0007311B::~Rva0007311B();
}

class Rva00073BFE_B2
{
public:
	virtual void f2();
};

class Rva00073BFE : public Rva0049B47C, public MiBase1, public Rva00073BFE_B2
{
public:
	virtual ~Rva00073BFE()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00073BFE_Anchor(Rva00073BFE *p)
{
	p->Rva00073BFE::~Rva00073BFE();
}

class Rva006F29B_B2
{
public:
	virtual void f2();
};

class BfmeRefSceneList : public Rva0049B47C, public MiBase1, public Rva006F29B_B2
{
public:
	virtual ~BfmeRefSceneList()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva006F29B_Anchor(BfmeRefSceneList *p)
{
	p->BfmeRefSceneList::~BfmeRefSceneList();
}

class Rva0072AED_B2
{
public:
	virtual void f2();
};

class Rva0072AED : public Rva0049B47C, public MiBase1, public Rva0072AED_B2
{
public:
	virtual ~Rva0072AED()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0072AED_Anchor(Rva0072AED *p)
{
	p->Rva0072AED::~Rva0072AED();
}

class Rva00783C5_B2
{
public:
	virtual void f2();
};

class GameFileClass : public Rva0049B47C, public MiBase1, public Rva00783C5_B2
{
public:
	virtual ~GameFileClass()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00783C5_Anchor(GameFileClass *p)
{
	p->GameFileClass::~GameFileClass();
}

class Rva0078B83_B2
{
public:
	virtual void f2();
};

class Rva0078B83 : public Rva0049B47C, public MiBase1, public Rva0078B83_B2
{
public:
	virtual ~Rva0078B83()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0078B83_Anchor(Rva0078B83 *p)
{
	p->Rva0078B83::~Rva0078B83();
}

class Rva00FF4D6_B2
{
public:
	virtual void f2();
};

class Rva00FF4D6 : public Rva0049B47C, public MiBase1, public Rva00FF4D6_B2
{
public:
	virtual ~Rva00FF4D6()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00FF4D6_Anchor(Rva00FF4D6 *p)
{
	p->Rva00FF4D6::~Rva00FF4D6();
}

class Rva0081C7F_B2
{
public:
	virtual void f2();
};

class Rva0081C7F : public Rva0049B47C, public MiBase1, public Rva0081C7F_B2
{
public:
	virtual ~Rva0081C7F()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0081C7F_Anchor(Rva0081C7F *p)
{
	p->Rva0081C7F::~Rva0081C7F();
}

class Rva0081FDD_B2
{
public:
	virtual void f2();
};

class Rva0081FDD : public Rva0049B47C, public MiBase1, public Rva0081FDD_B2
{
public:
	virtual ~Rva0081FDD()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0081FDD_Anchor(Rva0081FDD *p)
{
	p->Rva0081FDD::~Rva0081FDD();
}

class Rva008291D_B2
{
public:
	virtual void f2();
};

class Rva008291D : public Rva0049B47C, public MiBase1, public Rva008291D_B2
{
public:
	virtual ~Rva008291D()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva008291D_Anchor(Rva008291D *p)
{
	p->Rva008291D::~Rva008291D();
}

class Rva009A500_B2
{
public:
	virtual void f2();
};

class Rva009A500 : public Rva0049B47C, public MiBase1, public Rva009A500_B2
{
public:
	virtual ~Rva009A500()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva009A500_Anchor(Rva009A500 *p)
{
	p->Rva009A500::~Rva009A500();
}

class Rva00F2ECB_B2
{
public:
	virtual void f2();
};

class Rva00F2ECB : public Rva0049B47C, public MiBase1, public Rva00F2ECB_B2
{
public:
	virtual ~Rva00F2ECB()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00F2ECB_Anchor(Rva00F2ECB *p)
{
	p->Rva00F2ECB::~Rva00F2ECB();
}

class Rva007C0F5_B2
{
public:
	virtual void f2();
};

class Rva007C0F5 : public Rva0049B47C, public MiBase1, public Rva007C0F5_B2
{
public:
	virtual ~Rva007C0F5()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva007C0F5_Anchor(Rva007C0F5 *p)
{
	p->Rva007C0F5::~Rva007C0F5();
}

class Rva0010EDC2_B2
{
public:
	virtual void f2();
};

class Rva0010EDC2 : public Rva0049B47C, public MiBase1, public Rva0010EDC2_B2
{
public:
	virtual ~Rva0010EDC2()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0010EDC2_Anchor(Rva0010EDC2 *p)
{
	p->Rva0010EDC2::~Rva0010EDC2();
}

class Rva004E32F2_B2
{
public:
	virtual void f2();
};

class Rva004E32F2 : public Rva0049B47C, public MiBase1, public Rva004E32F2_B2
{
public:
	virtual ~Rva004E32F2()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva004E32F2_Anchor(Rva004E32F2 *p)
{
	p->Rva004E32F2::~Rva004E32F2();
}

class Rva005C7CA1
{
public:
	void clear();

private:
	class Rva005C7954Elem *m_elem;
	int m_pad04;
};

class Rva005C7CBB
{
public:
	virtual ~Rva005C7CBB();

private:
	Rva005C7CA1 m_member04;
};

Rva005C7CBB::~Rva005C7CBB()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005C7CBB_Anchor(Rva005C7CBB *p)
{
	p->Rva005C7CBB::~Rva005C7CBB();
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

private:
	Rva005CD14D m_member04;
};

Rva005CD1A9::~Rva005CD1A9()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005CD1A9_Anchor(Rva005CD1A9 *p)
{
	p->Rva005CD1A9::~Rva005CD1A9();
}

class Rva005F35D3
{
public:
	void clear();

private:
	class Rva005F2F80Elem *m_elem;
	int m_pad04;
};

class Rva005F38CA
{
public:
	virtual ~Rva005F38CA();

private:
	Rva005F35D3 m_member04;
};

Rva005F38CA::~Rva005F38CA()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005F38CA_Anchor(Rva005F38CA *p)
{
	p->Rva005F38CA::~Rva005F38CA();
}

class Rva005FC1CA
{
public:
	void clear();

private:
	class Rva005FBF97Elem *m_elem;
	int m_pad04;
};

class Rva005FC1E4
{
public:
	virtual ~Rva005FC1E4();

private:
	Rva005FC1CA m_member04;
};

Rva005FC1E4::~Rva005FC1E4()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005FC1E4_Anchor(Rva005FC1E4 *p)
{
	p->Rva005FC1E4::~Rva005FC1E4();
}

class Rva0060006A
{
public:
	void clear();

private:
	class Rva005FFBCBElem *m_elem;
	int m_pad04;
};

class Rva00600084
{
public:
	virtual ~Rva00600084();

private:
	Rva0060006A m_member04;
};

Rva00600084::~Rva00600084()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00600084_Anchor(Rva00600084 *p)
{
	p->Rva00600084::~Rva00600084();
}

class Rva002CEC0A_B2
{
public:
	virtual void f2();
};

class Rva002CEC0A : public Rva0049B47C, public MiBase1, public Rva002CEC0A_B2
{
public:
	virtual ~Rva002CEC0A()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva002CEC0A_Anchor(Rva002CEC0A *p)
{
	p->Rva002CEC0A::~Rva002CEC0A();
}

class Rva004E18A2_B2
{
public:
	virtual void f2();
};

class Rva004E18A2 : public Rva0049B47C, public MiBase1, public Rva004E18A2_B2
{
public:
	virtual ~Rva004E18A2()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva004E18A2_Anchor(Rva004E18A2 *p)
{
	p->Rva004E18A2::~Rva004E18A2();
}

class Rva0057C39C
{
public:
	void clear();

private:
	class Rva0057C2D4Elem *m_elem;
	int m_pad04;
};

class Rva0057C3B6
{
public:
	virtual ~Rva0057C3B6();

private:
	Rva0057C39C m_member04;
};

Rva0057C3B6::~Rva0057C3B6()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0057C3B6_Anchor(Rva0057C3B6 *p)
{
	p->Rva0057C3B6::~Rva0057C3B6();
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
	virtual void f2();

private:
	char m_pad04[12];
};

class Rva00494A97_S3
{
public:
	virtual void f3();
};

class Rva00494A97_S4
{
public:
	virtual void f4();
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
void Rva00494A97_Anchor(Rva00494A97 *p)
{
	p->Rva00494A97::~Rva00494A97();
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
void Rva005C3F02_Anchor(Rva005C3F02 *p)
{
	p->Rva005C3F02::~Rva005C3F02();
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

private:
	Rva005CB892 m_member04;
};

Rva005CB8D4::~Rva005CB8D4()
{
	m_member04.clear();
}

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva005CB8D4_Anchor(Rva005CB8D4 *p)
{
	p->Rva005CB8D4::~Rva005CB8D4();
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
void Rva003B4100_Anchor(Rva003B4100 *p)
{
	p->Rva003B4100::~Rva003B4100();
}

class Rva00AAE59_B2
{
public:
	virtual void f2();
};

class Rva00AAE59 : public Rva0049B47C, public MiBase1, public Rva00AAE59_B2
{
public:
	virtual ~Rva00AAE59()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00AAE59_Anchor(Rva00AAE59 *p)
{
	p->Rva00AAE59::~Rva00AAE59();
}

class Rva00AB15D_B2
{
public:
	virtual void f2();
};

class Rva00AB15D : public Rva0049B47C, public MiBase1, public Rva00AB15D_B2
{
public:
	virtual ~Rva00AB15D()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00AB15D_Anchor(Rva00AB15D *p)
{
	p->Rva00AB15D::~Rva00AB15D();
}

class Rva00B6CF1_B2
{
public:
	virtual void f2();
};

class Rva00B6CF1 : public Rva0049B47C, public MiBase1, public Rva00B6CF1_B2
{
public:
	virtual ~Rva00B6CF1()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00B6CF1_Anchor(Rva00B6CF1 *p)
{
	p->Rva00B6CF1::~Rva00B6CF1();
}

class Rva00B9AC2_B2
{
public:
	virtual void f2();
};

class Rva00B9AC2 : public Rva0049B47C, public MiBase1, public Rva00B9AC2_B2
{
public:
	virtual ~Rva00B9AC2()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00B9AC2_Anchor(Rva00B9AC2 *p)
{
	p->Rva00B9AC2::~Rva00B9AC2();
}

class Rva0079554_B2
{
public:
	virtual void f2();
};

class Rva0079554 : public Rva0049B47C, public MiBase1, public Rva0079554_B2
{
public:
	virtual ~Rva0079554()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0079554_Anchor(Rva0079554 *p)
{
	p->Rva0079554::~Rva0079554();
}

class Rva00BEDF0_B2
{
public:
	virtual void f2();
};

class Rva00BEDF0 : public Rva0049B47C, public MiBase1, public Rva00BEDF0_B2
{
public:
	virtual ~Rva00BEDF0()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00BEDF0_Anchor(Rva00BEDF0 *p)
{
	p->Rva00BEDF0::~Rva00BEDF0();
}

class Rva00C0DA3_B2
{
public:
	virtual void f2();
};

class Rva00C0DA3 : public Rva0049B47C, public MiBase1, public Rva00C0DA3_B2
{
public:
	virtual ~Rva00C0DA3()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00C0DA3_Anchor(Rva00C0DA3 *p)
{
	p->Rva00C0DA3::~Rva00C0DA3();
}

class Rva0073EE55_B2
{
public:
	virtual void f2();
};

class Rva0073EE55 : public Rva0049B47C, public MiBase1, public Rva0073EE55_B2
{
public:
	virtual ~Rva0073EE55()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0073EE55_Anchor(Rva0073EE55 *p)
{
	p->Rva0073EE55::~Rva0073EE55();
}

class Rva00AADC1_B2
{
public:
	virtual void f2();
};

class Rva000AADC1 : public Rva0049B47C, public MiBase1, public Rva00AADC1_B2
{
public:
	virtual ~Rva000AADC1()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00AADC1_Anchor(Rva000AADC1 *p)
{
	p->Rva000AADC1::~Rva000AADC1();
}

class Rva00AAD26_B2
{
public:
	virtual void f2();
};

class Rva00AAD26 : public Rva0049B47C, public MiBase1, public Rva00AAD26_B2
{
public:
	virtual ~Rva00AAD26()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00AAD26_Anchor(Rva00AAD26 *p)
{
	p->Rva00AAD26::~Rva00AAD26();
}

class Rva00B0028_B2
{
public:
	virtual void f2();
};

class Rva00B0028 : public Rva0049B47C, public MiBase1, public Rva00B0028_B2
{
public:
	virtual ~Rva00B0028()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00B0028_Anchor(Rva00B0028 *p)
{
	p->Rva00B0028::~Rva00B0028();
}

class Rva00B6DD2_B2
{
public:
	virtual void f2();
};

class Rva00B6DD2 : public Rva0049B47C, public MiBase1, public Rva00B6DD2_B2
{
public:
	virtual ~Rva00B6DD2()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00B6DD2_Anchor(Rva00B6DD2 *p)
{
	p->Rva00B6DD2::~Rva00B6DD2();
}

class Rva00B6971_B2
{
public:
	virtual void f2();
};

class Rva00B6971 : public Rva0049B47C, public MiBase1, public Rva00B6971_B2
{
public:
	virtual ~Rva00B6971()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00B6971_Anchor(Rva00B6971 *p)
{
	p->Rva00B6971::~Rva00B6971();
}

class Rva00C6D44_B2
{
public:
	virtual void f2();
};

class Rva00C6D44 : public Rva0049B47C, public MiBase1, public Rva00C6D44_B2
{
public:
	virtual ~Rva00C6D44()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00C6D44_Anchor(Rva00C6D44 *p)
{
	p->Rva00C6D44::~Rva00C6D44();
}

class Rva00A86CE_B2
{
public:
	virtual void f2();
};

class Rva00A86CE : public Rva0049B47C, public MiBase1, public Rva00A86CE_B2
{
public:
	virtual ~Rva00A86CE()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00A86CE_Anchor(Rva00A86CE *p)
{
	p->Rva00A86CE::~Rva00A86CE();
}

class Rva00A897D_B2
{
public:
	virtual void f2();
};

class Rva00A897D : public Rva0049B47C, public MiBase1, public Rva00A897D_B2
{
public:
	virtual ~Rva00A897D()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00A897D_Anchor(Rva00A897D *p)
{
	p->Rva00A897D::~Rva00A897D();
}

class Rva0084CEF_B2
{
public:
	virtual void f2();
};

class Rva0084CEF : public Rva0049B47C, public MiBase1, public Rva0084CEF_B2
{
public:
	virtual ~Rva0084CEF()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0084CEF_Anchor(Rva0084CEF *p)
{
	p->Rva0084CEF::~Rva0084CEF();
}

class ObjectModule_B2
{
public:
	virtual void f2();
};

// Owner proven (unlike the opaque entries above): this deleting dtor sits
// in slot 0 of the ObjectModule vtable (0xC07E1C, shared with the
// DrawableModule twin) and calls the 0x49B47C fold point through the shared
// base pin, matching retail 0x4A10FD.
class ObjectModule : public Rva0049B47C, public MiBase1, public ObjectModule_B2
{
public:
	virtual ~ObjectModule()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void ObjectModule_Anchor(ObjectModule *p)
{
	p->ObjectModule::~ObjectModule();
}

class Rva0014CD63_B2
{
public:
	virtual void f2();
};

// Owner unproven (opaque): this deleting dtor calls the 82B SEH prototype
// dtor at 0x0014CD63 (vptr 0xBD37EC, counted +0x14, StringClass +0x18)
// through the opaque pin, then frees via the pinned ??3. Retail 0x0014CEB4
// has no E8 callers (dead or indirect-only).
class Rva0014CD63 : public Rva0049B47C, public MiBase1, public Rva0014CD63_B2
{
public:
	virtual ~Rva0014CD63()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva0014CD63_Anchor(Rva0014CD63 *p)
{
	p->Rva0014CD63::~Rva0014CD63();
}

class Rva004D7B93_B2
{
public:
	virtual void f2();
};

class Rva004D7B93 : public Rva0049B47C, public MiBase1, public Rva004D7B93_B2
{
public:
	virtual ~Rva004D7B93()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva004D7B93_Anchor(Rva004D7B93 *p)
{
	p->Rva004D7B93::~Rva004D7B93();
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

class Rva005C3A37Elem
{
public:
	~Rva005C3A37Elem();
};

void Rva005C3EE8::clear()
{
	Rva005C3A37Elem *doomed = m_elem;
	m_elem = 0;
	delete doomed;
}

class Rva005C7954Elem
{
public:
	~Rva005C7954Elem();
};

void Rva005C7CA1::clear()
{
	Rva005C7954Elem *doomed = m_elem;
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

class Rva005FFBCBElem
{
public:
	~Rva005FFBCBElem();
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
// ?rva0057C339@Rva0057C339@@QAEXABVAsciiString@@ABUTreeHintRef00217D4C@@@Z @ 0x0057C339 91B gap via rowed AptCall TreeHintRef copy.
// Apt LoadContent loader with TreeHintRef member +0x14 flag +0x18 level +0x0 team +0x4.
// Evidence: TreeHintRef copy 0x002174A4, Version? no, AptCall 0x0050E9FE, LoadContent literal,
// empty g_Rva0107301CEmptyString, manager TheRva00222A8BTarget, caller jmp 0x0057C397.
class AsciiString;
struct TreeHintRef00217D4C
{
    void *m_ptr;
    TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);
class Rva0057C339
{
public:
    void rva0057C339(const AsciiString &a1, const TreeHintRef00217D4C &a2);
private:
    void *m_level;
    char *m_teamData;
    char m_pad08[0x14 - 8];
    TreeHintRef00217D4C m_hint;
    unsigned char m_flag;
};
void Rva0057C339::rva0057C339(const AsciiString &a1, const TreeHintRef00217D4C &a2)
{
    m_hint = a2;
    const char *team1;
    const char *a1data = *(char *const *)&a1;
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
    Rva0057C339 *m_p;
};
void Rva0057C394::rva0057C394(const AsciiString &a1, const TreeHintRef00217D4C &a2)
{
    return m_p->rva0057C339(a1, a2);
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
