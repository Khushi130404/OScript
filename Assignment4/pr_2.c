#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent Process (PID: %lu) is creating a child process...\n", GetCurrentProcessId());

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
        )) {
        printf("Process creation failed. Error: %d\n", GetLastError());
        return 1;
    }

    printf("Child Process Created (PID: %lu)\n", pi.dwProcessId);
    printf("Parent Process is waiting for the child to complete...\n");
    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("Child Process has finished execution.\n");
    printf("Parent Process (PID: %lu) resumes execution.\n", GetCurrentProcessId());
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

// PS D:\OScript>  & 'c:\Users\Khushi\.vscode\extensions\ms-vscode.cpptools-1.23.6-win32-x64\debugAdapters\bin\WindowsDebugLauncher.exe' '--stdin=Microsoft-MIEngine-In-k35pw3y1.kcb' '--stdout=Microsoft-MIEngine-Out-w5kj5mew.nfu' '--stderr=Microsoft-MIEngine-Error-hf1qobia.1lw' '--pid=Microsoft-MIEngine-Pid-reqtjsqk.qp0' '--dbgExe=C:\MinGW\bin\gdb.exe' '--interpreter=mi' 

// [Running] cd "d:\OScript\Assignment4\" && gcc pr_2.c -o pr_2 && "d:\OScript\Assignment4\"pr_2
// Child Process Running
// Parent Process (PID: 61520) is creating a child process...
// Child Process Created (PID: 14316)
// Parent Process is waiting for the child to complete...
// Child Process has finished execution.
// Parent Process (PID: 61520) resumes execution.

// [Done] exited with code=0 in 3.23 seconds