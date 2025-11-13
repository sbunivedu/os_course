# File System Crash Consistency

Please read the relevant chapters on file system crash consistency with journaling and answer the questions:

1. Explain in your own words what the crash-consistency problem is, including why file system updates are vulnerable when crashes or power failures occur during a sequence of writes.

2. Explain the journaling approach (write‐ahead log) in the context of file system updates: the sequence of logging transaction begin, writing metadata/data, writing transaction end, and checkpointing.