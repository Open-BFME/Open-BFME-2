// Target facts: Version has no bases or virtual functions. Constructor RVA 0x00238852 zeroes seven 4-byte string handles at +0x10 through +0x28, then calls initializeBuildMetadata (0x0023870E); destructor 0x00002152 releases those handles in reverse order through 0x00036410. Neither installs a vtable. WinMain allocates 0x30 bytes before its constructor call at 0x00003026; GlobalData's call at 0x00236A50 constructs it at +0xB08 before the next field at +0xB38.
// Target facts: initializeBuildMetadata copies four integers to +0/+4/+8/+0xC and assigns ID, MACHINE, USER, GUID, TIME, DATE, CONFIG to +0x10/+0x14/+0x18/+0x1C/+0x20/+0x24/+0x28 (key VAs 0x00BED340/0x00BED318/0x00BED32C/0x00BED2E8/0x00BED2D4/0x00BED2C0/0x00BED2B0), then clears the byte at +0x2C. getBuildGuid (0x0009AA0B) returns this+0x1C; parseFullVersion (0x003B9647) writes +0x2C. Rowed out-of-line methods: getAsciiVersion 0x00237EC1, rva00237F25MajorMinor 0x00237F25, rva00237F83ConfiguredVersion 0x00237F83, getFullUnicodeVersion 0x0023809E, getAsciiBuildTime 0x0023819B, getAsciiBuildLocation 0x002382FD, getUnicodeVersion 0x0023800A, getUnicodeBuildTime 0x00238215, getUnicodeBuildLocation 0x00238318, getUnicodeBuildUser 0x002383F0, rva00237E63 0x00237E63.
// Donor facts: Zero Hour Common/version.h names the numeric fields, location, user, time, date and showFullVersion/setShowFullVersion accessors. BFME2's metadata keys and getBuildGuid name the additional title, GUID and configuration members.
#pragma once

#ifndef __BFME2_VERSIONCLASS_H_
#define __BFME2_VERSIONCLASS_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class UnicodeString;

class Version
{
public:
    Version();
    ~Version();

    AsciiString getAsciiVersion();
    AsciiString rva00237F25MajorMinor();
    AsciiString rva00237F83ConfiguredVersion();
    UnicodeString getUnicodeVersion();
    UnicodeString getFullUnicodeVersion();
    AsciiString getAsciiBuildTime();
    UnicodeString getUnicodeBuildTime();
    AsciiString getAsciiBuildLocation();
    UnicodeString getUnicodeBuildLocation();
    UnicodeString getUnicodeBuildUser();
    AsciiString *getBuildGuid();
    int rva00237E63(const void *other, bool force);
    void initializeBuildMetadata();

    bool showFullVersion() { return m_showFullVersion; }
    void setShowFullVersion(bool value) { m_showFullVersion = value; }

private:
    int m_major;
    int m_minor;
    int m_buildNum;
    int m_localBuildNum;
    AsciiString m_buildTitle;
    AsciiString m_buildLocation;
    AsciiString m_buildUser;
    AsciiString m_buildGuid;
    AsciiString m_buildTime;
    AsciiString m_buildDate;
    AsciiString m_buildConfiguration;
    bool m_showFullVersion;
};

#endif
