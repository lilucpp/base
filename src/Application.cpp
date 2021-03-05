#include "Application.h"
#include "Encoding.h"

namespace peanut {
    // https://stackoverflow.com/a/55579815/8330816
    std::string GetApplicationPath() {
        #ifdef _WIN32
            char path[MAX_PATH] = { 0 };
            GetModuleFileNameA(NULL, path, MAX_PATH);
            return path;
        #else
            char result[PATH_MAX];
            ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
            return std::string(result, (count > 0) ? count : 0);
        #endif
    }

    std::string GetApplicationDir() {
        std::string path = GetApplicationPath();
        std::string::size_type pos = path.find_last_of("\\/");
        if(std::string::npos != pos)
            return path.substr(0, pos);
        
        return ".";
    }

    std::wstring GetApplicationPathW() {
        #ifdef _WIN32
            return gbktounicode(GetApplicationPath());
        #else
            return utf8tounicode(GetApplicationPath());
        #endif
    }

    std::wstring GetApplicationDirW() {
         #ifdef _WIN32
            return gbktounicode(GetApplicationDir());
        #else
            return utf8tounicode(GetApplicationDir());
        #endif
    }

}