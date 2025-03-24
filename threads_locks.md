This program, `x86.py`, allows you to see how different thread interleavings either cause or avoid race conditions. See the [README](https://github.com/remzi-arpacidusseau/ostep-homework/blob/master/threads-locks/README.md) for details on how the program works and answer the questions below. All source code can be found the same respository as the README.

## Questions
1. Examine `flag.s`. This code “implements” locking with a single memory flag. Can you understand the assembly?
2. When you run with the defaults, does `flag.s` work? Use the `-M` and `-R` flags to trace variables and registers (and turn on `-c` to see their values). Can you predict what value will end up in flag?
3. Change the value of the register `%bx` with the -a flag (e.g., `-a bx=2,bx=2` if you are running just two threads). What does the code do? How does it change your answer for the question above?
4. Set bx to a high value for each thread, and then use the `-i` flag to generate different interrupt frequencies; what values lead to a bad outcomes? Which lead to good outcomes?
5. Now let’s look at the program `test-and-set.s`. First, try to understand the code, which uses the `xchg` instruction to build a simple locking primitive. How is the lock acquire written? How about lock release?