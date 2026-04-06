# NetScannerMacOS (PoC)

A lightweight, high-performance network port scanner optimized for macOS (Apple Silicon/Intel). This tool is designed to rapidly probe specific IP addresses and small ranges for open services without triggering system watchdogs.

## 🚀 Key Features
- **High-Speed Probing**: Uses a synchronous TCP connect method with an aggressive 100ms timeout to ensure rapid execution.
- **Structured Reporting**: Generates dual-format output:
  - **Human-Readable**: A clean, formatted summary in the terminal.
  - **Machine-Readable**: A structured `scan_results.json` file for integration with other tools.
- **Robust Logging**: Integrated logging system providing `[INFO]`, `STDOUT`, and `[ERROR]` levels to `stdout` and `stderr`.
- **macOS Optimized**: Specifically configured to handle macOS networking stacks, including support for loopback (`127.0.0.1`) and local interface discovery.

## 🛠 Technical Stack
- **Language**: C++ (Standard 17)
- **Build System**: CMake
- **Dependencies**: `libpcap` (via Homebrew), `pkg-config`

## 📂 Project Structure
- `src/`: Core implementation logic (Scanner Engine, Reporter, Logger).
- `include/`: Header files defining the application's interfaces.
- `build/`: Compiled binaries and build artifacts.
- `scan_results.json`: The output file containing the results of the most recent scan.

## ⚙️ Installation & Build
Ensure you have `cmake` and `libpcap` installed via Homebrew:
```bash
brew install cmake libpcap pkg-config
```

To build the project:
```bash
cd NetScannerMacOS/build
cmake ..
make
```

## 🔍 Usage
The current PoC is configured to perform a high-speed scan of the loopback interface (`127.0.0.1`) across a defined port range (e.g., 1-1500) to detect certain local services.

Run the scanner:
```bash
./netscanner
```

## ⚠️ Operational Constraints (Development Note)
**IMPORTANT**: This tool is optimized for "Fast-Scan" mode. To prevent session timeouts in restricted environments, it currently focuses on targeted IP probes. Expanding to large CIDR ranges (e.g., `/24`) requires implementing asynchronous batching logic to avoid exceeding execution time limits.

***
