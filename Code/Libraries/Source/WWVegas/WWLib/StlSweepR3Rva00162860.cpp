// STLport 4.5.3 captured-bone copy forwarder.
// cl: /O2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <algorithm>

// The element identity is unresolved; this view matches htree.cpp.
struct BfmeCapturedBoneRotation
{
    float X, Y, Z, W; BfmeCapturedBoneRotation &operator=(const BfmeCapturedBoneRotation &q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;}
};

struct BfmeCapturedBoneTranslation
{
    float X, Y, Z;
    BfmeCapturedBoneTranslation() {}
    BfmeCapturedBoneTranslation &operator=(const BfmeCapturedBoneTranslation &v){X=v.X;Y=v.Y;Z=v.Z;return *this;}
    BfmeCapturedBoneTranslation(const BfmeCapturedBoneTranslation &v)
        : X(v.X), Y(v.Y), Z(v.Z) {}
};

struct CapturedTransform{BfmeCapturedBoneRotation Rotation;BfmeCapturedBoneTranslation Translation;};

struct Elem36{int Index;CapturedTransform Transform;bool WorldSpace;};

template Elem36 *_STL::__copy_backward<Elem36 *,Elem36 *,int>(Elem36 *,Elem36 *,Elem36 *,const _STL::random_access_iterator_tag &,int *);

template Elem36 *_STL::__copy_backward_ptrs<Elem36 *, Elem36 *>(Elem36 *, Elem36 *, Elem36 *, const _STL::__false_type &);
