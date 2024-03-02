#pragma once

#ifndef FADED_UTILS_MACROS_SINGLETON_SINGLETON_MACROS_H__
#define FADED_UTILS_MACROS_SINGLETON_SINGLETON_MACROS_H__

#include <string>

namespace Faded {
namespace Utils {
namespace Macros {
// used only with VS expend macro
#define SINGLETON_DEFINATION_GENERATOR(_type)                          \
  /*!                                                                  \
   * @brief Singleton pattern, get instance of this class,             \
   * 单例模式, 获取当前类实例                               \
   * @return pointer to the instance of this class, 当前类的实例 \
   */                                                                  \
  static _type* getInstance(void);                                     \
  /*!                                                                  \
   * @brief Singleton pattern, create a new instance of this class,    \
   * 单例模式, 创建一个新的实例                            \
   * @return pointer to the instance of this class, 当前类的实例 \
   */                                                                  \
  static _type* makeInstance(void);                                    \
  /*!                                                                  \
   * @brief Singleton pattern, remove the instance of this class,      \
   * 单例模式, 移除当前实例                                  \
   */                                                                  \
  static void removeInstacne(void);                                    \
  /*!                                                                  \
   * @brief Singleton pattern, check if the instance exist,            \
   * 单例模式, 确认实例是否存在                            \
   * @return if exist                                                  \
   */                                                                  \
  static bool ifExistInstance(void);
}  // namespace Macros
}  // namespace Utils
}  // namespace Faded

#endif  // !FADED_UTILS_MACROS_SINGLETON_SINGLETON_MACROS_H__
