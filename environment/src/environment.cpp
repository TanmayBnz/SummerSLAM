#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/header.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

#define FPS 30

class EnvironmentNode : public rclcpp::Node {
public:
    EnvironmentNode(const std::string& video_path)
        : Node("environment"), video_path_(video_path)
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/video", 1);
        cap_.open(video_path_);

        if (!cap_.isOpened()) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open video: %s", video_path_.c_str());
            rclcpp::shutdown();
        }

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1000 / FPS),
            std::bind(&EnvironmentNode::publish_frame, this)
        );
    }

private:
    void publish_frame() {
        cv::Mat frame;
        cap_ >> frame;

        if (frame.empty()) {
            RCLCPP_INFO(this->get_logger(), "Video ended or frame is empty.");
            rclcpp::shutdown();
            return;
        }

        auto header = std_msgs::msg::Header();
        header.stamp = this->get_clock()->now();

        cv_bridge::CvImage img_bridge;
        img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, frame);

        sensor_msgs::msg::Image img_msg;
        img_bridge.toImageMsg(img_msg);

        publisher_->publish(img_msg);

        RCLCPP_INFO(this->get_logger(), "[FRAME PUBLISHED]");
    }

    std::string video_path_;
    cv::VideoCapture cap_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    if (argc < 2) {
        std::cerr << "Usage: ros2 run your_package environment_node [video_path]" << std::endl;
        return 1;
    }

    auto node = std::make_shared<EnvironmentNode>(argv[1]);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
