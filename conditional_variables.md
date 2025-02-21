This homework lets you explore some real code that uses locks and
condition variables to implement various forms of the producer/consumer
queue discussed in chapter 30. You’ll look at the real code, run it in
various configurations, and use it to learn about what works and what
doesn’t, as well as other intricacies. Read the [README](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/threads-cv) for details.

### Questions
1. Our first question focuses on `main-two-cvs-while.c` (the working solution). First, study the code. Do you think you have an understanding of what should happen when you run the program?

2. Run with one producer and one consumer, and have the producer
produce a few values. Start with a buffer (size 1), and then increase
it. How does the behavior of the code change with larger buffers?
(or does it?) What would you predict num full to be with different
buffer sizes (e.g., `-m 10`) and different numbers of produced items
(e.g.,` -l 100`), when you change the consumer sleep string from
default (no sleep) to `-C 0,0,0,0,0,0,1`?
3. If possible, run the code on different systems (e.g., a Mac and Linux).
Do you see different behavior across these systems?
4. Let’s look at some timings. How long do you think the following execution, with one producer, three consumers, a single-entry shared buffer, and each consumer pausing at point `c3` for a second, will take?
`./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v -t`
5. Now change the size of the shared buffer to 3 (`-m 3`). Will this make
any difference in the total time?
6. Now change the location of the sleep to c6 (this models a consumer taking something off the queue and then doing something
with it), again using a single-entry buffer. What time do you predict in this case?
`./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10 -v -t`
7. Finally, change the buffer size to 3 again (`-m 3`). What time do you predict now?