#ifndef WASTE_PICKUP_H
#define WASTE_PICKUP_H

#include <string>
#include <crow.h>

class WastePickup {
public:
    int id;
    std::string wasteType;
    std::string pickupLocation;
    std::string pickupDateTime;
    std::string status;
    std::string userName;

    WastePickup(int id, std::string wasteType, std::string pickupLocation, std::string pickupDateTime, std::string userName)
        : id(id), wasteType(wasteType), pickupLocation(pickupLocation), pickupDateTime(pickupDateTime), status("Pending"), userName(userName) {}

    crow::json::wvalue serialize() const {
        return crow::json::wvalue({
            {"id", id},
            {"wasteType", wasteType},
            {"pickupLocation", pickupLocation},
            {"pickupDateTime", pickupDateTime},
            {"status", status},
            {"userName", userName}
        });
    }
};

#endif
