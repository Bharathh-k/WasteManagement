#ifndef WASTE_PICKUP_SERVICE_H
#define WASTE_PICKUP_SERVICE_H

#include "../models/WastePickup.h"
#include <vector>
#include <mutex>
#include <chrono>
#include <ctime>

class WastePickupService {
private:
    std::vector<WastePickup> wastePickups;
    std::mutex mtx;
    int nextId = 1;

public:
    WastePickup addWastePickup(const std::string& wasteType, const std::string& pickupLocation, const std::string& pickupDateTime, const std::string& userName) {
        std::lock_guard<std::mutex> lock(mtx);
        WastePickup w(nextId++, wasteType, pickupLocation, pickupDateTime, userName);
        wastePickups.push_back(w);
        return w;
    }

    std::vector<WastePickup> getAllWastePickups() {
        std::lock_guard<std::mutex> lock(mtx);
        return wastePickups;
    }

    WastePickup* getWastePickupById(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& w : wastePickups) {
            if (w.id == id) return &w;
        }
        return nullptr;
    }

    bool updateWastePickup(int id, const std::string& newPickupDateTime, const std::string& newStatus) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& w : wastePickups) {
            if (w.id == id) {
                if (!newPickupDateTime.empty()) w.pickupDateTime = newPickupDateTime;
                if (!newStatus.empty()) w.status = newStatus;
                return true;
            }
        }
        return false;
    }

    bool deleteWastePickup(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto it = wastePickups.begin(); it != wastePickups.end(); ++it) {
            if (it->id == id) {
                wastePickups.erase(it);
                return true;
            }
        }
        return false;
    }

    void updatePickupStatus(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& w : wastePickups) {
            if (w.id == id) {
                auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::string currentTime = std::ctime(&now);

                // Compare pickup time with current time
                if (w.pickupDateTime < currentTime && w.status != "Completed") {
                    w.status = "Completed";
                }
            }
        }
    }
};

#endif
