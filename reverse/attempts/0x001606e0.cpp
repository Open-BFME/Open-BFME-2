// ?Simple_Evaluate_Pivot@HTreeClass@@QBE_NHABVMatrix3D@@PAV2@@Z
// partial score=0.16370106761565836 date=2026-09-08
// cl: /G7 /arch:SSE /EHsc- /MD /DNDEBUG
// Root corrected rotation scale to current pivot BaseW: retail5607CE/7E1/7FA.
// This is an unverified partial reconstruction; no byte or semantic-completion claim.
struct Vector3 { float X,Y,Z; };
class Matrix3D { public: float M[3][4]; float *operator[](int i){return M[i];} const float *operator[](int i)const{return M[i];} void Make_Identity(){M[0][0]=1.0f;M[0][1]=0.0f;M[0][2]=0.0f;M[0][3]=0.0f;M[1][0]=0.0f;M[1][1]=1.0f;M[1][2]=0.0f;M[1][3]=0.0f;M[2][0]=0.0f;M[2][1]=0.0f;M[2][2]=1.0f;M[2][3]=0.0f;} void Set_Translation(const Vector3 &v){M[0][3]=v.X;M[1][3]=v.Y;M[2][3]=v.Z;} static void Multiply(const Matrix3D &,const Matrix3D &,Matrix3D *); };
struct PivotClass { char Name[16]; PivotClass *Parent; float BaseX,BaseY,BaseZ,BaseW; Vector3 BaseTranslation; unsigned char Opaque[28]; int Index; unsigned char Tail[8]; };
class HTreeClass { char Name[16];int NumPivots;PivotClass *Pivot;float ScaleFactor;unsigned int Owned[3],Unknown28,Unknown2c,Unknown30; public: bool Simple_Evaluate_Pivot(int,const Matrix3D &,Matrix3D *) const; };
typedef char p[(sizeof(PivotClass)==88)?1:-1]; typedef char h[(sizeof(HTreeClass)==52)?1:-1];
bool HTreeClass::Simple_Evaluate_Pivot(int pivot_index,const Matrix3D &obj_tm,Matrix3D *end_tm) const
{
    if (end_tm==0) return false;
    end_tm->Make_Identity();
    if (pivot_index<0 || pivot_index>=NumPivots) return false;
    float qx=0.0f,qy=0.0f,qz=0.0f,qw=1.0f;
    float tx=0.0f,ty=0.0f,tz=0.0f;
    for (PivotClass *pivot=&Pivot[pivot_index];pivot!=0 && pivot->Parent!=0;pivot=pivot->Parent) {
        float x = pivot->BaseW*tx + (pivot->BaseY*tz - ty*pivot->BaseZ);
        float y = pivot->BaseW*ty - (pivot->BaseX*tz - tx*pivot->BaseZ);
        float z = pivot->BaseW*tz + (pivot->BaseX*ty - tx*pivot->BaseY);
        float w = -(pivot->BaseX*tx + pivot->BaseY*ty + pivot->BaseZ*tz);
        float rtx = w*(-pivot->BaseX) + pivot->BaseW*x + (y*(-pivot->BaseZ) - (-pivot->BaseY)*z);
        float rty = w*(-pivot->BaseY) + pivot->BaseW*y - (x*(-pivot->BaseZ) - (-pivot->BaseX)*z);
        float rtz = w*(-pivot->BaseZ) + pivot->BaseW*z + (x*(-pivot->BaseY) - (-pivot->BaseX)*y);
        tx = rtx + pivot->BaseTranslation.X;
        ty = rty + pivot->BaseTranslation.Y;
        tz = rtz + pivot->BaseTranslation.Z;
        float nx = pivot->BaseW*qx + qw*pivot->BaseX + (pivot->BaseY*qz - qy*pivot->BaseZ);
        float ny = pivot->BaseW*qy + qw*pivot->BaseY - (pivot->BaseX*qz - qx*pivot->BaseZ);
        float nz = pivot->BaseW*qz + qw*pivot->BaseZ + (pivot->BaseX*qy - qx*pivot->BaseY);
        float nw = pivot->BaseW*qw - (pivot->BaseX*qx + pivot->BaseY*qy + pivot->BaseZ*qz);
        qx=nx; qy=ny; qz=nz; qw=nw;
    }
    float xx=qx*qx*2.0f, yy=qy*qy*2.0f, zz=qz*qz*2.0f;
    float xy=qx*qy*2.0f, xz=qx*qz*2.0f, xw=qx*qw*2.0f;
    float yz=qy*qz*2.0f, yw=qy*qw*2.0f, zw=qz*qw*2.0f;
    end_tm->M[0][0]=1.0f-yy-zz; end_tm->M[0][1]=xy-zw; end_tm->M[0][2]=xz+yw;
    end_tm->M[1][0]=xy+zw; end_tm->M[1][1]=1.0f-zz-xx; end_tm->M[1][2]=yz-xw;
    end_tm->M[2][0]=xz-yw; end_tm->M[2][1]=yz+xw; end_tm->M[2][2]=1.0f-yy-xx;
    end_tm->M[0][3]=tx; end_tm->M[1][3]=ty; end_tm->M[2][3]=tz;
    Matrix3D::Multiply(obj_tm,*end_tm,end_tm);
    return true;
}
