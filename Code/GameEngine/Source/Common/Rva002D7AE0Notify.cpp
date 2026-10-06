// cl: /O1 /DNDEBUG /MD /Oy-
//
// ?rva002D7AE0@@YAXHHH@Z @0x002D7AE0 56B and ?rva002D7B18@@YAXHHH@Z
// @0x002D7B18 56B: twin notification posts (cdecl, 3 int args, void).
// Each forwards (a, b, c) to a virtual on TheDisplay (slots 0x130 / 0x13c,
// null-guarded) then to TheRadar slot 0x24 / 0x2c (null-guarded).
// Display/Radar views use the numbered-placeholder idiom for slot
// resolution; /Oy- keeps the ebp frame retail has with no locals.
// Exact identities unproven, honest address-derived names.
class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75();
	virtual void v76(int a, int b, int c);
	virtual void v77();
	virtual void v78();
	virtual void v79(int a, int b, int c);
};
extern Display *TheDisplay;

class Radar
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s09();
	virtual void s10(int a, int b, int c);
	virtual void s11();
	virtual void s12(int a, int b, int c);
};
extern Radar *TheRadar;

// ?rva002D7AE0@@YAXHHH@Z
void __cdecl rva002D7AE0(int a, int b, int c)
{
	if (TheDisplay != 0)
		TheDisplay->v76(a, b, c);
	if (TheRadar != 0)
		TheRadar->s10(a, b, c);
}

// ?rva002D7B18@@YAXHHH@Z
void __cdecl rva002D7B18(int a, int b, int c)
{
	if (TheDisplay != 0)
		TheDisplay->v79(a, b, c);
	if (TheRadar != 0)
		TheRadar->s12(a, b, c);
}
