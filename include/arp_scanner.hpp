#ifndef ARP_SCANNER_HPP
#define ARP_SCANNER_HPP

#include <string>
#include <vector>
#include <chrono>

struct ArpResult {
    std::string ip_address;
    std::string mac_address;
    std::chrono::steady_clock::time_point timestamp;
};

class ArpScanner {
public:
    ArpScanner();
    ~ArpScanner();

    /**
     * Performs an ARP scan on the specified subnet.
     * @param interface The network interface to use (e.g., "en0").
     * @param subnet The subnet to scan (e.g., "192.16ram.0/24").
     * @param timeout_seconds Timeout for the scan in seconds.
     * @return A vector of ArpResult containing discovered devices.
     */
    std::vector<ArpResult> scan(const std::string& interface, const std::string& subnet, int timeout_seconds = 10);

private:
    // Internal helper to send ARP requests and listen for replies
    // This is a simplified placeholder for the actual implementation
};

#endif // ARP_SCANNER_HPP
