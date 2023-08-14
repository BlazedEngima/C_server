#include <iostream>
#include "libasyik/service.hpp"
#include "libasyik/http.hpp"

int main() {

  auto as = asyik::make_service();

  // std::cout << "Test" << std::endl;
  as->execute([=]() {

    auto req = asyik::http_easy_request(as, "POST", "http://127.0.0.1:8080/resize_image",
                                        "this is payload", {{"x-asyik", "ok"}});

    if (req->response.result() == 200) {
      LOG(INFO) << "Body = " << req->response.body << "\n";
      LOG(INFO) << "Request success!\n";
    } else {
      LOG(INFO) << "Request failed!\n";
    }

    as->stop();
      
  });

  as->run();
  return 0;
}