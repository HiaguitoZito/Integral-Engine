#include <windows.h>
#include <future>

class Process {
    void start(TCHAR* argv1){
        // Start the child process. 
        if( !CreateProcess( NULL,   // No module name (use command line)
            argv1,        // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &pi )           // Pointer to PROCESS_INFORMATION structure
        ) 
        {
            return;
        }

        // Wait until child process exits.
        WaitForSingleObject( pi.hProcess, INFINITE );
    }
public:
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    TCHAR* argv1;

    Process(int argc, TCHAR* argv[]){
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &pi, sizeof(pi) );

        if( argc != 2 )
        {
            return;
        }

        argv1 = argv[1];
    }
    ~Process(){
        // Close process and thread handles. 
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    }
    void Start(){
        std::future process = std::async(std::launch::async, start, argv1);
    }
};