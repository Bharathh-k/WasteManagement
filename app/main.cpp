#include <crow.h>
#include "controllers/WastePickupController.h"
#include <fstream>

int main() {
    crow::SimpleApp app;
    WastePickupService service;
    WastePickupController controller(service);

    CROW_ROUTE(app, "/")([]() {
        std::ifstream file("views/index.html");
        if (!file) return crow::response(404, "File Not Found");

        std::stringstream buffer;
        buffer << file.rdbuf();
        return crow::response(buffer.str());
    });

    CROW_ROUTE(app, "/style.css")([]() {
        std::ifstream file("views/style.css");
        if (!file) return crow::response(404, "File Not Found");

        std::stringstream buffer;
        buffer << file.rdbuf();
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/css");
        return res;
    });

    CROW_ROUTE(app, "/script.js")([]() {
        std::ifstream file("views/script.js");
        if (!file) return crow::response(404, "File Not Found");

        std::stringstream buffer;
        buffer << file.rdbuf();
        crow::response res(buffer.str());
        res.set_header("Content-Type", "application/javascript");
        return res;
    });

    CROW_ROUTE(app, "/wastepickuprequest").methods(crow::HTTPMethod::POST)
        ([&controller](const crow::request& req, crow::response& res) {
            controller.createWastePickup(req, res);
        });

    CROW_ROUTE(app, "/wastepickups").methods(crow::HTTPMethod::GET)
        ([&controller](const crow::request& req, crow::response& res) {
            controller.getAllWastePickups(req, res);
        });

    CROW_ROUTE(app, "/wastepickups/<int>").methods(crow::HTTPMethod::PUT)
        ([&controller](const crow::request& req, crow::response& res, int id) {
            controller.updateWastePickup(req, res, id);
        });

    CROW_ROUTE(app, "/wastepickupdelete/<int>").methods(crow::HTTPMethod::DELETE)
        ([&controller](const crow::request& req, crow::response& res, int id) {
            controller.deleteWastePickup(req, res, id);
        });

    app.port(8080).multithreaded().run();
}
