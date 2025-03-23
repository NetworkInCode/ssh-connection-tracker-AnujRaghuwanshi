/* main.c - User-space program to load eBPF and interact with it */
#include <stdio.h>
#include <stdlib.h>
#include <bpf/libbpf.h>
#include <unistd.h>
#include <signal.h>

#include "bpf_prog.skel.h"

static volatile int keep_running = 1;

void sigint_handler(int sig) {
    keep_running = 0;
}

int main() {
    struct bpf_prog *skel;
    int err;

    signal(SIGINT, sigint_handler);

    skel = bpf_prog__open_and_load();
    if (!skel) {
        fprintf(stderr, "Failed to load eBPF program\n");
        return 1;
    }

    err = bpf_prog__attach(skel);
    if (err) {
        fprintf(stderr, "Failed to attach eBPF program\n");
        goto cleanup;
    }

    printf("Tracking SSH connections... Press Ctrl+C to exit.\n");
    while (keep_running) {
        sleep(1);
    }

cleanup:
    bpf_prog__destroy(skel);
    return 0;
}

