// cl: /O2 /arch:SSE /EHsc /DNDEBUG /MD
// Descriptive BFME2 name; original retail function name is unrecovered.
// RVA 0x00717550: shortest-path normalized quaternion interpolation,
// called by encoding-0 channel evaluation at 0x001B3313. The retail dot
// product sums X then Z then Y then W; preserve that floating-point order.
// Complete 377-byte boundary ends at RET 0x00B176C8 before alignment.
class WWMath { public: static    float __fastcall Inv_Sqrt(float); };
class Quaternion { public:    float X, Y, Z, W; };
void BFME2_Nlerp(Quaternion &res,const Quaternion &p,const Quaternion &q,float alpha)
{
    float dot=p.X*q.X+p.Z*q.Z+p.Y*q.Y+p.W*q.W;
    float beta=1.0f-alpha;
    if (dot<0.0f) {
    res.X=beta*p.X-alpha*q.X;
    res.Y=beta*p.Y-alpha*q.Y;
    res.Z=beta*p.Z-alpha*q.Z;
    res.W=beta*p.W-alpha*q.W;
    } else {
    res.X=beta*p.X+alpha*q.X;
    res.Y=beta*p.Y+alpha*q.Y;
    res.Z=beta*p.Z+alpha*q.Z;
    res.W=beta*p.W+alpha*q.W;
    }
    float length=res.X*res.X+res.Y*res.Y+res.Z*res.Z+res.W*res.W;
    if (0.0f!=length) {
    float scale=WWMath::Inv_Sqrt(length);
    res.X *= scale;
    res.Y *= scale;
    res.Z *= scale;
    res.W *= scale;
    }
}
