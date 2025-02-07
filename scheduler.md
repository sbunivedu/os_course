The program `scheduler.py` allows you to see how different schedulers perform under scheduling metrics such as response time, turnaround time, and total wait time. See the [README](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-sched) for details. Please use `scheduler.py` to run the following experiments and report your findings.
1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.
2. Now do the same but with jobs of different lengths: 100, 200, and 300. 3. Now do the same, but also with the RR scheduler and a time-slice of 1.
3. For what types of workloads does SJF deliver the same turnaround times as FIFO?
4. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?
