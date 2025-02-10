#include <stdio.h>
#include <windows.h>

int main() {
    char buffer[128];
    DWORD bytesRead;

    // Read message from pipe
    if (ReadFile(GetStdHandle(STD_INPUT_HANDLE), buffer, sizeof(buffer), &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';  // Null terminate the string
        printf("Child Process (PID: %lu) received message: %s\n", GetCurrentProcessId(), buffer);
    } else {
        printf("Failed to read from pipe. Error: %d\n", GetLastError());
    }

    return 0;
}

// PS D:\OScript>  & 'c:\Users\Khushi\.vscode\extensions\ms-vscode.cpptools-1.23.6-win32-x64\debugAdapters\bin\WindowsDebugLauncher.exe' '--stdin=Microsoft-MIEngine-In-i3wa3izy.53h' '--stdout=Microsoft-MIEngine-Out-ugfkgqcm.onn' '--stderr=Microsoft-MIEngine-Error-iim22j2g.2a4' '--pid=Microsoft-MIEngine-Pid-tj00j1sz.dbl' '--dbgExe=C:\MinGW\bin\gdb.exe' '--interpreter=mi' 

// [Running] cd "d:\OScript\Assignment4\" && gcc pr_child_4.c -o pr_child_4 && "d:\OScript\Assignment4\"pr_child_4

// [Done] exited with code=1 in 119.353 seconds
