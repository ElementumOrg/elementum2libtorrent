#include "application.h"

#include <iostream>
#include <stdexcept>

#include <utils/logger.h>

#include <oatpp/network/Server.hpp>

#include <boost/stacktrace.hpp>

#ifdef USE_MIMALLOC
#include <mimalloc.h>
#include <mimalloc-override.h>
#endif

int main(int argc, char *argv[]) {
    auto const logger = std::make_shared<CustomLogger>();
    oatpp::base::Environment::init(logger);

    try {
        lh::Application::init(argc, argv);

        lh::app().run();
    } catch (const std::exception &e) {
        OATPP_LOGE("main", "Exception: %s", e.what())
        std::cerr << boost::stacktrace::stacktrace();
    } catch (...) {
        OATPP_LOGE("main", "Exception: %s", typeid(std::current_exception()).name())
        std::cerr << boost::stacktrace::stacktrace();
    }

    try {
        lh::app().close();
    } catch (const std::exception &e) {
        OATPP_LOGE("main", "Failed closing application with Exception: %s", e.what());
    } catch (...) {
        OATPP_LOGE("main", "Unknown Exception: %s", typeid(std::current_exception()).name());
    }

    oatpp::base::Environment::destroy();

    return 0;
}
