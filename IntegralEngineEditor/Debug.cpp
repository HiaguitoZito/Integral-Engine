#include <iostream>
#include <chrono>
#include <ctime>
#include <future>
#include <windows.h>

class process {
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

    process(int argc, TCHAR* argv[]){
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &pi, sizeof(pi) );

        if( argc != 2 )
        {
            return;
        }

        argv1 = argv[1];
    }
    ~process(){
        // Close process and thread handles. 
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    }
    void Start(){
        std::future process = std::async(std::launch::async, start, argv1);
    }
};

int main(int argc, TCHAR *argv[]){
    auto start = std::chrono::system_clock::now();
    
    process* p = new process(argc, argv);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;
    return 0;
}