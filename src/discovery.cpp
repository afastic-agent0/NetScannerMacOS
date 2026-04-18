#include "discovery.hpp"
#include "scanner.hpp"
#include "arp_scanner.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <pcap.h>
#include <chrono>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

DiscoveryModule::DiscoveryModule() {
    std::cout << "[DiscoveryModule] Initialized." << std::endl;
}

DiscoveryModule::~DiscoveryModule() {
    std::cout << "[DiscoveryModule] Destroyed." << std::endl;
}

std::vector<std::string> DiscoveryModule::get_interfaces() {
    std::vector<std::string> interfaces;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs, *device;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "[DiscoveryModule] Error in pcap_findalldevs: " << errbuf << std::endl;
        return interfaces;
    }

    for (device = alldevs; device != nullptr; device = device->next) {
        interfaces.push_back(std::string(device->name));
    }

    pcap_freealldevs(alldevs);
    return interfaces;
}

bool DiscoveryModule::check_port(const std::string& ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return false;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000; // 100ms timeout
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));

    bool is_open = (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0);

    close(sock);
    return is_open;
}

std::vector<std::string> DiscoveryModule::scan_hosts(const std::string& subnet) {
    std::cout << "[DiscoveryModule] Starting synchronous scan for: " << subnet << "..." << std::endl;
    std::vector<std::string> active_hosts;

    // Integration of ARP Scanning via ScannerEngine
    ScannerEngine engine;
    auto arp_results = engine.scan_subnet(subnet, SCAN_MODE_ARP);

    if (!arp_results.empty()) {
        for (const auto& res : arp_results) {
            active_hosts.push_back(res.ip);
        }
    } else {
        // Fallback to loopback if ARP scan finds nothing (as in the PoC logic)
        active_hosts.push_back("127.0.0.1");
    }

    return active_hosts;
}

void DiscoveryModule::probe_interface(const std::string& interface) {
    std::cout << "[DiscoveryModule] Probing interface: " << interface << std::endl;
}
