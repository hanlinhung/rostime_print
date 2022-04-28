
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/time_zone_base.hpp>
#include <boost/date_time/local_time/local_time.hpp>



#include <iostream>
#include <ros/ros.h>

using namespace std;

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::local_time;



int main(int argc, char **argv)
{
	ros::init(argc,argv,"rostime_print");	
	ros::NodeHandle nh;
	ros::Rate r(2);


        boost::local_time::time_zone_ptr tzp_cn = boost::local_time::time_zone_ptr(new posix_time_zone("HKT+08:00:00"));
	boost::local_time::time_zone_ptr tzp_0 = boost::local_time::time_zone_ptr(new posix_time_zone("GMT+00:00:00"));
	
	while(ros::ok())
	{
		ros::Time time_now =  ros::Time::now();

		boost::posix_time::ptime my_posix_time = time_now.toBoost();
		local_date_time time0(my_posix_time.date(), my_posix_time.time_of_day(),tzp_0,local_date_time::NOT_DATE_TIME_ON_ERROR);
		local_date_time cn_time = time0.local_time_in(tzp_cn);
		
		ros::spinOnce();
		std::cout<<"ros::Time::\t"<< std::setprecision (12)  << time_now.sec + time_now.nsec/1e9<< "\t:\t" <<cn_time<<endl;
		r.sleep();
	}

	return 0;
}

