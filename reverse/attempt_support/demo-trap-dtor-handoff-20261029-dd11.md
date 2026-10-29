# Rva0024A797Derived.cpp links once DemoTrapUpdate.cpp declares its destructors

Seat dd-11, 2026-10-29. Served unit
`Code/GameEngine/Source/Common/Rva0024A797Derived.cpp` (0x00253DFD, 1,590 B):
link_check reported `duplicate ??1DemoTrapUpdate@@UAE@XZ`. Base a33c933a9d.
Not landed: `Code/GameEngine/Source/GameLogic/Object/Update/DemoTrapUpdate.cpp`
was held by `yasinschroeder-claudeb2` (3 h left) when this seat tried to claim it,
so the patch below is handed off instead of committed.

## Cause

`DemoTrapUpdate.cpp` has its own single-inheritance view
(`class DemoTrapUpdate : public UpdateModule`) with real members and 10 matched
rows. Its implicit destructor is emitted as a COMDAT with the same name as
retail's 25-byte opaque multiple-inheritance destructor at 0x00495916, whose row
is owned by Rva0024A797Derived.cpp (`class DemoTrapUpdate : public UpdateModule,
public MiBase1, public Rva00495916_B2`). The two bodies differ, so the link can
pick the wrong one; the census flags the served unit `duplicate`.

## Patch (verified in the dd-11 sandbox)

In `Code/GameEngine/Source/GameLogic/Object/Update/DemoTrapUpdate.cpp`:

```cpp
 class UpdateModule : public ObjectModule,
 	public BehaviorInterface, public UpdateInterface
 {
 public:
 	UpdateModule(Thing *thing, const ModuleData *moduleData);
+	// Declared so this view emits no implicit base destructor when the derived
+	// destructor below is declared; retail's copy is rowed elsewhere.
+	virtual ~UpdateModule();
 	virtual void behaviorAnchor();
@@
 class DemoTrapUpdate : public UpdateModule
 {
 public:
 	DemoTrapUpdate(Thing *thing, const ModuleData *moduleData);
+	// Retail's 25-byte opaque multiple-inheritance dtor at 0x00495916 is rowed in
+	// Rva0024A797Derived.cpp; this single-inheritance view must not emit a second copy.
+	virtual ~DemoTrapUpdate();
 	virtual void objectModuleAnchor();
```

Declaring only the derived destructor is not enough: that alone makes the view
emit a non-retail `??1UpdateModule@@UAE@XZ` COMDAT, which turns
DemoTrapUpdate.cpp itself into a non-linking unit (`comdat ... not retail's
body`). Declaring the base destructor too suppresses both.

## Evidence (sandbox, census index 2026-10-29 15:08 at 85f6b7f40c)

Before, with the committed sources:

- `DemoTrapUpdate.cpp`: does not link — `comdat ??1DemoTrapUpdate@@UAE@XZ
  (retail: not retail's body)`.
- `Rva0024A797Derived.cpp`: does not link — `duplicate
  ??1DemoTrapUpdate@@UAE@XZ`.
- link_check: 0 of 2 link cleanly.

After the patch:

- `DemoTrapUpdate.cpp`: LINKS 0 -> 680 B, `./build.sh` 10/10 rows exact,
  1 literal, 0 float/import findings.
- `Rva0024A797Derived.cpp`: LINKS 0 -> 1,590 B.
- link_check: 2 of 2 link cleanly, 0 -> 2,270 B.

The served unit's own source is unchanged; only the other view's destructor
declarations differ, and no row or ledger line moves.
