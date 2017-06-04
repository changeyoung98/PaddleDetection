#ifndef PADDLE_PARAMETER_OPTIMIZER_H_
#define PADDLE_PARAMETER_OPTIMIZER_H_

#include <glog/logging.h>
#include <functional>
#include <string>
#include "OptimizerConfig.pb.h"
#include "Tensor.h"
#include "lr_policy.h"

namespace paddle {
namespace optimizer {

template <class T>
class ParameterOptimizer {
public:
  /**
   * @brief  update hook for algorithm need to traverse parameter more than
   * once.
   */
  ParameterOptimizer(const OptimizerConfig &config) : config_(config){};

  static ParameterOptimizer *create(const ::std::string &config_proto);
  virtual void update(const Tensor &gradient) = 0;
  virtual void destroy() = 0;
  virtual T *get_weight() const;
  virtual void set_weight(const Tensor<T> *parameter);
  // package optimizer config proto in runtime for saving checkpoint
  virtual char *get_config_proto();
  ~ParameterOptimzier() { delete parameter_; }

private:
  bool config_valid(::std::string &config) const;
  OptimizerConfig config_;
  Tensor<T> *parameter_;

  // learning rate policy
  BaseLr *lr_policy;
  uint64_t num_sample_passed;

  ParameterOptimizer(const ParameterOptimizer &) = delete;
  ParameterOptimizer &operator=(const ParameterOptimizer &) = delete;
  /**
   * @brief indicate if use L1, L2 regularizer
   */
};

}  // namespace optimizer
}  // namespace paddle

#endif
