#ifndef WASTE_PICKUP_CONTROLLER_H
#define WASTE_PICKUP_CONTROLLER_H

#include "../services/WastePickupService.h"

class WastePickupController {
private:
    WastePickupService& service;

public:
    WastePickupController(WastePickupService& service) : service(service) {}

    void createWastePickup(const crow::request& req, crow::response& res) {
        auto body = crow::json::load(req.body);
        if (!body || !body["wasteType"] || !body["pickupLocation"] || !body["pickupDateTime"] || !body["userName"]) {
            res.code = 400;
            res.body = "Invalid request data";
            res.end();
            return;
        }

        WastePickup w = service.addWastePickup(body["wasteType"].s(), body["pickupLocation"].s(), body["pickupDateTime"].s(), body["userName"].s());
        res.code = 201;
        res.write(w.serialize().dump());
        res.end();
    }

    void getAllWastePickups(const crow::request& req, crow::response& res) {
        std::vector<WastePickup> pickups = service.getAllWastePickups();
        crow::json::wvalue response;
        std::vector<crow::json::wvalue> pickupList;

        for (auto& w : pickups) {
            service.updatePickupStatus(w.id); // Auto-update status
            pickupList.push_back(w.serialize());
        }

        response["wastePickups"] = std::move(pickupList);
        res.write(response.dump());
        res.end();
    }

    void updateWastePickup(const crow::request& req, crow::response& res, int id) {
    auto body = crow::json::load(req.body);
    if (!body) {
        res.code = 400;
        res.body = "Invalid request data";
        res.end();
        return;
    }

    std::string newDateTime = body.has("pickupDateTime") ? std::string(body["pickupDateTime"].s()) : "";
    std::string newStatus = body.has("status") ? std::string(body["status"].s()) : "";

    if (service.updateWastePickup(id, newDateTime, newStatus)) {
        res.code = 200;
        res.body = "Updated";
    } else {
        res.code = 404;
        res.body = "Not found";
    }
    res.end();
}

    void deleteWastePickup(const crow::request& req, crow::response& res, int id) {
        if (service.deleteWastePickup(id)) {
            res.code = 200;
            res.body = "Deleted";
        } else {
            res.code = 404;
            res.body = "Not found";
        }
        res.end();
    }
};

#endif
