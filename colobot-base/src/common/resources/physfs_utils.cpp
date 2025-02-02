#include "common/resources/physfs_utils.h"

#include "common/logger.h"

#include <string>
#include <locale>
#include <sstream>
#include <ios>
#include <iomanip>

namespace {
    // https://codereview.stackexchange.com/q/295100/238668
    std::string encode(const char *s)
    {
        if(s == nullptr) return "nullptr";
        static const std::locale cLocale("C");
        std::stringstream out;
        out << '"';
        for(; *s; ++s)
        {
            switch(*s)
            {
                case '"':
                case '?': // May need escaping due to trigraphs
                case '\\':
                           out << '\\' << *s; break;
                case '\a': out << "\\a"; break;
                case '\b': out << "\\b"; break;
                case '\f': out << "\\f"; break;
                case '\n': out << "\\n"; break;
                case '\r': out << "\\r"; break;
                case '\t': out << "\\t"; break;
                case '\v': out << "\\v"; break;
                default:
                           if(std::isprint(*s, cLocale))
                           {
                               out << *s;
                           }
                           else
                           {
                               unsigned c = static_cast<unsigned char>(*s);
                               out << '\\' << std::oct << std::setw(3) << std::setfill('0') << c;
                           }
                           break;
            }
        }
        out << '"';
        return out.str();
    }

    void reportError(const char *funcName, const char *filename)
    {
        std::stringstream out;
        out << "Error: " << funcName << "(" << encode(filename) << ")==nullptr ";
        PHYSFS_ErrorCode err = PHYSFS_getLastErrorCode();
        out << "(code: " << err << ": " << PHYSFS_getErrorByCode(err) << ") ";

        PHYSFS_Stat stat;
        if (PHYSFS_stat(filename, &stat))
        {
            out << "filesize=" << stat.filesize << " filetype=" << stat.filetype << " readonly=" << stat.readonly;
        }
        else
        {
            PHYSFS_ErrorCode err = PHYSFS_getLastErrorCode();
            out << "PHYSFS_stat() failed (code: " << err << ": " << PHYSFS_getErrorByCode(err) << ")";
        }

        GetLogger()->Error("%%", out.str());
    }
};

PHYSFS_File *LoudOpenWrite(const char *filename)
{
    PHYSFS_getLastErrorCode();  // discard previous errors
    PHYSFS_File *file = PHYSFS_openWrite(filename);
    if (file != nullptr) return file;
    reportError("PHYSFS_openWrite", filename);
    return nullptr;
}

PHYSFS_File *LoudOpenAppend(const char *filename)
{
    PHYSFS_getLastErrorCode();  // discard previous errors
    PHYSFS_File *file = PHYSFS_openAppend(filename);
    if (file != nullptr) return file;
    reportError("PHYSFS_openAppend", filename);
    return nullptr;
}

PHYSFS_File *LoudOpenRead(const char *filename)
{
    PHYSFS_getLastErrorCode();  // discard previous errors
    PHYSFS_File *file = PHYSFS_openRead(filename);
    if (file != nullptr) return file;
    reportError("PHYSFS_openRead", filename);
    return nullptr;
}
