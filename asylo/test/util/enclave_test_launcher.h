/*
 *
 * Copyright 2017 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ASYLO_TEST_UTIL_ENCLAVE_TEST_LAUNCHER_H_
#define ASYLO_TEST_UTIL_ENCLAVE_TEST_LAUNCHER_H_

#include "absl/memory/memory.h"
#include "asylo/client.h"
#include "asylo/util/status.h"

namespace asylo {

// Handle setup and teardown of a single enclave .so for testing.
class EnclaveTestLauncher {
 public:
  // Loads and initializes the enclave passed in |enclave_path| and calls
  // EnterAndInitialize with |econfig|.
  Status SetUp(const std::string &enclave_path, const EnclaveConfig &econfig,
               const std::string &enclave_url);

  // Calls the client's EnterAndRun method with input.
  Status Run(const EnclaveInput &input, EnclaveOutput *output);

  // Runs EnterAndFinalize with |efinal| unless |skipTearDown| is true, and then
  // destroys the enclave.
  Status TearDown(const EnclaveFinal &efinal, bool skipTearDown = false);

  // Mutable access to the loaded client.
  EnclaveClient *mutable_client() { return client_; }

  // Sets test_string in the enclave_input_test_string protobuf extension.
  static void SetEnclaveInputTestString(EnclaveInput *enclave_input,
                                        const std::string &str_test);

  // Gets test_string from the enclave_output_test_string protobuf extension.
  static const std::string &GetEnclaveOutputTestString(const EnclaveOutput &output);

 private:
  EnclaveManager *manager_;
  EnclaveClient *client_;
  std::unique_ptr<SGXLoader> loader_;
};

}  // namespace asylo

#endif  // ASYLO_TEST_UTIL_ENCLAVE_TEST_LAUNCHER_H_
