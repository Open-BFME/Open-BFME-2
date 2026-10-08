// ?HandlePersistentStorageResponses@@YAXXZ
// partial score=0.988 date=2026-10-09
// Bank for ?HandlePersistentStorageResponses@@YAXXZ 0x005BDAC1 (1752B): unified diff to apply
// on Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp (pre-0x559D0C state).
#if 0
--- build/o3/pst.orig.cpp	2026-10-08 23:55:10.831298261 +0200
+++ build/o3/hpsr_bank.cpp	2026-10-09 00:01:10.602394563 +0200
@@ -55,6 +55,7 @@
 {
 public:
     basic_string();
+    basic_string(const CharT *text, const Alloc &alloc = Alloc());
     // STLport's inline teardown under the game allocator: free the block when
     // one was allocated (retail inlines it for by-value string temporaries).
     ~basic_string() { if (start) Rva00030830FreeAllocation(start); }
@@ -157,6 +158,7 @@
     virtual void rva005550A0(XferStub *);
     virtual void rva00555109(XferStub *);
     virtual void rva00554AF2(const Rva00553E47StatsCore *);
+    friend class Rva00559D0CRankWeights;
 private:
     StatsShortMap m_maps04_0;
     StatsShortMap m_maps04_1;
@@ -292,6 +294,8 @@
 	void setTournamentStats(Rva00385333 stats);
 	Int getLocale() const { return m_locale; }
 	void setID(Int id);
+	friend void HandlePersistentStorageResponses();
+	Int getID() const { return m_id; }
 
 private:
 	Int m_id;						// +0x000
@@ -921,6 +925,13 @@
 	virtual void addRequest(const BfmeOpaqueOwnedRecord1432 &req) = 0;
 	virtual bool getRequest(BfmeOpaqueOwnedRecord1432 &req) = 0;
 	virtual void addResponse(const BfmeOpaqueOwnedRecord1408 &resp) = 0;
+	virtual bool getResponse(BfmeOpaqueOwnedRecord1408 &resp);
+	virtual void trackPlayerStats(PSPlayerAllStats stats);
+	virtual void slot09();
+	virtual void slot10();
+	virtual void slot11();
+	virtual PSPlayerAllStats findPlayerStatsByID(Int id);
+	virtual Rva00385333 slot13(Int id);
 };
 extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;	// 0x00E05FC8
 
@@ -1826,8 +1837,35 @@
 		TheGameSpyPSMessageQueue->addRequest(req);
 }
 
-// TheGameSpyInfo's local email and base name (vtable 0x00C1DD90 slots 32 and
-// 37, rowed in PeerDefs.cpp); the earlier slots are not used here.
+#include "unicode_string.h"
+
+// PeerDefs.cpp's view of the lobby player record (map value at node +0x14).
+class PlayerInfo
+{
+public:
+	AsciiString m_name;
+	AsciiString m_locale;
+	AsciiString m_clan;
+	Int m_wins;
+	Int m_losses;
+	Int m_profileID;
+	Int m_flags;
+	Int m_rankPoints;
+	Int m_side;
+	Int m_unk24;
+	Int m_dc;
+	Int m_desync;
+	Int m_preorder;
+	~PlayerInfo();
+};
+struct AsciiComparator
+{
+	bool operator()(AsciiString s1, AsciiString s2) const;
+};
+typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;
+
+// TheGameSpyInfo (vtable 0x00C1DD90, rowed in PeerDefs.cpp); slot numbers
+// follow Zero Hour's GameSpyInfoInterface where the calls below use them.
 class GameSpyInfoInterface
 {
 public:
@@ -1836,12 +1874,29 @@
 	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
 	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
 	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
-	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
+	virtual void slot20(); virtual PlayerInfoMap *getPlayerInfoMap(); virtual void slot22(); virtual void slot23();
 	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
-	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
+	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual Int getLocalProfileID(void);
 	virtual AsciiString getLocalEmail(void);
 	virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
 	virtual AsciiString getLocalBaseName(void);
+	virtual void setCachedLocalPlayerStats(PSPlayerAllStats stats);
+	virtual void slot39();
+	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
+	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
+	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
+	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
+	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
+	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
+	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
+	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
+	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
+	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
+	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
+	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
+	virtual void slot88(); virtual void slot89();
+	virtual bool didPlayerPreorder(Int profileID) const;
+	virtual void markPlayerAsPreorder(Int profileID);
 };
 extern GameSpyInfoInterface *TheGameSpyInfo;
 extern int g_009C0758;
@@ -1874,3 +1929,280 @@
 	req.player = player;
 	TheGameSpyPSMessageQueue->addRequest(req);
 }
+
+// Zero Hour's CalculateRank as a member of BFME2's two 0x34-byte rank weight
+// tables (VA 0x00E05FCC for game mode 1, 0x00E06000 for mode 0): wins (the
+// +0x04 map) and losses (+0x10) are summed as unsigned words, scaled by the
+// +0x2C and +0x30 weights and floored at zero. Native [559D0C,559DA0),148B.
+class Rva00559D0CRankWeights
+{
+public:
+	Int rva00559D0C(const Rva00553E47StatsCore *stats) const;
+private:
+	unsigned char m_00[0x2C];
+	float m_winWeight;
+	float m_lossWeight;
+};
+Int Rva00559D0CRankWeights::rva00559D0C(const Rva00553E47StatsCore *stats) const
+{
+	if (stats->m_id == 0)
+		return 0;
+	Int wins = 0;
+	StatsShortMap::const_iterator it;
+	for (it = stats->m_maps04_0.begin(); it != stats->m_maps04_0.end(); ++it)
+		wins += (unsigned short)it->second;
+	Int winPoints = (Int)((float)wins * m_winWeight);
+	Int losses = 0;
+	for (it = stats->m_maps04_1.begin(); it != stats->m_maps04_1.end(); ++it)
+		losses += (unsigned short)it->second;
+	Int rank = (Int)((float)losses * m_lossWeight + (float)winPoints);
+	return _STL::max(rank, 0);
+}
+extern unsigned int g_Va00E05FCC;
+extern unsigned int g_Va00E06000;
+
+// The peer thread's request (0x1EC bytes, rowed constructor 0x001EF661 and
+// destructor 0x001EF723) and response records; only the fields used here.
+struct BfmeOpaqueOwnedRecord492
+{
+	BfmeOpaqueOwnedRecord492();
+	~BfmeOpaqueOwnedRecord492();
+	Int requestType;
+	unsigned char m_04[0x114];
+	Int m_118;
+	Int m_11c;
+	unsigned char m_120[0xCC];
+};
+typedef char PeerRequestViewSizeCheck[sizeof(BfmeOpaqueOwnedRecord492) == 0x1EC ? 1 : -1];
+class PeerResponse
+{
+public:
+	PeerResponse();
+	~PeerResponse();
+	Int peerResponseType;
+	Rva00385333String groupRoomName;
+	Rva00385333String nick;
+	Rva00385333String oldNick;
+	unsigned char text[12];				// wide string
+	Rva00385333String locale;
+	Rva00385333String stagingServerGameOptions;
+	unsigned char stagingServerName[12];	// wide string
+	Rva00385333String stagingServerPingString;
+	Rva00385333String stagingServerLadderIP;
+	Rva00385333String stagingRoomMapName;
+	Rva00385333String extraRoomString;
+	Rva00385333String stagingRoomPlayerNames[8];
+	Rva00385333String command;
+	Rva00385333String commandOptions;
+	unsigned char stringList[12];			// vector<AsciiString>
+	Int words[143];
+};
+typedef char PeerResponseViewSizeCheck[sizeof(PeerResponse) == 0x348 ? 1 : -1];
+class GameSpyPeerMessageQueueInterface
+{
+public:
+	virtual ~GameSpyPeerMessageQueueInterface();
+	virtual void startThread();
+	virtual void endThread();
+	virtual bool isThreadRunning();
+	virtual bool isConnected();
+	virtual bool isConnecting();
+	virtual void addRequest(const BfmeOpaqueOwnedRecord492 &req);
+	virtual bool getRequest(BfmeOpaqueOwnedRecord492 &req);
+	virtual void addResponse(const PeerResponse &resp);
+};
+extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
+
+class GameTextInterface
+{
+public:
+	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
+	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
+	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
+	virtual UnicodeString fetch(const char *label, bool *exists = 0);
+};
+extern GameTextInterface *TheGameText;
+void GSMessageBoxOk(UnicodeString title, UnicodeString message, void (*okFunc)());
+void Rva00548B97Free(int overlay);
+bool SetUnsignedIntInRegistry(Rva00385333String path, Rva00385333String key, unsigned int val);
+void Rva0043DB3DSet(unsigned char flag);
+struct Rva005B9717Block;
+void rva005B9717(const Rva005B9717Block *, const Rva005B9717Block *, const Rva005B9717Block *,
+	const Rva005B9717Block *, const Rva005B9717Block *, const Rva005B9717Block *);
+class GameSpyStagingRoomModeView
+{
+public:
+	unsigned char m_00[0x5C];
+	Int m_gameMode;
+};
+extern GameSpyStagingRoomModeView *TheGameSpyGame;
+struct Rva0059EB6FModeHolder
+{
+	unsigned char m_00[0x7C];
+	Int m_mode;
+};
+extern Rva0059EB6FModeHolder *g_Va00E0333C;
+// Stats-block getters rowed under their own address classes: the summed
+// +0x04 and +0x10 word maps (wins, losses) and a byte summary.
+class Rva005537BA { public: unsigned short rva005537BA(); };
+class Rva005537EB { public: unsigned short rva005537EB(); };
+class Rva00553D26 { public: unsigned char rva00553D26(); };
+
+// The two values a type-4 response delivers (kind 1 and kind 2).
+Int g_psResponseKind1Value;
+Int g_psResponseKind2Value;
+
+// Zero Hour's HandlePersistentStorageResponses (PopupPlayerInfo.cpp) on
+// BFME2's seven response types. Native [5BDAC1,5BE199),1752B.
+void HandlePersistentStorageResponses()
+{
+	if (TheGameSpyPSMessageQueue)
+	{
+	BfmeOpaqueOwnedRecord1408 resp;
+	if (TheGameSpyPSMessageQueue->getResponse(resp))
+	{
+		switch (resp.responseType)
+		{
+		case 1:
+			{
+				GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:PSCannotConnect"), 0);
+				Rva00548B97Free(0);
+			}
+			break;
+		case 2:
+			{
+				if (resp.preorder)
+				{
+					SetUnsignedIntInRegistry("", "Preorder", 1);
+					TheGameSpyInfo->markPlayerAsPreorder(TheGameSpyInfo->getLocalProfileID());
+					BfmeOpaqueOwnedRecord1408 newResp;
+					newResp.responseType = 0;
+					newResp.player = TheGameSpyPSMessageQueue->findPlayerStatsByID(TheGameSpyInfo->getLocalProfileID());
+					TheGameSpyPSMessageQueue->addResponse(newResp);
+				}
+			}
+			break;
+		case 3:
+			{
+				Rva00385333 tournament = TheGameSpyPSMessageQueue->slot13(resp.player.m_id);
+				if (resp.m_550 == TheGameSpyInfo->getLocalProfileID())
+				{
+					g_009C0758 = resp.m_554;
+					g_009C075C = resp.m_558;
+					if (tournament.m_id)
+						Rva005BD910Submit(&tournament);
+					BfmeOpaqueOwnedRecord492 req;
+					req.requestType = 0x19;
+					req.m_118 = g_009C0758;
+					req.m_11c = g_009C075C;
+					TheGameSpyPeerMessageQueue->addRequest(req);
+				}
+				PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->begin();
+				while (it != TheGameSpyInfo->getPlayerInfoMap()->end())
+				{
+					PlayerInfo *info = &(it->second);
+					if (info && info->m_profileID == resp.player.m_id)
+					{
+						info->m_side = g_009C0758;
+						info->m_unk24 = g_009C075C;
+						break;
+					}
+					++it;
+				}
+			}
+			break;
+		case 0:
+			{
+				TheGameSpyPSMessageQueue->trackPlayerStats(resp.player);
+				PSPlayerAllStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(resp.player.m_id);
+				Rva0038454E strategic(0);
+				Rva003844D7 openPlay(0);
+				Rva00385333 tournament(0);
+				strategic = stats.rva00389E0F();
+				openPlay = stats.rva00389DF1();
+				tournament = stats.rva00556508();
+				Rva00553E47StatsCore *current = 0;
+				if (g_Va00E0333C)
+				{
+					if (g_Va00E0333C->m_mode == 1)
+						current = &strategic;
+					else if (g_Va00E0333C->m_mode == 0)
+						current = &openPlay;
+				}
+				if (resp.player.getID() == TheGameSpyInfo->getLocalProfileID() && resp.m_04 == 1)
+				{
+					BfmeOpaqueOwnedRecord492 req;
+					req.requestType = 0x13;
+					TheGameSpyPeerMessageQueue->addRequest(req);
+					Rva005BD910Submit(&tournament);
+				}
+				if (stats.getID() == TheGameSpyInfo->getLocalProfileID())
+					TheGameSpyInfo->setCachedLocalPlayerStats(stats);
+				if (current)
+				{
+					PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->begin();
+					while (it != TheGameSpyInfo->getPlayerInfoMap()->end())
+					{
+						PlayerInfo *info = &(it->second);
+						if (info && info->m_profileID == stats.m_id)
+						{
+							info->m_wins = ((Rva005537BA *)current)->rva005537BA();
+							info->m_losses = ((Rva005537EB *)current)->rva005537EB();
+							if (TheGameSpyGame->m_gameMode == 1)
+								info->m_rankPoints = ((Rva00559D0CRankWeights *)&g_Va00E05FCC)->rva00559D0C(current);
+							else if (TheGameSpyGame->m_gameMode == 0)
+								info->m_rankPoints = ((Rva00559D0CRankWeights *)&g_Va00E06000)->rva00559D0C(current);
+							info->m_desync = ((Rva00553D26 *)current)->rva00553D26();
+							info->m_preorder = TheGameSpyInfo->didPlayerPreorder(info->m_profileID);
+							PeerResponse presp;
+							presp.peerResponseType = 13;
+							presp.nick = info->m_name.str();
+							presp.words[0] = info->m_profileID;
+							presp.words[4] = info->m_flags;
+							presp.words[1] = info->m_wins;
+							presp.words[2] = info->m_losses;
+							presp.locale = info->m_clan.str();
+							presp.words[6] = info->m_rankPoints;
+							presp.words[7] = info->m_desync;
+							presp.words[8] = info->m_preorder;
+							presp.words[140] = info->m_side;
+							presp.words[141] = info->m_unk24;
+							presp.words[142] = info->m_dc;
+							TheGameSpyPeerMessageQueue->addResponse(presp);
+							break;
+						}
+						++it;
+					}
+				}
+			}
+			break;
+		case 4:
+			if (resp.m_560 == 1)
+				g_psResponseKind1Value = resp.m_55C;
+			else if (resp.m_560 == 2)
+				g_psResponseKind2Value = resp.m_55C;
+			break;
+		case 5:
+			rva005B9717((const Rva005B9717Block *)resp.m_564[0], (const Rva005B9717Block *)resp.m_564[1],
+				(const Rva005B9717Block *)resp.m_564[2], (const Rva005B9717Block *)resp.m_564[3],
+				(const Rva005B9717Block *)resp.m_564[4], (const Rva005B9717Block *)resp.m_564[5]);
+			delete resp.m_564[0];
+			resp.m_564[0] = 0;
+			delete resp.m_564[1];
+			resp.m_564[1] = 0;
+			delete resp.m_564[2];
+			resp.m_564[2] = 0;
+			delete resp.m_564[3];
+			resp.m_564[3] = 0;
+			delete resp.m_564[4];
+			resp.m_564[4] = 0;
+			delete resp.m_564[5];
+			resp.m_564[5] = 0;
+			break;
+		case 6:
+			Rva0043DB3DSet(resp.m_57D);
+			break;
+		}
+	}
+	}
+}
#endif
