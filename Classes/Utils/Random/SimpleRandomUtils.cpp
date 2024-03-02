#include "SimpleRandomUtils.h"

namespace Random = ::Faded::Utils::Random;
using namespace Random;

bool SimpleRandomUtils::init(void) { return true; }

bool SimpleRandomUtils::init(int begin, int end) {
  std::uniform_int_distribution<> distrib(begin, end);
  // �����������Χ����Ϊ���ȷֲ�
  this->m_producer.int_t_producer = distrib;
  this->m_producerType = kInt;
  return true;
}

bool SimpleRandomUtils::init(float begin, float end) {
  std::uniform_real_distribution<> distrib(begin, end);
  // �����������Χ����Ϊ���ȷֲ�
  this->m_producer.float_t_producer = distrib;
  this->m_producerType = kFloat;
  return true;
}

SimpleRandomUtils* SimpleRandomUtils::create(int begin, int end) {
  SimpleRandomUtils* pRet = new (std::nothrow) SimpleRandomUtils();
  if (pRet && pRet->init(begin, end)) {
    pRet->autorelease();
    return pRet;
  } else {
    delete pRet;
    pRet = nullptr;
    return nullptr;
  }
}

SimpleRandomUtils* SimpleRandomUtils::create(float begin, float end) {
  SimpleRandomUtils* pRet = new (std::nothrow) SimpleRandomUtils();
  if (pRet && pRet->init(begin, end)) {
    pRet->autorelease();
    return pRet;
  } else {
    delete pRet;
    pRet = nullptr;
    return nullptr;
  }
}

SimpleRandomUtils* SimpleRandomUtils::getInstance(void) {
  return SimpleRandomUtils::create();
}

SimpleRandomUtils* SimpleRandomUtils::getInstance(int begin, int end) {
  return SimpleRandomUtils::create(begin, end);
}

SimpleRandomUtils* SimpleRandomUtils::getInstance(float begin, float end) {
  return SimpleRandomUtils::create(begin, end);
}

SimpleRandomUtils::return_t SimpleRandomUtils::random() {
  std::random_device seed;
  std::ranlux48 engine(seed());  // ���������������������

  switch (m_producerType) {
    case Faded::Utils::Random::SimpleRandomUtils::kInt:
      m_returnVal.int_return =
          this->m_producer.int_t_producer(engine);  // �����
      return m_returnVal;
      break;
    case Faded::Utils::Random::SimpleRandomUtils::kFloat:
      m_returnVal.real_return =
          this->m_producer.float_t_producer(engine);  // �����
      return m_returnVal;
      break;
    default:
      break;
  }
}

int SimpleRandomUtils::random(int begin, int end) {
  std::random_device seed;
  std::ranlux48 engine(seed());  // ���������������������
  // �����������Χ����Ϊ���ȷֲ�
  if (m_producerType == kFloat) {
    return 0;
  }
  std::uniform_int_distribution<> distrib(begin, end);
  m_producer.int_t_producer = distrib;
  return m_producer.int_t_producer(engine);  // �����
}

int SimpleRandomUtils::random(float begin, float end) {
  std::random_device seed;
  std::ranlux48 engine(seed());  // ���������������������
  // �����������Χ����Ϊ���ȷֲ�
  if (m_producerType == kInt) {
    return 0;
  }
  std::uniform_real_distribution<> distrib(begin, end);
  m_producer.float_t_producer = distrib;
  return m_producer.float_t_producer(engine);  // �����
}