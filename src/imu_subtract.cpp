#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

double x_or,y_or,z_or,w_or,x_v,y_v,z_v,x_ac,y_ac,z_ac;

void imu_callback(const sensor_msgs::Imu::ConstPtr& msg)
{
    x_or = msg->orientation.x; // @TODO make sure that q0 is scalar
    y_or = msg->orientation.y;
    z_or = msg->orientation.z;
    w_or = msg->orientation.w;
    x_ac = msg->linear_acceleration.x;
    y_ac = msg->linear_acceleration.y;
    z_ac = msg->linear_acceleration.z;
    x_v = msg->angular_velocity.x;
    y_v = msg->angular_velocity.y;
    z_v = msg->angular_velocity.z;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "imu_subtract");
    ROS_INFO("Imu driver is now running");
    ros::NodeHandle nh("~");

   
    std::string frame_id = "imu_link";
    if(!nh.getParam("frame_id", frame_id))
    {
        ROS_WARN_STREAM("No frame_id provided - default: " << frame_id);
    }

    ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("imu", 100);

    ros::Subscriber imu_sub = nh.subscribe("xsens/imu", 100,imu_callback);

    ros::Rate loop_rate(10);




    sensor_msgs::Imu imu_msg;
    while (ros::ok())
    {

        imu_msg.header.stamp = ros::Time::now();
        imu_msg.header.frame_id = frame_id;

        imu_msg.orientation.x -= x_or;
        imu_msg.orientation.y -= y_or;
        imu_msg.orientation.z -= z_or;
        imu_msg.orientation.w -= w_or;

        imu_msg.angular_velocity.x -= x_v;
        imu_msg.angular_velocity.y -= y_v;
        imu_msg.angular_velocity.z -= z_v;

        imu_msg.linear_acceleration.x -= x_ac;
        imu_msg.linear_acceleration.y -= y_ac;
        imu_msg.linear_acceleration.z -= z_ac;

        imu_pub.publish(imu_msg);

        ros::spinOnce();
        loop_rate.sleep();
        
    }
    return 0;
}