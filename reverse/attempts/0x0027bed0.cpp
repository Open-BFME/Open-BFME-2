// ?rva0027BED0@BfmeDrawableDrawTransform@@QAEXPAVMatrix3D@@@Z
// partial score=0.9844484666 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Reference WWMath Matrix3D postMul and assignment; native BED0 proves flag43F and order.
class Vector4{public:float X,Y,Z,W;__forceinline Vector4&operator=(const Vector4&v){X=v.X;Y=v.Y;Z=v.Z;W=v.W;return *this;}};
__forceinline float submul(const Vector4&row,float a,float b,float c){return row.X*a+row.Y*b+row.Z*c;}
__forceinline float submul2(const Vector4&row,const float&a,float b,float c){return row.X*a+row.Y*b+row.Z*c;}
class Matrix3D{public:Vector4 Row[3];__forceinline Matrix3D&operator=(const Matrix3D&m){Row[0]=m.Row[0];Row[1]=m.Row[1];Row[2]=m.Row[2];return *this;}
__forceinline void postMul(const Matrix3D&that){
float tmpX,tmpY,tmpZ,tmpW;
tmpX=submul(Row[0],that.Row[0].X,that.Row[1].X,that.Row[2].X);
tmpY=submul(Row[0],that.Row[0].Y,that.Row[1].Y,that.Row[2].Y);
tmpZ=submul(Row[0],that.Row[0].Z,that.Row[1].Z,that.Row[2].Z);
tmpW=submul(Row[0],that.Row[0].W,that.Row[1].W,that.Row[2].W);
Row[0].X = tmpX;
Row[0].Y = tmpY;
Row[0].Z = tmpZ;
Row[0].W += tmpW;
tmpX=submul(Row[1],that.Row[0].X,that.Row[1].X,that.Row[2].X);
tmpY=submul2(Row[1],that.Row[0].Y,that.Row[1].Y,that.Row[2].Y);
tmpZ=submul(Row[1],that.Row[0].Z,that.Row[1].Z,that.Row[2].Z);
tmpW=submul2(Row[1],that.Row[0].W,that.Row[1].W,that.Row[2].W);
Row[1].X = tmpX;
Row[1].Y = tmpY;
Row[1].Z = tmpZ;
Row[1].W += tmpW;
tmpX=submul(Row[2],that.Row[0].X,that.Row[1].X,that.Row[2].X);
tmpY=submul(Row[2],that.Row[0].Y,that.Row[1].Y,that.Row[2].Y);
tmpZ=submul(Row[2],that.Row[0].Z,that.Row[1].Z,that.Row[2].Z);
tmpW=submul(Row[2],that.Row[0].W,that.Row[1].W,that.Row[2].W);
Row[2].X = tmpX;
Row[2].Y = tmpY;
Row[2].Z = tmpZ;
Row[2].W += tmpW;
}};
class Drawable{public:const Matrix3D*getTransformMatrix()const;};
class Rva00271423{public:Matrix3D*rva00271423();};
class BfmeDrawableDrawTransform{public:void rva0027BED0(Matrix3D*matrix);void applyPhysicsXform(Matrix3D*);char pad[0x43f];bool noTransform;};
void BfmeDrawableDrawTransform::rva0027BED0(Matrix3D*matrix){
 *matrix=*((Drawable*)this)->getTransformMatrix();
 if(!noTransform)matrix->postMul(*((Rva00271423*)this)->rva00271423());
 applyPhysicsXform(matrix);
}
