// Vector4 template bodies for the StreakLine member containers.
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// Definitions use the shared WWLib simplevec.h template.

// Retail EH map has null states 1 and 3 for Vector3/Vector4 array
// construction within the inlined vector constructors. Their real empty
// default constructors retain these states; treating either type as POD
// removes a state even though the zero-length vector emits no allocation.
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

// Array deallocation is nonthrowing; preserve the retail unwind lifetimes.
void operator delete[](void *) throw();

#include "simplevec.h"

#include "../WWMath/Vector4Data.h"

// Emit only the owned Vector4 template bodies.
template bool SimpleVecClass<Vector4>::Resize(int);
template SimpleDynVecClass<Vector4>::~SimpleDynVecClass();
template bool SimpleDynVecClass<Vector4>::Resize(int);
