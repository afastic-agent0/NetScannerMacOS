# Technical Specification: ARP Scanning Module for NetScannerMacOS

## Overview
The goal is to add a new scanning capability to the `NetScannerMacOS` project: Address Resolution Protocol (ARP) scanning. This module will allow the scanner to discover active devices on the local network segment by sending ARP requests and analyzing the replies.

## Objectives
1. Implement an ARP scanning mechanism using raw sockets or `libpcap`.
2. Integrate the new module into the existing `Scanner` class architecture.
3. Ensure the results are properly formatted and passed to the `Reporter` module.
4. Maintain compliance with existing project constraints (synchronous execution, minimal target probes).

## Technical Requirements

### 1. Core Logic (`src/arp_scanner.cpp`)
- **Mechanism**: Use `libpcap` or raw sockets (`AF_PACKET`, `SOCK_RAW`) to broadcast ARP requests.
- **Targeting**: The module should scan the local subnet based on the user-defined range (defaulting to a single interface's subnet).
- **Protocol**:
    - Construct an Ethernet frame with a broadcast MAC address (`ff:ff:ff:ff:ϕ:ff`).
    - Construct an ARP packet containing the sender's MAC and IP, and the target's IP.
    - Listen for incoming ARP replies (`op=2`) matching the sent requests.

### 2. Integration Points
- **`include/scanner.hpp`**: Update the `Scanner` interface to include a new scanning mode: `SCAN_MODE_ARP`.
- **`src/scanner.cpp`**: Implement the logic to dispatch the ARP scan task when the mode is selected.
- **`src/discovery.cpp`**: The discovery engine should call the new ARP module during the discovery phase.

### 3. Data Structures
- **`struct ArpResult`**:
    - `std::string ip_address`
    - `std::string mac_address`
    - `std::chrono::steady_clock::time_point timestamp`

### 4. Constraints & Safety
- **Timeout**: The scan must complete within a reasonable timeframe to avoid the 60s watchdog timeout.
- **Synchronous execution**: No background threads for the scanning loop; use a blocking listen with a timeout.
- **No External IPs**: Do not attempt to ARP scan outside the local network interface range.

## Implementation Steps for Claude Code
1. Create `src/arp_scanner.cpp` and `include/arp_scanner.hpp`.
2. Update `include/scanner.hpp` to include `SCAN_MODE_ARP`.
3. Update `src/scanner.cpp` to handle the new mode.
4. Update `src/discovery.cpp` to invoke the ARP scanner.
5. Update `CMakeLists.txt` to include the new source files.
6. Add a basic test case in `tests/` to verify the module compiles and runs.

## Verification Plan (To be performed by Hermes)
- [ ] Compile project using `cmake`.
- [ ] Run existing test suite to ensure no regressions.
- [ ] Execute a manual scan test on `127.0.0.1` or local subnet if possible.
