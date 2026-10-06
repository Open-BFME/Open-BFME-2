// cl: /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// WWMath::Fast_Sin (0x000933AD) and WWMath::Float_To_Int_Floor (0x000930E0): retail holds one
// size-optimised (/O1) out-of-line copy of each header body.
// The pointer constants and anchors below only make this TU emit the inline bodies out of line; they are not retail code or data.
//
#include "quat.h"
#include "matrix3d.h"
#include "matrix4.h"
#include "wwmath.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define SLERP_EPSILON		0.001

extern float (*const g_bfmeFastSinAnchor)(float);
float (*const g_bfmeFastSinAnchor)(float) = &WWMath::Fast_Sin;
extern int (*const g_bfmeFloatToIntFloorAnchor)(const float &);
int (*const g_bfmeFloatToIntFloorAnchor)(const float &) = &WWMath::Float_To_Int_Floor;
