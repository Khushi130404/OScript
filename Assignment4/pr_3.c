#include <stdio.h>
#include <windows.h>

int main() 
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent Process (PID: %lu) is creating a child process...\n", GetCurrentProcessId());

    if (!CreateProcess(
            NULL,               
            "cmd /c dir",       
            NULL,               
            NULL,               
            FALSE,              
            0,                  
            NULL,               
            NULL,                
            &si,                 
            &pi                  
        )) {
        printf("Process creation failed. Error: %d\n", GetLastError());
        return 1;
    }
    printf("Child Process Created (PID: %lu). Executing 'dir' command...\n", pi.dwProcessId);
    printf("Parent Process is waiting for the child to complete...\n");
    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("Child Process has finished execution.\n");
    printf("Parent Process (PID: %lu) resumes execution.\n", GetCurrentProcessId());
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

// PS D:\OScript>  & 'c:\Users\Khushi\.vscode\extensions\ms-vscode.cpptools-1.23.6-win32-x64\debugAdapters\bin\WindowsDebugLauncher.exe' '--stdin=Microsoft-MIEngine-In-o0y5y4bt.ibl' '--stdout=Microsoft-MIEngine-Out-xu2ztkto.5dd' '--stderr=Microsoft-MIEngine-Error-qeysp42x.mru' '--pid=Microsoft-MIEngine-Pid-sn4otmtn.kk2' '--dbgExe=C:\MinGW\bin\gdb.exe' '--interpreter=mi' 

// [Running] cd "d:\OScript\Assignment4\" && gcc pr_3.c -o pr_3 && "d:\OScript\Assignment4\"pr_3
//  Volume in drive D is New Volume
//  Volume Serial Number is 3A17-096A

//  Directory of d:\OScript\Assignment4

// 10-02-2025  13:36    <DIR>          .
// 10-02-2025  12:53    <DIR>          ..
// 10-02-2025  13:11             2,371 pr_1.c
// 10-02-2025  13:09            50,768 pr_1.exe
// 10-02-2025  13:18             1,598 pr_2.c
// 10-02-2025  13:16            51,280 pr_2.exe
// 10-02-2025  13:25             1,601 pr_3.c
// 10-02-2025  13:36            42,944 pr_3.exe
// 10-02-2025  13:35             1,056 pr_child_4.c
// 10-02-2025  13:33            42,128 pr_child_4.exe
// 10-02-2025  13:36             2,350 pr_parent_4.c
// 10-02-2025  13:32            42,562 pr_parent_4.exe
//               10 File(s)        238,658 bytes
//                2 Dir(s)  243,303,321,600 bytes free
// Parent Process (PID: 71568) is creating a child process...
// Child Process Created (PID: 28756). Executing 'dir' command...
// Parent Process is waiting for the child to complete...
// Child Process has finished execution.
// Parent Process (PID: 71568) resumes execution.

// [Done] exited with code=0 in 3.235 seconds

