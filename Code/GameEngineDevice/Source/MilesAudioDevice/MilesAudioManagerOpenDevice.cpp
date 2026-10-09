// cl: /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/MilesAudioDevice/
// MilesAudioManager.cpp, openDevice. Target Ghidra boundary 0x61680/284B.
// Identity evidence: MSS directory literal and the startup/quick_startup/
// quick_handles import sequence, followed by verified OptionPreferences
// UseEAX3 getter and the recovered sample-pool/filter initialization methods.
// Target layout: global audioOn +0x99C; manager settings +0x10, driver +0x9DC,
// provider count/index +0x9CC/+0x9D0, owned device +0xB90, timestamp +0xBF8.
// AudioSettings format fields +0x54..+0x60 come directly from retail accesses.
// BFME2 replaces the donor timer setup with a 0x5C-byte object constructed
// at 0xA8903 from the driver. Its constructor stores the driver at +0x34;
// holder 0x53D66 replaces its pointer and destroys/deletes the old object.
// Address-derived types express only that evidence, not original class names.
// buildProviderList follows the donor; WB names selectProvider and its
// recovered bool ABI agrees with this UseEAX3-fed native call.

typedef bool Bool;
typedef __int64 Time64;
extern "C" __declspec(dllimport) Time64 __cdecl _time64(Time64 *);
extern "C" __declspec(dllimport) void __stdcall AIL_set_redist_directory(const char *);
extern "C" __declspec(dllimport) void __stdcall AIL_startup();
extern "C" __declspec(dllimport) int __stdcall AIL_quick_startup(int,int,int,int,int);
extern "C" __declspec(dllimport) int __stdcall AIL_quick_handles(void **,void *,void *);
class GlobalData { public: char unknown[0x99c]; Bool m_audioOn; };
extern GlobalData *TheWritableGlobalData;
struct AudioSettings {
 char unknown[0x54]; Bool m_useDigital; Bool m_useMidi; char pad[2];
 int m_outputRate; int m_outputBits; int m_outputChannels;
};
class OptionPreferences {
public:
 OptionPreferences(); virtual ~OptionPreferences(); Bool getUseEAX3();
private: char body[0x10];
};
class Rva000A8903AudioDevice {
public: Rva000A8903AudioDevice(void *driver);
private: char body[0x5c];
};
class Rva00053D66DeviceRef {
public: void assign(Rva000A8903AudioDevice *device);
private: void *object;
};
class MilesAudioManager {
public:
virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 virtual void setOn(Bool turnOn,int which);
virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual void v66();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void refreshCachedVariables();
 void openDevice();
private:
 void buildProviderList();
 void selectProvider(Bool accelerated);
 void initSamplePools();
protected:
 void initDelayFilter();
private:
 char prefix[0xc]; AudioSettings *m_audioSettings;
 char pad14[0x9cc-0x14]; unsigned m_providerCount; unsigned m_selectedProvider;
 char pad9d4[8]; void *m_digitalHandle;
 char pad9e0[0xb90-0x9e0]; Rva00053D66DeviceRef m_device;
 char padb94[0xbf8-0xb94]; unsigned int m_timeWords[2];
};
void MilesAudioManager::openDevice() {
 register int retval=0;
 *reinterpret_cast<Time64 *>(m_timeWords)=_time64(0);
 if(!TheWritableGlobalData->m_audioOn) return;
 AIL_set_redist_directory("MSS\\");
 AIL_startup();
 retval=AIL_quick_startup(m_audioSettings->m_useDigital,m_audioSettings->m_useMidi,
 m_audioSettings->m_outputRate,m_audioSettings->m_outputBits,m_audioSettings->m_outputChannels);
 AIL_quick_handles(&m_digitalHandle,0,0);
 if(retval) buildProviderList(); else setOn(0,0x1f);
 OptionPreferences prefs;
 selectProvider(prefs.getUseEAX3());
 initSamplePools();
 refreshCachedVariables();
 m_device.assign(new Rva000A8903AudioDevice(m_digitalHandle));
 if(m_selectedProvider<m_providerCount) initDelayFilter();
}
