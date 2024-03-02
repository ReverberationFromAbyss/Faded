#pragma once

#ifndef FADED_UTILS__SIMPLE_RANDOM_UTILS_H__
#define FADED_UTILS__SIMPLE_RANDOM_UTILS_H__

#include <random>

#include "cocos2d.h"

namespace Faded {
namespace Utils {
namespace Random {
class SimpleRandomUtils : private cocos2d::Ref {
 protected:
 private:
  bool init(void);
  bool init(int begin, int end);
  bool init(float begin, float end);
  CREATE_FUNC(SimpleRandomUtils);
  static SimpleRandomUtils* create(int begin, int end);
  static SimpleRandomUtils* create(float begin, float end);

  union {
    std::uniform_int_distribution<> int_t_producer;
    std::uniform_real_distribution<> float_t_producer;
  } m_producer{};
  union return_t {
    int int_return;
    float real_return;
  } m_returnVal;
  enum {
    kInt,
    kFloat,
  } m_producerType{kInt};

 public:
  SimpleRandomUtils() = default;
  virtual ~SimpleRandomUtils() = default;

  static SimpleRandomUtils* getInstance(void);
  static SimpleRandomUtils* getInstance(int begin, int end);
  static SimpleRandomUtils* getInstance(float begin, float end);

  return_t random();
  int random(int begin, int end);
  int random(float begin, float end);

  // TODO:
};
}  // namespace Random
}  // namespace Utils
}  // namespace Faded

#endif  //! FADED_UTILS__SIMPLE_RANDOM_UTILS_H__
