# Linux-IPC
This is a collection of mini-projects I did while learning Linux inter-process communication (IPC).

## Resources used
* "Linux Inter Process Communication (IPC) from Scratch" course on [Udemy](https://www.udemy.com/linuxipc) by Abhishek Sagar
* [The Linux Programming Interface](http://man7.org/tlpi) by Michael Kerrisk

## Structure
This repo contains several projects (each of them has a README providing more information), organized as follows:

* [`posix_message_queues`](https://github.com/alexandra-zaharia/Linux-IPC/tree/master/posix_message_queues) -- IPC via POSIX message queues (the server process receives integers sent by the client process)

* [`posix_shared_memory`](https://github.com/alexandra-zaharia/Linux-IPC/tree/master/posix_shared_memory) -- IPC via POSIX shared memory (the reader processes receive integers sent by the writer process)

* [`routing_table_manager`](https://github.com/alexandra-zaharia/Linux-IPC/tree/master/routing_table_manager) -- IPC via UNIX domain sockets, signals, and shared memory (the server process maintains a routing table that is synchronized across all clients)

* [`unix_domain_sockets`](https://github.com/alexandra-zaharia/Linux-IPC/tree/master/unix_domain_sockets) -- IPC via stream-based UNIX domain sockets (the server process computes sums of values that are sent out by clients)

## Compiling and running the code examples

Binaries can be compiled using `cmake` and `make`, as follows:
