// cl: /arch:SSE /G7 /DNDEBUG /EHsc /MD
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

// Declared object prefixes used only by the out-of-line frame calculation.
// Virtual slot3 is an independently observed DWORD getter with unknown meaning.
class HAnimClass {
public:
 virtual void Delete_This(); virtual ~HAnimClass();
 virtual const char *Get_Name() const;
 virtual unsigned int Unknown_Slot3() const;
 virtual const char *Get_HName() const;
 virtual int Get_Num_Frames(); virtual float Get_Frame_Rate();
};
class WW3D { static unsigned int SyncTime; public: static unsigned int Get_Sync_Time() {return SyncTime;} };
class Animatable3DObjClass {
 enum {SINGLE_ANIM=2, ANIM_MODE_MANUAL=0, ANIM_MODE_LOOP=1, ANIM_MODE_ONCE=2, ANIM_MODE_LOOP_PINGPONG=3, ANIM_MODE_CLAMP_TO_FRAME=4, ANIM_MODE_LOOP_BACKWARDS=5, ANIM_MODE_ONCE_BACKWARDS=6};
 // Verified RenderObj/Composite state plus hierarchy ownership ends at0x100.
 unsigned char ExistingObjectPrefix[0x100];
 int CurMotionMode;
 struct { HAnimClass *Motion; float Frame, TargetFrame; int AnimMode; unsigned int LastSyncTime; float animDirection, frameRateMultiplier; } ModeAnim;
protected: float Compute_Current_Frame(float *newDirection) const;
};
typedef char AnimatablePrefixSizeIs288[(sizeof(Animatable3DObjClass)==0x120)?1:-1];
float Animatable3DObjClass::Compute_Current_Frame(float *newDirection) const
{
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
                            if (frame > ModeAnim.TargetFrame) frame = ModeAnim.TargetFrame;
                        } else {
                            if (frame < ModeAnim.TargetFrame) frame = ModeAnim.TargetFrame;
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

