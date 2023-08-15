#include <charconv>
#include "libasyik/service.hpp"
#include "libasyik/http.hpp"
#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "lib/cpp-base64/base64.h"

// Helper function to resize OpenCV image
cv::Mat resize_img(cv::Mat img, int desired_width, int desired_height) {
    cv::Mat res;
    cv::resize(img, res, cv::Size(desired_width, desired_height), cv::INTER_LINEAR);

    return res;
}

int main() {
    auto as = asyik::make_service();
    auto server = asyik::make_http_server(as, "127.0.0.1", 8080);

    server->on_http_request("/resize_image", "POST", [](auto req, auto args) {
        // Decode base64 image
        std::string dec_jpg = base64_decode(req->body);
        std::vector<uchar> data(dec_jpg.begin(), dec_jpg.end());
        cv::Mat img = cv::imdecode(cv::Mat(data), 1);

        // Resize image
        int desired_width, desired_height;
        std::from_chars(req->headers["desired_width"].data(), req->headers["desired_width"].data() + req->headers["desired_width"].size(), desired_width);
        std::from_chars(req->headers["desired_height"].data(), req->headers["desired_height"].data() + req->headers["desired_height"].size(), desired_height);

        cv::Mat new_img = resize_img(img, desired_width, desired_height);
        
        // Reencode resized image
        std::vector<uchar> buffer;
        cv::imencode(".jpg", new_img, buffer);
        unsigned char *enc_msg = reinterpret_cast<unsigned char *>(buffer.data());

        req->response.body = base64_encode(enc_msg, buffer.size());

        // Set headers
        req->response.headers.set("content-type", "application/json");
        req->response.result(200);
    });

    as->run();

    return 0;
}