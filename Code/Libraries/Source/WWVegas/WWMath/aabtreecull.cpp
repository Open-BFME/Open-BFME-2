// cl: /Ob2 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /arch:SSE2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// Link view first: Vector3 operator== (and Length/Normalize/ctor/operator*) stay inline without emitting
// COMDAT copies that disagree with the first copy in link order.
#include "refcount.h"
#include "../../../../../reference/shims/bfme_vector3_eq_link/vector3_eq_link.h"
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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
 *                 Project Name : WWMath                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwmath/aabtreecull.cpp                       $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 8/26/01 2:18p                                               $*
 *                                                                                             *
 *                    $Revision:: 25                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


// LINK-COMDAT: FastCriticalSectionClass::LockClass ctor differs from the kept copy.
// ZH mutex.h (via mempool.h) defines it with inline asm (bts loop + Switch_Thread);
// the kept 20B copy (widestring.cpp, FastCriticalSectionLockCtor.cpp) calls spin.
// Declare it here and block mutex.h so this TU emits no copy; calls reach the kept copy.
#define MUTEX_H
class FastCriticalSectionClass
{
	unsigned Flag;
public:
	__declspec(dllimport) FastCriticalSectionClass() : Flag(0) {}
	class LockClass
	{
		FastCriticalSectionClass &cs;
	public:
		LockClass(FastCriticalSectionClass &critical_section);
		~LockClass() { cs.Flag = 0; }
	private:
		LockClass &operator=(const LockClass&);
		LockClass(const LockClass&);
	};
	friend class LockClass;
};

#define COLMATHPLANE_H // use the source-local inline expressions below
#include "aabtreecull.h"
// Use the shared object-pool release copy from AABTreeCullO1Inlines.cpp.
template <> void ObjectPoolClass<AABTreeLinkClass,256>::Free_Object_Memory(AABTreeLinkClass *);
// Defined in AABTreeCullO1Inlines.cpp: retail's single /O1 out-of-line copy of
// the header ctor. Calls here construct the link without emitting this TU's
// non-retail /Ob2 COMDAT copy.
AABTreeLinkClass *_bfmeAABTreeLinkAnchor(void *storage, AABTreeCullSystemClass *system);
#include "chunkio.h"
#include "iostruct.h"
#include <string.h>
#include "sphere.h"
#include "colmath.h"
#include "colmathinlines.h"

// BFME1@34f59164f6 supplies the plane-overlap expressions below.
// Keep the already-inlined math local: only the existing native providers
// own out-of-line get_far_extent (0x0007B5C8) and Plane/Point (0x0007B638).
#include "colmath.h"
#include "plane.h"
#include "aabox.h"
void get_far_extent(const Vector3 &,const Vector3 &,Vector3 *);
// ?bfmeNativePlanePointInline absent-from-retail
static __forceinline CollisionMath::OverlapType
bfmeNativePlanePointInline(const PlaneClass & plane,const Vector3 & point,const float & epsilon)
{
	float delta = Vector3::Dot_Product(point,plane.N) - plane.D;
	if (delta > epsilon) {
		return CollisionMath::POS;
	}
	if (delta < -epsilon) {
		return CollisionMath::NEG;
	}
	return CollisionMath::ON;
}


inline
CollisionMath::OverlapType
CollisionMath::Overlap_Test(const PlaneClass & plane,const AABoxClass & box)
{
	// First, we determine the the near and far points of the box in the
	// direction of the plane normal
	Vector3 posfarpt;
	Vector3 negfarpt;

	get_far_extent(plane.N,box.Extent,&posfarpt);

	negfarpt = -posfarpt;
	posfarpt += box.Center;
	negfarpt += box.Center;
	if (bfmeNativePlanePointInline(plane,negfarpt,COINCIDENCE_EPSILON) == POS) {
		return POS;
	}
	if (bfmeNativePlanePointInline(plane,posfarpt,COINCIDENCE_EPSILON) == NEG) {
		return NEG;
	}
	return BOTH;
}


/*
** Declare the pools
*/
DEFINE_AUTO_POOL(AABTreeLinkClass,256);
DEFINE_AUTO_POOL(AABTreeNodeClass,256);


/*
** Current version of the file format
*/
const uint32 AABTREE_CURRENT_VERSION = 0x00010000;


/*
** Chunk Id's used by the aabtree code to save itself into a file
*/
enum 
{
	AABTREE_CHUNK_VERSION					= 0x00000001,	// version wrapper, contains 32bit version #
	AABTREE_CHUNK_AABNODE					= 0x00000101,	// generic aab-node wrapper
		AABTREE_CHUNK_AABNODE_INFO,							// OBSOLETE! generic aab-node definition (IOAABNodeStruct)
		AABTREE_CHUNK_AABNODE_CONTENTS,						// wrapper around contents of the node
		AABTREE_CHUNK_AABNODE_VARIABLES,						// wrapper around variables for a node

	AABTREE_CHUNK_NODE_INDEX				= 0x00000200,	// wrapper around the node index for an object

	AABTREE_VARIABLE_NODESTRUCT			= 0x00,
	AABTREE_VARIABLE_USERDATA
};


/*
** IOAABNodeStruct
** Data structure for the contents of a node in the AAB-Tree
*/
#define AABNODE_ATTRIBUTE_FRONT_CHILD		0x00000001
#define AABNODE_ATTRIBUTE_BACK_CHILD		0x00000002

struct IOAABNodeStruct
{
	IOVector3Struct	Center;
	IOVector3Struct	Extent;
	uint32				Attributes;
};


/*************************************************************************
**
** Utility functions for walking the object list in an AABTree Node
**
*************************************************************************/
static inline CullableClass * get_first_object(AABTreeNodeClass * node)
{
	return node->Object;		
}

static inline CullableClass * get_next_object(CullableClass * obj)
{
	return ((AABTreeLinkClass *)obj->Get_Cull_Link())->NextObject;
}


// ?Collect_Objects_Recursive@AABTreeCullSystemClass@@ present-unmatched
void AABTreeCullSystemClass::Collect_Objects_Recursive(AABTreeNodeClass * node)
{
	/*
	** Collect any objects in this node
	*/
	if (node->Object) {
		CullableClass * obj = get_first_object(node);
		while (obj) {
			Add_To_Collection(obj);
			obj = get_next_object(obj);
		}
	}

	/*
	** Statistics
	*/
	NODE_TRIVIALLY_ACCEPTED();

	/*
	** Descend into the children
	*/
	if (node->Back) {
		Collect_Objects_Recursive(node->Back);
	}
	if (node->Front) {
		Collect_Objects_Recursive(node->Front);
	}
}


// ?Collect_Objects_Recursive@AABTreeCullSystemClass@@ present-unmatched
void AABTreeCullSystemClass::Collect_Objects_Recursive(AABTreeNodeClass * node,const Vector3 & point)
{
	/*
	** Is the point inside this volume?
	*/
	if (node->Box.Contains(point) == false) {
		NODE_REJECTED();
		return;
	} 

	NODE_ACCEPTED();

	/*
	** Collect any objects in this node
	*/
	if (node->Object) {
		CullableClass * obj = get_first_object(node);
		while (obj) {
			if (obj->Get_Cull_Box().Contains(point)) {
				Add_To_Collection(obj);
			}
			obj = get_next_object(obj);
		}
	}

	/*
	** Descend into the children
	*/
	if (node->Back) {
		Collect_Objects_Recursive(node->Back,point);
	}
	if (node->Front) {
		Collect_Objects_Recursive(node->Front,point);
	}
}

// ?Collect_Objects_Recursive@AABTreeCullSystemClass@@ present-unmatched
void AABTreeCullSystemClass::Collect_Objects_Recursive(AABTreeNodeClass * node,const AABoxClass & box)
{
	/*
	** Cull the given box against the bounding volume of this node
	** If it is culled, stop descending the tree.  If the current node is
	** completely contained inside the given box, jump into the collection function
	** that doesn't do any more volume checking...
	*/
	CollisionMath::OverlapType overlap = CollisionMath::Overlap_Test(box,node->Box);
	if (overlap == CollisionMath::OUTSIDE) {
		NODE_REJECTED();
		return;
	} else if (overlap == CollisionMath::INSIDE) {
		Collect_Objects_Recursive(node);
		return;
	}
	
	NODE_ACCEPTED();

	/*
	** Test any objects in this node
	*/
	if (node->Object) {
		CullableClass * obj = get_first_object(node);
		while (obj) {
			if (CollisionMath::Overlap_Test(box,obj->Get_Cull_Box()) != CollisionMath::OUTSIDE) {
				Add_To_Collection(obj);
			}
			obj = get_next_object(obj);
		}
	}

	/*
	** Recurse into any children
	*/
	if (node->Back) {
		Collect_Objects_Recursive(node->Back,box);
	}
	if (node->Front) {
		Collect_Objects_Recursive(node->Front,box);
	}
}


void AABTreeCullSystemClass::Collect_Objects_Recursive
(
	AABTreeNodeClass * node,
	const FrustumClass & frustum,
	int planes_passed
)
{
	/*
	** Cull the bounding volume of this node against the frustum.
	** If it is culled, stop descending the tree.
	*/
	CollisionMath::OverlapType overlap = CollisionMath::Overlap_Test(frustum,node->Box,planes_passed);
	if (overlap == CollisionMath::OUTSIDE) {
		NODE_REJECTED();
		return;
	} else if (overlap == CollisionMath::INSIDE) {
		Collect_Objects_Recursive(node);
		return;
	}

	NODE_ACCEPTED();
	
	/*
	** Test any objects in this node
	*/
	if (node->Object) {
		CullableClass * obj = get_first_object(node);
		while (obj) {
			if (CollisionMath::Overlap_Test(frustum,obj->Get_Cull_Box()) != CollisionMath::OUTSIDE) {
				Add_To_Collection(obj);
			}
			obj = get_next_object(obj);
		}
	}

	/*
	** Recurse into any children
	*/
	if (node->Back) {
		Collect_Objects_Recursive(node->Back,frustum,planes_passed);
	}
	if (node->Front) {
		Collect_Objects_Recursive(node->Front,frustum,planes_passed);
	}
}


// ?Update_Bounding_Boxes_Recursive@AABTreeCullSystemClass@@ present-unmatched
void AABTreeCullSystemClass::Update_Bounding_Boxes_Recursive(AABTreeNodeClass * node)
{
	MinMaxAABoxClass minmaxbox(node->Box);

	/*
	** Update child boxes first and ensure that we bound them
	*/
	if (node->Front) {
		Update_Bounding_Boxes_Recursive(node->Front);
		minmaxbox.Add_Box(node->Front->Box);
	}
	if (node->Back) {
		Update_Bounding_Boxes_Recursive(node->Back);
		minmaxbox.Add_Box(node->Back->Box);
	}

	/*
	** Make sure we bound our contained objects
	*/
	if (node->Object) {
		CullableClass * obj = get_first_object(node);
		while (obj) {
			minmaxbox.Add_Box(obj->Get_Cull_Box());
			obj = get_next_object(obj);
		}
	}

	node->Box.Init_Min_Max(minmaxbox.MinCorner,minmaxbox.MaxCorner);
}


/*************************************************************************
**
** AABTreeNodeClass Implementation
**
*************************************************************************/
// ??0AABTreeNodeClass@@ present-unmatched
AABTreeNodeClass::AABTreeNodeClass(void) :
	Index(0),	
	Box(Vector3(0,0,0),Vector3(0,0,0)),
	Parent(NULL),
	Front(NULL),
	Back(NULL),
	Object(NULL),
	UserData(0)
{
}


/******************************************************************************************
**
** Partitioning code which generates the tree based on a set of input boxes
**
******************************************************************************************/
// ?Partition@AABTreeNodeClass@@ present-unmatched
void AABTreeNodeClass::Partition(const AABoxClass & bounds,SimpleDynVecClass<AABoxClass> & boxes)
{
	Box = bounds;

	/*
	** if we're down to only 1 box, we're done
	*/
	if (boxes.Count() <= 1) return;

	/*
	** Select and assign the splitting plane
	*/
	SplitChoiceStruct sc;
	Select_Splitting_Plane(&sc,boxes);
	
	/*
	** If there was no good split, just leave all of
	** the objects in this node
	*/
	if (sc.Cost == FLT_MAX) {
		return;
	}

	/*
	** Split the boxes
	** Deallocate the input box array to conserve RAM
	*/
	SimpleDynVecClass<AABoxClass> frontboxes(sc.FrontCount);
	SimpleDynVecClass<AABoxClass> backboxes(sc.BackCount);
	Split_Boxes(sc,boxes,frontboxes,backboxes);
	boxes.Delete_All();

	/*
	** Build a front tree if necessary.
	*/
	if (frontboxes.Count() > 0) {
		Front = new AABTreeNodeClass;
		Front->Parent = this;
		Front->Partition(sc.FrontBox,frontboxes);
	} else {
		Front = NULL;
	}
	
	/*
	** Build a back tree if necessary. 
	*/
	if (backboxes.Count() > 0) {
		Back = new AABTreeNodeClass;
		Back->Parent = this;
		Back->Partition(sc.BackBox,backboxes);
	} else {
		Back = NULL;
	}
}

void AABTreeNodeClass::Split_Boxes
(
	const AABTreeNodeClass::SplitChoiceStruct & sc,
	SimpleDynVecClass<AABoxClass> & boxes,
	SimpleDynVecClass<AABoxClass> & frontboxes,
	SimpleDynVecClass<AABoxClass> & backboxes
)
{
	WWASSERT(boxes.Count() == sc.FrontCount + sc.BackCount);

	// copy each box in the input array into the appropriate output array
	for (int i=0; i<boxes.Count(); i++) {
		
		const AABoxClass & box = boxes[i];

		if (CollisionMath::Overlap_Test(sc.Plane,box.Center) == CollisionMath::FRONT) {

			frontboxes.Add(box);

		} else {

			backboxes.Add(box);

		}
	}

	// when we are all done, the counts should match. 
	WWASSERT(frontboxes.Count() == sc.FrontCount);
	WWASSERT(backboxes.Count() == sc.BackCount);
}


/******************************************************************************************
**
** Partitioning code which searches for the best split for a given set of boxes.  This
** code is re-used by both types of partitioning (partitioning contained objects or
** partitioning based on a set of "seed" boxes.)
**
******************************************************************************************/

void AABTreeNodeClass::Select_Splitting_Plane
(
	SplitChoiceStruct * sc,
	SimpleDynVecClass<AABoxClass> & boxes
)
{
	const int NUM_TRYS = 300;

	/*
	** Try putting axis-aligned planes through some random vertices
	*/
	int objcount = boxes.Count();	
	int trys = 0;
	for (trys = 0; trys < MIN(NUM_TRYS,objcount); trys++) {

		int obj_index;
		SplitChoiceStruct test;
		
		/*
		** Select a random object
		*/
		obj_index = rand() % objcount;
		const AABoxClass & box = boxes[obj_index];

		/*
		** Select a random plane which co-incides with one of the faces
		** of the object's bounding box
		*/
		switch(rand() % 6) {
			case 0:	test.Plane.Set(AAPlaneClass::XNORMAL,box.Center.X + box.Extent.X);	break;
			case 1:	test.Plane.Set(AAPlaneClass::XNORMAL,box.Center.X - box.Extent.X);	break;
			case 2:	test.Plane.Set(AAPlaneClass::YNORMAL,box.Center.Y + box.Extent.Y);	break;
			case 3:	test.Plane.Set(AAPlaneClass::YNORMAL,box.Center.Y - box.Extent.Y);	break;
			case 4:	test.Plane.Set(AAPlaneClass::ZNORMAL,box.Center.Z + box.Extent.Z);	break;
			case 5:	test.Plane.Set(AAPlaneClass::ZNORMAL,box.Center.Z - box.Extent.Z);	break;
		};

		/*
		** Get the score for this plane
		*/
		Compute_Score(&test,boxes);
		if (test.Cost < sc->Cost) {
			*sc = test;
		}

	}

	/*
	** Still haven't found a valid splitting plane, uh-oh.
	*/
	if ((trys >= MIN(NUM_TRYS,objcount)) && (sc->Cost == FLT_MAX)) {
		Select_Splitting_Plane_Brute_Force(sc,boxes);
		return;
	}
}

void AABTreeNodeClass::Select_Splitting_Plane_Brute_Force
(
	AABTreeNodeClass::SplitChoiceStruct * sc,
	SimpleDynVecClass<AABoxClass> & boxes
)
{ 
	/*
	** Try putting axis-aligned planes along each face of each box
	*/
	int objcount = boxes.Count();	
	for (int obj_index = 0; obj_index < objcount; obj_index++) {

		AAPlaneClass plane;
		const AABoxClass & box = boxes[obj_index];

		/*
		** Try each face of this box 
		*/
		for (int plane_index = 0; plane_index < 6; plane_index++) {
			SplitChoiceStruct test;
			switch(plane_index % 6) {
				case 0:	test.Plane.Set(AAPlaneClass::XNORMAL,box.Center.X + box.Extent.X);	break;
				case 1:	test.Plane.Set(AAPlaneClass::XNORMAL,box.Center.X - box.Center.Y);	break;
				case 2:	test.Plane.Set(AAPlaneClass::YNORMAL,box.Center.Y + box.Center.Y);	break;
				case 3:	test.Plane.Set(AAPlaneClass::YNORMAL,box.Center.Y - box.Center.Y);	break;
				case 4:	test.Plane.Set(AAPlaneClass::ZNORMAL,box.Center.Z + box.Center.Z);	break;
				case 5:	test.Plane.Set(AAPlaneClass::ZNORMAL,box.Center.Z - box.Center.Z);	break;
			};

			test.FrontBox.Init_Empty();
			test.BackBox.Init_Empty();

			/*
			** Get the score for this plane
			*/
			Compute_Score(&test,boxes);
			if (test.Cost < sc->Cost) {
				*sc = test;
			}
		}
	}

	/*
	** Notify user that we couldn't split this node
	*/
#ifdef WWDEBUG
	if (sc->Cost == FLT_MAX) {		
		WWDEBUG_SAY(("Unable to split node!  objcount = %d. (%.2f,%.2f,%.2f)\r\n",objcount,Box.Center.X, Box.Center.Y, Box.Center.Z));
	}
#endif
}


void AABTreeNodeClass::Compute_Score
(
	AABTreeNodeClass::SplitChoiceStruct * sc,
	SimpleDynVecClass<AABoxClass> & boxes
)
{
	/*
	** Suitability of a plane as a partition plane is based on the following factors:
	** - How many "tiles" are on each side of the plane,
	*/
	for (int i=0; i<boxes.Count(); i++) {

		const AABoxClass & box = boxes[i];

		if (CollisionMath::Overlap_Test(sc->Plane,box.Center) == CollisionMath::FRONT) {

			sc->FrontCount++;	
			sc->FrontBox.Add_Box(box);	

		} else {
			
			sc->BackCount++;	
			sc->BackBox.Add_Box(box);	

		}
	}

	/*
	** Compute the cost.
	*/
	float back_cost = sc->BackBox.Volume() * sc->BackCount;
	float front_cost = sc->FrontBox.Volume() * sc->FrontCount;
	
	sc->Cost = front_cost + back_cost;
	
	if ((sc->FrontCount == 0) || (sc->BackCount == 0)) {
		sc->Cost = FLT_MAX;
	}
}


void AABTreeIterator::Reset(void)
{
	CurNodeIndex = 0;
}

/*

  Can we make a more compact AABTree?

  Here is the existing data in each Node:

	uint32					Index;				// Index of this node
	AABoxClass				Box;					// Bounding box of the node
	AABTreeNodeClass *	Parent;				// parent of this node
	AABTreeNodeClass *	Front;				// front node
	AABTreeNodeClass *	Back;					// back node
	CullableClass *		Object;				// objects in this node
	uint32					UserData;			// 32bit field for the user, initialized to 0

	Total Size:				48 bytes

	Here is a possible replacement:

	uint16					Index;
	short						x,y,z,w,l,h;		// Need origin and scale factors for the boxes stored in tree
	uint16					ParentIndex;
	uint16					FrontIndex;
	uint16					BackIndex;
	CullableClass *		Object;
	uint32					UserData;
	
	Total Size:				28 bytes

*/
