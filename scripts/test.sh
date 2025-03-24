#!/bin/bash

# Test script for SSH Connection Tracker
echo "Starting SSH Connection Tracker test..."

# Build the program
make clean && make
if [ $? -ne 0 ]; then
    echo "Build failed! Exiting."
    exit 1
fi

echo "Running SSH Connection Tracker..."
./ssh_audit &
AUDIT_PID=$!
sleep 2

# Simulate SSH connections
echo "Simulating SSH connections..."
ssh localhost -p 22 -o StrictHostKeyChecking=no -o ConnectTimeout=2 exit

# Allow time for the eBPF program to capture events
sleep 5

# Stop the tracker
echo "Stopping SSH Connection Tracker..."
kill $AUDIT_PID

# Check logs or output manually
echo "Test completed. Check the output above for SSH tracking results."

