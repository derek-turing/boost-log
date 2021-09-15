#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>


void init()
{
    boost::log::add_file_log
    (
        // boost::log::keywords::file_name = "sample_%N.log",    
        boost::log::keywords::file_name = "sample_.log",                                     /*< file name pattern >*/
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0), /*< ...or at midnight >*/
        boost::log::keywords::open_mode = ( std::ios::out | std::ios::app),
        //[%TimeStamp%]（%LineID%）[%ThreadID%][%Severity%] [%Tag%]：%Message%"
        boost::log::keywords::format = "[%TimeStamp%] ThreadID: %ThreadID%, Message: %Message%"   /*< log record format >*/
        
        /*需要add_common_attributes()來初始化*/
    );

     

    boost::log::core::get()->set_filter
    (        
        boost::log::trivial::severity >= boost::log::trivial::trace
    );
}
//]

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
    boost::log::add_common_attributes();  //簡單的日誌屬性初始化程式。

    // level namespace
    using namespace boost::log::trivial;
    boost::log::sources::severity_logger<severity_level> lg;  //也可以自定義日誌級別

    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";

    return 0;
}