// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?rva002BF4F3@Rva002BF4F3@@QAE_NPAVRenderObjClass@@PBVVector3@@PAV3@H_N@Z @0x002BF4F3 189B unlock: AABox early-out then down-cast via rowed 0x002BF198; callers 0x002BF5B0 0x002BF935; box getter slot 0x108; float -1.0f via g_00BBB9AC

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

class RenderObjClass
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65();
	virtual const AABoxClass *GetBoundingBox();
};

extern float g_00BBB9AC;

class Rva00DFEF18Host
{
public:
	bool Cast(RenderObjClass *obj, const Vector3 &start, const Vector3 &dir, Vector3 *out, int collisionType, bool checkHidden);
};

class Rva002BF4F3
{
public:
	bool rva002BF4F3(RenderObjClass *obj, const Vector3 *pt, Vector3 *out, int collisionType, bool checkHidden);
};

bool Rva002BF4F3::rva002BF4F3(RenderObjClass *obj, const Vector3 *pt, Vector3 *out, int collisionType, bool checkHidden)
{
	const AABoxClass *box = obj->GetBoundingBox();
	if (box->Center.X - box->Extent.X > pt->X)
		return false;
	if (pt->X > box->Center.X + box->Extent.X)
		return false;
	if (box->Center.Y - box->Extent.Y > pt->Y)
		return false;
	if (pt->Y > box->Center.Y + box->Extent.Y)
		return false;
	Vector3 start;
	Vector3 dir;
	start.X = pt->X;
	start.Y = pt->Y;
	start.Z = box->Center.Z + box->Extent.Z;
	dir.X = 0.0f;
	dir.Y = 0.0f;
	dir.Z = g_00BBB9AC;
	return ((Rva00DFEF18Host *)this)->Cast(obj, start, dir, out, collisionType, checkHidden);
}
