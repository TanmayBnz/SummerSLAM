from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    environment_pkg_path = get_package_share_directory('environment')

    video_path = os.path.join(environment_pkg_path, 'utils', 'video.mp4')
    rviz_config_path = os.path.join(environment_pkg_path, 'config', 'viz.rviz')

    return LaunchDescription([
        Node(
            package='environment',
            executable='environment_node',
            name='environment',
            arguments=[video_path],
            output='log'
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            name='viz',
            arguments=['-d', rviz_config_path],
            output='screen'
        )
    ])
