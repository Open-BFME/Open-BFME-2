// Target facts: BFME2 View is polymorphic and has a Snapshot base at +0.
// Constructor RVA 0x0025EDE6 stores VA 0x00BF6178 at 0x0025EDF5; its last
// four-byte store is +0xB0 at 0x0025EEEC. W3DView calls it at 0x0008B7E3,
// then constructs SubsystemInterface at +0xB4 (0x0008B7EA..0x0008B7FB): sizeof 0xB4.
// View table slot 0 is deleting destructor 0x0025EFF1, which calls 0x0025EF18.
// That body clears +4 at 0x0025EF18 and restores Snapshot's VA 0x00BBB554
// at 0x0025EF1C. This is base destruction, not a competing View table.
// Snapshot occupies slots 0..3: destructor, loadPostProcess (0x000B3FD0),
// name getter (0x0008BC8D returns "View" at VA 0x00BC7800), xfer (0x0025F020).
// VA 0x00BF6178 has 153 consecutive code pointers, ending before VA 0x00BF63DC;
// W3DView's VA 0x00BC7568 preserves these positions and adds derived slots.
// Named rowed View slots: 13 getScreenCornerWorldPointsAtZ (0x0025EC22),
// 18 setOrigin (0x000851A6), 19 getOrigin (0x0008BB0E), 21 lookAt (0x0025EA7C),
// 63 setAngle (0x0025EAFB), 65 setPitch (0x0025EB09), 70 getPosition
// (0x0008BB27), 77 zoomIn (0x0025EA2E), 78 zoomOut (0x0025EA55),
// 86 setFieldOfView (0x00086191). W3DView rows prove slots 4 init (0x0008C224),
// 9 pickDrawable (0x0008B1E5), 10 iterateDrawablesInRegion (0x00086245),
// 14 setWidth (0x00087B81), 16 setHeight (0x00087AF4), 20 forceRedraw
// (0x0008D134), 22 initHeightForMap (0x0008D807), 31 cameraModFinalZoom
// (0x000865DB), 34 cameraModFinalPitch (0x0008691F), 36 cameraModFreezeAngle
// (0x00086702), 37/38 cameraModLookToward/cameraModFinalLookToward
// (0x000890FE/0x000892F0), 42 Add_Camera_Shake (0x000875F2),
// 48 setFadeParameters (0x00085EC7), 51 rotateCamera (0x0008647C),
// 52/53 rotateCameraTowardObject/Position (0x0008652B/0x00088D65),
// 61/62 zoomCamera/pitchCamera (0x00088FF6/0x0008907A), 74 setZoom
// (0x0008D3C1), 76 setHeightAboveGround (0x0008D2B8), 88 worldToScreenTriReturn
// (0x0008619F), 90 screenToTerrain (0x0008DE7A), 91 screenToWorldAtZ
// (0x0008A0E5), 107 shake (0x00087452), 157 setViewFilterPos (0x00085F12).
// Getter bodies prove +0x18/+0x1C dimensions (0x002A79A1/0x0030F2C7),
// +0x28/+0x2C angles (0x00094A98/0x00094A9C), +0x34 maximum zoom
// (0x004987FA), +0x3C zoom (0x0008E10E), +0x40 height (0x0008BB38),
// +0x50/+0x54 current/terrain height (0x0008BB58/0x0008BB46), +0x6C FOV
// (0x0008BD0F), +0x58/+0x5C camera locks (0x003F3FCE/0x0008BB81),
// +0x74 mouse lock (0x0008BB85/0x0008BB8F), +0x75 adjustment (0x0008BB3C).
// Constructor 0x0025EDE6 proves all remaining storage widths and offsets below;
// xfer 0x0025F020 proves the pointer at +0x80 and integer triple at +0x8C.
// Nonvirtual worldToScreen is rowed at 0x00050F29 and calls slot 88;
// protected setPosition is rowed at 0x002E6A82 and copies 12 bytes to +0x0C.
// Donor facts: Zero Hour GameClient/View.h supplies the camera API names,
// enum values and field names where the retail accesses agree. Unknown slots
// and storage retain neutral names. Methods are declared for out-of-line use.

#pragma once
#ifndef BFME2_GAMECLIENT_VIEW_H
#define BFME2_GAMECLIENT_VIEW_H

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Coord2D;
struct ICoord2D;
struct IRegion2D;
class Drawable;
class ViewLocation;
class Waypoint;
class AsciiString;
enum ObjectID;
enum FilterModes;
enum FilterTypes;

class View : public Snapshot
{
public:
    enum CameraShakeType { SHAKE_SUBTLE, SHAKE_NORMAL, SHAKE_STRONG, SHAKE_SEVERE, SHAKE_CINE_EXTREME, SHAKE_CINE_INSANE, SHAKE_COUNT };
    enum WorldToScreenReturn { WTS_INSIDE_FRUSTUM, WTS_OUTSIDE_FRUSTUM, WTS_INVALID, WTS_COUNT };
    enum CameraLockType { LOCK_FOLLOW, LOCK_TETHER };

    View();
    virtual ~View();
    // The capitalized Snapshot surface spells slots 1 and 3 itself; View inherits them there.
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
#ifndef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void xfer(Xfer *xfer);
#endif

    virtual void init(); // 4
    virtual void reset();
    virtual unsigned int getID();
    virtual void setZoomLimited(bool limit);
    virtual bool isZoomLimited();
    virtual Drawable *pickDrawable(const ICoord2D *screen, bool forceAttack, int pickType) = 0;
    virtual int iterateDrawablesInRegion(IRegion2D *region, int (*callback)(Drawable *, void *), void *userData) = 0;
    virtual void slot11();
    virtual void slot12();
    virtual void getScreenCornerWorldPointsAtZ(Coord3D *topLeft, Coord3D *topRight, Coord3D *bottomLeft, Coord3D *bottomRight, float z);
    virtual void setWidth(int width);
    virtual int getWidth();
    virtual void setHeight(int height);
    virtual int getHeight();
    virtual void setOrigin(int x, int y);
    virtual void getOrigin(int *x, int *y);
    virtual void forceRedraw() = 0;
    virtual void lookAt(const Coord3D *position);
    virtual void initHeightForMap();
    virtual void scrollBy(Coord2D *delta);
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual bool isCameraMovementFinished();
    virtual void cameraModFinalZoom(float zoom, float easeIn, float easeOut);
    virtual void cameraModRollingAverage(int frames);
    virtual void cameraModFinalTimeMultiplier(int multiplier);
    virtual void cameraModFinalPitch(float pitch, float easeIn, float easeOut);
    virtual void cameraModFreezeTime();
    virtual void cameraModFreezeAngle();
    virtual void cameraModLookToward(Coord3D *position);
    virtual void cameraModFinalLookToward(Coord3D *position);
    virtual void cameraModFinalMoveTo(Coord3D *position);
    virtual void cameraEnableSlaveMode(const AsciiString &thingTemplate, const AsciiString &bone);
    virtual void cameraDisableSlaveMode();
    virtual void Add_Camera_Shake(const Coord3D &position, float radius, float duration, float power);
    virtual FilterModes getViewFilterMode();
    virtual FilterTypes getViewFilterType();
    virtual bool setViewFilterMode(FilterModes mode);
    virtual void slot46();
    virtual bool setViewFilter(FilterTypes filter);
    virtual void setFadeParameters(int frames, int direction);
    virtual void set3DWireFrameMode(bool enable);
    virtual void resetCamera(const Coord3D *location, int frames, float easeIn, float easeOut);
    virtual void rotateCamera(float rotations, int frames, bool unknown, float easeIn, float easeOut);
    virtual void rotateCameraTowardObject(ObjectID id, int milliseconds, int holdMilliseconds, float a, float b, float c);
    virtual void rotateCameraTowardPosition(const Coord3D *position, int milliseconds, float easeIn, float easeOut, bool reverse);
    virtual bool isTimeFrozen();
    virtual int getTimeMultiplier();
    virtual void setTimeMultiplier(int multiplier);
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void zoomCamera(float zoom, int milliseconds, float easeIn, float easeOut);
    virtual void pitchCamera(float pitch, int milliseconds, float easeIn, float easeOut);
    virtual void setAngle(float angle);
    virtual float getAngle();
    virtual void setPitch(float angle);
    virtual float getPitch();
    virtual void slot67(float value);
    virtual float slot68();
    virtual void setAngleAndPitchToDefault();
    virtual void getPosition(Coord3D *position);
    virtual const Coord3D &get3DCameraPosition() const = 0;
    virtual void slot72() = 0;
    virtual float getZoom();
    virtual void setZoom(float zoom);
    virtual float getHeightAboveGround();
    virtual void setHeightAboveGround(float height);
    virtual void zoomIn();
    virtual void zoomOut();
    virtual void setZoomToDefault();
    virtual float getMaxZoom();
    virtual void setOkToAdjustHeight(bool value);
    virtual float getTerrainHeightUnderCamera();
    virtual void setTerrainHeightUnderCamera(float height);
    virtual float getCurrentHeightAboveGround();
    virtual void setCurrentHeightAboveGround(float height);
    virtual void setFieldOfView(float angle);
    virtual float getFieldOfView();
    virtual WorldToScreenReturn worldToScreenTriReturn(const Coord3D *world, ICoord2D *screen) = 0;
    virtual void screenToWorld(const ICoord2D *screen, Coord3D *world) = 0;
    virtual bool screenToTerrain(const ICoord2D *screen, Coord3D *world, bool unknown) = 0;
    virtual void screenToWorldAtZ(const ICoord2D *screen, Coord3D *world, float z) = 0;
    virtual void getLocation(ViewLocation *location);
    virtual void setLocation(const ViewLocation *location);
    virtual void drawView() = 0;
    virtual void updateView() = 0;
    virtual ObjectID getCameraLock() const;
    virtual void setCameraLock(ObjectID id);
    virtual void snapToCameraLock();
    virtual void setSnapMode(CameraLockType type, float distance);
    virtual void slot100(float value);
    virtual float slot101();
    virtual Drawable *getCameraLockDrawable() const;
    virtual void setCameraLockDrawable(Drawable *drawable);
    virtual void slot104();
    virtual void setMouseLock(bool value);
    virtual bool getMouseLock() const;
    virtual void shake(const Coord3D *position, CameraShakeType type);
    virtual float getFXPitch() const;
    virtual void slot109(float value);
    virtual void forceCameraConstraintRecalc();
    virtual void setGuardBandBias(const Coord2D *bias) = 0;
    virtual void slot112() = 0;
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131();
    virtual void slot132();
    virtual void slot133();
    virtual void slot134();
    virtual void slot135();
    virtual void slot136();
    virtual void slot137();
    virtual void slot138();
    virtual void slot139();
    virtual void slot140();
    virtual void slot141();
    virtual void slot142();
    virtual void slot143();
    virtual void slot144();
    virtual void slot145();
    virtual void slot146();
    virtual void slot147();
    virtual void slot148();
    virtual void slot149();
    virtual void slot150();
    virtual View *prependViewToList(View *list);
    virtual View *getNextView();

    bool worldToScreen(const Coord3D *world, ICoord2D *screen);

protected:
    void setPosition(const Coord3D *position);
    const Coord3D *getPosition() const { return &m_pos; }
    static unsigned int m_idNext;

public:
    View *m_next; // +0x04
    unsigned int m_id;
    Coord3D m_pos;
    int m_width;
    int m_height;
    int m_originX;
    int m_originY;
    float m_angle;
    float m_pitchAngle;
    float m_field30;
    float m_maxZoom;
    float m_field38;
    float m_zoom;
    float m_heightAboveGround;
    bool m_zoomLimited;
    float m_defaultAngle;
    float m_defaultPitchAngle;
    float m_currentHeightAboveGround;
    float m_terrainHeightUnderCamera;
    ObjectID m_cameraLock;
    Drawable *m_cameraLockDrawable;
    CameraLockType m_lockType;
    float m_lockDist;
    float m_field68;
    float m_FOV;
    float m_field70;
    bool m_mouseLocked;
    bool m_okToAdjustHeight;
    bool m_snapImmediate;
    float m_guardBandBias[2];
    void *m_field80;
    bool m_field84;
    unsigned int m_field88;
    int m_field8C[3];
    float m_field98;
    float m_field9C;
    float m_fieldA0;
    float m_fieldA4;
    float m_fieldA8;
    float m_fieldAC;
    float m_fieldB0;
};

extern View *TheTacticalView;

#endif
