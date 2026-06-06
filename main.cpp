#include <windows.h>
#include <stdio.h>

void SetCleanAMOLEDAccent(){

    HKEY hKey;

    BYTE blackPalette[32] = {0};

    BYTE black = 0x00000000;

    DWORD off = 0;

    if (RegCreateKeyExW(
        HKEY_CURRENT_USER, 
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Accent", 
        0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL
    ) == ERROR_SUCCESS)
    {
        RegSetValueExW(hKey, L"AccentPalette", 0, REG_BINARY, blackPalette, sizeof(blackPalette));
        RegSetValueExW(hKey, L"AccentColor", 0, REG_DWORD, (BYTE*)&black, sizeof(black));
        RegCloseKey(hKey);
    }
    if(RegCreateKeyExW(
        HKEY_CURRENT_USER, 
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DWM", 
        0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL
    ) == ERROR_SUCCESS) 
    {
      RegSetValueExW(hKey, L"ColorizationColor", 0, REG_DWORD, (BYTE*)&black, sizeof(black));
      RegSetValueExW(hKey, L"ColorPrevalence", 0, REG_DWORD, (BYTE*)&black, sizeof(black));
      RegSetValueExW(hKey, L"EnableTransparency", 0, REG_DWORD, (BYTE*)&black, sizeof(black));
      RegCloseKey(hKey);
    }
    if(RegCreateKeyExW(
        HKEY_CURRENT_USER, 
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 
        0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL
    ) == ERROR_SUCCESS) 
    {
        RegSetValueExW(hKey, L"AppsUseLightTheme", 0, REG_DWORD, (BYTE*)&off, sizeof(off));
        RegSetValueExW(hKey, L"SystemUsesLightTheme", 0, REG_DWORD, (BYTE*)&off, sizeof(off));
        RegSetValueExW(hKey, L"EnableTransparency", 0, REG_DWORD, (BYTE*)&off, sizeof(off));
        RegCloseKey(hKey);
    }
}

int main(){
    SetCleanAMOLEDAccent();
    system("taskkill /F /IM explorer.exe > nul 2>&1"); 
    Sleep(1500);
    system("start explorer.exe");
    printf("Done");
    return 0;
}