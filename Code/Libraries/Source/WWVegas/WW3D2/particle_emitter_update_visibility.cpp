// cl: /G7 /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Update_On_Visibilty@ParticleEmitterClass@@MAEXXZ @ 0x001A2260 (91B).
//
// BFME1 donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp
// (ParticleEmitterClass::Update_On_Visibilty via Is_Not_Hidden plus Start and Stop).
// Evidence: vtable slot 132 offset 0x210 of 0x007D69F8 for ctor 0x001A1070 class;
// retail calls virtual plus 0x184 twice and tail-jmps to Start 0x001A1B20;
// Active at plus 0x110 and IsInScene at plus 0x129 and IsInvisible at plus 0x130
// match 0xC4 base layout already proved by Set_Name at 0x001A2220;
// Stop and Is_Stopped are inlined as store plus compares with no direct calls.
// TU-scoped vtable fix: the shared bfmerendobj shim places Is_Not_Hidden_At_All
// at plus 0x180 while retail calls it at plus 0x184 (one missing slot before it).
// This TU models the 0xC4 base with 97 dummy slots so Is_Not_Hidden sits at
// plus 0x184; member offsets (Active 0x110, IsInScene 0x129, IsInvisible 0x130)
// match the donor layout already proved by Set_Name at 0x001A2220.
#define BFME_DUMMY8(a, b, c, d, e, f, g, h) \
	virtual void Dummy##a(); virtual void Dummy##b(); \
	virtual void Dummy##c(); virtual void Dummy##d(); \
	virtual void Dummy##e(); virtual void Dummy##f(); \
	virtual void Dummy##g(); virtual void Dummy##h();

class RenderObjClass
{
public:
	BFME_DUMMY8(0, 1, 2, 3, 4, 5, 6, 7)
	BFME_DUMMY8(8, 9, 10, 11, 12, 13, 14, 15)
	BFME_DUMMY8(16, 17, 18, 19, 20, 21, 22, 23)
	BFME_DUMMY8(24, 25, 26, 27, 28, 29, 30, 31)
	BFME_DUMMY8(32, 33, 34, 35, 36, 37, 38, 39)
	BFME_DUMMY8(40, 41, 42, 43, 44, 45, 46, 47)
	BFME_DUMMY8(48, 49, 50, 51, 52, 53, 54, 55)
	BFME_DUMMY8(56, 57, 58, 59, 60, 61, 62, 63)
	BFME_DUMMY8(64, 65, 66, 67, 68, 69, 70, 71)
	BFME_DUMMY8(72, 73, 74, 75, 76, 77, 78, 79)
	BFME_DUMMY8(80, 81, 82, 83, 84, 85, 86, 87)
	BFME_DUMMY8(88, 89, 90, 91, 92, 93, 94, 95)
	virtual void Dummy96();
	virtual int Is_Not_Hidden_At_All();

	unsigned char _pad[0xC0];
};

class ParticleEmitterClass : public RenderObjClass
{
public:
	void Start();

protected:
	virtual void Update_On_Visibilty();

private:
	unsigned char _pad0[0x4C];
	bool Active;
	bool FirstTime;
	bool BufferSceneNeeded;
	unsigned char _pad1;
	int ParticlesLeft;
	int MaxParticles;
	bool IsComplete;
	unsigned char _pad2[3];
	char *NameString;
	char *UserString;
	bool RemoveOnComplete;
	bool IsInScene;
	unsigned char GroupID;
	unsigned char _pad3;
	void *Buffer;
	bool IsInvisible;
};
#undef BFME_DUMMY8

void ParticleEmitterClass::Update_On_Visibilty(void)
{
	if (Is_Not_Hidden_At_All() && !IsInvisible && !Active && IsInScene) {
		Start();
	} else if ((!Is_Not_Hidden_At_All() || IsInvisible) && Active) {
		Active = false;
	}
	return;
}
