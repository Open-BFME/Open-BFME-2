// ?rva0024622F@GameLogic@@QAEX_N@Z
// partial score=0.95 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Apply the patch below to Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (git apply after stripping the #if 0 wrapper; base 704bf0a3e3). It adds the
// TerrainLogic +0x18/+0xBC slots, ThingTemplate +0x5E5, Thing/Object/MapObject
// accessors and the bridge pass. Compiled 498B vs 499B; everything but the
// created-vector register residue is exact.
// Residue, now explained: retail keeps created._M_start in edi after the
// 0x00244D56 call and frees it without reloading, which MSVC 7.1 does only
// when the vector has not escaped. &created reaches GameLogic::rva00244D56,
// and that body is in retail's own TU (GameLogic.cpp), so retail saw it does
// nothing but push_back. Here it is only declared, so the call escapes the
// vector. Measured with scratch .cod probes: a visible non-capturing callee
// removes the reload, and an external one restores it. So this body lands
// after 0x00244D56 lands in GameLogicInit.cpp (banked partial 0.90).
// Pins needed: push_back<Rva0024622FEntry> 0x00539A2E,
// Object::rva002951AB 0x002951AB.
#if 0
diff --git a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
index d9b100017d..5b13beae6e 100644
--- a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
+++ b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
@@ -150,8 +150,50 @@ public:
 	virtual bool loadMap(const AsciiString &filename, Rva00240000 *stream, bool query,
 		bool newGame);                                                   // +0x10
 	virtual void newMap(bool loadingSaveGame);                           // +0x14
-	virtual void t06(void); virtual void t07(void);
+	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const; // +0x18
+	virtual void t07(void);
 	virtual void getExtent(Region3D *extent) const;                      // +0x20
+	virtual void t09(void);
+	virtual void t0A(void);
+	virtual void t0B(void);
+	virtual void t0C(void);
+	virtual void t0D(void);
+	virtual void t0E(void);
+	virtual void t0F(void);
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
+	virtual void t1A(void);
+	virtual void t1B(void);
+	virtual void t1C(void);
+	virtual void t1D(void);
+	virtual void t1E(void);
+	virtual void t1F(void);
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
+	virtual void t2A(void);
+	virtual void t2B(void);
+	virtual void t2C(void);
+	virtual void t2D(void);
+	virtual void t2E(void);
+	// +0xBC: the bridge pass calls it for every bridge it creates; the
+	// name is carried from the BFME 1 donor (addLandmarkBridgeToLogic).
+	virtual void addLandmarkBridgeToLogic(Object *bridgeObj);            // +0xBC
 	void rva002817F2(const AsciiString &filename);
 	void rva00283642(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
 	void rva00280176(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
@@ -1232,6 +1274,8 @@ class ThingTemplate
 {
 public:
 	const AsciiString &getName(void) const { return m_name; }
+	// +0x5E5: the flag the bridge pass selects on (donor: isBridge).
+	bool isBridge(void) const { return m_isBridge; }
 	__forceinline bool isKindOf(KindOfType t) const
 	{
 		unsigned int mask = 1u << (t & 31);
@@ -1243,6 +1287,8 @@ private:
 	AsciiString m_name;
 	char m_pad68[0x10c - 0x68];
 	unsigned int m_kindof[4];
+	char m_pad11C[0x5e5 - 0x11c];
+	bool m_isBridge;                                                     // +0x5E5
 };
 
 class Dict;
@@ -1253,6 +1299,8 @@ class Thing
 {
 public:
 	Drawable *getDrawable(void) const;
+	void setOrientation(float angle);
+	void setPosition(const Coord3D *pos);
 };
 
 class Object : public Thing
@@ -1260,6 +1308,7 @@ class Object : public Thing
 public:
 	const ThingTemplate *getTemplate(void) const { return m_template; }
 	Object *getNextObject(void) const { return m_next; }
+	void rva002951AB(Dict *properties);
 	void rva00293E64(Dict *properties);
 
 private:
@@ -1366,6 +1415,8 @@ class MapObject
 public:
 	MapObject *getNext(void) const { return m_next; }
 	const Coord3D *getLocation(void);
+	float getAngle(void) const { return m_angle; }
+	int getFlags(void) const { return m_flags; }
 	Dict *getProperties(void) { return &m_properties; }
 	const ThingTemplate *getThingTemplate(void) const;
 
@@ -1495,6 +1546,83 @@ public:
 // Binds the kind to a temporary for the loader's pointer argument.
 static __forceinline const KindOfType *kindRef(const KindOfType &kind) { return &kind; }
 
+float normalizeAngle(float angle);
+
+// ?rva0024622F@GameLogic@@QAEX_N@Z
+// @0x0024622F 499B (ret 4 at 0x0024641F; caller 0x00246E74).
+// Target evidence: the body walks the map object list skipping flagged
+// objects (0x36), template-less objects and templates whose +0x5E5 flag is
+// clear. Each survivor's template is announced to a fresh asset list
+// (notify 0x0033CF34, merge 0x0061F010); unless the flag argument is set it
+// is created through 0x002D0A23 on the neutral player's default team,
+// dropped to the ground (TerrainLogic +0x18), oriented by normalizeAngle,
+// positioned, passed to TerrainLogic +0xBC, recorded with its map object
+// and given the map properties (0x002951AB). The rest of the map objects
+// follow through 0x00244D56 restricted to kind 0x3C, then every recorded
+// object gets 0x00293E64 with its map properties. Donor: BFME 1
+// GameLogic::startNewGame's bridge pass ("Special case, load any bridge map
+// objects": isBridge, neutral default team, getGroundHeight, normalizeAngle,
+// setOrientation, setPosition, addLandmarkBridgeToLogic). BFME 2 split it
+// into this helper; the helper names stay address names.
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
+		Object *obj = TheThingFactory->rva002D0A23(thingTemplate, team, mask, (ObjectID)0);
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
+
 void GameLogic::rva00246422(bool dontCreate)
 {
 	_STL::vector<Rva0024622FEntry> created;
#endif
