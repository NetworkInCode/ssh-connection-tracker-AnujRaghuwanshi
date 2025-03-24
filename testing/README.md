## Test Environment Setup
The SSH Connection Tracker is designed to run on Linux, utilizing eBPF to track SSH connections in real time. Below are the necessary setup steps:

### System Requirements
- Ubuntu 20.04+ or equivalent Linux distribution
- Kernel version 5.4+ (for eBPF support)
- Clang/LLVM, libbpf, and other dependencies installed:
  ```sh
  sudo apt update && sudo apt install clang llvm libelf-dev libbpf-dev make gcc git -y
  ```
- Root privileges (to run eBPF programs)

---

## Details of the Implementation

### Functions Used
- `track_ssh_connections()`: Monitors active SSH connections.
- `filter_auth_failures()`: Captures SSH authentication failures.
- `log_permission_issues()`: Logs file access permission denials.
- `user_space_display()`: Outputs SSH connection statistics at set intervals.

### eBPF Libraries Used
- **libbpf**: For loading and interacting with eBPF programs.
- **BCC (if used)**: Alternative eBPF framework for monitoring.

### eBPF Hooks Used
- **kprobe**: Hooks into SSH process initiation.
- **tracepoint**: Monitors authentication failures.
- **LSM (Linux Security Module) hooks**: Detects permission errors.

### User-Space Program Details
- Implemented in **C**, interacts with eBPF via **libbpf**.
- Parses collected data and displays stats at configurable intervals.
- Provides options via CLI (e.g., time interval configuration).

---

## Test Cases Covered

| Test Case | Expected Outcome |
|-----------|-----------------|
| Track active SSH connections | Displays IP, client port, and duration |
| Detect multiple concurrent connections from a single client | Identifies and lists duplicate sessions |
| Capture SSH authentication failures | Logs failed login attempts |
| Detect file permission issues for SSH users | Logs permission-denied errors |
| Adjust reporting interval via CLI | Updates display frequency accordingly |

To execute tests, run:
```sh
chmod +x scripts/test.sh
./scripts/test.sh
```

Ensure SSH access is available and check logs for expected outputs.
