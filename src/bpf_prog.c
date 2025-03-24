/* bpf_prog.c - eBPF program to track SSH connections */
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

struct event_t {
    __u32 pid;
    __u32 uid;
    __u32 gid;
    __u32 saddr;
    __u32 daddr;
    __u16 sport;
    __u16 dport;
};

struct {
    __uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
    __uint(key_size, sizeof(int));
    __uint(value_size, sizeof(int));
} events SEC("maps");

SEC("kprobe/inet_accept")
int BPF_KPROBE(track_ssh_accept, struct socket *sock) {
    struct event_t event = {};
    struct inet_sock *inet = (struct inet_sock *)sock->sk;

    event.pid = bpf_get_current_pid_tgid() >> 32;
    event.uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
    event.sport = BPF_CORE_READ(inet, inet_sport);
    event.dport = BPF_CORE_READ(inet, inet_dport);

    bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU, &event, sizeof(event));
    return 0;
}

char LICENSE[] SEC("license") = "GPL";

