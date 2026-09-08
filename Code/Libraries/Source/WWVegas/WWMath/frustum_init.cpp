// cl: /Ireference/shims/bfmefrustum /Ireference/shims/bfmerendobj /G7 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep


#include "../../../../../reference/shims/bfmecamera/frustum.h"


void FrustumClass::Init
( 
	const Matrix3D &		camera,
	const Vector2 &		vpmin,
	const Vector2 &		vpmax,
	float						znear,
	float						zfar,
	bool ortho
)
{
	int i;
	
	// Store the camera transform
	CameraTransform = camera;

   // Forward is negative Z in our viewspace coordinate system.
	// Just flip the sign if the user passed in positive values.
   if ((znear > 0.0f) && (zfar > 0.0f)) {
		znear = -znear;
		zfar = -zfar;
	}

	// Calculate the corners of the camera frustum.
	// Generate the camera-space frustum corners by linearly
   // extrapolating the viewplane to the near and far z clipping planes.

	// The camera frustum corners are defined in the following order:
	// When looking at the frustum from the position of the camera, the near four corners are
	// numbered: upper left 0, upper right 1, lower left 2, lower right 3. The far plane's
	// Frustum corners are numbered from 4 to 7 in an analogous fashion.
  // (remember: the camera space has x going to the right, y up and z backwards).

	//calculate a proper z-vector assuming our right-handed coordinate system
	Vector3	zv;
	Vector3::Cross_Product(CameraTransform.Get_X_Vector(),CameraTransform.Get_Y_Vector(),&zv);

	//compare correct z-vector with the one in the camera matrix.  If they point in
	//opposite directions, we have a reflected camera matrix.
	if (Vector3::Dot_Product(CameraTransform.Get_Z_Vector(),zv) < 0)
	{	//flip the frustum corners horizontally for a reflected matrix
	  Corners[1].Set(vpmin.X, vpmax.Y, 1.0);
	  Corners[5] = Corners[1];
		Corners[0].Set(vpmax.X, vpmax.Y, 1.0);
		Corners[4] = Corners[0];
		Corners[3].Set(vpmin.X, vpmin.Y, 1.0);
		Corners[7] = Corners[3];
		Corners[2].Set(vpmax.X, vpmin.Y, 1.0);
		Corners[6] = Corners[2];
	}
	else
	{	//normal camera
		Corners[0].Set(vpmin.X, vpmax.Y, 1.0);
		Corners[4] = Corners[0];
		Corners[1].Set(vpmax.X, vpmax.Y, 1.0);
		Corners[5] = Corners[1];
		Corners[2].Set(vpmin.X, vpmin.Y, 1.0);
		Corners[6] = Corners[2];
		Corners[3].Set(vpmax.X, vpmin.Y, 1.0);
		Corners[7] = Corners[3];
	}


	if (ortho) {
		Corners[0].Z = znear;
		Corners[1].Z = znear;
		Corners[2].Z = znear;
		Corners[3].Z = znear;
		Corners[4].Z = zfar;
		Corners[5].Z = zfar;
		Corners[6].Z = zfar;
		Corners[7].Z = zfar;
	} else {
		Corners[0] *= znear;
		Corners[1] *= znear;
		Corners[2] *= znear;
		Corners[3] *= znear;
		Corners[4] *= zfar;
		Corners[5] *= zfar;
		Corners[6] *= zfar;
		Corners[7] *= zfar;
	}

	// Transform the eight corners of the view frustum from camera space to world space.
	for (i = 0; i < 8; i++) {
		Matrix3D::Transform_Vector(CameraTransform, Corners[i], &(Corners[i]));
	}

	// Create the six frustum bounding planes from the eight corner Corners.
	// The bounding planes are oriented so that their normals point outward
	PlaneClass frustum_planes[6];
	Planes[0].Set(Corners[0], Corners[3], Corners[1]);	// near
	Planes[1].Set(Corners[0], Corners[5], Corners[4]);	// bottom
	Planes[2].Set(Corners[0], Corners[6], Corners[2]); // right
	Planes[3].Set(Corners[2], Corners[7], Corners[3]); // top
	Planes[4].Set(Corners[1], Corners[7], Corners[5]); // left
	Planes[5].Set(Corners[4], Corners[7], Corners[6]); // far

	// find the bounding box of the entire frustum (may be used for sloppy quick rejection)
	BoundMin = BoundMax = Corners[0];

	for (i=1; i<8;i++) {
		if (Corners[i].X < BoundMin.X) BoundMin.X = Corners[i].X;
		if (Corners[i].X > BoundMax.X) BoundMax.X = Corners[i].X;

		if (Corners[i].Y < BoundMin.Y) BoundMin.Y = Corners[i].Y;
		if (Corners[i].Y > BoundMax.Y) BoundMax.Y = Corners[i].Y;

		if (Corners[i].Z < BoundMin.Z) BoundMin.Z = Corners[i].Z;
		if (Corners[i].Z > BoundMax.Z) BoundMax.Z = Corners[i].Z;
	}
}

