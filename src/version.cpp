#include "uincampus/version.hpp"

namespace uin {
std::string_view version()
{
#ifdef UIN_VERSION_STRING
    return UIN_VERSION_STRING;
#else
    return "1.0.0";
#endif
}
} // namespace uin