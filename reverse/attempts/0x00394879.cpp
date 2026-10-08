// ?isLocationClearOfObjects@BuildAssistant@@UAE_NPBUCoord3D@@PBVThingTemplate@@MPAVObject@@IPAVPlayer@@_N@Z
// partial score=0.75 date=2026-10-08
// Banked partial for BuildAssistant::isLocationClearOfObjects (0x00394879, 1838 bytes).
// Unified diff against Code/GameEngine/Source/Common/System/BuildAssistant.cpp at 5f2e8463c2; apply with patch -p0.
#if 0
// Also needs these header/contract declarations (callees 0x00005A26 and 0x00003755):
diff --git a/Code/Libraries/Include/Lib/Coord2D.h b/Code/Libraries/Include/Lib/Coord2D.h
index 179dc4a9d4..25c2b3fe55 100644
--- a/Code/Libraries/Include/Lib/Coord2D.h
+++ b/Code/Libraries/Include/Lib/Coord2D.h
@@ -9,6 +9,7 @@ public:
     float x;
     float y;
     void normalize();
+    float length() const;
 };
 
 #endif // CANONICAL_COORD2D_H
diff --git a/Code/Libraries/Include/Lib/Coord3D.h b/Code/Libraries/Include/Lib/Coord3D.h
index 356c770a80..bcd7685170 100644
--- a/Code/Libraries/Include/Lib/Coord3D.h
+++ b/Code/Libraries/Include/Lib/Coord3D.h
@@ -9,6 +9,7 @@ struct Coord3D {
     float y;
     float z;
     float length() const;
+    float GetLength() const;
     void normalize();
     bool operator==(const Coord3D &r);
 };
diff --git a/reverse/class_contracts/Coord2D.json b/reverse/class_contracts/Coord2D.json
index f4e65f36a8..d69c132889 100644
--- a/reverse/class_contracts/Coord2D.json
+++ b/reverse/class_contracts/Coord2D.json
@@ -31,6 +31,14 @@
     "size": 71,
     "source": "Code/Libraries/Source/WWVegas/WWMath/coord2d.cpp",
     "decided_by": "byte-verified owner; native 0x004EFDDC AISkirmishPlayer::computeSuperweaponTarget calls this owner on its eight-byte two-float offset"
+   },
+   {
+    "declaration": "float length() const;",
+    "name": "?length@Coord2D@@QBEMXZ",
+    "rva": "0x00003755",
+    "size": 53,
+    "source": "Code/Libraries/Source/WWVegas/WWMath/coord2d.cpp",
+    "decided_by": "byte-verified owner; BuildAssistant::isLocationClearOfObjects 0x00394DD8 calls it on its eight-byte two-float door delta"
    }
   ]
  },
diff --git a/reverse/class_contracts/Coord3D.json b/reverse/class_contracts/Coord3D.json
index 4ffc988594..4acb7c4bcb 100644
--- a/reverse/class_contracts/Coord3D.json
+++ b/reverse/class_contracts/Coord3D.json
@@ -51,6 +51,14 @@
     "size": 57,
     "source": "Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp",
     "decided_by": "byte-verified owner ??8Coord3D@@QBE_NABV0@@Z; this nonconst struct spelling is the existing symbols.csv pin the struct-key callers use; Weapon::getPreAttackDelay 0x002CCFF0 and DockUpdate 0x00589A86 call it on two three-float positions"
+   },
+   {
+    "declaration": "float GetLength() const;",
+    "name": "?GetLength@Coord3D@@QBEMXZ",
+    "rva": "0x00005A26",
+    "size": 43,
+    "source": "Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp",
+    "decided_by": "byte-verified owner; BuildAssistant::isLocationClearOfObjects 0x00394CB6 calls it on its twelve-byte door offset"
    }
   ]
  },
// BuildAssistant.cpp diff follows.
--- Code/GameEngine/Source/Common/System/BuildAssistant.cpp
+++ Code/GameEngine/Source/Common/System/BuildAssistant.cpp
@@ -43,6 +43,7 @@
 #include <math.h>
 #include "ascii_string.h"
 #include "unicode_string.h"
+#include "../../../../Libraries/Include/Lib/Coord2D.h"
 #include "../../../../Libraries/Include/Lib/Coord3D.h"
 #include "../GameLogicObjectLookupView.h"
 #include "../PartitionRangeQueryCallView.h"
@@ -73,6 +74,7 @@
 	KINDOF_2 = 2,
 	KINDOF_SHRUBBERY = 6,
 	KINDOF_STRUCTURE = 7,
+	KINDOF_12 = 12,
 	KINDOF_DOZER = 14,
 	KINDOF_15 = 15,
 	KINDOF_30 = 30,
@@ -82,6 +84,7 @@
 	KINDOF_86 = 86,		// ZH's KINDOF_SUPPLY_SOURCE role
 	KINDOF_INERT = 89,
 	KINDOF_104 = 104,
+	KINDOF_120 = 120,
 	KINDOF_149 = 149,
 	KINDOF_152 = 152,
 	KINDOF_NOT_SELLABLE = 154,
@@ -96,7 +99,8 @@
 {
 	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
 	OBJECT_STATUS_UNSELECTABLE = 3,
-	OBJECT_STATUS_SOLD = 19
+	OBJECT_STATUS_SOLD = 19,
+	OBJECT_STATUS_98 = 98
 };
 
 enum DamageType
@@ -166,7 +170,9 @@
 
 enum CellShroudStatus
 {
-	CELLSHROUD_CLEAR
+	CELLSHROUD_CLEAR,
+	CELLSHROUD_3 = 3,
+	CELLSHROUD_4 = 4
 };
 
 enum ObjectScriptStatusBit
@@ -260,6 +266,28 @@
 	Real m_range;				// +0x30
 };
 
+// What ThingTemplate::rva0033B3D7 finds among the template's module data:
+// +0x2C is the range isLocationClearOfObjects' position filter accepts.
+class Rva0033B3D7Data
+{
+public:
+	unsigned char m_pad00[0x2C];
+	Real m_range;				// +0x2C
+};
+
+// The template's behavior module records (ModuleInfo, 20 bytes each).
+class ModuleInfo
+{
+public:
+	Int getCount() const { return ((const char *)m_end - (const char *)m_begin) / 20; }
+	const ModuleData *getNthData(Int i) const;
+
+private:
+	const void *m_begin;
+	const void *m_end;
+	const void *m_storage;
+};
+
 class ThingTemplate
 {
 public:
@@ -267,11 +295,14 @@
 	Bool isEquivalentTo(const ThingTemplate *tt) const;
 	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
 	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
+	__forceinline Bool isKindOfB(KindOfType t) const { return (((const unsigned char *)m_kindOf)[t >> 3] & (1 << (t & 7))) != 0; }
 	UnsignedInt getMaxSimultaneousOfType() const { return m_maxSimultaneousOfType; }
 	Real friend_calcVisionRange() const { return m_visionRange; }
 	UnsignedShort getRefundValue() const { return m_refundValue; }
 	Int rva0033A69A(const Player *player, Int a, Int b) const;
 	const ModuleData *rva0033B427(Int unused) const;
+	const ModuleData *rva0033B3D7() const;
+	const ModuleInfo &getBehaviorModuleInfo() const { return m_behaviorModuleInfo; }
 
 private:
 	unsigned char m_pad000[0x64];
@@ -280,7 +311,9 @@
 	GeometryInfo m_geometryInfo;	// +0xA0
 	unsigned char m_pad0FC[0x108 - 0xFC];
 	UnsignedInt m_kindOf[8];		// +0x108
-	unsigned char m_pad128[0x4AC - 0x128];
+	unsigned char m_pad128[0x2E4 - 0x128];
+	ModuleInfo m_behaviorModuleInfo;	// +0x2E4
+	unsigned char m_pad2F0[0x4AC - 0x2F0];
 	Real m_visionRange;			// +0x4AC, ZH's name for addBibs' base range
 	unsigned char m_pad4B0[0x5DC - 0x4B0];
 	UnsignedShort m_refundValue;		// +0x5DC
@@ -586,6 +619,7 @@
 {
 public:
 	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
+	__forceinline Bool isKindOfB(KindOfType t) const { return m_template->isKindOfB(t); }
 	Bool isEffectivelyDead() const { return m_isEffectivelyDead; }
 	Bool testScriptStatusBit(ObjectScriptStatusBit b) const { return (m_scriptStatus & b) != 0; }
 	AIUpdateInterface *getAI() const { return m_ai; }
@@ -599,6 +633,7 @@
 	const Coord3D *getPosition() const { return &m_position; }
 	Real getOrientation() const { return m_orientation; }
 	Relationship getRelationship(const Object *that) const;
+	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
 	ObjectID getID() const { return m_id; }
 	Bool testStatus(ObjectStatusTypes bit) const;
 	void rva0028CDEB(const Rva00346BC0 &mask, Bool set);		// setStatus
@@ -621,7 +656,9 @@
 	Real m_orientation;			// +0x044
 	unsigned char m_pad048[0x74 - 0x48];
 	ObjectID m_id;				// +0x074
-	unsigned char m_pad078[0xA8 - 0x78];
+	unsigned char m_pad078[0x94 - 0x78];
+	unsigned int m_statusBits[3];		// +0x094
+	unsigned char m_pad0A0[0xA8 - 0xA0];
 	GeometryInfo m_geometryInfo;		// +0x0A8
 	unsigned char m_pad104[0x244 - 0x104];
 	BehaviorModule **m_behaviors;		// +0x244, null-terminated
@@ -787,6 +824,8 @@
 	Real m_allowedHeightVariationForBuilding;	// +0xA70
 	unsigned char m_padA74[0xB94 - 0xA74];
 	Real m_sellPercentage;			// +0xB94
+	unsigned char m_padB98[0x1220 - 0xB98];
+	Real m_1220;				// +0x1220, isLocationClearOfObjects' query margin
 };
 extern GlobalData *TheWritableGlobalData;
 
@@ -841,6 +880,7 @@
 	void AddObjectToPathfindMap(Object *object);
 	void GetCellType(int pos, void *isValid, void *isBlocked, void *cellType, int layer);
 	void *rva001E4461(int layer, int pos);
+	Bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, Int unused);
 };
 
 class AI
@@ -2105,3 +2145,367 @@
 	return LBC_OK;
 
 }  // end isLocationLegalToBuild
+
+// isLocationClearOfObjects' position filter (ctor 0x00391667, vftable
+// 0x00C1A068): +0x08 is a range read from the template's module data.
+class Rva00391667 : public Rva000421C8
+{
+public:
+	Rva00391667(const void *pos);
+	virtual Bool allow(Object *obj);
+
+	Real m_range;				// +0x08
+	Coord3D m_pos;				// +0x0C
+};
+
+// The would-collide filter with BFME2's second flag (ctor 0x0039161C,
+// vftable 0x00C1A05C); a KINDOF_189 build clears +0x1D.
+class Rva0039161C : public Rva000421C8
+{
+public:
+	Rva0039161C(const void *pos, const void *geom, Real angle, bool desired);
+	virtual Bool allow(Object *obj);
+
+	Coord3D m_pos;				// +0x08
+	const void *m_geom;			// +0x14
+	Real m_angle;				// +0x18
+	bool m_desired;				// +0x1C
+	bool m_1d;				// +0x1D
+};
+
+// vftable 0x00C0716C: the player-index filter the door check links behind
+// the structure filter.
+class Rva00261353Filter : public Rva000421C8
+{
+public:
+	Rva00261353Filter(Int playerIndex) : m_playerIndex(playerIndex) {}
+	virtual Bool allow(Object *obj);
+
+	Int m_playerIndex;			// +0x08
+};
+
+class Module
+{
+	unsigned char m_pad00[0x18];
+public:
+	ObjectID m_18;				// +0x18
+};
+
+class CastleBehavior
+{
+public:
+	static Module *rva000395708(Object *obj);
+};
+
+class PoolMember
+{
+public:
+	void Rva00268902();
+};
+
+struct Rva00394173Node
+{
+	Rva00394173Node *m_next;
+	Rva00394173Node *m_prev;
+	ObjectID m_id;				// +0x08
+};
+
+// The ObjectID list the player's getter (0x00394173) returns by value; its
+// destructor is the pool list teardown 0x00268902.
+class Rva00394173Member
+{
+public:
+	Rva00394173Member(const Rva00394173Member &that);
+	~Rva00394173Member() { ((PoolMember *)this)->Rva00268902(); }
+
+	Rva00394173Node *m_head;
+};
+
+class Rva00394173Field
+{
+public:
+	Rva00394173Member get() const;
+};
+
+// ModuleData vslots 25 and 29: the exit and door data
+// isLocationClearOfObjects offsets its path check by.
+struct Rva00394879Exit
+{
+	unsigned char m_pad00[0x14];
+	Coord3D m_offset;			// +0x14
+};
+
+struct Rva00394879Door
+{
+	unsigned char m_pad00[0xC8];
+	Coord3D m_offset;			// +0xC8
+};
+
+class ModuleData
+{
+public:
+	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
+	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
+	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
+	virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
+	virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
+	virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
+	virtual void m24();
+	virtual const Rva00394879Exit *rva00394879Exit() const;	// +0x64
+	virtual void m26(); virtual void m27(); virtual void m28();
+	virtual const Rva00394879Door *rva00394879Door() const;	// +0x74
+};
+
+class WWMath
+{
+public:
+	static float __fastcall Inv_Sqrt(float val);
+};
+
+class Vector4
+{
+public:
+	float X, Y, Z, W;
+	float &operator[](int i) { return (&X)[i]; }
+	const float &operator[](int i) const { return (&X)[i]; }
+};
+
+class Matrix3D
+{
+public:
+	__forceinline void Make_Identity()
+	{
+		Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
+		Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
+		Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
+	}
+	__forceinline void Rotate_Z(float theta)
+	{
+		float tmp1, tmp2;
+		float c = (float)cos(theta);
+		float s = (float)sin(theta);
+		tmp1 = Row[0][0]; tmp2 = Row[0][1];
+		Row[0][0] = c * tmp1 + s * tmp2;
+		Row[0][1] = -s * tmp1 + c * tmp2;
+		tmp1 = Row[1][0]; tmp2 = Row[1][1];
+		Row[1][0] = c * tmp1 + s * tmp2;
+		Row[1][1] = -s * tmp1 + c * tmp2;
+		tmp1 = Row[2][0]; tmp2 = Row[2][1];
+		Row[2][0] = c * tmp1 + s * tmp2;
+		Row[2][1] = -s * tmp1 + c * tmp2;
+	}
+	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
+	{
+		Vector3 tmp(0.0f, 0.0f, 0.0f);
+		const Vector3 *v;
+		if (out == &in)
+		{
+			tmp = in;
+			v = &tmp;
+		}
+		else
+		{
+			v = &in;
+		}
+		out->X = A.Row[0][0] * v->X + A.Row[0][1] * v->Y + A.Row[0][2] * v->Z + A.Row[0][3];
+		out->Y = A.Row[1][0] * v->X + A.Row[1][1] * v->Y + A.Row[1][2] * v->Z + A.Row[1][3];
+		out->Z = A.Row[2][0] * v->X + A.Row[2][1] * v->Y + A.Row[2][2] * v->Z + A.Row[2][3];
+	}
+
+	Vector4 Row[3];
+};
+
+//-------------------------------------------------------------------------------------------------
+/** Is the footprint of 'build' at 'worldPos' clear of objects that would stop
+  * the construction? Zero Hour's check (objects to remove for construction,
+  * inert kinds, the builder and enemies) with BFME2's additions read off
+  * retail 0x00394879: module data that supplies its own query range, the
+  * shroud test for the builder's player, castle members of a KINDOF_120
+  * builder, the player's ObjectID list option, and a final path and door
+  * check from the template's exit or door offset. */
+inline Bool Object::testStatus( ObjectStatusTypes bit ) const
+{
+	return ( m_statusBits[(UnsignedInt)bit >> 5] & ( 1 << ( bit & 31 ) ) ) != 0;
+}
+
+//-------------------------------------------------------------------------------------------------
+Bool BuildAssistant::isLocationClearOfObjects( const Coord3D *worldPos, const ThingTemplate *build, Real angle, Object *builderObject, UnsignedInt options, Player *player, Bool flag )
+{
+	Bool b20 = (options >> 5) & 1;
+	Bool b40 = (options >> 6) & 1;
+	Bool b100 = (options >> 8) & 1;
+	Bool b200 = (options >> 9) & 1;
+	Bool b400 = (options >> 10) & 1;
+
+	Rva00391667 rangeFilter( worldPos );
+	Rva0039161C collideFilter( worldPos, &build->getTemplateGeometryInfo(), angle, true );
+
+	Real range;
+	Rva000421C8 *filter;
+	const Rva0033B3D7Data *data = (const Rva0033B3D7Data *)build->rva0033B3D7();
+	if( data )
+	{
+		range = TheWritableGlobalData->m_1220 * 2.0f;
+		rangeFilter.m_range = data->m_range;
+		filter = &rangeFilter;
+	}
+	else
+	{
+		range = build->getTemplateGeometryInfo().getBoundingCircleRadius() + TheWritableGlobalData->m_1220;
+		if( build->isKindOf( KINDOF_189 ) )
+			collideFilter.m_1d = false;
+		filter = &collideFilter;
+	}
+
+	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange( worldPos, range, FROM_BOUNDINGSPHERE_3D, filter, 0 );
+	Object *them;
+	while( (them = iter.next()) != NULL )
+	{
+		if( builderObject && flag )
+		{
+			CellShroudStatus cs = them->getShroudStatusForPlayer( builderObject->getControllingPlayer()->m_playerIndex );
+			if( cs == CELLSHROUD_3 || cs == CELLSHROUD_4 )
+				continue;
+		}
+
+		if( isRemovableForConstruction( them ) == TRUE )
+			continue;
+
+		if( them->isKindOfB( KINDOF_12 ) || them->isKindOfB( KINDOF_INERT ) )
+			continue;
+
+		if( b100 && builderObject && builderObject->isKindOf( KINDOF_120 ) )
+		{
+			Module *m = CastleBehavior::rva000395708( them );
+			if( m )
+			{
+				ObjectID id = m->m_18;
+				if( id == builderObject->getID() )
+					continue;
+			}
+			if( them == builderObject )
+				continue;
+			if( them->isKindOfB( KINDOF_DOZER ) )
+				continue;
+		}
+
+		if( !build->isKindOf( KINDOF_104 ) && build->isKindOf( KINDOF_189 ) && them->isKindOfB( KINDOF_156 ) && them == builderObject )
+			continue;
+
+		if( them->testStatus( OBJECT_STATUS_98 ) )
+			continue;
+
+		if( them->isKindOfB( KINDOF_152 ) )
+			continue;
+
+		if( them->isKindOfB( KINDOF_2 ) )
+		{
+			if( b20 && builderObject && builderObject->getRelationship( them ) != ENEMIES )
+				continue;
+			return FALSE;
+		}
+
+		if( builderObject && builderObject->getRelationship( them ) == ENEMIES && !b200 )
+			return FALSE;
+
+		if( b200 && builderObject && builderObject->getRelationship( them ) == ENEMIES && them->isKindOfB( KINDOF_STRUCTURE ) )
+			return FALSE;
+	}
+
+	if( b400 && builderObject )
+	{
+		Player *owner = builderObject->getControllingPlayer();
+		if( owner )
+		{
+			Rva00394173Member list = ((const Rva00394173Field *)owner)->get();
+			for( Rva00394173Node *node = list.m_head->m_next; node != list.m_head; node = node->m_next )
+			{
+				Object *obj = TheGameLogic->findObjectByID( node->m_id );
+				if( obj && build->getTemplateGeometryInfo().bfmeIntersects( *worldPos, angle, obj->getGeometryInfo(), *obj->getPosition(), obj->getOrientation() ) )
+					return FALSE;
+			}
+		}
+	}
+
+	if( b20 || b40 || b100 )
+		return TRUE;
+
+	Coord3D pt;
+	pt.x = 0.0f;
+	pt.y = 0.0f;
+	pt.z = 0.0f;
+	const ModuleInfo &info = build->getBehaviorModuleInfo();
+	Int count = info.getCount();
+	for( Int i = 0; i < count; ++i )
+	{
+		const ModuleData *md = info.getNthData( i );
+		if( md )
+		{
+			const Rva00394879Exit *exitData = md->rva00394879Exit();
+			if( exitData )
+			{
+				pt = exitData->m_offset;
+				Vector3 dir( pt.x, pt.y, pt.z );
+				Real len2 = dir.X * dir.X + dir.Y * dir.Y + dir.Z * dir.Z;
+				if( len2 != 0.0f )
+				{
+					Real inv = WWMath::Inv_Sqrt( len2 );
+					dir.X *= inv;
+					dir.Y *= inv;
+					dir.Z *= inv;
+				}
+				pt.x += dir.X * 20.0f;
+				pt.y += dir.Y * 20.0f;
+				pt.z += dir.Z * 20.0f;
+				break;
+			}
+			const Rva00394879Door *doorData = md->rva00394879Door();
+			if( doorData )
+			{
+				pt = doorData->m_offset;
+				break;
+			}
+		}
+	}
+
+	if( pt.GetLength() != 0.0f )
+	{
+		Matrix3D tm;
+		tm.Make_Identity();
+		tm.Rotate_Z( angle );
+		Vector3 out( 0.0f, 0.0f, 0.0f );
+		Matrix3D::Transform_Vector( tm, Vector3( pt.x, pt.y, pt.z ), &out );
+		out.X += worldPos->x;
+		out.Y += worldPos->y;
+
+		if( builderObject && builderObject->isKindOf( KINDOF_DOZER )
+				&& !TheAI->pathfinder()->QuickDoesPathExist( builderObject, worldPos, (const Coord3D *)&out, 0 ) )
+			return FALSE;
+
+		Real dy = out.Y - worldPos->y;
+		Coord2D dir;
+		dir.x = out.X - worldPos->x;
+		dir.y = dy;
+		Real len = dir.length();
+		GeometryInfo doorGeom( GEOMETRY_BOX, FALSE, 1.0f, len * 0.5, 0.5f );
+		Real inv = 1.0f / len;
+		Real doorAngle = atan2f( dir.x * inv, dy * inv );
+		Coord3D center;
+		center.x = (out.X + worldPos->x) * 0.5f;
+		center.y = (out.Y + worldPos->y) * 0.5f;
+		center.z = worldPos->z;
+		Real doorRange = build->getTemplateGeometryInfo().getMajorRadius() * 2.0f;
+
+		BfmeWideResult iter2 = ThePartitionManager->iterateObjectsInRange( worldPos, doorRange, FROM_CENTER_3D,
+			Rva0004584D( *(BfmeFixedStorage0004543D *)&Rva00045411BitSet( 0, KINDOF_STRUCTURE ), *(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE )
+				.link( &Rva00261353Filter( builderObject->getControllingPlayer()->m_playerIndex ) ), 0 );
+		while( (them = iter2.next()) != NULL )
+		{
+			if( them->getGeometryInfo().bfmeIntersects( *them->getPosition(), them->getOrientation(), doorGeom, center, doorAngle ) )
+				return FALSE;
+		}
+	}
+
+	return TRUE;
+
+}  // end isLocationClearOfObjects
#endif
