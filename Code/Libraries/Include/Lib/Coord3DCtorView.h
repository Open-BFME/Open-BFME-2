// Coord3D with retail's user-written constructors: opt-in companion to Coord3D.h.
//
// Retail's Coord3D is a class with an empty user default constructor (0x0047A6A9) and a member-wise
// user copy constructor (0x004216D3, three dword moves); coord3d.cpp carries that private view for
// the library bodies. The canonical Coord3D.h stays plain (POD) because the matched rows of ~1,250
// dependents byte-match against it: with these constructors 324 of 5,252 of them stop matching
// (33 units no longer compile: Coord3D union members, `Coord3D p = {x, y, z}`; 37 rows change bytes).
// A unit whose bytes need the non-POD type (by-value Coord3D arguments built through the copy
// constructor, expression temporaries with an ESP save) includes this header INSTEAD of Coord3D.h,
// before anything else that includes it: it takes Coord3D.h's include guard.
// `#define COORD3D_VIEW_EXTERN_CTOR` / `COORD3D_VIEW_EXTERN_DTOR` declare the default constructor (0x0047A6A9) / destructor
// (0x000B3FD0) out of line for units whose bytes call the retail rows instead of inlining them.
// `#define COORD3D_VIEW_INLINE` first makes zero/set/add/sub/scale header-inline as in Zero Hour
// (plus BFME2 MathCoord3D.h's in-place operators, operator/= among them).
// `#define COORD3D_VIEW_INLINE_ONLY` with it declares those members dllimport __forceinline: they inline and emit no copy.
// `#define COORD3D_VIEW_DTOR` first adds retail's empty user destructor (0x000B3FD0), which keeps by-value
// results and arrays on the unwind path (units whose temporaries or arrays retail registers for EH).
#ifndef CANONICAL_COORD3D_H
#define CANONICAL_COORD3D_H

struct Coord3D {
    float x;
    float y;
    float z;
#ifdef COORD3D_VIEW_EXTERN_CTOR
    Coord3D();
#else
    Coord3D() {}
#endif
    Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
    Coord3D(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
#if defined(COORD3D_VIEW_EXTERN_DTOR)
    ~Coord3D();
#elif defined(COORD3D_VIEW_DTOR)
    ~Coord3D() {}
#endif
    float length() const;
    void normalize();
    bool operator==(const Coord3D &r);
    float GetLengthSqrd() const;
    float GetLength() const;
    float GetLengthEstimate2D() const;
    float GetLength2D() const;
    float Normalize();
    float operator*(const struct Coord3DBase &r) const;
#ifdef COORD3D_VIEW_INLINE
#ifdef COORD3D_VIEW_INLINE_ONLY
#define COORD3D_VIEW_INLINE_SPEC __declspec(dllimport) __forceinline
#else
#define COORD3D_VIEW_INLINE_SPEC
#endif
    // Zero Hour's header-inline mutators (as Lib/Coord3DInline.h).
    COORD3D_VIEW_INLINE_SPEC void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
    COORD3D_VIEW_INLINE_SPEC void set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    COORD3D_VIEW_INLINE_SPEC void set(const Coord3D *p) { x = p->x; y = p->y; z = p->z; }
    COORD3D_VIEW_INLINE_SPEC void add(const Coord3D *p) { x += p->x; y += p->y; z += p->z; }
    COORD3D_VIEW_INLINE_SPEC void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
    COORD3D_VIEW_INLINE_SPEC void scale(float s) { x *= s; y *= s; z *= s; }
    COORD3D_VIEW_INLINE_SPEC void scaleInlined(float s) { x *= s; y *= s; z *= s; }
    COORD3D_VIEW_INLINE_SPEC void add(Coord3D a) { x += a.x; y += a.y; z += a.z; }
    COORD3D_VIEW_INLINE_SPEC Coord3D &operator-=(const Coord3D &o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    COORD3D_VIEW_INLINE_SPEC Coord3D &operator+=(const Coord3D &o) { x += o.x; y += o.y; z += o.z; return *this; }
    COORD3D_VIEW_INLINE_SPEC Coord3D &operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    // MathCoord3D.h:569 (WB 0x41FA20, assert "Coord3D::operator`/='"): one reciprocal, three
    // multiplies; BuildAssistant::getPortTransform 0x392802 inlines it.
    COORD3D_VIEW_INLINE_SPEC Coord3D &operator/=(float d) { float inv = 1.0f / d; x *= inv; y *= inv; z *= inv; return *this; }
    COORD3D_VIEW_INLINE_SPEC float lengthSqr() const { return x * x + y * y + z * z; }
#undef COORD3D_VIEW_INLINE_SPEC
#else
    void zero();
    void set(float x, float y, float z);
    void scale(float s);
#endif
    void set(const struct Coord3DBase *p);
    bool equals(const struct Coord3DBase &that) const;
    float GetLengthEstimate() const;
    // Zero Hour's spelling of the same estimate; retail exports both names at 0x00003ACE (ICF fold).
    float lengthEstimate() const;
};

#endif // CANONICAL_COORD3D_H
