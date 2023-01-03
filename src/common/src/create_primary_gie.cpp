#include "common/create_primary_gie.hpp"
#include "config/config.hpp"

GstElement* PrimaryGie::Create(std::string name){
  NvDsPrimaryGieBin *nvds_primary_gie_bin = new NvDsPrimaryGieBin();
  NvDsGieConfig *nvds_gie_config = new NvDsGieConfig();

  auto all_configs = Config::Instance()->GetAllConfig();
  auto primary_config = all_configs["gie"][name];

  std::string model_config = primary_config["model_config"];
  nvds_gie_config->config_file_path = strdup(model_config.c_str());
  auto enable =  primary_config["enable"];

  enable = enable ? 1 : 0;
  nvds_gie_config->enable = enable;
  // nvds_gie_config->batch_size = stoi(primary_config["batch_size"]);
  // nvds_gie_config->interval = stoi(primary_config["interval"]);
  // nvds_gie_config->unique_id = stoi(primary_config["unique_id"]);
  // nvds_gie_config->gpu_id = stoi(primary_config["gpu_id"]);
  // nvds_gie_config->plugin_type = NV_DS_GIE_PLUGIN_INFER;
  // nvds_gie_config->nvbuf_memory_type =  all_configs["common"]["nvbuf_memory_type"];
  

  return NULL;
}