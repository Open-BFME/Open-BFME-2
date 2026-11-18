// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?setPauseAnimation@W3DModelDraw@@UAEX_N@Z, retail 0x000B377E (114 bytes,
// RET 4): slot 28 of the draw-interface vtable 0x007CBB78, so `this` is the
// interface subobject at +0x0C (m_renderObject +0x50, m_pauseAnimation +0x81,
// m_animationMode +0x84 of W3DModelDraw). Zero Hour's
// W3DModelDraw::setPauseAnimation: an HLod render object (Class_ID 0x19) is
// set to its current animation and frame, held in manual mode while paused
// and back in the remembered mode otherwise. HLodClass's BFME 2 slots:
// Peek_Animation_And_Info +0x208, Set_Animation +0xB4. Storage view as in
// W3DModelDrawGetCurrentBonePositions.cpp.
#include "../../../../../../GameEngine/Include/Common/ScalarTypes.h"

class HAnimClass;

class RenderObjClass
{
public:
	virtual void r000();
	virtual void r001();
	virtual void r002();
	virtual int Class_ID(void) const;	// +0x0C
	virtual void r004();
	virtual void r005();
	virtual void r006();
	virtual void r007();
	virtual void r008();
	virtual void r009();
	virtual void r010();
	virtual void r011();
	virtual void r012();
	virtual void r013();
	virtual void r014();
	virtual void r015();
	virtual void r016();
	virtual void r017();
	virtual void r018();
	virtual void r019();
	virtual void r020();
	virtual void r021();
	virtual void r022();
	virtual void r023();
	virtual void r024();
	virtual void r025();
	virtual void r026();
	virtual void r027();
	virtual void r028();
	virtual void r029();
	virtual void r030();
	virtual void r031();
	virtual void r032();
	virtual void r033();
	virtual void r034();
	virtual void r035();
	virtual void r036();
	virtual void r037();
	virtual void r038();
	virtual void r039();
	virtual void r040();
	virtual void r041();
	virtual void r042();
	virtual void r043();
	virtual void r044();
	virtual void Set_Animation(HAnimClass *motion, float frame, int anim_mode);	// +0xB4
	virtual void r046();
	virtual void r047();
	virtual void r048();
	virtual void r049();
	virtual void r050();
	virtual void r051();
	virtual void r052();
	virtual void r053();
	virtual void r054();
	virtual void r055();
	virtual void r056();
	virtual void r057();
	virtual void r058();
	virtual void r059();
	virtual void r060();
	virtual void r061();
	virtual void r062();
	virtual void r063();
	virtual void r064();
	virtual void r065();
	virtual void r066();
	virtual void r067();
	virtual void r068();
	virtual void r069();
	virtual void r070();
	virtual void r071();
	virtual void r072();
	virtual void r073();
	virtual void r074();
	virtual void r075();
	virtual void r076();
	virtual void r077();
	virtual void r078();
	virtual void r079();
	virtual void r080();
	virtual void r081();
	virtual void r082();
	virtual void r083();
	virtual void r084();
	virtual void r085();
	virtual void r086();
	virtual void r087();
	virtual void r088();
	virtual void r089();
	virtual void r090();
	virtual void r091();
	virtual void r092();
	virtual void r093();
	virtual void r094();
	virtual void r095();
	virtual void r096();
	virtual void r097();
	virtual void r098();
	virtual void r099();
	virtual void r100();
	virtual void r101();
	virtual void r102();
	virtual void r103();
	virtual void r104();
	virtual void r105();
	virtual void r106();
	virtual void r107();
	virtual void r108();
	virtual void r109();
	virtual void r110();
	virtual void r111();
	virtual void r112();
	virtual void r113();
	virtual void r114();
	virtual void r115();
	virtual void r116();
	virtual void r117();
	virtual void r118();
	virtual void r119();
	virtual void r120();
	virtual void r121();
	virtual void r122();
	virtual void r123();
	virtual void r124();
	virtual void r125();
	virtual void r126();
	virtual void r127();
	virtual void r128();
	virtual void r129();
	virtual HAnimClass *Peek_Animation_And_Info(float &frame, int &numFrames, int &mode, float &mult);	// +0x208
};

enum
{
	CLASSID_HLOD = 0x19,
	ANIM_MODE_MANUAL = 0
};

class W3DModelDrawBase
{
public:
	virtual void base00();
protected:
	void *m_moduleData;		// +0x04
	void *m_drawable;		// +0x08
};

class W3DModelDrawInterface
{
public:
	virtual void i00();
	virtual void i01();
	virtual void i02();
	virtual void i03();
	virtual void i04();
	virtual void i05();
	virtual void i06();
	virtual void i07();
	virtual void i08();
	virtual void i09();
	virtual void i10();
	virtual void i11();
	virtual void i12();
	virtual void i13();
	virtual void i14();
	virtual void i15();
	virtual void i16();
	virtual void i17();
	virtual void i18();
	virtual void i19();
	virtual void i20();
	virtual void i21();
	virtual void i22();
	virtual void i23();
	virtual void i24();
	virtual void i25();
	virtual void i26();
	virtual void i27();
	virtual void setPauseAnimation(Bool pauseAnim);	// slot 28
};

class W3DModelDraw : public W3DModelDrawBase, public W3DModelDrawInterface
{
public:
	virtual void setPauseAnimation(Bool pauseAnim);
private:
	char m_pad010[0x50 - 0x10];
	RenderObjClass *m_renderObject;		// +0x50
	char m_pad054[0x81 - 0x54];
	Bool m_pauseAnimation;			// +0x81
	char m_pad082[0x84 - 0x82];
	int m_animationMode;			// +0x84
};

void W3DModelDraw::setPauseAnimation(Bool pauseAnim)
{
	if (m_pauseAnimation == pauseAnim)
		return;

	m_pauseAnimation = pauseAnim;
	if (m_renderObject && m_renderObject->Class_ID() == CLASSID_HLOD)
	{
		float framenum, dummy;
		int mode, numFrames;
		RenderObjClass *hlod = m_renderObject;
		HAnimClass *anim = hlod->Peek_Animation_And_Info(framenum, numFrames, mode, dummy);
		if (anim)
		{
			if (m_pauseAnimation)
			{
				m_animationMode = mode;
				hlod->Set_Animation(anim, framenum, ANIM_MODE_MANUAL);
			}
			else
			{
				hlod->Set_Animation(anim, framenum, m_animationMode);
			}
		}
	}
}
