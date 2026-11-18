# tri_compute_normal.cpp: framed `Vector3::Cross_Product` copy (2026-11-18)

Link blocker (322 B): `?Cross_Product@Vector3@@SAXABV1@0PAV1@@Z` differs from the first copy in
link order. The unit builds `/Oy-` for its two rows (Compute_Normal 0x0006A0CA, Normalize
0x0006924F), so the inline helper's out-of-line copy is the 96-byte framed form; 20 other units
emit the 95-byte frameless form. 44a4769d87 retired the `#pragma optimize("y", on)` that used to
parse vector3.h under FPO.

Verified repair, no directive: the unit's shim `reference/shims/bfme_tri_math/vector3.h` takes the
helper `__declspec(dllimport) __forceinline` when the unit defines
`BFME_TRI_MATH_CROSS_PRODUCT_NO_COPY`. Compute_Normal still expands it (retail inlines it) and no
copy is emitted. Measured: build.sh 16/16 over the shim's four users (tri_compute_normal.cpp,
colmathfrustum.cpp, colmathline.cpp, particle_emitter_convert_version.cpp); link_check 4/4,
2,920 -> 3,242 B.

Do not use a declaration-only helper: the call is then not expanded and Compute_Normal fails
(15/16).

Not published: the shim is named `vector3.h`, so `tools/header_dependents.py --staged` counts 2,354
dependents by name, exceeds its 2,000 limit and the pre-commit hook runs the whole-tree gate
(over 22 minutes here without finishing; the pre-push hook repeats it on every attempt). A seat
with that budget can apply the patch below as it stands. Renaming the shim first (it is included
by explicit path from four units) would bound the gate to those four.

```diff
diff --git a/Code/Libraries/Source/WWVegas/WWMath/tri_compute_normal.cpp b/Code/Libraries/Source/WWVegas/WWMath/tri_compute_normal.cpp
index e9e8de12ae..ab8f3e5c41 100644
--- a/Code/Libraries/Source/WWVegas/WWMath/tri_compute_normal.cpp
+++ b/Code/Libraries/Source/WWVegas/WWMath/tri_compute_normal.cpp
@@ -13,10 +13,10 @@ static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
 // this small TU at the retail size-optimized settings and take its address so
 // MSVC emits the COMDAT body for the ledger's unexported collision helper.
 // The TU needs /Oy- for its own rows, but that forces an EBP frame into every
-// out-of-line Vector3 helper it also emits, while the kept copies elsewhere
-// are frameless. Parse vector3.h first with FPO on so those helpers emit the
-// kept frameless form; TriClass::Compute_Normal below is still parsed with the
-// TU flags and keeps its frame.
+// out-of-line Vector3 helper it also emits, while the kept copy of Cross_Product
+// elsewhere is frameless. Compute_Normal expands that helper inline, so it is
+// taken import-inline here: expanded as before, and no framed copy is emitted.
+#define BFME_TRI_MATH_CROSS_PRODUCT_NO_COPY
 #include "../../../../../reference/shims/bfme_tri_math/vector3.h"
 #include "rendobj.h"
 #include "tri.h"
diff --git a/reference/shims/bfme_tri_math/vector3.h b/reference/shims/bfme_tri_math/vector3.h
index d2134aff4f..3eabbdd948 100644
--- a/reference/shims/bfme_tri_math/vector3.h
+++ b/reference/shims/bfme_tri_math/vector3.h
@@ -73,6 +73,16 @@
 #ifndef VECTOR3_H
 #define VECTOR3_H
 
+// A unit built with frame pointers (/Oy-) would emit a framed out-of-line copy of
+// the three-argument Cross_Product beside the frameless one every other unit emits
+// and the link keeps. Such a unit defines BFME_TRI_MATH_CROSS_PRODUCT_NO_COPY: the
+// body is still expanded where it is used, and no copy is emitted.
+#ifdef BFME_TRI_MATH_CROSS_PRODUCT_NO_COPY
+#define BFME_TRI_MATH_CROSS_PRODUCT_INLINE __declspec(dllimport) __forceinline
+#else
+#define BFME_TRI_MATH_CROSS_PRODUCT_INLINE WWINLINE
+#endif
+
 #include "always.h"
 #include "wwmath.h"
 #include <assert.h>
@@ -156,7 +166,7 @@ public:
 #ifdef ALLOW_TEMPORARIES
 	static WWINLINE Vector3 Cross_Product(const Vector3 &a,const Vector3 &b);
 #endif
-	static WWINLINE void Cross_Product(const Vector3 &a,const Vector3 &b,Vector3 * result);
+	static BFME_TRI_MATH_CROSS_PRODUCT_INLINE void Cross_Product(const Vector3 &a,const Vector3 &b,Vector3 * result);
 	static WWINLINE void Normalized_Cross_Product(const Vector3 &a, const Vector3 &b, Vector3 * result);
 	static WWINLINE float Cross_Product_X(const Vector3 &a,const Vector3 &b);
 	static WWINLINE float Cross_Product_Y(const Vector3 &a,const Vector3 &b);
@@ -374,7 +384,7 @@ WWINLINE Vector3 Vector3::Cross_Product(const Vector3 &a,const Vector3 &b)
 }
 #endif
 
-WWINLINE void Vector3::Cross_Product(const Vector3 &a,const Vector3 &b,Vector3 * set_result)
+BFME_TRI_MATH_CROSS_PRODUCT_INLINE void Vector3::Cross_Product(const Vector3 &a,const Vector3 &b,Vector3 * set_result)
 {
 	assert(set_result != &a);
 	set_result->X = (a.Y * b.Z - a.Z * b.Y);
```
