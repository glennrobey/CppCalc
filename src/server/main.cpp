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
            try {
              auto expr = req->getParameter("expr");

              if (expr.empty()) {
                Json::Value json;
                json["error"] = "Missing expression";

                auto response = drogon::HttpResponse::newHttpJsonResponse(json);

                response->setStatusCode(drogon::k400BadRequest);

                callback(response);
                return;
              }

              auto result = calc.evaluate(expr);

              Json::Value json;
              json["result"] = result;

              auto response = drogon::HttpResponse::newHttpJsonResponse(json);

              callback(response);

            } catch (const std::exception &e) {

              Json::Value json;
              json["error"] = e.what();

              auto response = drogon::HttpResponse::newHttpJsonResponse(json);

              response->setStatusCode(drogon::k400BadRequest);

              callback(response);
            }
          })
      .addListener("127.0.0.1", 8080)
      .run();

  return 0;
}
