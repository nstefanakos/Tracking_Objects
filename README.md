# Tracking_Objects
Codes for tracking objects, while they are moving in an enviroment with a fixed background.

# Codes
### Map
Designing a map around a LaserScan using an occupancy grid.

### Task1
A basic listener-talker msgs project.

### Task2
- Publish a new LaserScan msg that contains only the moving object, deleting all the points that represent the background. (Callback_1)
- Transform an RGB video in Grayscale keeping only the pixels that belong to the moving object into there original value. (Callback_2)

# Notes
- This project is designed with ROS nodes in mind.
- The LaserScan and Image msgs are stored in a rosbag that is not provided. You can change the path to your own rosbag by modifying the start.launch file.
