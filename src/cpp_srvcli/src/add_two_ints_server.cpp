#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/srv/add_three_ints.hpp"

#include <memory>
void add(const std::shared_ptr<my_interfaces::srv::AddThreeInts::Request> request,
         std::shared_ptr<my_interfaces::srv::AddThreeInts::Response> response)
{
    response->sum = request->a + request->b;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld", request->a, request->b);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

  rclcpp::Service<my_interfaces::srv::AddThreeInts>::SharedPtr service =
    node->create_service<my_interfaces::srv::AddThreeInts>("add_two_ints", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}