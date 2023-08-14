#include "libasyik/service.hpp"
#include "libasyik/http.hpp"
#include "opencv4/opencv2/core.hpp"

int main() {
    auto as = asyik::make_service();
    auto server = asyik::make_http_server(as, "127.0.0.1", 8080);

    server->on_http_request("/resize_image", "POST", [](auto req, auto args) {
        req->response.body = "{\"value\":\"Hello " + args[1] + "!\"}";
        LOG(INFO) << "X-Asyik = " << req->headers["x-asyik"] << "\n";
        LOG(INFO) << "Body = " << req->body << "\n";

        req->response.headers.set("x-asyik-reply", "ok");
        req->response.headers.set("content-type", "test/json");

        req->response.result(200);
    });

    as->run();

    return 0;
}