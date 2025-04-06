#ifndef ENVIRONMENT__ENVIRONMENT_HPP_
#define ENVIRONMENT__ENVIRONMENT_HPP_

#include <string>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "opencv2/opencv.hpp"

namespace env
{
  class EnvironmentNode : public rclcpp::Node
  {
  public:
    explicit EnvironmentNode(const std::string &video_path);

  private:
    void publish_frame();

    std::string video_path_;
    cv::VideoCapture cap_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
  };
}  // namespace env

#endif  // ENVIRONMENT__ENVIRONMENT_HPP_
