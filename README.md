# Invertedpendulum_practice

## Overview
I did an experiment of directing the pendulum for going through waypoints. The pendulum goes through the waypoints and then comes back to home position.

## Steps for running this code
1. Clone the repository. After that, run "catkin_make" when present at the src folder, at the top of this directory.
2. Source the setup file for your shells by doing "source devel/setup.bash" when present at the src folder.
3. Run the three commands on each shell, by following the order given here. "roslaunch invpend_gazebo invpend_world.launch" , "roslaunch invpend_control invpend_control.launch" and "rosrun invpend_ctrl invpend_ctrl src/".
4. The terminal on which the last command given above will ask for number of waypoints of slider and pendulum each. You can enter how many waypoints you need each for slider and pendulum. For example, if you give the value 2, then you have to give the 2 waypoints for slider and 2 waypoints for pendulum.
  The pendulum and slider then goes through the points which you have given, and at last goes to 0 position, each for slider and pendulum.

## Working of this code
* The code consists of two important control packages used for this experiment given below. 
1. The "invpend_control" package has a launch file named "invpend_control.launch" which loads the control configurations present in the yaml file. It also loads the two position controllers used in this experiment. The yaml file consists of two position control configurations, one for "slider to cart" and other for "cart to pole." The values of PID which are initially found from "rqt_reconfigure gui" for slider and cart are fed in this yaml file. 
2. The "invpend_ctrl" package has a C++ code. The C++ code has 2 publishers and 1 subscriber. The two publishers publish the positions of slider and pendulum and the subscriber subscribes to joint_states topic. The joint_states topic gives the positions of slider and pendulum which are then used for proper positioning of the slider and pendulum. When the code is run, initially, the slider goes to -2.3 position (on X-axis) and then, we have to give the waypoints. After going through the given waypoints, the pendulum and slider go to their home positions which are 0 for slider and 0 radian for pendulum.

## Experiment highlights
### 1
![](/output/img_petrvse0.png)

Slider goes to -2.3 position
### 2
![](/output/pe0.png)
![](/output/pe1.png)

Give the number of waypoints of slider and pendulum each
### 3
![](/output/img_petrvse1.png)
![](/output/img_petrvse2.png)

Goes to the positions given by user
### 4
![](/output/last_pe.png)

Goes to home position (slider and pendulum both are zero)

### Original author and creators given below.

* Author: linZHank
> Using gazebo to simulate inverted pendulum and control through ROS
> The URDF model of the inverted pendulum and gazebo model spawn were refered to [this tutorial](http://gazebosim.org/tutorials?tut=ros_urdf&cat=connect_ros)
> Thanks to [Matthew Chan](https://medium.com/@tuzzer/cart-pole-balancing-with-q-learning-b54c6068d947) and [Arthur Juliani](https://medium.com/emergent-future/simple-reinforcement-learning-with-tensorflow-part-0-q-learning-with-tables-and-neural-networks-d195264329d0) for their brilliant tutorials.
