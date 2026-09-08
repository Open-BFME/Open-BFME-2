// cl: /O2 /EHsc /MD /DNDEBUG
// BFME2 Control_Bone uses sorted 36-byte captured-bone records at this+1C/20.
// Each record stores index, quaternion, translation, and world-space flag.
// Original capture-record type name is unknown. The preceding tree fields
// are opaque here; only the independently decoded capture-buffer layout is used.
// Complete112-byte RET12 boundary; the sole call is held Build_Quaternion360.
class Quaternion { public: float X,Y,Z,W; Quaternion &operator=(const Quaternion &q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;} };
class Vector3 { public: float X,Y,Z; Vector3(const Vector3 &v):X(v.X),Y(v.Y),Z(v.Z){} Vector3 &operator=(const Vector3 &v){X=v.X;Y=v.Y;Z=v.Z;return *this;} Vector3(float x,float y,float z):X(x),Y(y),Z(z){} };
class Matrix3D { public: float M[3][4]; void Get_Translation(Vector3 *v) const {v->X=M[0][3];v->Y=M[1][3];v->Z=M[2][3];} };
Quaternion Build_Quaternion(const Matrix3D &);
class PivotClass;
class HTreeClass {
 struct CapturedBone {int Index;Quaternion Rotation;Vector3 Translation;bool WorldSpaceTranslation;};
 char TreeFields[28];
 CapturedBone *Begin,*End,*Capacity;
public: void Control_Bone(int,const Matrix3D &,bool);
};
void HTreeClass::Control_Bone(int boneindex,const Matrix3D &relative_tm,bool world_space_translation)
{
 CapturedBone *bone=Begin;
 while(bone!=End && bone->Index<boneindex) ++bone;
 if(bone==End || bone->Index!=boneindex) return;
 bone->WorldSpaceTranslation=world_space_translation;
 bone->Rotation=Build_Quaternion(relative_tm);
 relative_tm.Get_Translation(&bone->Translation);
}
