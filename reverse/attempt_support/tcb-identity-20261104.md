# TCB vector identity retirement: constructor-pointer prerequisite

Inspected revision: `84d348bb2988bd746044c83acd00d7e6a9f8cfcc`, 2026-11-04.
Read the prior native-vector repair and LINK-004 before checking this item.

`./build.sh Code/Libraries/Source/WWVegas/WWMath/tcbspline.cpp` passes all
five existing rows (340 bytes). `repair_queue.py retire identity` now reaches
its scan without reporting missing or stale objects, but reports all one key
still found; nothing is retired. `allowed_symbols.py --source` reports the
DynamicVector Resize reference at +0x0c as `wrong/unknown` at 0x000F0BF1.
The kept TCB Resize definition is tcbspline.cpp's sole 227-byte variant.
`pin_consistency.py --symbol` reports its existing pin consistent.

A read-only call to the existing `pin_admission.fold_proof_problems` judge,
proposing `fold-proof=Code/Libraries/Source/WWVegas/WWMath/tcbspline.cpp`
without writing a pin, refuses:

```
+0x4c binds ??0TCBClass@TCBSpline3DClass@@QAE@XZ
where the VectorClass<Vector3>::Resize owner binds ??0Vector3@@QAE@XZ
(DIR32 slots are copied from retail, so equal bytes alone do not prove a fold)
```

The complete proof receipt is empty. The existing body's byte/EH evidence
does not establish this distinct external constructor-pointer identity.
The next prerequisite is reconciling that identity through the normal class
and naming/proof paths, rather than rebuilding missing objects or repeating
the unchanged Resize reconstruction. No source, pin, hatch or baseline changed;
no fresh linking or census gain is claimed. Both RVA claims were released.
