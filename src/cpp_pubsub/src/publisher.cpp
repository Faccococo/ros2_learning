#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"  // rcl: ros2 client library
#include "my_interfaces/msg/num.hpp"


using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher() : Node("minimal_publisher"), count(0)
  {
    publisher = this->create_publisher<my_interfaces::msg::Num>("topic", 10);
    timer = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = my_interfaces::msg::Num();
    message.num = this->count++;
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.num << "'");
    this->publisher->publish(message);
  }
  size_t count;
  rclcpp::Publisher<my_interfaces::msg::Num>::SharedPtr publisher;
  rclcpp::TimerBase::SharedPtr timer;
};

int main()
{
    rclcpp::init(0, nullptr);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}
