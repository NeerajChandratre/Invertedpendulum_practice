#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "sensor_msgs/JointState.h"
#include <iostream>
#include <sstream>
#include<functional>

class pendulum_control
{
private:
	float xp1,xp2,a,b,a1,b1;	//xp1 for slider and xp2 for pendulum
public:
  void rcve_msg(const sensor_msgs::JointState::ConstPtr& msgr)
  {
	a = (*msgr).position[1];
	a1 = (int)(a * 10);
	b = (*msgr).position[0];
	b1 = (int)(b * 10);
	xp1 = a1/10;
	xp2 = b1/10;
	std::cout<<"current slider position is "<<xp1<<std::endl;	//slider
	std::cout<<"current pendulum position is "<<xp2<<std::endl;	//pendulum
  }
  void run_steps(float d,float e) //d for slider and e for arm
  {
	ros::NodeHandle n;
  	ros::Publisher nc_pub = n.advertise<std_msgs::Float64>("/invpend/joint1_position_controller/command",1000);
    	std_msgs::Float64 msg; //slider
        ros::Publisher ncc_pub = n.advertise<std_msgs::Float64>("/invpend/joint2_position_controller/command",1000);
	ros::Subscriber sub = n.subscribe("/invpend/joint_states",1000,&pendulum_control::rcve_msg,this);
	std_msgs::Float64 msg2; //pndlm
	while(xp1!=d || xp2!=e)
	{	
		ros::spinOnce();
		ros::Rate loop_rate(10);
		loop_rate.sleep();
		msg2.data = e; //pndlm
	    	msg.data = d;  //slider";
//   		ROS_INFO("%f",dta);
		nc_pub.publish(msg);
		ncc_pub.publish(msg2);	
  	}
  }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "inpndctrl");
  pendulum_control m;
  float x[10],p[10],l1,l2,fsldr,fpdnlm;
  int i,j,h,k;
  m.run_steps(-2.3,0); //setting at home position
  std::cout<<"How many number of waypoints of slider and pendulum each?"<<std::endl;
  std::cin>>k;
  std::cout<<"Enter the waypoints of slider (values after first decimal place are neglected)"<<std::endl;
  for (i = 0; i < k; i++)
  {
  	std::cin>>x[i];	//slider
  }
  std::cout<<"Enter the waypoints of pendulum (values after first decimal place are neglected)"<<std::endl;
  for (j = 0; j < k; j++)
  {
	std::cin>>p[j];	//pendulum
  }
  for (h = 0; h < k; h ++)
  {
  	float sldr = x[h];	//slider
	l1 = (int)(sldr * 10);
        float pdnlm = p[h];	//pendulum
	l2 = (int)(pdnlm * 10);
	fsldr = l1/10;
	fpdnlm = l2/10;
	m.run_steps(fsldr,fpdnlm);
  }
  m.run_steps(0,0); //setting at (0,0)
  return 0;
}
