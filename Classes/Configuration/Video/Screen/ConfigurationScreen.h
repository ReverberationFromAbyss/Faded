#pragma once

#ifndef FADED_CONFIGURATION_VIDEO_SCREEN__CONFIGURATION_VIDEO_H__
#define FADED_CONFIGURATION_VIDEO_SCREEN__CONFIGURATION_VIDEO_H__

#include <Map>
#include <cstdint>
#include <string>

#include "cocos2d.h"

namespace Faded {
namespace Configuration {
namespace Video {
using refreshRate_t = uint8_t;
using brightness_t = uint16_t;

/*!
 * @brief Configuration Utils for Screen, (Resolutions, Refesh Rate,
 * Brightness...)
 */
class ConfigurationScreen : private cocos2d::Ref {
 protected:
 private:
  ConfigurationScreen() = default;
  static ConfigurationScreen* configurationScreenInstance;

  /*!
   * @brief Initialize singleton ConfigurationResolution
   * @return If ConfigurationResolution initizlized successfully.
   */
  virtual bool init(void);
  CREATE_FUNC(ConfigurationScreen);

  static const std::string userConfigPath;  // path to screen configuration
  static const std::string
      configurationScreenConfPath;  // path to `configurationScreen' class conf

  // Resolution
  /**
   * designed resolution, resolution of resources
   * 设计分辨率, 素材的分辨率
   */

  using resolution_t = cocos2d::Size;

  /*!
   * @brief designed resolution list (a map), 设计分辨率列表
   */
  std::map<std::string, resolution_t> m_designedResolutions{};
  /*!
   * @brief window fram size list (a map), 窗口分辨率列表
   */
  std::map<std::string, resolution_t> m_windowFrameSizes{};
  /*!
   * @brief Current configuration for resolution, 当前使用的分辨率设置;
   * left empty if using customized configuration, 为空则使用自定义配置
   */
  std::string m_selectedResolutionSetting{};
  /*!
   * @brief Current configuration for fame size, 当前使用的窗口大小设置;
   * left empty if using customized configuration, 为空则使用自定义配置
   */
  std::string m_selectedFrameSizeSetting{};
  /*!
   * @brief Current resolution, 当前分辨率配置;
   * or customized configuration, 可能为自定义分辨率
   */
  cocos2d::Size m_currentResolution{};

  // Window
  /**
   * frame size, resolution of window
   * 帧大小, 窗口分辨率大小
   */

  /*!
   * @brief resolution of window
   * 当前窗口的分辨率
   */
  cocos2d::Size m_currentWindowFrameSize{};
  /*!
   * @brief If full screen, 是否为全屏显示
   * true, full screen, 是, 全屏
   * false, windowed, 否, 窗口化
   * default is false,
   */
  bool m_ifFullScreen{false};
  /*!
   * @brief Current refresh rate, 当前刷新率
   * default is 60, 默认为60Hz
   */
  refreshRate_t m_refreshRate{60};
  /*!
   * @brief Current brightness, 当前亮度
   * default is ***, 默认为***
   * TODO: fill the *** part
   * useless tile now.
   */
  brightness_t m_brightness{0};

  // load
  /*!
   * @brief Get designed resolution information and write into member
   * `m_designedResolutions',
   * 获取设计分辨率信息(列表), 并且写入成员`m_designedResolutions'
   * @return If success read the configure file
   */
  bool loadConfigurationScreenConfiguration(void);
  /*!
   * @brief Get designed resolution information and write into member
   * `m_designedResolutions',
   * 获取设计分辨率信息(列表), 并且写入成员`m_designedResolutions'
   * @return If success read the configure file
   */
  bool reloadConfigurationScreenConfiguration(void);

  /*!
   * @brief loading screen configuration
   * @return if success
   */
  bool loadScreenConfiguration(void);
  /*!
   * @brief loading screen configuration
   * @return if success
   */
  bool reloadScreenConfiguration(void);

 public:
  virtual ~ConfigurationScreen() = default;

  // Sigleton

  /*!
   * @brief Singleton pattern, get instance of this class,
   * 单例模式, 获取当前类实例
   * @return pointer to the instance of this class, 当前类的实例
   */
  static ConfigurationScreen* getInstance(void);
  /*!
   * @brief Singleton pattern, create a new instance of this class,
   * 单例模式, 创建一个新的实例
   * @return pointer to the instance of this class, 当前类的实例
   */
  static ConfigurationScreen* makeInstance(void);
  /*!
   * @brief Singleton pattern, remove the instance of this class,
   * 单例模式, 移除当前实例
   */
  static void removeInstance(void);
  /*!
   * @brief Singleton pattern, check if the instance exist,
   * 单例模式, 确认实例是否存在
   * @return if exist
   */
  static bool ifExistInstance(void);

  // Get *

  /*!
   * @brief Get current designed resolution,
   * 获取当前设计分辨率
   * @param
   * @return Current selected resolution
   */
  virtual const cocos2d::Size& getSelectedResolution(void);
  /*!
   * @brief Get current selected resolution Configure name,
   * 获取当前设计分辨率配置
   * @return current selected resolution setting's name
   */
  virtual const std::string& getSelectedResolutionName(void);

  /*!
   * @brief Get current designed resolution,
   * 获取当前设计分辨率, just as `getSelectedResolution'
   * @param
   * @return Current selected resolution
   */
  virtual const cocos2d::Size& getDesignResolution(void);
  /*!
   * @brief Get current selected resolution Configure name,
   * 获取当前设计分辨率配置
   * @return current selected resolution setting's name
   */
  virtual const std::string getDesignResolutionName(void);
  /*!
   * @brief Get current window size, 获取当前窗口分辨率大小
   * @return Current window size
   */
  virtual const cocos2d::Size getWindowFrameSize(void);
  /*!
   * @brief Get current refresh rate setting
   * @param
   * @return Current refresh rate
   */
  virtual refreshRate_t getRefreshRate(void);
  /*!
   * @brief Get current brightness setting
   * @param
   * @return Current brightness
   */
  virtual brightness_t getBrightness(void);

  // Set *

  virtual void setResolution(std::string resolutionSettingName);
  virtual void setResolution(cocos2d::Size resolution);
  virtual void setFrameSize(std::string frameSizeSettingName);
  virtual void setFrameSize(cocos2d::Size frameSize);
  virtual void setRefreshRate(refreshRate_t refreshRate);
  virtual void setBrightness(brightness_t brightness);
  virtual void setFullScreen(bool ifFullScreen);

  // apply the configuration

  /*!
   * @brief apply configuration to current running instance
   */
  virtual void applyConfiguration(void);
  /*!
   * @brief synchronize configureation and current running instance
   */
  virtual void synchronizeConfiguration(void);

  // TODO: write configuration
};
}  // namespace Video
}  // namespace Configuration
}  // namespace Faded

#endif  // !FADED_CONFIGURATION_VIDEO_SCREEN__CONFIGURATION_VIDEO_H__
