#pragma once
// GeneralsMD code includes either <winsock2.h> or <winsock.h>; route both to the
// same full shim so name-resolution / socket helpers are available everywhere.
#include "winsock.h"
