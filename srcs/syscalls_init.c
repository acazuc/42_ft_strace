#include "ft_strace.h"

t_syscall *g_syscalls;

void syscalls_init(void)
{
	t_syscall syscalls[] = {{3, "read", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{3, "write", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{3, "open", {PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{1, "close", {PARAM_NUMBER}},
		{2, "stat", {PARAM_STRING, PARAM_ADDR}},
		{2, "fstat", {PARAM_NUMBER, PARAM_ADDR}},
		{2, "lstat", {PARAM_STRING, PARAM_ADDR}},
		{3, "poll", {PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "lseek", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{6, "mmap", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "mprotect", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "munmap", {PARAM_NUMBER, PARAM_NUMBER}},
		{1, "brk", {PARAM_ADDR}},
		{4, "rt_sigaction", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{4, "rt_sigprocmask", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{1, "rt_sigreturn", {PARAM_NUMBER}},
		{3, "ioctl", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "pread64", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "pwrite64", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "readv", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{3, "writev", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{2, "access", {PARAM_STRING, PARAM_NUMBER}},
		{1, "pipe", {PARAM_ADDR}},
		{5, "select", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_ADDR, PARAM_ADDR}},
		{0, "sched_yield", {}},
		{5, "mremap", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "msync", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "mincore", {PARAM_NUMBER, PARAM_NUMBER, PARAM_STRING}},
		{3, "madvise", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "shmget", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "shmat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{3, "shmctl", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{1, "dup", {PARAM_NUMBER}},
		{2, "dup2", {PARAM_NUMBER, PARAM_NUMBER}},
		{0, "pause", {}},
		{2, "nanosleep", {PARAM_ADDR, PARAM_ADDR}},
		{2, "getitimer", {PARAM_NUMBER, PARAM_ADDR}},
		{1, "alarm", {PARAM_NUMBER}},
		{3, "setitimer", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{0, "getpid", {}},
		{4, "sendfile", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{3, "socket", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "connect", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{3, "accept", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{6, "sendto", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{6, "recvfrom", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{3, "sendmsg", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{3, "recvmsg", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{2, "shutdown", {PARAM_NUMBER, PARAM_NUMBER}},
		{3, "bind", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{2, "listen", {PARAM_NUMBER, PARAM_NUMBER}},
		{3, "getsockname", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{3, "getpeername", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{4, "socketpair", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{5, "setsockopt", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{5, "getsockopt", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_STRING, PARAM_ADDR}},
		{4, "clone", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{0, "fork", {}},
		{0, "vfork", {}},
		{3, "execve", {PARAM_STRING, PARAM_ADDR, PARAM_ADDR}},
		{1, "exit", {PARAM_NUMBER}},
		{4, "wait4", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR}},
		{2, "kill", {PARAM_NUMBER, PARAM_NUMBER}},
		{1, "uname", {PARAM_ADDR}},
		{3, "semget", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "semop", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{4, "semctl", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{1, "shmdt", {PARAM_STRING}},
		{2, "msgget", {PARAM_NUMBER, PARAM_NUMBER}},
		{4, "msgsnd", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "msgrcv", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "msgctl", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{3, "fcntl", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "flock", {PARAM_NUMBER, PARAM_NUMBER}},
		{1, "fsync", {PARAM_NUMBER}},
		{1, "fdatasync", {PARAM_NUMBER}},
		{2, "truncate", {PARAM_STRING, PARAM_NUMBER}},
		{2, "ftruncate", {PARAM_NUMBER, PARAM_NUMBER}},
		{3, "getdents", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{2, "getcwd", {PARAM_STRING, PARAM_NUMBER}},
		{1, "chdir", {PARAM_STRING}},
		{1, "fchdir", {PARAM_NUMBER}},
		{2, "rename", {PARAM_STRING, PARAM_STRING}},
		{2, "mkdir", {PARAM_STRING, PARAM_NUMBER}},
		{1, "rmdir", {PARAM_STRING}},
		{2, "creat", {PARAM_STRING, PARAM_NUMBER}},
		{2, "link", {PARAM_STRING, PARAM_STRING}},
		{1, "unlink", {PARAM_STRING}},
		{2, "symlink", {PARAM_STRING, PARAM_STRING}},
		{3, "readlink", {PARAM_STRING, PARAM_STRING, PARAM_NUMBER}},
		{2, "chmod", {PARAM_STRING, PARAM_NUMBER}},
		{2, "fchmod", {PARAM_NUMBER, PARAM_NUMBER}},
		{3, "chown", {PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "fchown", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "lchown", {PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{1, "umask", {PARAM_NUMBER}},
		{2, "gettimeofday", {PARAM_ADDR, PARAM_ADDR}},
		{2, "getrlimit", {PARAM_NUMBER, PARAM_ADDR}},
		{2, "getrusage", {PARAM_NUMBER, PARAM_ADDR}},
		{1, "sysinfo", {PARAM_ADDR}},
		{1, "times", {PARAM_ADDR}},
		{4, "ptrace", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{0, "getuid", {}},
		{3, "syslog", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{0, "getgid", {}},
		{1, "setuid", {PARAM_NUMBER}},
		{1, "setgid", {PARAM_NUMBER}},
		{0, "geteuid", {}},
		{0, "getegid", {}},
		{2, "setpgid", {PARAM_NUMBER, PARAM_NUMBER}},
		{0, "getppid", {}},
		{0, "getpgrp", {}},
		{0, "setsid", {}},
		{2, "setreuid", {PARAM_NUMBER, PARAM_NUMBER}},
		{2, "setregid", {PARAM_NUMBER, PARAM_NUMBER}},
		{2, "getgroups", {PARAM_NUMBER, PARAM_ADDR}},
		{2, "setgroups", {PARAM_NUMBER, PARAM_ADDR}},
		{3, "setresuid", {PARAM_ADDR, PARAM_ADDR, PARAM_ADDR}},
		{3, "getresuid", {PARAM_ADDR, PARAM_ADDR, PARAM_ADDR}},
		{3, "setresgid", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "getresgid", {PARAM_ADDR, PARAM_ADDR, PARAM_ADDR}},
		{1, "getpgid", {PARAM_NUMBER}},
		{1, "setfsuid", {PARAM_NUMBER}},
		{1, "setfsgid", {PARAM_NUMBER}},
		{1, "getsid", {PARAM_NUMBER}},
		{2, "capget", {PARAM_NUMBER, PARAM_NUMBER}},
		{2, "capset", {PARAM_NUMBER, PARAM_NUMBER}},
		{2, "rt_sigpending", {PARAM_ADDR, PARAM_NUMBER}},
		{4, "rt_sigtimedwait", {PARAM_ADDR, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{3, "rt_sigqueueinfo", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{2, "rt_sigsuspend", {PARAM_ADDR, PARAM_NUMBER}},
		{2, "sigaltstack", {PARAM_ADDR, PARAM_ADDR}},
		{2, "utime", {PARAM_STRING, PARAM_ADDR}},
		{3, "mknod", {PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{1, "uselib", {PARAM_NUMBER}},
		{1, "personality", {PARAM_NUMBER}},
		{2, "ustat", {PARAM_NUMBER, PARAM_ADDR}},
		{2, "statfs", {PARAM_STRING, PARAM_ADDR}},
		{2, "fstatfs", {PARAM_NUMBER, PARAM_ADDR}},
		{3, "sysfs", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "getpriority", {PARAM_NUMBER, PARAM_NUMBER}},
		{3, "setpriority", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "sched_setparam", {PARAM_NUMBER, PARAM_ADDR}},
		{2, "sched_getparam", {PARAM_NUMBER, PARAM_ADDR}},
		{3, "sched_setscheduler", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{1, "sched_getscheduler", {PARAM_NUMBER}},
		{1, "sched_get_priority_max", {PARAM_NUMBER}},
		{1, "sched_get_priority_min", {PARAM_NUMBER}},
		{2, "sched_rr_get_interval", {PARAM_NUMBER, PARAM_ADDR}},
		{2, "mlock", {PARAM_NUMBER, PARAM_NUMBER}},
		{2, "munlock", {PARAM_NUMBER, PARAM_NUMBER}},
		{1, "mlockall", {PARAM_NUMBER}},
		{0, "munlockall", {}},
		{0, "vhangup", {}},
		{3, "modify_ldt", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{2, "pivot_root", {PARAM_STRING, PARAM_STRING}},
		{1, "_sysctl", {PARAM_ADDR}},
		{5, "prctl", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "arch_prctl", {PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR}},
		{1, "adjtimex", {PARAM_ADDR}},
		{2, "setrlimit", {PARAM_NUMBER, PARAM_ADDR}},
		{1, "chroot", {PARAM_STRING}},
		{0, "sync", {}},
		{1, "acct", {PARAM_STRING}},
		{2, "settimeofday", {PARAM_ADDR, PARAM_ADDR}},
		{5, "mount", {PARAM_STRING, PARAM_STRING, PARAM_STRING, PARAM_NUMBER, PARAM_ADDR}},
		{2, "umount2", {PARAM_STRING, PARAM_NUMBER}},
		{2, "swapon", {PARAM_STRING, PARAM_NUMBER}},
		{1, "swapoff", {PARAM_STRING}},
		{4, "reboot", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{2, "sethostname", {PARAM_STRING, PARAM_NUMBER}},
		{2, "setdomainname", {PARAM_STRING, PARAM_NUMBER}},
		{2, "iopl", {PARAM_NUMBER, PARAM_ADDR}},
		{3, "ioperm", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{1, "create_module", {PARAM_NUMBER}},
		{3, "init_module", {PARAM_ADDR, PARAM_NUMBER, PARAM_STRING}},
		{2, "delete_module", {PARAM_ADDR, PARAM_NUMBER}},
		{1, "get_kernel_syms", {PARAM_NUMBER}},
		{1, "query_module", {PARAM_NUMBER}},
		{4, "quotactl", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_ADDR}},
		{1, "nfsservctl", {PARAM_NUMBER}},
		{1, "getpmsg", {PARAM_NUMBER}},
		{1, "putpmsg", {PARAM_NUMBER}},
		{1, "afs_syscall", {PARAM_NUMBER}},
		{1, "tuxcall", {PARAM_NUMBER}},
		{1, "security", {PARAM_NUMBER}},
		{0, "gettid", {}},
		{3, "readahead", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "setxattr", {PARAM_STRING, PARAM_STRING, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "lsetxattr", {PARAM_STRING, PARAM_STRING, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "fsetxattr", {PARAM_NUMBER, PARAM_STRING, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "getxattr", {PARAM_STRING, PARAM_STRING, PARAM_ADDR, PARAM_NUMBER}},
		{4, "lgetxattr", {PARAM_STRING, PARAM_STRING, PARAM_ADDR, PARAM_NUMBER}},
		{4, "fgetxattr", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{3, "listxattr", {PARAM_STRING, PARAM_STRING, PARAM_NUMBER}},
		{3, "llistxattr", {PARAM_STRING, PARAM_STRING, PARAM_NUMBER}},
		{3, "flistxattr", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{2, "removexattr", {PARAM_STRING, PARAM_STRING}},
		{2, "lremovexattr", {PARAM_STRING, PARAM_STRING}},
		{2, "fremovexattr", {PARAM_NUMBER, PARAM_STRING}},
		{2, "tkill", {PARAM_NUMBER, PARAM_NUMBER}},
		{1, "time", {PARAM_ADDR}},
		{6, "futex", {PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{3, "sched_setaffinity", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{3, "sched_getaffinity", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{1, "set_thread_area", {PARAM_NUMBER}},
		{2, "io_setup", {PARAM_NUMBER, PARAM_ADDR}},
		{1, "io_destroy", {PARAM_NUMBER}},
		{4, "io_getevents", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{3, "io_submit", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{3, "io_cancel", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{1, "get_thread_area", {PARAM_NUMBER}},
		{3, "lookup_dcookie", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{1, "epoll_create", {PARAM_NUMBER}},
		{1, "epoll_ctl_old", {PARAM_NUMBER}},
		{1, "epoll_wait_old", {PARAM_NUMBER}},
		{5, "remap_file_pages", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "getdents64", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{1, "set_tid_address", {PARAM_ADDR}},
		{0, "restart_syscall", {}},
		{4, "semtimedop", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR}},
		{4, "fadvise64", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "timer_create", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{4, "timer_settime", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{2, "timer_gettime", {PARAM_NUMBER, PARAM_ADDR}},
		{1, "timer_getoverrun", {PARAM_NUMBER}},
		{1, "timer_delete", {PARAM_NUMBER}},
		{2, "clock_settime", {PARAM_NUMBER, PARAM_ADDR}},
		{2, "clock_gettime", {PARAM_NUMBER, PARAM_ADDR}},
		{2, "clock_getres", {PARAM_NUMBER, PARAM_ADDR}},
		{4, "clock_nanosleep", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{1, "exit_group", {PARAM_NUMBER}},
		{4, "epoll_wait", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "epoll_ctl", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{3, "tgkill", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "utimes", {PARAM_STRING, PARAM_ADDR}},
		{1, "vserver", {PARAM_NUMBER}},
		{6, "mbind", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "set_mempolicy", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{5, "get_mempolicy", {PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "mq_open", {PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{1, "mq_unlink", {PARAM_STRING}},
		{5, "mq_timedsend", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{5, "mq_timedreceive", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{2, "mq_notify", {PARAM_NUMBER, PARAM_ADDR}},
		{3, "mq_getsetattr", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{4, "kexec_load", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{5, "waitid", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR}},
		{4, "add_key", {PARAM_STRING, PARAM_STRING, PARAM_ADDR, PARAM_NUMBER}},
		{4, "request_key", {PARAM_STRING, PARAM_STRING, PARAM_STRING, PARAM_NUMBER}},
		{5, "keyctl", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "ioprio_set", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "ioprio_get", {PARAM_NUMBER, PARAM_NUMBER}},
		{0, "inotify_init", {}},
		{3, "inotify_add_watch", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{2, "inotify_rm_watch", {PARAM_NUMBER, PARAM_NUMBER}},
		{4, "migrate_pages", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{4, "openat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "mkdirat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{4, "mknodat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "fchownat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "futimesat", {PARAM_NUMBER, PARAM_STRING, PARAM_ADDR}},
		{4, "newfstatat", {PARAM_NUMBER, PARAM_STRING, PARAM_ADDR, PARAM_NUMBER}},
		{3, "unlinkat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{4, "renameat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_STRING}},
		{5, "linkat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{3, "symlinkat", {PARAM_STRING, PARAM_NUMBER, PARAM_STRING}},
		{4, "readlinkat", {PARAM_NUMBER, PARAM_STRING, PARAM_STRING, PARAM_NUMBER}},
		{3, "fchmodat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{3, "faccessat", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{6, "pselect6", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_ADDR, PARAM_ADDR, PARAM_ADDR}},
		{5, "ppoll", {PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{1, "unshare", {PARAM_NUMBER}},
		{2, "set_robust_list", {PARAM_ADDR, PARAM_NUMBER}},
		{3, "get_robust_list", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{6, "splice", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "tee", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "sync_file_range", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "vmsplice", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{6, "move_pages", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{4, "utimensat", {PARAM_NUMBER, PARAM_STRING, PARAM_ADDR, PARAM_NUMBER}},
		{6, "epoll_pwait", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{3, "signalfd", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{2, "timerfd_create", {PARAM_NUMBER, PARAM_NUMBER}},
		{1, "eventfd", {PARAM_NUMBER}},
		{4, "fallocate", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "timerfd_settime", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{2, "timerfd_gettime", {PARAM_NUMBER, PARAM_ADDR}},
		{4, "accept4", {PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{4, "signalfd4", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "eventfd2", {PARAM_NUMBER, PARAM_NUMBER}},
		{1, "epoll_create1", {PARAM_NUMBER}},
		{3, "dup3", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "pipe2", {PARAM_ADDR, PARAM_NUMBER}},
		{1, "inotify_init1", {PARAM_NUMBER}},
		{5, "preadv", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "pwritev", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "rt_tgsigqueueinfo", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{5, "perf_event_open", {PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "recvmmsg", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR}},
		{2, "fanotify_init", {PARAM_NUMBER, PARAM_NUMBER}},
		{5, "fanotify_mark", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{4, "prlimit64", {PARAM_NUMBER, PARAM_NUMBER, PARAM_ADDR, PARAM_ADDR}},
		{5, "name_to_handle_at", {PARAM_NUMBER, PARAM_STRING, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{5, "open_by_handle_at", {PARAM_NUMBER, PARAM_STRING, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{2, "clock_adjtime", {PARAM_NUMBER, PARAM_ADDR}},
		{1, "syncfs", {PARAM_NUMBER}},
		{4, "sendmmsg", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "setns", {PARAM_NUMBER, PARAM_NUMBER}},
		{3, "getcpu", {PARAM_ADDR, PARAM_ADDR, PARAM_ADDR}},
		{6, "process_vm_readv", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{6, "process_vm_writev", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "kcmp", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{3, "finit_module", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{3, "sched_setattr", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{4, "sched_getattr", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{5, "renameat2", {PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{3, "seccomp", {PARAM_NUMBER, PARAM_NUMBER, PARAM_STRING}},
		{3, "getrandom", {PARAM_STRING, PARAM_NUMBER, PARAM_NUMBER}},
		{2, "memfd_create", {PARAM_STRING, PARAM_NUMBER}},
		{5, "kexec_file_load", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_STRING, PARAM_NUMBER}},
		{3, "bpf", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER}},
		{5, "stub_execveat", {PARAM_NUMBER, PARAM_STRING, PARAM_ADDR, PARAM_ADDR, PARAM_NUMBER}},
		{1, "userfaultfd", {PARAM_NUMBER}},
		{2, "membarrier", {PARAM_NUMBER, PARAM_NUMBER}},
		{3, "mlock2", {PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{6, "copy_file_range", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER}},
		{6, "preadv2", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}},
		{6, "pwritev2", {PARAM_NUMBER, PARAM_ADDR, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER, PARAM_NUMBER}}};
    if (!(g_syscalls = malloc(sizeof(syscalls))))
    {
      	ft_putendl_fd("ft_strace: can't malloc syscalls names", 2);
      	exit(EXIT_FAILURE);
    }
    ft_memcpy(g_syscalls, syscalls, sizeof(syscalls));
}
