# CSE221BKL
===========

**Project Description**

In building an operating system, it is important to be able to determine the performance characteristics of underlying hardware components (CPU, RAM, disk, network, etc.), and to understand how their performance influences or constrains operating system services. 

This project has two parts. First, you will implement and perform a series of experiments. Second, you will write a report documenting the methodology and results of your experiments. When you finish, you will submit your report as well as the code used to perform your experiments.


**Operations**

***CPU, Scheduling, and OS Services***

Measurement overhead: Report the overhead of reading time, and report the overhead of using a loop to measure many iterations of an operation.

Procedure call overhead: Report as a function of number of integer arguments from 0-7. What is the increment overhead of an argument?

System call overhead: 

Report the cost of a minimal system call. How does it compare to the cost of a procedure call? Note that some operating systems will cache the results of some system calls (e.g., idempotent system calls like getpid), so only the first call by a process will actually trap into the OS.
Task creation time: Report the time to create and run both a process and a kernel thread (kernel threads run at user-level, but they are created and managed by the OS; e.g., pthread_create on modern Linux will create a kernel-managed thread). How do they compare?

Context switch time: 

Report the time to context switch from one process to another, and from one kernel thread to another. How do they compare? In the past students have found using blocking pipes to be useful for forcing context switches.

***Memory***

RAM access time: 

Report latency for individual integer accesses to main memory and the L1 and L2 caches. Present results as a graph with the x-axis as the log of the size of the memory region accessed, and the y-axis as the average latency. Note that the lmbench paper is a good reference for this experiment. In terms of the lmbench paper, measure the "back-to-back-load" latency and report your results in a graph similar to Fig. 1 in the paper. You should not need to use information about the machine or the size of the L1, L2, etc., caches when implementing the experiment; the experiment will reveal these sizes. In your graph, label the places that indicate the different hardware regimes (L1 to L2 transition, etc.).

RAM bandwidth:

Report bandwidth for both reading and writing. Use loop unrolling to get more accurate results, and keep in mind the effects of cache line prefetching (e.g., see the lmbench paper).
Page fault service time: Report the time for faulting an entire page from disk (mmap is one useful mechanism). Dividing by the size of a page, how does it compare to the latency of accessing a byte from main memory?

***Network***

Round trip time: 

Compare with the time to perform a ping (ICMP requests are handled at kernel level).

Peak bandwidth:

Connection overhead: 

Report setup and tear-down. Evaluate for the TCP protocol. For each quantity, compare both remote and loopback interfaces. Comparing the remote and loopback results, what can you deduce about baseline network performance and the overhead of OS software? For both round trip time and bandwidth, how close to ideal hardware performance do you achieve? What are reasons why the TCP performance does not match ideal hardware performance (e.g., what are the pertinent overheads)? In describing your methodology for the remote case, either provide a machine description for the second machine (as above), or use two identical machines.

***File System***

Size of file cache:

Note that the file cache size is determined by the OS and will be sensitive to other load on the machine; for an application accessing lots of file system data, an OS will use a notable fraction of main memory (GBs) for the file system cache. Report results as a graph whose x-axis is the size of the file being accessed and the y-axis is the average read I/O time. Do not use a system call or utility program to determine this metric except to sanity check.

File read time: 

Report for both sequential and random access as a function of file size. Discuss the sense in which your "sequential" access might not be sequential. Ensure that you are not measuring cached data (e.g., use the raw device interface). Report as a graph with a log/log plot with the x-axis the size of the file and y-axis the average per-block time.

Remote file read time:

Repeat the previous experiment for a remote file system. What is the "network penalty" of accessing files over the network? You can either configure your second machine to provide remote file access, or you can perform the experiment on a department machine (e.g., APE lab). On these machines your home directory is mounted over NFS, so accessing a file under your home directory will be a remote file access (although, again, keep in mind file caching effects).

Contention: 

Report the average time to read one file system block of data as a function of the number of processes simultaneously performing the same operation on different files on the same disk (and not in the file buffer cache).

**How to execute (Raspberry Pi)**

make

./run 


