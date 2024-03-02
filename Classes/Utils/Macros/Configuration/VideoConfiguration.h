#pragma once

#ifndef FADED_UTILS_MACRO_CONFIGURATION__VIDEO_CONFIGURATION__
#define FADED_UTILS_MACRO_CONFIGURATION__VIDEO_CONFIGURATION__

#include "Configuration/Video/Screen/ConfigurationScreen.h"

namespace Faded {
namespace Utils {
namespace Macros {
#define FADED__GET_RESOLUTION_SPECIFIED_RCPATH(_path, _name)                \
  std::string(_path)                                                        \
      .append(                                                              \
          ::Faded::Configuration::Video::ConfigurationScreen::getInstance() \
              ->getDesignResolutionName()                                   \
              .c_str())                                                     \
      .append("/")                                                          \
      .append(_name)
}  // namespace Macros
}  // namespace Utils
}  // namespace Faded

#endif  // !FADED_UTILS_MACRO_CONFIGURATION__VIDEO_CONFIGURATION__
