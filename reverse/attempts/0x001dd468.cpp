// ?internalReportEvaEvent@Eva@@QAE_NPBUEvaEventReport@@@Z
// partial score=0.85 date=2026-10-06
// Banked near miss for Eva::internalReportEvaEvent (0x001DD468, 123B); class views in
// Code/GameEngine/Source/GameClient/Eva.cpp (/O1 /G7). Logic and instruction
// set match; register allocation differs: retail keeps this in ecx and loads
// both array bases (eax/edx) before the optional-position args, report in esi,
// eventID in edi; this compiles this->esi, report->edi, eventID->ecx.
// Eva::internalReportEvaEvent, retail 0x001DD468 (123 bytes).
Bool Eva::internalReportEvaEvent(const EvaEventReport *report)
{
	EvaEventID eventID = report->m_eventID;
	if (eventID < 0 || (UnsignedInt)eventID >= m_eventStatus.size())
		return false;
	if (m_eventStatus.size() != m_allEventInfos.size())
		return false;
	return m_eventStatus[eventID].rva001DCDAF(&m_allEventInfos[eventID],
		report->m_hasPosition ? &report->m_position : 0,
		report->m_hasSecondPosition ? &report->m_secondPosition : 0);
}

