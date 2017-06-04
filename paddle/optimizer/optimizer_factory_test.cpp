#include "optimizer_factory.h"
#include "gtest/gtest.h"
#include "parameter_optimizer.h"

#define float TestType;

class OptimizerTest : public testing::Test {
public:
  virtual void SetUp() {
    paddle::OptimizerConfig config;
    config.set_learning_rate(0.01);
    config.set_decay(0.0);
    config.set_momentum(0.0);
    config.set_nesterov(false);
    config.set_lr_decay_a(0.9);
    config.set_lr_decay_b(0.1);

    std::string config_proto = config.SerializeAsString();
    ParameterOptimizer<TestType>::create(config_proto, )
  }
  virtual void TearDown() {}

private:
  ParameterOptimizer<TestType>* o;
};

TEST_F(OptimizerTest, createOptimizer) {}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
