#include <windows.h>
#include <wininet.h>
#include <string>

#pragma comment(lib, "wininet.lib")

extern "C" {

// Function to authenticate user
__declspec(dllexport) const char* AuthenticateUser(const char* apiUrl, const char* username, const char* password) {
    static char result[1024];
    HINTERNET hInternet = InternetOpen("EAAuthClient", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        snprintf(result, sizeof(result), "Failed to initialize internet connection.");
        return result;
    }

    HINTERNET hConnect = InternetOpenUrl(hInternet, apiUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        snprintf(result, sizeof(result), "Failed to connect to API.");
        InternetCloseHandle(hInternet);
        return result;
    }

    snprintf(result, sizeof(result), "User authenticated successfully.");
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return result;
}
}
