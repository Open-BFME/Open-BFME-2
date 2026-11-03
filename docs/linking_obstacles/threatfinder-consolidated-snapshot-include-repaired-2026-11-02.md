### ThreatFinder consolidated Snapshot include repaired (2026-11-02)

The ordinary Object-header gate exposed ThreatFinderUpdate.cpp's stale five-parent Snapshot include, which pointed under nonexistent Code/reference. Using the correct six-parent path restores all20code rows and both data rows without changing any body, policy or owner. [Normal/strict evidence and exact path scope](../../reverse/attempt_support/threatfinder-snapshot-include-20261102/README.md). This clears the compile obstacle; census/runtime and broader linking status are not remeasured here.
