#include "core/Calculator.hpp"
#include <drogon/drogon.h>

int main() {

  Calculator calc;

  auto addCorsHeaders = [](const drogon::HttpResponsePtr &response) {
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response->addHeader("Access-Control-Allow-Headers", "Content-Type");
  };

  drogon::app()

      // Calculator endpoint
      .registerHandler(
          "/calculate",
          [&calc, &addCorsHeaders](
              const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            try {
              auto expr = req->getParameter("expr");

              if (expr.empty()) {
                Json::Value json;
                json["error"] = "Missing expression";

                auto response = drogon::HttpResponse::newHttpJsonResponse(json);

                response->setStatusCode(drogon::k400BadRequest);

                addCorsHeaders(response);

                callback(response);
                return;
              }

              auto result = calc.evaluate(expr);

              Json::Value json;
              json["result"] = result;

              auto response = drogon::HttpResponse::newHttpJsonResponse(json);

              addCorsHeaders(response);

              callback(response);

            } catch (const std::exception &e) {

              Json::Value json;
              json["error"] = e.what();

              auto response = drogon::HttpResponse::newHttpJsonResponse(json);

              response->setStatusCode(drogon::k400BadRequest);
              addCorsHeaders(response);

              callback(response);
            }
          })

      // Health check endpoint
      .registerHandler(
          "/health",
          [&addCorsHeaders](
              const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            Json::Value json;
            json["status"] = "ok";

            auto response = drogon::HttpResponse::newHttpJsonResponse(json);

            addCorsHeaders(response);
            callback(response);
          })

      .addListener("127.0.0.1", 8080)
      .run();

  return 0;
}
