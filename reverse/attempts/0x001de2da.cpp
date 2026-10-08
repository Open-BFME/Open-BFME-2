// ?reportEvaEvent@Eva@@QAE_NW4EvaEventID@@PBUCoord3D@@1@Z
// partial score=0.99 date=2026-10-08
// Banked near miss for Eva::reportEvaEvent (0x001DE2DA, 247B), Eva.cpp /O1 /G7.
// Compiles to 247 bytes; one byte differs plus the unpinned 0x001DD468 call.
// Retail puts insert_equal's iterator return slot at [ebp+8] (eventID's slot,
// shared with the frame-key temp); this compiles it at [ebp+0xc]. Tried without
// change: named frame local, named or reference-bound delayed object (fixes
// slot, loses push eax), static inline maker, inline ctor (inlines),
// STLport const_iterator conversion (insert stops inlining), __forceinline insert,
// const UnsignedInt& ctor param. The key to the register shape was a
// reference to the delay field (const UnsignedInt &delay). Needs a pin for
// internalReportEvaEvent at 0x001DD468 (unrowed).
// Declarations added to Eva.cpp (full diff vs e4ff732f3a follows the body):
//   struct Rva001DD063 { Rva001DD063(); EvaEventID m_eventID; Bool m_hasPosition;
//     Bool m_hasSecondPosition; pad[2]; Coord3D m_position; Coord3D m_secondPosition; };
//   struct Rva001DD1B3 { Rva001DD1B3(const Int &frame, const Rva001DD063 &report);
//     Int m_frame; Rva001DD063 m_report; };
//   _STL::multiset<Rva001DD1B3,...> m_delayedEvents at Eva+0x10 (inline insert ->
//   _Rb_tree::insert_equal 0x001DDA1C); Arg001DCDAF::m_delayFrames at +0x0C;
//   GameLogic::rva001DCD1C() 0x001DCD1C.
Bool Eva::reportEvaEvent(EvaEventID eventID, const Coord3D *position, const Coord3D *secondPosition)
{
	if (eventID == EVA_INVALID)
		return false;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	Rva001DD063 report;
	report.m_eventID = eventID;
	if (position)
	{
		report.m_position = *position;
		report.m_hasPosition = true;
	}
	else
		report.m_hasPosition = false;
	if (secondPosition)
	{
		report.m_secondPosition = *secondPosition;
		report.m_hasSecondPosition = true;
	}
	else
		report.m_hasSecondPosition = false;
	const UnsignedInt &delay = m_allEventInfos[eventID].m_delayFrames;
	if (delay > 0)
	{
		GameLogic *logic = TheGameLogic;
		if (!logic->rva001DCD1C())
		{
			m_delayedEvents.insert(Rva001DD1B3(logic->m_frame + delay, report));
			return true;
		}
	}
	return internalReportEvaEvent(&report);
}

/* full diff:
diff --git a/Code/GameEngine/Source/GameClient/Eva.cpp b/Code/GameEngine/Source/GameClient/Eva.cpp
index 0836891e59..0925bc499c 100644
--- a/Code/GameEngine/Source/GameClient/Eva.cpp
+++ b/Code/GameEngine/Source/GameClient/Eva.cpp
@@ -59,7 +59,9 @@ struct EvaCoord
 // argument.
 struct Arg001DCDAF
 {
-	unsigned char m_data[0x20];
+	unsigned char m_data[0x0c];
+	UnsignedInt m_delayFrames;				// +0x0C, observed retail unsigned test
+	unsigned char m_pad10[0x20 - 0x10];
 	EvaEventID *m_eventIDsStart;			// +0x20, observed retail pointer read
 	EvaEventID *m_eventIDsFinish;			// +0x24, observed retail pointer read
 	unsigned char m_pad28[0x2c - 0x28];
@@ -111,6 +113,8 @@ public:
 class GameLogic
 {
 public:
+	Bool rva001DCD1C();					// 0x001DCD1C
+
 	unsigned char m_pad00[0x40];
 	UnsignedInt m_frame;				// +0x40, observed retail load
 };
@@ -127,29 +131,82 @@ public:
 	void rva001DD240(UnsignedInt *info);			// 0x001DD240
 };
 
-// The report internalReportEvaEvent takes: the event, then two optional
-// positions, each behind a presence flag.
-struct EvaEventReport
+// The report internalReportEvaEvent takes (WB's report record; rowed under
+// the placeholder Rva001DD063, default constructor 0x001DD1D0): the event,
+// then two optional positions, each behind a presence flag.
+struct Rva001DD063
 {
+	Rva001DD063();						// 0x001DD1D0
+
 	EvaEventID m_eventID;					// +0x00
 	Bool m_hasPosition;					// +0x04
 	Bool m_hasSecondPosition;				// +0x05
 	unsigned char m_pad06[2];
-	Vec001DCDAF m_position;					// +0x08
-	Vec001DCDAF m_secondPosition;				// +0x14
+	Coord3D m_position;					// +0x08
+	Coord3D m_secondPosition;				// +0x14
+};
+
+// A delayed report keyed by the frame it is due (0x001DD2BF), held in Eva's
+// multiset.
+struct Rva001DD1B3
+{
+	Rva001DD1B3(const Int &frame, const Rva001DD063 &report);
+
+	Int m_frame;						// +0x00
+	Rva001DD063 m_report;					// +0x04
+};
+
+// STLport's tree as far as the delayed-report multiset calls it.
+namespace _STL
+{
+template <class T> struct _Identity {};
+template <class T> struct less {};
+template <class T> class allocator {};
+template <class T> struct _Nonconst_traits {};
+template <class T> struct _Const_traits {};
+template <class T, class Traits> struct _Rb_tree_iterator
+{
+	_Rb_tree_iterator() {}
+	_Rb_tree_iterator(const _Rb_tree_iterator<T, _Nonconst_traits<T> > &it) { _M_node = it._M_node; }
+	void *_M_node;
+};
+template <class Key, class Value, class KeyOfValue, class Compare, class Alloc> class _Rb_tree
+{
+public:
+	typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;
+	typedef _Rb_tree_iterator<Value, _Const_traits<Value> > const_iterator;
+	iterator insert_equal(const Value &v);	// 0x001DDA1C
+
+private:
+	void *_M_header;
+	UnsignedInt _M_node_count;
+	Compare _M_key_compare;
+};
+template <class Key, class Compare, class Alloc> class multiset
+{
+public:
+	typedef _Rb_tree<Key, Key, _Identity<Key>, Compare, Alloc> _Rep_type;
+	typedef typename _Rep_type::iterator iterator;
+	iterator insert(const Key &x) { return _M_t.insert_equal(x); }
+
+private:
+	_Rep_type _M_t;
 };
+}
 
 class Eva
 {
 public:
-	Bool internalReportEvaEvent(const EvaEventReport *report);	// 0x001DD468, unrowed
+	Bool reportEvaEvent(EvaEventID eventID, const Coord3D *position, const Coord3D *secondPosition);
+	Bool internalReportEvaEvent(const Rva001DD063 *report);	// 0x001DD468, unrowed
 	void countEvaEventAsPlayed(EvaEventID eventID);
 	Bool isEventBlockedByTimeout(EvaEventID eventID) const;
 	Bool isEventAboutToPlay(EvaEventID eventID) const;
 	Bool getLastReallyPlayedFrameForEvaEvent(EvaEventID eventID, UnsignedInt *frame) const;
 
 private:
-	unsigned char m_pad00[0x1c];
+	unsigned char m_pad00[0x10];
+	_STL::multiset<Rva001DD1B3, _STL::less<Rva001DD1B3>, _STL::allocator<Rva001DD1B3> > m_delayedEvents;	// +0x10
 	EvaVectorView<Arg001DCDAF> m_allEventInfos;		// +0x1C (WB name)
 	unsigned char m_pad28[0x5c - 0x28];
 	EvaVectorView<Rva001DCDAF> m_eventStatus;		// +0x5C
@@ -209,6 +266,47 @@ Bool Eva::getLastReallyPlayedFrameForEvaEvent(EvaEventID eventID, UnsignedInt *f
 	return true;
 }
 
+// Eva::reportEvaEvent, retail 0x001DE2DA (247 bytes; WorldBuilder's Eva.cpp
+// 0x00ACC880, asserts at lines 1230..1270): a report for an event whose info
+// carries a delay is queued until the frame it is due, unless the logic's
+// 0x001DCD1C state holds; otherwise it is reported now.
+Bool Eva::reportEvaEvent(EvaEventID eventID, const Coord3D *position, const Coord3D *secondPosition)
+{
+	if (eventID == EVA_INVALID)
+		return false;
+	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
+		return false;
+	if (m_eventStatus.size() != m_allEventInfos.size())
+		return false;
+	Rva001DD063 report;
+	report.m_eventID = eventID;
+	if (position)
+	{
+		report.m_position = *position;
+		report.m_hasPosition = true;
+	}
+	else
+		report.m_hasPosition = false;
+	if (secondPosition)
+	{
+		report.m_secondPosition = *secondPosition;
+		report.m_hasSecondPosition = true;
+	}
+	else
+		report.m_hasSecondPosition = false;
+	const UnsignedInt &delay = m_allEventInfos[eventID].m_delayFrames;
+	if (delay > 0)
+	{
+		GameLogic *logic = TheGameLogic;
+		if (!logic->rva001DCD1C())
+		{
+			m_delayedEvents.insert(Rva001DD1B3(logic->m_frame + delay, report));
+			return true;
+		}
+	}
+	return internalReportEvaEvent(&report);
+}
+
 // ?rva001DD7C1@Rva001DCDAF@@QAEXPAUArg001DCDAF@@PBUVec001DCDAF@@@Z 74B @0x001DD7C1.
 // Class identity follows the existing 0x34-byte Rva001DCDAF status record;
 // retail writes its +0x22 flag, +0x24 position and +0x30 frame. The argument
*/
