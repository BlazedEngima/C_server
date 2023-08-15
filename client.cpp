#include <iostream>
#include "libasyik/service.hpp"
#include "libasyik/http.hpp"
#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/imgcodecs.hpp"
#include "lib/cpp-base64/base64.h"


int main(int argc, char *argv[]) {

    if (argc != 4) {
        std::cout << "Incorrect number of arguments!" << std::endl;
        std::cout << "Arguments are <source_image_path> <desired_width> <desired_height>" << std::endl;

        return -1;
    }

    auto as = asyik::make_service();

    // Read image and encode to base64
    std::vector<uchar> buffer;
    cv::Mat img = cv::imread(argv[1]);

    if (img.empty()) {
        std::cout << "Image empty or path not pointing to jpg image" << std::endl;
        return -1;
    }

    int res = cv::imencode(".jpg", img, buffer);
    unsigned char *enc_msg = reinterpret_cast<unsigned char*>(buffer.data());
    std::string encoded = base64_encode(enc_msg, buffer.size());

    as->execute([=]() {
        // Send post request to http server
        auto req = asyik::http_easy_request(as, "POST", "http://127.0.0.1:8080/resize_image",
                                                encoded, {
                                                    {"content-type", "application/json"},
                                                    {"desired_width", argv[2]},
                                                    {"desired_height", argv[3]}
                                                }
                                            );
    
        // If response is successful
        if (req->response.result() == 200) {
            // Decode base64 image
            std::string dec_jpg = base64_decode(req->response.body);
            std::vector<uchar> data(dec_jpg.begin(), dec_jpg.end());
            cv::Mat save_img = cv::imdecode(cv::Mat(data), 1);

            // Write resized image to resources
            cv::imwrite("resources/result.jpg", save_img);

            LOG(INFO) << "Request success!\n";

        } else {
            LOG(INFO) << "Request failed!\n";
        }

        as->stop();
        
    });

    as->run();
    return 0;
}