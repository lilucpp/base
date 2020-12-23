// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_PRINT_H
#define PEANUT_BASE_PRINT_H

#include <stdarg.h>
#include <string>

namespace peanut {

/*
How to put color on Windows console(https://www.codeproject.com/Tips/5255355/How-to-Put-Color-on-Windows-Console)
On old builds (Windows 10 1909 or prior) Windows just recognize the ESC code 1, but it is possible for Windows to
recognize the ESC code \033 (or other depending on the language) with a modification in the record (regedit.exe).

The modification
For modification, you need to run the command below: (on CMD as administrator)

reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f
In case of error (it'll have no error, but...), here is the command to undo: (on CMD as administrator)

reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000000 /f
*/

enum Color { BLACK = 30, RED, GREEN, YELLOW, BLUE, PURPLE };  // enum Color

static void ColorPrintln(enum Color color, const char *fmt, ...) {
  va_list ap;
  printf("\033[0;%dm", color);
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  printf("\033[0m\n");  // if not \n , in some situation , the next lines will be set the same color unexpectedly
}

}  // namespace peanut

#endif  // PEANUT_BASE_PRINT_H
