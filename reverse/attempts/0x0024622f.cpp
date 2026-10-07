// ?rva0024622F@GameLogic@@QAEX_N@Z
// partial score=0.94 date=2026-10-07
// ?rva0024622F@GameLogic@@QAEX_N@Z
// partial score=0.94 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Apply the patch below to Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (git apply after stripping the #if 0 wrapper): TerrainLogic +0xBC slot,
// ThingTemplate +0x5E5 flag, Thing/Object views, MapObject/PlayerList views
// and the bridge pass (BFME 1 startNewGame donor). Compiled 498B vs 499B;
// frame, first loop and calls are exact. Only residue: after the 0x00244D56
// call retail loads created._M_start into edi, iterates from it and frees it
// in the vector dtor without reloading (cross-call CSE of the address-taken
// vector, so edi is saved in the prologue instead of the first loop's region).
// Plain cl 7.1 reloads [ebp-0x34]; /Oa /Ow and loop spellings (iterator,
// pointer copy, empty() guard, do-while, while) do not change it. Same wall as
// 0x002444BE; likely /GL escape analysis.
// Pins needed (placeholder names): _Vector_base<Rva0024622FEntry> ctor
// 0x00211E58, push_back 0x00539A2E, GameLogic::rva00244D56 0x00244D56,
// Object::rva002951AB 0x002951AB.
#if 0
diff --git a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
index b270205782..fd706dbf52 100644
--- a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
+++ b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
@@ -21,6 +21,8 @@
 // stay offset names: only the donor knows their meaning.
 #include <list>
 #include <map>
+#include <set>
+#include <vector>
 #include <math.h>
 #include "ascii_string.h"
 #include "../../../../Libraries/Include/Lib/Coord3D.h"
@@ -123,8 +125,58 @@ public:
 	void rva006C0810(const Region3D *extent, float cellSize);
 };
 
+class Object;
+
+// Primary vtable after Snapshot's slots: getGroundHeight +0x18 (ZH argument
+// list) and +0xBC, which the bridge pass calls for every object it creates.
+// The +0xBC name is carried from the BFME 1 donor (startNewGame's bridge pass
+// calls TerrainLogic::addLandmarkBridgeToLogic there); retail has no symbol.
 class TerrainLogic : public Snapshot, public SubsystemInterface
 {
+public:
+	virtual void t04(void); virtual void t05(void);
+	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
+	virtual void t07(void);
+	virtual void t08(void);
+	virtual void t09(void);
+	virtual void t0a(void);
+	virtual void t0b(void);
+	virtual void t0c(void);
+	virtual void t0d(void);
+	virtual void t0e(void);
+	virtual void t0f(void);
+	virtual void t10(void);
+	virtual void t11(void);
+	virtual void t12(void);
+	virtual void t13(void);
+	virtual void t14(void);
+	virtual void t15(void);
+	virtual void t16(void);
+	virtual void t17(void);
+	virtual void t18(void);
+	virtual void t19(void);
+	virtual void t1a(void);
+	virtual void t1b(void);
+	virtual void t1c(void);
+	virtual void t1d(void);
+	virtual void t1e(void);
+	virtual void t1f(void);
+	virtual void t20(void);
+	virtual void t21(void);
+	virtual void t22(void);
+	virtual void t23(void);
+	virtual void t24(void);
+	virtual void t25(void);
+	virtual void t26(void);
+	virtual void t27(void);
+	virtual void t28(void);
+	virtual void t29(void);
+	virtual void t2a(void);
+	virtual void t2b(void);
+	virtual void t2c(void);
+	virtual void t2d(void);
+	virtual void t2e(void);
+	virtual void addLandmarkBridgeToLogic(Object *bridgeObj);          // +0xBC
 };
 
 class BuffLogic : public Snapshot, public SubsystemInterface
@@ -282,6 +334,20 @@ public:
 class GameInfo;
 class LoadScreen;
 class Object;
+class MapObject;
+
+// One record per object the map loader created: the object and the map
+// object it came from (8 bytes; push_back 0x00539A2E).
+struct Rva0024622FEntry
+{
+	Object *obj;
+	MapObject *mapObj;
+};
+
+enum KindOfType
+{
+	KINDOF_INVALID = -1
+};
 
 class GameLogic : public SubsystemInterface
 {
@@ -298,6 +364,9 @@ public:
 	void rva0023D17D(void);
 	void destroyAllObjectsImmediate(void);
 	void rva00376D49(void);
+	void rva0024622F(bool dontCreate);
+	void rva00244D56(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
+		const KindOfType *requireKind, bool dontCreate);
 	void rva00244CB0(bool loadingSaveGame, GameInfo *game);
 
 	Object *getFirstObject(void) const { return m_objList; }
@@ -960,17 +1029,32 @@ class ThingTemplate
 {
 public:
 	const AsciiString &getName(void) const { return m_name; }
+	// +0x5E5: the flag the bridge pass selects on (donor: isBridge).
+	bool isBridge(void) const { return m_isBridge; }
 
 private:
 	char m_pad00[0x64];
 	AsciiString m_name;
+	char m_pad68[0x5e5 - 0x68];
+	bool m_isBridge;
+};
+
+class Dict;
+
+class Thing
+{
+public:
+	void setOrientation(float angle);
+	void setPosition(const Coord3D *pos);
 };
 
-class Object
+class Object : public Thing
 {
 public:
 	const ThingTemplate *getTemplate(void) const { return m_template; }
 	Object *getNextObject(void) const { return m_next; }
+	void rva002951AB(Dict *properties);
+	void rva00293E64(Dict *properties);
 
 private:
 	void *m_vtbl;
@@ -1017,3 +1101,182 @@ void GameLogic::xferObjectTOC(Xfer *xfer)
 		}
 	}
 }
+
+// ?rva0024622F@GameLogic@@QAEX_N@Z
+// @0x0024622F 499B (ret 4 at 0x0024641F; caller 0x00246E74).
+// Target evidence: the body walks the map object list (0x00A00940) skipping
+// roads and bridges by flag (0x36), template-less objects and templates whose
+// +0x5E5 flag is clear. Each survivor's template is announced to a fresh asset
+// list (notify 0x0033CF34, merge 0x0061F010); unless the flag argument is set
+// it is created through newObject (0x002D0A23) on the neutral player's default
+// team, dropped to the ground (TerrainLogic +0x18), oriented by
+// normalizeAngle (0x00238954), positioned, passed to TerrainLogic +0xBC,
+// recorded with its map object and given the map properties (0x002951AB).
+// The rest of the map objects follow through 0x00244D56 restricted to kind
+// 0x3C, then every recorded object gets 0x00293E64 with its map properties.
+// Donor: BFME 1 GameLogic::startNewGame's bridge pass ("Special case, load
+// any bridge map objects": isBridge, neutral default team, getGroundHeight,
+// normalizeAngle, setOrientation, setPosition, addLandmarkBridgeToLogic,
+// updateObjValuesFromMapProperties). BFME 2 split it into this helper; the
+// helper names stay address names because only the donor names them.
+class Rva0020AA00Target
+{
+public:
+	void notify(int a, int b);
+};
+
+struct Rva001408C0Target;
+typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>,
+	_STL::allocator<Rva001408C0Target *> > Rva001408C0Set;
+
+class AssetList
+{
+public:
+	AssetList() : m_treeLayoutPad(0), m_changed(true) {}
+
+private:
+	Rva001408C0Set m_prototypes;
+	unsigned int m_treeLayoutPad;
+	bool m_changed;
+};
+
+// The second notify argument: the callee picks one of two 0x14-byte asset
+// records at +0x3C4 by its first byte.
+struct AssetLoadMode
+{
+	bool m_alternate;
+	AssetLoadMode() : m_alternate(false) {}
+};
+
+void bfmeMergeReceiverKeys(int value);
+
+class Dict
+{
+};
+
+class MapObject
+{
+public:
+	MapObject *getNext(void) const { return m_next; }
+	const Coord3D *getLocation(void);
+	float getAngle(void) const { return m_angle; }
+	int getFlags(void) const { return m_flags; }
+	Dict *getProperties(void) { return &m_properties; }
+	const ThingTemplate *getThingTemplate(void) const;
+
+private:
+	void *m_vtbl;
+	MapObject *m_next;
+	Coord3D m_location;
+	AsciiString m_objectName;
+	const ThingTemplate *m_thingTemplate;
+	float m_angle;
+	int m_flags;
+	Dict m_properties;
+};
+
+class MapObjectListHolder
+{
+public:
+	MapObject *m_first;
+};
+
+extern MapObjectListHolder *BfmeTheMapObjectListHolder;
+
+struct CreateMask
+{
+	unsigned int m_bits[4];
+};
+
+class Team;
+
+class Player
+{
+public:
+	Team *getDefaultTeam(void) const { return m_defaultTeam; }
+
+private:
+	char m_pad00[0x2ec];
+	Team *m_defaultTeam;
+};
+
+class PlayerList
+{
+public:
+	Player *getNeutralPlayer(void) const { return m_neutralPlayer; }
+
+private:
+	char m_pad00[0x18];
+	Player *m_neutralPlayer;
+};
+
+class ThingFactory
+{
+public:
+	Object *newObject(const ThingTemplate *tt, Team *team, const CreateMask *mask, bool b);
+};
+
+extern ThingFactory *TheThingFactory;
+extern PlayerList *ThePlayerList;
+
+float normalizeAngle(float angle);
+
+void GameLogic::rva0024622F(bool dontCreate)
+{
+	_STL::vector<Rva0024622FEntry> created;
+	for (MapObject *pMapObj = BfmeTheMapObjectListHolder->m_first; pMapObj; pMapObj = pMapObj->getNext()) {
+		Rva0134FAA0->slot28();
+		bfmeReleaseQueuedDeviceInterfaces();
+
+		if (pMapObj->getFlags() & 0x36)
+			continue;
+
+		const ThingTemplate *thingTemplate = pMapObj->getThingTemplate();
+		if (thingTemplate == 0)
+			continue;
+		if (!thingTemplate->isBridge())
+			continue;
+
+		AssetLoadMode mode;
+		AssetList assets;
+		((Rva0020AA00Target *)thingTemplate)->notify((int)&assets, (int)&mode);
+		bfmeMergeReceiverKeys((int)&assets);
+		if (dontCreate)
+			continue;
+
+		Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
+		CreateMask mask;
+		memset(&mask, 0, sizeof(mask));
+		Object *obj = TheThingFactory->newObject(thingTemplate, team, &mask, false);
+		if (obj == 0)
+			continue;
+
+		const Coord3D *loc = pMapObj->getLocation();
+		Coord3D pos;
+		pos.x = loc->x;
+		pos.y = loc->y;
+		pos.z = loc->z;
+		pos.z += TheTerrainLogic->getGroundHeight(pos.x, pos.y);
+		obj->setOrientation(normalizeAngle(pMapObj->getAngle()));
+		obj->setPosition(&pos);
+		if (thingTemplate->isBridge())
+			TheTerrainLogic->addLandmarkBridgeToLogic(obj);
+
+		Rva0024622FEntry entry;
+		entry.obj = obj;
+		entry.mapObj = pMapObj;
+		created.push_back(entry);
+		obj->rva002951AB(pMapObj->getProperties());
+	}
+
+	{
+		KindOfType kind = (KindOfType)0x3c;
+		rva00244D56(&created, 0, &kind, dontCreate);
+	}
+
+	for (Rva0024622FEntry *it = created.begin(); it != created.end(); ++it) {
+		Rva0134FAA0->slot28();
+		bfmeReleaseQueuedDeviceInterfaces();
+		it->obj->rva00293E64(it->mapObj->getProperties());
+	}
+}
#endif
