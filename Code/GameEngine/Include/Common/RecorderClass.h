// Target facts (addresses are retail RVAs unless marked VA):
// createRecorder 0037BCC4 allocates 0xE7C (push at 0037BCCF) and calls
// 0037BB98 at 0037BCE8. Those constructor/destructor rows retain the ledger
// name Rva0037BBED; the factory and the table's RecorderClass::update slot
// establish their RecorderClass receiver without changing any row names.
// Constructor 0037BB98 calls SubsystemInterface at 0037BBA9, stores VA
// 00C18828 at +0 (0037BBB2), clears UnicodeStrings +14/+20, constructs the
// +24 member through 0037BADD, clears dword +E78, then calls init 0037B326.
// Destructor 0037BBED restores VA 00C18828, closes FILE +10, destroys the
// +24 member through 0037BB53, releases +20/+14 through 00036E70, then
// calls SubsystemInterface's destructor 001B4E74, which stores VA 00BD77A0.
// VA 00BD77A0 is base teardown, not a second RecorderClass table.
// VA 00C18828 has 14 code entries and is followed by string data: slots
// 0-13 are 0037BD48, 0037B326, 001B5384, 000B3FD0, 005CB9FF, 0047A699,
// 000D43D0, 0047A69C, 000B3FD0, 0037B3D1, 0037DC36, 005CB9FF,
// 000B3FD0, 0047A69C. Slot 0 calls 0037BBED and conditionally deletes this;
// RecorderClass therefore has a virtual destructor. init/reset/update occupy
// slots 1/9/10. The other slots retain the registered parent's declarations.
// Base constructor 001B4E63 proves byte +4 and AsciiString +8: base size C.
// init 0037B326 proves FILE +10, file position +18, mode +1C, dwords
// +E60/+E64/+E68/+E6C/+E74 and analysis byte +E70. getMode 0030F2C7
// reads +1C; initControls 0037BD81 compares it with playback value 1.
// playbackFile calls constructor 0037D076 and stores its pointer at +C
// (0037D2D8); CRC dispatcher 0037D0A7 dereferences that member. The frame
// reader 0037B7C7 reads four bytes into +E78 and writes -1 on failure.
// The +24 member constructor 0037BADD builds GameInfo and eight slots of
// stride 1AC at member +DC, giving extent E3C and ending at recorder +E60.
// Its type remains opaque here. Constructor/destructor and rowed methods
// below are declared out of line; no special-member body is emitted here.
// Named out-of-line rows: isMultiplayer 0037B18C, initControls 0037BD81,
// playbackFile 0037D1E6, copyCurrentRecordingToFile 0037D6E8,
// stopRecording 0037B42D, logPlayerDisconnect 0037B287, logCRCMismatch
// 0037ADB6, logGameEnd 0037AE4E, readArgument 0037AF88, writeArgument
// 0037AF05, rva0037AEE2 0037AEE2, dumpCommandHistory 0037BE15,
// writeToFile 0037B461, appendNextCommand 0037B7F6, updateRecord 0037D42B,
// logGameStart 0037B1FA and startRecording 0037C57E. getMode's existing
// symbol pin names the shared 0030F2C7 accessor called by 0031B99A.
// Donor facts: Zero Hour Common/Recorder.h supplies the established field
// and lifecycle names. BFME2's named ledger rows supply method signatures;
// unidentified storage and virtual slots keep neutral names.
#pragma once
#ifndef __BFME2_RECORDERCLASS_H_
#define __BFME2_RECORDERCLASS_H_

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include <stdio.h>

class GameLogic;
class GameMessage;
class CommandDumpFile0037BE15;
class Rva0037D076;
class Rva0037B7C7;
union GameMessageArgumentType;
enum RecorderModeType;

class RecorderClass : public SubsystemInterface
{
    friend class GameLogic;
    friend class Rva0037B7C7;
public:
    RecorderClass();
    virtual ~RecorderClass();
    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif

    RecorderModeType getMode();
    bool isMultiplayer();
    void initControls();
    bool playbackFile(UnicodeString);
    bool copyCurrentRecordingToFile(UnicodeString *, UnicodeString *);
    void stopRecording();
    void logPlayerDisconnect(UnicodeString, int);
    void logCRCMismatch();
    void logGameEnd() throw();
    void readArgument(int, GameMessage *);
    void writeArgument(int, GameMessageArgumentType);
    void rva0037AEE2();

protected:
    void dumpCommandHistory(CommandDumpFile0037BE15 *, unsigned int);
    void writeToFile(GameMessage *);
    void appendNextCommand();
    void updateRecord();
    void logGameStart(AsciiString);
    void startRecording(int, int, int, int);

public:
    Rva0037D076 *m_crcInfo;
    FILE *m_file;
    UnicodeString m_fileName;
    int m_currentFilePosition;
    int m_mode;
    UnicodeString m_currentReplayFilename;
    unsigned char m_field24[0xE3C];
    int m_fieldE60;
    int m_fieldE64;
    int m_fieldE68;
    int m_fieldE6C;
    bool m_doingAnalysis;
    unsigned char m_padE71[3];
    int m_originalGameMode;
    unsigned int m_nextFrame;
};

typedef char RecorderClassSizeCheck[sizeof(RecorderClass) == 0xE7C ? 1 : -1];

extern RecorderClass *TheRecorder;
RecorderClass *createRecorder();

#endif
