#include <bits/stdc++.h>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "smkm_interfaces/msg/gamepad.hpp"

class F310Gamepad : public rclcpp::Node
{
public:
    F310Gamepad() : Node("f310_gamepad")
    {
        publisher_ = this->create_publisher<smkm_interfaces::msg::Gamepad>("f310_gamepad", 1);
        subscriber_ = this->create_subscription<sensor_msgs::msg::Joy>("joy", 1, [this](const sensor_msgs::msg::Joy::SharedPtr msg){
            if(msg->buttons.size() == 0)
            {
                RCLCPP_ERROR(this->get_logger(), "/gamepadがF310コントローラではありません．jsのidを確認してください");
            }

            f310_gamepad_.header.stamp = this->get_clock()->now();
            f310_gamepad_.header.frame_id = "f310_gamepad";
            f310_gamepad_.l_stick_left = msg->axes.at(0);
            f310_gamepad_.l_stick_up = msg->axes.at(1);
            f310_gamepad_.l_trigger = (-msg->axes.at(2) + 1)/2;
            f310_gamepad_.r_stick_left = msg->axes.at(3);
            f310_gamepad_.r_stick_up = msg->axes.at(4);
            f310_gamepad_.r_trigger = (-msg->axes.at(5) + 1)/2;
            f310_gamepad_.cross_left = msg->axes.at(6);
            f310_gamepad_.cross_up = msg->axes.at(7);

            f310_gamepad_.action_down = msg->buttons.at(0);
            f310_gamepad_.action_right = msg->buttons.at(1);
            f310_gamepad_.action_left = msg->buttons.at(2);
            f310_gamepad_.action_up = msg->buttons.at(3);
            f310_gamepad_.l_button = msg->buttons.at(4);
            f310_gamepad_.r_button = msg->buttons.at(5);
            f310_gamepad_.center_button_left = msg->buttons.at(6);
            f310_gamepad_.center_button_right = msg->buttons.at(7);
            f310_gamepad_.center_button = msg->buttons.at(8);
            f310_gamepad_.l_stick_push = msg->buttons.at(9);
            f310_gamepad_.r_stick_push = msg->buttons.at(10);

            publisher_->publish(f310_gamepad_);
        });
    }
private:
    smkm_interfaces::msg::Gamepad f310_gamepad_;
    rclcpp::Publisher<smkm_interfaces::msg::Gamepad>::SharedPtr publisher_;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscriber_;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<F310Gamepad>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}