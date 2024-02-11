#include <bits/stdc++.h>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "smkm_interfaces/msg/gamepad.hpp"


int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("f310_gamepad");
    auto publisher = node->create_publisher<smkm_interfaces::msg::Gamepad>("f310_gamepad", 1);
    smkm_interfaces::msg::Gamepad f310_gamepad;
    auto subscriber = node->create_subscription<sensor_msgs::msg::Joy>("joy", 1, [&](const sensor_msgs::msg::Joy& msg){
        if(msg.buttons.size()==0)
            std::cout<<"/gamepadがF310コントローラではありません．jsのidを確認してください"<<std::endl;

        f310_gamepad.l_stick_left = msg.axes.at(0);
        f310_gamepad.l_stick_up = msg.axes.at(1);
        f310_gamepad.l_trigger = (-msg.axes.at(2) + 1)/2;
        f310_gamepad.r_stick_left = msg.axes.at(3);
        f310_gamepad.r_stick_up = msg.axes.at(4);
        f310_gamepad.r_trigger = (-msg.axes.at(5) + 1)/2;
        f310_gamepad.cross_left = msg.axes.at(6);
        f310_gamepad.cross_up = msg.axes.at(7);

        f310_gamepad.action_down = msg.buttons.at(0);
        f310_gamepad.action_right = msg.buttons.at(1);
        f310_gamepad.action_left = msg.buttons.at(2);
        f310_gamepad.action_up = msg.buttons.at(3);
        f310_gamepad.l_button = msg.buttons.at(4);
        f310_gamepad.r_button = msg.buttons.at(5);
        f310_gamepad.center_button_left = msg.buttons.at(6);
        f310_gamepad.center_button_right = msg.buttons.at(7);
        f310_gamepad.center_button = msg.buttons.at(8);
        f310_gamepad.l_stick_push = msg.buttons.at(9);
        f310_gamepad.r_stick_push = msg.buttons.at(10);

        publisher->publish(f310_gamepad);
    });

    rclcpp::spin(node);
    // node = nullptr;
    rclcpp::shutdown();
    return 0;
}