from launch import LaunchDescription

import launch.actions
import launch_ros.actions


def generate_launch_description():
    return LaunchDescription([

        launch.actions.ExecuteProcess(
            cmd=['ros2', 'topic', 'pub', '/clock', 'rosgraph_msgs/Clock', 'clock: {sec: 10000, nanosec: 1000}', '-r', '10'],
            output='screen'),

        launch_ros.actions.Node(
            package='bug595',
            node_executable='bug595',
            node_name='bug595',
            output='screen',
            parameters=[{'use_sim_time': True}])
    ])