#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    char message[] = "Hello from Parent!";
    char buffer[128];
    DWORD bytesRead, bytesWritten;
    
    // Create a pipe
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        printf("Failed to create pipe. Error: %d\n", GetLastError());
        return 1;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Set child process to inherit read handle
    si.hStdInput = hRead;
    si.dwFlags |= STARTF_USESTDHANDLES;

    printf("Parent Process (PID: %lu) is creating a child process...\n", GetCurrentProcessId());

    // Create the child process
    if (!CreateProcess(
            NULL,                   
            "cmd /c child.exe",     
            NULL,                   
            NULL,                   
            TRUE,                   
            0,                      
            NULL,                   
            NULL,                   
            &si,                    
            &pi                    
        )) {
        printf("Child process creation failed. Error: %d\n", GetLastError());
        return 1;
    }

    WriteFile(hWrite, message, sizeof(message), &bytesWritten, NULL);
    CloseHandle(hWrite); 
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hRead);
    printf("Parent Process (PID: %lu) has finished.\n", GetCurrentProcessId());
    return 0;
}

// PS D:\OScript>  & 'c:\Users\Khushi\.vscode\extensions\ms-vscode.cpptools-1.23.6-win32-x64\debugAdapters\bin\WindowsDebugLauncher.exe' '--stdin=Microsoft-MIEngine-In-pok3d413.yib' '--stdout=Microsoft-MIEngine-Out-fmdmyw42.aqt' '--stderr=Microsoft-MIEngine-Error-a2mibnci.qwq' '--pid=Microsoft-MIEngine-Pid-0mdwynrg.hci' '--dbgExe=C:\MinGW\bin\gdb.exe' '--interpreter=mi' 

// Running] cd "d:\OScript\Assignment4\" && gcc pr_parent_4.c -o pr_parent_4 && "d:\OScript\Assignment4\"pr_parent_4
// Parent Process (PID: 25488) is creating a child process...
// Parent Process (PID: 25488) has finished.
// [Done] exited with code=0 in 3.197 seconds

