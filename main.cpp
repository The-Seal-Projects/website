#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;

    if (!svr.set_mount_point("/", "./public")) {
        std::cerr << "public folder not found. Run ./main from the website folder.\n";
        return 1;
    }

    // Basic GET route
    svr.Get("/hi", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get(R"(/users/(\d+))", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("User ID: " + req.matches[1].str(), "text/plain");
    });

    // Basic POST route
    svr.Post("/data", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("Received: " + req.body, "text/plain");
    });

    std::cout << "Starting server on port 8080...\n";
    if (!svr.listen("0.0.0.0", 8080)) {
        std::cerr << "Failed to bind to port 8080.\n";
        return 1;
    }

    return 0;
}