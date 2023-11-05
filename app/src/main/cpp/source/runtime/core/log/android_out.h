#pragma once

#include <android/log.h>
#include <sstream>

/*!
 * Use this to log strings out to logcat. Note that you should use std::endl to commit the line
 *
 * ex:
 *  acout << "Hello World" << std::endl;
 */
extern std::ostream acout;

#define cout(x) acout<<x<<"\t"<<__FILE__<<":"<<__LINE__<<std::endl

/*!
 * Use this class to create an output stream that writes to logcat. By default, a global one is
 * defined as @a acout
 */
class android_out : public std::stringbuf {
public:
  /*!
   * Creates a new output stream for logcat
   * @param kLogTag the log tag to output
   */
  inline android_out(const char *kLogTag) : m_logTag(kLogTag) {}

protected:
  virtual int sync() override {
    __android_log_print(ANDROID_LOG_DEBUG, m_logTag, "%s", str().c_str());
    str("");
    return 0;
  }

private:
  const char *m_logTag;
};