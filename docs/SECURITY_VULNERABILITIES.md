# Security Vulnerability Report

This document details the security vulnerabilities and potential issues identified during a security audit of the NetScannerMacOS codebase.

## Executive Summary

The NetScannerMacOS project is currently in a Proof-of Concept (PoC) stage, primarily designed for localized scanning of `127.0.0.1`. While the current scope limits exposure, several vulnerabilities were identified that could pose significant risks if the tool is expanded to support external network ranges or user-provided inputs without proper hardening.

The identified issues range from **High Severity** (potential for unintended connections and data corruption) to **Low Severity** (build configuration and logging concerns).

---

## High-Severity Vulnerabilities

### 1. Unchecked IP Address Parsing (Uninitialized Memory Usage)
*   **Location:** `src/discovery.cpp`, `check_port` function.
*   **Description:** The `inet_pton` call does not validate its return value. If an invalid or malformed IP string is provided, the `sin_addr` structure remains uninitialized.
*   **Impact:** Attempting to connect using uninitialized memory can lead to connections to random/unintended IP addresses, potentially exposing sensitive local services to unauthorized probing.
*   **Mitigation:** Implement a check on the return value of `inet_pton`. If it is `<= 0`, the function should abort the connection attempt immediately.

### 2. Malformed JSON Output (Injection/Format String Risk)
*   **Location:** `src/scanner.cpp`, `format_as_json` function.
*   **Description:** JSON output is manually constructed using string concatenation. There is no escaping of special characters (e.g., `"`, `\`) within the data fields.
*   **Impact:** If user-controlled data (like hostnames) is introduced, an attacker could inject malicious JSON structures, causing parsing failures or downstream injection attacks in tools consuming the `scan_results.json`.
*   **Mitigation:** Integrate a robust JSON library such as `nlohmann/json` to handle serialization and automatic character escaping.

---

## Medium-Severity Issues

### 1. Lack of Input Validation (Improper Input Handling)
*   **Location:** Throughout `src/scanner.cpp` and `src/main.cpp`.
*   **Description:** There are no bounds checks for port ranges or subnet inputs. While currently hardcoded, any future expansion to user input lacks validation.
*   **Impact:** Maliciously crafted inputs (e.g., extreme port ranges) could lead to resource exhaustion, application crashes, or infinite loops.
*   **Mitigation:** Implement strict bounds checking for all network parameters (e.g., ensuring ports are within the `1-65535` range).

### 2. Synchronous Scanning Bottlenecks (Potential DoS)
*   **Location:** `src/scanner.cpp`, `scan_subnet` and `probe_tcp_port`.
*   **Description:** The scanner uses blocking TCP connections sequentially. While effective for small local ranges, it is inefficient for larger targets.
*   **Impact:** Large-scale scans could inadvertently trigger Denial-of-Service (DoS) conditions on target services by overwhelming them with connection requests in a tight loop.
*   **Mitigation:** Transition to an asynchronous scanning model (using threads or `epoll`/`kqueue`) and implement rate limiting.

### 3. Unused libpcap Dependency (Privilege Escalation Risk)
*   **Location:** `CMakeLists.txt` and `src/discovery.cpp`.
*   **Description:** The project links to `libpcap`, but currently only uses it for interface listing, not packet capture.
*   **Impact:** If the binary is run with elevated privileges (required for raw sockets), the presence of unused sniffing capabilities increases the attack surface for privilege escalation.
*   **Mitigation:** Remove the `libpcap` dependency if packet capture functionality is not implemented, or ensure strict privilege dropping.

---

## Low-Severity Issues

### 1. Hardcoded Library Path in Build
*   **Location:** `CMakeLists.txt`.
*   **Description:** The `PKG_CONFIG_PATH` is hardcoded to a specific directory, assuming a standard Homebrew installation.
*   **Impact:** Reduced portability and potential build failures on non-standard or different macOS environments.
*   **Mitigation:** Rely on standard `pkg-config` search paths.

### 2. Insufficient Error Handling for Socket Operations
*   **Location:** `src/scanner.cpp`, `src/discovery.cpp`.
*   **Description:** Critical socket operations like `socket()` and `setsockopt()` do not always have comprehensive error logging.
*   **Impact:** Silent failures can make debugging difficult and mask underlying network or resource issues.
*   **Mitigation:** Ensure all system call return values are checked and logged via the `Logger` class.

### /3. Lack of Automated Testing
*   **Location:** `tests/` directory.
*   **Description:** The current test suite is empty.
*   **Impact:** High risk of regressions and undetected vulnerabilities during future development.
*   **Mitigation:** Implement unit tests for IP parsing, port range validation, and JSON formatting.

---

## Recommendations Summary

1.  **Immediate Action:** Fix the `inet_pton` return value check in `discovery.cpp`.
2.  **Structural Change:** Replace manual JSON string building with a dedicated library (`nlohmann/json`).
3.  **Hardening:** Implement robust input validation and error handling for all network-facing code.
4.  **Testing:** Build a comprehensive test suite to validate security-critical components.
