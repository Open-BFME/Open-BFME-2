/* Target facts (code addresses are RVAs; tables are VAs): IMEManager is polymorphic. Constructor 0x0023309A calls SubsystemInterface's constructor 0x001B4E63 at 0x0023309D and installs 0x00BE82B8 at 0x002330A4. Destructor 0x0023361E installs that table at 0x0023362F, restores IMEManagerInterface's table 0x00BE8238 at 0x002336B2 and calls SubsystemInterface's destructor 0x001B4E74 at 0x002336B8. The interface constructor 0x00232DA2 calls the same base at 0x00232DA5 and installs 0x00BE8238 at 0x00232DAA; its destructor 0x00232D7B restores that table and jumps to 0x001B4E74. These are successive base and derived lifetimes. The interface adds no storage to the 0x0C-byte SubsystemInterface prefix (byte +4, AsciiString +8, established by 0x001B4E63/0x001B4E74). CreateIMEManagerInterface pushes 0x3064 at 0x002331C6, calls operator new at 0x002331CB and the constructor at 0x002331DF, proving sizeof 0x3064.
   Tables 0x00BE8238 and 0x00BE82B8 each have 32 slots. The interface ends at the derived table, which ends at text at 0x00BE8338. Slots 0-13 are SubsystemInterface's: 0 deleting destructor (interface 00232D86, derived 00233A3E), 1 init (pure in the interface, derived 002336CA), 2 loadIniFilesFromLegend 001B5384, 3/8/12 empty 000B3FD0, 4/11 false-ret-4 005CB9FF, 5 false 0047A699, 6 zero 000D43D0, 7/13 ret-4 0047A69C, 9 reset and 10 update (pure in the interface, empty in the derived table). Interface slots 14-31 are pure; derived slots are 14 attach 00233138, 15 detatch 00232DB4, 16 enable 00232E01, 17 disable 00232E1E, 18 isEnabled 00232E2F, 19 isAttachedTo 0056A9CF (compares +10 with its argument), 20 getWindow 001DB09D (reads +10), 21 isComposing 00232E8F, 22 getCompositionString 00233186, 23 getCompositionCursorPosition 00232E93, 24 getIndexBase 00232F7D, 25 getCandidateCount 0023303C, 26 getCandidate 002339AA, 27 getSelectedCandidateIndex 00233043, 28 getCandidatePageSize 0023304A, 29 getCandidatePageStart 00233051, 30 serviceIMEMessage 00233C0B, 31 result 001DB0A8 (reads +0C). Calls at 00233147/0023315D dispatch through slots 15/17. These table entries prove slot ownership, not the identities of unrelated ICF-folded ledger names.
   Constructor stores at 002330AA-00233114 prove dwords +0C/+10/+14/+18/+1C, byte +20, dwords +3028/+302C/+3030/+3034/+3038/+303C/+3040/+3044, byte +3048 and dwords +304C/+3050/+3054/+3058/+305C/+3060. Its loop at 0023311A-00233132 clears 0x801 words at +22 and +1024. updateCompositionString 00232E9A clears a word at +2026; storage through +3027 remains unnamed. Ledger methods also prove convertCharToWide 00232E3D (two unsigned arguments), getResultsString 00232F0C, updateProperties 00232F4F, resizeCandidateWindow 00232F84, openStatusWindow 00233058, closeStatusWindow 0023306A, convertToUnicode 0023323B, closeCandidateList 002332B2, updateCandidateList 002332FB and openCandidateList 002338B4. Zero Hour's GeneralsMD IMEManager.h and GUI/IMEManager.cpp supply the interface, method and member names where these retail accesses agree; the extra storage at +2026 uses a neutral name. */
#ifndef BFME2_IMEMANAGERCLASS_H
#define BFME2_IMEMANAGERCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class GameWindow;
class UnicodeString;

class IMEManagerInterface : public SubsystemInterface
{
public:
    virtual ~IMEManagerInterface();

#ifndef BFME_SUBSYSTEM_SLOTS
    virtual void init() = 0;
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif

    virtual void attach(GameWindow *window) = 0;
    virtual void detatch() = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual bool isEnabled() = 0;
    virtual bool isAttachedTo(GameWindow *window) = 0;
    virtual GameWindow *getWindow() = 0;
    virtual bool isComposing() = 0;
    virtual void getCompositionString(UnicodeString &string) = 0;
    virtual int getCompositionCursorPosition() = 0;
    virtual int getIndexBase() = 0;
    virtual int getCandidateCount() = 0;
    virtual UnicodeString *getCandidate(int index) = 0;
    virtual int getSelectedCandidateIndex() = 0;
    virtual int getCandidatePageSize() = 0;
    virtual int getCandidatePageStart() = 0;
    virtual bool serviceIMEMessage(void *windowsHandle, unsigned int message, int wParam, int lParam) = 0;
    virtual int result() = 0;
};

class IMEManager : public IMEManagerInterface
{
public:
    IMEManager();
    virtual ~IMEManager();

    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void attach(GameWindow *window);
    virtual void detatch();
    virtual void enable();
    virtual void disable();
    virtual bool isEnabled();
    virtual bool isAttachedTo(GameWindow *window);
    virtual GameWindow *getWindow();
    virtual bool isComposing();
    virtual void getCompositionString(UnicodeString &string);
    virtual int getCompositionCursorPosition();
    virtual int getIndexBase();
    virtual int getCandidateCount();
    virtual UnicodeString *getCandidate(int index);
    virtual int getSelectedCandidateIndex();
    virtual int getCandidatePageSize();
    virtual int getCandidatePageStart();
    virtual bool serviceIMEMessage(void *windowsHandle, unsigned int message, int wParam, int lParam);
    virtual int result();

protected:
    enum { MAX_COMPSTRINGLEN = 2 * 1024 };

    int m_result;
    GameWindow *m_window;
    void *m_context;
    void *m_oldContext;
    int m_disabled;
    bool m_composing;
    unsigned short m_compositionString[MAX_COMPSTRINGLEN + 1];
    unsigned short m_resultsString[MAX_COMPSTRINGLEN + 1];
    unsigned short field2026[MAX_COMPSTRINGLEN + 1];
    int m_compositionCursorPos;
    int m_compositionStringLength;
    int m_indexBase;
    int m_pageStart;
    int m_pageSize;
    int m_selectedIndex;
    int m_candidateCount;
    UnicodeString *m_candidateString;
    bool m_unicodeIME;
    int m_compositionCharsDisplayed;

    unsigned short convertCharToWide(unsigned int mbchar, unsigned int codePage);
    void updateCompositionString();
    void getResultsString();
    void updateProperties();
    void openCandidateList(int candidateFlags);
    void closeCandidateList(int candidateFlags);
    void updateCandidateList(int candidateFlags);
    void convertToUnicode(char *mbcs, UnicodeString &unicode);
    void resizeCandidateWindow(int pageSize);
    void openStatusWindow();
    void closeStatusWindow();

    GameWindow *m_candidateWindow;
    GameWindow *m_statusWindow;
    GameWindow *m_candidateTextArea;
    GameWindow *m_candidateUpArrow;
    GameWindow *m_candidateDownArrow;
};

IMEManager *CreateIMEManagerInterface();

#endif
