#include <stdio.h>
#include <windows.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(
            NULL,                                
            "cmd /c echo Child Process Running", 
            NULL,                                
            NULL,                                
            FALSE,                               
            0,                                   
            NULL,                                
            NULL,                                
            &si,                                 
            &pi                                  
            )){
        printf("Process creation failed. Error: %d\n", GetLastError());
        return 1;
    }

    printf("Parent Process:\n");
    printf("PID: %lu\n", GetCurrentProcessId());
    printf("Child Process Created (PID: %lu)\n", pi.dwProcessId);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

// =thread-group-added,id="i1"
// GNU gdb (GDB) 7.6.1
// Copyright (C) 2013 Free Software Foundation, Inc.
// License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
// This is free software: you are free to change and redistribute it.
// There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
// and "show warranty" for details.
// This GDB was configured as "mingw32".
// For bug reporting instructions, please see:
// <http://www.gnu.org/software/gdb/bugs/>.
// Warning: Debuggee TargetArchitecture not detected, assuming x86_64.
// =cmd-param-changed,param="pagination",value="off"
// =cmd-param-changed,param="args",value="2>CON 1>CON <CON"
// [New Thread 68308.0xcbec]
// [New Thread 68308.0xddfc]
// Loaded 'C:\Windows\SysWOW64\kernel32.dll'. Symbols loaded.
// Loaded 'C:\Windows\SysWOW64\KernelBase.dll'. Symbols loaded.
// Loaded 'C:\Windows\SysWOW64\apphelp.dll'. Symbols loaded.
// Loaded 'C:\Windows\SysWOW64\msvcrt.dll'. Symbols loaded.
// [New Thread 68308.0xa054]
// Child Process Running
// Parent Process:
// PID: 68308
// Child Process Created (PID: 62164)
// The program 'D:\OScript\Assignment4\pr_1.exe' has exited with code 0 (0x00000000).