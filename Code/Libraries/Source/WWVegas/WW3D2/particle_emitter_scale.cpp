// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// ?Scale@ParticleEmitterClass@@UAEXM@Z @ 0x001A18D0 152B
// ParticleEmitterClass Scale slot 92 vtable 0x7D69F8; Buffer Scale via +0x170.
// Stash scored 0.99 with +0x168 via bfmerendobj shim; bfme2renderobj adds the
// two retail slots shifting Scale to +0x170. Evidence: rep movsd shape with
// PosRand/VelRand/Buffer Scale calls, neighbours part_emt/frame.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "rendobj.h"
#include "part_emt.h"
#include "wwdebug.h"
#include "ww3d.h"
#include "assetmgr.h"
#include "part_ldr.h"
#include "w3derr.h"
#include "scene.h"
#include "texture.h"
#include "wwprofile.h"
#include <limits.h>
#include "gcd_lcm.h"

void ParticleEmitterClass::Scale(float scale)
{
	// Scale all velosity and position parameters
	if (PosRand) PosRand->Scale(scale);
	BaseVel *= scale;
	if (VelRand) VelRand->Scale(scale);
	OutwardVel *= scale;

	// Scale sizes of all particles
	// Retail calls Buffer Scale via vtable slot 92 (+0x170, vtable 0x7D69F8);
	// the shims place it at +0x168/+0x16c, so call the proven slot via a
	// TU-local vtable view (member pointer, no bodies emitted).
	struct Scale92Buffer
	{
		virtual ~Scale92Buffer();
		virtual void _v01(); virtual void _v02(); virtual void _v03(); virtual void _v04();
		virtual void _v05(); virtual void _v06(); virtual void _v07(); virtual void _v08();
		virtual void _v09(); virtual void _v10(); virtual void _v11(); virtual void _v12();
		virtual void _v13(); virtual void _v14(); virtual void _v15(); virtual void _v16();
		virtual void _v17(); virtual void _v18(); virtual void _v19(); virtual void _v20();
		virtual void _v21(); virtual void _v22(); virtual void _v23(); virtual void _v24();
		virtual void _v25(); virtual void _v26(); virtual void _v27(); virtual void _v28();
		virtual void _v29(); virtual void _v30(); virtual void _v31(); virtual void _v32();
		virtual void _v33(); virtual void _v34(); virtual void _v35(); virtual void _v36();
		virtual void _v37(); virtual void _v38(); virtual void _v39(); virtual void _v40();
		virtual void _v41(); virtual void _v42(); virtual void _v43(); virtual void _v44();
		virtual void _v45(); virtual void _v46(); virtual void _v47(); virtual void _v48();
		virtual void _v49(); virtual void _v50(); virtual void _v51(); virtual void _v52();
		virtual void _v53(); virtual void _v54(); virtual void _v55(); virtual void _v56();
		virtual void _v57(); virtual void _v58(); virtual void _v59(); virtual void _v60();
		virtual void _v61(); virtual void _v62(); virtual void _v63(); virtual void _v64();
		virtual void _v65(); virtual void _v66(); virtual void _v67(); virtual void _v68();
		virtual void _v69(); virtual void _v70(); virtual void _v71(); virtual void _v72();
		virtual void _v73(); virtual void _v74(); virtual void _v75(); virtual void _v76();
		virtual void _v77(); virtual void _v78(); virtual void _v79(); virtual void _v80();
		virtual void _v81(); virtual void _v82(); virtual void _v83(); virtual void _v84();
		virtual void _v85(); virtual void _v86(); virtual void _v87(); virtual void _v88();
		virtual void _v89(); virtual void _v90(); virtual void _v91();
		virtual void Scale(float s);
	};
	((Scale92Buffer *)Buffer)->Scale(scale);
}
