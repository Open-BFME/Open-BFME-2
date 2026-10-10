// ?CheckCorners@BaseHeightMapRenderObjClass@@QAEXHHHHHHPA_N0@Z
// partial score=0.986 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?CheckCorners@BaseHeightMapRenderObjClass@@QAEXHHHHHHPA_N0@Z, retail
// 0x00067494..0x000677CA (822 bytes, RET 0x20). WorldBuilder's debug build
// names it BaseHeightMapRenderObjClass::CheckCorners (BaseHeightMap.cpp:1819,
// ASSERT(heightIn && slopeIn)); retail keeps the asserts out. For the four
// corners of one cell it samples the terrain through the virtual
// getHeightMapHeight (vtable slot 0x244, with the normal out-parameter):
// the truncated height must lie in [heightMin, heightMax] or *heightIn is
// cleared, and the slope angles away from the x and y axes
// (|90 - atan2(nz, nx)| and |90 - atan2(nz, ny)| in degrees) must lie in
// [slopeMin, slopeMax] or *slopeIn is cleared. Both flags start true.

typedef int Int;
typedef float Real;
typedef bool Bool;

extern "C" float __cdecl atan2f(float y, float x);
extern "C" double __cdecl fabs(double x);

struct Coord3D
{
	Real x, y, z;
};

#define RAD_TO_DEG 57.295776f

class BaseHeightMapRenderObjClass
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual void v137();
	virtual void v138();
	virtual void v139();
	virtual void v140();
	virtual void v141();
	virtual void v142();
	virtual void v143();
	virtual void v144();
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;
	void CheckCorners(Int x, Int y, Int heightMax, Int heightMin, Int slopeMax, Int slopeMin, Bool *heightIn, Bool *slopeIn);
};

void BaseHeightMapRenderObjClass::CheckCorners(Int x, Int y, Int heightMax, Int heightMin, Int slopeMax, Int slopeMin, Bool *heightIn, Bool *slopeIn)
{
	*heightIn = true;
	*slopeIn = true;

	Coord3D normal;
	Real py = y * 10.0f;
	Real px = x * 10.0f;
	Int height = (Int)getHeightMapHeight(px, py, &normal);
	if (height < heightMin || height > heightMax)
		*heightIn = false;
	Real slopeX = fabs(90.0f - atan2f(normal.z, normal.x) * RAD_TO_DEG);
	Real slopeY = fabs(90.0f - atan2f(normal.z, normal.y) * RAD_TO_DEG);
	if (slopeMin > slopeX || slopeX > slopeMax || slopeMin > slopeY || slopeY > slopeMax)
		*slopeIn = false;

	x++;
	Real px2 = x * 10.0f;
	height = (Int)getHeightMapHeight(px2, py, &normal);
	if (height < heightMin || height > heightMax)
		*heightIn = false;
	slopeX = fabs(90.0f - atan2f(normal.z, normal.x) * RAD_TO_DEG);
	slopeY = fabs(90.0f - atan2f(normal.z, normal.y) * RAD_TO_DEG);
	if (slopeMin > slopeX || slopeX > slopeMax || slopeMin > slopeY || slopeY > slopeMax)
		*slopeIn = false;

	y++;
	Real py2 = y * 10.0f;
	height = (Int)getHeightMapHeight(px2, py2, &normal);
	if (height < heightMin || height > heightMax)
		*heightIn = false;
	slopeX = fabs(90.0f - atan2f(normal.z, normal.x) * RAD_TO_DEG);
	slopeY = fabs(90.0f - atan2f(normal.z, normal.y) * RAD_TO_DEG);
	if (slopeMin > slopeX || slopeX > slopeMax || slopeMin > slopeY || slopeY > slopeMax)
		*slopeIn = false;

	height = (Int)getHeightMapHeight(px, py2, &normal);
	if (height < heightMin || height > heightMax)
		*heightIn = false;
	slopeX = fabs(90.0f - atan2f(normal.z, normal.x) * RAD_TO_DEG);
	slopeY = fabs(90.0f - atan2f(normal.z, normal.y) * RAD_TO_DEG);
	if (slopeMin > slopeX || slopeX > slopeMax || slopeMin > slopeY || slopeY > slopeMax)
		*slopeIn = false;
}
