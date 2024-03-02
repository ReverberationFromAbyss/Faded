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
   * ��Ʒֱ���, �زĵķֱ���
   */

  using resolution_t = cocos2d::Size;

  /*!
   * @brief designed resolution list (a map), ��Ʒֱ����б�
   */
  std::map<std::string, resolution_t> m_designedResolutions{};
  /*!
   * @brief window fram size list (a map), ���ڷֱ����б�
   */
  std::map<std::string, resolution_t> m_windowFrameSizes{};
  /*!
   * @brief Current configuration for resolution, ��ǰʹ�õķֱ�������;
   * left empty if using customized configuration, Ϊ����ʹ���Զ�������
   */
  std::string m_selectedResolutionSetting{};
  /*!
   * @brief Current configuration for fame size, ��ǰʹ�õĴ��ڴ�С����;
   * left empty if using customized configuration, Ϊ����ʹ���Զ�������
   */
  std::string m_selectedFrameSizeSetting{};
  /*!
   * @brief Current resolution, ��ǰ�ֱ�������;
   * or customized configuration, ����Ϊ�Զ���ֱ���
   */
  cocos2d::Size m_currentResolution{};

  // Window
  /**
   * frame size, resolution of window
   * ֡��С, ���ڷֱ��ʴ�С
   */

  /*!
   * @brief resolution of window
   * ��ǰ���ڵķֱ���
   */
  cocos2d::Size m_currentWindowFrameSize{};
  /*!
   * @brief If full screen, �Ƿ�Ϊȫ����ʾ
   * true, full screen, ��, ȫ��
   * false, windowed, ��, ���ڻ�
   * default is false,
   */
  bool m_ifFullScreen{false};
  /*!
   * @brief Current refresh rate, ��ǰˢ����
   * default is 60, Ĭ��Ϊ60Hz
   */
  refreshRate_t m_refreshRate{60};
  /*!
   * @brief Current brightness, ��ǰ����
   * default is ***, Ĭ��Ϊ***
   * TODO: fill the *** part
   * useless tile now.
   */
  brightness_t m_brightness{0};

  // load
  /*!
   * @brief Get designed resolution information and write into member
   * `m_designedResolutions',
   * ��ȡ��Ʒֱ�����Ϣ(�б�), ����д���Ա`m_designedResolutions'
   * @return If success read the configure file
   */
  bool loadConfigurationScreenConfiguration(void);
  /*!
   * @brief Get designed resolution information and write into member
   * `m_designedResolutions',
   * ��ȡ��Ʒֱ�����Ϣ(�б�), ����д���Ա`m_designedResolutions'
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
   * ����ģʽ, ��ȡ��ǰ��ʵ��
   * @return pointer to the instance of this class, ��ǰ���ʵ��
   */
  static ConfigurationScreen* getInstance(void);
  /*!
   * @brief Singleton pattern, create a new instance of this class,
   * ����ģʽ, ����һ���µ�ʵ��
   * @return pointer to the instance of this class, ��ǰ���ʵ��
   */
  static ConfigurationScreen* makeInstance(void);
  /*!
   * @brief Singleton pattern, remove the instance of this class,
   * ����ģʽ, �Ƴ���ǰʵ��
   */
  static void removeInstance(void);
  /*!
   * @brief Singleton pattern, check if the instance exist,
   * ����ģʽ, ȷ��ʵ���Ƿ����
   * @return if exist
   */
  static bool ifExistInstance(void);

  // Get *

  /*!
   * @brief Get current designed resolution,
   * ��ȡ��ǰ��Ʒֱ���
   * @param
   * @return Current selected resolution
   */
  virtual const cocos2d::Size& getSelectedResolution(void);
  /*!
   * @brief Get current selected resolution Configure name,
   * ��ȡ��ǰ��Ʒֱ�������
   * @return current selected resolution setting's name
   */
  virtual const std::string& getSelectedResolutionName(void);

  /*!
   * @brief Get current designed resolution,
   * ��ȡ��ǰ��Ʒֱ���, just as `getSelectedResolution'
   * @param
   * @return Current selected resolution
   */
  virtual const cocos2d::Size& getDesignResolution(void);
  /*!
   * @brief Get current selected resolution Configure name,
   * ��ȡ��ǰ��Ʒֱ�������
   * @return current selected resolution setting's name
   */
  virtual const std::string getDesignResolutionName(void);
  /*!
   * @brief Get current window size, ��ȡ��ǰ���ڷֱ��ʴ�С
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
