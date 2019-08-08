#include "CXXWinApi.h"

#ifdef _WIN32

#include "Windows.h"

#include <sstream>

namespace spp
{

std::string CXXWinApi::getFileVersionInfo(const std::string &module /*= ""*/)
{
    TCHAR szVersionFile[MAX_PATH]; 

    if (module.empty())
    {
        GetModuleFileName(nullptr, szVersionFile, MAX_PATH);
    }
    else
    {
        strcpy(szVersionFile, module.c_str());
    }
    
    DWORD verHandle = 0;    
    DWORD verSize = GetFileVersionInfoSize(szVersionFile, &verHandle);

    if (verSize != 0)
    {
        char * verData = new char[verSize];

        if (GetFileVersionInfo(szVersionFile, verHandle, verSize, verData))
        {
            UINT size = 0;
            LPBYTE lpBuffer = nullptr;
            if (VerQueryValue(verData, "\\", (VOID FAR* FAR*)&lpBuffer, &size))
            {
                if (size > 0)
                {
                    VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd)
                    {
                        // Doesn't matter if you are on 32 bit or 64 bit,
                        // DWORD is always 32 bits, so first two revision numbers
                        // come from dwFileVersionMS, last two come from dwFileVersionLS
                        int major = (verInfo->dwFileVersionMS >> 16) & 0xffff;
                        int minor = (verInfo->dwFileVersionMS >> 0) & 0xffff;
                        int patch = (verInfo->dwFileVersionLS >> 16) & 0xffff;
                        int rev = (verInfo->dwFileVersionLS >> 0) & 0xffff;

                        std::stringstream str;
                        str << major << "." << minor << "." << patch << "." << rev;
                        return str.str();
                    }
                }
            }
        }
        delete[] verData;
    }
    return {};
}

} /* namespace spp */

#endif // _WIN32