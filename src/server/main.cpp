#include "core/Calculator.hpp"
#include <drogon/drogon.h>

int main() {

  Calculator calc;

  drogon::app()
      .registerHandler(
          "/calculate",
          [&calc](
              const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            auto expr = req->getParameter("expr");

            auto result = calc.evaluate(expr);

            Json::Value json;
            json["result"] = result;

            auto response = drogon::HttpResponse::newHttpJsonResponse(json);

            callback(response);
          })
      .addListener("127.0.0.1", 8080)
      .run();

  return 0;
}
