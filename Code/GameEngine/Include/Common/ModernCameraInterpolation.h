#ifndef BFME2_MODERN_CAMERA_INTERPOLATION_H
#define BFME2_MODERN_CAMERA_INTERPOLATION_H
#if !defined(BFME2_MODERN)
#error Modern camera interpolation requires the modern variant
#endif
class CameraClass;
void modernBeginCameraUpdate();
void modernResetCamera(const void *view);
// A load/map setup can capture intermediate poses before it returns or throws.
// Clear on both boundaries so none become interpolation endpoints.
class ModernCameraDiscontinuity
{
public:
    explicit ModernCameraDiscontinuity(const void *view) : m_view(view)
    { modernResetCamera(m_view); }
    ~ModernCameraDiscontinuity() { modernResetCamera(m_view); }
private:
    ModernCameraDiscontinuity(const ModernCameraDiscontinuity &);
    ModernCameraDiscontinuity &operator=(const ModernCameraDiscontinuity &);
    const void *m_view;
};
// Only borrows the camera for one draw, never across an update or destruction.
class ModernCameraPresentation
{
public:
    ModernCameraPresentation(const void *view, CameraClass *camera);
    ~ModernCameraPresentation();
private:
    ModernCameraPresentation(const ModernCameraPresentation &);
    ModernCameraPresentation &operator=(const ModernCameraPresentation &);
    CameraClass *m_camera;
    float m_original[12];
};
#endif
