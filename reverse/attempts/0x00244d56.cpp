// ?rva00244D56@GameLogic@@QAEXPAV?$vector@URva0024622FEntry@@V?$allocator@URva0024622FEntry@@@_STL@@@_STL@@PBW4KindOfType@@1_N@Z
// partial score=0.91 date=2026-10-07
// ?rva00244D56@GameLogic@@QAEXPAV?$vector@URva0024622FEntry@@V?$allocator@URva0024622FEntry@@@_STL@@@_STL@@PBW4KindOfType@@1_N@Z
// partial score=0.91 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Patch against Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp at
// 2ad71f6faf (git apply after stripping the #if 0 wrapper). Adds the
// TerrainLogic / AIData / ThingTemplate / Object / MapObject / Matrix3D /
// Team / Drawable views and the body ported onto the current file (the
// Rva0024622FEntry vector, Rva00148F5ECache keys, CreateMask, AssetLoadMode).
// @0x00244D56 2052B; compiled 2014B. Masked of frame offsets and relocations,
// the only residue is register allocation:
//  - retail spills pMapObj to ebp-0x14 for the create path and keeps the
//    properties Dict in edi (add edi,0x24); ours keeps pMapObj in edi and
//    rematerialises lea [edi+0x24]. The spill gives retail its pre-tested
//    loop (cmp/je/jmp + reload at top) and the 4 extra frame bytes.
//  - Rotate_Z: retail holds s in xmm0 and tmp1 in xmm1 (movaps xmm3,xmm0);
//    ours multiplies s from memory.
// Tried with no change to the spill (all compile identical): props as a
// loop-top / function-scope / per-branch variable or inline
// pMapObj->getProperties() at each use, pMapObj and thingTemplate declared
// at function scope (donor style), if (obj) {...} instead of continue,
// inverted prop/create branch order. Rotate_Z: cosf/sinf, c*tmp2 - s*tmp1,
// a WWMath Vector4 Row[] with operator[] (worse), inline vs __forceinline
// (inline is not expanded under /O1).
// Fixed this session: getDefaultTeam() == team operand order (cmp [eax+0x2ec],ebx).
// Pins needed: 0x6AA1C _Rb_tree::clear (AssetList set), 0x23B383, 0x27D3D9,
// 0x2951AB, 0x2A851D, push_back<Rva0024622FEntry> 0x539A2E.
// 0x24622F (bridge pass, stash 0x0024622f.cpp) needs this body in the TU.
#if 0
diff --git a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
index d9b100017d..1e22b73670 100644
--- a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
+++ b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
@@ -142,6 +142,12 @@ class Object;
 class ThingTemplate;
 class Matrix3D;
 
+enum PathfindLayerEnum
+{
+	LAYER_INVALID = 0,
+	LAYER_GROUND = 1
+};
+
 class Rva00240000;
 
 class TerrainLogic : public Snapshot, public SubsystemInterface
@@ -150,11 +156,17 @@ public:
 	virtual bool loadMap(const AsciiString &filename, Rva00240000 *stream, bool query,
 		bool newGame);                                                   // +0x10
 	virtual void newMap(bool loadingSaveGame);                           // +0x14
-	virtual void t06(void); virtual void t07(void);
+	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const; // +0x18
+	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
+		Coord3D *normal = 0, bool clip = true) const;                    // +0x1C
 	virtual void getExtent(Region3D *extent) const;                      // +0x20
 	void rva002817F2(const AsciiString &filename);
+	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
+	// Placement helpers taking (template, position, matrix, scale): trees
+	// (kind 62), kind 63 and the remaining props.
 	void rva00283642(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
 	void rva00280176(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
+	void rva0027D3D9(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
 };
 
 class BuffLogic : public Snapshot, public SubsystemInterface
@@ -174,16 +186,32 @@ class Pathfinder
 {
 public:
 	void rva002E8DAA(void);
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
 };
 
 class AI : public SubsystemInterface
 {
 public:
 	Pathfinder *pathfinder(void) { return m_pathfinder; }
+	const AIData *getAiData(void) const { return m_aiData; }
 
 private:
 	int m_0c;
 	Pathfinder *m_pathfinder;                                            // +0x10
+	char m_pad14[0x18 - 0x14];
+	AIData *m_aiData;                                                    // +0x18
 };
 
 class AssetList;
@@ -345,6 +373,8 @@ class Dict
 public:
 	Dict(int numPairs = 0);
 	~Dict() { releaseData(); }
+	bool getBool(int key, bool *exists = 0) const;
+	float getReal(int key, bool *exists = 0) const;
 	AsciiString getAsciiString(int key, bool *exists = 0) const;
 	void setInt(int key, int value);
 	void setBool(int key, bool value);
@@ -1232,6 +1262,7 @@ class ThingTemplate
 {
 public:
 	const AsciiString &getName(void) const { return m_name; }
+	int rva000456AC(int bit) const;
 	__forceinline bool isKindOf(KindOfType t) const
 	{
 		unsigned int mask = 1u << (t & 31);
@@ -1241,8 +1272,22 @@ public:
 private:
 	char m_pad00[0x64];
 	AsciiString m_name;
-	char m_pad68[0x10c - 0x68];
-	unsigned int m_kindof[4];
+	char m_pad68[0x108 - 0x68];
+
+public:
+	unsigned int m_108;                                                  // +0x108
+	unsigned int m_kindof[4];                                            // +0x10C
+	unsigned int m_11c;
+	unsigned int m_120;                                                  // +0x120
+	char m_pad124[0x4a0 - 0x124];
+	float m_fenceWidth;                                                  // +0x4A0
+	char m_pad4A4[0x4e0 - 0x4a4];
+	float m_4e0;                                                         // +0x4E0
+	char m_pad4E4[0x5e5 - 0x4e4];
+	bool m_5e5;                                                          // +0x5E5
+	char m_pad5E6[0x5eb - 0x5e6];
+	bool m_5eb;
+	bool m_5ec;
 };
 
 class Dict;
@@ -1253,6 +1298,9 @@ class Thing
 {
 public:
 	Drawable *getDrawable(void) const;
+	void setTransformMatrix(const Matrix3D *mtx);
+	void setOrientation(float angle);
+	void setPosition(const Coord3D *pos);
 };
 
 class Object : public Thing
@@ -1260,6 +1308,8 @@ class Object : public Thing
 public:
 	const ThingTemplate *getTemplate(void) const { return m_template; }
 	Object *getNextObject(void) const { return m_next; }
+	void rva002951AB(Dict *properties);
+	void rva0028B4CE(PathfindLayerEnum layer);
 	void rva00293E64(Dict *properties);
 
 private:
@@ -1343,6 +1393,7 @@ class AssetList
 {
 public:
 	AssetList() : m_treeLayoutPad(0), m_changed(true) {}
+	void clear(void) { m_prototypes.clear(); m_changed = true; }
 
 private:
 	Rva001408C0Set m_prototypes;
@@ -1366,6 +1417,8 @@ class MapObject
 public:
 	MapObject *getNext(void) const { return m_next; }
 	const Coord3D *getLocation(void);
+	float getAngle(void) const { return m_angle; }
+	int getFlags(void) const { return m_flags; }
 	Dict *getProperties(void) { return &m_properties; }
 	const ThingTemplate *getThingTemplate(void) const;
 
@@ -1450,6 +1503,7 @@ public:
 	Player *getNthPlayer(int index);
 	Player *findPlayerWithNameKey(NameKeyType key);
 	void setLocalPlayer(Player *player);
+	Team *rva002A851D(AsciiString owner, MapObject *mapObj);
 
 private:
 	char m_pad0C[0x10 - 0x0c];
@@ -1471,6 +1525,7 @@ extern PlayerList *ThePlayerList;
 class Matrix3D
 {
 public:
+	Matrix3D(void) {}
 	explicit Matrix3D(bool init)
 	{
 		if (init) {
@@ -1480,6 +1535,28 @@ public:
 		}
 	}
 
+	// WWMath Matrix3D::Rotate_Z.
+	__forceinline void Rotate_Z(float theta)
+	{
+		float tmp1, tmp2;
+		float c, s;
+
+		c = (float)cos(theta);
+		s = (float)sin(theta);
+
+		tmp1 = m_row[0][0]; tmp2 = m_row[0][1];
+		m_row[0][0] = (float)(c * tmp1 + s * tmp2);
+		m_row[0][1] = (float)(-s * tmp1 + c * tmp2);
+
+		tmp1 = m_row[1][0]; tmp2 = m_row[1][1];
+		m_row[1][0] = (float)(c * tmp1 + s * tmp2);
+		m_row[1][1] = (float)(-s * tmp1 + c * tmp2);
+
+		tmp1 = m_row[2][0]; tmp2 = m_row[2][1];
+		m_row[2][0] = (float)(c * tmp1 + s * tmp2);
+		m_row[2][1] = (float)(-s * tmp1 + c * tmp2);
+	}
+
 private:
 	float m_row[3][4];
 };
@@ -1723,10 +1800,13 @@ class GameLODManager
 {
 public:
 	int getStaticLODLevel(void) const { return m_staticLODLevel; }
+	int get1774(void) const { return m_1774; }
 
 private:
 	char m_pad0000[0x1768];
 	int m_staticLODLevel;
+	char m_pad176C[0x1774 - 0x176c];
+	int m_1774;                                                          // +0x1774
 };
 
 
@@ -2456,10 +2536,13 @@ class Drawable
 public:
 	void rva00278C6B(void);
 	Drawable *getNextDrawable(void) const { return m_next; }
+	void setDrawableStatus(unsigned int bits) { m_status |= bits; }
 
 private:
 	char m_pad000[0x104];
 	Drawable *m_next;                                                    // +0x104
+	char m_pad108[0x114 - 0x108];
+	unsigned int m_status;                                               // +0x114
 };
 
 class ClientFrameSubsystem
@@ -2475,6 +2558,7 @@ public:
 	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
 	virtual void v20(); virtual void v21(); virtual void v22();
 	virtual Drawable *getDrawableList(void);                             // +0x8C
+	void rva0023B383(Dict *properties, const ThingTemplate *tt, const Coord3D *pos);
 };
 
 enum GameSpyBuddyStatus
@@ -3559,3 +3643,251 @@ void populateRandomSideAndColor(GameInfo *game)
 		}
 	}
 }
+
+// ---------------------------------------------------------------------------
+// ?rva00244D56@GameLogic@@QAEXPAV?$vector@URva0024622FEntry@@V?$allocator@URva0024622FEntry@@@_STL@@@_STL@@PBW4KindOfType@@1_N@Z
+// @0x00244D56 2052B (ret 0x10 at 0x00245557; next body 0x0024555A).
+// Target evidence: callers 0x002463CE, 0x00246561 and 0x0024657E pass a
+// vector, two optional kind pointers (0x3C) and a no-create flag. The body
+// reads three tree template names from TheAI's data (+0xDC..+0xE4) through
+// findTemplate (0x002D06CA), swaps them for their final overrides unless the
+// game is multiplayer or mode 2, then walks the map object list: flagged
+// objects (0x36), bridges (+0x5E5) and unwanted kinds (0x000456AC on the
+// +0x108 bits) are skipped, the position is dropped to the ground
+// (TerrainLogic +0x18) and the angle normalized. Props, fluff (a kind bit
+// with a zero fence width), unnamed objects and the two tree kinds go to the
+// TerrainLogic placement helpers or 0x0023B383 on TheGameClient with a
+// Matrix3D built from alignToTerrain or Rotate_Z; everything else is created
+// through 0x002D0A23 on the team validated from originalOwner (0x002A851D),
+// positioned, given its map properties (0x002951AB) and layer, activated
+// and appended to the vector. Every 20 templates the asset list is merged
+// (0x0061F010) and cleared.
+// Donor: BFME 1 GameLogic::startNewGame's map object loop (getGroundHeight,
+// normalizeAngle, the prop/fluff split, validateTeam, setOrientation,
+// setPosition, updateObjValuesFromMapProperties, getLayerForDestination,
+// setActive, addObjectToPathfindMap). BFME 2 moved it into this helper; the
+// helper names stay address names because only the donor names them.
+// ---------------------------------------------------------------------------
+extern "C" int (__cdecl * const _imp__strncmp)(const char *s1, const char *s2, unsigned int count);
+
+class Rva0028CBFD
+{
+public:
+	void rva0028CBFD(void);
+};
+
+class Rva0033A68A
+{
+public:
+	Overridable *rva0033A68A(void);
+};
+
+static __forceinline const ThingTemplate *finalOverride(const ThingTemplate *tt)
+{
+	return (const ThingTemplate *)((Rva0033A68A *)tt)->rva0033A68A();
+}
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
+	bool m_active;                                                       // +0x5D
+	bool m_created;                                                      // +0x5E
+};
+
+extern Rva00148F5ECache TheKey_objectName;
+extern Rva00148F5ECache TheKey_objectPrototypeScale;
+extern Rva00148F5ECache TheKey_alignToTerrain;
+extern Rva00148F5ECache TheKey_originalOwner;
+
+float normalizeAngle(float angle);
+void alignToTerrain(float angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);
+
+void GameLogic::rva00244D56(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
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
+		if (TheAI->getAiData()->m_d8 && TheGameLODManager->get1774() <= 0 && treeA) {
+			useOverrides = true;
+			treeA = finalOverride(treeA);
+			treeB = finalOverride(treeB);
+			treeC = finalOverride(treeC);
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
+		if (excludeKind && (char)thingTemplate->rva000456AC(*excludeKind))
+			continue;
+		if (requireKind && !(char)thingTemplate->rva000456AC(*requireKind))
+			continue;
+		if ((thingTemplate->m_108 & 0x40) && !useTrees)
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
+		bool isProp = (thingTemplate->m_kindof[2] >> 4) & 1;
+		if ((thingTemplate->m_kindof[0] & 0x80000) && thingTemplate->m_fenceWidth == 0.0f)
+			isProp = true;
+
+		bool unnamed = false;
+		if (thingTemplate->m_120 & 1) {
+			bool exists;
+			AsciiString name = pMapObj->getProperties()->getAsciiString(TheKey_objectName.get(), &exists);
+			if (!exists || name.isEmpty())
+				unnamed = true;
+		}
+
+		if (!isProp && !unnamed && !(thingTemplate->m_kindof[1] & 0xc0000000)) {
+			Dict *props = pMapObj->getProperties();
+			AsciiString originalOwner = props->getAsciiString(TheKey_originalOwner.get());
+			Team *team = ThePlayerList->rva002A851D(originalOwner, pMapObj);
+			if (ThePlayerList->getNeutralPlayer()->getDefaultTeam() == team
+				&& _imp__strncmp("Player_", originalOwner.str(), 7) == 0
+				&& !(thingTemplate->m_120 & 0x20000))
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
+			Object *obj = TheThingFactory->rva002D0A23(thingTemplate, team, mask, (ObjectID)0);
+			if (obj == 0)
+				continue;
+
+			if ((pMapObj->getFlags() & 1) || (obj->getTemplate()->m_108 & 0x20)) {
+				Drawable *draw = obj->getDrawable();
+				if (draw)
+					draw->setDrawableStatus(1);
+			}
+
+			bool align;
+			if (props->getBool(TheKey_alignToTerrain.get(), &align) && align) {
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
+			Rva0024622FEntry entry;
+			entry.obj = obj;
+			entry.mapObj = pMapObj;
+			created->push_back(entry);
+		} else {
+			Dict *props = pMapObj->getProperties();
+			bool hasScale;
+			float scale = props->getReal(TheKey_objectPrototypeScale.get(), &hasScale);
+			Matrix3D mtx(true);
+			bool align;
+			if (props->getBool(TheKey_alignToTerrain.get(), &align) && align) {
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
+			if (thingTemplate->m_kindof[1] & 0x40000000) {
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
+			} else if (thingTemplate->m_kindof[1] & 0x80000000) {
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
