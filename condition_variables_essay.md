# Condition Variables

Please read the relevant chapters on condition variables and answer the questions:

1. Explain why a simple lock (mutex) is not sufficient for scenarios where one thread must wait for a certain condition (state change) before proceeding. Use examples (such as a parent waiting for a child thread or producer/consumer buffer) from the chapter.

2. Describe how a condition variable together with a mutex offers a better abstraction for this "waiting until condition" problem—discuss the semantics of `wait()` and `signal()` operations.