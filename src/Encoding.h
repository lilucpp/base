#ifndef PEANUT_BASE_ENCODING_H
#define PEANUT_BASE_ENCODING_H

#include <string>
#include <boost/locale/encoding.hpp>

namespace peanut {
  inline std::string gbktoutf8(const std::string from) {
    return boost::locale::conv::to_utf<char>(from, "gbk");
  }

  inline std::string utf8togbk(const std::string from) {
    return boost::locale::conv::from_utf(from, "gbk");
  }

  inline std::wstring gbktounicode(const std::string from) {
    return boost::locale::conv::to_utf<wchar_t>(from, "gbk");
  }

  inline std::string unicodetogbk(const std::wstring from) {
    return boost::locale::conv::from_utf(from, "gbk");
  }

  inline std::wstring utf8tounicode(const std::string from) {
    return boost::locale::conv::utf_to_utf<wchar_t>(from);
  }

  inline std::string unicodetoutf8(const std::wstring from) {
    return boost::locale::conv::utf_to_utf<char>(from);
  }

}

#endif // PEANUT_BASE_ENCODING_H