#include "hk/svc/api.h"
#include "nn/fs.h"
#include "nn/time.h"
#include "cstdio"
#include "log.h"

#define LOG_FILE "sdmc://groove/log.txt"

using namespace nn::fs;
using namespace nn::time;


void initLog() {
    CreateFile(LOG_FILE, 0);

    log("Log initialised");
}


void vlog(const char* fmt, va_list args) {
    char msg[2048];

    const s32 msgLen = vsnprintf(msg, sizeof(msg), fmt, args);
    if (msgLen < 0) {
        return;
    }

    hk::svc::OutputDebugString(msg, std::min<size_t>(msgLen, sizeof(msg) - 1));

    FileHandle file{};

    while (true) {
        if (OpenFile(&file, LOG_FILE, OpenMode_Write).IsFailure())
            break;

        s64 fileSize = 0;
        if (GetFileSize(&fileSize, file).IsFailure())
            break;

        if (fileSize > 64 * 1024 * 1024) {
            fileSize = 0;
        }

        PosixTime pTime{};
        if (StandardUserSystemClock::GetCurrentTime(&pTime).IsFailure())
            break;

        CalendarTime cTime{};
        CalendarAdditionalInfo cTimeInfo{};
        if (ToCalendarTime(&cTime, &cTimeInfo, pTime).IsFailure())
            break;

        char newMsg[msgLen + 32];
        sprintf(newMsg, "[%04d/%02d/%02d %02d:%02d:%02d.%03lu] %s",
            cTime.year, cTime.month, cTime.day,
            cTime.hour, cTime.minute, cTime.second,
            pTime.time % 1000,
            msg
        );

        const s64 newMsgLen = static_cast<s64>(strlen(newMsg));

        if (SetFileSize(file, fileSize + newMsgLen + 1).IsFailure())
            break;

        const auto opt = WriteOption::CreateOption(WriteOptionFlag_Flush);
        static constexpr char newline = '\n';

        if (WriteFile(file, fileSize, newMsg, newMsgLen, opt).IsFailure())
            break;

        if (WriteFile(file, fileSize + newMsgLen, &newline, 1, opt).IsFailure())
            break;

        break;
    }

    CloseFile(file);
}


void log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vlog(fmt, args);
    va_end(args);
}
