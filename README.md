# Setup Repository

## Introduction
This is a library which is capable to read from several can-spi-interfaces on the rasberry pi, decode them in a readable form and publish them on several topics on ROS. 


##### Install dbcppp
```
git clone --recurse-submodules https://github.com/xR3b0rn/dbcppp.git
cd dbcppp
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j
make RunTests
make install
ldconfig # on Unix-systems only
```

##### Clone the Repository in ROS

``` 
cd catkin_ws/src/

catkin_create_pkg crossi roscpp message_generation message_runtime

cd crossi/

rm -rf include/ src/ CMakeLists.txt package.xml

cd ..

git clone --recursive https://github.com/Oszimilian/CROSSI.git crossi

cd crossi/

mkdir msg

cd msg 

touch test.msg
```

##### Build the ROS-Node
Before you build the workspace you have to modify the CMakeLists.txt to tell CROSSI where to find the crossi_config.txt
```
cd ~/catkin_ws/src/crossi

nano CMakeLists.txt

#modify this:

add_definitions(-DEFAULT_CONFIG_PATH="[your_path_to_crossi_config.txt]")
```

Now you can build the workspace
```
cd ~/catkin_ws

catkin build
```

##### Start the ROS-Node

Make sure that everything is setup correctly in the crossi_config.txt file

- Start the Roscore `roscore` in a seperate terminal
- open a new terminal 
    - source the setup.bash `source devel/setup.bash`
    - start the rosnode `rosrun crossi crossi_node`
- open a new terminal
    - source the setup.bash `source devel/setup.bash`
    - look at the rostopic `rostopic info`
    - subscripe to the topic `rostopic echo /topic...`

