#include <memory>
#include <exception>
#include "rclcpp/rclcpp.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  try {
    auto node=rclcpp::Node::make_shared("minimal_subscriber");
    rclcpp::Rate loop_rate(1);


    auto ac = rclcpp::SyncParametersClient(node);


    RCLCPP_INFO(node->get_logger(), "Before first spin");
    // RCLCPP_INFO(node->get_logger(), "- param: %s",  ac.get_parameter("use_sim_time", false) ? "true": "false");
    RCLCPP_INFO(node->get_logger(), "- Node Time is %ld", node->now().nanoseconds());
    RCLCPP_INFO(node->get_logger(), "- Clock Time is %ld", rclcpp::Clock(RCL_ROS_TIME).now().nanoseconds());
    rclcpp::spin_some(node);
    RCLCPP_INFO(node->get_logger(), "After first spin");

    uint64_t counter = 1;


    while(rclcpp::ok()) {
      RCLCPP_INFO(node->get_logger(), "Count: %u", counter);
      RCLCPP_INFO(node->get_logger(), "- param: %s",  ac.get_parameter("use_sim_time", false) ? "true": "false");
      RCLCPP_INFO(node->get_logger(), "- Node Time is %ld", node->now().nanoseconds());
      RCLCPP_INFO(node->get_logger(), "- Clock Time is %ld", rclcpp::Clock(RCL_ROS_TIME).now().nanoseconds());
      rclcpp::spin_some(node);
      loop_rate.sleep();
      ++counter;
      // if (counter > 20) break;
    }
  } catch (...) {
    std::cerr << "caught exception" << std::endl;
  }
  rclcpp::shutdown();


  return 0;
}