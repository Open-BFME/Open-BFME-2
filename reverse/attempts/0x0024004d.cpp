// ?rva0024004D@GameLogic@@QAEX_N@Z
// partial score=0.96 date=2026-10-07
// Banked 0x24004D attempt: unified diff against GameLogicInit.cpp at 7c8583487f.
// Apply with git apply after stripping these comment lines; the body is the tail hunk.
diff --git a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
index 8734df59eb..d634cf9892 100644
--- a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
+++ b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
@@ -394,7 +394,9 @@ public:
 	bool m_70;
 	bool m_71;
 	bool m_72;
-	char m_pad073[0x94 - 0x73];
+	char m_pad073[0x78 - 0x73];
+	bool m_78;
+	char m_pad079[0x94 - 0x79];
 	int m_94;
 	bool m_98;
 	bool m_99;
@@ -905,6 +907,11 @@ public:
 	virtual ~LoadScreen(void);
 	virtual void v01(void);
 	virtual void init(GameInfo *game);                                   // +0x08
+	virtual void v03(void); virtual void v04(void);
+	virtual bool v05(void);                                              // +0x14
+
+	char m_pad04[0xc - 0x4];
+	bool m_c;
 };
 
 class Rva009EB960
@@ -924,6 +931,7 @@ public:
 	virtual void v08();
 	virtual void slot24();
 	void rva001DC5EC(void);
+	void setGroup(AsciiString groupName, bool immidiate = false);
 };
 
 class Rva0023C7D2
@@ -1486,7 +1494,8 @@ public:
 	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
 	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
 	virtual void v38(); virtual void v39(); virtual void v3a(); virtual void v3b();
-	virtual void v3c(); virtual void v3d(); virtual void v3e(); virtual void v3f();
+	virtual void v3c(float value, bool flag);                            // +0xF0
+	virtual void v3d(); virtual void v3e(); virtual void v3f();
 	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
 	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
 	virtual void v48(); virtual void v49(); virtual void v4a(); virtual void v4b();
@@ -2395,3 +2404,88 @@ void GameLogic::rva0023F52C(bool loadingSaveGame)
 		Sleep(1);
 	}
 }
+
+// ?rva0024004D@GameLogic@@QAEX_N@Z @0x0024004D 247B (frame without EH,
+// ret 4; next body 0x00240144). Called from the new-game pass 0x00248558.
+// Target evidence: unless +0x72 or +0x78 is set or the Apt window manager's
+// +0x31C is non-zero, TheTransitionHandler takes the "FadeWholeScreen"
+// group (0x001DC252) and waits (0x001DC5EC); GlobalData +0xAF5 is cleared
+// and 0x00376D49 runs; when TheDisplay's virtual +0x114 holds, the load
+// screen at +0x120 is polled through its virtual +0x14 with Sleep(5). In
+// modes 1, 2 and 5 (+0x110) a timed operation is queued through 0x003FE7E6
+// with the holder 0x0023E8AC (built from an empty local) and the id slot
+// 0x00E02EC4, the load screen's +0x0C flag is cleared, 98.0 goes to the
+// float at 0x00DFE788 and TheAudio's virtual +0xF0 gets (0.0, true).
+// Donor: BFME 1 GameLogic.cpp startNewGame's closing steps (the fade-in
+// transition, m_loadScreenRender = FALSE, deleteLoadScreen-time waits);
+// names stay offset names.
+class Bfme5RefHolderA
+{
+public:
+	Bfme5RefHolderA(int unused);
+	~Bfme5RefHolderA(void);
+
+	void *m_node;
+};
+
+class BfmeAptWindowManager
+{
+public:
+	char m_pad000[0x31c];
+	int m_31c;
+};
+
+class Display
+{
+public:
+	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
+	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
+	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
+	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
+	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
+	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
+	virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
+	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
+	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
+	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
+	virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
+	virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
+	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
+	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
+	virtual void v38(); virtual void v39(); virtual void v3a(); virtual void v3b();
+	virtual void v3c(); virtual void v3d(); virtual void v3e(); virtual void v3f();
+	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
+	virtual void v44();
+	virtual bool v45(void);                                              // +0x114
+};
+
+extern BfmeAptWindowManager *g_bfmeAptWindowManager;
+extern Display *TheDisplay;
+extern int g_00E02EC4;
+extern float g_00DFE788;
+
+bool rva003FE7E6(Bfme5RefHolderA op, int *id);
+
+void GameLogic::rva0024004D(bool loadingSaveGame)
+{
+	if (!m_72 && !m_78 && !g_bfmeAptWindowManager->m_31c) {
+		TheTransitionHandler->setGroup(AsciiString("FadeWholeScreen"));
+		TheTransitionHandler->rva001DC5EC();
+	}
+	TheWritableGlobalData->m_af5 = false;
+	rva00376D49();
+
+	if (TheDisplay->v45() && m_120) {
+		while (!m_120->v05())
+			Sleep(5);
+	}
+
+	if (m_110 == 2 || m_110 == 1 || m_110 == 5) {
+		struct Functor {} functor;
+		rva003FE7E6((int)&functor, &g_00E02EC4);
+		if (m_120)
+			m_120->m_c = false;
+		g_00DFE788 = 98.0f;
+		TheAudio->v3c(0.0f, true);
+	}
+}
