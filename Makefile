BPF_OBJ = bpf_prog.bpf.o
USER_BIN = ssh_audit

CC = clang
BPFTOOL = bpftool
LIBBPF_DIR = /usr/lib/libbpf
CFLAGS = -I/usr/include -Wall -O2
LDFLAGS = -lelf -lz -lbpf

all: $(BPF_OBJ) $(USER_BIN)

$(BPF_OBJ): bpf_prog.c
	clang -target bpf -D__KERNEL__ -Wall -O2 -c $< -o $@

$(USER_BIN): main.c $(BPF_OBJ)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(BPF_OBJ) $(USER_BIN)
