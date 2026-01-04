#include <drogon/drogon.h>

#include "sus.hpp"

#include "dicer_games/ATO.hpp"
#include "dicer_games/Oathsworn.hpp"

using namespace drogon;
using namespace spaceless;

class trantor_logger : public logger {
public:
    virtual void log(const log_record &record) noexcept override {
        trantor::Logger::LogLevel level;
        switch (record.level) {
        case log_level::debug:
            level = trantor::Logger::LogLevel::kDebug;
        case log_level::info:
            level = trantor::Logger::LogLevel::kInfo;
        case log_level::warning:
            level = trantor::Logger::LogLevel::kWarn;
        case log_level::error:
            level = trantor::Logger::LogLevel::kError;
        case log_level::critical:
            level = trantor::Logger::LogLevel::kFatal;
        default:
            level = trantor::Logger::LogLevel::kInfo;
        }
        trantor::Logger(trantor::Logger::SourceFile(record.source_location.file_name())
            , record.source_location.line()
            , level
            , record.source_location.function_name()).stream() << record.message;
    }
};

int main(int argc, char **argv) {
    init_option option;
    option.logging_option.flags = logging::init_option::none;
    init(argc, argv, option);
    logging::register_wrapper_logger(std::make_unique<trantor_logger>());

    app().addListener("0.0.0.0", 8080);

    // app().loadConfigFile("config.json");

    app().registerHandler(
        "/",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("Welcome to spaceless.games!");
            callback(resp);
        },
        {Get});

    app().registerHandler(
        "/api/hello",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback) {
            Json::Value json;
            json["message"] = "Hello from spaceless.games backend!";
            json["status"] = "success";
            auto resp = HttpResponse::newHttpJsonResponse(json);
            callback(resp);
        },
        {Get, Post});

    app().setThreadNum(4);
    
    app().enableSession(1200);
    
    LOG(INFO) << "Hello!";
    LOG_INFO << "Server running on http://0.0.0.0:8080";

    // Run HTTP framework
    app().run();

    return 0;
}
