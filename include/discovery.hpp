#ifndef DISCOVERY_HPP
#define DISCOVERY_HPP

#include <string>
#include <vector>
#include <pcap.h>

class DiscoveryModule {
public:
    DiscoveryModule();
    ~DiscoveryModule();

    // Returns a list of available network interfaces
    std::vector<std::string> get_interfaces();

    // Phase 3: Scans a specific subnet for active hosts (e.g., "192.168.1.0/24")
    std::vector<std::string> scan_hosts(const std::string& subnet);

    // Phase 3: Checks if a specific port is open on a given IP
    bool check_port(const std::string& ip, int port);

private:
    // Internal method to perform ARP/ICNP probing
    void probe_interface(const std::string& interface);
};

#endif // DISCOVERY_HPP
