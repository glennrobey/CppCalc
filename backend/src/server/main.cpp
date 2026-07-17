#include "cli/Commands.hpp"
#include "core/Calculator.hpp"
#include <drogon/drogon.h>
#include <iostream>

int main() {
  Calculator calc;
  Commands commands(calc);
  std::cout << "C++Calc server running on port 8080\n";

  auto addCorsHeaders = [](const drogon::HttpResponsePtr &response) {
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response->addHeader("Access-Control-Allow-Headers", "Content-Type");
  };

  drogon::app()

      // CORS preflight handler
      .registerHandler(
          "/calculate",
          [&addCorsHeaders](
              const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            auto response = drogon::HttpResponse::newHttpResponse();

            response->setStatusCode(drogon::k204NoContent);

            addCorsHeaders(response);

            callback(response);
          },
          {drogon::Options})

      // Calculator endpoint
      .registerHandler(
          "/calculate",
          [&calc, &commands, &addCorsHeaders](
              const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            Json::Value responseJson;

            auto json = req->getJsonObject();

            if (!json || !json->isMember("expression")) {
              responseJson["error"] = "Missing expression";

              auto response =
                  drogon::HttpResponse::newHttpJsonResponse(responseJson);

              response->setStatusCode(drogon::k400BadRequest);
              addCorsHeaders(response);

              callback(response);
              return;
            }

            try {
              auto expression = (*json)["expression"].asString();
              // std::cout << "Received: [" << expression << "]\n";

              if (expression == "help" || expression == "vars" ||
                  expression == "history" || expression == "clear" ||
                  expression == "cls" || expression == "reset") {

                responseJson["result"] = commands.handleCommand(expression);

              } else {

                auto result = calc.evaluate(expression);

                responseJson["result"] = result;
              }

              auto response =
                  drogon::HttpResponse::newHttpJsonResponse(responseJson);

              addCorsHeaders(response);

              callback(response);
            } catch (const std::exception &e) {
              responseJson["error"] = e.what();

              auto response =
                  drogon::HttpResponse::newHttpJsonResponse(responseJson);

              response->setStatusCode(drogon::k400BadRequest);
              addCorsHeaders(response);

              callback(response);
            }
          },
          {drogon::Post})

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
