// Target facts: WW3D is a plain static utility class with no virtual functions, bases or instance fields. No WW3D constructor, destructor or vftable is named in the matched target ledger; its methods use static cdecl ABI. Sync RVA 0x00117490 accesses globals, not this. sizeof 1 and the class-key come from the empty C++ layout and Zero Hour declaration; no retail allocation proves sizeof. All methods with WW3D ledger rows remain declared out of line.
// Target method RVAs: Is_Snapshot_Activated 0x00065F60; Get_Frame_Time 0x0008513B; Activate_Snapshot 0x00116E10; Set_NPatches_Gap_Filling_Mode 0x00116E50; Set_NPatches_Level 0x00116E70; Set_Any_Render_Device 0x00116F00; Set_Render_Device 0x00116F10; Set_Next_Render_Device 0x00116F50; Get_Window 0x00116F60; Get_Render_Device 0x00116F80; Get_Render_Device_Desc 0x00116F90; Get_Render_Device_Name 0x00116FB0; Set_Device_Resolution 0x00116FC0; Get_Render_Target_Resolution 0x00116FF0; Get_Device_Resolution 0x00117000; Registry_Load_Render_Device 0x00117090; _Invalidate_Mesh_Cache 0x001170A0; _Invalidate_Textures 0x001171B0; Set_Texture_Filter 0x00117280; Prepare_Render_New_Frame 0x001172B0; End_Render 0x00117410; Flip_To_Primary 0x00117460; Get_Last_Frame_Poly_Count 0x00117470; Get_Last_Frame_Vertex_Count 0x00117480; Sync 0x00117490; Set_Ext_Swap_Interval 0x001174B0; Make_Screen_Shot 0x001174F0; Stop_Movie_Capture 0x00117A10; Capture_Next_Movie_Frame 0x00117A60; Pause_Movie 0x00117A70; Is_Movie_Paused 0x00117A80; Is_Recording_Next_Frame 0x00117A90; Is_Movie_Ready 0x00117AC0; Update_Movie_Capture 0x00117AD0; Set_Texture_Reduction 0x00117BB0; Enable_Texturing 0x00117BD0; Enable_Coloring 0x00117BF0; Get_Texture_Reduction 0x00117C00; Add_To_Static_Sort_List 0x00117C40; Render_And_Clear_Static_Sort_Lists 0x00117C60; Enable_Sorting 0x00117C90; Override_Current_Static_Sort_Lists 0x00117CB0; Reset_Current_Static_Sort_Lists_To_Default 0x00117CC0; Set_Gamma 0x00117CD0; Init 0x00118040; Shutdown 0x001180E0; Begin_Render 0x00118170; Render(RenderObjClass,RenderInfoClass) 0x00118430; Normalize_Coordinates 0x001184D0; Start_Movie_Capture 0x00118530; Toggle_Movie_Capture 0x00118610; Render(LayerClass) 0x00118700; Render(LayerListClass) 0x00118760; Is_Sorting_Enabled 0x0012D2A0; Is_Coloring_Enabled 0x0013C5C0; Get_Pixel_Center 0x0014D220. Flush names the donor operation whose native body is rowed as rva001173f0 at RVA 0x001173F0; the existing Flush pin and native caller RVA 0x00104956 pass its one word argument. Set_Render_Device has eight arguments; Begin_Render has four. Init, Shutdown, Set_Render_Device, Set_Device_Resolution, Begin_Render, End_Render and Render return bool in the target ledger.
// Target static accesses: IsInitted VA 0x00DEC3D4 at RVA 0x000422F3; ThumbnailEnabled VA 0x00DB5F8C at RVA 0x000422FD; IsScreenUVBiased VA 0x00DEC3D7 at RVA 0x00042307; PrelitMode VA 0x00DB5F88 at RVA 0x00042311; AreStaticSortListsEnabled VA 0x00DEC3D9 at RVA 0x0004231B; SnapshotActivated VA 0x00DEC3FD at RVA 0x00065F60; IsCurrentlyRenderingShadowMap VA 0x00DEC404 at RVA 0x0006E175; SyncTime VA 0x00DEC3CC at RVA 0x00080895; PreviousSyncTime VA 0x00DEC3D0 at RVA 0x00085140; NPatchesGapFillingMode VA 0x00DB5F90 at RVA 0x00116E54; NPatchesLevel VA 0x00DB5F94 at RVA 0x00116E8B; TextureFilter VA 0x00DB5F9C at RVA 0x0011728A; IsRendering VA 0x00DEC3D5 at RVA 0x00117424; FrameCount VA 0x00DEC3E0 at RVA 0x00117430; IsCapturing VA 0x00DEC3D6 at RVA 0x00117A10; Movie VA 0x00DEC3DC at RVA 0x00117A19; RecordNextFrame VA 0x00DEC3C8 at RVA 0x00117A60; PauseRecord VA 0x00DEC3C9 at RVA 0x00117A74; IsTexturingEnabled VA 0x00DB5F98 at RVA 0x00117BD4; IsColoringEnabled VA 0x00DEC405 at RVA 0x00117BF8; CurrentStaticSortLists VA 0x00DEC3F4 at RVA 0x00117C44; IsSortingEnabled VA 0x00DB5F7C at RVA 0x00117C9C; DefaultStaticSortLists VA 0x00DEC3F0 at RVA 0x00117CC0; MungeSortOnLoad VA 0x00DEC3DA at RVA 0x00171670. These are globals, not instance offsets: flags use byte accesses and integers, enums and pointers use dwords. Shadow-map compatibility accessors express the native read at RVA 0x00101816 and writes at RVA 0x0007DCE0/0x0007DDE9 of the rowed IsCurrentlyRenderingShadowMap static. Other accessor names, enum labels and default arguments come from GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h in the Zero Hour reference; the target ledger fixes differing signatures and the existing private declarations fix static symbol access. No donor header or shim is included.

#pragma once
#ifndef BFME2_WW3DCLASS_H
#define BFME2_WW3DCLASS_H

class Vector3;
class RenderObjClass;
class RenderInfoClass;
class RenderDeviceDescClass;
class LayerClass;
class LayerListClass;
class StaticSortListClass;
class FrameGrabClass;

namespace FXParticleSystem {
    class ButterflyDrawModule;
    class LightningDrawModule;
    class QuadDrawModule;
    class GpuDrawModule;
    class StreakDrawModule;
    template<int CATEGORY> class DefaultModule;
}

class WW3D
{
public:
    enum PrelitModeEnum {
        PRELIT_MODE_VERTEX,
        PRELIT_MODE_LIGHTMAP_MULTI_PASS,
        PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE
    };
    enum NPatchesGapFillingModeEnum {
        NPATCHES_GAP_FILLING_DISABLED,
        NPATCHES_GAP_FILLING_ENABLED,
        NPATCHES_GAP_FILLING_FORCE
    };
    enum ScreenShotFormatEnum { TGA, BMP };

    static bool Init(void *hwnd, char *defaultpal = 0, bool lite = false);
    static bool Shutdown();
    static int Get_Render_Device();
    static const char *Get_Render_Device_Name(int device_index);
    static const RenderDeviceDescClass &Get_Render_Device_Desc(int device = -1);
    static bool Set_Render_Device(int dev = -1, int resx = -1, int resy = -1, int bits = -1, int windowed = -1, bool resize_window = false, bool reset_device = false, bool restore_assets = true);
    static bool Set_Next_Render_Device();
    static bool Set_Any_Render_Device();
    static void *Get_Window();
    static void Get_Pixel_Center(float &x, float &y);
    static void Get_Render_Target_Resolution(int &width, int &height, int &bits, bool &windowed);
    static void Get_Device_Resolution(int &width, int &height, int &bits, bool &windowed);
    static bool Set_Device_Resolution(int width = -1, int height = -1, int bits = -1, int windowed = -1, bool resize_window = false);
    static bool Registry_Load_Render_Device(const char *sub_key, char *device, int device_len, int &width, int &height, int &depth, int &windowed, int &texture_depth);
    static void Set_Texture_Filter(int filter);
    static bool Begin_Render(bool clear, bool clearz, const Vector3 &color, float dest_alpha);
    static bool Render(const LayerListClass &layerlist);
    static bool Render(const LayerClass &layer);
    static bool Render(RenderObjClass &obj, RenderInfoClass &rinfo);
    static void Flush(RenderInfoClass &rinfo);
    static bool End_Render(bool flip_frame = true);
    static bool Prepare_Render_New_Frame();
    static void Flip_To_Primary();
    static void Sync(unsigned int sync_time);
    static unsigned int Get_Frame_Time();
    static unsigned int Get_Last_Frame_Poly_Count();
    static unsigned int Get_Last_Frame_Vertex_Count();
    static void Make_Screen_Shot(const char *filename = "ScreenShot", float gamma = 1.3f, ScreenShotFormatEnum format = TGA);
    static void Start_Movie_Capture(const char *filename_base, float frame_rate, int count, bool compressed);
    static void Stop_Movie_Capture();
    static bool Toggle_Movie_Capture(const char *filename_base, float frame_rate, int count, bool compressed);
    static void Capture_Next_Movie_Frame();
    static void Update_Movie_Capture();
    static void Pause_Movie(bool mode);
    static bool Is_Movie_Paused();
    static bool Is_Recording_Next_Frame();
    static bool Is_Movie_Ready();
    static void Set_Ext_Swap_Interval(long swap);
    static void Set_Texture_Reduction(int value);
    static int Get_Texture_Reduction();
    static void _Invalidate_Mesh_Cache();
    static void _Invalidate_Textures();
    static void Enable_Sorting(bool onoff);
    static bool Is_Sorting_Enabled();
    static void Normalize_Coordinates(int x, int y, float &fx, float &fy);
    static void Set_NPatches_Gap_Filling_Mode(NPatchesGapFillingModeEnum mode);
    static void Set_NPatches_Level(unsigned int level);
    static void Enable_Texturing(bool onoff);
    static bool Is_Coloring_Enabled();
    static void Enable_Coloring(unsigned int color);
    static void Add_To_Static_Sort_List(RenderObjClass *robj, unsigned int sort_level);
    static void Render_And_Clear_Static_Sort_Lists(RenderInfoClass &rinfo);
    static void Override_Current_Static_Sort_Lists(StaticSortListClass *sort_list);
    static void Reset_Current_Static_Sort_Lists_To_Default();
    static bool Is_Snapshot_Activated();
    static void Activate_Snapshot(bool onoff);
    static void Set_Gamma(float gamma, float bright, float contrast, bool calibrate = true);

    static bool Is_Initted() { return IsInitted; }
    static bool Is_Rendering() { return IsRendering; }
    static unsigned int Get_Sync_Time() { return SyncTime; }
    static unsigned int Get_Frame_Count() { return FrameCount; }
    static int Get_Texture_Filter() { return TextureFilter; }
    static bool Is_Texturing_Enabled() { return IsTexturingEnabled; }
    static void Set_Thumbnail_Enabled(bool onoff) { ThumbnailEnabled = onoff; }
    static bool Get_Thumbnail_Enabled() { return ThumbnailEnabled; }
    static void Set_Screen_UV_Bias(bool onoff) { IsScreenUVBiased = onoff; }
    static bool Is_Screen_UV_Biased() { return IsScreenUVBiased; }
    static void Set_Prelit_Mode(PrelitModeEnum mode) { PrelitMode = mode; }
    static PrelitModeEnum Get_Prelit_Mode() { return PrelitMode; }
    static NPatchesGapFillingModeEnum Get_NPatches_Gap_Filling_Mode() { return NPatchesGapFillingMode; }
    static unsigned int Get_NPatches_Level() { return NPatchesLevel; }
    static void Enable_Static_Sort_Lists(bool onoff) { AreStaticSortListsEnabled = onoff; }
    static bool Are_Static_Sort_Lists_Enabled() { return AreStaticSortListsEnabled; }
    static void Enable_Munge_Sort_On_Load(bool onoff) { MungeSortOnLoad = onoff; }
    static bool Is_Munge_Sort_On_Load_Enabled() { return MungeSortOnLoad; }
    static bool Is_Currently_Rendering_Shadow_Map() { return IsCurrentlyRenderingShadowMap; }
    static void Set_Rendering_Shadow_Map(bool onoff) { IsCurrentlyRenderingShadowMap = onoff; }

private:
    template<class T> friend struct DataRowPrivateProbe;
    friend class DX8Wrapper;
    friend class BaseHeightMapRenderObjClass;
    friend class RTS3DScene;
    friend class MeshModelClass;
    friend class W3DProjectedShadowManager;
    friend class W3DSnowManager;
    friend class W3DStatusCircle;
    friend class BfmeB1137;
    friend class Rva0004CA4C;
    friend class Rva0004D47D;
    friend class Rva0007F0FBOwner;
    friend class Rva00743060Class;
    friend class Rva000422F3;
    friend class Rva0006614F;
    friend class Rva0007B275;
    friend void bfmeSetRS(unsigned long, unsigned int);
    friend void Rva000A8F98();
    friend int Rva00083B7BGet();
    friend int Rva00171660Get();
    friend unsigned char Rva0004CAB7GetByte();
    friend unsigned char Rva00131062GetByte();
    friend unsigned char Rva00110094GetByte();
    friend unsigned char Rva00171670GetByte();
    friend bool Rva00118660Call(void *owner, void *camera);
    friend bool Rva001182A0(void *owner, RenderInfoClass &rinfo);
    friend class FXParticleSystem::ButterflyDrawModule;
    friend class FXParticleSystem::LightningDrawModule;
    friend class FXParticleSystem::QuadDrawModule;
    friend class FXParticleSystem::GpuDrawModule;
    friend class FXParticleSystem::StreakDrawModule;
    friend class FXParticleSystem::DefaultModule<6>;

    static unsigned int SyncTime;
    static unsigned int PreviousSyncTime;
    static int FrameCount;
    static bool IsInitted;
    static bool IsRendering;
    static bool IsCapturing;
    static bool IsSortingEnabled;
    static bool IsScreenUVBiased;
    static bool AreStaticSortListsEnabled;
    static bool MungeSortOnLoad;
    static bool SnapshotActivated;
    static bool IsCurrentlyRenderingShadowMap;
    static bool IsTexturingEnabled;
    static bool IsColoringEnabled;
    static bool ThumbnailEnabled;
    static bool PauseRecord;
    static bool RecordNextFrame;
    static int TextureFilter;
    static PrelitModeEnum PrelitMode;
    static NPatchesGapFillingModeEnum NPatchesGapFillingMode;
    static unsigned int NPatchesLevel;
    static FrameGrabClass *Movie;
    static StaticSortListClass *DefaultStaticSortLists;
    static StaticSortListClass *CurrentStaticSortLists;
};

#endif
