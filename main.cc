#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

#if 0  //0 代表off, 1代表on

//[ example_tutorial_file_simple
void init()
{
    logging::add_file_log("sample.log");

    logging::core::get()->set_filter
        (
        logging::trivial::severity >= logging::trivial::info
        );
}
//]

// We need this due to this bug: https://svn.boost.org/trac/boost/ticket/4416
//[ example_tutorial_file_advanced_no_callouts
void init()
{
    logging::add_file_log
        (
        keywords::file_name = "sample_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%]: %Message%"
        );

    logging::core::get()->set_filter
        (
        logging::trivial::severity >= logging::trivial::info
        );
}
//]

#else

//[ example_tutorial_file_advanced
void init()
{
    logging::add_file_log
        (
        keywords::file_name = "sample_%N.log",                                        /*< file name pattern >*/
        keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), /*< ...or at midnight >*/
        keywords::format = "[%TimeStamp%], threadID: %ThreadID%, Message: %Message%"    /*< log record format >*/
        /*需要add_common_attributes()來初始化*/
        );

    logging::core::get()->set_filter
        (
        logging::trivial::severity >= logging::trivial::info
        );
}
//]

#endif

int main(int, char*[])
{
    init();

    /*!
    * \brief Simple attribute initialization routine
    *
    * The function adds commonly used attributes to the logging system. Specifically, the following
    * attributes are registered globally:
    *
    * \li LineID - logging records counter with value type <tt>unsigned int</tt>
    * \li TimeStamp - local time generator with value type <tt>boost::posix_time::ptime</tt>
    * \li ProcessID - current process identifier with value type
    *     <tt>attributes::current_process_id::value_type</tt>
    * \li ThreadID - in multithreaded builds, current thread identifier with
    *     value type <tt>attributes::current_thread_id::value_type</tt>
    */
    logging::add_common_attributes();  //簡單的日誌屬性初始化程式。

    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;  //也可以自定義日誌級別

    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";

    return 0;
}