// cl: /Ireference/shims/bfme2hanim /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeanimobj /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
 // Verified RenderObj/Composite state plus hierarchy ownership ends at0x100.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// RenderObj/Composite state and hierarchy ownership end at +0x100.
// HAnim virtual slot 3 is a DWORD getter; frame count and rate occupy slots 5 and 6.
#include "rendobj.h"
#include "../../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/composite.h"
#include "animobj.h"
#include "ww3d.h"

float Animatable3DObjClass::Compute_Current_Frame(float *newDirection) const
{
	// BFME 2 inserts clamp-to-frame before the backwards modes; PrevFrame holds its target.
	enum { ANIM_MODE_CLAMP_TO_FRAME = 4, ANIM_MODE_LOOP_BACKWARDS = 5, ANIM_MODE_ONCE_BACKWARDS = 6 };
	float frame = 0;
	float direction = ModeAnim.animDirection;

	switch (CurMotionMode)
	{
		case SINGLE_ANIM:
		{
			frame = ModeAnim.Frame;

			//
			//	Compute the current frame based on elapsed time.
			//
			if (ModeAnim.AnimMode != ANIM_MODE_MANUAL) {
				float sync_time_diff = WW3D::Get_Sync_Time() - ModeAnim.LastSyncTime;
				float delta = ModeAnim.Motion->Get_Frame_Rate() * ModeAnim.frameRateMultiplier * ModeAnim.animDirection * sync_time_diff * 0.001f;
				frame += delta;

				//
				//	Wrap the frame
				//
				switch (ModeAnim.AnimMode)
				{
					case ANIM_MODE_ONCE:
						if (frame >= ModeAnim.Motion->Get_Num_Frames() - 1) {
							frame = ModeAnim.Motion->Get_Num_Frames() - 1;
						}
						break;
					case ANIM_MODE_LOOP:
						if ( frame >= ModeAnim.Motion->Get_Num_Frames() - 1 ) {
							frame -= ModeAnim.Motion->Get_Num_Frames() - 1;
						}
						// If it is still too far out, reset
						if ( frame >= ModeAnim.Motion->Get_Num_Frames() - 1 ) {
							frame = 0;
						}
						break;
					case ANIM_MODE_ONCE_BACKWARDS:	//play animation one time but backwards
						if (frame < 0) {
							frame = 0;
						}
						break;
					case ANIM_MODE_LOOP_BACKWARDS:	//play animation backwards in a loop
						if ( frame < 0 ) {
							frame += ModeAnim.Motion->Get_Num_Frames() - 1;
						}
						// If it is still too far out, reset
						if ( frame < 0 ) {
							frame = ModeAnim.Motion->Get_Num_Frames() - 1;
						}
						break;
					case ANIM_MODE_LOOP_PINGPONG:
						if (ModeAnim.animDirection >= 1.0f)
						{	//playing forwards, reverse direction
							if (frame >= (ModeAnim.Motion->Get_Num_Frames() - 1))
							{	//step backwards in animation by excess time
								frame = (ModeAnim.Motion->Get_Num_Frames() - 1)*2 - frame;
								// If it is still too far out, reset
								if ( frame >= ModeAnim.Motion->Get_Num_Frames() - 1 )
									frame = (ModeAnim.Motion->Get_Num_Frames() - 1);
								direction = ModeAnim.animDirection * -1.0f;
							}
						}
						else
						{	//playing backwards, reverse direction
							if (frame < 0)
							{	//step forwards in animation by excess time
								frame = -frame;
								// If it is still too far out, reset
								if ( frame >= ModeAnim.Motion->Get_Num_Frames() - 1 )
										frame = 0;
								direction = ModeAnim.animDirection * -1.0f;
							}
						}
						break;
					case ANIM_MODE_CLAMP_TO_FRAME:
                        if (ModeAnim.animDirection > 0.0f) {
                            if (frame > ModeAnim.PrevFrame) frame = ModeAnim.PrevFrame;
                        } else {
                            if (frame < ModeAnim.PrevFrame) frame = ModeAnim.PrevFrame;
                        }
                        break;

				}
			}
		}
		break;
	}
  
	if (newDirection)
		*newDirection = direction;
	return frame;	  
}

