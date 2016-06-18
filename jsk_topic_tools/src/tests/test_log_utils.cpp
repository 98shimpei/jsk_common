#include "jsk_topic_tools/log_utils.h"
#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <gtest/gtest.h>


TEST(LogUtils, testWarnNoRemap){
  ros::NodeHandle pnh = ros::NodeHandle("~");
  ros::Publisher pub_remap = pnh.advertise<std_msgs::Header>(
    /*topic=*/"remap", /*queue_size=*/10);
  ros::Publisher pub_noremap = pnh.advertise<std_msgs::Header>(
    /*topic=*/"noremap", /*queue_size=*/10);

  std::vector<std::string> topics;
  topics.push_back(std::string("~remap"));
  bool actual;
  actual = jsk_topic_tools::warnNoRemap(topics);
  EXPECT_EQ(true, actual);

  topics.push_back(std::string("~noremap"));
  actual = jsk_topic_tools::warnNoRemap(topics);
  EXPECT_EQ(false, actual);
}

TEST(LogUtils, testGetFunctionName){
  std::string name = std::string(
    "virtual void jsk_topic_tools::ConnectionBasedNodelet::warnNeverSubscribedCallback(const ros::WallTimerEvent&)");
  std::string actual = jsk_topic_tools::getFunctionName(name);
  std::string expected = std::string("jsk_topic_tools::ConnectionBasedNodelet::warnNeverSubscribedCallback");
  ASSERT_STREQ(expected.c_str(), actual.c_str());
}

int main(int argc, char **argv){
  ros::init(argc, argv, "simple_lookup_transform");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
