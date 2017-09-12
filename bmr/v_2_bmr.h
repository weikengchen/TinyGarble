/*
 This file is part of TinyGarble.

 TinyGarble is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TinyGarble is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TinyGarble.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BMR_V_2_BMR_H_
#define BMR_V_2_BMR_H_

#include <string>
#include <vector>
#include <utility>
using std::vector;
using std::pair;
using std::string;

class ReadBMRGateString {
 public:
  string input[2];
  string output;
  short type;
};


class ReadBMRCircuitString {

 public:
  vector<ReadBMRGateString> gate_list_string;
  vector<ReadBMRGateString> dff_list_string;
  vector<pair<string, string>> assignment_list_string;
  uint64_t p_init_size;
  uint64_t g_init_size;
  uint64_t e_init_size;
  uint64_t p_input_size;
  uint64_t g_input_size;
  uint64_t e_input_size;
  uint64_t output_size;
  bool     has_terminate; // has terminate signal

  ReadBMRCircuitString()
      : gate_list_string(0),
        dff_list_string(0) {
    p_init_size = 0;
    g_init_size = 0;
    e_init_size = 0;
    p_input_size = 0;
    g_input_size = 0;
    e_input_size = 0;
    output_size = 0;
    has_terminate = false;
  }
};

class ReadBMRGate {
 public:
  int64_t input[2];
  int64_t output;
  short type;
};

class ReadBMRCircuit {

 public:
  vector<uint64_t> output_list;
  vector<ReadBMRGate> gate_list;
  vector<ReadBMRGate> dff_list;
  vector<uint64_t> task_schedule;

  uint64_t p_init_size;
  uint64_t g_init_size;
  uint64_t e_init_size;
  uint64_t p_input_size;
  uint64_t g_input_size;
  uint64_t e_input_size;
  uint64_t dff_size;
  uint64_t gate_size;
  uint64_t output_size;
  uint64_t wire_size; // total number of wires as required by BMR inplementation in https://github.com/cryptobiu/Semi-Honest-BMR
  uint64_t terminate_id; // terminate signal id, 0 in case of no signal

  uint64_t get_init_input_size() const {
    return p_init_size + g_init_size + e_init_size + p_input_size + g_input_size
        + e_input_size;
  }

  ReadBMRCircuit()
      : output_list(0),
        gate_list(0),
        dff_list(0),
        task_schedule(0) {
    p_init_size = 0;
    g_init_size = 0;
    e_init_size = 0;
    p_input_size = 0;
    g_input_size = 0;
    e_input_size = 0;
    dff_size = 0;
    gate_size = 0;
    output_size = 0;
    terminate_id = 0;
  }
};

int Verilog2BMR(const string &in_file_name, const string& out_mapping_filename,
                const string &out_file_name);
#endif
