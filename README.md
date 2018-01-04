# imu_subtract
To initialize imu with all zeros in the current position.

This takes ros imu message from any topic and according to the initial value of it we zero them all. 

To install - 

Clone the repositry 
```
git clone https://github.com/ajwahir/imu_subtract.git
cd imu_subtract
```

In `src/imu_subtract.cpp`, change your topic name to be subscribed and the frame id you want for this topic
```
catkin_make
source devel/setup.zsh

rosrun imu_subtract imu_subtract
```


