#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/num.hpp"
using std::placeholders::_1;

class MinimakSubsriber : public rclcpp::Node
{
public:
  MinimakSubsriber() : Node("minimal_subscriber")
  {
    subscription = this->create_subscription<my_interfaces::msg::Num>(
        "topic", 10, std::bind(&MinimakSubsriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const my_interfaces::msg::Num& msg) const
  {
    RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << msg.num << "'");
  }
  rclcpp::Subscription<my_interfaces::msg::Num>::SharedPtr subscription;
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimakSubsriber>());
  rclcpp::shutdown();
  return 0;
}