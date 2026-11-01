// Shared header context for the LineGroup translation unit.
// Retail's out-of-line header bodies use size optimization; method bodies
// retain the translation unit's O2/SSE/G7 profile. These two controls moved
// from LineGroupClassRender.cpp without increasing their total count.
#ifndef BFME_LINEGRP_HEADERS_H
#define BFME_LINEGRP_HEADERS_H
#pragma optimize("s", on)
#include "../../../../../reference/shims/bfme_vector3_full_link/vector3_full_link.h"
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
#include "sharebuf.h"
#include "linegrp_class.h"
#include "texture.h"
#include "vertmaterial.h"
#include <d3d8.h>
#include "always.h"
#include "wwdebug.h"
#include "refcount.h"
#include "dx8fvf.h"
#pragma optimize("", on)
#endif
