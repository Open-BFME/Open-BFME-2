#pragma once

// Accessed vector prefix shared by this builder's registration and object
// pruning bodies: the real STLport vector. The bodies declare the members
// retail calls out of line as decl-only specializations.
#include <vector>
