# Summer SLAM
Mentor: Tanmay

Your task is to analyze a video depicting an agent navigating through an environment from a first-person perspective. The goal is to determine the agent's positional changes in terms of x and y coordinates as well as its orientation (the angle it's facing) relative to its starting point (first frame). The coordinates of the starting point are (0, 0) with an initial facing direction of 0 degrees.

---
**Deliverables:**
  - The program must publish the translation and orientation as a ROS nav_msgs/Odometry message and visualize the path covered by the agent in RViz as the frames progress.
  - You are required to write the algorithms yourself, including any deep learning methodologies if necessary.
  - However, you may utilize existing libraries such as OpenCV, PyTorch, and TensorFlow to assist you in the implementation process.

**BONUS Task:**
As a bonus, try to generate a 3D map of the surroundings of the agent along with the odometry in real time. When done, you’ll be allowed to run your code on our ground vehicle Nova.

## Setup
This repo contains the package to simulate the pov of a car travelling somewhere. You can set it up by cloning this repo as the `src` foler and building it using catkin_make/catkin build.
```zsh
git clone git@github.com:TanmayBnz/SummerSLAM.git
colcon build
```
After this you have to download the video from youtube, you can do this by running the `get_video` script in the `utils` folder inside the package. Give it executable permissions and run the script.
_Note: The download can take around 15-30 mins_
```zsh
cd src/environment/utils/
chmod 777 get_video # giving it all the permissions
./get_video
```
If this doesn't work download stacher for linux and download the [video](https://youtu.be/LQg-tdu91o4) in .mp4 format.
Finally you can launch the simulation using the roslaunch command in the workspace. (Do not forget to source the package)
```zsh
cd /path/to/ws
source install/setup.bash # or setup.zsh depending on what you're using
roslaunch enviroment environment.launch.py
```
In RViz, add a new Image visualisation for the topic "/video".
