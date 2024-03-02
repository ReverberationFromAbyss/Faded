#include "ConfigurationScreen.h"

#include "Configuration/GameBasic/GameBasicInformation.h"

namespace Video = ::Faded::Configuration::Video;
using namespace Video;

ConfigurationScreen* ConfigurationScreen::configurationScreenInstance{nullptr};

const std::string ConfigurationScreen::configurationScreenConfPath{
    "res/config/screenInfo.plist"};
const std::string ConfigurationScreen::userConfigPath{"conf/cfg.plist"};

bool ConfigurationScreen::init(void) {
  auto director = cocos2d::Director::getInstance();
  auto glview = director->getOpenGLView();

  if (!this->loadConfigurationScreenConfiguration()) {
    return false;
  }
  if (!this->loadScreenConfiguration()) {
    return false;
  }

  auto& windowTitle =
      ::Faded::Configuration::GameBasic::GameBasicInformation::getInstance()
          ->getGameTitle();

  if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || \
    (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) ||   \
    (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

    glview = this->m_ifFullScreen
                 ? cocos2d::GLViewImpl::createWithFullScreen(windowTitle)
                 : cocos2d::GLViewImpl::createWithRect(
                       windowTitle,
                       cocos2d::Rect(0, 0, this->m_currentWindowFrameSize.width,
                                     this->m_currentWindowFrameSize.height));
#else
    glview = GLViewImpl::create("Faded");
#endif
    director->setOpenGLView(glview);
  }
  if (!glview) {
    return false;
  }
  return true;
}

void ConfigurationScreen::applyConfiguration(void) {
  // init variables
  auto director = cocos2d::Director::getInstance();
  auto glview = director->getOpenGLView();

  // set window
  glview->setFrameSize(this->m_currentWindowFrameSize.width,
                       this->m_currentWindowFrameSize.height);
  // Set the design resolution
  glview->setDesignResolutionSize(this->m_currentResolution.width,
                                  this->m_currentResolution.height,
                                  ResolutionPolicy::NO_BORDER);

#ifdef _DEBUG

  // turn on display FPS
  director->setDisplayStats(true);

  // TODO: add a switch for FPS
#endif  //  _DEBUG

  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0f / this->m_refreshRate);

  // configure frame
  auto largeResolutionSize = this->m_designedResolutions.at("large");
  auto mediumResolutionSize = this->m_designedResolutions.at("medium");
  auto smallResolutionSize = this->m_designedResolutions.at("small");
  auto designResolutionSize = this->m_currentResolution;

  auto frameSize = glview->getFrameSize();
  // if the frame's height is larger than the height of medium size.
  if (frameSize.height > mediumResolutionSize.height) {
    director->setContentScaleFactor(
        MIN(largeResolutionSize.height / designResolutionSize.height,
            largeResolutionSize.width / designResolutionSize.width));
  }
  // if the frame's height is larger than the height of small size.
  else if (frameSize.height > smallResolutionSize.height) {
    director->setContentScaleFactor(
        MIN(mediumResolutionSize.height / designResolutionSize.height,
            mediumResolutionSize.width / designResolutionSize.width));
  }
  // if the frame's height is smaller than the height of medium size.
  else {
    director->setContentScaleFactor(
        MIN(smallResolutionSize.height / designResolutionSize.height,
            smallResolutionSize.width / designResolutionSize.width));
  }
}

void ConfigurationScreen::synchronizeConfiguration(void) {
  this->reloadConfigurationScreenConfiguration();
  this->reloadScreenConfiguration();
  this->applyConfiguration();
}

bool ConfigurationScreen::loadConfigurationScreenConfiguration(void) {
  auto plistInfo = cocos2d::FileUtils::getInstance()->getValueMapFromFile(
      ConfigurationScreen::configurationScreenConfPath);
  auto& resolutionList = plistInfo.at("resolutionList").asValueMap();
  for (auto& map : resolutionList) {
    /**
     * plist
     * > resolutionList     dict
     * |> <conf-name>       dict
     * ||> designResolution dict
     * |||> width           integer  <value>
     * |||> height          integer  <value>
     * ||> windowFrameSize  dict
     * |||> width           integer  <value>
     * |||> height          integer  <value>
     */

    auto& resolutionInfo = map.second.asValueMap();
    auto& designResolution = resolutionInfo.at("designResolution").asValueMap();
    auto& windowFrameSize = resolutionInfo.at("windowFrameSize").asValueMap();

    this->m_designedResolutions[map.first] =
        cocos2d::Size(designResolution.at("width").asFloat(),
                      designResolution.at("height").asFloat());
    this->m_windowFrameSizes[map.first] =
        cocos2d::Size(windowFrameSize.at("width").asFloat(),
                      windowFrameSize.at("height").asFloat());
  }

  return true;
}

bool ConfigurationScreen::reloadConfigurationScreenConfiguration(void) {
  // clear all configuration
  this->m_designedResolutions.clear();
  this->m_windowFrameSizes.clear();

  // and reload them ...
  if (!this->loadScreenConfiguration()) {
    return false;
  }

  return true;
}

bool ConfigurationScreen::loadScreenConfiguration(void) {
  // TODO: change readFromFile to readFromData

  auto plistInfo = cocos2d::FileUtils::getInstance()->getValueMapFromFile(
      ConfigurationScreen::userConfigPath);
  this->setResolution(plistInfo.at("resolution").asString());
  this->setFrameSize(plistInfo.at("resolution").asString());
  this->setRefreshRate(plistInfo.at("refreshRate").asInt());
  this->setFullScreen(plistInfo.at("fullScreen").asBool());

  return true;
}

bool ConfigurationScreen::reloadScreenConfiguration(void) {
  // clear all configuration
  this->m_brightness = 0;
  this->m_selectedResolutionSetting = "";
  this->m_selectedFrameSizeSetting = "";
  this->m_currentResolution = cocos2d::Size(0, 0);
  this->m_currentWindowFrameSize = cocos2d::Size(0, 0);
  this->m_ifFullScreen = false;
  this->m_refreshRate = 60;

  // and reload them ..
  if (!this->loadScreenConfiguration()) {
    return false;
  }

  return true;
}

ConfigurationScreen* ConfigurationScreen::getInstance(void) {
  if (!configurationScreenInstance) {
    return makeInstance();
  }
  return configurationScreenInstance;
}

ConfigurationScreen* ConfigurationScreen::makeInstance(void) {
  if (!configurationScreenInstance) {
    configurationScreenInstance =
        ConfigurationScreen::create();
  }
  return configurationScreenInstance;
}

void ConfigurationScreen::removeInstance(void) {
  configurationScreenInstance = nullptr;
}

bool ConfigurationScreen::ifExistInstance(void) {
  return configurationScreenInstance ? true : false;
}

inline cocos2d::Size const& ConfigurationScreen::getSelectedResolution(void) {
  return this->m_currentResolution;
}

inline std::string const& ConfigurationScreen::getSelectedResolutionName(void) {
  return this->m_selectedResolutionSetting;
}

const cocos2d::Size& ConfigurationScreen::getDesignResolution(void) {
  return this->m_currentResolution;
}

const std::string ConfigurationScreen::getDesignResolutionName(void) {
  // TODO
  if (this->m_currentResolution.width - 1920.0f < 0.0000001f &&
      this->m_currentResolution.height - 1080 < 0.0000001f) {
    return "1920x1080";
  } else if (this->m_currentResolution.width - 480 < 0.0000001f &&
             this->m_currentResolution.height - 360 < 0.0000001f) {
    return "480x360";
  } else if (this->m_currentResolution.width - 1024 < 0.0000001f &&
             this->m_currentResolution.height - 768 < 0.0000001f) {
    return "1024x768";
  } else if (this->m_currentResolution.width - 2048 < 0.0000001f &&
             this->m_currentResolution.height - 1536 < 0.0000001f) {
    return "2048x1536";
  }
  return "";
}

inline cocos2d::Size const ConfigurationScreen::getWindowFrameSize(void) {
  return cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
}

inline refreshRate_t ConfigurationScreen::getRefreshRate(void) {
  return this->m_refreshRate;
}

inline brightness_t ConfigurationScreen::getBrightness(void) {
  return this->m_brightness;
}

inline void ConfigurationScreen::setResolution(
    std::string resolutionSettingName) {
  this->m_selectedResolutionSetting = resolutionSettingName;
  this->m_currentResolution =
      this->m_designedResolutions.at(this->m_selectedResolutionSetting);
}

inline void ConfigurationScreen::setResolution(cocos2d::Size resolution) {
  this->m_selectedResolutionSetting = "";
  this->m_currentResolution = resolution;
}

inline void ConfigurationScreen::setFrameSize(
    std::string frameSizeSettingName) {
  this->m_selectedFrameSizeSetting = frameSizeSettingName;
  this->m_currentWindowFrameSize =
      this->m_windowFrameSizes.at(this->m_selectedFrameSizeSetting);
}

inline void ConfigurationScreen::setFrameSize(cocos2d::Size frameSize) {
  this->m_selectedFrameSizeSetting = "";
  this->m_currentWindowFrameSize = frameSize;
}

inline void ConfigurationScreen::setRefreshRate(refreshRate_t refreshRate) {
  this->m_refreshRate = refreshRate;
}

inline void ConfigurationScreen::setBrightness(brightness_t brightness) {
  this->m_brightness = brightness;
}

inline void ConfigurationScreen::setFullScreen(bool ifFullScreen) {
  this->m_ifFullScreen = ifFullScreen;
}
