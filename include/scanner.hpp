#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>

enum ScanMode {
    SCAN_MODE_TCP,
    SCAN_MODE_ICMP,
    SCAN_MODE_ARP
};

struct ScanResult {
    std::string ip;
    bool is_active;
    std::vector<int> open_ports;
    std::string mac_address;
};

class ScannerEngine {
public:
    ScannerEngine();
    ~ScannerEngine();
    // Now accepts a subnet and a port range (min to max) and a ScanMode
    std::vector<ScanResult> scan_subnet(const std::string& subnet, ScanMode mode = SCAN_MODE_TCP, int min_port = 1, int max_port = 1024);
    bool probe_tcp_port(const std::string& ip, int port);
    bool icmp_ping(const std::string& ip);
    static std::string format_as_json(const std::vector<ScanResult>& results);
};

#endif // SCANNER_HPP
