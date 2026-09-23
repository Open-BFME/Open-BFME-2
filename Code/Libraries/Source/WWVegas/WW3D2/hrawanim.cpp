// cl: /Ireference/shims/bfmehrawanim /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/hrawanim.cpp); this unit had no counterpart under Code/.
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/hrawanim.cpp                           $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 11/25/01 6:06p                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   HRawAnimClass::HRawAnimClass -- constructor                                                     * 
 *   HRawAnimClass::~HRawAnimClass -- Destructor                                                     * 
 *   HRawAnimClass::Free -- De-allocates all memory in use                                        * 
 *   HRawAnimClass::Load -- Loads hierarchy animation from a file                                 * 
 *   HRawAnimClass::read_channel -- Reads in a single channel of motion                           * 
 *   HRawAnimClass::add_channel -- Adds a motion channel to the animation                         * 
 *   HRawAnimClass::Get_Translation -- returns the translation vector for the given frame         * 
 *   HRawAnimClass::Get_Orientation -- returns a quaternion for the orientation of the pivot      * 
 *   HRawAnimClass::Get_XRotation -- Returns the X euler angle for the given pivot, frame         * 
 *   HRawAnimClass::Get_YRotation -- returns the Y Euler angle for the given pivot, frame         * 
 *   HRawAnimClass::Get_ZRotation -- returns the Z Euler angle for the given pivot, frame         * 
 *   HRawAnimClass::read_bit_channel -- read a bit channel from the file                          *
 *   HRawAnimClass::add_bit_channel -- install a bit channel into the animation                   *
 *   HRawAnimClass::Get_Visibility -- return visibility state for given pivot/frame               *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "hrawanim.h"
#include "motchan.h"
#include "chunkio.h"
#include "assetmgr.h"
#include "htree.h"

// Retail Get_Orientation blends with the normalized-lerp helper at 0x00717550
// (ledger ?BFME2_Nlerp@@YAXAAVQuaternion@@ABV1@1M@Z) where Zero Hour calls
// Fast_Slerp: the target body issues `call 0x717550` for this blend while the
// struct stride already proves the BFME fade-channel layout. Same
// four-argument cdecl shape, so only the REL32 target changes.
void BFME2_Nlerp(Quaternion &result, const Quaternion &p, const Quaternion &q, float alpha);

/***********************************************************************************************
 * NodeMotionStruct::NodeMotionStruct -- constructor                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *=============================================================================================*/
NodeMotionStruct::NodeMotionStruct() : 
	X(NULL),
	Y(NULL),
	Z(NULL),
	XR(NULL),
	YR(NULL),
	ZR(NULL),
	Q(NULL),
	Fade(NULL),
	Vis(NULL)
{
}


/***********************************************************************************************
 * NodeMotionStruct::~NodeMotionStruct -- destructor                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/23/98   GTH : Created.                                                                 *
 *=============================================================================================*/
// ??1NodeMotionStruct@@QAE@XZ present-unmatched
NodeMotionStruct::~NodeMotionStruct()
{
	if (X != NULL) {
		delete X;
	}
	if (Y != NULL) {
		delete Y;
	}
	if (Z != NULL) {
		delete Z;
	}
	if (XR != NULL) {
		delete XR;
	}
	if (YR != NULL) {
		delete YR;
	}
	if (ZR != NULL) {
		delete ZR;
	}
	if (Q != NULL) {
		delete Q;
	}
	if (Vis != NULL) {
		delete Vis;
	}
	if (Fade != NULL) {
		delete Fade;
	}
}


/*********************************************************************************************** 
 * HRawAnimClass::HRawAnimClass -- constructor                                                       * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ??0HRawAnimClass@@QAE@XZ present-unmatched
HRawAnimClass::HRawAnimClass(void) :
	NumFrames(0),
	NumNodes(0),
	FrameRate(0),
	NodeMotion(NULL)
{
	memset(Name,0,W3D_NAME_LEN);
	memset(HierarchyName,0,W3D_NAME_LEN);
}


/*********************************************************************************************** 
 * HRawAnimClass::~HRawAnimClass -- Destructor                                                       * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
HRawAnimClass::~HRawAnimClass(void)
{
	Free();
}


/*********************************************************************************************** 
 * HRawAnimClass::Free -- De-allocates all memory in use                                          * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
void HRawAnimClass::Free(void)
{
	if (NodeMotion != NULL) {
		delete[] NodeMotion;
		NodeMotion = NULL;
	}
}


/*********************************************************************************************** 
 * HRawAnimClass::Load -- Loads hierarchy animation from a file                                   * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// Load_W3D is recovered in HRawLoadW3D.cpp.


/*********************************************************************************************** 
 * HRawAnimClass::read_channel -- Reads in a single channel of motion                             * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
bool HRawAnimClass::read_channel(ChunkLoadClass & cload,MotionChannelClass * * newchan,bool pre30)
{
	*newchan = W3DNEW MotionChannelClass;
	bool result = (*newchan)->Load_W3D(cload);	
	
	if (result && pre30) {
//		(*newchan)->PivotIdx += 1;
		(*newchan)->Set_Pivot((*newchan)->Get_Pivot()+1);
	}
	
	return result;
}

/*********************************************************************************************** 
 * HRawAnimClass::add_channel -- Adds a motion channel to the animation                           * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
void HRawAnimClass::add_channel(MotionChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case ANIM_CHANNEL_X:
			NodeMotion[idx].X = newchan;
			break;

		case ANIM_CHANNEL_Y:
			NodeMotion[idx].Y = newchan;
			break;

		case ANIM_CHANNEL_Z:
			NodeMotion[idx].Z = newchan;
			break;

		case ANIM_CHANNEL_XR:
			NodeMotion[idx].XR = newchan;
			break;

		case ANIM_CHANNEL_YR:
			NodeMotion[idx].YR = newchan;
			break;

		case ANIM_CHANNEL_ZR:
			NodeMotion[idx].ZR = newchan;
			break;

		case ANIM_CHANNEL_Q:
			NodeMotion[idx].Q = newchan;
			break;

		case 15: // ANIM_CHANNEL_FADE: BFME per-pivot fade channel (value 15,
			// BFME1 w3d_file.h; Zero Hour's enum ends at ADAPTIVEDELTA_Q).
			// Stored at NodeMotion[idx].Fade (+0x1C), ahead of Vis.
			NodeMotion[idx].Fade = newchan;
			break;
	}

}


/***********************************************************************************************
 * HRawAnimClass::read_bit_channel -- read a bit channel from the file                            *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?read_bit_channel@HRawAnimClass@@AAE_NAAVChunkLoadClass@@PAPAVBitChannelClass@@_N@Z present-unmatched
bool HRawAnimClass::read_bit_channel(ChunkLoadClass & cload,BitChannelClass * * newchan,bool pre30)
{
	*newchan = W3DNEW BitChannelClass;
	bool result = (*newchan)->Load_W3D(cload);	

	if (result && pre30) {
		(*newchan)->PivotIdx += 1;
	}
	
	return result;
}


/***********************************************************************************************
 * HRawAnimClass::add_bit_channel -- install a bit channel into the animation                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
void HRawAnimClass::add_bit_channel(BitChannelClass * newchan)
{
	int idx = newchan->Get_Pivot();

	switch (newchan->Get_Type())
	{
		case BIT_CHANNEL_VIS:
			NodeMotion[idx].Vis = newchan;
			break;
	}
}

/*********************************************************************************************** 
 * HRawAnimClass::Get_Translation -- returns the translation vector for the given fr              * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?Get_Translation@HRawAnimClass@@UBEXAAVVector3@@HM@Z present-unmatched
void HRawAnimClass::Get_Translation(Vector3& trans, int pividx, float frame ) const
{
	struct NodeMotionStruct * motion = &NodeMotion[pividx];

	if ( (motion->X == NULL) && (motion->Y == NULL) && (motion->Z == NULL) ) {
		 trans.Set(0.0f,0.0f,0.0f);
		return;
	}

//	int frame0 = (int)frame;
	int frame0=WWMath::Float_To_Long(frame-0.499999f);

	int frame1 = frame0 + 1;

	float ratio = frame - (float)frame0;
	WWASSERT( (ratio >= -WWMATH_EPSILON) && (ratio < 1.0f + WWMATH_EPSILON) );

	if ( frame1 >= NumFrames ) {
		frame1 = 0;
	}

	Vector3 trans0(0.0f,0.0f,0.0f);

	if (motion->X != NULL) {
		motion->X->Get_Vector((int)frame0,&(trans0[0]));
	}
	if (motion->Y != NULL) {
		motion->Y->Get_Vector((int)frame0,&(trans0[1]));
	}
	if (motion->Z != NULL) {
		motion->Z->Get_Vector((int)frame0,&(trans0[2]));
	}

	if ( ratio == 0.0f ) {
		trans=trans0;
		return;
	}

	Vector3 trans1(0.0f,0.0f,0.0f);

	if (motion->X != NULL) {
		motion->X->Get_Vector((int)frame1,&(trans1[0]));
	}
	if (motion->Y != NULL) {
		motion->Y->Get_Vector((int)frame1,&(trans1[1]));
	}
	if (motion->Z != NULL) {				
		motion->Z->Get_Vector((int)frame1,&(trans1[2]));
	}

	Vector3::Lerp( trans0, trans1, ratio, &trans );
}

/*********************************************************************************************** 
 * HRawAnimClass::Get_Orientation -- returns a quaternion for the orientation of the              * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
 bool HRawAnimClass::Get_Orientation(Quaternion& q, int pividx,float frame) const
{
	// BFME reports success like BFME1's bool revision (retail 0x0018DD60 sets
	// al=1 on every return path); the quaternion logic below is Zero Hour's.
	// The blend helper is the normalized lerp at 0x00717550, not Fast_Slerp.
//	int frame0 = (int)frame;
	int frame0 = WWMath::Float_To_Long(frame-0.499999f);
	int frame1 = frame0 + 1;

	float ratio = frame - (float)frame0;
	WWASSERT( (ratio >= -WWMATH_EPSILON) && (ratio < 1.0f + WWMATH_EPSILON) );

	if ( frame1 >= NumFrames ) 
	{
		frame1 = 0;
	}

#ifdef SPECIAL_GETVEC_AS_QUAT

	Quaternion q0, q1;

	MotionChannelClass* mc = NodeMotion[pividx].Q;
	if (mc != NULL) 
	{
		mc->Get_Vector_As_Quat((int)frame0, q0);
		mc->Get_Vector_As_Quat((int)frame1, q1);
	}
	else
	{
		q0.Set();
		q1.Set();
	}

	if ( ratio == 0.0f ) 
	{
		q = q0;
	}
	else if ( ratio == 1.0f ) 
	{
		q = q1;
	}
	else
	{
		BFME2_Nlerp(q, q0, q1, ratio);
	}

#else
	float vals[4];

	Quaternion q0(1);
	if (NodeMotion[pividx].Q != NULL) {
		NodeMotion[pividx].Q->Get_Vector((int)frame0,vals);
		q0.Set(vals[0],vals[1],vals[2],vals[3]);
	}

	if ( ratio == 0.0f ) {
		q=q0;
		return;
	}

	Quaternion q1(1);
	if (NodeMotion[pividx].Q != NULL) {
		NodeMotion[pividx].Q->Get_Vector((int)frame1,vals);
		q1.Set(vals[0],vals[1],vals[2],vals[3]);
	}

	Fast_Slerp(q, q0, q1, ratio );
#endif
	// BFME1 keeps Zero Hour behaviour behind a bool report: always true here.
	return true;
}

/*********************************************************************************************** 
 * HRawAnimClass::Get_Transform -- returns the transform matrix for the given frame            * 
 *                                                                                             * 
 * INPUT:                                                                                      * 
 *                                                                                             * 
 * OUTPUT:                                                                                     * 
 *                                                                                             * 
 * WARNINGS:                                                                                   * 
 *                                                                                             * 
 * HISTORY:                                                                                    * 
 *   08/11/1997 GH  : Created.                                                                 * 
 *=============================================================================================*/
// ?Get_Transform@HRawAnimClass@@UBEXAAVMatrix3D@@HM@Z present-unmatched
void HRawAnimClass::Get_Transform(Matrix3D& mtx, int pividx, float frame ) const
{
	struct NodeMotionStruct * motion = &NodeMotion[pividx];

//	if ( (motion->X == NULL) && (motion->Y == NULL) && (motion->Z == NULL) ) {
//		 trans.Set(0.0f,0.0f,0.0f);
//		return;
//	}

	int frame0=WWMath::Float_To_Long(frame-0.499999f);

	int frame1 = frame0 + 1;

	float ratio = frame - (float)frame0;
	WWASSERT( (ratio >= -WWMATH_EPSILON) && (ratio < 1.0f + WWMATH_EPSILON) );

	if ( frame1 >= NumFrames ) {
		frame1 = 0;
	}

	float vals[4];
	Quaternion q0(1);
	if (NodeMotion[pividx].Q != NULL) {
		NodeMotion[pividx].Q->Get_Vector((int)frame0,vals);
		q0.Set(vals[0],vals[1],vals[2],vals[3]);
	}

	if ( ratio == 0.0f ) {
		::Build_Matrix3D(q0,mtx);
		if (motion->X != NULL) motion->X->Get_Vector((int)frame0,&(mtx[0][3]));
		if (motion->Y != NULL) motion->Y->Get_Vector((int)frame0,&(mtx[1][3]));
		if (motion->Z != NULL) motion->Z->Get_Vector((int)frame0,&(mtx[2][3]));
		return;
	}

	Quaternion q1(1);
	if (NodeMotion[pividx].Q != NULL) {
		NodeMotion[pividx].Q->Get_Vector((int)frame1,vals);
		q1.Set(vals[0],vals[1],vals[2],vals[3]);
	}

	Quaternion q;
	Fast_Slerp(q, q0, q1, ratio );
	::Build_Matrix3D(q,mtx);

	Vector3 trans0(0.0f,0.0f,0.0f);
	if (motion->X != NULL) motion->X->Get_Vector((int)frame0,&(trans0[0]));
	if (motion->Y != NULL) motion->Y->Get_Vector((int)frame0,&(trans0[1]));
	if (motion->Z != NULL) motion->Z->Get_Vector((int)frame0,&(trans0[2]));

	Vector3 trans1(0.0f,0.0f,0.0f);
	if (motion->X != NULL) motion->X->Get_Vector((int)frame1,&(trans1[0]));
	if (motion->Y != NULL) motion->Y->Get_Vector((int)frame1,&(trans1[1]));
	if (motion->Z != NULL) motion->Z->Get_Vector((int)frame1,&(trans1[2]));

	Vector3 trans;
	Vector3::Lerp( trans0, trans1, ratio, &trans );

	mtx.Set_Translation(trans);
}

/***********************************************************************************************
 * HRawAnimClass::Get_Visibility -- return visibility state for given pivot/frame                 *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   1/19/98    GTH : Created.                                                                 *
 *=============================================================================================*/
// ?Get_Visibility@HRawAnimClass@@UAE_NHM@Z present-unmatched
bool HRawAnimClass::Get_Visibility(int pividx,float frame)
{
	if (NodeMotion[pividx].Vis != NULL) {
		return (NodeMotion[pividx].Vis->Get_Bit((int)frame) == 1);
	}

	// default to always visible...
	return 1;
}


/***********************************************************************************************
 * HRawAnimClass::Is_Node_Motion_Present -- return true if there is motion defined for this frame *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/23/99    EHC : Created.                                                                 *
 *=============================================================================================*/
bool HRawAnimClass::Is_Node_Motion_Present(int pividx) 
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));

	if (NodeMotion[pividx].X != NULL) return true;
	if (NodeMotion[pividx].Y != NULL) return true;
	if (NodeMotion[pividx].Z != NULL) return true;
	if (NodeMotion[pividx].XR != NULL) return true;
	if (NodeMotion[pividx].YR != NULL) return true;
	if (NodeMotion[pividx].ZR != NULL) return true;
	if (NodeMotion[pividx].Q  != NULL) return true;
	if (NodeMotion[pividx].Vis != NULL) return true;

	return false;
}

bool HRawAnimClass::Has_X_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].X != NULL;
}

bool HRawAnimClass::Has_Y_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].Y != NULL;
}

bool HRawAnimClass::Has_Z_Translation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].Z != NULL;
}

bool HRawAnimClass::Has_Rotation (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].Q != NULL;
}

bool HRawAnimClass::Has_Visibility (int pividx)
{
	WWASSERT((pividx >= 0) && (pividx < NumNodes));
	return NodeMotion[pividx].Vis != NULL;
}


