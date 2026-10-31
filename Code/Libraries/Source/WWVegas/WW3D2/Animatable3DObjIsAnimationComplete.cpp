// cl: /Ireference/shims/bfme2hanim /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeanimobj /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Is_Animation_Complete@Animatable3DObjClass@@UBE_NXZ, RVA 0x001A5360, 117B. Virtual slot 131 (offset 0x20C) of vtable 0x007D6D10 (class of ??0Animatable3DObjClass@@QAE@PBD@Z in animobj.cpp). Evidence: vtable slot 131 next to slot 130 Peek_Animation_And_Info at 0x001A53E0; donor BFME1 animobj.cpp Is_Animation_Complete extended with BFME2 CLAMP_TO_FRAME per AnimatableFrameProgress.cpp modes; retail checks AnimMode 2 ONCE vs NumFrames-1 and 6 ONCE_BACKWARDS vs 0 and 4 CLAMP_TO_FRAME vs PrevFrame at +0x10C; HAnim Get_Num_Frames at slot 5 (+0x14).
// ?Is_Animation_Complete@Animatable3DObjClass@@UBE_NXZ, RVA 0x001A5360, 117B. Virtual slot 131 (offset 0x20C) of vtable 0x007D6D10 (class of ??0Animatable3DObjClass@@QAE@PBD@Z in animobj.cpp). Evidence: vtable slot 131 next to slot 130 Peek_Animation_And_Info at 0x001A53E0; donor BFME1 animobj.cpp Is_Animation_Complete extended with BFME2 CLAMP_TO_FRAME per AnimatableFrameProgress.cpp modes; retail checks AnimMode 2 ONCE vs NumFrames-1 and 6 ONCE_BACKWARDS vs 0 and 4 CLAMP_TO_FRAME vs TargetFrame; HAnim Get_Num_Frames at slot 5 (+0x14).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
#include "rendobj.h"
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/composite.h"
#include "animobj.h"
#include "ww3d.h"

bool Animatable3DObjClass::Is_Animation_Complete(void) const
{
	// BFME 2 inserts clamp-to-frame before the backwards modes; PrevFrame holds its target.
	enum { ANIM_MODE_CLAMP_TO_FRAME = 4, ANIM_MODE_ONCE_BACKWARDS = 6 };
	if (CurMotionMode == SINGLE_ANIM) {
		if (ModeAnim.AnimMode == ANIM_MODE_ONCE) {
			return (ModeAnim.Frame == (float)(ModeAnim.Motion->Get_Num_Frames() - 1));
		} else if (ModeAnim.AnimMode == ANIM_MODE_ONCE_BACKWARDS) {
			return (ModeAnim.Frame == 0.0f);
		} else if (ModeAnim.AnimMode == ANIM_MODE_CLAMP_TO_FRAME) {
			return (ModeAnim.Frame == ModeAnim.PrevFrame);
		}
	}
	return false;
}
