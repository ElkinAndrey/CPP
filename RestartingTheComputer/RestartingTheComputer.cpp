#include <iostream>
#include <string>

#include <windows.h>

using namespace std;

struct winapi_exception {
    std::string func_;
    DWORD       code_;
    winapi_exception(const std::string& func, DWORD code)
        :func_(func)
        , code_(code)
    {}
};

struct check_error_t {
    std::string desc_;
    BOOL operator = (BOOL val) {
        if (FALSE == val)
            throw winapi_exception(desc_, GetLastError());
        return TRUE;
    }
    check_error_t(const std::string& desc)
        :desc_(desc)
    {}
};

void set_privilege(HANDLE token,
    LPCTSTR priv,
    bool enable)
{
    check_error_t chker("SetPrivilege");

    TOKEN_PRIVILEGES tp;
    LUID luid;
    TOKEN_PRIVILEGES tpPrevious;
    DWORD cbPrevious = sizeof(TOKEN_PRIVILEGES);

    chker = LookupPrivilegeValue(NULL, priv, &luid);

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = 0;

    chker = AdjustTokenPrivileges(
        token,
        FALSE,
        &tp,
        sizeof(TOKEN_PRIVILEGES),
        &tpPrevious,
        &cbPrevious);

    tpPrevious.PrivilegeCount = 1;
    tpPrevious.Privileges[0].Luid = luid;

    if (enable) {
        tpPrevious.Privileges[0].Attributes |= (SE_PRIVILEGE_ENABLED);
    }
    else {
        tpPrevious.Privileges[0].Attributes ^=
            (SE_PRIVILEGE_ENABLED & tpPrevious.Privileges[0].Attributes);
    }
    chker = AdjustTokenPrivileges(
        token,
        FALSE,
        &tpPrevious,
        cbPrevious,
        NULL,
        NULL);
}

void reboot_pc() {

    check_error_t chker("reboot_pc");
    HANDLE _token;
    chker = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &_token);
    set_privilege(_token, SE_SHUTDOWN_NAME, TRUE); // throw
    chker = InitiateSystemShutdownEx(NULL, NULL, 0, TRUE, TRUE,
        SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_MAINTENANCE | SHTDN_REASON_FLAG_PLANNED);
}


int main() {

    try {
        reboot_pc();
    }
    catch (const winapi_exception& ex) {
        cout << "Error " << ex.func_ << " Code " << ex.code_ << "\n";
    }

    return 0;
}