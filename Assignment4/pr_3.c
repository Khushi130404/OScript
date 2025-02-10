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