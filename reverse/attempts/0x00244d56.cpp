// ?rva00244D56@GameLogic@@QAEXPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PBW4KindOfType@@1_N@Z
// partial score=0.9 date=2026-10-07
// ?rva00244D56@GameLogic@@QAEXPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PBW4KindOfType@@1_N@Z
// partial score=0.90 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Apply the patch below to Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (git apply after stripping the #if 0 wrapper). It adds the TerrainLogic /
// AIData / ThingTemplate / Object / MapObject / Matrix3D views and the body.
// @0x00244D56 2052B; compiled 2013B. 545 of 587 instructions align once frame
// offsets are masked. Remaining residue (register allocation):
//  - retail spills the map object pointer to ebp-0x14 in the create path and
//    keeps the properties Dict in edi (add edi,0x24); ours keeps pMapObj in
//    edi and rematerialises lea [edi+0x24]. That spill also gives retail its
//    pre-test loop (cmp/je/jmp body + reload at top) and the 4 extra frame bytes.
//  - Rotate_Z: retail holds s in xmm0 and tmp1 in xmm1 (movaps xmm3,xmm0);
//    ours multiplies from memory. Writing (-s) explicitly enregisters -s (addss).
//  - strncmp must be the import call [0x00BBA55C]; the dllimport declaration
//    placed before the includes still compiles to a direct call under /D_CRTIMP=.
//  - Frame slot order differs (treeB/treeC, angle/s, originalOwner).
// Levers found: copy pos field by field (struct copy uses movsd and wrecks
// esi/edi); AssetLoadMode aggregate puts the notify mode at ebp-0x9c/-0x98;
// __forceinline Rotate_Z. Loop shape (for/do-while/outer decl), props as one
// variable or per-path, cosf/sinf, const props: no effect.
// Pins needed: 0x6AA1C _Rb_tree::clear, 0x456AC ThingTemplate::isKindOf,
// 0x23B383, 0x27D3D9, 0x280176, 0x283642, 0x2951AB, 0x2A851D.
#if 0
diff --git a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
index b270205782..767a5ec646 100644
--- a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
+++ b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
@@ -19,8 +19,12 @@
 // setup and the ghost manager, an out-of-line player-leave reset
 // (0x0023D17D through TheGameLogic) and moved field offsets. Field names
 // stay offset names: only the donor knows their meaning.
+// strncmp stays an import call under /D_CRTIMP= (retail 0x00245041).
+extern "C" __declspec(dllimport) int __cdecl strncmp(const char *, const char *, unsigned int);
 #include <list>
 #include <map>
+#include <set>
+#include <vector>
 #include <math.h>
 #include "ascii_string.h"
 #include "../../../../Libraries/Include/Lib/Coord3D.h"
@@ -123,8 +127,30 @@ public:
 	void rva006C0810(const Region3D *extent, float cellSize);
 };
 
+enum PathfindLayerEnum
+{
+	LAYER_INVALID = 0,
+	LAYER_GROUND = 1
+};
+
+class Object;
+class ThingTemplate;
+class Matrix3D;
+
+// Primary vtable after Snapshot's four slots: getGroundHeight +0x18 and
+// getLayerHeight +0x1C (ZH argument lists). The non-virtual members are the
+// retail placement helpers 0x00283642, 0x00280176 and 0x0027D3D9, each taking
+// (template, position, matrix, scale); only getLayerForDestination is named.
 class TerrainLogic : public Snapshot, public SubsystemInterface
 {
+public:
+	virtual void t04(void); virtual void t05(void);
+	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
+	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer, Coord3D *normal = 0, bool clip = true) const;
+	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
+	void rva00283642(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
+	void rva00280176(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
+	void rva0027D3D9(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
 };
 
 class BuffLogic : public Snapshot, public SubsystemInterface
@@ -139,8 +165,35 @@ public:
 	virtual void reset(void);                                            // +0x10
 };
 
+class Pathfinder
+{
+public:
+	void AddObjectToPathfindMap(Object *obj);
+};
+
+// AIData (TheAI+0x18): +0xD8 tree-override enable, +0xDC/+0xE0/+0xE4 the
+// three tree template names, +0xE8 their scale, +0xEC the no-trees option.
+class AIData
+{
+	char m_pad00[0xd8];
+public:
+	bool m_d8;
+	AsciiString m_treeName[3];
+	float m_treeScale;
+	bool m_ec;
+};
+
 class AI : public SubsystemInterface
 {
+public:
+	Pathfinder *pathfinder(void) const { return m_pathfinder; }
+	const AIData *getAiData(void) const { return m_aiData; }
+
+private:
+	char m_pad0C[0x10 - 0x0c];
+	Pathfinder *m_pathfinder;
+	char m_pad14[0x18 - 0x14];
+	AIData *m_aiData;
 };
 
 class ScriptEngine : public SubsystemInterface
@@ -282,6 +335,19 @@ public:
 class GameInfo;
 class LoadScreen;
 class Object;
+class MapObject;
+
+// The 8-byte record the map-object placement pass appends per created object.
+struct BfmeE8
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
@@ -304,6 +370,8 @@ public:
 	ObjectTOCEntry *findTOCEntryByName(AsciiString name);
 	void addTOCEntry(AsciiString name, unsigned short id);
 	void xferObjectTOC(Xfer *xfer);
+	void rva00244D56(_STL::vector<BfmeE8> *created, const KindOfType *excludeKind,
+		const KindOfType *requireKind, bool dontCreate);
 
 private:
 	LoadScreen *getLoadScreen(bool saveGame);
@@ -338,7 +406,8 @@ public:
 	char m_pad0B0[0xb4 - 0xb0];
 	char m_b4[0x10c - 0xb4];
 	int m_10c;
-	char m_pad110[0x11d - 0x110];
+	int m_110;
+	char m_pad114[0x11d - 0x114];
 	bool m_11d;
 	char m_pad11E[0x120 - 0x11e];
 	LoadScreen *m_120;
@@ -956,21 +1025,58 @@ protected:
 	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
 };
 
+class Rva0033A68A
+{
+public:
+	Overridable *rva0033A68A(void);
+};
+
+// Kind-of bits live at +0x108 (isKindOf 0x000456AC tests them there); the
+// placement pass tests fixed bits inline. +0x4A0 is the ZH fence width.
 class ThingTemplate
 {
 public:
 	const AsciiString &getName(void) const { return m_name; }
+	bool isKindOf(KindOfType kind) const;
+	const ThingTemplate *getFinalOverride(void) const { return (const ThingTemplate *)((Rva0033A68A *)this)->rva0033A68A(); }
 
 private:
 	char m_pad00[0x64];
 	AsciiString m_name;
+	char m_pad68[0x108 - 0x68];
+
+public:
+	unsigned int m_kindof[7];
+	char m_pad124[0x4a0 - 0x124];
+	float m_fenceWidth;
+	char m_pad4A4[0x4e0 - 0x4a4];
+	float m_4e0;
+	char m_pad4E4[0x5e5 - 0x4e4];
+	bool m_5e5;
+	char m_pad5E6[0x5eb - 0x5e6];
+	bool m_5eb;
+	bool m_5ec;
+};
+
+class Dict;
+class Drawable;
+
+class Thing
+{
+public:
+	void setTransformMatrix(const Matrix3D *mtx);
+	void setOrientation(float angle);
+	void setPosition(const Coord3D *pos);
 };
 
-class Object
+class Object : public Thing
 {
 public:
 	const ThingTemplate *getTemplate(void) const { return m_template; }
 	Object *getNextObject(void) const { return m_next; }
+	Drawable *getDrawable(void) const;
+	void rva002951AB(Dict *properties);
+	void rva0028B4CE(PathfindLayerEnum layer);
 
 private:
 	void *m_vtbl;
@@ -1017,3 +1123,422 @@ void GameLogic::xferObjectTOC(Xfer *xfer)
 		}
 	}
 }
+
+// ?rva00244D56@GameLogic@@QAEXPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@PBW4KindOfType@@1_N@Z
+// @0x00244D56 2052B (ret 0x10 at 0x00245557; next body 0x0024555A).
+// Target evidence: callers 0x002463CE, 0x00246561 and 0x0024657E pass a
+// vector, two optional kind-of pointers (0x3C) and a no-create flag. The body
+// reads three tree template names from TheAI's data (+0xDC..+0xE4) through
+// findTemplate (0x002D06CA), swaps them for their final overrides unless the
+// game is multiplayer or mode 2, then walks the map object list
+// (0x00A00940): roads and bridges (flags 0x36) and unwanted kinds are
+// skipped, the position is dropped to the ground (TerrainLogic slot +0x18) and
+// the angle normalized (0x00238954). Props, fluff (kind bit at +0x10E with a
+// zero fence width), unnamed objects and the two tree kinds go to the
+// TerrainLogic placement helpers or 0x0023B383 on TheGameClient with a
+// Matrix3D built from alignToTerrain (0x0027CEDE) or Rotate_Z; everything else
+// is created through newObject (0x002D0A23) on the team validated from
+// originalOwner (0x002A851D), positioned, given its map properties
+// (0x002951AB) and layer, activated and appended to the vector. Every 20
+// templates the asset list is merged (0x0061F010) and cleared.
+// Donor: BFME 1 GameLogic::startNewGame's map object loop (getGroundHeight,
+// normalizeAngle, the prop/fluff split, validateTeam, setOrientation,
+// setPosition, updateObjValuesFromMapProperties, getLayerForDestination,
+// setActive, addObjectToPathfindMap). BFME 2 moved it into this helper; the
+// helper names stay address names because only the donor names them.
+class Rva0020AA00Target
+{
+public:
+	void notify(int a, int b);
+};
+
+class Rva0028CBFD
+{
+public:
+	void rva0028CBFD(void);
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
+	void clear(void) { m_prototypes.clear(); m_changed = true; }
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
+enum NameKeyType
+{
+	NAMEKEY_INVALID = 0
+};
+
+class StaticNameKey
+{
+public:
+	NameKeyType key(void) const;
+};
+
+extern const StaticNameKey TheKey_objectName;
+extern const StaticNameKey TheKey_objectPrototypeScale;
+extern const StaticNameKey TheKey_alignToTerrain;
+extern const StaticNameKey TheKey_originalOwner;
+
+class Dict
+{
+public:
+	bool getBool(int key, bool *exists = 0) const;
+	float getReal(int key, bool *exists = 0) const;
+	AsciiString getAsciiString(int key, bool *exists = 0) const;
+};
+
+class Matrix3D
+{
+public:
+	Matrix3D(void) {}
+	explicit Matrix3D(bool init) { if (init) Make_Identity(); }
+
+	void Make_Identity(void)
+	{
+		Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
+		Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
+		Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
+	}
+
+	__forceinline void Rotate_Z(float theta)
+	{
+		float tmp1, tmp2;
+		float c, s;
+
+		c = (float)cos(theta);
+		s = (float)sin(theta);
+
+		tmp1 = Row[0][0]; tmp2 = Row[0][1];
+		Row[0][0] = (float)(c * tmp1 + s * tmp2);
+		Row[0][1] = (float)(-s * tmp1 + c * tmp2);
+
+		tmp1 = Row[1][0]; tmp2 = Row[1][1];
+		Row[1][0] = (float)(c * tmp1 + s * tmp2);
+		Row[1][1] = (float)(-s * tmp1 + c * tmp2);
+
+		tmp1 = Row[2][0]; tmp2 = Row[2][1];
+		Row[2][0] = (float)(c * tmp1 + s * tmp2);
+		Row[2][1] = (float)(-s * tmp1 + c * tmp2);
+	}
+
+	float Row[3][4];
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
+class Team
+{
+public:
+	void setActive(void)
+	{
+		if (!m_active) {
+			m_created = true;
+			m_active = true;
+		}
+	}
+
+private:
+	char m_pad00[0x5d];
+	bool m_active;
+	bool m_created;
+};
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
+	Team *rva002A851D(AsciiString owner, MapObject *mapObj);
+
+private:
+	char m_pad00[0x18];
+	Player *m_neutralPlayer;
+};
+
+class ThingFactory
+{
+public:
+	const ThingTemplate *findTemplate(const AsciiString &name);
+	Object *newObject(const ThingTemplate *tt, Team *team, const CreateMask *mask, bool b);
+};
+
+class RecorderClass
+{
+public:
+	bool isMultiplayer(void);
+};
+
+class GameLODManager
+{
+	char m_pad00[0x1774];
+public:
+	int m_1774;
+};
+
+class GameClient
+{
+public:
+	void rva0023B383(Dict *properties, const ThingTemplate *tt, const Coord3D *pos);
+};
+
+class Drawable
+{
+public:
+	void setDrawableStatus(unsigned int bits) { m_status |= bits; }
+
+private:
+	char m_pad00[0x114];
+	unsigned int m_status;
+};
+
+extern ThingFactory *TheThingFactory;
+extern RecorderClass *TheRecorder;
+extern GameLODManager *TheGameLODManager;
+extern PlayerList *ThePlayerList;
+extern GameClient *TheGameClient;
+
+float normalizeAngle(float angle);
+void alignToTerrain(float angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);
+
+void GameLogic::rva00244D56(_STL::vector<BfmeE8> *created, const KindOfType *excludeKind,
+	const KindOfType *requireKind, bool dontCreate)
+{
+	bool useTrees = true;
+	const ThingTemplate *treeA = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[0]);
+	const ThingTemplate *treeB = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[1]);
+	if (treeB == 0)
+		treeA = 0;
+	const ThingTemplate *treeC = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[2]);
+	if (treeC == 0)
+		treeA = 0;
+
+	bool useOverrides = false;
+	bool multiplayer = TheRecorder->isMultiplayer();
+	if (TheGameLogic->m_110 == 2)
+		multiplayer = false;
+	if (!multiplayer) {
+		if (TheAI->getAiData()->m_d8 && TheGameLODManager->m_1774 <= 0 && treeA) {
+			useOverrides = true;
+			treeA = treeA->getFinalOverride();
+			treeB = treeB->getFinalOverride();
+			treeC = treeC->getFinalOverride();
+		}
+		useTrees = !TheAI->getAiData()->m_ec;
+	}
+
+	AssetList assets;
+	int count = 0;
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
+		if (thingTemplate->m_5e5)
+			continue;
+		if (excludeKind && thingTemplate->isKindOf(*excludeKind))
+			continue;
+		if (requireKind && !thingTemplate->isKindOf(*requireKind))
+			continue;
+		if ((thingTemplate->m_kindof[0] & 0x40) && !useTrees)
+			continue;
+
+		const Coord3D *loc = pMapObj->getLocation();
+		Coord3D pos;
+		pos.x = loc->x;
+		pos.y = loc->y;
+		pos.z = loc->z;
+		pos.z += TheTerrainLogic->getGroundHeight(pos.x, pos.y);
+		float angle = normalizeAngle(pMapObj->getAngle());
+
+		bool isProp = (thingTemplate->m_kindof[3] >> 4) & 1;
+		if ((thingTemplate->m_kindof[1] & 0x80000) && thingTemplate->m_fenceWidth == 0.0f)
+			isProp = true;
+
+		bool unnamed = false;
+		if (thingTemplate->m_kindof[6] & 1) {
+			bool exists;
+			AsciiString name = pMapObj->getProperties()->getAsciiString(TheKey_objectName.key(), &exists);
+			if (!exists || name.isEmpty())
+				unnamed = true;
+		}
+
+		if (!isProp && !unnamed && !(thingTemplate->m_kindof[2] & 0xc0000000)) {
+			Dict *props = pMapObj->getProperties();
+			AsciiString originalOwner = props->getAsciiString(TheKey_originalOwner.key());
+			Team *team = ThePlayerList->rva002A851D(originalOwner, pMapObj);
+			if (team == ThePlayerList->getNeutralPlayer()->getDefaultTeam()
+				&& strncmp("Player_", originalOwner.str(), 7) == 0
+				&& !(thingTemplate->m_kindof[6] & 0x20000))
+				continue;
+
+			AssetLoadMode mode;
+			((Rva0020AA00Target *)thingTemplate)->notify((int)&assets, (int)&mode);
+			if (++count == 20) {
+				count = 0;
+				bfmeMergeReceiverKeys((int)&assets);
+				assets.clear();
+			}
+			if (dontCreate)
+				continue;
+
+			CreateMask mask;
+			memset(&mask, 0, sizeof(mask));
+			Object *obj = TheThingFactory->newObject(thingTemplate, team, &mask, false);
+			if (obj == 0)
+				continue;
+
+			if ((pMapObj->getFlags() & 1) || (obj->getTemplate()->m_kindof[0] & 0x20)) {
+				Drawable *draw = obj->getDrawable();
+				if (draw)
+					draw->setDrawableStatus(1);
+			}
+
+			bool align;
+			if (props->getBool(TheKey_alignToTerrain.key(), &align) && align) {
+				Coord3D zero;
+				zero.x = 0.0f;
+				zero.y = 0.0f;
+				zero.z = 0.0f;
+				Coord3D normal;
+				TheTerrainLogic->getLayerHeight(pos.x, pos.y, LAYER_GROUND, &normal, true);
+				Matrix3D mtx;
+				alignToTerrain(angle, zero, normal, mtx);
+				obj->setTransformMatrix(&mtx);
+			} else {
+				obj->setOrientation(angle);
+			}
+			obj->setPosition(&pos);
+			obj->rva002951AB(props);
+			obj->rva0028B4CE(TheTerrainLogic->getLayerForDestination(obj, &pos));
+			Rva0134FAA0->slot28();
+			bfmeReleaseQueuedDeviceInterfaces();
+			((Rva0028CBFD *)obj)->rva0028CBFD();
+			team->setActive();
+			TheAI->pathfinder()->AddObjectToPathfindMap(obj);
+
+			BfmeE8 entry;
+			entry.obj = obj;
+			entry.mapObj = pMapObj;
+			created->push_back(entry);
+		} else {
+			Dict *props = pMapObj->getProperties();
+			bool hasScale;
+			float scale = props->getReal(TheKey_objectPrototypeScale.key(), &hasScale);
+			Matrix3D mtx(true);
+			bool align;
+			if (props->getBool(TheKey_alignToTerrain.key(), &align) && align) {
+				Coord3D normal;
+				TheTerrainLogic->getLayerHeight(pos.x, pos.y, LAYER_GROUND, &normal, true);
+				Coord3D zero;
+				zero.x = 0.0f;
+				zero.y = 0.0f;
+				zero.z = 0.0f;
+				alignToTerrain(angle, zero, normal, mtx);
+			} else {
+				mtx.Rotate_Z(pMapObj->getAngle());
+			}
+
+			float propScale = thingTemplate->m_4e0;
+			if (hasScale)
+				propScale *= scale;
+
+			AssetLoadMode mode;
+			((Rva0020AA00Target *)thingTemplate)->notify((int)&assets, (int)&mode);
+			if (++count == 20) {
+				count = 0;
+				bfmeMergeReceiverKeys((int)&assets);
+				assets.clear();
+			}
+			if (dontCreate)
+				continue;
+
+			if (thingTemplate->m_kindof[2] & 0x40000000) {
+				if (treeA && useOverrides) {
+					if (thingTemplate->m_5eb && thingTemplate->m_5ec)
+						thingTemplate = treeA;
+					else if (!thingTemplate->m_5eb && thingTemplate->m_5ec)
+						thingTemplate = treeB;
+					else
+						thingTemplate = treeC;
+					propScale = TheAI->getAiData()->m_treeScale;
+				}
+				if (useTrees)
+					TheTerrainLogic->rva00283642(thingTemplate, &pos, &mtx, propScale);
+			} else if (thingTemplate->m_kindof[2] & 0x80000000) {
+				TheTerrainLogic->rva00280176(thingTemplate, &pos, &mtx, propScale);
+			} else if (unnamed) {
+				TheGameClient->rva0023B383(props, thingTemplate, &pos);
+			} else {
+				TheTerrainLogic->rva0027D3D9(thingTemplate, &pos, &mtx, propScale);
+			}
+		}
+	}
+	bfmeMergeReceiverKeys((int)&assets);
+}
#endif
