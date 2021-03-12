# -*- coding: utf-8 -*- 
import os 
import sys
import platform

if platform.system() == 'Windows':
  import win32api
else:
  from subprocess import call

def isSkipFile(filename):
    filename = filename.lower()
    skippath = []
    for val in skippath:
        if filename.endswith(val):
            return True 

    suffix = ['.cpp', '.cc', '.c', '.cxx', '.h', '.hpp', '.hxx']
    for val in suffix:
        if filename.endswith(val):
            return False 
    
    return True

def isSkipPath(dir):
    dir = dir.lower()
    skipdir = ['.git','.vscode', 'fmt']
    for val in skipdir:
        if dir.endswith(val):
            return True 
    
    return False

def dir(rootDir): 
    if(isSkipPath(rootDir)):
        return ;

    for filename in os.listdir(rootDir):
        path = os.path.join(rootDir, filename)
        if os.path.isdir(path): 
            dir(path)

        if(isSkipFile(path)):
            continue

        #param = r'''-style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 100, SpacesInParentheses: true, SpacesInAngles: true}" ''' + filename + " -i"
        param = "-style=file \"" + filename + "\" -i"
        if platform.system() == 'Windows':
          print(param)
          win32api.ShellExecute(0, 'open', r'clang-format.exe', param, rootDir, 0) 
        else:
          runcommand = 'clang-format ' + param
          print(runcommand)
          status = call(runcommand, cwd=rootDir, shell=True)

def main(argv):
    dir(argv[1])

if __name__=="__main__":
    if len(sys.argv) != 2:
        print("Usage: python clang-format.py path")
    else:
        main(sys.argv)
