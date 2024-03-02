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
   * ����ģʽ, ��ȡ��ǰ��ʵ��                               \
   * @return pointer to the instance of this class, ��ǰ���ʵ�� \
   */                                                                  \
  static _type* getInstance(void);                                     \
  /*!                                                                  \
   * @brief Singleton pattern, create a new instance of this class,    \
   * ����ģʽ, ����һ���µ�ʵ��                            \
   * @return pointer to the instance of this class, ��ǰ���ʵ�� \
   */                                                                  \
  static _type* makeInstance(void);                                    \
  /*!                                                                  \
   * @brief Singleton pattern, remove the instance of this class,      \
   * ����ģʽ, �Ƴ���ǰʵ��                                  \
   */                                                                  \
  static void removeInstacne(void);                                    \
  /*!                                                                  \
   * @brief Singleton pattern, check if the instance exist,            \
   * ����ģʽ, ȷ��ʵ���Ƿ����                            \
   * @return if exist                                                  \
   */                                                                  \
  static bool ifExistInstance(void);
}  // namespace Macros
}  // namespace Utils
}  // namespace Faded

#endif  // !FADED_UTILS_MACROS_SINGLETON_SINGLETON_MACROS_H__
