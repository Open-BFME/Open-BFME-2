// Target facts: CameraClass holds two ViewportClass values (Viewport, ViewPlane; see CameraClass.h); Zero Hour WW3D2/camera.h supplies Min/Max.
// Not registered yet.
#pragma once

#ifndef BFME2_WW3D2_VIEWPORT_CLASS_H
#define BFME2_WW3D2_VIEWPORT_CLASS_H

#include "rendobj.h"

class ViewportClass
{
public:
    Vector2 Min;
    Vector2 Max;
};

#endif
