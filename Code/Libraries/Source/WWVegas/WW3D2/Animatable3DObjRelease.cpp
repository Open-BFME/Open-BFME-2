// cl: /Ireference/shims/bfme2hanim /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeanimobj /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Animatable3DObjClass::Release at 0x001A4AA0 releases motions and the slave master.
// Motion mode is at +0x100; animation references begin at +0x104; the master is at +0xFC.

//
// Animatable3DObjClass::Release at 0x001A4AA0.
//
// Zero Hour's switch plus one release Zero Hour does not have: after dropping
// the single or double animation references, BFME also drops its reference on
// the hierarchy tree, which it counts like the animations.  The case values are
// one higher than Zero Hour's (the bytes test 2 and 3).  Release_Ref inlines to
// --NumRefs / Delete_This through vtable slot 0.
//
// The shared bfme2htree shim models HTreeClass without the reference count, so
// animobj.cpp cannot express the tree release; this unit carries a reduced model
// instead, as Open-BFME-1 did, laid out by BFME 2's offsets (the tree at +0xFC,
// the motion mode at +0x100, the animations from +0x104), four bytes below BFME
// 1's.  /G7 is the unit's tell.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
// Match the retail RefCountClass release helper at 0x5D1A7D.
// Its declaration uses the verified provider's size context; callers retain theirs.
#include "rendobj.h"
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/composite.h"
#include "animobj.h"
#include "ww3d.h"

// The retail RefCountClass release helper is at 0x005D1A7D; Delete_This uses slot 0.
// SINGLE_ANIM and DOUBLE_ANIM use values 2 and 3.
void Animatable3DObjClass::Release(void)
{
	switch (CurMotionMode)
	{
		case SINGLE_ANIM:
			if (ModeAnim.Motion != 0)
			{
				ModeAnim.Motion->Release_Ref();
				ModeAnim.Motion = 0;
			}
			break;

		case DOUBLE_ANIM:
			if (ModeInterp.Motion0 != 0)
			{
				ModeInterp.Motion0->Release_Ref();
				ModeInterp.Motion0 = 0;
			}

			if (ModeInterp.Motion1 != 0)
			{
				ModeInterp.Motion1->Release_Ref();
				ModeInterp.Motion1 = 0;
			}
			break;

		default:
			break;
	}

	if (_bfme_a3o_v0 != 0)
	{
		_bfme_a3o_v0->Release_Ref();
		_bfme_a3o_v0 = 0;
	}
}
