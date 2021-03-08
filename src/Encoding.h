#ifndef PEANUT_BASE_ENCODING_H
#define PEANUT_BASE_ENCODING_H

#include <boost/locale/encoding.hpp>
#include <boost/locale/util.hpp>
#include <string>

namespace peanut {
inline std::string GBKToUTF8(const std::string from) { return boost::locale::conv::to_utf<char>(from, "gbk"); }

inline std::string UTF8ToGBK(const std::string from) { return boost::locale::conv::from_utf(from, "gbk"); }

inline std::wstring GBKToUnicode(const std::string from) { return boost::locale::conv::to_utf<wchar_t>(from, "gbk"); }

inline std::string UnicodeToGBK(const std::wstring from) { return boost::locale::conv::from_utf(from, "gbk"); }

inline std::wstring UTF8ToUnicode(const std::string from) { return boost::locale::conv::utf_to_utf<wchar_t>(from); }

inline std::string UnicodeToUtf8(const std::wstring from) { return boost::locale::conv::utf_to_utf<char>(from); }

inline std::string GetSystemLocale() { return boost::locale::util::get_system_locale(); }

inline std::string ToUtf8(const std::string &from, const std::string &charset) {
  return boost::locale::conv::to_utf<char>(from, charset);
}

inline std::wstring ToUnicode(const std::string &from, const std::string &charset) {
  return boost::locale::conv::to_utf<wchar_t>(from, charset);
}

}  // namespace peanut

#endif  // PEANUT_BASE_ENCODING_H